#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int main()
{
  int length, price;
  vector<int> prices;
  cin >> length;
  cout << length;
  for(int i = 0; i < length; i++)
  {
    cin >> price;
    prices.push_back(price);
  }
}
