/*
 * Coursera/Algorithms on Strings/Week 2/Problem 3:
 * Implement Better Burrows–Wheeler Matching
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

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position 
//       of this character in the sorted array of 
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
//void PreprocessBWT(const string& bwt, 
                  // map<char, int>& starts, 
                  // map<char, vector<int> >& occ_count_before) {
  // Implement this function yourself
//}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.




class BWMatching {

    const std::size_t N;
    const std::string& bwt;
    std::vector<std::vector<int> > symbolsCounterByIndex;
    std::vector<int> symbolsCounter;

    inline int getIndex(char s) noexcept
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

    inline int getFirstPosition(char s) noexcept
    {
        switch (s) {
        case 'A':
            return 1;
        case 'C':
            return symbolsCounter[0] + 1;
        case 'G':
            return symbolsCounter[1] + symbolsCounter[0] + 1;
        case 'T':
            return symbolsCounter[2] + symbolsCounter[1] + symbolsCounter[0] + 1;
        default:
            return 0;
        }
    }

    inline int getSymbolsCountByIndex(int i, char s) noexcept
    {
        return symbolsCounterByIndex[getIndex(s)][i];
    }

    inline bool isSymbolInTopBottomRange(int top, int bottom, char s) noexcept
    {
        return symbolsCounterByIndex[getIndex(s)][bottom] > symbolsCounterByIndex[getIndex(s)][top];
    }

public:
    explicit BWMatching(const std::string& bwt)
        : N{ bwt.size() }
        , bwt{ bwt }
        , symbolsCounter{ std::vector<int>(5) }
        , symbolsCounterByIndex{ std::vector<std::vector<int> >(5, std::vector<int>(bwt.size() + 1)) }
    {
        for (int i = 1; i <= N; ++i) {
            for (auto& o : symbolsCounterByIndex) {
                o[i] = o[i - 1];
            }
            ++symbolsCounter[getIndex(bwt[i - 1])];
            ++symbolsCounterByIndex[getIndex(bwt[i - 1])][i];
        }
    }

    int getNumOfPatternOccurences(const std::string& pattern)
    {

        if (pattern.size() == 1) {
            return symbolsCounter[getIndex(pattern[0])];
        }

        int top = 0, bottom = bwt.size() - 1;
        int k = pattern.size();

        while (top <= bottom) {
            if (k) {
                char s = pattern[--k];
                if (isSymbolInTopBottomRange(top, bottom + 1, s)) {
                    top = getFirstPosition(s) + getSymbolsCountByIndex(top, s);
                    bottom = getFirstPosition(s) + getSymbolsCountByIndex(bottom + 1, s) - 1;
                }
                else {
                    return 0;
                }
            }
            else {
                return (bottom - top) + 1;
            }
        }
    }
};

int main()
{
    std::string bwt;
    std::cin >> bwt;

    BWMatching bwm(bwt);

    int s;
    std::cin >> s;

    while (s--) {
        std::string pattern;
        std::cin >> pattern;
        std::cout << bwm.getNumOfPatternOccurences(pattern) << '\n';
    }
    return 0;
}