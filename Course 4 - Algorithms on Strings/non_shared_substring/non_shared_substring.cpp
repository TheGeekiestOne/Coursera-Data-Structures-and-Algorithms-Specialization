#include <iostream>
#include <algorithm>
#include <vector>

/* The Geekiest One
 * Coursera/Algorithms on Strings/Week 1/Advanced Problem:
 * Find the Shortest Non-Shared Substring of Two Strings
 * Author: Ayran Olckers
 * Website: https://ayran.dev
 * Respect Coursera Honor Code
 * Copyright © 2019. All rights reserved
 *
 */

using namespace std;

enum class NodeProperties {
    OnlyLTypeLeafs,
    OnlyRTypeLeafs,
    RTypeAndLtypeLeafs,
    None
};

struct SuffixTree {
    SuffixTree(const string& text, int second)
        : text(text)
        , LENGTH(text.size())
        , first(0)
        , second(second)
    {
        tree.emplace_back(Edges{});
        tree.reserve(LENGTH / 10);
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

    void print_tree_edges() noexcept
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

    NodeProperties search_leafs(int node, string s = "")
    {
        bool is_L_type_leaf = false;
        bool is_R_type_leaf = false;

        for (Node& n : tree[node]) {
            NodeProperties np = search_leafs(n.next, s + text.substr(n.start, n.end - n.start));

            if (np == NodeProperties::OnlyLTypeLeafs) {
                is_L_type_leaf = true;
                if (node == 0) {
                    substrings.emplace_back(text.substr(n.start, n.end - n.start));
                }
            }
            else if (np == NodeProperties::OnlyRTypeLeafs) {
                is_R_type_leaf = true;
            }
            else if (np == NodeProperties::RTypeAndLtypeLeafs) {
                is_R_type_leaf = true;
                is_L_type_leaf = true;
            }
            else {
                for (int i = n.start; i < n.end; ++i) {
                    if (text[i] == '$') {
                        is_R_type_leaf = true;
                        break;
                    }
                    if (text[i] == '#') {
                        is_L_type_leaf = true;
                        break;
                    }
                }
            }
        }

        if (is_R_type_leaf && is_L_type_leaf) {

            for (Node& n : tree[node]) {
                if (text[n.start] == '#' || text[n.start] == '$')
                    continue;

                for (int i = n.start; i < n.end; ++i) {
                    if (text[i] == '#') {
                        substrings.emplace_back(s + text[n.start]);
                        break;
                    }
                }
            }
            return NodeProperties::RTypeAndLtypeLeafs;
        }
        else if (!is_R_type_leaf && is_L_type_leaf) {
            for (Node& n : tree[node]) {
                if (text[n.start] == '$')
                    continue;
                for (int i = n.start; i < n.end; ++i) {
                    if (text[i] == '#') {
                        substrings.emplace_back(s);
                        break;
                    }
                }
            }
            return NodeProperties::OnlyLTypeLeafs;
        }
        else if (is_R_type_leaf && !is_L_type_leaf) {
            return NodeProperties::OnlyRTypeLeafs;
        }
        else {
            return NodeProperties::None;
        }
    }

    void print_non_shared_substring()
    {
        search_leafs(0);

        int max_size = 100000;
        int k = 0;
        for (int i = 0; i < substrings.size(); ++i) {
            //cout << substrings[i] << endl;
            if (substrings[i].size() < max_size) {
                k = i;
                max_size = substrings[i].size();
            }
        }
        cout << substrings[k] << endl;
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
    int first, second;
    vector<string> substrings;
};

int main(void)
{
    string text1;
    std::cin >> text1;
    string text2;
    std::cin >> text2;
    text1 += "#" + text2 + "$";

    SuffixTree suffixTree(text1, text2.size() + 1);
    suffixTree.build_tree();

    suffixTree.print_non_shared_substring();

    return 0;
}