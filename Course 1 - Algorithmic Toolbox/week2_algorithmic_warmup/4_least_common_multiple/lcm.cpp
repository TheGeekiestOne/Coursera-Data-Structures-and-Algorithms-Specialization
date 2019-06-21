#include <iostream>

// This is quite straightforward, nothing too complicated.
//  Here, I’m using this property, GCD (a, b) · LCM (a, b) = a · b, to calculate LCM.

int euclidGCD (int a, int b){
  if (b== 0) return a;
  return euclidGCD(b, a%b);
}

long long lcm_naive(long long a, long long b) {
  // for (long l = 1; l <= (long long) a * b; ++l)
  //   if (l % a == 0 && l % b == 0)
  //     return l;
  //
  // return (long long) a * b;

  return (a * b)/euclidGCD(a, b);
}

int main() {
  long long a, b;
  std::cin >> a >> b;
  std::cout << lcm_naive(a, b) << std::endl;
  return 0;
}
