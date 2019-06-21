#include <iostream>

// Well there’s not much to say, as it is not a very tricky problem. I just
// implemented the algorithm that they suggested in What To Do section. Instead of
// storing the whole Fibonacci number, just store their modulus and calculate the
// next one using that.


// int get_fibonacci_last_digit_naive(int n) {
//     if (n <= 1)
//         return n;
//
//     int previous = 0;
//     int current  = 1;
//
//     for (int i = 0; i < n - 1; ++i) {
//         int tmp_previous = previous;
//         previous = current;
//         current = tmp_previous + current;
//     }
//
//     return current % 10;
// }
//
// int main() {
//     int n;
//     std::cin >> n;
//     int c = get_fibonacci_last_digit_naive(n);
//     std::cout << c << '\n';
//     }
//


int get_fibonacci_last_digit(long long n) {
    int first = 0;
    int second = 1;

    int res;

    for (int i = 2; i <= n; i++) {
        res = (first + second) % 10;
        first = second;
        second = res;
    }

    return res;
}

int main() {
    int n;
    std::cin >> n;
    int c = get_fibonacci_last_digit(n);
    std::cout << c << '\n';

    return 0;
}
