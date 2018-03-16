/*Author: Joshua David Edward Thurston
 *Date: 9/19/2017
 */

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;

int totalWeight;
pair<int, int> removed;

class disjointSet
{
  public:
    disjointSet(int numberOfNodes);
    int find(int x);
    void merge(int x, int y);
  
  private:
    vector<int> rank;
    vector<int> parent;
    int nodes;
};

disjointSet::disjointSet(int numberOfNodes)
{
  nodes = numberOfNodes;
  //  Make-Set all V  //
  for(int i = 0; i < nodes; i++)
  {
    parent.push_back(i);
    rank.push_back(0);
  }
}

int disjointSet::find(int x)
{
  if(x != parent[x])
    parent[x] = find(parent[x]);
  return parent[x];
}

void disjointSet::merge(int x, int y)
{
  if(rank[x] > rank[y])
    parent[y] = x;
  else if(rank[x] < rank[y])
    parent[y] = x;
  else
  {
    parent[x] = y;
    rank[y] = rank[y] + 1;
  }
}

vector<pair<int, int> > kruskal(vector< pair<int, pair<int, int> > > G)
{
  totalWeight = 0;
  vector<pair<int, int> > mst;
  int rep_u, rep_v;
  // Make set is part of disjoint set constructor
  std::sort(G.begin(), G.end());
  disjointSet ds(G.size());
  for(unsigned i = 0; i < G.size(); i++)
  {
    rep_u = ds.find(G[i].second.first);
    rep_v = ds.find(G[i].second.second);

    if(rep_u != rep_v)
    {
      mst.push_back({G[i].second.first, G[i].second.second});
      totalWeight += G[i].first;
      ds.merge(rep_u, rep_v);
    }
    else
      removed = {G[i].second.first, G[i].second.second};
  }
  return mst;
}

int main(int argc, char* argv[])
{
  vector< pair<int, pair<int, int> > > WeightCombined;
  vector< pair<int , int> > MST;
  int N, M, a, b, w, A, B, C, D, w_1, w_2, c_1, c_2;
  int years = 10;
  bool case1 = false;
  bool case2 = false;
  bool case3 = false;

  cin >> N;
  for(int i = 0; i < N-1; i++)
  {
    cin >> a >> b >> w;
    WeightCombined.push_back({(w*years), {a, b}});
  }
  cin >> M;
  for(int i = 0; i < M-1; i++)
  {
    cin >> a >> b >> w;
    WeightCombined.push_back({(w*years), {a+N, b+N}});
  }
  cin >> A >> C >> w_1 >> c_1 >> B >> D >> w_2 >> c_2;
  WeightCombined.push_back({w_1*years+c_1, {A, C+N}});
  WeightCombined.push_back({w_2*years+c_2, {B, D+N}});

  MST = kruskal(WeightCombined);

  for(unsigned int i = 0; i < MST.size(); i++)
  {
    if((MST[i].first == A && MST[i].second == C+N) || (MST[i].first == C+N && MST[i].second == A))
      case1 = true;
    if((MST[i].first == B && MST[i].second == D+N) || (MST[i].first == D+N && MST[i].second == B))
      case2 = true;
    if(case1 && case2)
      case3 = true;
  }

  if(case1 && !case3)
    printf("%i %i %i\n", A, C, totalWeight);
  else if(case2 && !case3)
    printf("%i %i %i\n", B, D, totalWeight);
  else if(case3)
  {
    if(removed.first > N)
      printf("%i %i %i %i\n", removed.first-N, removed.second-N, 2, totalWeight);
    else
      printf("%i %i %i %i\n", removed.first, removed.second, 1, totalWeight);
  }
  return 0;
}
