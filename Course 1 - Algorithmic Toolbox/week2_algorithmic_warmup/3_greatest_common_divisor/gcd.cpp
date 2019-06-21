#include <iostream>

// Although the first function, gcd(a, b), gives the correct answer, we can’t use
// it because on larger inputs, like in Sample 2, it takes too long to compute the
// answer and we can’t fulfill the Time Limit constraint, i-e 1 sec.
//
// Therefore, we use a more complex but faster algorithm, euclidGCD(a,b). If you
// want to understand this algorithm and see how and why it works, here is a nice
// explanation at Khan Academy.

int gcd_naive(int a, int b) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int euclidGCD (int a, int b){
  if (b== 0) return a;
  return euclidGCD(b, a%b);
}

int main() {
  int a, b;
  std::cin >> a >> b;
  //std::cout << gcd_naive(a, b) << std::endl;
  std::cout << euclidGCD(a, b) << std::endl;
  return 0;
}
