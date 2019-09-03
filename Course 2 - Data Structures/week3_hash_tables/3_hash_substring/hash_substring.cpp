#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

/*********************************
******                      ******
***        Ayran Olckers       ***
**                              **
**            07/2019           **
******                      ******
**********************************/


long long hash(const std::string &s, const long long &p, const long long &x) {
    long long hash{0};
    // hash = sum(s[i] * x^i mod p)
    for (int i = s.size() - 1; i >= 0; --i) {
        hash = (hash * x + s[i]) % p;
    }
    return hash;
}

std::vector<long long> compute_hashes(const std::string &text, const size_t psize,
                                      const long long &p, const long long &x) {
    // Dynamically compute hashes to save time.
    size_t size = text.size() - psize + 1;
    std::vector<long long> hashes(size);
    // Initialize last hash
    auto begin = text.begin() + size - 1;
    auto end = text.end();
    std::string last(begin, end);
    hashes[size - 1] = hash(last, p, x);
    // Dynamically compute hashes: h_{k-1} = x*h_k + text_{k-1} - text_{k+p-1}*x^p mod p
    // Precoumpute x^psize
    long long x_to_psize = 1;
    for (int i = 1; i <= psize; ++i) {
        x_to_psize = (x_to_psize * x) % p;
    }
    for (int k = (int)size - 1; k > 0; --k) {
        hashes[k - 1] = (x * hashes[k] + text[k - 1] - text[k + psize - 1] * x_to_psize) % p;
        // Normalize mod p value to positive representative.
        hashes[k - 1] = (hashes[k - 1] + p) % p;
    }
    return hashes;
}

// Rabin-Karp's algorithm for searching pattern in a text
std::vector<size_t> rabin_karp(const std::string &pattern, const std::string &text) {
    // Choose a prime and number x in 1, prime - 1 for hashing function
    long long p{1299709};
    long long x{23};
    // Precompute hashes of substrings
    size_t psize = pattern.size();
    long long phash = hash(pattern, p, x);
    auto hashes = compute_hashes(text, psize, p, x);
    // Compare substrings via their hashes
    std::vector<size_t> indexes;
    for (size_t idx = 0; idx < hashes.size(); ++idx) {
        if (hashes[idx] == phash) {
            // Get substring in text to compare
            auto first = text.begin() + idx;
            auto last = text.begin() + idx + psize;
            std::string compare(first, last);
            if (compare == pattern) {
                // Found a match!
                indexes.push_back(idx);
            }
        } else {
            // If hashes are different, substrings can't match. Do nothing.
        }
    }
    return indexes;
}

std::vector<size_t> naive_matching(const std::string &pattern, const std::string &text) {
    std::vector<size_t> ans;
    for (size_t i = 0; i + pattern.size() <= text.size(); ++i)
        if (text.substr(i, pattern.size()) == pattern)
            ans.push_back(i);
    return ans;
}

// Helper function to output a vector in the console.
template <class T> void display(const std::vector<T> &vector) {
    for (auto &v : vector) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

bool test_solution(const std::string &pattern, const std::string &text) {
    auto positions = rabin_karp(pattern, text);
    auto positions_naive = naive_matching(pattern, text);
    std::cout << "Rabin-Karp: ";
    display(positions);
    std::cout << "Naive: ";
    display(positions_naive);
    bool correct = (positions == positions_naive);
    if (correct) {
        std::cout << "OK!" << std::endl;
    } else {
        std::cout << "FAIL!" << std::endl;
        std::cout << pattern << std::endl << text << std::endl;
    }
    return correct;
}

int main() {
    std::string pattern, text;
    std::cin >> pattern;
    std::cin >> text;
    // test_solution(pattern, text);
    auto positions = rabin_karp(pattern, text);
    display(positions);
    return 0;
}