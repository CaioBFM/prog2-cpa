#include<iostream>
#include <algorithm>

using namespace std;

int knapsack(int c, const int value[], const int weight[], int n){
    int cost[n+1][c+1];

    for (int i = 0; i <= n; ++i){
        cost[i][0] = 0;
    }

    for (int w = 1; w <= c; ++w){
        cost[0][w] = 0;
    }

    for (int i = 1; i <= n; ++i){
        for(int w = 1; w <= c; ++w){
            if(weight[i - 1] > w){
                cost[i][w] = cost[i-1][w];
            } else {
                cost[i][w] = max(
                    cost[i-1][w],
                    value[i - 1] + cost[i-1][w - weight[i - 1]]
                );
            }
        }
    }
    
    return cost[n][c];
}

int main(){
    int t;
    cin >> t;

    int n;
    int p;
    int w;
    int g;
    int c;
    int ans;

    for(int i = 0; i < t; ++i){
        ans = 0;
        cin >> n;

        int value[n];
        int weight[n];

        for(int j = 0; j < n; ++j){
            cin >> p;
            cin >> w;
            value[j] = p;
            weight[j] = w;
        }

        cin >> g;

        for (int k = 0; k < g; k++){
            cin >> c;
            ans += knapsack(c, value, weight, n);
        }
        
        cout << ans << endl;

    }
}