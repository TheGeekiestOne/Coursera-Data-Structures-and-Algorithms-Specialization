#include <algorithm>
#include <cmath>
#include <iomanip>
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


struct Point2D {
    int x;
    int y;

    Point2D() : x(0), y(0){};
    Point2D(int x, int y) : x(x), y(y){};
};

// Node structure to use in the priority_queue supporting Prim's algorithm
struct Node {
    size_t idx;
    double dist;

    Node(size_t idx, double dist) : idx(idx), dist(dist){};

    bool operator>(const Node &rhs) const { return dist > rhs.dist; }
};

double distance(const Point2D &s, const Point2D &t) { return std::hypot(s.x - t.x, s.y - t.y); }

double minimum_distance(std::vector<Point2D> &points) {
    // Adapt Prim's MST algorithm
    // dist are the priority, initialize to "infinity"
    std::vector<double> dist(points.size(), std::numeric_limits<double>::max());
    // start with first point
    dist[0] = 0;

    // keep elements to be processed in a priority queue
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    pq.push(Node(0, 0));

    // priority_queue doesn't support changes of priority so we need to keep track
    // of updated distances some other way
    std::set<size_t> processed;

    // keep track of missing vertices
    std::set<size_t> missing;
    for (size_t i = 0; i < points.size(); i++) {
        missing.insert(i);
    }

    double result = 0.;
    while (not pq.empty()) {
        auto min = pq.top();
        pq.pop();
        // check whether we have seen the node before (i.e. distance was updated)
        // NOTE: this is a hack to avoid implementing a change_priority method
        if (processed.find(min.idx) != processed.end()) {
            continue;
        }

        result += min.dist;
        missing.erase(min.idx);
        // loop through all vertices not yet reached by the MST
        // recompute distances to current state of MST
        for (auto i : missing) {
            auto d = distance(points[min.idx], points[i]);
            if (d < dist[i]) {
                dist[i] = d;
                pq.push(Node(i, d));
            }
        }
        processed.insert(min.idx);
    }

    return result;
}

int main() {
    size_t n;
    std::cin >> n;
    std::vector<Point2D> points(n);

    for (size_t i = 0; i < n; i++) {
        std::cin >> points[i].x >> points[i].y;
    }

    std::cout << std::setprecision(10) << minimum_distance(points) << std::endl;
}