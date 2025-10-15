#include <vector>
#include <string>
#include <exception>
#include <gtest/gtest.h>
#include "Pair.hpp"
#include "Dictionary.hpp"

// TEST: Confirm default constructor behaves correctly

TEST(DictUnitTests, DefaultConstructor) {
	Dictionary<int,std::string> * aDict  = new Dictionary<int,std::string>();
	EXPECT_FALSE(aDict == nullptr);
  EXPECT_TRUE(aDict->empty());
	delete aDict;
}


TEST(DictUnitests, InsertNewThing) {
  Dictionary<int, std::string> *aDict = new Dictionary<int,std::string>();
	EXPECT_FALSE(aDict == nullptr);
	EXPECT_EQ(aDict->size(), 0);
  aDict->insert(42, "DummyValue");
	EXPECT_EQ(aDict->size(), 1);
  aDict->insert(59, "DummyValue");
	EXPECT_EQ(aDict->size(), 2);
	delete aDict;

}
// TEST: at() retrieves correct value for existing key
TEST(DictUnitTests, AtReturnsCorrectValue) {
    Dictionary<int, std::string> dict;
    dict.insert(1, "one");
    dict.insert(2, "two");
    std::string result1 = dict.at(1);
    EXPECT_EQ(result1, "one");
    std::string result2 = dict.at(2);
    EXPECT_EQ(result2, "two");
}

// TEST: at() throws for missing key
TEST(DictUnitTests, AtThrowsForMissingKey) {
    Dictionary<int, std::string> dict;
    dict.insert(1, "one");
    EXPECT_THROW(dict.at(99), std::out_of_range);
}

// TEST: operator[] returns correct value for existing key
TEST(DictUnitTests, OperatorBracketReturnsCorrectValue) {
    Dictionary<int, std::string> dict;
    dict.insert(5, "five");
    EXPECT_EQ(dict[5], "five");
}

// TEST: size() reflects number of unique keys
TEST(DictUnitTests, SizeReflectsUniqueKeys) {
    Dictionary<int, std::string> dict;
    EXPECT_EQ(dict.size(), 0);
    dict.insert(1, "one");
    EXPECT_EQ(dict.size(), 1);
    dict.insert(2, "two");
    EXPECT_EQ(dict.size(), 2);
}

// TEST: empty() returns true only when dictionary is empty
TEST(DictUnitTests, EmptyReturnsTrueOnlyWhenEmpty) {
    Dictionary<int, std::string> dict;
    EXPECT_TRUE(dict.empty());
    dict.insert(1, "one");
    EXPECT_FALSE(dict.empty());
}

// TEST: Insert duplicate key (behavior depends on Tree implementation, but should not increase size)
TEST(DictUnitTests, InsertDuplicateKeyDoesNotIncreaseSize) {
    Dictionary<int, std::string> dict;
    dict.insert(1, "one");
    size_t before = dict.size();
    dict.insert(1, "uno"); // Insert with same key, different value
    EXPECT_EQ(dict.size(), before);
    // Depending on Tree, value may or may not update; check if value is updated
    EXPECT_EQ(dict.at(1), "uno");
}
