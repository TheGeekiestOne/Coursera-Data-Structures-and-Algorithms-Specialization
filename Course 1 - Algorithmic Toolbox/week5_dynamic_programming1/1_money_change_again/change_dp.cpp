// Recursive C program for
// coin change problem.
#include <iostream>
#include <vector>
#include <climits>

////////////////////////////////////////////////////////////////////////////////
// Created By Ayran Olckers
//
//
// Reversi
////////////////////////////////////////////////////////////////////////////////

using std::vector;
vector<int> coins = {1 , 3 , 4};

int get_change(int m)
{

  std::vector<int> table(m + 1);

  table[0] = 0;

  for (int i = 1; i <= m; ++i)
    table[i] = INT_MAX;

  for (int i = 1; i <= m; ++i)
  {
    for (int j = 0; j < m; ++j)
    {
      if (coins[j] <= i)
      {
        int sub_res = table[i - coins[j]];
        if (sub_res != INT_MAX && sub_res + 1 < table[i])
          table[i] = sub_res + 1;
      }
    }
  }
  return table[m];
}

int main()
{
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
