#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int dijkstraPar(const vector<vector<int>>& graph, int c){
	vector<vector<int>> dist(c + 1, vector<int>(2, 10001));
	for(int i = 1; i <= c; ++i){
		dist[i][0] = 10001;
		dist[i][1] = 10001;
	}

	dist[1][0] = 0;

	priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> minHeap;

	minHeap.push(make_tuple(0, 1, 0)); // cost, city, parity

	while(!minHeap.empty()){

		auto [currentCost, currentCity, currentParity] = minHeap.top();
		minHeap.pop();

		if(currentCost > dist[currentCity][currentParity]){
			continue;
		}

		for(int nextCity = 1; nextCity <= c; ++nextCity){

			if(graph[currentCity][nextCity] != 0){
				int newCost = currentCost + graph[currentCity][nextCity];
				int newParity = 1 - currentParity; // toggle parity

				// update distance if a shorter path is found
				if(newCost < dist[nextCity][newParity]){
					dist[nextCity][newParity] = newCost;
					minHeap.push(make_tuple(newCost, nextCity, newParity));
				}
			}
		}
	}

	return dist[c][0];
}

int main(){
	int c;
	int v;
	cin >> c;
	cin >> v;
	
	vector<vector<int>> graph(c + 1, vector<int>(c + 1, 0));
	
	int c1, c2, g;

	for(int i = 0; i < v; ++i){
		cin >> c1 >> c2 >> g;
		graph[c1][c2] = g;
		graph[c2][c1] = g;
	}

	int result = dijkstraPar(graph, c);
	if(result == 10001){
		cout << -1 << endl; // no path found
	} else {
		cout << result << endl;
	}

}
