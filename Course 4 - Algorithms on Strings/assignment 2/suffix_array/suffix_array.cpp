/*
 * Coursera/Algorithms on Strings/Week 2/Problem 4:
 * Construct the Suffix Array of a String
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
#include <map>

using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.




struct SuffixTree {
    SuffixTree(const string& text)
        : text(text)
        , LENGTH(text.size())
    {
        tree.reserve(LENGTH / 10);
        tree.emplace_back(Edges{});
    }

    struct Node {
        int next{ 0 };
        int start{ 0 };
        int end{ 0 };
        int suffix_start{ 0 };
    };

    using Edges = map<char, Node>;

    inline void add_node(int start, int i, int suffix_start)
    {
        tree[i].emplace(
            make_pair(text[start], Node{ cnt++, start, LENGTH, suffix_start }));
        tree.emplace_back(Edges{});
    }

    inline void add_nodes_branching(Node& node, int k, int m, int suffix_start)
    {
        if (!tree[node.next].empty()) {
            tree.emplace_back(Edges{});
            tree.emplace_back(Edges{});

            tree[cnt] = std::move(tree[node.next]);

            tree[node.next].emplace(
                make_pair(text[m], Node{ cnt++, m, node.end, suffix_start }));
            tree[node.next].emplace(
                make_pair(text[k], Node{ cnt++, k, LENGTH, suffix_start }));

            node.end = m;
        }
        else {
            add_node(k, node.next, suffix_start);
            add_node(m, node.next, node.suffix_start);
            node.end = m;
        }
    }
    void print_suffix_array(int level = 0)
    {
        for (const auto& it : tree[level]) {
            if (!tree[it.second.next].empty()) {
                print_suffix_array(it.second.next);
            }
            else {
                cout << it.second.suffix_start << ' ';
            }
        }
    }

    void build_tree() noexcept
    {
        for (int j = 0; j < LENGTH; ++j) {
            int cur = ROOT;

            for (int k = j; true;) {
                auto it = tree[cur].find(text[k]);

                if (it == tree[cur].end()) {
                    add_node(k, cur, j);
                    break;
                }

                Node& node = it->second;
                int m = node.start;

                for (; k < LENGTH && m < node.end; ++k, ++m) {
                    if (text[k] != text[m]) {
                        add_nodes_branching(node, k, m, j);
                        goto inner_loop_wayout;
                    }
                }
                if (m == node.end && k == LENGTH) {
                    break;
                }
                else if (m == node.end) {
                    if (tree[node.next].empty()) {
                        add_node(k, node.next, j);
                        break;
                    }
                    cur = node.next;
                    continue;
                }
                else {
                    if (tree[node.next].empty()) {
                        add_node(m, node.next, j);
                        node.end = m;
                        break;
                    }
                    tree.emplace_back(Edges{});
                    tree[cnt].emplace(
                        make_pair(text[m], Node{ node.next, m, node.end, j }));
                    node.next = cnt;
                    node.end = m;
                    break;
                }
            inner_loop_wayout:
                break;
            }
        }
    }

    int cnt{ 1 };
    const string& text;

    const int LENGTH{ 0 };
    const int ROOT{ 0 };

    vector<Edges> tree;
};

int main(void)
{
    string text;
    std::cin >> text;

    SuffixTree suffixTree(text);
    suffixTree.build_tree();
    suffixTree.print_suffix_array();

    return 0;
}