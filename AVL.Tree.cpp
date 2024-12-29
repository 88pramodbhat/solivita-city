#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
    
    Node(int value) {
        data = value;
        left = right = nullptr;
        height = 1;
    }
};

int height(Node* node) {
    return (node == nullptr) ? 0 : node->height;
}
int getBalance(Node* node) {
    return (node == nullptr) ? 0 : height(node->left) - height(node->right);
}
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    
    return y;
}

Node* insert(Node* node, int key) {
    if (node == nullptr)
        return new Node(key);
    
    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    else
        return node;
  
    node->height = 1 + max(height(node->left), height(node->right));
  
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->data)
        return rightRotate(node);
  
    if (balance < -1 && key > node->right->data)
        return leftRotate(node);
  
    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
  
    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}

void preOrder(Node* root) {
    if (root != nullptr) {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}
int main() {
    Node* root = nullptr;  
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 15);
    root = insert(root, 25);
    
    cout << "Pre-order traversal of the AVL tree: ";
    preOrder(root);
    
    return 0;
}
