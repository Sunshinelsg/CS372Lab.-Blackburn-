//
// File:    Tree.h
// Author:  Adam.Lewis@athens.edu
// Purpose:
// Use C++ templates, STL classes and functions, and smart pointers to
// implement a binary search tree.
//
// A binary search tree is defined as being either empty, or a 3-tuple
// (left.subtree, value, right.subtree) where left.subtree is a binary search
// tree that only contains values less than our value and right.subtree is a
// binary search tree that only contains values larger than our value.
//
// Note: We are strongly encouraged by the C++ Core Guidelines to strive
// for immutability in our data structures.  This means that we should not
// modify the tree in place, but rather create a new tree that is a modified
// version of the original tree.  This is a bit of a pain, but it is the
// right thing to do.  It allows us to reason about our code more easily, and
// it allows us to use the tree in a functional programming style.  
// 
// The downside of immutability is there are is a lot of copying of data.  This
// is mitigated by the use of smart pointers, which allow us to share ownership. But even so,  
// we should be careful about how we use this class to avoid unnecessary copies.
//
#pragma once

#include <memory>
#include <functional>
#include <cassert>
#include <initializer_list>
#include <queue>
template<typename T>
class Tree {
public:
    struct Node {
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        Node* parent;
        T value;

        Node(const T& val, std::shared_ptr<Node> lft = nullptr, std::shared_ptr<Node> rgt = nullptr, Node* prnt = nullptr)
            : left(lft), right(rgt), parent(prnt), value(val) {}
    };

    std::shared_ptr<Node> root;

    Tree() : root(nullptr) {}

    // Example insert (recursive, sets parent pointer)
    void insert(const T& val) {
        root = insertHelper(root, val, nullptr);
    }

private:
    std::shared_ptr<Node> insertHelper(std::shared_ptr<Node> node, const T& val, Node* parent) {
        if (!node) return std::make_shared<Node>(val, nullptr, nullptr, parent);
        if (val < node->value)
            node->left = insertHelper(node->left, val, node.get());
        else if (val > node->value)
            node->right = insertHelper(node->right, val, node.get());
        // No duplicates
        return node;
    }
};

template<typename T>
Tree<T> prune(const Tree<T>& tree) {
    if (tree.isEmpty()) return Tree<T>();

    if (tree.left().isEmpty() && tree.right().isEmpty()) {
        return Tree<T>();
    }
    return Tree<T>(
        prune(tree.left()), tree.root(), prune(tree.right())
    );
}


// Overload the << operator to print the tree in a human-readable format   
// This is a simple implementation that prints the tree in a pre-order traversal.
// Note how the overload takes advantage of the preorder function to print the values in the tree
// and the ability to pass a callable object to the preorder function.
template<typename T>
std::ostream& operator<<(std::ostream& os, const Tree<T>& tree) {
	if (tree.isEmpty()) {
		os << "[]";
		return os;
	}
	os << "[";
	tree.preorder([&os](T val) { os << val << " "; });
	os << "]";
	return os;
}

template<typename T>
void levelTraversal(const Tree<T>& tree, std::function<void(const T&)> visit) {
    if (!tree.root) return;
    std::queue<typename Tree<T>::Node*> q;
    q.push(tree.root.get());
    while (!q.empty()) {
        auto* node = q.front(); q.pop();
        visit(node->value);
        if (node->left) q.push(node->left.get());
        if (node->right) q.push(node->right.get());
    }
}

