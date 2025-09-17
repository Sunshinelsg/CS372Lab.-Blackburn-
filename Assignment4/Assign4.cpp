#include <iostream>
#include "assign4queue.hpp"

int josephus(int N, int M) {
	Queue<int> circle;

	for (int i = 1; i <= N; ++i) {
		circle.push(i);
	}

	while (true) {
		for (int i = 0; i < M; ++i) {
			int person = circle.back();
			circle.pop();
			circle.push(person);
		}
		int eliminated = circle.back();
		circle.pop();

		std::cout << "Eliminated: " << eliminated << std::endl;

		if (circle.empty()) {
			return eliminated;
		}
	}
}

int main() {
	int N, M;
	std::cout << "Enter number of people (N): ";
	std::cin >> N;
	std::cout << "Enter number of passes (M): ";
	std::cin >> M;

	int winner = josephus(N, M);
	std::cout << "The Winner is: " << winner << std::endl;

	return 0;
}