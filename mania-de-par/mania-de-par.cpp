#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to;
    int cost;
};

struct State {
    int cost;
    int city;
    int parity;
};

struct CompareState {
    bool operator()(const State& a, const State& b) const {
        return a.cost > b.cost; // lower cost has higher priority
    }
};

int dijkstraEvenTolls(const vector<vector<Edge>>& graph, int destination) {
    int numberOfCities = graph.size() - 1;

    // dist(i, j) = minimum cost to reach city i with parity j (0 for even, 1 for odd)
    vector<vector<int>> dist(numberOfCities + 1, vector<int>(2, INF));

    // Min-heap priority queue to store states based on cost
    priority_queue<State, vector<State>, CompareState> pq;

    dist[1][0] = 0;
    pq.push({0, 1, 0}); // cost, city, parity

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int currentCost = current.cost;
        int currentCity = current.city;
        int currentParity = current.parity;

        // If we have already found a better way to reach this city with the same parity, skip
        if (currentCost > dist[currentCity][currentParity]) {
            continue;
        }

        // Explore neighbors of the current city and update distances 
        for (const Edge& edge : graph[currentCity]) {
            int nextCity = edge.to;
            int newCost = currentCost + edge.cost;
            int newParity = 1 - currentParity;

            // If newCost is cheaper than dist(nextCity, newParity), update and push to the priority queue
            if (newCost < dist[nextCity][newParity]) {
                dist[nextCity][newParity] = newCost;
                pq.push({newCost, nextCity, newParity});
            }
        }
    }

    return dist[destination][0];
}

int main() {
    int cities, roads;
    cin >> cities >> roads;

    vector<vector<Edge>> graph(cities + 1);

    for (int i = 0; i < roads; i++) {
        int city1, city2, toll;
        cin >> city1 >> city2 >> toll;

        graph[city1].push_back({city2, toll});
        graph[city2].push_back({city1, toll});
    }

    int answer = dijkstraEvenTolls(graph, cities);

    if (answer == INF) {
        // Impossible to reach the destination with an even number of tolls, output -1
        cout << -1 << endl;
    } else {
        cout << answer << endl;
    }

    return 0;
}