#include <iostream>
#include <vector>

using namespace std;

void printString(vector<int> B, vector<int> A, int indexA)
{
  if(indexA != B[indexA])
    printString(B, A, B[indexA]);
  cout << A[indexA] << " ";
}

int main()
{
  vector<int> A = { 7, 4, 2, 6, 3, 5, 1, 10, 8, 13, 9, 11, 4 };
  vector<int> Length = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
  vector<int> Backtracking = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  
  for(int i = 1; i < A.size(); i++)
  {
    for(int j = 0; j < i; j++)
    {
      if(A[i] > A[j] && Length[i] <= Length[j])
      {
        Length[i]++;
        Backtracking[i] = j;
      }
    }
  }
  int greatest = 0;
  for(int i = 0; i < Length.size(); i++)
    if(Length[i] > Length[greatest])
      greatest = Length[i];
  cout<< greatest << " " << endl;      
  printString(Backtracking, A, 11);
  return 0;
}
