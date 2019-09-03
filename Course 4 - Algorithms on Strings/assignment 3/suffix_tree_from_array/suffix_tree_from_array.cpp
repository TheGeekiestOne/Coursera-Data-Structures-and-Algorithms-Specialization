/*
 * Coursera/Algorithms on Strings/Weeks 3-4/Advanced Problem:
 * Construct the Suffix Tree from the SuffixArray (liner time)
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
#include <stack>
#include <string>
#include <cstdio>
#include <map>

using std::make_pair;
using std::map;
using std::pair;
using std::string;
using std::vector;
using std::stack;
using std::cin;
using std::cout;
using std::endl;

/*
 * The commented lines compute longest common prefix (LCP) array.
 * Though, in this problem, LCP array is given together with suffix array
 * Note that herein a buffer of nodes (compared to heap allocations)
 * and some other std::ios tweaks are used to speed up the execution.
 *
 */

/*
int LCP_of_suffixes(const string &S, int i, int j, int equal)
{
    int lcp = std::max(0, equal);
    while(i + lcp < S.size() && j + lcp < S.size()) {
        if(S[i+lcp] == S[j+lcp]) {
            ++lcp;
        }
        else {
            break;
        }
    }
    return lcp;
}
vector<int> invert_suffix_array(const vector<int> &order)
{
    vector<int> pos(order.size());
    for(int i = 0; i < pos.size() ; ++i) {
        pos[order[i]] = i;
    }
    return pos;
}
vector<int> compute_lcp_array(const string &S, const vector<int> &order)
{
    vector<int> lcp_array(S.size()-1);
    int lcp = 0;
    auto pos_in_order = invert_suffix_array(order);
    auto suffix = order[0];
    for(int i = 0; i < S.size(); ++i) {
        auto order_index = pos_in_order[suffix];
        if(order_index == S.size() - 1) {
            lcp = 0;
            suffix = (suffix + 1) % S.size();
            continue;
        }
        auto next_suffix = order[order_index+1];
        lcp = LCP_of_suffixes(S, suffix, next_suffix, lcp - 1);
        lcp_array[order_index] = lcp;
        suffix = (suffix + 1) % S.size();
    }
    return lcp_array;
}
*/
// Data structure to store edges of a suffix tree.
//struct Edge {
  // The ending node of this edge.
  //int node;
  // Starting position of the substring of the text 
  // corresponding to the label of this edge.
  //int start;
  // Position right after the end of the substring of the text 
  // corresponding to the label of this edge.
  //int end;

  //Edge(int node_, int start_, int end_) : node(node_), start(start_), end(end_) {}
  //Edge(const Edge& e) : node(e.node), start(e.start), end(e.end) {}
//};

struct suffix_tree_node {
    suffix_tree_node* parent{ nullptr };
    map<char, suffix_tree_node*> children;
    int string_depth{ 0 };
    int edge_start{ -1 };
    int edge_end{ -1 };
};

suffix_tree_node snodes_buf[400000];
int cur_buf_index = 0;

inline suffix_tree_node* new_tree_node(suffix_tree_node* parent, int depth, int start, int end)
{
    snodes_buf[cur_buf_index].parent = parent;
    snodes_buf[cur_buf_index].string_depth = depth;
    snodes_buf[cur_buf_index].edge_start = start;
    snodes_buf[cur_buf_index].edge_end = end;

    return &(snodes_buf[cur_buf_index++]);
}

inline suffix_tree_node* create_new_leaf(suffix_tree_node* node, const string& S, int suffix)
{
    suffix_tree_node* leaf = new_tree_node(node, S.size() - suffix, suffix + node->string_depth, S.size() - 1);
    node->children[S[leaf->edge_start]] = leaf;

    return leaf;
}

// Build suffix tree of the string text given its suffix array suffix_array
// and LCP array lcp_array. Return the tree as a mapping from a node ID
// to the vector of all outgoing edges of the corresponding node. The edges in the
// vector must be sorted in the ascending order by the first character of the edge label.
// Root must have node ID = 0, and all other node IDs must be different
// nonnegative integers.
//
// For example, if text = "ACACAA$", an edge with label "$" from root to a node with ID 1
// must be represented by Edge(1, 6, 7). This edge must be present in the vector tree[0]
// (corresponding to the root node), and it should be the first edge in the vector 
// (because it has the smallest first character of all edges outgoing from the root).
//map<int, vector<Edge> > SuffixTreeFromSuffixArray(
  //  const vector<int>& suffix_array,
  //  const vector<int>& lcp_array,
  //  const string& text) {
  //map<int, vector<Edge> > tree;
  // Implement this function yourself
  //return tree;
