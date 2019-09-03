
/*
* Author: Ayran Olckers
* Website https://ayran.dev
* Respect Coursera Honor Code
* Copyright © 2019. All rights reserved
* - optional/Tasks 3-4 - contraction hierarchies (small and large road networks)
*
*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <functional>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Graph
using Length = int;
using Edge = pair<int, int>;
using Distance = vector<vector<Length>>;
using Queue = priority_queue<Edge, vector<Edge>, greater<Edge>>;
using AdjacencyList = vector<vector<vector<pair<int, int>>>>;

// ContractionHierarchies
using ImportanceNode = pair<int, int>;
using ImportanceQueue = priority_queue<ImportanceNode, vector<ImportanceNode>, greater<ImportanceNode>>;

Length INF = std::numeric_limits<Length>::max() / 2;

struct Graph {
  AdjacencyList adj;
  Distance dist;
  vector<vector<bool>> visited;
  vector<int> min_outgoing, max_outgoing, max_incoming, workset;
  Queue queue, queue_R;

  Graph(int);
  void reset_containers();
  void add_edge(int, int, int);
  void process(int, Queue&, int);
  void relax(Queue&, Length, int, int, int);
  Length get_shortest_dist(int, int);
};

Graph::Graph(int n):
   adj(AdjacencyList(2, vector<vector<pair<int, int>>>(n, vector<pair<int, int>> ()))),
   dist(2, vector<Length>(n, INF)),
   visited(2, vector<bool>(n, false)),
   min_outgoing(n, INF),
   max_outgoing(n, 0),
   max_incoming(n, 0)
   {}

inline void Graph::add_edge(int u, int v, int w)
{
  adj[0][u].push_back(Edge(w, v));
  adj[1][v].push_back(Edge(w, u));

 if(max_outgoing[u] < w)
    max_outgoing[u] = w;

 if(max_incoming[v] < w)
    max_incoming[v] = w;

 if(min_outgoing[u] > w)
    min_outgoing[u] = w;
}

void Graph::reset_containers()
{
  for(auto v : workset)
  {
      dist[0][v] = dist[1][v] = INF;
      visited[0][v] = visited[1][v] = false;
  }
  workset.clear();
}

inline void Graph::relax(Queue& queue, Length weight, int v, int u, int side)
{
  if(dist[side][v] > dist[side][u] + weight)
  {
     dist[side][v] = dist[side][u] + weight;
     queue.push(Edge(dist[side][v], v));
     workset.push_back(v);
  }
}

inline void Graph::process(int u, Queue& queue, int side)
{
  for(auto edge: adj[side][u])
     relax(queue, edge.first, edge.second, u, side);
}

Length Graph::get_shortest_dist(int s, int t)  {
  reset_containers();

  Length estimate = INF;

  queue.push(Edge(0, s));
  queue_R.push(Edge(0, t));

  dist[0][s] = dist[1][t] = 0;

  workset.push_back(s);
  workset.push_back(t);

  bool need_process{true};

  while(!queue.empty() || !queue_R.empty())
  {

    if(!queue.empty())
    {
       int u = queue.top().second;
       queue.pop();

       need_process = true;

       for(auto pred : adj[1][u])
       {
           if (dist[0][pred.second] + pred.first < dist[0][u])
           {
               dist[0][u] = dist[0][pred.second] + pred.first + 1;
               need_process = false;
               break;
           }
       }

       if(need_process && dist[0][u] <= estimate)
         process(u, queue, 0);

       visited[0][u] = true;

       if(visited[1][u] && dist[0][u] + dist[1][u] < estimate)
          estimate = dist[0][u] + dist[1][u];
     }

     if(!queue_R.empty())
     {
       int u = queue_R.top().second;
       queue_R.pop();

       need_process = true;

       for(auto pred : adj[0][u])
       {
           if (dist[1][pred.second] + pred.first < dist[1][u])
           {
               dist[1][u] = dist[1][pred.second] + pred.first + 1;
               need_process = false;
               break;
           }
       }

       if(need_process && dist[1][u] <= estimate)
         process(u, queue_R, 1);

       visited[1][u] = true;

       if(visited[0][u] && dist[0][u] + dist[1][u] < estimate)
         estimate = dist[0][u] + dist[1][u];
     }
  }

  return  estimate == INF ? -1 : estimate;
}

struct ContractionHierarchies {

    struct Shortcut {
        int to;
        int from;
        Length dist;
        Shortcut(int f, int t, Length d): from(f),  to(t), dist(d) {}
    };

    bool is_adding_shortcuts{false};
    int  contract_node_importance{0};
    int  n;

    vector<int> rank, node_level, settled_vertices;
    vector<Shortcut> shortcuts;

    Graph& G;
    ImportanceQueue importanceQueue;
    vector<Length> dist;

    ContractionHierarchies(Graph& graph):
      G(graph), n(graph.adj[0].size()), dist(vector<Length>(n, INF)), rank(n, INF), node_level(n, 0)
      {}

    void initialize_nodes_queue();
    void witness_search(int, int, int);
    void contract_node(int);
    void remove_edges();
    void preprocess_graph();
    void update_neighbors_node_level(int);
    int  sum_contracted_neighbors_and_node_level(int);

};

void ContractionHierarchies::update_neighbors_node_level(int v)
{
    auto & outgoing_edges = G.adj[0][v];
    auto & incoming_edges = G.adj[1][v];

    int current_v_level = node_level[v] + 1;

    for(auto neighbor: outgoing_edges) {
        if(node_level[neighbor.second] < current_v_level)
          node_level[neighbor.second] = current_v_level;
    }

    for(auto neighbor: incoming_edges) {
        if(node_level[neighbor.second] < current_v_level)
          node_level[neighbor.second] = current_v_level;
    }
}

int ContractionHierarchies::sum_contracted_neighbors_and_node_level(int v)
{
    int num{0};
    int level{0};

    auto & outgoing_edges = G.adj[0][v];
    auto & incoming_edges = G.adj[1][v];

    for(auto neighbor: outgoing_edges)
    {
        if(rank[neighbor.second] != INF)
        {
            ++num;
            if(node_level[neighbor.second] > level)
                level = node_level[neighbor.second];
        }
    }

    for(auto neighbor: incoming_edges)
    {
        if(rank[neighbor.second] != INF)
        {
            ++num;
            if(node_level[neighbor.second] > level)
                level = node_level[neighbor.second];
        }
    }

    return num + level + 1;
}

void ContractionHierarchies::witness_search(int source, int v, int limit)
{
  Queue queue;
  queue.push(Edge(0, source));
  settled_vertices.push_back(source);

  dist[source] = 0;

  int hops = 5;

  while(hops-- && !queue.empty())
  {
    int u = queue.top().second;
    queue.pop();

    if(limit < dist[u])
       break;

    auto & outgoing_edges = G.adj[0][u];

    for(auto w: outgoing_edges)
    {

       if(rank[w.second] < rank[v] || w.second == v)
         continue;

        if(dist[w.second] > dist[u] + w.first)
        {
            dist[w.second] = dist[u] + w.first;
            queue.push(Edge(dist[w.second], w.second));
            settled_vertices.push_back(w.second);
        }
    }
  }
}

void ContractionHierarchies::contract_node(int v)
{
  shortcuts.clear();

  int added_shortcuts{0};
  int shortcut_cover{0};

  auto &outgoing_edges = G.adj[0][v];
  auto &incoming_edges = G.adj[1][v];

  for(auto u: incoming_edges)
  {
     if(rank[u.second] < rank[v] || outgoing_edges.empty())
          continue;

     witness_search(u.second, v, G.max_incoming[v] + G.max_outgoing[v]);// - G.min_outgoing[v]);

     bool at_least_one_shortcut{false};

     for(auto w: outgoing_edges)
     {
       if(rank[w.second] < rank[v])
         continue;

       bool is_shortcut_needed{true};

       for(auto x: G.adj[1][w.second])
       {
         if(rank[x.second] < rank[v] || x.second == v)
            continue;

         if(u.first + w.first >= dist[x.second] + x.first)
         {
            is_shortcut_needed = false;
            break;
         }
       }

       if(is_shortcut_needed)
       {
         ++added_shortcuts;
         at_least_one_shortcut = true;

         if(is_adding_shortcuts)
           shortcuts.emplace_back(Shortcut(u.second, w.second, u.first + w.first));
       }
    }

    if(at_least_one_shortcut)
      ++shortcut_cover;

    for(auto x: settled_vertices)
      dist[x] = INF;

    settled_vertices.clear();
  }

  contract_node_importance =   added_shortcuts - outgoing_edges.size() - incoming_edges.size()
                               + shortcut_cover + sum_contracted_neighbors_and_node_level(v);
}

void ContractionHierarchies::remove_edges()
{
   for(int i = 0; i < G.adj[0].size(); ++i)
   {
     for(int j = 0; j < G.adj[0][i].size(); ++j)
       if(rank[i] > rank[G.adj[0][i][j].second])
          G.adj[0][i].erase(G.adj[0][i].begin() + j--);

     for(int j = 0; j < G.adj[1][i].size(); ++j)
       if(rank[i] > rank[G.adj[1][i][j].second])
          G.adj[1][i].erase(G.adj[1][i].begin() + j--);
   }
}

void ContractionHierarchies::initialize_nodes_queue()
{
  for(int v = 0; v < G.adj[0].size(); ++v)
  {
    contract_node(v);
    importanceQueue.push(ImportanceNode(contract_node_importance, v));
  }
}

void ContractionHierarchies::preprocess_graph()
{
   initialize_nodes_queue();
   is_adding_shortcuts = true;

   for(int i = 0; importanceQueue.size(); ++i)
   {
      int v = importanceQueue.top().second;
              importanceQueue.pop();

      contract_node(v);

      if(importanceQueue.empty() || contract_node_importance <=importanceQueue.top().first)
      {
         for(auto &shortcut: shortcuts)
           G.add_edge(shortcut.from, shortcut.to, shortcut.dist);

         update_neighbors_node_level(v);
         rank[v] = i;
      }
      else
      {
         importanceQueue.push(ImportanceNode(contract_node_importance, v));
      }

   }

   remove_edges();
}

int  main() {
  int  n, m, s, t, q;
  cin >> n >> m;
  Graph g(n);

  for (int  i = 0; i < m; i++)
  {
      int  x, y, w;
      std::cin >> x >> y >> w;
      g.add_edge(x-1, y-1, w);
  }

 // high_resolution_clock::time_point t1 = high_resolution_clock::now();

  ContractionHierarchies ch(g);
  ch.preprocess_graph();

 // high_resolution_clock::time_point t2 = high_resolution_clock::now();

  std::cout << "Ready" << std::endl;

 // std::cout << std::endl << "It took me " << (duration_cast<duration<double>>(t2 - t1)).count() << " seconds for preprocessing" << std::endl;

  std::cin >> q;
  while(q--)
  {
    std::cin >> s >> t;
    std::cout << g.get_shortest_dist(s-1, t-1) << std::endl;
  }

  return 0;
}