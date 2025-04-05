#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfsRecursive(int node, vector<bool>& visited, const vector<vector<int>>& graph) {
    visited[node] = true;
    cout << node << " "; // Process the node
    
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfsRecursive(neighbor, visited, graph);
        }
    }
}

void dfsRecursiveStart(const vector<vector<int>>& graph, int startNode) {
    vector<bool> visited(graph.size(), false);
    dfsRecursive(startNode, visited, graph);
}
int main() {
    // Graph representation: adjacency list
    vector<vector<int>> graph = {
        {1, 2},     // Node 0
        {0, 3, 4},   // Node 1
        {0, 5},      // Node 2
        {1},         // Node 3
        {1, 5},      // Node 4
        {2, 4}       // Node 5
    };
    
    cout << "Recursive DFS: ";
    dfsRecursiveStart(graph, 0);
    cout << endl;
    
    cout << "Iterative DFS: ";
    dfsIterative(graph, 0);
    cout << endl;
    
    return 0;
}
