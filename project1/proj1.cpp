/*Author: Joshua David Edward Thurston
 *Date: 9/5/2017
 */

#include <iostream>
#include <stdio.h>
#include <vector>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::min;

enum Vstate{WHITE, GRAY, BLACK};
int t, DFSCount;
vector<int> disc; 
vector<int> fini; 
vector<int> lows;
vector<int> parent;
vector<int> ID;

void DFSVisit(vector< vector<int> > &graph, int u, vector<Vstate> &states)
{
  t += 1;
  disc[u] = t;
  lows[u] = t;
  states[u] = GRAY;
  for(unsigned int i = 0; i < graph[u].size(); i++)
  {
    if(states[graph[u][i]] == WHITE)
    {
      parent[graph[u][i]] = u;
      DFSVisit(graph, graph[u][i], states);
      lows[u] = min(lows[u], lows[graph[u][i]]);
    }
    else
    {
      if(graph[u][i] != parent[u])
      {
        lows[u] = min(lows[u], lows[graph[u][i]]);
      }
    }
  }
  states[u] = BLACK;
  t += 1;
  ID[u] = DFSCount;
  fini[u] = t;
  for(unsigned int j = 0; j < graph[u].size(); j++)
  {
    if(graph[u][j] != parent[u])
      min(disc[u], lows[u]);
  }

}

void DFS(vector< vector<int> > &graph, int N)
{
  vector<Vstate> states;
  t = 0;
  DFSCount = 0;
  disc.clear();
  fini.clear();
  lows.clear();
  parent.clear();
  ID.clear();
  for(int i = 0; i < N; i++)
  {
    states.push_back(WHITE);
    disc.push_back(0);
    fini.push_back(0);
    lows.push_back(0);
    ID.push_back(-1);
    parent.push_back(-1);
  }
  for(int i = 0; i < N; i++)
  {
    if(states[i] == WHITE)
    {
      DFSVisit(graph, i, states);
      DFSCount += 1;
    }
  }
}

int main(int argc, char* argv[])
{
  int N, M;
  int v, n;

  vector< vector<int> > graph;
  vector< vector<int> > graph_BCC;
  vector< vector<int> > graph_B;
  vector< vector<int> > graph_H;

  cin >> N >> M;
  if(N <= 0)
  {
    cerr << "ERROR: graph is empty.";
    return 1;
  }
  for(int i = 0; i < N; i++)
  {
    vector<int> adjList; 
    graph.push_back(adjList);
    graph_B.push_back(adjList);
    graph_BCC.push_back(adjList);
  }
  for(int i = 0; i < M; i++)
  {
    cin >> v >> n;
    int newEdge = n;
    graph[v].push_back(newEdge);
    
    //because it is an undirected graph we have to add reverse edge
    int reverseEdge = v;
    graph[n].push_back(reverseEdge);
  }
  
  DFS(graph, N);
  graph_BCC = graph;
  //looping through and building bridge BCC graph
  for(int i = 0; i < N; i++)
  {
    if(disc[i] == lows[i] && parent[i] != -1)
    {
      graph_B[parent[i]].push_back(i);
      graph_B[i].push_back(parent[i]);

      for(unsigned int j = 0; j < graph_BCC[i].size(); j++)
      {
        if(graph_BCC[i][j] == parent[i])
          graph_BCC[i].erase(graph_BCC[i].begin()+j);
      }
      for(unsigned int j = 0; j < graph_BCC[parent[i]].size(); j++)
      {
        if(graph_BCC[parent[i]][j] == i)
          graph_BCC[parent[i]].erase(graph_BCC[parent[i]].begin()+j);
      }
    }
  }
  DFS(graph_BCC, N);
  int largest = 0;
  for(unsigned int i = 0; i < ID.size(); i++)
  {
    if(largest < ID[i])
      largest = ID[i];
  }
  for(int i = 0; i < largest + 1; i++)
  {
     vector<int> adjListH;
     graph_H.push_back(adjListH);
  }
  for(unsigned int i = 0; i < graph_B.size();i++)
  {
    for(unsigned int j = 0; j < graph_B[i].size();j++)
      graph_H[ID[i]].push_back(ID[graph_B[i][j]]);
  }
  int leaves = 0;
  for(unsigned int i = 0; i < graph_H.size(); i++)
  {
    if(graph_H[i].size() == 1)
      leaves += 1;
  }
  if(leaves%2 > 0)
    leaves += 1;
  cout << leaves/2 << endl;
  for(int i = 0; i < lows.size(); i++)
    printf("%i:%i\n",i,  lows[i]);
  return 0;
}
