/*
 *@author Joshua D. Thurston
 *@date 11/16/17
 *@brief Suffix Array Induced Sort (SAIS) Printing bwt
 */

#include <iostream>
#include <sstream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::getline;
using std::ostringstream;

/*
 *@brief Checks to see if two LMS substrings are the same
 *@param[T] vector containing Whole string
 *@param[t] vector containing l/s type of whole string
 *@param[previous] starting index of previous LMS substring within T
 *@param[current] starting index of current LMS substring within T
 *@return True if previous and current are the same and false if not
 */
bool isSameLMS(const vector<int> &T, vector<bool> &t, int previous, int current)
{
  //compare two lms substrings if the same return true else return false
  int i = 0;
  int j = 0;
  while(i == j)
  {
    //if comparing to dollar
    if(T[current] == 0 || T[previous] == 0)
      return false;
    else
    {
      //if current and previous are same character and type
      if(t[current+i] == t[previous+j] && T[current+i] == T[previous+j])
      {
        //if both are LMS
        if(t[current+i-1] == 0 && t[current+i] == 1 && t[previous+j-1] == 0 && t[previous+j] == 1 && i > 0 && j > 0){
//          for(int z = 0; z < i+1; z++)
//            cout << T[current+z] << " ";
//          cout << " "; 
//          for(int z = 0; z < j+1; z++)
//            cout << T[previous+z] << " ";
//          cout << endl;
          return true;
        }
        //if current is not an LMS
        if(!(t[current+i-1] == 0 && t[current+i] == 1) || i == 0)
          i++;
        //if previous is not an LMS
        if(!(t[previous+j-1] == 0 && t[previous+j] == 1) || j == 0)
          j++;
      }
      else
        return false;
    }
  }
  return false;
}

/*
 *@brief recursive suffix array induced sort
 *@param[T] LMS Substring
 *@param[SA] Suffix Array
 *@param[alphabetSize] Number of characters in the alphabet
 */
void SAIS(vector<int> &T, vector<int> &SA, int alphabetSize)
{
  if((signed)T.size() == alphabetSize)
  {
    for(unsigned int i = 0; i < T.size(); i++)
    {
      SA[T[i]] = i;
    }
    return;
  }

  int x = 0;
  int previous = 0;
  int nameCounter = -1;
  vector<int> A;
  vector<int> B;
  vector<int> BOriginal;
  vector<int> C;
  vector<int> COriginal;
  vector<int> N;
  vector<int> T1;
  vector<int> R;
  vector<int> SA1;
  vector<bool> L;
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
  COriginal = C;

  t.resize(T.size());
  SA.resize(T.size(), -1);
  L.resize(SA.size());
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
  C = COriginal;
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
        //checking for LMS for L vector
        //if SA[i] is S type
        if(t[SA[i]] == 1)
        {
          //if SA[i]-1 is L type then LMS
          if(t[SA[i]-1] == 0)
          {
	    L[i] = 1;
          }
        }
      }
    }
  }

  N.resize(T.size(), -1);
  N[N.size()-1] = 0;
  previous = SA[0];
  for(unsigned int i = 0; i < SA.size(); i++)
  {
    if(L[i] == 1)
    {
      if(isSameLMS(T, t, previous, SA[i])){
        N[SA[i]]=nameCounter;
         
      }
      else
      {
        nameCounter++;
        N[SA[i]]=nameCounter;
      }
      previous = SA[i];
    }
  }
//  for(int i = 0; i < N.size(); i++)
//    cout << N[i] << endl;
  for(unsigned int i = 0; i < N.size(); i++)
  {
    if(N[i] >= 0)
    {
      T1.push_back(N[i]);
      R.push_back(i);
    }
  }

  SA1.resize(T1.size(), -1);
  //cout << x+1 << endl << endl;
//  SAIS(T1, SA1, x+1);
  SAIS(T1, SA1, nameCounter+1);
  B = BOriginal;
  for(unsigned int i = 0; i < SA.size(); i++)
    SA[i] = -1;

  //step 4
  for(int i = SA1.size()-1; i > -1; i--)
  {
    SA[B[T[R[SA1[i]]]]] = R[SA1[i]];
    B[T[R[SA1[i]]]]--;
  }
  B = BOriginal;
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
  {
    if(SA[i]-1 != -1)
      cout << T[SA[i]-1];
  }
  cout << endl;
  return 0;
}
