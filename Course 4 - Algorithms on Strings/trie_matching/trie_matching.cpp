#include <iostream>
#include <vector>
#include <map>


/* The Geekiest One
 * Coursera/Algorithms on Strings/Week 1/Problem 2: Implement TrieMatchin
 * Author: Ayran Olckers
 * Website: https://ayran.dev
 * Respect Coursera Honor Code
 * Copyright © 2019. All rights reserved
 *
 */


using namespace std;

using edges = map<char, int>;
using trie = vector<edges>;

trie build_trie(vector<string>& patterns)
{

    if (patterns.empty()) {
        return trie{};
    }

    trie t{ edges{} };

    int root{ 0 }, cnt{ 0 };

    for (auto& p : patterns) {
        int current = root;

        for (auto s : p) {
            if (t[current].find(s) != t[current].end()) {
                current = t[current][s];
            }
            else {
                t.emplace_back(edges{});
                t[current][s] = ++cnt;
                current = cnt;
            }
        }
    }
    return t;
}

vector<int> trie_matching(const string& text, int n, vector<string>& patterns)
{
    vector<int> positions;
    trie patterns_trie = build_trie(patterns);

    for (int i = 0; i < text.size(); ++i) {
        int current_vertex = 0, current_symbol_index = i;
        char symbol = text[current_symbol_index];
        while (true) {
            if (patterns_trie[current_vertex].empty()) {
                positions.push_back(i);
                break;
            }
            else if (patterns_trie[current_vertex].find(symbol) != patterns_trie[current_vertex].end()) {
                current_vertex = patterns_trie[current_vertex][symbol];
                symbol = text[++current_symbol_index];
            }
            else {
                break;
            }
        }
    }

    return positions;
}

int main(void)
{
    string text;
    cin >> text;

    int n;
    cin >> n;

    vector<string> patterns(n);
    for (int i = 0; i < n; i++) {
        cin >> patterns[i];
    }

    vector<int> ans = trie_matching(text, n, patterns);

    for (int i = 0; i < (int)ans.size(); i++) {
        cout << ans[i];
        if (i + 1 < (int)ans.size()) {
            cout << " ";
        }
        else {
            cout << endl;
        }
    }

    return 0;
}