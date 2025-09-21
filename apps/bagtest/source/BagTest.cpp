#include <vector> 
#include <gtest/gtest.h>
#include "bag.hpp"
// TEST: Confirm default constructor behaves correctly
TEST(BagUnitTests, DefaultConstructor) {
	Bag<int> aBag;
	EXPECT_EQ(aBag.size(), 0);
	EXPECT_EQ(aBag.count(42), 0);
}

TEST(BagUnitTests, InsertNewThing) {
	Bag<int> aBag;
	EXPECT_EQ(aBag.size(), 0);
	EXPECT_EQ(aBag.count(10), 0);
	aBag.insert(42);
	EXPECT_EQ(aBag.size(), 1);
	EXPECT_EQ(aBag.count(42), 1);
	aBag.insert(59);
	EXPECT_EQ(aBag.size(), 2);
	EXPECT_EQ(aBag.count(59), 1);
}

TEST(BagUnitTests, RemoveItemFromBag) {
	Bag<int> aBag;
	EXPECT_EQ(aBag.size(), 0);
	EXPECT_EQ(aBag.count(10), 0);
	aBag.insert(42);
	EXPECT_EQ(aBag.size(), 1);
	EXPECT_EQ(aBag.count(42), 1);
	aBag.insert(59);
	EXPECT_EQ(aBag.size(), 2);
	EXPECT_EQ(aBag.count(59), 1);
	int thing = aBag.pop();
	EXPECT_EQ(thing, 59);
	EXPECT_EQ(aBag.size(), 1);
	EXPECT_EQ(aBag.count(59), 0);
	thing = aBag.pop();
	EXPECT_EQ(thing, 42);
	EXPECT_EQ(aBag.size(), 0);
	EXPECT_EQ(aBag.count(42), 0);
	thing = aBag.pop();
	EXPECT_EQ(aBag.size(), 0);
}

TEST(BagUnitTests, InsertDuplicateItems) {
    Bag<int> aBag;
    aBag.insert(42);
    aBag.insert(42);
    EXPECT_EQ(aBag.size(), 2);
    EXPECT_EQ(aBag.count(42), 2);
}

TEST(BagUnitTests, PopFromEmptyBag) {
    Bag<int> aBag;
    int thing = aBag.pop();
    EXPECT_EQ(aBag.size(), 0);
    // Depending on implementation, thing may be default value
}

TEST(BagUnitTests, CountAfterRemove) {
    Bag<int> aBag;
    aBag.insert(1);
    aBag.insert(1);
    aBag.pop();
    EXPECT_EQ(aBag.count(1), 1);
}

TEST(BagUnitTests, MultipleTypes) {
    Bag<std::string> strBag;
    strBag.insert("hello");
    strBag.insert("world");
    EXPECT_EQ(strBag.size(), 2);
    EXPECT_EQ(strBag.count("hello"), 1);
    EXPECT_EQ(strBag.count("world"), 1);
}

TEST(BagUnitTests, ClearBag) {
    Bag<int> aBag;
    aBag.insert(5);
    aBag.insert(10);
    while (aBag.size() > 0) {
        aBag.pop();
    }
    EXPECT_EQ(aBag.size(), 0);
}