#include <iostream>
#include <chrono>
#include <stack>
#include <cmath>
using namespace std;
using namespace std::chrono;

void moveDisks(int, stack<int>&, stack<int>&, stack<int>&, bool);
void printIt(int, char, char, bool);
void MoveDisksHelper(stack<int>&, stack<int>&, char, char, bool);

int main() {
    const bool PRINT_MOVES = false;
    for (auto numdisks : { 5, 10, 15, 20, 25, 30, 35 }) {
        stack<int> source;
        stack<int> dest;
        stack<int> aux;

        cout << "Numdisks: " << numdisks << endl;
        auto start = high_resolution_clock::now();
        moveDisks(numdisks, source, aux, dest, PRINT_MOVES);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end-start);
        cout << "Moved " << numdisks << " pegs." << endl;
        cout << "Duration: " << duration.count() << " milliseconds" << endl;
    }
    return 0;
}

void moveDisks(int num, stack<int>& fromPeg, stack<int>& tempPeg, stack<int>& toPeg, bool printMoves) {
    char s = 'S', d = 'D', a = 'A';
    if (num % 2 == 0) { // Swap in num disks is even.
        char temp = d;
        d = a;
        a = temp;
    }
    int numberOfMoves = pow(2, num) - 1;
    for (int i = num; i >= 1; i--) {
        fromPeg.push(i);
    }
    // now do moves:
    for (int i = 1; i <= numberOfMoves; i++) {
        if (i % 3 == 0) {
            MoveDisksHelper(tempPeg, toPeg, a, d, printMoves);
        }
        else if (i % 3 == 2) {
            MoveDisksHelper(fromPeg, tempPeg, s, a, printMoves);
        }
        else if (i % 3 == 1) {
            MoveDisksHelper(fromPeg, toPeg, s, d, printMoves);
        }
    }
}

void MoveDisksHelper(stack<int>& source, stack<int>& dest, char s, char d, bool printMoves) {
    int top1;
    int top2;
    if (source.empty()) {
        top2 = dest.top();
        dest.pop();
        source.push(top2);
        printIt(top2, d, s, printMoves);
    }
    else if (dest.empty()) {
        top1 = source.top();
        source.pop();
        dest.push(top1);
        printIt(top1, s, d, printMoves);
    }
    else if (source.top() > dest.top()) {
        top1 = source.top();
        source.pop();
        top2 = dest.top();
        dest.pop();
        source.push(top1);
        source.push(top2);
        printIt(top2, d, s, printMoves);
    }
    else {
        top2 = dest.top();
        dest.pop();
        top1 = source.top();
        source.pop();
        dest.push(top2);
        dest.push(top1);
        printIt(top1, s, d, printMoves);
    }
}

void printIt(int disk, char fromPeg, char toPeg, bool printMoves) {
    // Do nothing for timing test, but otherwise
    if (!printMoves)return;
    std::cout << "Move disk " << disk
        << "from peg " << fromPeg
        << "to peg " << toPeg << std::endl;
}


