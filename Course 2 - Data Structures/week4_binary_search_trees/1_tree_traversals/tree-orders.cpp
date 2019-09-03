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


template <class T> void display(const std::vector<T> vec) {
    for (auto &e : vec) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

class BinaryTree {
  private:
    std::vector<int> key;
    std::vector<int> left;
    std::vector<int> right;

  public:
    void read_input() {
        int n;
        std::cin >> n;
        key.resize(n);
        left.resize(n);
        right.resize(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> key[i] >> left[i] >> right[i];
        }
    }

    std::vector<int> in_order_traversal() {
        std::vector<int> result;
        std::set<int> processed;
        std::stack<int> to_process;
        // Initialize
        processed.insert(-1);
        to_process.push(0);
        while (not to_process.empty()) {
            auto idx = to_process.top();
            if (processed.find(left[idx]) != processed.end()) {
                result.push_back(key[idx]);
                processed.insert(idx);
                to_process.pop();
                if (right[idx] != -1) {
                    to_process.push(right[idx]);
                }
            } else {
                to_process.push(left[idx]);
            }
        }
        return result;
    }

    std::vector<int> pre_order_traversal() {
        std::vector<int> result;
        std::stack<int> to_process;
        // Initialize
        to_process.push(0);
        while (not to_process.empty()) {
            auto idx = to_process.top();
            result.push_back(key[idx]);
            to_process.pop();
            if (right[idx] != -1) {
                to_process.push(right[idx]);
            }
            if (left[idx] != -1) {
                to_process.push(left[idx]);
            }
        }
        return result;
    }

    std::vector<int> post_order_traversal() {
        std::vector<int> result;
        std::set<int> processed;
        std::stack<int> to_process;
        // Initialize
        processed.insert(-1);
        to_process.push(0);
        while (not to_process.empty()) {
            auto idx = to_process.top();
            bool flag{true};
            if (processed.find(right[idx]) == processed.end()) {

                to_process.push(right[idx]);
                flag = false;
            }
            if (processed.find(left[idx]) == processed.end()) {
                to_process.push(left[idx]);
                flag = false;
            }
            if (flag) {
                result.push_back(key[idx]);
                to_process.pop();
                processed.insert(idx);
            }
        }
        return result;
    }
};

int main() {
    BinaryTree t;
    t.read_input();
    display(t.in_order_traversal());
    display(t.pre_order_traversal());
    display(t.post_order_traversal());
    return 0;
}