#include <iostream>
#include "assign4stack.hpp"

void printItem(int& item) {
    std::cout << item << " ";
}

int main() {
    Stack<int> aStackOfIntegers;
    if (aStackOfIntegers.empty()) {
        std::cout << "Yep, the new list is empty. " << std::endl;
    }
    for (int i = 3; i >= 0; i--) {
        aStackOfIntegers.push(i);
    }
    aStackOfIntegers.traverse(printItem);
    std::cout << std::endl;

    std::cout << std::endl;
    for (int i = 0; i < 3; i++) {
        int datum = aStackOfIntegers.front();
        std::cout << datum << " ";
        aStackOfIntegers.pop();
    }
    std::cout << std::endl;
    if (!aStackOfIntegers.empty()) {
        aStackOfIntegers.traverse(printItem);
        std::cout << std::endl;
    }
    aStackOfIntegers.push(42);
    aStackOfIntegers.traverse(printItem);
    std::cout << std::endl;
    return 0;
}
