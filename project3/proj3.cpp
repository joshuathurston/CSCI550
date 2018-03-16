#include <iostream>
#include <vector>

using std::string;
using std::cin;
using std::cout;
using std::vector;

int main()
{
  vector< vector<bool> > P;
  vector<int> C;
  vector<int> B;
  std::string palindrome;

  std::cin >> palindrome;
  for(int i = 0; i < palindrome.size(); i++)
  std::cout << palindrome[i] << std::endl;
  return 0;
}
