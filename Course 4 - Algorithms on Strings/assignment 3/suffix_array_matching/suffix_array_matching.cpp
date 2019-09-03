/*
 * Coursera/Algorithms on Strings/Weeks 3-4/Problem 3:
 * Pattern Matching with the Suffix Array
 * 
 * Author: Ayran Olckers @ The Geekiest One
 * Site: http://ayran.dev
 * Respect Coursera Honor Code
 * Copyright © 2019. All rights reserved
 *
 */

#include <iostream>
#include <vector>
#include <utility>
#include <string.h>

using namespace std;

constexpr unsigned ALPHABET_SIZE = 5;

char text[100001];
char pattern[100001];

unsigned S;
unsigned PS;

inline int getIndex(char c)
{
    switch (c) {
    case 'A':
        return 1;
    case 'C':
        return 2;
    case 'G':
        return 3;
    case 'T':
        return 4;
    default:
        return 0;
    }
}

std::vector<int> sortDoubled(int L, const std::vector<int>& order,
    const std::vector<int>& cclass)
{
    std::vector<int> count(S);
    std::vector<int> newOrder(S);

    for (int i = 0; i < S; ++i) {
        ++count[cclass[i]];
    }

    for (int j = 1; j < S; ++j) {
        count[j] += count[j - 1];
    }

    for (int i = S - 1; i >= 0; --i) {
        int start = (order[i] - L + S) % S;
        newOrder[--count[cclass[start]]] = start;
    }

    return newOrder;
}

std::vector<int> computeCharacterClasses(const std::vector<int>& order)
{
    std::vector<int> cclass(S);

    for (int i = 1; i < S; ++i) {
        if (*(text + order[i]) != *(text + order[i - 1]))
            cclass[order[i]] = cclass[order[i - 1]] + 1;
        else
            cclass[order[i]] = cclass[order[i - 1]];
    }

    return cclass;
}

std::vector<int> countingCharactersSort()
{
    std::vector<int> order(S), cnt(ALPHABET_SIZE);

    for (int i = 0; i < S; ++i)
        ++cnt[getIndex(*(text + i))];

    for (int j = 1; j < ALPHABET_SIZE; ++j)
        cnt[j] += cnt[j - 1];

    for (int i = S - 1; i >= 0; --i)
        order[--cnt[getIndex(*(text + i))]] = i;

    return order;
}

std::vector<int> updateClasses(const std::vector<int>& newOrder,
    const std::vector<int>& cclass, int L)
{
    const int n = newOrder.size();
    std::vector<int> newCclass(n);

    for (int i = 1; i < n; ++i) {
        int cur = newOrder[i], prev = newOrder[i - 1];
        int mid = cur + L, midPrev = (prev + L) % n;

        if (cclass[cur] != cclass[prev] || cclass[mid] != cclass[midPrev]) {
            newCclass[cur] = newCclass[prev] + 1;
        }
        else {
            newCclass[cur] = newCclass[prev];
        }
    }
    return std::move(newCclass);
}

std::vector<int> buildSuffixArray()
{
    std::vector<int> order = countingCharactersSort();
    std::vector<int> cclass = computeCharacterClasses(order);
    int L = 1;

    while (L < S) {
        order = sortDoubled(L, order, cclass);
        cclass = updateClasses(order, cclass, L);
        L *= 2;
    }
    return order;
}

void suffixArrayPatternMatching(const std::vector<int>& suffixArray,
    vector<pair<int, int> >& results)
{
    int minIndex = 0;
    int maxIndex = S;

    while (minIndex < maxIndex) {
        int midIndex = (minIndex + maxIndex) / 2;
        if (strncmp(pattern, text + suffixArray[midIndex], PS) > 0) {
            minIndex = midIndex + 1;
        }
        else {
            maxIndex = midIndex;
        }
    }

    int start = minIndex;
    maxIndex = S;

    while (minIndex < maxIndex) {
        int midIndex = (minIndex + maxIndex) / 2;
        if (strncmp(pattern, text + suffixArray[midIndex], PS) < 0) {
            maxIndex = midIndex;
        }
        else {
            minIndex = midIndex + 1;
        }
    }

    int end = maxIndex;

    if (start > end) {
        return;
    }

    for (auto& p : results) {
        if (p.first <= start && end <= p.second) {
            return;
        }
        else if (p.first <= start && end > p.second) {
            if (p.second >= start) {
                p.second = end;
                return;
            }
        }
        else if (end >= p.first) {
            p.first = start;
            return;
        }
    }

    results.push_back(std::pair<int, int>(start, end));
}

int main()
{
    scanf("%s", text);
    S = strlen(text);
    *(text + S++) = '$';
    *(text + S) = '\0';

    std::vector<int> suffixArray = buildSuffixArray();
    vector<pair<int, int> > results;

    int numOfPatterns;
    scanf("%d", &numOfPatterns);

    while (numOfPatterns--) {
        scanf("%s", pattern);
        PS = strlen(pattern);
        suffixArrayPatternMatching(suffixArray, results);
    }

    for (auto& resp : results) {
        while (resp.first < resp.second) {
            printf("%d ", suffixArray[resp.first++]);
        }
    }

    return 0;
}