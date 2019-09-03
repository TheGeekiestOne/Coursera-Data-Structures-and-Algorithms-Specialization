#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>


/*********************************
******                      ******
***        Ayran Olckers       ***
**                              **
**            07/2019           **
******                      ******
**********************************/

const bool DEBUG = false;

// Splay tree implementation to support the Rope data structure

// Vertex of a splay tree
struct Vertex {
    // key field stores an index pointing to a character via the initial string.
    int key;
    // Include size to be able to compute order statistics of the key values.
    int size;
    Vertex *left;
    Vertex *right;
    Vertex *parent;

    Vertex(int key) : key(key), size(1), left(nullptr), right(nullptr), parent(nullptr) {}
};

void update(Vertex *v) {
    if (v == nullptr)
        return;
    v->size =
        1 + (v->left != nullptr ? v->left->size : 0) + (v->right != nullptr ? v->right->size : 0);
    if (v->left != nullptr) {
        v->left->parent = v;
    }
    if (v->right != nullptr) {
        v->right->parent = v;
    }
}

void small_rotation(Vertex *v) {
    Vertex *parent = v->parent;
    if (parent == nullptr) {
        return;
    }
    Vertex *grandparent = v->parent->parent;
    if (parent->left == v) {
        Vertex *m = v->right;
        v->right = parent;
        parent->left = m;
    } else {
        Vertex *m = v->left;
        v->left = parent;
        parent->right = m;
    }
    update(parent);
    update(v);
    v->parent = grandparent;
    if (grandparent != nullptr) {
        if (grandparent->left == parent) {
            grandparent->left = v;
        } else {
            grandparent->right = v;
        }
    }
}

