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
    int testCases;
    cin >> testCases;

    for(int i = 0; i < testCases; ++i){
        int ans = 0; 

        int numberOfItens;
        cin >> numberOfItens;

        int p; // price of item
        int w; // weight of item

        int value[numberOfItens]; // array to store the value of items
        int weight[numberOfItens]; // array to store the weight of items

        for(int i = 0; i < numberOfItens; ++i){
            cin >> p;
            cin >> w;
            value[i] = p;
            weight[i] = w;
        }

        int familySize;
        cin >> familySize;

        int capacity; // capacity of each knapsack for each person

        for (int k = 0; k < familySize; ++k){
            cin >> capacity;
            ans += knapsack_PD(capacity, numberOfItens, value, weight);
        }
        
        cout << ans << endl;
    }
}