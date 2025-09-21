
// Implement the Bag ADT.
//
#pragma once
#include <iostream>
#include <vector>

template <typename Thing>
class Bag {
public:
  void insert(const Thing& aThing) {
    bagContents.push_back(aThing);
    bagSize++;
  }
  Thing pop() {
      if (bagContents.empty()) {
          std::cerr << "Can't pop out of an empty bag" << std::endl;
          return aThing;
      }
      Thing value = bagContents.back();
      bagcontents.pop_back();
      return value;
  }

  int size() const {
    return bagSize();
  }
  int count(const Thing& aThing) const{
    int bagCount = 0;
    for (int i = 0 ; i < bagSize; i++) {
      if (bagContents[i] == aThing) {
        bagCount++;
      }
    }
    return bagCount;
  }
private:
    List<Thing> bagContents;
    int bagSize() const {
        int count = 0;
        for (auto it = bagContents.cbegin(); it != bagContents.cend(); ++it) {
            ++count;
        }
        return count;
    }
};
