#include <iostream>
#include <chrono>
long fibonacci(unsigned n) {
    if (n < 2) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}
long fibit(int num) {
   long x = 0, y = 1, z = 0;
   if (num == 0) {return x;}
   for (int i = 2; i <= num; i++) {
      z = x + y;
      x = y;
      y = z;
   }
   return y;
}
int main() {
    auto start = std::chrono::steady_clock::now();
    std::cout << "f(30), recursivley = " << fibonacci(30) << '\n';
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << std::scientific << elapsed_seconds.count() << "s\n";
    start = std::chrono::steady_clock::now();
    std::cout << "f(30), iterativly  = " << fibit(30) << '\n';
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
    std::cout << "elapsed time: " << std::scientific << elapsed_seconds.count() << "s\n";
    return 0;
}
