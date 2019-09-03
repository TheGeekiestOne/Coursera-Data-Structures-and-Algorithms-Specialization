#include <iostream>
#include <vector>

using std::vector;
using std::pair;

/*
* Coursera/Advanced Algorithms and Complexity/Week 1/Problem 3(advanced):
* Stock Charts (maximum flow and path cover, etc)
* Author: Ayran Olckers
* Website https://ayran.dev
* Respect Coursera Honor Code
* Copyright © 2019. All rights reserved
*
*/

/*
 * Useful to read: http://mradwan.github.io/algorithms/2014/05/02/flows-cuts-and-matchings/
*/

void explore(int v,vector<vector<int> > &adj,vector<bool> &visited){
  visited[v] = true;
  for(size_t i = 0; i < adj[v].size(); i++){
    // if not visited then explore
    int w = adj[v][i]; // edge (v,w) explore all the w vertices 
    if(!visited[w])
      explore(w, adj, visited);
  }
}

int number_of_components(vector<vector<int> > &adj) {
  vector<bool> visited;
  visited.resize(adj.size());
  int cc = 0;
  for(size_t v = 0; v < adj.size(); v++){
    if(!visited[v]){
      explore(v, adj, visited);
      cc++;
    }
  }
  
  return cc;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    int a = x - 1;
    int b = y - 1;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  std::cout << number_of_components(adj);

}