void big_rotation(Vertex *v) {
    if (v->parent->left == v && v->parent->parent->left == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else {
        // Zig-zag
        small_rotation(v);
        small_rotation(v);
    }
}

// Makes splay of the given vertex and makes
// it the new root.
void splay(Vertex *&root, Vertex *v) {
    if (v == nullptr)
        return;
    while (v->parent != nullptr) {
        if (v->parent->parent == nullptr) {
            small_rotation(v);
            break;
        }
        big_rotation(v);
    }
    root = v;
}

// Searches the tree for the node in position k (1-based) ~ k-th order statistic
// Assume k in [1, size]
Vertex *find(Vertex *&root, int k) {
    if (k == 0) {
        return nullptr;
    }
    int s{0};
    if (root->left != nullptr) {
        s = root->left->size;
    }
    if (k == s + 1) {
        return root;
    } else if (k < s + 1 and root->left != nullptr) {
        return find(root->left, k);
    } else if (root->right != nullptr) {
        return find(root->right, k - s - 1);
    } else {
        return nullptr;
    }
}

void split(Vertex *root, int pos, Vertex *&left, Vertex *&right) {
    right = find(root, pos);
    splay(root, right);
    if (right == nullptr) {
        left = root;
        return;
    }
    left = right->left;
    right->left = nullptr;
    if (left != nullptr) {
        left->parent = nullptr;
    }
    update(left);
    update(right);
}

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree,
// returns nullptr.
Vertex *old_find(Vertex *&root, int key) {
    Vertex *v = root;
    Vertex *last = root;
    Vertex *next = nullptr;
    while (v != nullptr) {
        if (v->key >= key && (next == nullptr || v->key < next->key)) {
            next = v;
        }
        last = v;
        if (v->key == key) {
            break;
        }
        if (v->key < key) {
            v = v->right;
        } else {
            v = v->left;
        }
    }
    splay(root, last);
    return next;
}

// Version of split using the old_find function, used for rope initalization.
void old_split(Vertex *root, size_t key, Vertex *&left, Vertex *&right) {
    right = old_find(root, key);
    splay(root, right);
    if (right == nullptr) {
        left = root;
        return;
    }
    left = right->left;
    right->left = nullptr;
    if (left != nullptr) {
        left->parent = nullptr;
    }
    update(left);
    update(right);
}

Vertex *merge(Vertex *left, Vertex *right) {
    if (left == nullptr)
        return right;
    if (right == nullptr)
        return left;
    Vertex *min_right = right;
    while (min_right->left != nullptr) {
        min_right = min_right->left;
    }
    splay(right, min_right);
    right->left = left;
    update(right);
    return right;
}

class Rope {
    std::string s, s_slow;
    Vertex *root = nullptr;

    void insert(int idx) {
        Vertex *left = nullptr;
        Vertex *right = nullptr;
        Vertex *new_vertex = nullptr;
        old_split(root, idx, left, right);
        if (right == nullptr || right->key != idx) {
            new_vertex = new Vertex(idx);
        }
        root = merge(merge(left, new_vertex), right);
    }

    void traverse(Vertex *node, std::stringstream &ss) {
        // In order search of the spaly tree
        if (node == nullptr) {
            return;
        }
        traverse(node->left, ss);
        // output original character
        ss << s[node->key];
        traverse(node->right, ss);
    }

  public:
    Rope(const std::string &s) : s(s), s_slow(s) {
        for (size_t idx = 0; idx < s.size(); ++idx) {
            insert(idx);
        }
    }

    void process_slow(int i, int j, int k) {
        // t is the substring of s without the characters between i-th through j-th
        std::string t = s_slow.substr(0, i) + s_slow.substr(j + 1);
        s_slow = t.substr(0, k) + s_slow.substr(i, j - i + 1) + t.substr(k);
    }

    void process(int i, int j, int k) {

        if (DEBUG) {
            std::cout << std::endl
                      << "Processing: i=" << i << " j=" << j << " k=" << k << std::endl;
        }

        Vertex *left = nullptr;
        Vertex *middle = nullptr;
        Vertex *right = nullptr;

        if (DEBUG) {
            std::cout << "  Initial state (root): ";
            std::cout << result(root) << std::endl;
        }

        split(root, j + 2, middle, right);
        if (DEBUG) {
            std::cout << "  After 1st call to split: " << std::endl;
            std::cout << "    middle: ";
            std::cout << result(middle) << std::endl;

            std::cout << "    right: ";
            std::cout << result(right) << std::endl;
        }

        split(middle, i + 1, left, middle);

        if (DEBUG) {
            std::cout << "  After 2nd call to split: " << std::endl;
            std::cout << "    left: ";
            std::cout << result(left) << std::endl;

            std::cout << "    middle: ";
            std::cout << result(middle) << std::endl;

            std::cout << "    right: ";
            std::cout << result(right) << std::endl;
        }

        root = merge(left, right);

        if (DEBUG) {
            std::cout << "  Merged left & right: ";
            std::cout << result(root) << std::endl;
        }

        if (root != nullptr) {
            split(root, k + 1, left, right);
        } else {
            root = middle;
        }

        if (DEBUG) {
            std::cout << "  After 3rd call to split (insert step):" << std::endl;
            std::cout << "    left: ";
            std::cout << result(left) << std::endl;

            std::cout << "    right: ";
            std::cout << result(right) << std::endl;
        }

        root = merge(merge(left, middle), right);

        if (DEBUG) {
            std::cout << "State after process (root): ";
            std::cout << result(root) << std::endl;
        }
    }

    std::string result() {
        std::stringstream ss;
        std::string result;
        traverse(root, ss);
        ss >> result;
        return result;
    }

    std::string result(Vertex *node) {
        std::stringstream ss;
        std::string result;
        if (node != nullptr) {
            traverse(node, ss);
            ss >> result;
        }
        return result;
    }

    std::string result_slow() { return s_slow; }

    void test_find() {
        std::cout << result(root) << std::endl;
        while (true) {
            size_t k;
            std::cin >> k;
            auto v = find(root, k);
            std::cout << s[v->key] << ", size=" << v->size << std::endl;
        }
    }
};

void stress_test() {
    while (true) {
        std::string alphabet{"abcdefghijklmnopqrstuvwxyz"};
        std::string s;

        std::cout << "generate string" << std::endl;
        // generate test string of size from 1 up to 300 000
        int ssize = (rand() % 30) + 1;
        for (int i = 0; i < ssize; ++i) {
            s += alphabet[rand() % alphabet.size()];
        }
        std::cout << "size: " << ssize << std::endl;
        std::cout << "string: " << s << std::endl;

        std::cout << "create rope" << std::endl;
        Rope rope(s);

        std::cout << "generate queries" << std::endl;
        // generate queries
        int q = (rand() % 5) + 1;
        for (int q_i = 0; q_i < q; ++q_i) {
            int a = rand() % ssize;
            int b = rand() % ssize;
            int i = std::min(a, b);
            int j = std::max(a, b);
            int k_limit = ssize - (j - i + 1);
            int k{0};
            if (k_limit > 0) {
                k = rand() % (ssize - (j - i + 1));
            }

            std::cout << i << " " << j << " " << k << std::endl;

            std::cout << "s_prev" << std::endl;
            auto s_prev = rope.result();

            std::cout << "process" << std::endl;
            rope.process(i, j, k);
            std::cout << "process_slow" << std::endl;
            rope.process_slow(i, j, k);

            std::cout << "result" << std::endl;
            auto result = rope.result();

            std::cout << "result_slow" << std::endl;
            auto result_slow = rope.result_slow();

            if (result == result_slow) {
                std::cout << "OK!" << std::endl;
            } else {
                std::cout << "FAIL!" << std::endl;
                std::cout << "s=" << s << std::endl;
                std::cout << "i=" << i << " j=" << j << " k=" << k << std::endl;
                std::cout << "s_prev=" << s_prev << std::endl;
                std::cout << "result=" << result << std::endl;
                std::cout << "result_slow=" << result_slow << std::endl;
                break;
            }
        }
    }
}

int main() {

    // stress_test();

    std::string s;
    std::cin >> s;
    Rope rope(s);

    if (DEBUG) {
        while (true) {
            int i, j, k;
            std::cin >> i >> j >> k;
            rope.process(i, j, k);
        }
    } else {
        int nops;
        std::cin >> nops;
        for (int op = 0; op < nops; ++op) {
            int i, j, k;
            std::cin >> i >> j >> k;
            rope.process(i, j, k);
        }
    }

    std::cout << rope.result() << std::endl;
}