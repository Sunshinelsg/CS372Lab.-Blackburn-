#pragma once
#include "assignlist4.hpp"

template <typename T>
class Stack {
private:
    List<T> stackList;
public:
    Stack() {}
    Stack(const Stack& rhs) : stackList(rhs.stackList) {}
    ~Stack() {}
    bool  empty() { return stackList.empty(); }
    void push(T data) { stackList.push_front(data); }
    void pop() { stackList.pop_front(); }
    T front() { return stackList.front(); }
    T back() { return stackList.back(); }
    void traverse(void (*doIt)(T& data)) {
        stackList.traverse(doIt);
    }

};
