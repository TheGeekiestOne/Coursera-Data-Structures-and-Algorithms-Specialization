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
    size_t _size{0};

    void _explore(const int node, std::set<int> &visited, std::set<int> &path) {
        // pre-visit
        // std::cout << node << std::endl;
        visited.insert(node);
        path.insert(node);
        for (auto a : this->adj[node]) {
            if (path.find(a) != path.end()) {
                // node already exist in the path, we found cycle!
                // std::cout << "cycle!" << std::endl;
                throw std::logic_error("There is a cycle!");
            }
            if (visited.find(a) == visited.end()) {
                this->_explore(a, visited, path);
            }
        }
        // post-visit
        path.erase(node);
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

    bool empty() { return this->_size == 0; }

    bool is_acyclic() {
        // perform dfs recursively
        std::set<int> visited;
        // keep track of the nodes in the current depth first path.
        std::set<int> path;
        for (int node = 0; node < this->_size; ++node) {
            if (visited.find(node) == visited.end()) {
                // std::cout << "New component! " << node << std::endl;
                try {
                    this->_explore(node, visited, path);
                } catch (std::logic_error &err) {
                    // found a cycle
                    return false;
                }
            }
        }
        return true;
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
    // output wether the graph is acylcic
    std::cout << not graph.is_acyclic() << std::endl;
}