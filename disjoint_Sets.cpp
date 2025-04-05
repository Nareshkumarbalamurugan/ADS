#include <vector>

class DisjointSet {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    DisjointSet(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return;

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }

    bool isConnected(int x, int y) {
        return find(x) == find(y);
    }
}; 
int main() {
    DisjointSet ds(10); // Create a disjoint set with 10 elements

    ds.unionSets(1, 2);
    ds.unionSets(2, 3);
    ds.unionSets(4, 5);
    ds.unionSets(6, 7);
    ds.unionSets(5, 6);
    ds.unionSets(3, 7);

    std::cout << "Is 1 connected to 7? " << (ds.isConnected(1, 7) ? "Yes" : "No") << std::endl;
    std::cout << "Is 1 connected to 8? " << (ds.isConnected(1, 8) ? "Yes" : "No") << std::endl;

    return 0;
}
