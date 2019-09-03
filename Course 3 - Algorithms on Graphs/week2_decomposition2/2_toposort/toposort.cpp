#include <iostream>
#include <set>
#include <stack>
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
    size_t _size{0};

    void _explore(const int node, std::set<int> &visited, std::stack<int> &ordering) {
        // pre-visit
        visited.insert(node);
        for (auto a : this->adj[node]) {
            if (visited.find(a) == visited.end()) {
                this->_explore(a, visited, ordering);
            }
        }
        // post-visit
        ordering.push(node);
    }

  public:
    DiGraph(size_t size) : adj(size, std::vector<int>()), _size(size) {}

    void add_edges(const size_t m) {
        for (size_t j = 0; j < m; ++j) {
            size_t s, t;
            std::cin >> s >> t;
            // we use 0 index instead of 1 index
            this->adj[s - 1].push_back(t - 1);
        }
    }

    void display() {
        std::cout << "# nodes = " << this->_size << std::endl;
        std::cout << "Adjacencies: " << std::endl;
        for (size_t node = 0; node < this->_size; ++node) {
            std::cout << node + 1 << " -> ";
            for (auto a : this->adj[node]) {
                std::cout << a + 1 << " ";
            }
            std::cout << std::endl;
        }
    }

    std::stack<int> topo_sort() {
        std::stack<int> ordering;
        std::set<int> visited;
        for (int node = 0; node < this->_size; ++node) {
            if (visited.find(node) == visited.end()) {
                this->_explore(node, visited, ordering);
            }
        }
        return ordering;
    }

    void display_ordering() {
        std::stack<int> ordering = this->topo_sort();
        while (not ordering.empty()) {
            int n = ordering.top();
            ordering.pop();
            std::cout << n + 1 << " ";
        }
        std::cout << std::endl;
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
    graph.display_ordering();
}