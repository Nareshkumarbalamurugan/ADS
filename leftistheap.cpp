#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int npl; // Null Path Length

    Node(int k) : key(k), left(nullptr), right(nullptr), npl(0) {}
};

class LeftistHeap {
private:
    Node* root;

    Node* merge(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;
        if (h1->key > h2->key) swap(h1, h2);
        h1->right = merge(h1->right, h2);
        if (!h1->left || (h1->left->npl < h1->right->npl)) swap(h1->left, h1->right);
        h1->npl = (h1->right) ? h1->right->npl + 1 : 0;
        return h1;
    }

public:
    LeftistHeap() : root(nullptr) {}

    void insert(int key) {
        root = merge(root, new Node(key));
    }

    int extractMin() {
        if (!root) {
            cout << "Heap is empty!" << endl;
            return -1;
        }
        int minKey = root->key;
        Node* oldRoot = root;
        root = merge(root->left, root->right);
        delete oldRoot;
        return minKey;
    }

    void printMin() {
        if (root)
            cout << "Minimum key: " << root->key << endl;
        else
            cout << "Heap is empty!" << endl;
    }
};

int main() {
    LeftistHeap heap;
    int choice, key;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Extract Min\n";
        cout << "3. Print Min\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                heap.insert(key);
                break;
            case 2:
                cout << "Extracted min: " << heap.extractMin() << endl;
                break;
            case 3:
                heap.printMin();
                break;
            case 4:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice, try again." << endl;
        }
    }

    return 0;
}
