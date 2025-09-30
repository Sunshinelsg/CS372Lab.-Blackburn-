#pragma once
#include <functional>
#include "List.hpp"

template <typename T>
class SelfList : public List<T> {
private:
    using Node = typename List<T>::Node; 
    int numDeleted = 0;
    int numActive = 0;

    typename List<T>::iterator findInList(const T& data) {
        auto itr = this->List<T>::begin();
        auto endItr = this->List<T>::end();
        while (itr != endItr) {
            if (!itr== data) {
                return itr;
            }
            ++itr;
        }
        return endItr;;
    }

    void getWrong() {
        if (numDeleted >= numActive) {
            auto itr = this->List<T>::begin();
            while (itr != this->List<T>::end()) {
                SelfList<T>::iterator selfItr(itr.current());
               if (!itr.IsDeleted()) {
                    itr = this->List<T>::erase(itr);
                    --numDeleted;
                }
                else {
                    ++itr;
                }
            }
        }
    }


public:
    SelfList() :List<T>(), numDeleted(0), numActive(0) {}

    void push_front(const T& data) {
        this->List<T>::push_front(data);
        ++numActive;
    }

    void push_back(const T& data) {
        this->List<T>::push_back(data);
        ++numActive;
    }

    typename List<T>::iterator erase(typename List<T>::iterator itr) {
        if (itr == this->List<T>::end())
            return itr;
        SelfList<T>::iterator selfItr(itr.current());
        itr.markDeleted = true;
        ++numDeleted;
        --numActive;
        getWrong();
        return ++itr;
    }
    void traverse(std::function<void(T&)>doIt) {
        auto curr = this->head->next;
        while (curr != this->tail) {
            if (!curr->deleted) {
                doIt(curr->data);
            }
            curr = curr->next;
        }
    }
    class const_iterator : public List<T>::const_iterator {
    public:
        using List<T>::const_iterator::current;
        bool isDeleted() const {
            return current->deleted;
        }

        const_iterator(Node* p) :List<T>::const_iterator(p) {
            while (current && (current->isHiddenNode || current->deleted)) {
                current = current->next;
            }
        }
        const_iterator& operator++() {
            do {
                current = current->next;
            } while (current && (current->isHiddenNode || current->deleted));
            return *this;
        }
        const_iterator& operator++(int) {
            const_iterator old = *this;
            ++(*this);
            return old;
        }
    };
    class iterator :public const_iterator {
    public:
        using List<T>::const_iterator::current;

        iterator(Node* p) : const_iterator(p) {}
        iterator(typename List<T>::iterator const& baseIt) :const_iterator(baseIt.current) {}
        T& operator*() {
            return this->retrieve();
        }
        void markDeleted() {
            current->deleted = true;
        }
        bool isDeleted()const {
            return current->deleted;
        }
        Node* getNode() const {
            return current;
        }
    };
        iterator& operator++() {
            do {
                this->current = this->current->next;
            } while (this->current && (this->current->isHiddenNode || this->current->deleted));
            return *this;
        }
        iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }
        Node* getNode() const {
            return this->current;
        }
        friend class SelfList<T>;
    };
    iterator begin() const {
        Node* p = this->head->next;
        while (p && (p->isHiddenNode
            || p->deleted)) {
            p = p->next;
        }
        return iterator(p);
    }
    iterator end() const {
        return iterator(this->tail);
    }
    const_iterator dbegin() const {
        Node* p = this->head->next;
        while (p && (p->isHiddenNode || p->deleted)) {
            p = p->next;
        }
        return const_iterator(p);
    }
    const_iterator dend() const {
        return const_iterator(this->tail);
    }

    void pop_back() {
        auto itr = this->List<T>::end();
        --itr;
        SelfList<T>::iterator selfItr(itr.current());
       while (itr != this->List<T>::begin() && itr.current->deleted) {
            --itr;
        }
        if (itr != this->List<T>::end()) {
            erase(itr);
        }
    }
    void pop_front() {
        auto itr = this->List<T>::begin();
        SelfList<T>::iterator selfItr(itr.current()); 
        while (itr != this->List<T>::end() && itr.current->deleted) {
            ++itr;
        }
        if (itr != this->List<T>::end()) {
            erase(itr);
        }
    }
    typename List<T>::iterator findIt(const T& data){
       ???????????????????????????????/ auto baseIt = findIt(data);
        if (baseIt != this->List<T>::end()) {
            T temp = *baseIt;
            erase(baseIt);
            push_front(temp);
            return this->begin();
        }
        return this->end();
    }
    bool isEmpty()const {
        return numActive == 0;
    }
};
