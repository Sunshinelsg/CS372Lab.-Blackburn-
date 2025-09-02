#include <iostream>
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
    std::cout << "f(30), recursivley = " << fibonacci(30) << '\n';
    std::cout << "f(30), iterativly  = " << fibit(30) << '\n';
    return 0;
}
