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

    int distance(const int s, const int t) {
        // bfs starting at node s
        std::vector<int> dist(adj.size());
        // initialize distances to "infinity"
        for (auto &node : dist) {
            node = -1;
        }
        dist[s] = 0;

        // queue of nodes to be processed, heart of bfs algorithm
        std::queue<int> q;
        q.push(s);

        while (not q.empty()) {
            auto curr = q.front();
            q.pop();
            // add unprocessed nodes to the queue
            for (auto n : adj[curr]) {
                if (dist[n] == -1) {
                    q.push(n);
                    // set distance of node
                    dist[n] = dist[curr] + 1;
                }
            }
        }

        return dist[t];
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    // initialize graph
    Graph graph(n);
    // read edges
    graph.add_edges(m);

    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << graph.distance(s, t) << std::endl;
}