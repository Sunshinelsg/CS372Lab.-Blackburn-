#include "randomsort.hpp"
#include <algorithm>

void selectionSort(std::vector<int>& arr) {
	size_t n = arr.size();
	for (size_t i = 0; i < n - 1; i++) {
		size_t min_idx = i;
		for (size_t j = i + 1; j < n; j++) {
			if (arr[j] < arr[min_idx])
				min_idx = j;
		}
		std::swap(arr[i], arr[min_idx]);
	}
}

void bubbleSort(std::vector<int>& arr) {
	size_t n = arr.size();
	for (size_t i = 0; i < n - 1; i++) {
		for (size_t j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1])
				std::swap(arr[j], arr[j + 1]);
		}
	}
}
void insertionSort(std::vector<int>& arr) {
	size_t n = arr.size();
	for (size_t i = 1; i < n; i++) {
		int key = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}
int partition(std::vector<int>& arr, int low, int high) {
	int pivot = arr[high];
	int i = low - 1;

	for (int j = low; j < high; j++) {
		if (arr[j] <= pivot) {
			i++;
			std::swap(arr[i], arr[j]);
		}
	}

	std::swap(arr[i + 1], arr[high]);
	return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}