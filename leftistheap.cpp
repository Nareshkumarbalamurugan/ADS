#include <iostream>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
    int rank;
    
    Node(int k) : key(k), left(nullptr), right(nullptr), rank(1) {}
};

class LeftistHeap {
private:
    Node* merge(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;
        
        if (h1->key > h2->key)
            swap(h1, h2);
        
        h1->right = merge(h1->right, h2);
        
        if (!h1->left || (h1->left->rank < h1->right->rank))
            swap(h1->left, h1->right);
        
        h1->rank = h1->right ? h1->right->rank + 1 : 1;
        
        return h1;
    }
    
public:
    Node* root;
    
    LeftistHeap() : root(nullptr) {}
    
    void insert(int key) {
        Node* newNode = new Node(key);
        root = merge(root, newNode);
    }
    
    int deleteMin() {
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
    
    void mergeWith(LeftistHeap& other) {
        root = merge(root, other.root);
        other.root = nullptr;
    }
    
    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }
    
    void printHeap() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    LeftistHeap heap;
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(30);
    heap.insert(15);
    
    cout << "Heap after insertions: ";
    heap.printHeap();
    
    cout << "Deleted min: " << heap.deleteMin() << endl;
    
    cout << "Heap after deletion: ";
    heap.printHeap();
    
    return 0;
}
