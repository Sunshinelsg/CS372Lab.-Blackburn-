#include <iostream>
#include "assign4queue.hpp"

void printItem(int& item) {
    std::cout << item << " ";
}

int main() {
    Queue<int> aQueueOfIntegers;
    if (aQueueOfIntegers.empty()) {
        std::cout << "Yep, the new queue is empty. " << std::endl;
    }
    for (int i = 3; i >= 0; i--) {
        aQueueOfIntegers.push(i);
    }
    aQueueOfIntegers.traverse(printItem);
    std::cout << std::endl;

    for (int i = 0; i < 3; i++) {
        int datum = aQueueOfIntegers.back();
        std::cout << datum << " ";
        aQueueOfIntegers.pop();
    }
    std::cout << std::endl;
    if (!aQueueOfIntegers.empty()) {
        aQueueOfIntegers.traverse(printItem);
        std::cout << std::endl;
    }
    aQueueOfIntegers.push(42);
    aQueueOfIntegers.traverse(printItem);
    std::cout << std::endl;
    return 0;
}
