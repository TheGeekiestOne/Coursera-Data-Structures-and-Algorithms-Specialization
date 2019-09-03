/*
 * Coursera/Algorithms on Strings/Weeks 3-4/Problem 2:
 * Construct the Suffix Array of a Long String (linear time)
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

using namespace std;

constexpr int ALPHABET_SIZE = 5;

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

std::vector<int> sortDoubled(const std::string& s, int L, const std::vector<int>& order, const std::vector<int>& cclass)
{
    std::vector<int> count(s.size());
    std::vector<int> newOrder(s.size());

    for (int i = 0; i < s.size(); ++i) {
        ++count[cclass[i]];
    }

    for (int j = 1; j < s.size(); ++j) {
        count[j] += count[j - 1];
    }

    for (int i = s.size() - 1; i >= 0; --i) {
        int start = (order[i] - L + s.size()) % s.size();
        int cl = cclass[start];
        newOrder[--count[cl]] = start;
    }

    return newOrder;
}

std::vector<int> computeCharacterClasses(const std::string& s, const std::vector<int>& order)
{
    std::vector<int> cclass(s.size());

    for (int i = 1; i < s.size(); ++i) {
        if (s[order[i]] != s[order[i - 1]]) {
            cclass[order[i]] = cclass[order[i - 1]] + 1;
        }
        else {
            cclass[order[i]] = cclass[order[i - 1]];
        }
    }

    return cclass;
}

std::vector<int> countingCharactersSort(const std::string& s)
{
    std::vector<int> order(s.size());
    std::vector<int> count(ALPHABET_SIZE);

    for (auto& c : s) {
        ++count[getIndex(c)];
    }

    for (int j = 1; j < ALPHABET_SIZE; ++j) {
        count[j] += count[j - 1];
    }

    for (int i = s.size() - 1; i >= 0; --i) {
        char c = s[i];
        count[getIndex(c)] -= 1;
        order[count[getIndex(c)]] = i;
    }
    return order;
}

std::vector<int> updateClasses(const std::vector<int>& newOrder, const std::vector<int>& cclass, int L)
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

std::vector<int> buildSuffixArray(const std::string& s)
{
    std::vector<int> order = countingCharactersSort(s);
    std::vector<int> cclass = computeCharacterClasses(s, order);
    int L = 1;

    while (L < s.size()) {
        order = sortDoubled(s, L, order, cclass);
        cclass = updateClasses(order, cclass, L);
        L *= 2;
    }
    return std::move(order);
}

int main()
{
    std::string s;
    cin >> s;
    auto order = buildSuffixArray(s);

    for (auto i : order) {
        cout << i << ' ';
    }

    return 0;
}