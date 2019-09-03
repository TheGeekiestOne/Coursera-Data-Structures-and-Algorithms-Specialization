/*
 * Coursera/Algorithms on Strings/Weeks 3-4/Problem 1:
 * Find All Occurrences of a Pattern in a String (Knuth-Morris-Pratt Algorithm)
 * 
 * Author: Ayran Olckers @ The Geekiest One
 * Site: http://ayran.dev
 * Respect Coursera Honor Code
 * Copyright © 2019. All rights reserved
 *
 */

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

vector<int> compute_prefix_function(const string& p)
{
    vector<int> s(p.size());

    for (int j = 1, border = 0, n = p.size(); j < n; ++j) {
        while (border && p[j] != p[border]) {
            border = s[border - 1];
        }
        border = (p[j] == p[border]) ? ++border : 0;
        s[j] = border;
    }

    return s;
}

vector<int> find_pattern_ocurrences(const string& pattern, const string& text)
{
    string S = pattern + '$' + text;
    vector<int> s = compute_prefix_function(S);
    vector<int> result;

    for (int i = pattern.size() + 1; i < S.size(); ++i) {
        if (s[i] == pattern.size()) {
            result.push_back(i - 2 * pattern.size());
        }
    }

    return result;
}

int main()
{
    string pattern, text;
    cin >> pattern;
    cin >> text;

    vector<int> result = find_pattern_ocurrences(pattern, text);
    for (int i = 0; i < result.size(); ++i) {
        printf("%d ", result[i]);
    }

    return 0;
}