#pragma once
#include <functional>
#include "List.hpp"
template <typename T>
class SelfList : public List<T> {
private:
  typename List<T>::iterator findInList(const T &data)  {
    typename List<T>::iterator placeInList = this->begin();
    typename List<T>::iterator endOfList = this->end();
    bool found = false;
    while (!found && placeInList != endOfList) {
      if (*placeInList == data) {
        found = true;
      } else {
        ++placeInList;
      }
    }
    return placeInList;
  }
public:
  typename SelfList<T>::iterator findIt(const T &data) {
    typename List<T>::iterator whereFound = findInList(data);
    if (whereFound != this->end()) {
        // An important reminder here about the difference between 
		// T and T&.  T is a copy of the data, T& is a reference to the data.
		// Setting the type of temp to T& would allow us to modify the data in place.
        // This caused a bug where the thing temp was referring to got deleted as part
		// of the processing of the erase() method.
      T temp = *whereFound;
      auto revisedIterator = this->erase(whereFound);
      this->push_front(temp);
      whereFound = this->begin();
    }
    return whereFound;
  }
};
