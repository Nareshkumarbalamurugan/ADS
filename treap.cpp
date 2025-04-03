#include <iostream>
#include <cstdlib>
using namespace std;

struct Node {
    int key, priority;
    Node* left;
    Node* right;
    
    Node(int k) : key(k), priority(rand()), left(nullptr), right(nullptr) {}
};

class Treap {
private:
    Node* root;
    
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        return x;
    }
    
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }
    
    Node* insert(Node* root, int key) {
        if (!root) return new Node(key);
        
        if (key < root->key) {
            root->left = insert(root->left, key);
            if (root->left->priority > root->priority)
                root = rotateRight(root);
        } else {
            root->right = insert(root->right, key);
            if (root->right->priority > root->priority)
                root = rotateLeft(root);
        }
        return root;
    }
    
    Node* remove(Node* root, int key) {
        if (!root) return root;
        
        if (key < root->key)
            root->left = remove(root->left, key);
        else if (key > root->key)
            root->right = remove(root->right, key);
        else {
            if (!root->left)
                return root->right;
            else if (!root->right)
                return root->left;
            
            if (root->left->priority > root->right->priority) {
                root = rotateRight(root);
                root->right = remove(root->right, key);
            } else {
                root = rotateLeft(root);
                root->left = remove(root->left, key);
            }
        }
        return root;
    }
    
    void inorder(Node* root) {
        if (root) {
            inorder(root->left);
            cout << root->key << " ";
            inorder(root->right);
        }
    }
    
public:
    Treap() : root(nullptr) {}
    
    void insert(int key) {
        root = insert(root, key);
    }
    
    void remove(int key) {
        root = remove(root, key);
    }
    
    void printInorder() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    Treap treap;
    int choice, key;
    
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Print Inorder\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                treap.insert(key);
                break;
            case 2:
                cout << "Enter key to delete: ";
                cin >> key;
                treap.remove(key);
                break;
            case 3:
                cout << "Inorder traversal: ";
                treap.printInorder();
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
