//
// File:   skiplist.cpp
// Author: Your Glorious Instructor
// Purpose:
// Demonstrate the use of Skip lists

#include <iostream>
#include <cassert>
#include "skiplist.hpp"

// Test Cases
void runTests() {
    SkipList<int> sl;

    // Insert and search tests
    sl.insert(3);
    sl.insert(6);
    sl.insert(7);
    sl.insert(9);
    sl.insert(12);
    sl.insert(19);
    sl.insert(17);
    sl.insert(26);
    sl.insert(21);
    sl.insert(25);

    assert(sl.search(3) == true);
    assert(sl.search(6) == true);
    assert(sl.search(7) == true);
    assert(sl.search(9) == true);
    assert(sl.search(12) == true);
    assert(sl.search(19) == true);
    assert(sl.search(17) == true);
    assert(sl.search(26) == true);
    assert(sl.search(21) == true);
    assert(sl.search(25) == true);
    assert(sl.search(15) == false); // 15 is not in the list

    // Deletion test
    sl.erase(6);
    assert(sl.search(6) == false);

    sl.erase(19);
    assert(sl.search(19) == false);

    sl.erase(3);
    assert(sl.search(3) == false);

    std::cout << "All tests passed successfully!\n";
}

int main() {
    runTests();
    return 0;
}
