//
// File:   vector.h
// Author: Your Glorious Instructor
// Purpose:
// A simplifed version of the C++ STL vector class

#pragma once
#include <iostream>

template <typename T>
class Vector {
public:
	Vector() : arr(new T[1]), vCapacity(1), length(0) {}

	Vector(const Vector& obj) {
		vCapacity = obj.vCapacity;
		length = obj.length;
		arr = new T[vCapacity];
		for (int i = 0; i < length; i++) {
			arr[i] = obj.arr[i];
		}
	}
  ~Vector() {
    delete [] arr;
    arr = nullptr;
  }

  void put(int index, T data) {
    if (index == length) {
      push_back(data);
    }
	else if (index >= 0 && index < length) {
		arr[index] = data;
	}
	else{
		std::cerr << "Vector: out of bounds" << std::endl;
		exit(1);
    }
  }

  void push_back(T data) {
    // if number of elements is equal to capacity
		// than we need to reallocate and deep copy
		if (length == vCapacity) {
			expand(2 * vCapacity);
		}
		arr[length] = data;
		length++;
  }

  T& at(int index) {
	  if (index < 0 || index >= length) {
		  std::cerr << "This vector is not within access bounds." << std::endl;
		  exit(1);
	  }
	  return arr[index];
  }
  const T& at(int index) const{
    if (index < 0 || index >= length) {
			std::cerr << "Vector: index out of bounds on access" << std::endl;
			exit(1);
		}
	return arr[index];
  }

  int size() const{
    return length;
  }

  int capacity() const{
    return vCapacity;
  }

  void traverse () const {
		for (int i = 0; i < length; i++) {
			std::cout << arr[i] << std::endl;
		}
		std::cout << std::endl;
  }

	bool operator==(const Vector& other) const {
		if (other.size() != length) {
			return false;
		}
		for (int i = 0; i < length; i++) {
			if (arr[i] != other.arr[i]) {
				return false;
			}
		}
		return true;
	}
	

  T& operator[](int i) {
    if ((i < 0) || (i >= length)) {
      std::cerr << std::endl << "Vector index out of bounds" << std::endl;
	  exit(1);
    }
    return arr[i];
  }

	Vector& operator=(const Vector& source) {
		// Do a self check.
		if (this == &source)
		{
			return *this;
		}
		// Reset self
		delete[] arr;

		vCapacity = source.vCapacity;
		length = 0;
		arr = new T[vCapacity];
		for (int i = 0; i < source.size(); i++) {
			push_back(source.at(i));
		}
		return *this;
	}
private:
  T *arr;
  int vCapacity = 1;
  int length = 0;

  void expand(int newCapacity) {
    if (newCapacity > vCapacity) {
      T *temp = new T[newCapacity];
      for (int i = 0; i < length; i++) {
        temp[i] = arr[i];
      }
      delete[] arr;
	  arr = temp;
      vCapacity = newCapacity;
    }
    else {
      std::cerr << "vector::expand: new capacity is less than equal to current\n";
	  exit(1);
    }
  }
};
