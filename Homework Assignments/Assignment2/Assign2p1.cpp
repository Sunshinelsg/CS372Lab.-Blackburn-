#include <iostream>
#include <chrono>
#include <string>
#include <algorithm>

using namespace std;
using namespace std::chrono;


class Vector {
public:
    virtual void push_back(int val) = 0;
    virtual ~Vector() {}
};

class MainVector : public Vector {
protected:
    int* data;
    size_t capacity;
    size_t size;

    virtual void increase_capacity() {
        size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
        int* new_data = new int[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
public:
    MainVector() : data(nullptr), capacity(0), size(0) {}
    virtual ~MainVector() { delete[]data; }

    virtual void push_back(int val) override {
        if (size == capacity) {
            increase_capacity();
        }
        data[size++] = val;
    }
};

class CopyVector : public MainVector {
protected:
    void increase_capacity() override{
        size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
        int* new_data = new int[new_capacity];
        std::copy(data, data + size, new_data);
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
};
class FastGrowVector : public MainVector {
protected:
    void increase_capacity() override {
        size_t new_capacity = (capacity == 0) ? 128 : capacity * 4;
        int* new_data = new int[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
};

template <typename T>
void ourSwap(T& left, T& right) {
    T temp;
    temp = left;
    left = right;
    right = temp;
}

template <typename T>
int Partition(T a[], int start, int end) {
    int pivotValue, pivotIndex, mid;
    mid = (start + end) / 2;
    ourSwap(a[start], a[mid]);
    pivotIndex = start;
    pivotValue = a[start];
    for (int scan = start + 1; scan <= end; scan++) {
        if (a[scan] < pivotValue) {
            pivotIndex++;
            ourSwap(a[pivotIndex], a[scan]);
        }
    }
    ourSwap(a[start], a[pivotIndex]);
    return pivotIndex;
}

void time_vector(const std::string& name) {
    Vector* vec = nullptr;

    for (int exp = 1; exp <= 16; ++exp) {
        size_t num_elements = 1 << exp;

        delete vec;
        if (name == "MainVector") vec = new MainVector();
        else if (name == "SameVector") vec = new CopyVector();
        else if (name == "FastGrowVector") vec = new FastGrowVector();

            auto start = high_resolution_clock::now();
            for (size_t i = 0; i < num_elements; ++i) {
                vec->push_back(static_cast<int>(i));
            }
        auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start).count();
            cout << name << " size: " << num_elements << " time: " << duration << "ms\n";
    }
    delete vec;
}

    template<typename T>
    void printArray(T theArray[], int size) {
        for (int index = 0; index < size; ++index) {
            cout << theArray[index] << " ";
        }
        cout << endl;
    }

   int main() {
        cout << " *Compare the time* ";
        time_vector("MainVector");
        cout << "\n";
        time_vector("SameVector");
        cout << "\n";
        time_vector("FastGrowVector");
        return 0;
    }
