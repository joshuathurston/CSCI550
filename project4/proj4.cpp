/*
 *@author Joshua D. Thurston
 *@date 11/8/17
 *@brief step 0 and 1 of Suffix Array Induced Sort (SAIS)
 */

#include <iostream>
#include <sstream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::getline;
using std::ostringstream;

/*
 *@brief recursive suffix array induced sort
 *@param[T] LMS Substring
 *@param[SA] Suffix Array
 *@param[alphabetSize] Number of characters in the alphabet
 */
void SAIS(vector<int> &T, vector<int> &SA, int alphabetSize)
{
  vector<int> A;
  vector<int> B;
  vector<int> BOriginal;
  vector<int> C;
  vector<bool> t;
  A.push_back(1);
  B.push_back(0);
  C.push_back(0);
  vector<int> count;
  count.resize(alphabetSize);

  for(unsigned int i = 0; i < T.size(); i++)
  {
    count[T[i]] += 1;
  }
  for(unsigned int i = 1; i < count.size(); i++)
  {
    if(count[i] >= 1)
    {
      A.push_back(count[i]);
      C.push_back(B[B.size()-1]+1);
      B.push_back(B[B.size()-1]+count[i]);
    }
  }
  BOriginal = B;

  t.resize(T.size());
  SA.resize(T.size(), -1);
  t[t.size()-1] = 1;
  for(int i = T.size()-1; i > -1; i--)
  {
    if(i+1 <= (signed)T.size()-1)
    {
      if(T[i] < T[i+1])
        t[i] = 1;
      else if(T[i] > T[i+1])
        t[i] = 0;
      else if(T[i] == T[i+1])
        t[i] = t[i+1];
      
      //scan 1 t for SA "if LMS"
      if(t[i] == 0 && t[i+1] == 1)
      {
        SA[B[T[i+1]]] = i+1;
        B[T[i+1]] -= 1;
      }
    }
  }
  B = BOriginal;
  //scan 2 SA for SA "left to right L type"
  for(unsigned int i = 0; i < SA.size(); i++)
  {
    if(SA[i] != -1)
    {
      if(SA[i] > 0)
      {
        if(t[SA[i]-1] == 0)
        {
          SA[C[T[SA[i]-1]]] = SA[i]-1;
          C[T[SA[i]-1]] += 1;
        }
      }
    }
  }

  //scan 3 SA for SA

  for(int i = SA.size()-1; i > -1; i--)
  {
    if(SA[i] != -1)
    {
      if(SA[i] > 0)
      {
        if(t[SA[i]-1] == 1)
        {
          SA[B[T[SA[i]-1]]] = SA[i]-1;
          B[T[SA[i]-1]] -= 1;
        }
      }
    }
  }
}

/*
 *@brief main driver of the program and taking in and converting string to simple names
 */
int main()
{
  string T;
  ostringstream ss;
  int counter=1;

  vector<int> count;
  count.resize(256, 0);
  vector<int> newName;
  newName.resize(256, 0);
  vector<int> TRep;
  vector<int> SA;

  while(getline(cin, T))
    ss << T;
  T = ss.str();

  //scan T
  for(unsigned int i = 0; i < T.size(); i++)
    count[(int)T[i]] = count[(int)T[i]] + 1;
  //scan count
  for(unsigned int i = 1; i < count.size(); i++)
  {
    if(count[i] >= 1)
    {
      newName[i] += counter;
      counter++;
    }
  }
  //scan T for TRep
  for(unsigned int i = 0; i < T.size(); i++)
    TRep.push_back(newName[T[i]]);
  TRep.push_back(0);

  SAIS(TRep, SA, newName.size());

  for(unsigned int i = 0; i < SA.size(); i++)
    cout << SA[i] << " ";
  cout << std::endl;
  return 0;
}
