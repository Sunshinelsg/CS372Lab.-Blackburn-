//
// File:   TreeFixture.cpp
// Author: Your Glorious Instructor
// Purpose:
//  Provide unit tests for our Tree class
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <random>
#include <list>
#include "Tree.hpp"

// We are violating one of the conventions of unit testing here by 
// providing some global state .  This is done to make the tests
// easier to write and read.  In a production system, we would 
// use a fixture to set up the state for each test, but that would
// make the tests more verbose and harder to read. 

Tree<int> aTree{ 45,74,28,32,44, 100 };
std::list<int> resultList;
void printIt(int thing) { std::cout << thing << " "; }
void addToResult(int thing) { resultList.push_back(thing); }

template <typename Iterable>
void printAny(Iterable aContainer) {
	for (auto aThing : aContainer) {
		std::cout << aThing << " ";
	}
	std::cout << std::endl;
}

// The first set of tests will verify that the tree is constructed correctly.

// Test: Verify that the tree size is correct after construction
// Precondition: A tree has been constructed with 6 elements.
// Postcondition: The tree size should be 6.
TEST(TreeConstruct, TreeSize) {
    EXPECT_EQ(aTree.size(), 6);
}

// Test: Verify that an empty tree behaves correctly
// Precondition: An empty tree is created.
// Postcondition: The tree should be empty, size should be 0, 
// and member() should return false for any value.
TEST(TreeConstruct, EmptyTree) {
    Tree<int> emptyTree;
    EXPECT_TRUE(emptyTree.isEmpty());
    EXPECT_EQ(emptyTree.size(), 0u);
    EXPECT_FALSE(emptyTree.member(1));
}

// Test: Verify initializer list constructor
// Precondition: A tree is constructed using an initializer list.
// Postcondition: The tree should contain the elements from the initializer list,
TEST(TreeConstruct, InitializerListConstructor) {
    Tree<int> t{ 1, 2, 3, 4 };
    EXPECT_EQ(t.size(), 4u);
    EXPECT_TRUE(t.member(3));
    EXPECT_FALSE(t.member(99));
}

// Test: Verify that the copy constructor and assignment operator work correctly
// Precondition: A tree is constructed with some elements.
// Postcondition: The copied tree should have the same elements and size as the original tree.
TEST(TreeConstruct, CopyConstructorAndAssignment) {
    Tree<int> t1{ 1, 2, 3 };
    Tree<int> t2 = t1; // Copy constructor
    EXPECT_EQ(t1.size(), t2.size());
    EXPECT_TRUE(t2.member(2));

    Tree<int> t3;
    t3 = t1; // Copy assignment
    EXPECT_EQ(t3.size(), t1.size());
    EXPECT_TRUE(t3.member(3));
}
// Test: Verify that the move constructor and assignment operator work correctly
// Precondition: A tree is constructed with some elements.
// Postcondition: The moved tree should have the same elements and size as the original tree,
// and the original tree should be empty.
TEST(TreeConstruct, MoveConstructorAndAssignment) {
    Tree<int> t1{ 1, 2, 3 };
    Tree<int> t2 = std::move(t1); // Move constructor
    EXPECT_EQ(t2.size(), 3u);

    Tree<int> t3;
    t3 = std::move(t2); // Move assignment
    EXPECT_EQ(t3.size(), 3u);
}

// Test: Verify that the tree can handle strings
// Precondition: A tree is constructed with string elements.
// Postcondition:
TEST(TreeConstruct, TreeWithStrings) {
    Tree<std::string> t{ "apple", "banana", "cherry" };
    EXPECT_TRUE(t.member("banana"));
    EXPECT_FALSE(t.member("date"));
    EXPECT_EQ(t.size(), 3u);
}

// The next set of tests will verify that the tree can be modified correctly.

// Test insert and member functions
// Precondition: A tree is created and elements are inserted.
// Postcondition: The member function should return true for inserted elements 
// and false for non-inserted elements.
TEST(TreeModify, InsertAndMember) {
    Tree<int> t;
    t = t.insert(10);
    t = t.insert(5);
    t = t.insert(20);

    EXPECT_TRUE(t.member(10));
    EXPECT_TRUE(t.member(5));
    EXPECT_TRUE(t.member(20));
    EXPECT_FALSE(t.member(15));
}

// Test insert function with existing elements
TEST(TreeModify, InsertExistingElements) {
    Tree<int> t;
    t = t.insert(10);
    t = t.insert(20);
    t = t.insert(5);

    EXPECT_TRUE(t.member(10));
    EXPECT_TRUE(t.member(20));
    EXPECT_TRUE(t.member(5));
    EXPECT_EQ(t.size(), 3); // Size should be 3 after insertions
}
// Test insert function with duplicates
TEST(TreeModify, InsertDuplicates) {
    Tree<int> t;
    t = t.insert(10);
    t = t.insert(10); // Duplicate insert
    t = t.insert(20);

    EXPECT_TRUE(t.member(10));
    EXPECT_TRUE(t.member(20));
    EXPECT_EQ(t.size(), 2); // Size should be 2, as duplicates are not added
}
// Test: Verify that insert does not add duplicates
// Precondition: A tree has been constructed with specific values.
// Postcondition: The size of the tree should not change when trying to insert a duplicate value.
TEST(TreeModify, InsertNoDuplicates) {
    Tree<int> t = aTree.insert(45); // 45 already present
    EXPECT_EQ(t.size(), aTree.size());
}

