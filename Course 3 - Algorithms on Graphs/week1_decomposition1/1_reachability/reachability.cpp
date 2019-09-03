#include <iostream>
#include <vector>

/*
* Author: Ayran Olckers
* Website https://ayran.dev
* Respect Coursera Honor Code
* Copyright © 2019. All rights reserved
*
*/

using std::vector;
using std::pair;


void explore(int v,vector<vector<int> > &adj,vector<bool> &visited){
  visited[v] = true;
  for(size_t i = 0; i < adj[v].size(); i++){
    // if not visited then explore
    int w = adj[v][i]; // edge (v,w) explore all the w vertices 
    if(!visited[w])
      explore(w, adj, visited);
  }
}

int reach(vector<vector<int> > &adj, int x, int y) {
  vector<bool> visited;
  visited.resize(adj.size());
  // just explore x and see if you visit y along the way
  explore(x, adj, visited);
  if(visited[x] && visited[y])// if both visited then you are good to go
    return 1;
  
  return 0;
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
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}