#include <algorithm>
#include <iostream>
#include <set>
#include <stdexcept>
#include <vector>

/*********************************
******                      ******
***        Ayran Olckers       ***
**                              **
**            08/2019           **
******                      ******
**********************************/


// Class for directed Graphs
class DiGraph {
    std::vector<std::vector<int>> adj;
    std::vector<std::vector<int>> _reverseadj;
    size_t _size{0};

    void _explore(const int node, std::set<int> &visited) {
        // pre-visit
        visited.insert(node);
        for (auto a : this->adj[node]) {
            if (visited.find(a) == visited.end()) {
                this->_explore(a, visited);
            }
        }
        // post-visit
    }

    void _reverse_explore(const int node, std::set<int> &visited, std::vector<int> &ordering) {
        // pre-visit
        visited.insert(node);
        for (auto a : this->_reverseadj[node]) {
            if (visited.find(a) == visited.end()) {
                this->_reverse_explore(a, visited, ordering);
            }
        }
        // post-visit
        ordering.push_back(node);
    }

  public:
    DiGraph(size_t size)
        : adj(size, std::vector<int>()), _reverseadj(size, std::vector<int>()), _size(size) {}

    void add_edges(const size_t m) {
        for (size_t j = 0; j < m; ++j) {
            size_t s, t;
            std::cin >> s >> t;
            // we use 0 index instead of 1 index
            this->adj[s - 1].push_back(t - 1);
            // we also want to save the reverse graph
            this->_reverseadj[t - 1].push_back(s - 1);
        }
    }

    void display() {
        std::cout << "# nodes = " << this->_size << std::endl;
        std::cout << "Adjacencies: " << std::endl;
        // for each node, display its adjancent nodes
        for (size_t node = 0; node < this->_size; ++node) {
            std::cout << node + 1 << " -> ";
            for (auto a : this->adj[node]) {
                std::cout << a + 1 << " ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<int> get_reverse_post_order() {
        // dfs of the reversed graph
        std::vector<int> ordering;
        std::set<int> visited;
        for (int node = 0; node < this->_size; ++node) {
            if (visited.find(node) == visited.end()) {
                this->_reverse_explore(node, visited, ordering);
            }
        }
        std::reverse(ordering.begin(), ordering.end());
        // ordering in reversed post-ordering wrt. the original graph
        return ordering;
    }

    size_t number_of_strong_components() {
        if (this->_size == 0) {
            return 0;
        }
        std::set<int> visited;
        size_t ncomponents = 0;
        // we want to loop through the nodes in reverse post-order
        auto node_list = get_reverse_post_order();
        for (auto node : node_list) {
            // std::cout << node << std::endl;
            // in reverse post-order, explore finds the strong connected component of the node
            if (visited.find(node) == visited.end()) {
                this->_explore(node, visited);
                ncomponents++;
            }
        }
        return ncomponents;
    }
};

int main() {
    size_t n, m;
    std::cin >> n >> m;
    // initialize graph
    DiGraph graph(n);
    // read edges
    graph.add_edges(m);
    // graph.display();
    // output a topological ordering
    std::cout << graph.number_of_strong_components() << std::endl;
}