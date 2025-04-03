#include <iostream>
#include <cmath>
using namespace std;

struct Node {
    int key;
    int degree;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    bool mark;
    
    Node(int k) : key(k), degree(0), parent(nullptr), child(nullptr), mark(false) {
        left = right = this;
    }
};

class FibonacciHeap {
private:
    Node* minNode;
    int nodeCount;
    
    void link(Node* y, Node* x) {
        y->left->right = y->right;
        y->right->left = y->left;
        y->parent = x;
        y->right = y->left = y;
        if (!x->child) {
            x->child = y;
        } else {
            y->right = x->child;
            y->left = x->child->left;
            x->child->left->right = y;
            x->child->left = y;
        }
        x->degree++;
        y->mark = false;
    }
    
    void consolidate() {
        int maxDegree = log2(nodeCount) + 1;
        Node* A[maxDegree] = {nullptr};
        
        Node* start = minNode;
        Node* x = start;
        do {
            Node* next = x->right;
            int d = x->degree;
            while (A[d]) {
                Node* y = A[d];
                if (x->key > y->key)
                    swap(x, y);
                link(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
            x = next;
        } while (x != start);
        
        minNode = nullptr;
        for (int i = 0; i < maxDegree; i++) {
            if (A[i]) {
                if (!minNode || A[i]->key < minNode->key)
                    minNode = A[i];
            }
        }
    }
    
public:
    FibonacciHeap() : minNode(nullptr), nodeCount(0) {}
    
    void insert(int key) {
        Node* newNode = new Node(key);
        if (!minNode) {
            minNode = newNode;
        } else {
            newNode->right = minNode;
            newNode->left = minNode->left;
            minNode->left->right = newNode;
            minNode->left = newNode;
            if (key < minNode->key)
                minNode = newNode;
        }
        nodeCount++;
    }
    
    int extractMin() {
        if (!minNode) {
            cout << "Heap is empty!" << endl;
            return -1;
        }
        Node* oldMin = minNode;
        int minKey = oldMin->key;
        
        if (oldMin->child) {
            Node* child = oldMin->child;
            do {
                Node* next = child->right;
                child->left->right = child->right;
                child->right->left = child->left;
                child->right = minNode;
                child->left = minNode->left;
                minNode->left->right = child;
                minNode->left = child;
                child->parent = nullptr;
                child = next;
            } while (child != oldMin->child);
        }
        
        oldMin->left->right = oldMin->right;
        oldMin->right->left = oldMin->left;
        
        if (oldMin == oldMin->right) {
            minNode = nullptr;
        } else {
            minNode = oldMin->right;
            consolidate();
        }
        
        delete oldMin;
        nodeCount--;
        return minKey;
    }
    
    void printMin() {
        if (minNode)
            cout << "Minimum key: " << minNode->key << endl;
        else
            cout << "Heap is empty!" << endl;
    }
};

int main() {
    FibonacciHeap heap;
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
