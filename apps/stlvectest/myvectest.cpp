//
// File:   myvectest.cpp
// Author: Your Glorious Instructor
// Purpose:
// Determine behavior and performance of capacity increate in STL vector.
//
#include "vector.hpp"
#include <chrono>
#include <iostream>

class VecTester {
private:
    Vector<int> testVector;
    
    void fillVector(size_t cap) {
        for (int i = 0 ; i < cap; ++i) { testVector[i] = i; }
    }
public:
    void tester() {
        size_t oldCap = testVector.capacity();
        std::cout << "Starting capacity: " << oldCap << std::endl;
        for (int i = 0; i <= 10000; i++) {
            auto start = std::chrono::steady_clock::now();
            testVector.push_back(i);
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elaspedSeconds = end - start;
            int newCap = testVector.capacity();
            if (oldCap != newCap) {
                std::cout << " Capacity after add "
                << oldCap
                << " Time: "
                << elaspedSeconds.count() << " seconds"
                << std::endl;
                oldCap = newCap;
            }
                
        }
    }
};

int main() {
    VecTester testingObject;
    std::cout << "Starting test: " << std::endl;
    testingObject.tester();
    return 0;
}
