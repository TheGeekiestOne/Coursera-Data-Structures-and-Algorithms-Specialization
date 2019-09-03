#include <iostream>
#include <queue>
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

// structure to support undefined number and avoid overflow issues
class Number {
  public:
    long long value;
    bool is_infty;
    // undefined works as infinity
    Number() : is_infty(true) {}

    void set_value(long long value) {
        this->value = value;
        this->is_infty = false;
    }

    // implement infinity arithmetic
    Number operator+(const long long &rhs) {
        Number res = Number();
        if (not is_infty) {
            res.set_value(value + rhs);
        }
        return res;
    }

    Number operator+(const Number &rhs) {
        Number res = Number();
        res.is_infty = is_infty or rhs.is_infty;
        if (not res.is_infty) {
            res.set_value(value + rhs.value);
        }
        return res;
    }

    // infinity comparison
    bool operator>(const Number &rhs) {
        if (is_infty) {
            return !rhs.is_infty;
        } else if (rhs.is_infty) {
            return false;
        } else {
            return value > rhs.value;
        }
    }
};

// dummy pair structure to contain the results of the Bellman-Ford algorithm
struct Result {
    std::vector<Number> dist;
    std::vector<int> prev;
    std::set<int> neg_infty;

    Result(std::vector<Number> dist, std::vector<int> prev, std::set<int> neg_infty)
        : dist(dist), prev(prev), neg_infty(neg_infty) {}
};

// Weighted directed graph class
class WeightedDiGraph {
    std::vector<std::vector<int>> adj;
    std::vector<std::vector<long long>> weights;

  public:
    WeightedDiGraph(int n) : adj(n, std::vector<int>()), weights(n, std::vector<long long>()) {}

    void add_edges(const int m) {
        for (int j = 0; j < m; ++j) {
            int s, t, w;
            std::cin >> s >> t >> w;
            // we use 0 index instead of 1 index
            this->adj[s - 1].push_back(t - 1);
            this->weights[s - 1].push_back(w);
        }
    }

    // adapt Bellman Ford algorithm to find shortest paths with, possibly, negative cycles.
    Result bellman_ford(const int s) {
        // dist is long long to prevent overflow problems caused by with negative distances
        std::vector<Number> dist(adj.size());
        std::vector<int> prev(adj.size(), -1);

        dist[s].set_value(0);
        prev[s] = 0;

        // loop through edges |V| - 1 times to update distance estimates
        for (int count = 0; count < adj.size() - 1; ++count) {
            if (DEBUG) {
                std::cout << "Count=" << count << std::endl;
            }
            for (int u = 0; u < adj.size(); ++u) {
                for (int j = 0; j < adj[u].size(); ++j) {
                    int v = adj[u][j];

                    if (DEBUG) {
                        std::cout << "Processing edge: "
                                  << "(" << u << ", " << v << ")" << std::endl;
                    }

                    // try to update the distance estimates
                    if (dist[v] > dist[u] + weights[u][j]) {
                        dist[v] = dist[u] + weights[u][j];
                        prev[v] = u;
                    }
                }

                if (DEBUG) {
                    for (int i = 0; i < dist.size(); ++i) {
                        std::cout << i << ":" << dist[i].value << " ";
                    }
                    std::cout << std::endl;
                }
            }
        }

        if (DEBUG) {
            std::cout << "Last state: ";
            for (int i = 0; i < dist.size(); ++i) {
                std::cout << i << ":" << dist[i].value << " ";
            }
            std::cout << std::endl;
        }

        // go again one last time to detect nodes reachable from negative cycles via BFS.
        std::queue<int> nqueue;
        std::set<int> neg_infty;
        std::set<int> processed;
        for (int u = 0; u < adj.size(); ++u) {
            for (int j = 0; j < adj[u].size(); ++j) {
                int v = adj[u][j];
                if (dist[v] > dist[u] + weights[u][j]) {
                    dist[v] = dist[u] + weights[u][j];
                    nqueue.push(v);
                    processed.insert(v);
                    if (DEBUG) {
                        std::cout << v << std::endl;
                    }
                }
            }
        }

        while (not nqueue.empty()) {
            auto curr = nqueue.front();
            nqueue.pop();

            neg_infty.insert(curr);

            for (auto n : adj[curr]) {
                if (processed.find(n) == processed.end()) {
                    nqueue.push(n);
                    processed.insert(n);
                }
            }
        }

        return Result(dist, prev, neg_infty);
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    // initialize graph
    WeightedDiGraph graph(n);
    // read edges
    graph.add_edges(m);

    int s;
    std::cin >> s;
    s--;

    auto res = graph.bellman_ford(s);

    for (int node = 0; node < n; ++node) {
        if (res.prev[node] == -1) {
            std::cout << "*";
        } else if (res.neg_infty.find(node) != res.neg_infty.end()) {
            std::cout << "-";
        } else {
            std::cout << res.dist[node].value;
        }
        std::cout << std::endl;
    }
}