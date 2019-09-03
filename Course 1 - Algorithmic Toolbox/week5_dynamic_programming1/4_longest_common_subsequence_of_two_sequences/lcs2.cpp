#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>

////////////////////////////////////////////////////////////////////////////////
// Created By Ayran Olckers
//
//
// Reversi
////////////////////////////////////////////////////////////////////////////////

using std::vector;
using std::string;

int lcs(vector<int> &X, vector<int> &Y)
{
    int m = X.size();
    int n = Y.size();

    vector<vector<int> >L(m + 1 , vector<int>(n + 1 , 0));
    int i, j;

    for (i=0; i<=m; i++)
    {
        for (j=0; j<=n; j++)
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;

            else if (X[i-1] == Y[j-1])
                L[i][j] = L[i-1][j-1] + 1;

            else
                L[i][j] = std::max(L[i-1][j], L[i][j-1]);
        }
    }

    return L[m][n];
}

int main()
{
    int m;
    std::cin >> m;

    vector<int> X(m);
    for (int i = 0; i < m; ++i)
    {
        std::cin >> X[i];
    }

    int n;
    std::cin >> n;

    vector<int> Y(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> Y[i];
    }

    std::cout << lcs(X, Y) << std::endl;

    return 0;
}