// Test: Verify that insert adds a new value
// Precondition: A tree has been constructed with specific values.
// Postcondition: The size of the tree should increase by 1 when a new value is inserted.
TEST(TreeModify, InsertAddsValue) {
    Tree<int> t = aTree.insert(200);
    EXPECT_TRUE(t.member(200));
    EXPECT_EQ(t.size(), aTree.size() + 1);
}

// Test: Verify that can correctly insert into an empty tree
// Precondition: An empty tree is created.
// Postcondition: The new tree should contain the inserted value, and its size should be 1.
TEST(TreeModify, InsertIntoEmptyTree) {
	Tree<int> emptyTree;
	Tree<int> newTree = emptyTree.insert(42);
	EXPECT_TRUE(newTree.member(42));
	EXPECT_EQ(newTree.size(), 1u);
}

// Test: Insertion Edge Cases
// Precondition: A tree has been constructed with specific values.
// Postcondition: The tree should handle edge cases like inserting negative values
// and duplicates correctly.
TEST(TreeModify, InsertDuplicatesAndNegatives) {
    Tree<int> t;
    t = t.insert(-10);
    t = t.insert(-10); // duplicate
    t = t.insert(0);
    EXPECT_EQ(t.size(), 2u);
    EXPECT_TRUE(t.member(-10));
    EXPECT_TRUE(t.member(0));
}

// The next set of tests will verify that the tree can be searched correctly.
// 
// Test: Verify that member() correctly identifies present and absent values.
// Precondition: A tree has been constructed with specific values.
// Postcondition: The member function should return true for present values 
// and false for absent values.
TEST(TreeSearch, MemberFunction) {
    EXPECT_TRUE(aTree.member(45));
    EXPECT_TRUE(aTree.member(74));
    EXPECT_FALSE(aTree.member(999));
    EXPECT_FALSE(aTree.member(-1));
}

// Test: Verify find() returns correct value and bool
// Precondition: A tree has been constructed with specific values.
// Postcondition: The find function should return true for present values,
TEST(TreeSearch, FindFunction) {
    bool found = false;
    Tree<int> foundTree;
    found = aTree.find(45, foundTree);
    EXPECT_TRUE(found);
    EXPECT_EQ(foundTree.root(), 45);
    found = aTree.find(99, foundTree);
    EXPECT_FALSE(found);
    EXPECT_TRUE(foundTree.isEmpty()); // Should be empty if not found
    found = aTree.find(100, foundTree);
    EXPECT_TRUE(found);
    found = aTree.find(28, foundTree);
    EXPECT_TRUE(found);
    EXPECT_EQ(foundTree.root(), 28);
    found = aTree.find(32, foundTree);
    EXPECT_TRUE(found);
    EXPECT_EQ(foundTree.root(), 32);
    found = aTree.find(44, foundTree);
    EXPECT_TRUE(found);
    EXPECT_EQ(foundTree.root(), 44);
    found = aTree.find(74, foundTree);
    EXPECT_TRUE(found);
    EXPECT_EQ(foundTree.root(), 74);
    found = aTree.find(12345, foundTree);
    EXPECT_FALSE(found);
    EXPECT_TRUE(foundTree.isEmpty()); // Should be empty if not found
}

// The next set of tests will verify that the tree can be traversed correctly.

// Test: Traversal Orders
// Precondition: A BST has been created with specific values.
// Postcondition: The traversal orders (preorder, inorder, postorder)
// should be correct.
TEST(TreeTraversal, TraversalOrders) {
    Tree<int> t{ 3, 1, 4, 2 };
    std::vector<int> preorder, inorder, postorder;
    t.preorder([&](int v) { preorder.push_back(v); });
    t.inorder([&](int v) { inorder.push_back(v); });
    t.postorder([&](int v) { postorder.push_back(v); });

    // Preorder: root, left, right
    EXPECT_EQ(preorder.front(), 3);
    // Inorder: should be sorted
    EXPECT_EQ(inorder, (std::vector<int>{1,2,3,4}));
    // Postorder: left, right, root
    EXPECT_EQ(postorder.back(), 3);
}

