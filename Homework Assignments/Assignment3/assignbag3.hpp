// Implement the Bag ADT.
//
#pragma once
#include <iostream>
#include "assignlist3.hpp"

template <typename Thing>
class Bag {
public:
    void insert(Thing aThing) {
        bagContents.push_back(aThing);
        bagSize++;
    }
    Thing& pop() {
        Thing aThing;
        if (bagContents.size() > 0) {
            aThing = bagContents[bagSize];
            bagSize--;
        }
        else {
            std::cerr << "Can't pop out of an empty bag" << std::endl;
        }
        return aThing;
    }
    int size() {
        return bagSize;
    }
    int count(Thing aThing) {
        int bagCount = 0;
        for (int i = 0; i < bagSize; i++) {
            if (bagContents[i] == aThing) {
                bagCount++;
            }
        }
        return bagCount;
    }
private:
    std::vector<Thing> bagContents;
    int bagSize = 0;
};
