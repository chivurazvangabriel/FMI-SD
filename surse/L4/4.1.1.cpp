#include <iostream>
#include <vector>

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int x) {
        if (!node) return new Node(x);
        if (x < node->value) node->left = insert(node->left, x);
        else if (x > node->value) node->right = insert(node->right, x);
        return node;
    }

    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* erase(Node* node, int x) {
        if (!node) return nullptr;
        if (x < node->value) node->left = erase(node->left, x);
        else if (x > node->value) node->right = erase(node->right, x);
        else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->value = temp->value;
            node->right = erase(node->right, temp->value);
        }
        return node;
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void construct(const std::vector<int>& values) {
        destroy(root);
        root = nullptr;
        for (int val : values) {
            root = insert(root, val);
        }
    }

    bool exists(int x) {
        Node* curr = root;
        while (curr) {
            if (curr->value == x) return true;
            if (x < curr->value) curr = curr->left;
            else curr = curr->right;
        }
        return false;
    }

    void insert(int x) {
        root = insert(root, x);
    }

    void erase(int x) {
        root = erase(root, x);
    }

    int predecessor(int x) {
        Node* curr = root;
        int pred = -1; 
        while (curr) {
            if (curr->value < x) {
                pred = curr->value;
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
        return pred;
    }

    int successor(int x) {
        Node* curr = root;
        int succ = -1; 
        while (curr) {
            if (curr->value > x) {
                succ = curr->value;
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return succ;
    }
};