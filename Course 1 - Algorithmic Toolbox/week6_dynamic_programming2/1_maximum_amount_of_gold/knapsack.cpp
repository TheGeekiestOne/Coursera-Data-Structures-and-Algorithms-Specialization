#include <iostream>
#include <algorithm>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
// Created By Ayran Olckers
//
//
// Reversi
////////////////////////////////////////////////////////////////////////////////

using std::vector;

bool greater(int a , int b)
{
    return a > b;
}

int optimal_weight(int W, vector<int> &w)
{
    vector<vector<int> >K(w.size() + 1 , vector<int>(W + 1 , 0));

    for (int i = 0; i <= w.size(); ++i)
    {
        for (int j = 0; j <= W; ++j)
        {
            if (i == 0 || j == 0)
                K.at(i).at(j) = 0;
            else if (w[i - 1] <= j)
                K.at(i).at(j) = std::max(K.at(i - 1).at(j) , w[i - 1] + K.at(i - 1).at(j - w[i - 1]));
            else
                K.at(i).at(j) = K.at(i - 1).at(j);
        }
    }
    return K.at(w.size()).at(W);
}

int main()
{
    int n, W;
    std::cin >> W >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> w[i];
    }
    std::sort(w.begin() , w.end() , greater);
    std::cout << optimal_weight(W, w) << '\n';
}
