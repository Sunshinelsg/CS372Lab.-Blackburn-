

#pragma once
#include "List.hpp"
template <typename T>
class Queue {
private:
   List<T> queueList;
public:
   Queue() {}
   Queue(Queue &rhs) {}
   ~Queue() { }
   bool  empty() {return queueList.empty();}
   void push(T data) {queueList.push_front(data);}
   T front() { return queueList.front(); }
   T back() { return queueList.back(); }
   void pop() { queueList.pop_back();}
   void traverse(void (*doIt)(T &data)){
      queueList.traverse(doIt);
   };

};
