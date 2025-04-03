#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int rank;

    Node(int k) : key(k), left(nullptr), right(nullptr), rank(1) {}
};

class LeftistHeap {
private:
    Node* root;

    Node* merge(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        if (h1->key > h2->key)
            swap(h1, h2);

        h1->right = merge(h1->right, h2);

        if (!h1->left || (h1->right && h1->left->rank < h1->right->rank))
            swap(h1->left, h1->right);

        h1->rank = h1->right ? h1->right->rank + 1 : 1;
        return h1;
    }

public:
    LeftistHeap() : root(nullptr) {}

    void insert(int key) {
        Node* newNode = new Node(key);
        root = merge(root, newNode);
    }

    int extractMin() {
        if (!root) {
            cout << "Heap is empty!" << endl;
            return -1;
        }
        int minKey = root->key;
        Node* temp = root;
        root = merge(root->left, root->right);
        delete temp;
        return minKey;
    }

    void mergeWith(LeftistHeap& otherHeap) {
        root = merge(root, otherHeap.root);
        otherHeap.root = nullptr; 
    }

    void printMin() {
        if (!root) cout << "Heap is empty!" << endl;
        else cout << "Minimum key: " << root->key << endl;
    }
};

int main() {
    LeftistHeap heap1, heap2;
    int choice, key;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Extract Min\n";
        cout << "3. Print Min\n";
        cout << "4. Merge Two Heaps\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                heap1.insert(key);
                break;
            case 2:
                cout << "Extracted Min: " << heap1.extractMin() << endl;
                break;
            case 3:
                heap1.printMin();
                break;
            case 4:
                cout << "Enter elements for second heap (-1 to stop): ";
                while (true) {
                    cin >> key;
                    if (key == -1) break;
                    heap2.insert(key);
                }
                heap1.mergeWith(heap2);
                cout << "Heaps merged successfully!" << endl;
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice, try again." << endl;
        }
    }
}
