#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int main(){
    int n;
    while (cin >> n && n != 0) {
    
        vector<int> sizes(n);
        for (int i=0; i<n; i++)
            cin>> sizes[i];

        map<int,int> levels;
        int maxLevel=0;
        for (int num : sizes){
            levels[num]++;
            if (num> maxLevel)
                maxLevel = num;
        }

        priority_queue<long long, vector<long long>, greater<long long>> heap;
        long long currentValue = 1;

        for (int level = maxLevel; level >=1; level--){
            if (levels.count(level)){ //false se for 0, true se >0
                for (int i = 0; i < levels[level]; i++) {
                    heap.push(currentValue); // Folhas do último nível
                }
            }

            if (n == 1) {
                continue;
            }

            int levelElements = heap.size(); 
            vector<long long> parents;

            while (heap.size() >= 2) { // Pra impedir que as folhas próprias do nível se fundam com os nós intermediarios
                long long child1 = heap.top(); heap.pop();
                long long child2 = heap.top(); heap.pop();

                currentValue = max(currentValue, child2);
                parents.push_back(child1 + child2);
            }
        
            for (long long parent : parents){
                heap.push(parent);
            }
        }

        if (!heap.empty()) {
            cout << heap.top() << endl;
        }
    }
        
    return 0; 
}