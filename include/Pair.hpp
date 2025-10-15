//
// File:    Pair.hpp
// Author:  Your Glorious Instructor
// Purpose:
// A simplifed implementation of the Ordered Pair ADT
//
#pragma once
template <typename KeyType, typename ValueType>
class Pair {
public:
  KeyType first;
  ValueType second;

  Pair() = delete;
  Pair(KeyType x, ValueType y): first(x), second(y) {}

  bool operator<(const Pair<KeyType, ValueType> rhs) const {
    bool meetsCriteria = false;
    if (this->first < rhs.first) {
      meetsCriteria = true;
    }
    return meetsCriteria;
  }


  bool operator>(const Pair<KeyType, ValueType> rhs) const {
    bool meetsCriteria = false;
    if (this->first > rhs.first) {
      meetsCriteria = true;
    }
    return meetsCriteria;
  }


  bool operator==(const Pair<KeyType, ValueType> rhs) const {
    bool meetsCriteria = false;
    if (this->first == rhs.first) {
      meetsCriteria = true;
    }
    return meetsCriteria;
  }
};

template <typename KeyType, typename ValueType>
Pair<KeyType, ValueType> & MakePair(KeyType first, ValueType second) {
  Pair<KeyType, ValueType> * newPair = new Pair<KeyType, ValueType>(first, second);
  return *newPair;
}
