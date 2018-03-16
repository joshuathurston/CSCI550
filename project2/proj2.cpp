/*Author: Joshua David Edward Thurston
 *Date: 9/16/2017
 *Brief: Project 2
 */

#include <iostream>
#include <stdio.h>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;

enum Vstate{WHITE, GRAY, BLACK};

vector<int> parent;
vector<int> last;
vector<int> first;

void DFSVisit(vector< vector< pair<int, int> > > &graph, int u, vector<Vstate> &states)
{
  states[u] = GRAY;
  for(unsigned int i = 0; i < graph[u].size(); i++)
    if(states[graph[u][i].first] == WHITE)
    {
      parent[graph[u][i].first] = u;
      DFSVisit(graph, graph[u][i].first, states);
    }
    else if(states[u] == GRAY && parent[u] != graph[u][i].first)
    {
      last.push_back(u);
      first.push_back(graph[u][i].first);
    }

  states[u] = BLACK;
}

int main(int argc, char* argv[])
{
  vector< vector< pair<int, int> > > G;
  vector<Vstate> states;
  pair<int, int> edgeToRemove;
  int N, M, a, b, w, A, B, C, D, w_1, w_2, c_1, c_2;
  int maxWeight;
  int current;
  int years = 10;
  int sum;
  //  get input  //
  cin >> N;
  //  RedNova Graph Prep  //
  for(int i = 0; i < N; i++)
  {
    vector<pair<int, int> > weightedAdjList;
    G.push_back(weightedAdjList);
  }
  for(int i = 0; i < N-1; i++)
  {
    cin >> a >> b >> w;
    sum += w*years;
    G[a].push_back({b, w*years});
    G[b].push_back({a, w*years});
  }
  cin >> M;
  G.resize(N+M);
  //  StarTrace Graph Prep
  for(int i = 0; i < M; i++)
  {
    vector<pair<int, int> > weightedAdjList;
    G.push_back(weightedAdjList);
  }
  for(int i = 0; i < M-1; i++)
  {
    cin >> a >> b >> w;
    sum += w*years;
    G[a+N].push_back({b+N, w*years});
    G[b+N].push_back({a+N, w*years});
  }

  //  Parent and States Prep for DFS  //
  for(int i = 0; i < N+M; i++)
  {
    parent.push_back(-1);
    states.push_back(WHITE);
  }

  cin >> A >> C >> w_1 >> c_1;
  cin >> B >> D >> w_2 >> c_2;

  sum += (w_1*years)+c_1;
  sum += (w_2*years)+c_2;

  G[A].push_back({C+N, (w_1*years)+c_1});
  G[C+N].push_back({A, (w_1*years)+c_1});
  G[B].push_back({D+N, (w_2*years)+c_2});
  G[D+N].push_back({B, (w_2*years)+c_2});

  //  Run DFS  //
  DFSVisit(G, 0, states);
  current = last[0];

  //  check first vertex in the parent path  //
  for(unsigned int i = 0; i < G[first[0]].size(); i++)
  {
    //  Checking adj. List for last[0] //
    if(G[first[0]][i].first == last[0])
    {
      maxWeight = G[current][i].second;
      edgeToRemove = {first[0], last[0]};
    }
  }
  //  check the rest of the parent path  //
  while(current != first[0])
  {
    for(unsigned int i = 0; i < G[current].size(); i++)
    {
      //  checking adj. List  //
      if(G[current][i].first == parent[current])
      {
        if(maxWeight < G[current][i].second)
        {
          maxWeight = G[current][i].second;
          edgeToRemove = {current, G[current][i].first};
        }
      }
    }  
    current = parent[current];
  }

//  User output  //
  if((edgeToRemove.first == A && edgeToRemove.second == C+N) || (edgeToRemove.first == C+N && edgeToRemove.second == A))
    printf("%i %i %i\n", B, D, sum-maxWeight);
  else if((edgeToRemove.first == B && edgeToRemove.second == D+N) || (edgeToRemove.first == D+N && edgeToRemove.second == B))
    printf("%i %i %i\n", A, C, sum-maxWeight);
  else
    if(edgeToRemove.first > N)
    {
      if(edgeToRemove.second-N < edgeToRemove.first-N)
        printf("%i %i %i %i\n", edgeToRemove.second-N, edgeToRemove.first-N, 2, sum-maxWeight);
      else
        printf("%i %i %i %i\n", edgeToRemove.first-N, edgeToRemove.second-N, 2, sum-maxWeight);
    }
    else
    {
      if(edgeToRemove.second < edgeToRemove.first)
        printf("%i %i %i %i\n", edgeToRemove.second, edgeToRemove.first, 1, sum-maxWeight);
      else
        printf("%i %i %i %i\n", edgeToRemove.first, edgeToRemove.second, 1, sum-maxWeight);
    }
  return 0;
}
