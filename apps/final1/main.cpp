#ifndef FINAL_FRINGE_TEST
#include "Tree.hpp"
#include <iostream>

int main() {
	Tree<int> t1{ 5,8,7,3,1,6,4,2 };
	Tree<int> t2 = Tree<int>(Tree<int>{6, 3}, 9, Tree<int>{5, 8});

	auto f1 = fringe(t1);
	auto f2 = fringe(t2);

	std::cout << "Fringe of tree 1: ";
	for (int x : f1) std::cout << x << "";
	std::cout << "\n";

	std::cout << "Fringe of tree 2: ";
	for (int x : f2) std::cout << x << "";
	std::cout << "\n";

	if (sameFringe(t1, t2)) {
		std::cout << "The two trees have the same fringe.\n";
	}
}
#endif // !FINAL_FRINGE_TEST
