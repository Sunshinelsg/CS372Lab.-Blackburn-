#include <iostream>
#include <chrono>
using namespace std;

void moveDisks(int, int, int, int);
void printIt(int , int , int );

int main() {
    const int FROMPEG = 1;
    const int TOPEG = 3;
    const int TEMPPEG = 2;
    
    for (auto numdisks: {5,10,15,20,25,30,35}) {
      cout << "Numdisks: " << numdisks << endl;
      auto start = chrono::high_resolution_clock::now();
      moveDisks(numdisks, FROMPEG, TOPEG, TEMPPEG);
      auto end = chrono::high_resolution_clock::now();
      chrono::duration<double, std::milli> elapsed = end - start;
      cout << "Elapsed time: " << elapsed.count() << " ms" << endl;
      cout << "Moved " << numdisks << " pegs"
           << " from peg " << FROMPEG
           << " to peg " << TOPEG << endl;
    }
}

void moveDisks(int num, int fromPeg, int toPeg, int tempPeg) {
     if (num > 0) {
        moveDisks(num -1, fromPeg, tempPeg, toPeg);
        printIt(num, fromPeg, toPeg);
        moveDisks(num-1, tempPeg, toPeg, fromPeg);
     }
}

void printIt(int disk, int fromPeg, int toPeg) {
  // Do nothing for timing test, but otherwise
  //.cout<< "Move disk " << disk
//      << " from pef " << fromPeg
  //    << " to peg " << toPeg << endl;
}
