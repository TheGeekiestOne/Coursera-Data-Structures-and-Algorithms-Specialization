#include <iostream>
#include <limits>
#include <set>
#include <vector>

/*
* Author: Ayran Olckers
* Website https://ayran.dev
* Respect Coursera Honor Code
* Copyright © 2019. All rights reserved
*
*/

const bool DEBUG = false;

// Weighted directed graph class
class WeightedDiGraph {
    std::vector<std::vector<int>> adj;
    std::vector<std::vector<int>> weights;

  public:
    WeightedDiGraph(int n) : adj(n, std::vector<int>()), weights(n, std::vector<int>()) {}

    void add_edges(const int m) {
        for (int j = 0; j < m; ++j) {
            int s, t, w;
            std::cin >> s >> t >> w;
            // we use 0 index instead of 1 index
            this->adj[s - 1].push_back(t - 1);
            this->weights[s - 1].push_back(w);
        }
    }

    // adapt Bellman Ford algorithm to find negative cycles reachable from s
    bool bellman_ford(const int s) {
        // dist is long long to prevent overflow problems caused by with negative distances
        std::vector<long long> dist(adj.size());
        // initialize distances to "infinity"
        for (int i = 0; i < adj.size(); ++i) {
            dist[i] = std::numeric_limits<int>::max();
        }
        dist[s] = 0;

        // loop through edges |V| - 1 times to update distance estimates
        for (int count = 0; count < adj.size() - 1; ++count) {
            for (int u = 0; u < adj.size(); ++u) {
                if (DEBUG) {
                    std::cout << "Count=" << count << std::endl;
                    for (int i = 0; i < dist.size(); ++i) {
                        std::cout << i << ":" << dist[i] << " ";
                    }
                    std::cout << std::endl;
                }
                for (int j = 0; j < adj[u].size(); ++j) {
                    int v = adj[u][j];

                    if (DEBUG) {
                        std::cout << "Processing edge: "
                                  << "(" << u << ", " << v << ")" << std::endl;
                    }

                    // try to update the distance estimates
                    if (dist[v] > dist[u] + weights[u][j]) {
                        dist[v] = dist[u] + weights[u][j];
                    }
                }
            }
        }

        if (DEBUG) {
            for (int i = 0; i < dist.size(); ++i) {
                std::cout << i << ":" << dist[i] << " ";
            }
            std::cout << std::endl;
        }

        // go again one last time
        // if any edge can update any distance, we must have a negative cycle
        for (int u = 0; u < adj.size(); ++u) {
            for (int j = 0; j < adj[u].size(); ++j) {
                int v = adj[u][j];
                if (dist[v] > dist[u] + weights[u][j]) {
                    return true;
                }
            }
        }

        return false;
    }

    bool contains_negative_cycle() {
        for (int s = 0; s < adj.size(); ++s) {
            if (bellman_ford(s)) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    // initialize graph
    WeightedDiGraph graph(n);
    // read edges
    graph.add_edges(m);

    std::cout << graph.bellman_ford(0) << std::endl;
    // std::cout << graph.contains_negative_cycle() << std::endl;
}