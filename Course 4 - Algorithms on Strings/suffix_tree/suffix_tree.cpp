/* The Geekiest One
 * Coursera/Algorithms on Strings/Week 1/Problem 4:
 * Construct the Suffix Tree of a String
 * Author: Ayran Olckers
 * Website: https://ayran.dev
 * Respect Coursera Honor Code
 * Copyright © 2019. All rights reserved
 *
 */

#include <algorithm>
#include <iostream>
#include <vector>

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.


using namespace std;

struct SuffixTree {
    SuffixTree(const string& text)
        : text(text)
        , LENGTH(text.size())
    {
        tree.reserve(LENGTH / 10);
        tree.emplace_back(Edges{});
    }

    struct Node {
        Node(int next, int start, int end)
            : next(next)
            , start(start)
            , end(end)
        {
        }

        int next{ 0 };
        int start{ 0 };
        int end{ 0 };
    };

    using Edges = vector<Node>;

    inline void add_node(int start, int i)
    {
        tree.emplace_back(Edges{});
        tree[i].emplace_back(Node(cnt++, start, LENGTH));
    }

    inline void add_nodes_branching(Node& node, int k, int m)
    {
        if (!tree[node.next].empty()) {
            tree.emplace_back(Edges{});
            tree.emplace_back(Edges{});

            tree[cnt] = std::move(tree[node.next]);

            tree[node.next].emplace_back(Node{ cnt++, m, node.end });
            tree[node.next].emplace_back(Node(cnt++, k, LENGTH));

            node.end = m;
        }
        else {
            add_node(m, node.next);
            add_node(k, node.next);
            node.end = m;
        }
    }

    void print_tree_edges()
    {

        for (const auto& edges : tree) {
            for (const auto& e : edges) {
                for (int i = e.start; i < e.end; ++i) {
                    cout << text[i];
                }
                cout << "\n";
            }
        }
    }

    void build_tree() noexcept
    {

        for (int j = 0; j < LENGTH; ++j) {
            int cur = ROOT;

            for (int k = j; true;) {
                char symbol = text[k];

                auto it = find_if(tree[cur].begin(), tree[cur].end(),
                    [&](const Node& n) { return text[n.start] == symbol; });

                if (it == tree[cur].end()) {
                    add_node(k, cur);
                    break;
                }

                Node& node = *it;
                int m = node.start;

                for (; k < LENGTH && m < node.end; ++k, ++m) {
                    if (text[k] != text[m]) {
                        add_nodes_branching(node, k, m);
                        goto inner_loop_wayout;
                    }
                }
                if (m == node.end && k == LENGTH) {
                    break;
                }
                else if (m == node.end) {
                    if (tree[node.next].empty()) {
                        add_node(k, node.next);
                        break;
                    }
                    cur = node.next;
                    continue;
                }
                else {
                    if (tree[node.next].empty()) {
                        add_node(m, node.next);
                        node.end = m;
                        break;
                    }
                    tree.emplace_back(Edges{});
                    tree[cnt].emplace_back(Node(node.next, m, node.end));
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
    suffixTree.print_tree_edges();

    return 0;
}