// Test: Verify that a preorder traversal happens in correct order
// Precondition: A BST has been created
// Postcondition: A list is created that has the correct preorder walk
//                of the tree.
TEST(TreeTraversal, InorderTraversal) {
	aTree.inorder(addToResult);
	printAny(resultList);
	aTree.inorder(printIt);
	resultList.clear();
}
// Test: Verify that a preorder traversal happens in correct order
// Precondition: A BST has been created
// Postcondition: A list is created that has the correct preorder walk
//                of the tree.
TEST(TreeTraversal, PreorderTraversal) {
    aTree.preorder(addToResult);
    printAny(resultList);
    aTree.preorder(printIt);
    resultList.clear();
}

// Test: Verify that a preorder traversal happens in correct order
// Precondition: A BST has been created
// Postcondition: A list is created that has the correct preorder walk
//                of the tree.
TEST(TreeTraversal, PostorderTraversal) {
    aTree.postorder(addToResult);
    printAny(resultList);
    aTree.postorder(printIt);
    resultList.clear();
}

// And finally, we will test the size of the tree.

// Test: Size of an empty tree should be zero
// Precondition: An empty tree is created.
// Postcondition: The size of the tree should be 0.
TEST(TreeSizeTests, EmptyTreeSize) {
    Tree<int> t;
    EXPECT_EQ(t.size(), 0u);
}

// Test: Size after inserting unique elements
// Precondition: A tree is created and elements are inserted.
// Postcondition: The size of the tree should equal the number 
// of unique elements inserted.
TEST(TreeSizeTests, SizeAfterInsertions) {
    Tree<int> t;
    t = t.insert(10);
    t = t.insert(20);
    t = t.insert(5);
    EXPECT_EQ(t.size(), 3u);
}

// Test: Size does not increase when inserting duplicates
// Precondition: A tree is created and elements are inserted.
// Postcondition: The size of the tree should not increase when duplicates are inserted.
TEST(TreeSizeTests, SizeWithDuplicates) {
    Tree<int> t;
    t = t.insert(10);
    t = t.insert(10); // duplicate
    t = t.insert(20);
    t = t.insert(20); // duplicate
    EXPECT_EQ(t.size(), 2u);
}

// Test: Size with initializer list constructor
// Precondition: A tree is constructed using an initializer list.
// Postcondition: The size of the tree should equal the number of elements 
// in the initializer list.
TEST(TreeSizeTests, SizeWithInitializerList) {
    Tree<int> t{ 1, 2, 3, 4, 5 };
    EXPECT_EQ(t.size(), 5u);
}

// Test: Size after multiple insertions and checking immutability
// Precondition: A tree is created and elements are inserted.
// Postcondition: The size of the original tree should remain unchanged after insertions.
TEST(TreeSizeTests, SizeImmutability) {
    Tree<int> t1;
    Tree<int> t2 = t1.insert(1);
    Tree<int> t3 = t2.insert(2);
    EXPECT_EQ(t1.size(), 0u);
    EXPECT_EQ(t2.size(), 1u);
    EXPECT_EQ(t3.size(), 2u);
}


// Test: Find function with existing elements operates as expected.
// Precondition: A tree is created and elements are inserted.
// Postcondition: The find function should return true for existing elements,
TEST(TreeSearch, Find) {
    Tree<int> t;
	Tree<int> resultTree;
    t = t.insert(7);
    t = t.insert(3);
    t = t.insert(9);

    bool found = t.find(3, resultTree);
    ASSERT_NE(found, false);
    EXPECT_EQ(resultTree.root(), 3);

    found = t.find(9, resultTree);
    ASSERT_NE(found, false);
    EXPECT_EQ(resultTree.root(), 9);

    found = t.find(8, resultTree);
    EXPECT_EQ(found, false); // Should not find 8
	EXPECT_TRUE(resultTree.isEmpty()); // resultTree should be empty if not found	
}

// Test: find function with non-existent element
// Precondition: A tree is created and elements are inserted.
// Postcondition: The find function should return false for non-existent elements,
TEST(TreeSearch, FindNonExistent) {
	Tree<int> t;
	Tree<int> resultTree;
	t = t.insert(1);
	t = t.insert(2);
	t = t.insert(3);

	bool found = t.find(4, resultTree);
	EXPECT_EQ(found, false); // Should not find 4
	EXPECT_TRUE(resultTree.isEmpty()); // resultTree should be empty if not found
	EXPECT_EQ(resultTree.size(), 0); // Size should be 0 if not found
	EXPECT_EQ(t.size(), 3); // Original tree size should remain unchanged
	EXPECT_FALSE(t.member(4)); // Should not be a member of the tree
}

// Test: find function with empty tree
// Precondition: An empty tree is created.
// Postcondition: The find function should return false and resultTree should be empty.
TEST(TreeSearch, FindEmptyTree) {
	Tree<int> t;
	Tree<int> resultTree;
	bool found = t.find(1, resultTree);
	EXPECT_EQ(found, false); // Should not find 1
	EXPECT_TRUE(resultTree.isEmpty()); // resultTree should be empty if not found
}

