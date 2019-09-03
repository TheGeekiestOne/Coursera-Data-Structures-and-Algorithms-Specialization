#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

////////////////////////////////////////////////////////////////////////////////
// Created By Ayran Olckers
//
//
// Reversi
////////////////////////////////////////////////////////////////////////////////

using std::string;
using std::vector;

int edit_distance(const string &str1, const string &str2) {
    vector<vector<int> > dp (str1.size() + 1 , vector<int>(str2.size() + 1));

    for (int i = 0; i <= str1.size(); ++i)
    {
        for (int j = 0; j <= str2.size(); ++j)
        {
        if (i == 0)
            dp[i][j] = j;

        else if (j == 0)
            dp[i][j] = i;

        else if (str1[i - 1] == str2[j - 1])
            dp[i][j] = dp[i-1][j-1];

        else
            dp[i][j] = 1 + std::min(std::min(dp[i][j - 1] , dp[i - 1][j]), dp[i - 1][j - 1]);
        }
    }
    return dp[str1.size()][str2.size()];
}

int main() {
    string str1;
    string str2;
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;
    return 0;
}
