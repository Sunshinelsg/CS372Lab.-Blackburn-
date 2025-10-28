//
// File:   heapstl.cpp
// Author: Adam.Lewis@athens.edu
// Purpose:
// Demonstrate working with heaps using the C++ standard library algorithms
//
#include<iostream>
#include<vector>

std::vector<int> numbers = {0,1,2,3,4,5,6,7,8,9};
void convertToHeap() {
  // Use the make_heap algorithm.  Note that the parameters are
  // C++ STL iterator objects indicating the start and end of the
  // collection we want to heapify.
  std::make_heap(begin(numbers), end(numbers));
  for (int number: numbers) {
    std::cout << number << ' ';
  }
  std::cout << std::endl;
}
int main() {
  convertToHeap();
  // And let's test the result using is_heap() and is_heap_util()
  if (std::is_heap(std::begin(numbers), std::end(numbers))) {
    std::cout << "Yep it's a heap" << std::endl;
  }
  auto heapEnd = std::is_heap_until(std::begin(numbers), std::end(numbers));
  if (heapEnd != std::begin(numbers)) {
    std::cout << "Yep it's a heap" << std::endl;
    if (heapEnd == end(numbers)) {
      std::cout << "It's all a heap!";
    }
    else {
      std::cout << "Here's the part that is a heap:" << std::endl;
      std::copy(std::begin(numbers), heapEnd, std::ostream_iterator<int>(std::cout, " "));
      std::cout << std::endl;
    }
  }
  return 0;
}
