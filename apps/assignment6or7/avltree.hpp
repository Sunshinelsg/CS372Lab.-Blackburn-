// File:   avltree.hpp
// Author: Your Glorious Instructor
// Purpose:
// Provide a balanced AVL Tree
//
#pragma once
#include <iostream>
#include <algorithm>

template <typename T>
class AVLTree {
private:
    class AVLNode {
    public:
        T key;
        AVLNode* left;
        AVLNode* right;
        int height;
        AVLNode(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
    };
    AVLNode* root;

    // Get height of a node
    int height(AVLNode* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    // Get balance factor of a node
    int getBalance(AVLNode* node) {
        return (node == nullptr) ? 0 : height(node->left) - height(node->right);
    }

    // Right rotation
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    // Left rotation
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    // Insert a node in AVL tree
    AVLNode* insert(AVLNode* node, int key) {
        if (node == nullptr) return new AVLNode(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;  // Duplicates not allowed

        // Update height
        node->height = 1 + std::max(height(node->left), height(node->right));

        // Get balance factor
        int balance = getBalance(node);

        // Perform rotations if unbalanced
        // Left-Left (LL) Case
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        // Right-Right (RR) Case
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        // Left-Right (LR) Case
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right-Left (RL) Case
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Find the node with the minimum value (for deletion)
    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    // Delete a node
    AVLNode* deleteNode(AVLNode* root, int key) {
        if (root == nullptr) return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                AVLNode* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                delete temp;
            } else {
                AVLNode* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (root == nullptr) return root;

        root->height = 1 + std::max(height(root->left), height(root->right));

        int balance = getBalance(root);

        // Left-Left (LL)
        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);

        // Left-Right (LR)
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right-Right (RR)
        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);

        // Right-Left (RL)
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    // In-order traversal
    void inorder(AVLNode* root) {
        if (root != nullptr) {
            inorder(root->left);
            std::cout << root->key << " ";
            inorder(root->right);
        }
    }

    void destroy(AVLNode *node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

public:
    AVLTree() : root(nullptr) {}
    AVLTree(const AVLTree&) = default; 
    AVLTree& operator=(const AVLTree&) = default; 
    AVLTree(AVLTree&&) = default; 
    AVLTree& operator=(AVLTree&&) = default;
    virtual ~AVLTree() {
       destroy(root);
    }


    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }
    bool search(int key) const {
        AVLNode* current = root;
        while (current != nullptr) {
            if (key == current->key)
                return true;
            else if (key < current->key) current = current->left;
            else
                current = current->right;
        }
        return false;
    }

    void display() {
        inorder(root);
        std::cout << std::endl;
    }
};
