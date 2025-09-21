

#pragma once
#include "List.hpp"
template <typename T>
class Stack {
private:
   List<T> stackList; 
public:
   Stack() {}
   Stack(Stack &rhs) {}
   ~Stack() { }
   bool  empty() {return stackList.empty();}
   void push(T data) {stackList.push_front(data);}
   void pop() { return stackList.pop_front(); }
   T front() { return stackList.front(); }
   T back() { return stackList.back(); }
   void traverse(void (*doIt)(T &data)){
      stackList.traverse(doIt);
   };

};
