#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <string>
#include "randomsort.hpp"

using namespace std;
using namespace std::chrono;

template<typename Func>
double timeSort(Func sortFunction, vector<int> arr) {
	auto start = high_resolution_clock::now();
	sortFunction(arr);
	auto end = high_resolution_clock::now();
	duration<double, milli> duration = end - start;
	return duration.count();
}

double timeQuickSort(vector<int> arr) {
	auto start = high_resolution_clock::now();
	quickSort(arr, 0, arr.size()-1);
	auto end = high_resolution_clock::now();
	duration<double, milli> duration = end - start;
	return duration.count();
}

int main() {
	vector<int>sizes = { 10,50,100,500,1000,5000,10000,50000,100000,250000};
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>dis(1, 1000000);

	cout << left << setw(10) << "Sort" << setw(15) << "SelectionSort" << setw(15) << "BubbleSort" << setw(15) << "InsertionSort" << setw(15) << "QuickSort" << endl;

	for (int size : sizes) {
		vector<int> baseArray(size);
		generate(baseArray.begin(), baseArray.end(), [&]() {return dis(gen); });

		double bubbleTime = -1, selectionTime = -1, insertionTime = -1, quickTime = -1;

		if (size <= 10000) {
			bubbleTime = timeSort(bubbleSort, baseArray);
			selectionTime = timeSort(selectionSort, baseArray);
			insertionTime = timeSort(insertionSort, baseArray);

		}
		quickTime = timeQuickSort(baseArray);
		cout << left << setw(10) << size 
			<< setw(15) << (bubbleTime >= 0 ? to_string(bubbleTime) + " ms" : "Very Slow") 
			<< setw(15) << (selectionTime >= 0 ? to_string(selectionTime) + " ms" : "Very Slow") 
			<< setw(15) << (insertionTime >= 0 ? to_string(insertionTime) + " ms" : "Very Slow") 
			<< setw(15) << (quickTime >= 0 ? to_string(quickTime) + " ms" : "Wrong") << endl;
	}
	return 0;
}