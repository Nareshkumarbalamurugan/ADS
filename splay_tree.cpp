#include <iostream>

using namespace std;

struct Node {
    int key;
    Node *left, *right;
};

Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = node->right = nullptr;
    return node;
}

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
    if (root == nullptr || root->key == key)
        return root;

    if (root->key > key) {
        if (root->left == nullptr)
            return root;
        if (root->left->key > key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        else if (root->left->key < key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != nullptr)
                root->left = leftRotate(root->left);
        }
        return (root->left == nullptr) ? root : rightRotate(root);
    }
    else {
        if (root->right == nullptr)
            return root;
        if (root->right->key > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != nullptr)
                root->right = rightRotate(root->right);
        }
        else if (root->right->key < key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        return (root->right == nullptr) ? root : leftRotate(root);
    }
}

Node* insert(Node* root, int key) {
    if (root == nullptr)
        return newNode(key);

    root = splay(root, key);

    if (root->key == key)
        return root;

    Node* node = newNode(key);
    if (root->key > key) {
        node->right = root;
        node->left = root->left;
        root->left = nullptr;
    }
    else {
        node->left = root;
        node->right = root->right;
        root->right = nullptr;
    }
    return node;
}

void preOrder(Node* node) {
    if (node != nullptr) {
        cout << node->key << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
}

int main() {
    Node* root = nullptr;
    root = insert(root, 100);
    root = insert(root, 50);
    root = insert(root, 200);
    root = insert(root, 40);
    root = insert(root, 60);
    cout << "Preorder traversal of the modified Splay tree:" << endl;
    preOrder(root);
    return 0;
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    #include <iostream>
using namespace std;

// Node structure for the Splay Tree
class SplayTreeNode {
public:
    int key;
    SplayTreeNode* left;
    SplayTreeNode* right;
    SplayTreeNode* parent;

    SplayTreeNode(int key) {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    }
};

// Splay Tree class
class TopDownSplayTree {
private:
    SplayTreeNode* root;

    // Function to perform rotations
    void rotate(SplayTreeNode* x) {
        SplayTreeNode* p = x->parent;
        SplayTreeNode* g = p->parent;

        if (x == p->left) {
            // Right rotation
            p->left = x->right;
            if (x->right) x->right->parent = p;
            x->right = p;
        } else {
            // Left rotation
            p->right = x->left;
            if (x->left) x->left->parent = p;
            x->left = p;
        }

        p->parent = x;
        x->parent = g;

        // If g is not null, connect the new subtree
        if (g) {
            if (g->left == p) {
                g->left = x;
            } else {
                g->right = x;
            }
        } else {
            root = x; // x is now the root
        }
    }

    // Top-Down splay operation to bring x to root
    void topDownSplay(SplayTreeNode* x) {
        while (x->parent != nullptr) {
            SplayTreeNode* p = x->parent;
            SplayTreeNode* g = p->parent;

            if (g == nullptr) {
                // Zig operation (single rotation)
                rotate(x);
            } else if ((x == p->left && p == g->left) || (x == p->right && p == g->right)) {
                // Zig-zig operation (double rotation)
                rotate(p);
                rotate(x);
            } else {
                // Zig-zag operation (double rotation)
                rotate(x);
                rotate(x);
            }
        }
    }

public:
    TopDownSplayTree() {
        root = nullptr;
    }

    // Insert a new key into the tree
    void insert(int key) {
        if (root == nullptr) {
            root = new SplayTreeNode(key);
            return;
        }

        SplayTreeNode* current = root;
        SplayTreeNode* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        SplayTreeNode* newNode = new SplayTreeNode(key);
        if (key < parent->key) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
        newNode->parent = parent;

        // Perform the top-down splay operation
        topDownSplay(newNode);
    }

    // Search for a key and splay the found node to the root
    void search(int key) {
        SplayTreeNode* current = root;

        while (current != nullptr && current->key != key) {
            if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (current != nullptr) {
            topDownSplay(current);
        }
    }

    // Helper function to print the tree (in-order traversal)
    void inorder(SplayTreeNode* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

    void printTree() {
        inorder(root);
        cout << endl;
    }
};

// Main function to test the Splay Tree
int main() {
    TopDownSplayTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(15);

    cout << "In-order traversal after inserts: ";
    tree.printTree();

    tree.search(15);
    cout << "In-order traversal after searching for 15: ";
    tree.printTree();

    tree.search(5);
    cout << "In-order traversal after searching for 5: ";
    tree.printTree();

    return 0;
}

