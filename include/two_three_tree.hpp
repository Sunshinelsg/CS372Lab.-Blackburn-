#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <queue>
#include <algorithm>

template <typename Comparable>
class TwoThreeTree {
private:
    class TwoThreeNode {
    public:
        std::vector<Comparable> keys; // Holds 1 or 2 keys
        std::vector<std::unique_ptr<TwoThreeNode>> children; // Holds 0, 2, or 3 children

        TwoThreeNode(Comparable key) {
            keys.push_back(key);
        }

        bool isLeaf() const {
            return children.empty();
        }

        bool isFull() const {
            return keys.size() == 2;
        }
    };
    std::unique_ptr<TwoThreeNode> root;

public:
    void insert(Comparable key) {
        if (!root) {
            root = std::make_unique<TwoThreeNode>(key);
            return;
        }

        auto [newRoot, promotedKey] = insertRec(root, key);
        if (newRoot) {
            auto newTreeRoot = std::make_unique<TwoThreeNode>(promotedKey.value());
            newTreeRoot->children.push_back(std::move(root));
            newTreeRoot->children.push_back(std::move(newRoot));
            root = std::move(newTreeRoot);
        }
    }

    std::optional<Comparable> search(Comparable key) const {
        return searchRec(root.get(), key);
    }

    void levelOrderTraversal() const {
        if (!root) return;

        std::queue<TwoThreeNode*> q;
        q.push(root.get());

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; ++i) {
                auto* node = q.front();
                q.pop();
                if (node != nullptr) {
                    for (int key : node->keys) {
                        std::cout << key << " ";
                    }
                    std::cout << " | ";

                    for (const auto& child : node->children) {
                        q.push(child.get());
                    }
                }
            }
            std::cout << std::endl;
        }
    }

private:
    std::pair<std::unique_ptr<TwoThreeNode>, std::optional<Comparable>> insertRec(std::unique_ptr<TwoThreeNode>& node, Comparable key) {
        if (node->isLeaf()) {
            node->keys.push_back(key);
            std::sort(node->keys.begin(), node->keys.end());
            return splitNode(node);
        }

        size_t index = 0;
        while (index < node->keys.size() && key > node->keys[index]) {
            ++index;
        }

        auto [newChild, promotedKey] = insertRec(node->children[index], key);
        if (newChild) {
            node->keys.insert(node->keys.begin() + index, promotedKey.value());
            node->children.insert(node->children.begin() + index + 1, std::move(newChild));
            return splitNode(node);
        }

        return {nullptr, std::nullopt};
    }

    std::pair<std::unique_ptr<TwoThreeNode>, std::optional<Comparable>> splitNode(std::unique_ptr<TwoThreeNode>& node) {
        if (!node->isFull()) return {nullptr, std::nullopt};

        auto newNode = std::make_unique<TwoThreeNode>(node->keys[1]);
        node->keys.pop_back();

        if (!node->isLeaf()) {
            newNode->children.push_back(std::move(node->children[1]));
            newNode->children.push_back(std::move(node->children[2]));
            node->children.resize(2);
        }

        return {std::move(newNode), node->keys[0]};
    }

    std::optional<Comparable> searchRec(const TwoThreeNode* node, Comparable key) const {
        if (!node) return std::nullopt;

        for (int nodeKey : node->keys) {
            if (key == nodeKey) return key;
        }

        if (node->isLeaf()) return std::nullopt;

        size_t index = 0;
        while (index < node->keys.size() && key > node->keys[index]) {
            ++index;
        }
        return searchRec(node->children[index].get(), key);
    }
};