//}

inline suffix_tree_node* breake_edge(suffix_tree_node* node, const string& S, int start, int offset)
{
    char startChar = S[start];
    char midChar = S[start + offset];

    suffix_tree_node* midNode = new_tree_node(node, node->string_depth + offset, start, start + offset - 1);
    midNode->children[midChar] = node->children[startChar];
    node->children[startChar]->parent = midNode;
    node->children[startChar]->edge_start += offset;
    node->children[startChar] = midNode;

    return midNode;
}

suffix_tree_node* suffix_tree_from_array(const string& S, const vector<int>& order, const vector<int>& lcp_array)
{
    suffix_tree_node* root = new_tree_node(nullptr, 0, -1, -1);
    suffix_tree_node* curNode = root;

    int lcpPrev = 0;
    const int N = S.size();

    for (int i = 0; i < N; ++i) {
        auto suffix = order[i];

        while (curNode->string_depth > lcpPrev) {
            curNode = curNode->parent;
        }

        if (curNode->string_depth == lcpPrev) {
            curNode = create_new_leaf(curNode, S, suffix);
        }
        else {
            int edge_start = order[i - 1] + curNode->string_depth;
            int offset = lcpPrev - curNode->string_depth;
            suffix_tree_node* midNode = breake_edge(curNode, S, edge_start, offset);
            curNode = create_new_leaf(midNode, S, suffix);
        }

        if (i < N - 1) {
            lcpPrev = lcp_array[i];
        }
    }

    return root;
}

  // Build the suffix tree and get a mapping from 
  // suffix tree node ID to the list of outgoing Edges.
  //map<int, vector<Edge> > tree = SuffixTreeFromSuffixArray(suffix_array, lcp_array, text);
  //printf("%s\n", buffer);
  // Output the edges of the suffix tree in the required order.
  // Note that we use here the contract that the root of the tree
  // will have node ID = 0 and that each vector of outgoing edges
  // will be sorted by the first character of the corresponding edge label.
  //
  // The following code avoids recursion to avoid stack overflow issues.
  // It uses a stack to convert recursive function to a while loop.
  // The stack stores pairs (node, edge_index). 
  // This code is an equivalent of 
  //
  //    OutputEdges(tree, 0);
  //
  // for the following _recursive_ function OutputEdges:
  //
  // void OutputEdges(map<int, vector<Edge> > tree, int node_id) {
  //   const vector<Edge>& edges = tree[node_id];
  //   for (int edge_index = 0; edge_index < edges.size(); ++edge_index) {
  //     printf("%d %d\n", edges[edge_index].start, edges[edge_index].end);
  //     OutputEdges(tree, edges[edge_index].node);
  //   }
  // }
  
void recursive_preorder_print(suffix_tree_node* node)
{
    cout << node->edge_start << ' ' << node->edge_end + 1 << '\n';

    for (auto& next : node->children) {
        recursive_preorder_print(next.second);
    }
}

void iterative_preorder_print(suffix_tree_node* root)
{
    stack<suffix_tree_node*> nodeStack;

    for (auto iter = root->children.rbegin(); iter != root->children.rend(); ++iter) {
        nodeStack.push(iter->second);
    }

    while (!nodeStack.empty()) {

        suffix_tree_node* node = nodeStack.top();
        nodeStack.pop();

        cout << node->edge_start << ' ' << node->edge_end + 1 << '\n';

        for (auto iter = node->children.rbegin(); iter != node->children.rend(); ++iter) {
            nodeStack.push(iter->second);
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);

    string text;
    cin >> text;

    vector<int> suffix_array(text.size());
    vector<int> lcp_array(text.size() - 1);

    for (int j = 0, N = text.size(); j < N; ++j) {
        cin >> suffix_array[j];
    }

    for (int j = 0, N = text.size() - 1; j < N; ++j) {
        cin >> lcp_array[j];
    }

    suffix_tree_node* root = suffix_tree_from_array(text, suffix_array, lcp_array);

    cout << text << endl;

    iterative_preorder_print(root);

    return 0;
}