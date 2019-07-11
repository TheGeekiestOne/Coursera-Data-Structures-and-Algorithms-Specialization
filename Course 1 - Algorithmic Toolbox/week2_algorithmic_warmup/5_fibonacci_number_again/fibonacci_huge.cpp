#include <iostream>

// I couldn’t find a suitable definition for Pisano period so that I could make a
// naive algorithm. Well, it turns out, I was looking at the wrong place. The whole
// time, it was right in front of my eyes but I couldn’t see it. So, without further
// ado, here’s the definition. This was a very tricky one. I had to search a lot and
// read quite a few posts in the Course forum to understand the algorithm.
//
// The algorithm to compute the get_fibonacci_huge was given in the What To Do section.
// “Therefore, to compute, say, F(2015) mod 3 we just need to find the remainder of
// 2015 when divided by 8. Since 2015 = 251·8+7, we conclude that F(2015) mod 3 = F 7 mod 3 = 1.”
//  We just have to generalize it.
//
// First we need to find the remainder of F(n) divided by the length of Paisano
// period given m. To find the length of Paisano period for m, simply find the
// remainder of F(0) mod m to F(m*m) mod m and stop as soon as you encounter 01,
// as they indicate that the next iteration is being started, and return the length
// up to that point.
//
// Now, you only need to find the F(remainder), which is going to be a lot less than F(n) and simply return it.

long long get_pisano_period(long long m) {
    long long a = 0, b = 1, c = a + b;
    for (int i = 0; i < m * m; i++) {
        c = (a + b) % m;
        a = b;
        b = c;
        if (a == 0 && b == 1) return i + 1;
    }
}

long long get_fibonacci_huge_naive(long long n, long long m) {
    // if (n <= 1)
    //     return n;
    long long remainder = n % get_pisano_period(m);

    long long previous = 0;
    long long current  = 1;

    long long res = remainder;

    // for (long long i = 0; i < n - 1; ++i) {
    //     long long tmp_previous = previous;
    //     previous = current;
    //     current = tmp_previous + current;

    for (int i = 1; i < remainder; i++) {
      res = (previous + current) % m;
      previous = current;
      current = res;
    }

    return res % m;
    //return current % m;
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonacci_huge_naive(n, m) << '\n';
}
