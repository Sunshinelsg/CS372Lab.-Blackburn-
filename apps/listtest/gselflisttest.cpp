//
// File:   selflisttest.cpp
// Author: Your Glorious Instructor <
// Purpose:
// Show how to use Google Test to test our SelfList class.
//
#include <gtest/gtest.h>
#include "SelfList.hpp"

void collectItem(int& item, std::vector<int>& out) {
    out.push_back(item);
}

TEST(SelfListTest, EmptyOnCreation) {
    SelfList<int> list;
    EXPECT_TRUE(list.empty());
}

TEST(SelfListTest, PushFrontAndTraverse) {
    SelfList<int> list;
    for (int i = 3; i >= 0; i--) {
        list.push_front(i);
    }
    std::vector<int> items;
    list.traverse([&](int& item){ items.push_back(item); });
    std::vector<int> expected = {0, 1, 2, 3};
    EXPECT_EQ(items, expected);
}

TEST(SelfListTest, MutableIterator) {
    SelfList<int> list;
    for (int i = 3; i >= 0; i--) {
        list.push_front(i);
    }
    std::vector<int> items;
    for (auto it = list.begin(); it != list.end(); ++it) {
        items.push_back(*it + 4);
    }
    std::vector<int> expected = {4, 5, 6, 7};
    EXPECT_EQ(items, expected);
}

TEST(SelfListTest, ConstIterator) {
    SelfList<int> list;
    for (int i = 3; i >= 0; i--) {
        list.push_front(i);
    }
    std::vector<int> items;
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        items.push_back(*it);
    }
    std::vector<int> expected = {0, 1, 2, 3};
    EXPECT_EQ(items, expected);
}

TEST(SelfListTest, PopBack) {
    SelfList<int> list;
    for (int i = 3; i >= 0; i--) {
        list.push_front(i);
    }
    std::vector<int> popped;
    for (int i = 0; i < 3; i++) {
        popped.push_back(list.back());
        list.pop_back();
    }
    std::vector<int> expected = {3, 2, 1};
    EXPECT_EQ(popped, expected);
    EXPECT_FALSE(list.empty());
    std::vector<int> remaining;
    list.traverse([&](int& item){ remaining.push_back(item); });
    EXPECT_EQ(remaining, std::vector<int>{0});
}

TEST(SelfListTest, PushBackAndTraverse) {
    SelfList<int> list;
    list.push_back(42);
    std::vector<int> items;
    list.traverse([&](int& item){ items.push_back(item); });
    EXPECT_EQ(items, std::vector<int>{42});
}

TEST(SelfListTest, PushBackMultiple) {
    SelfList<int> list;
    for (int i = 5; i >= 0; --i) {
        list.push_back(i);
    }
    std::vector<int> items;
    list.traverse([&](int& item){ items.push_back(item); });
    std::vector<int> expected = {5, 4, 3, 2, 1, 0};
    EXPECT_EQ(items, expected);
}

TEST(SelfListTest, FindItMoveToFront) {
    SelfList<int> list;
    for (int i = 5; i >= 0; --i) {
        list.push_back(i);
    }
    list.push_back(42); // Now: 5 4 3 2 1 0 42
    auto it = list.findIt(3);
    EXPECT_EQ(*it, 3);
    std::vector<int> items;
    list.traverse([&](int& item){ items.push_back(item); });
    EXPECT_EQ(items.front(), 3);
}

TEST(SelfListTest, FindItNotFound) {
    SelfList<int> list;
    for (int i = 5; i >= 0; --i) {
        list.push_back(i);
    }
    auto it = list.findIt(45);
    EXPECT_EQ(it, list.end());
}

TEST(SelfListTest, FindItMultiple) {
    SelfList<int> list;
    for (int i = 5; i >= 0; --i) {
        list.push_back(i);
    }
    list.findIt(3);
    list.findIt(3);
    std::vector<int> items;
    list.traverse([&](int& item){ items.push_back(item); });
    EXPECT_EQ(items.front(), 3);
    list.findIt(4);
    items.clear();
    list.traverse([&](int& item){ items.push_back(item); });
    EXPECT_EQ(items.front(), 4);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}