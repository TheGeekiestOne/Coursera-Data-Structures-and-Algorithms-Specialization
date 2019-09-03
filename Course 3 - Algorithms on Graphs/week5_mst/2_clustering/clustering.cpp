#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>


/*
* Author: Ayran Olckers
* Website https://ayran.dev
* Respect Coursera Honor Code
* Copyright © 2019. All rights reserved
*
*/


const bool DEBUG = false;

struct Point2D {
    int x;
    int y;

    Point2D() : x(0), y(0) {}
    Point2D(int x, int y) : x(x), y(y) {}

    friend std::ostream &operator<<(std::ostream &os, const Point2D &point);
};

std::ostream &operator<<(std::ostream &os, const Point2D &point) {
    os << "(" << point.x << ", " << point.y << ") ";
    return os;
}

struct Set {
    size_t rank;
    int parent;

    Set() : rank(0), parent(-1) {}
};

class DisjointSets {
    std::vector<Set> _sets;

  public:
    DisjointSets(size_t size) : _sets(size) {
        for (size_t i = 0; i < size; ++i) {
            _sets[i].parent = i;
        }
    }

    size_t find(size_t u) {
        // find parent and compress path
        size_t idx{u};
        if (_sets[idx].parent != idx) {
            _sets[idx].parent = find(_sets[idx].parent);
        }
        return _sets[idx].parent;
    }

    void take_union(size_t u, size_t v) {
        auto u_id = find(u);
        auto v_id = find(v);

        if (u_id == v_id) {
            return;
        }

        if (_sets[u_id].rank > _sets[v_id].rank) {
            _sets[v_id].parent = u_id;
        } else {
            _sets[u_id].parent = v_id;
            if (_sets[u_id].rank == _sets[v_id].rank) {
                _sets[v_id].rank++;
            }
        }
    }
};

double distance(const Point2D &s, const Point2D &t) { return std::hypot(s.x - t.x, s.y - t.y); }

// Adaptation of Kruskal's algorithm
// Kruskal's algorithm starts with each vertex as a disjoint set
// The basic idea is to run the algo until only k disjoint sets are left
double clustering(std::vector<Point2D> &points, int k) {
    size_t n{points.size()};
    size_t nclusters{n};
    DisjointSets sets(n);
    // keep track of all edges
    std::vector<std::pair<size_t, size_t>> edges;
    edges.reserve((size_t)n * (n - 1) / 2);
    for (size_t s = 0; s < n; ++s) {
        for (size_t t = s + 1; t < n; ++t) {
            edges.push_back({s, t});
        }
    }
    // sort edges by distances
    std::sort(edges.begin(), edges.end(),
              // lambda function to be able to translate from index to points
              [points](std::pair<size_t, size_t> lhs, std::pair<size_t, size_t> rhs) {
                  auto norm_lhs = distance(points[lhs.first], points[lhs.second]);
                  auto norm_rhs = distance(points[rhs.first], points[rhs.second]);
                  return norm_lhs < norm_rhs;
              });

    // if (DEBUG) {
    //     for (auto &e : edges) {
    //         std::cout << points[e.first] << " -> " << points[e.second] << std::endl;
    //     }
    // }

    // loop through edges in increasing order
    size_t idx{0};
    while (nclusters >= k) {
        auto edge = edges[idx];
        if (DEBUG) {
            std::cout << points[edge.first] << " -> " << points[edge.second] << std::endl;
        }
        if (sets.find(edge.first) != sets.find(edge.second)) {
            sets.take_union(edge.first, edge.second);
            nclusters--;
        }
        idx++;
    }
    // go back one edge, that is the one that made nclusters < k
    auto edge = edges[--idx];
    if (DEBUG) {
        std::cout << points[edge.first] << " -> " << points[edge.second] << std::endl;
    }
    return distance(points[edge.first], points[edge.second]);
}

int main() {
    size_t n;
    int k;
    std::cin >> n;
    std::vector<Point2D> points(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> points[i].x >> points[i].y;
    }
    std::cin >> k;
    std::cout << std::setprecision(10) << clustering(points, k) << std::endl;
}