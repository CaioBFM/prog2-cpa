#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long computeMinimumTextSize(int maxDepth, const vector<int>& leavesAtDepth) {
    long long minimumAllowedWeight = 1;

    // currentLevelNodes stores the weights of nodes currently being processed at a given depth
    vector<long long> currentLevelNodes;

    // Process the Huffman tree from the deepest level up to the root
    for (int depth = maxDepth; depth >= 1; depth--) {

        // Add all leaves that must appear exactly at this depth
        for (int i = 0; i < leavesAtDepth[depth]; i++) {
            currentLevelNodes.push_back(minimumAllowedWeight);
        }

        // Sort nodes to simulate Huffman's choice of the two minimum weights
        sort(currentLevelNodes.begin(), currentLevelNodes.end());

        // parentNodes stores the nodes that will be moved to the upper level
        vector<long long> parentNodes;

        // Join nodes two by two, exactly as Huffman would do in reverse
        for (int i = 0; i < (int)currentLevelNodes.size(); i += 2) {
            long long leftChild = currentLevelNodes[i];
            long long rightChild = currentLevelNodes[i + 1];

            long long parentWeight = leftChild + rightChild;
            parentNodes.push_back(parentWeight);

            // Future leaves cannot have weight smaller than the second minimum used here
            minimumAllowedWeight = max(minimumAllowedWeight, rightChild);
        }

        // Move one level up in the tree
        currentLevelNodes = parentNodes;
    }

    // After processing all levels, only the root remains.
    // Its weight is the minimum total size of the original text.
    return currentLevelNodes[0];
}

int main() {
    int numberOfCharacters;

    while (cin >> numberOfCharacters && numberOfCharacters != 0) {
        vector<int> codeLengths(numberOfCharacters);

        int maxDepth = 0;

        for (int i = 0; i < numberOfCharacters; i++) {
            cin >> codeLengths[i];
            maxDepth = max(maxDepth, codeLengths[i]);
        }

        // leavesAtDepth[d] = number of leaves with code length d
        vector<int> leavesAtDepth(maxDepth + 1, 0);

        for (int length : codeLengths) {
            leavesAtDepth[length]++;
        }

        cout << computeMinimumTextSize(maxDepth, leavesAtDepth) << endl;
    }

    return 0;
}
