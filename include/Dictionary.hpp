//
// File:   Dictionary.hpp
// Author: Your Glorious Instructor
// Purpose:
// A simplified implementation of the Dictionary ADT
//
#pragma once
#include <iostream>
#include <stdexcept>
#include <functional>
#include <optional>
#include "Tree.hpp"
#include "Pair.hpp"

template <typename KeyType, typename ValueType>
class Dictionary {
private:
	using KeyValueType = Pair<KeyType, ValueType>;
	Tree<KeyValueType> dictTree;

public:
	// Always be explicit about taking the defaults for special member functions.
	Dictionary() = default;
	Dictionary(const Dictionary<KeyType, ValueType>& other) = default;
	Dictionary(Dictionary<KeyType, ValueType>&& other) = default;
	Dictionary<KeyType, ValueType>& operator=(const Dictionary<KeyType, ValueType>& other) = default;
	Dictionary<KeyType, ValueType>& operator=(Dictionary<KeyType, ValueType>&& other) = default;
	~Dictionary() = default;

	bool empty() const {
		return dictTree.isEmpty();
	}

	size_t size() const {
		return dictTree.size();
	}

	void insert(KeyType key, ValueType value) {
		Pair<KeyType, ValueType> newEntry = MakePair(key, value);
		dictTree = dictTree.insert(newEntry);
	}
	
	ValueType& at(const KeyType& item) {
		auto compareFirst = [](const KeyValueType& lhs, const KeyValueType& rhs) {
			return lhs.first < rhs.first;
			};
		Tree<KeyValueType> resultTree;
		bool wasFound = dictTree.find(KeyValueType(item, ValueType()), resultTree, compareFirst);
		if (!wasFound) {
			throw std::out_of_range("Key not found in dictionary");
		}
		return resultTree.root().second;
	}
		
	ValueType& operator[](const KeyType& item) {
		return at(item);
	}

};
