#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Fibonacci Heap Node Structure
template <typename T>
struct FibNode {
    T key;
    int degree;
    FibNode *parent, *child, *left, *right;
    bool marked;

    FibNode(T val) : key(val), degree(0), parent(nullptr), child(nullptr), marked(false) {
        left = right = this;
    }
};

// Fibonacci Heap Class
template <typename T>
class FibonacciHeap {
private:
    FibNode<T>* minNode;
    int nodeCount;

    void link(FibNode<T>* y, FibNode<T>* x) {
        y->left->right = y->right;
        y->right->left = y->left;
        y->parent = x;
        y->right = y->left = y;
        if (!x->child) {
            x->child = y;
        } else {
            y->right = x->child->right;
            y->left = x->child;
            x->child->right->left = y;
            x->child->right = y;
        }
        x->degree++;
        y->marked = false;
    }

    void consolidate() {
        int maxDegree = static_cast<int>(log2(nodeCount)) + 1;
        vector<FibNode<T>*> degreeTable(maxDegree, nullptr);
        
        vector<FibNode<T>*> rootList;
        FibNode<T>* x = minNode;
        if (x) {
            do {
                rootList.push_back(x);
                x = x->right;
            } while (x != minNode);
        }
        
        for (FibNode<T>* w : rootList) {
            x = w;
            int d = x->degree;
            while (degreeTable[d]) {
                FibNode<T>* y = degreeTable[d];
                if (x->key > y->key) swap(x, y);
                link(y, x);
                degreeTable[d] = nullptr;
                d++;
            }
            degreeTable[d] = x;
        }
        
        minNode = nullptr;
        for (FibNode<T>* node : degreeTable) {
            if (node) {
                if (!minNode || node->key < minNode->key) {
                    minNode = node;
                }
            }
        }
    }

public:
    FibonacciHeap() : minNode(nullptr), nodeCount(0) {}

    void insert(T key) {
        FibNode<T>* newNode = new FibNode<T>(key);
        if (!minNode) {
            minNode = newNode;
        } else {
            newNode->right = minNode->right;
            newNode->left = minNode;
            minNode->right->left = newNode;
            minNode->right = newNode;
            if (newNode->key < minNode->key) {
                minNode = newNode;
            }
        }
        nodeCount++;
    }

    T getMin() {
        return minNode ? minNode->key : T();
    }

    void deleteMin() {
        if (!minNode) return;
        FibNode<T>* oldMin = minNode;
        if (oldMin->child) {
            FibNode<T>* child = oldMin->child;
            do {
                FibNode<T>* nextChild = child->right;
                child->left = minNode->left;
                child->right = minNode;
                minNode->left->right = child;
                minNode->left = child;
                child->parent = nullptr;
                child = nextChild;
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
    }

    void merge(FibonacciHeap<T>& other) {
        if (!other.minNode) return;
        if (!minNode) {
            minNode = other.minNode;
        } else {
            minNode->right->left = other.minNode->left;
            other.minNode->left->right = minNode->right;
            minNode->right = other.minNode;
            other.minNode->left = minNode;
            if (other.minNode->key < minNode->key) {
                minNode = other.minNode;
            }
        }
        nodeCount += other.nodeCount;
        other.minNode = nullptr;
        other.nodeCount = 0;
    }

    bool isEmpty() {
        return minNode == nullptr;
    }
};

int main() {
    FibonacciHeap<int> heap1, heap2;
    int choice, value;
    
    do {
        cout << "\nFibonacci Heap Menu";
        cout << "\n1. Insert into Heap1";
        cout << "\n2. Insert into Heap2";
        cout << "\n3. Get Min from Heap1";
        cout << "\n4. Delete Min from Heap1";
        cout << "\n5. Merge Heap1 and Heap2";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                heap1.insert(value);
                break;
            case 2:
                cout << "Enter value: ";
                cin >> value;
                heap2.insert(value);
                break;
            case 3:
                if (!heap1.isEmpty())
                    cout << "Minimum in Heap1: " << heap1.getMin() << endl;
                else
                    cout << "Heap1 is empty" << endl;
                break;
            case 4:
                heap1.deleteMin();
                cout << "Min deleted from Heap1" << endl;
                break;
            case 5:
                heap1.merge(heap2);
                cout << "Heaps merged successfully" << endl;
                break;
            case 6:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 6);
    
    return 0;
}
