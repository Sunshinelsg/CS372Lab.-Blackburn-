#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

void moveDisks(int, int, int, int);
void printIt(int, int, int);

int main() {
    const int FROMPEG = 1;
    const int TOPEG = 3;
    const int TEMPPEG = 2;

    for (auto numdisks : { 3,5,6 }) {
        cout << "Numdisks: " << numdisks << endl;
        auto start = high_resolution_clock::now();
        moveDisks(numdisks, FROMPEG, TOPEG, TEMPPEG);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);

        cout << "Moved " << numdisks << " pegs"
            << " from peg " << FROMPEG
            << " to peg " << TOPEG << endl;
    }
    return 0;
}

void moveDisks(int num, int fromPeg, int toPeg, int tempPeg) {
    if (num > 0) {
        moveDisks(num - 1, fromPeg, tempPeg, toPeg);
        printIt(num, fromPeg, toPeg);
        moveDisks(num - 1, tempPeg, toPeg, fromPeg);
    }
}

void printIt(int disk, int fromPeg, int toPeg) {
    // Do nothing for timing test, but otherwise
    cout << "Move disk " << disk
        << " from pef " << fromPeg
        << " to peg " << toPeg << endl;
}

