#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int main(){

    int n, l;
    while (cin >> l && l != 0) {
        cin >> n;

        int c[n+2];
        c[0] = 0;
        c[n+1] = l;
        for (int i=1; i<n+1; i++){
            cin >> c[i];
        }

        int cost[n+2][n+2];

        //Casos base
        for (int i=0; i<n+2; i++){
            for (int j=0; j<n+2; j++){
                if ((j==i) || (j == i+1))
                    cost[i][j] = 0;
            }
        }

        int minCost;
        int j, currentCost;
        
        for (int g= 2; g< n+2; g++) { // Controle para preencher a matriz na ordem correta
            for (int i=0; i< n+2-g; i++) {
                int j= i+g;

                minCost = INT_MAX;

                for (int k=i+1; k<j; k++){
                    currentCost = cost[i][k]+ cost[k][j];
                    minCost = min (currentCost, minCost);
                }

                cost[i][j] = c[j] - c[i] + minCost;
            }
        }    
        cout << cost[0][n+1] << endl;
    }

    return 0;
}