#include <iostream>
using namespace std;

template <typename T>
struct LeftistNode {
    T key;
    LeftistNode *left, *right;
    int sValue; // Null Path Length (NPL)

    LeftistNode(T val) : key(val), left(nullptr), right(nullptr), sValue(1) {}
};

template <typename T>
class LeftistHeap {
private:
    LeftistNode<T> *root;

    LeftistNode<T>* merge(LeftistNode<T>* h1, LeftistNode<T>* h2) {
        if (!h1) return h2;
        if (!h2) return h1;
        if (h1->key > h2->key) swap(h1, h2);
        h1->right = merge(h1->right, h2);
        if (!h1->left || (h1->left->sValue < h1->right->sValue))
            swap(h1->left, h1->right);
        h1->sValue = h1->right ? h1->right->sValue + 1 : 1;
        return h1;
    }

public:
    LeftistHeap() : root(nullptr) {}

    void insert(T key) {
        root = merge(root, new LeftistNode<T>(key));
    }

    T getMin() {
        return root ? root->key : T();
    }

    void deleteMin() {
        if (!root) return;
        LeftistNode<T> *oldRoot = root;
        root = merge(root->left, root->right);
        delete oldRoot;
    }

    void mergeHeap(LeftistHeap<T>& other) {
        root = merge(root, other.root);
        other.root = nullptr;
    }

    bool isEmpty() {
        return root == nullptr;
    }
};

int main() {
    LeftistHeap<int> heap1, heap2;
    int choice, value;

    do {
        cout << "\nLeftist Heap Menu";
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
                if (!heap1.isEmpty()) {
                    heap1.deleteMin();
                    cout << "Min deleted from Heap1" << endl;
                } else {
                    cout << "Heap1 is empty" << endl;
                }
                break;
            case 5:
                heap1.mergeHeap(heap2);
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
