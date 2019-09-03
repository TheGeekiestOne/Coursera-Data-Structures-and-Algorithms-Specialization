#include <iostream>
#include <limits>
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

// Node structure to use in the priority_queue supporting Dijkstra's algorithm
struct Node {
    int idx;
    int dist;

    Node(int idx, int dist) : idx(idx), dist(dist) {}

    bool operator>(const Node &rhs) const { return this->dist > rhs.dist; }
};

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

    // Dijkstra's algorithm to compute weighted distance fron node s
    std::vector<int> dijkstra(const int s) {
        // initialize distances to "infinity"
        std::vector<int> dist(adj.size(), std::numeric_limits<int>::max());
        dist[s] = 0;

        // keep nodes to be processed in a priority queue, heart of Dijkstra's algorithm
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
        pq.push(Node(s, 0));

        // priority_queue doesn't support changes of priority so we need to keep track
        // of updated distances some other way
        std::set<int> processed;

        while (not pq.empty()) {
            auto curr = pq.top();
            pq.pop();
            int curr_idx = curr.idx;

            if (DEBUG) {
                std::cout << "Processing: " << curr.idx << ", dist=" << curr.dist << std::endl;
            }
            // check whether we have seen the node before (i.e. distance was updated)
            if (processed.find(curr_idx) != processed.end()) {
                if (DEBUG) {
                    std::cout << "Node " << curr.idx << " was already processed." << std::endl;
                }
                continue;
            }
            // process outgoing edges to improve distance estimates
            for (int i = 0; i < adj[curr_idx].size(); ++i) {
                int n = adj[curr_idx][i];
                if (dist[n] > dist[curr_idx] + weights[curr_idx][i]) {
                    dist[n] = dist[curr_idx] + weights[curr_idx][i];
                    // append node with improved distance estimate
                    pq.push(Node(n, dist[n]));
                }
            }
            processed.insert(curr_idx);
        }

        return dist;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    // initialize graph
    WeightedDiGraph graph(n);
    // read edges
    graph.add_edges(m);

    int s, t;
    std::cin >> s >> t;
    s--, t--;
    auto s_dist = graph.dijkstra(s);
    std::cout << (s_dist[t] == std::numeric_limits<int>::max() ? -1 : s_dist[t]) << std::endl;
}