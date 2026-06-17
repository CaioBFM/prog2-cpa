#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <functional>

using namespace std;

const int INF = 1000000000;

int dijkstraPar(const vector<vector<pair<int, int>>>& graph, int c) {
    vector<vector<int>> dist(c + 1, vector<int>(2, INF));

    dist[1][0] = 0;

    priority_queue<
        tuple<int, int, int>,
        vector<tuple<int, int, int>>,
        greater<tuple<int, int, int>>
    > minHeap;

    minHeap.push(make_tuple(0, 1, 0)); // cost, city, parity

    while (!minHeap.empty()) {
        auto [currentCost, currentCity, currentParity] = minHeap.top();
        minHeap.pop();

        if (currentCost > dist[currentCity][currentParity]) {
            continue;
        }

        for (auto [nextCity, toll] : graph[currentCity]) {
            int newCost = currentCost + toll;
            int newParity = 1 - currentParity;

            if (newCost < dist[nextCity][newParity]) {
                dist[nextCity][newParity] = newCost;
                minHeap.push(make_tuple(newCost, nextCity, newParity));
            }
        }
    }

    return dist[c][0];
}

int main() {
    int c;
    int v;
    cin >> c;
    cin >> v;

    vector<vector<pair<int, int>>> graph(c + 1);

    int c1, c2, g;

    for (int i = 0; i < v; ++i) {
        cin >> c1 >> c2 >> g;

        graph[c1].push_back({c2, g});
        graph[c2].push_back({c1, g});
    }

    int result = dijkstraPar(graph, c);

    if (result == INF) {
        cout << -1 << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}