#pragma once
#ifndef RANDOMSORT_HPP
#define RANDOMSORT_HPP

#include <iostream>
#include <vector>


void selectionSort(std::vector<int>& arr);
void bubbleSort(std::vector<int>& arr);
void insertionSort(std::vector<int>& arr);
void quickSort(std::vector<int>& arr, int low, int high);

#endif 
