/*
* Author: Ayran Olckers
* Website https://ayran.dev
* Respect Coursera Honor Code
* Copyright © 2019. All rights reserved
*
*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <functional>
#include <cmath>

using namespace std;

using Point = pair<long long, long long>;
using Length = long long;
using Edge = pair<long long, int>;
using Adj_List = vector<vector<vector<Edge>>>;
using Distance = vector<vector<Length>>;
using Queue = priority_queue<Edge, vector<Edge>, greater<Edge>>;

Length INF = std::numeric_limits<Length>::max() / 4;

class Graph {
  Adj_List adj;
  Distance dist;
  vector<Point> coords;
  vector<int> visited, visited_r, workset;
  Queue queue, queue_R;
  int t_{0}, s_{0};

  void clear_containers() noexcept;
  Length compute_path() noexcept;
  inline void process(int, Queue&, int) noexcept;
  inline void relax(Queue&, Length, int, int, int) noexcept;

public:
  Graph(int) noexcept;
  void add_edge(int u, int v, int w) noexcept;
  Length bidirectional_Dijkstra(int s, int t) noexcept;
};

Graph::Graph(int n) noexcept:
   adj(Adj_List(2, vector<vector<Edge>>(n, vector<Edge>()))),
   dist(2, vector<Length>(n, INF)),
   visited(vector<int>(n, 0)),
   visited_r(vector<int>(n, 0))
   {};

void Graph::add_edge(int u, int v, int w) noexcept {
 adj[0][u].push_back(Edge(w, v));
 adj[1][v].push_back(Edge(w, u));
}

void Graph::clear_containers() noexcept {
  for(int u = -1; !queue.empty(); queue.pop() ) {
    u = queue.top().second;
    dist[1][u] = dist[0][u] = INF;
    visited[u] = visited_r[u] = 0;
  }

  for(int u = -1; !queue_R.empty(); queue_R.pop() ) {
    u = queue_R.top().second;
    dist[1][u] = dist[0][u] = INF;
    visited[u] = visited_r[u] = 0;
  }

  for(auto u: workset) {
    dist[1][u] = dist[0][u] = INF;
    visited[u] = visited_r[u] = 0;
  }

  workset.clear();
}

void Graph::relax(Queue& queue, Length weight, int v, int u, int side) noexcept {
  if(dist[side][v] > dist[side][u] + weight) {
     dist[side][v] = dist[side][u] + weight;
     queue.push(Edge(dist[side][v], v));
  }
}

void Graph::process(int u, Queue& queue, int side) noexcept {
  queue.pop();
  for(auto &edge: adj[side][u])
     relax(queue, edge.first, edge.second, u, side);
}

Length Graph::compute_path() noexcept {
  Length result = INF;
  for(auto u: workset)
    if(dist[0][u] + dist[1][u] < result)
      result = dist[0][u] + dist[1][u];
  return result == INF ? -1 : result;
}

Length Graph::bidirectional_Dijkstra(int s, int t) noexcept {
  clear_containers();
  s_ = s, t_ = t;

  queue.push(Edge(0, s));
  queue_R.push(Edge(0, t));
  dist[0][s] = dist[1][t] = 0;

  do {
     int u = queue.top().second;
     process(u, queue, 0);
     visited[u]++;
     if(visited_r[u])
       break;
     workset.push_back(u);

     u = queue_R.top().second;
     process(u, queue_R, 1);
     visited_r[u]++;
     if(visited[u])
       break;
     workset.push_back(u);

  } while(!queue.empty() && !queue_R.empty());

  return compute_path();
}

int  main() {
    int  n, m, s, t, q;
    cin >> n >> m;
    Graph g(n);

    for (int  i = 0; i < m; i++) {
        int  x, y, w;
        std::cin >> x >> y >> w;
        g.add_edge(x-1, y-1, w);
    }

    std::cin >> q;
    while(q--)
    {
      std::cin >> s >> t;
      std::cout << g.bidirectional_Dijkstra(--s, --t) << std::endl;
    }
}