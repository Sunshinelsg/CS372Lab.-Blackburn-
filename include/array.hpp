





#pragma once
#include <iostream>
#include <stdexcept> 

template <typename T, size_t N>
class Array {
public:
    Array() {
        for (size_t i = 0; i < N; ++i) {
            data[i] = T(); 
        }
    }

    Array(const Array<T, N>& other) {
        for (size_t i = 0; i < N; ++i) {
            data[i] = other.data[i];
        }
    }

    T& operator[](size_t index) {
        if (index >= N) {
            throw std::out_of_range("Array index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= N) {
            throw std::out_of_range("Array index out of range");
        }
        return data[index];
    }

    T& at(size_t index) {
        if (index >= N) {
            throw std::out_of_range("Array::at - index out of range");
        }
        return data[index];
    }

    const T& at(size_t index) const {
        if (index >= N) {
            throw std::out_of_range("Array::at - index out of range");
        }
        return data[index];
    }
    constexpr size_t size() const {
        return N;
    }
    void traverse() const {
        for (size_t i = 0; i < N; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    T data[N];
};