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

    Tree(std::initializer_list<T> init) : root(nullptr) {
        for (const T& val : init) {
            insert(val);
        }
	}
	Tree(const Tree& other) : root(other.root) {}
	Tree& operator=(const Tree& other) {
		if (this != &other) {
			root = other.root;
		}
		return *this;
	}
	Tree(Tree&& other) noexcept : root(std::move(other.root)) {
		other.root = nullptr;
	}

    // Insert function (already present)
    void insert(const T& val) {
        root = insertHelper(root, val, nullptr);
    }

    // Add these methods:
    bool isEmpty() const {
        return !root;
    }

    size_t size() const {
        return sizeHelper(root);
    }

    bool member(const T& val) const {
        return memberHelper(root, val);
    }

    Tree insert(T x) const {
        Tree t = *this;
        t.insert(x);
        return t;
    }

    T root() const {
        if (!root) throw std::runtime_error("Empty tree");
        return root->value;
    }

    // Traversal methods
    template<typename Func>
    void preorder(Func visit) const {
        preorderHelper(root, visit);
    }
    template<typename Func>
    void inorder(Func visit) const {
        inorderHelper(root, visit);
    }
    template<typename Func>
    void postorder(Func visit) const {
        postorderHelper(root, visit);
    }

    // Find method
    bool find(const T& val, Tree& subtreeWhereFound) const {
        Node* found = findHelper(root.get(), val);
        if (found) {
            subtreeWhereFound.root = std::make_shared<Node>(*found);
            return true;
        } else {
            subtreeWhereFound.root = nullptr;
            return false;
        }
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

    size_t sizeHelper(std::shared_ptr<Node> node) const {
        if (!node) return 0;
        return 1 + sizeHelper(node->left) + sizeHelper(node->right);
    }

    bool memberHelper(std::shared_ptr<Node> node, const T& val) const {
        if (!node) return false;
        if (val == node->value) return true;
        if (val < node->value) return memberHelper(node->left, val);
        return memberHelper(node->right, val);
    }

    void preorderHelper(std::shared_ptr<Node> node, std::function<void(T)> visit) const {
        if (!node) return;
        visit(node->value);
        preorderHelper(node->left, visit);
        preorderHelper(node->right, visit);
    }
    void inorderHelper(std::shared_ptr<Node> node, std::function<void(T)> visit) const {
        if (!node) return;
        inorderHelper(node->left, visit);
        visit(node->value);
        inorderHelper(node->right, visit);
    }
    void postorderHelper(std::shared_ptr<Node> node, std::function<void(T)> visit) const {
        if (!node) return;
        postorderHelper(node->left, visit);
        postorderHelper(node->right, visit);
        visit(node->value);
    }

    Node* findHelper(Node* node, const T& val) const {
        if (!node) return nullptr;
        if (val == node->value) return node;
        if (val < node->value) return findHelper(node->left.get(), val);
        return findHelper(node->right.get(), val);
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

