#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Recursive DFS function
void dfsRecursive(int node, const vector<vector<int>>& adjMatrix, vector<bool>& visited) {
    visited[node] = true;
    cout << node << " ";

    for (int i = 0; i < adjMatrix.size(); ++i) {
        if (adjMatrix[node][i] == 1 && !visited[i]) {
            dfsRecursive(i, adjMatrix, visited);
        }
    }
}

// Iterative DFS function
void dfsIterative(int startNode, const vector<vector<int>>& adjMatrix) {
    vector<bool> visited(adjMatrix.size(), false);
    stack<int> s;

    s.push(startNode);

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited[node]) {
            visited[node] = true;
            cout << node << " ";

            for (int i = adjMatrix.size() - 1; i >= 0; --i) {
                if (adjMatrix[node][i] == 1 && !visited[i]) {
                    s.push(i);
                }
            }
        }
    }
}

int main() {
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;

    // Initialize adjacency matrix
    vector<vector<int>> adjMatrix(V, vector<int>(V, 0));

    cout << "Enter the adjacency matrix:\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cout << "Is there an edge from " << i << " to " << j << "? (1/0): ";
            cin >> adjMatrix[i][j];
        }
    }

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. DFS Recursive\n";
        cout << "2. DFS Iterative\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            int startNode;
            cout << "Enter start node (0 to " << V - 1 << "): ";
            cin >> startNode;

            if (startNode < 0 || startNode >= V) {
                cout << "Invalid start node!\n";
                continue;
            }

            if (choice == 1) {
                vector<bool> visited(V, false);
                cout << "DFS Recursive traversal: ";
                dfsRecursive(startNode, adjMatrix, visited);
                cout << endl;
            } else if (choice == 2) {
                cout << "DFS Iterative traversal: ";
                dfsIterative(startNode, adjMatrix);
                cout << endl;
            }
        } else if (choice != 3) {
            cout << "Invalid choice!\n";
        }

    } while (choice != 3);

    cout << "Program exited.\n";
    return 0;
}
