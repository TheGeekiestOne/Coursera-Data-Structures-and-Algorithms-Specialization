/*
 * Coursera/Algorithms on Strings/Week 2/Problem 2:
 * Reconstruct a String from its Burrows–Wheeler Transform
 * 
 * Author: Ayran Olckers @ The Geekiest One
 * Site: http://ayran.dev
 * Respect Coursera Honor Code
 * Copyright © 2019. All rights reserved
 *
 */

#include <algorithm>
#include <iostream>
#include <vector>

using Symbols = std::vector<int>;

inline int getIndexInSymbols(char s)
{
    switch (s) {
    case 'A':
        return 0;
    case 'C':
        return 1;
    case 'G':
        return 2;
    case 'T':
        return 3;
    default:
        return 4;
    }
}

inline int getIndexInRrightColumn(Symbols& sm, char s, int cnt)
{
    switch (s) {
    case 'A':
        return cnt;
    case 'C':
        return sm[0] + cnt;
    case 'G':
        return sm[1] + sm[0] + cnt;
    case 'T':
        return sm[2] + sm[1] + sm[0] + cnt;
    default:
        return 0;
    }
}

void inverseBWT(const std::string& bwt)
{
    if (bwt.size() == 1) {
        std::cout << bwt << '\n';
        return;
    }

    Symbols symbols(5, 0);
    std::vector<int> indexes(bwt.size(), 0);

    auto* iptr = &indexes[0];
    auto* sptr = bwt.c_str();
    while (*sptr) {
        *iptr++ = ++symbols[getIndexInSymbols(*sptr++)];
    }

    const auto rsize = bwt.size();
    char r[rsize + 1];
    r[rsize] = '\0';

    char s = bwt[0];
    int j = indexes[0];
    int k = bwt.size() - 1;

    r[k--] = '$';
    r[k--] = s;

    for (int i = 2, iters = bwt.size() - i; iters--; ++i) {
        int indexInRrightColumn = getIndexInRrightColumn(symbols, s, j);
        r[k--] = bwt[indexInRrightColumn];
        j = indexes[indexInRrightColumn];
        s = r[k + 1];
    }

    std::cout << r << '\n';
}

int main()
{
    std::string bwt;
    std::cin >> bwt;
    inverseBWT(bwt);
    return 0;
}