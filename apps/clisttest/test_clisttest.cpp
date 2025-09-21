// test_clisttest.cpp

#include <gtest/gtest.h>
#include "CircularList.hpp"
#include <vector>

class CircularListTest : public ::testing::Test {
protected:
  CircularList<int> list;

  static void collectItem(int &item, std::vector<int> *vec) {
    vec->push_back(item);
  }
};

TEST_F(CircularListTest, NewListIsEmpty) {
  EXPECT_TRUE(list.empty());
}

TEST_F(CircularListTest, PushFrontAddsElementsInReverseOrder) {
  for (int i = 10; i >= 0; --i) {
    list.push_front(i);
  }
  std::vector<int> result;
  list.traverse([&](int &item){ result.push_back(item); });
  std::vector<int> expected = {0,1,2,3,4,5,6,7,8,9,10};
  EXPECT_EQ(result, expected);
}

TEST_F(CircularListTest, PopBackRemovesElementsFromBack) {
  for (int i = 10; i >= 0; --i) {
    list.push_front(i);
  }
  std::vector<int> popped;
  for (int i = 0; i < 10; ++i) {
    popped.push_back(list.back());
    list.pop_back();
  }
  std::vector<int> expected = {10,9,8,7,6,5,4,3,2,1};
  EXPECT_EQ(popped, expected);
  EXPECT_FALSE(list.empty());
}

TEST_F(CircularListTest, TraverseAfterPopping) {
  for (int i = 10; i >= 0; --i) {
    list.push_front(i);
  }
  for (int i = 0; i < 10; ++i) {
    list.pop_back();
  }
  std::vector<int> result;
  list.traverse([&](int &item){ result.push_back(item); });
  std::vector<int> expected = {0};
  EXPECT_EQ(result, expected);
}

TEST_F(CircularListTest, PushBackAddsElementToEnd) {
  list.push_back(42);
  std::vector<int> result;
  list.traverse([&](int &item){ result.push_back(item); });
  std::vector<int> expected = {42};
  EXPECT_EQ(result, expected);
  EXPECT_FALSE(list.empty());
}

TEST_F(CircularListTest, EmptyAfterAllPops) {
  list.push_back(1);
  list.pop_back();
  EXPECT_TRUE(list.empty());
}