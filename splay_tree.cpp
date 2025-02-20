#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(NULL), right(NULL) {}
};

class SplayTree {
public:
    Node* root;

    SplayTree() : root(NULL) {}

    Node* rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    Node* splay(Node* root, int key) {
        if (!root || root->key == key) return root;

        if (key < root->key) {
            if (!root->left) return root;

            if (key < root->left->key) {
                root->left->left = splay(root->left->left, key);
                root = rightRotate(root);
            } else if (key > root->left->key) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right) root->left = leftRotate(root->left);
            }
            return (root->left == NULL) ? root : rightRotate(root);
        } else {
            if (!root->right) return root;

            if (key > root->right->key) {
                root->right->right = splay(root->right->right, key);
                root = leftRotate(root);
            } else if (key < root->right->key) {
                root->right->left = splay(root->right->left, key);
                if (root->right->left) root->right = rightRotate(root->right);
            }
            return (root->right == NULL) ? root : leftRotate(root);
        }
    }

    void insert(int key) {
        if (!root) {
            root = new Node(key);
            return;
        }
        root = splay(root, key);
        if (root->key == key) return;

        Node* newNode = new Node(key);
        if (key < root->key) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = NULL;
        } else {
            newNode->left = root;
            newNode->right = root->right;
            root->right = NULL;
        }
        root = newNode;
    }

    void inorder(Node* root) {
        if (!root) return;
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }

    void printTree() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    SplayTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    cout << "Inorder traversal after insertions: ";
    tree.printTree();

    return 0;
}
