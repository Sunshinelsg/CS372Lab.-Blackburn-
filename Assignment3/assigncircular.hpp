// Build a cicuular list using the classic double linked version of a linked list.
//
#pragma once
#include <iostream>
#include <functional>

template <typename T>
class CircularList {
private:
    class Node {
    public:
        T  data;
        Node* prev;
        Node* next;

        Node(const T& d) : data(d), prev(nullptr), next(nullptr) {}
    };
    Node* head = nullptr;
    Node* tail = nullptr;

    void deleteListContents() {
        if (empty()) return;

        Node* current = head;
        do {
            Node* next = current->next;
            delete current;
            current = next;
        } while (current != head);
        head = tail = nullptr;
    }
public:
    CircularList() = default;

    CircularList(const CircularList& rhs) { // copy constructor
        if (!rhs.empty()) {
            Node* current = rhs.head;
            do {
                push_back(current->data);
                current = current->next;
            } while (current != rhs.head);
        }
    }



CircularList& operator=(const CircularList& rhs) { // copy assignment
    if (this != &rhs) {
        deleteListContents();
        if (!rhs.empty()) {
            Node* current = rhs.head;
            do {
                push_back(current->data);
                current = current->next;
            } while (current != rhs.head);
        }
    }
    return *this;
};


CircularList(CircularList&& rhs) noexcept { //move construtor

    head = rhs.head;
    tail = rhs.tail;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}
CircularList& operator=(CircularList&& rhs) noexcept {
    if (this != &rhs) {
        deleteListContents();
        head = rhs.head;
        tail = rhs.tail;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
    return *this;
}
~CircularList() {
    deleteListContents();
}

bool empty() const {
    return head == nullptr;
}

void push_front(const T& data) {
    Node* newNode = new Node(data);
    if (empty()) {
        head = tail = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    }
    else {
        newNode->next = head;
        newNode->prev = tail;
        head->prev = newNode;
        tail->next = newNode;
        head = newNode;
    }
}

void push_back(const T& data) {
    Node* newNode = new Node(data);
    if (empty()) {
        head = tail = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    }
    else {
        newNode->prev = tail;
        newNode->next = head;
        tail->next = newNode;
        head->prev = newNode;
        tail = newNode;
    }
}

void pop_back() {

    if (empty()) return;
    if (head == tail) {
        delete tail;
        head = tail = nullptr;
    }
    else {
        Node* lastNode = tail;
        tail = tail->prev;
        tail->next = head;
        head->prev = tail;
        delete lastNode;
    }
}

void pop_front() {
    if (empty()) return;

    if (head == tail) {
        delete head;
        head = tail = nullptr;
    }
    else {
        Node* lastNode = head;
        head = head->next;
        head->prev = tail;
        tail->next = head;
        delete lastNode;
    }
}
T& front() {
    if (!empty()) {
        return head->data;
    }
    else {
        // This is drastic, and should be handled using an exception handler
        std::cout << "Exception: list is empty." << std::endl;
        exit(1);
    }
}

T& back() {
    if (!empty()) {
        return tail->data;
    }
    else {
        // This is drastic, and should be handled using an exception handler
        std::cout << "Exception: list is empty." << std::endl;
        exit(1);
    }
}
void traverse(std::function<void(const T&)> doIt) const {
    if (empty()) return;
    Node* current = head;
    do {
        doIt(current->data);
        current = current->next;
    } while (current != head);
}
};
