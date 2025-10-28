//
// File:   avltest.cpp
// Author: Your Glorious Instructor
// Purpose:
// Test the AVLTree class

#include <iostream>
#include "avltree.hpp"

int main() {
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    std::cout << "AVL Tree after insertion: ";
    tree.display();

    tree.remove(30);
    std::cout << "AVL Tree after deletion of 30: ";
    tree.display();

    return 0;
}

