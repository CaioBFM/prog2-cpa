#include<iostream>
#include <algorithm>

using namespace std;

int knapsack_PD(int c, int n, const int value[], const int weight[]){
    int cost[n+1][c+1]; // cost(i, j) = max value for first i items and capacity j

    // base case: cost(i, j) = 0 if i = 0 or j = 0
    for (int i = 0; i <= n; ++i)
        cost[i][0] = 0;

    for (int w = 1; w <= c; ++w)
        cost[0][w] = 0;

    for (int i = 1; i <= n; ++i){
        for(int w = 1; w <= c; ++w){
            if(weight[i-1] > w){
                // cost(i, j) = cost(i-1, j) if vi > j
                cost[i][w] = cost[i-1][w];
            } else {
                // cost(i, j) = max(cost(i-1, j), vi + cost(i-1, j-wi)) otherwise
                cost[i][w] = max(
                    cost[i-1][w],
                    value[i-1] + cost[i-1][w - weight[i-1]]
                );
            }
        }
    }
    
    return cost[n][c];
}

int main(){
    int t; // number of test cases
    cin >> t;

    for(int i = 0; i < t; ++i){
        int ans = 0; 

        int n; // number of items
        cin >> n;

        int p; // price of item
        int w; // weight of item

        int value[n]; // array to store the price of items
        int weight[n]; // array to store the weight of items

        for(int j = 0; j < n; ++j){
            cin >> p;
            cin >> w;
            value[j] = p;
            weight[j] = w;
        }

        int g; // number of people in family
        cin >> g;

        int c; // capacity of each knapsack for each person

        for (int k = 0; k < g; k++){
            cin >> c;
            ans += knapsack_PD(c, n, value, weight);
        }
        
        cout << ans << endl;
    }
}