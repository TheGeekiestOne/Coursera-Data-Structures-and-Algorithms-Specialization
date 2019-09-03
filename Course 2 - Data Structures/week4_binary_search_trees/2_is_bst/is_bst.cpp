#include <algorithm>
#include <iostream>
#include <set>
#include <stack>
#include <vector>


/*********************************
******                      ******
***        Ayran Olckers       ***
**                              **
**            07/2019           **
******                      ******
**********************************/

using std::cin;
using std::cout;
using std::endl;
using std::vector;

template <class T> void display(const std::vector<T> vec) {
    for (auto &e : vec) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

struct Node {
    int key;
    int left;
    int right;

    Node() : key(0), left(-1), right(-1) {}
    Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

vector<int> in_order_traversal(const vector<Node> &tree) {
    std::vector<int> result;
    std::set<int> processed;
    std::stack<int> to_process;
    // Initialize
    processed.insert(-1);
    to_process.push(0);
    while (not to_process.empty()) {
        auto idx = to_process.top();
        if (processed.find(tree[idx].left) != processed.end()) {
            result.push_back(tree[idx].key);
            processed.insert(idx);
            to_process.pop();
            if (tree[idx].right != -1) {
                to_process.push(tree[idx].right);
            }
        } else {
            to_process.push(tree[idx].left);
        }
    }
    return result;
}

bool IsBinarySearchTree(const vector<Node> &tree) {
    // Implement correct algorithm here
    if (tree.empty()) {
        return true;
    }
    auto traversed = in_order_traversal(tree);
    vector<int> keys(tree.size());
    for (int i = 0; i < tree.size(); ++i) {
        keys[i] = tree[i].key;
    }
    std::sort(keys.begin(), keys.end());
    // display(traversed);
    // display(keys);
    return keys == traversed;
}

int main() {
    int nodes;
    cin >> nodes;
    vector<Node> tree;
    for (int i = 0; i < nodes; ++i) {
        int key, left, right;
        cin >> key >> left >> right;
        tree.push_back(Node(key, left, right));
    }
    if (IsBinarySearchTree(tree)) {
        cout << "CORRECT" << endl;
    } else {
        cout << "INCORRECT" << endl;
    }
    return 0;
}