#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include "Tree.hpp"
#include "avltree.hpp"

AVLTree<int> buildAVLTreeFromVector(const std::vector<int>& values) {
	AVLTree<int> avlTree;
	for (int value : values) {
		avlTree.insert(value);
	}
	return avlTree;
}
std::pair<double, double>& compare_search_times(const std::vector<int>& values, const AVLTree<int>& avlTree, const Tree<int>& tree) {
	static std::pair<double, double> times;

	std::vector<int>sample;
	sample.reserve(100);
	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<> dist(0, static_cast<int>(values.size()) - 1);
	for (int i = 0; i < 100 && !values.empty(); ++i)
		sample.push_back(values[dist(gen)]);

	auto startAVL = std::chrono::high_resolution_clock::now();
	for (int value : values) {
		avlTree.search(value);
	}
	auto endAVL = std::chrono::high_resolution_clock::now();
	times.first = std::chrono::duration<double, std::milli>(endAVL - startAVL).count();

	auto startTree = std::chrono::high_resolution_clock::now();
	for (int value : values) {
		tree.member(value);
	}
	auto endTree = std::chrono::high_resolution_clock::now();
	times.second = std::chrono::duration<double, std::milli>(endTree - startTree).count();
		return times;
}
std::vector<int> randomTree_to_vector(const Tree<int>& tree) {
	std::vector<int> values;
	tree.inorder([&values](int val) {values.push_back(val); });
	return values;
}
int main() {
	std::vector<int> sizes = { 100, 500, 1000, 2500, 5000, 10000 };

	for (int n : sizes) {
		const auto randomTree = make_random_tree(n);
		auto avlTree = buildAVLTreeFromVector(randomTree_to_vector(randomTree));
		const auto& times = compare_search_times(randomTree_to_vector(randomTree), avlTree, randomTree);
		std::cout << "Sizes:" << n << " | AVL Search Time: " << times.first << " ms" << " | Standard Tree Search Time:" << times.second << " ms" << std::endl;
	}
	return 0;
}