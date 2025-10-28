//
// File: two_three_test.cpp
// Author: Your Glorious Instructor
// Purpose:
//   This file is used to test the TwoThreeTree class.
//
#include <iostream>
#include <gtest/gtest.h>
#include "two_three_tree.hpp"

TEST(TwoThreeTreeTest, InsertAndSearch) {
    TwoThreeTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(5);
    tree.insert(15);
    tree.insert(25);
    tree.insert(35);

    // Test values that should be found
    EXPECT_TRUE(tree.search(10).has_value());
    EXPECT_TRUE(tree.search(20).has_value());
    EXPECT_TRUE(tree.search(30).has_value());
    EXPECT_TRUE(tree.search(5).has_value());
    EXPECT_TRUE(tree.search(15).has_value());
    EXPECT_TRUE(tree.search(25).has_value());
    EXPECT_TRUE(tree.search(35).has_value());

    // Test a value that should not be found
    EXPECT_FALSE(tree.search(40).has_value());
}

TEST(TwoThreeTreeTest, DuplicateInsert) {
    TwoThreeTree<int> tree;
    tree.insert(10);
    tree.insert(10); // Insert duplicate

    // Should still find 10
    EXPECT_TRUE(tree.search(10).has_value());
}

TEST(TwoThreeTreeTest, EmptyTreeSearch) {
    TwoThreeTree<int> tree;
    EXPECT_FALSE(tree.search(1).has_value());
}
