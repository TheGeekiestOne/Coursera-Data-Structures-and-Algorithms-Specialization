#include <iostream>
#include <queue>
#include <vector>

/*
* Author: Ayran Olckers
* Website https://ayran.dev
* Respect Coursera Honor Code
* Copyright © 2019. All rights reserved
*
*/


class Graph {
    std::vector<std::vector<int>> adj;

  public:
    Graph(int n) : adj(n, std::vector<int>()) {}

    void add_edges(const int m) {
        for (int j = 0; j < m; ++j) {
            int s, t;
            std::cin >> s >> t;
            // we use 0 index instead of 1 index
            // undirected graph, need to add both adjacencies
            this->adj[s - 1].push_back(t - 1);
            this->adj[t - 1].push_back(s - 1);
        }
    }

    // Finds whether the graph is bipartite.
    // We can do this by running a BFS while tracking the color (0/1) of the nodes.
    // WLOG assume the color of the 0th node is 0.
    bool is_bipartite() {
        std::vector<int> color(adj.size());
        // initialize colors to "undefined"
        for (auto &node : color) {
            node = -1;
        }
        // we assume that the given graph is non-empty
        color[0] = 0;

        // queue of nodes to be processed, heart of bfs algorithm
        std::queue<int> q;
        q.push(0);

        while (not q.empty()) {
            auto curr = q.front();
            q.pop();
            // add unprocessed nodes to the queue
            for (auto n : adj[curr]) {
                if (color[n] == -1) {
                    q.push(n);
                    // set distance of node (this marks the node as processed)
                    color[n] = !color[curr];
                } else if (color[n] == color[curr]) {
                    return false;
                }
            }
        }
        // we didn't find any triangles, graph is bipartite
        return true;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    // initialize graph
    Graph graph(n);
    // read edges
    graph.add_edges(m);

    std::cout << graph.is_bipartite() << std::endl;
}