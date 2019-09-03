#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <bits/stdc++.h>
using namespace std;
using std::vector;

////////////////////////////////////////////////////////////////////////////////
// Created By Ayran Olckers
//
//
// Reversi
////////////////////////////////////////////////////////////////////////////////





bool subsetSum(int S[], int n, int a, int b, int c, auto &lookup)
{

    if (a == 0 && b == 0 && c == 0)
        return true;

    if (n < 0)
        return false;

    string key = to_string(a) + "|" + to_string(b) + "|" + to_string(c) + "|" + to_string(n);

    if (lookup.find(key) == lookup.end())
    {

        bool A = false;
        if (a - S[n] >= 0)
            A = subsetSum(S, n - 1, a - S[n], b, c, lookup);

        bool B = false;
        if (!A && (b - S[n] >= 0))
            B = subsetSum(S, n - 1, a, b - S[n], c, lookup);

        bool C = false;
        if ((!A && !B) && (c - S[n] >= 0))
            C = subsetSum(S, n - 1, a, b, c - S[n], lookup);

        lookup[key] = A || B || C;
    }

    return lookup[key];
}

bool partition(int S[], int n)
{
    if (n < 3)
        return false;

    unordered_map<string, bool> lookup;

    int sum = accumulate(S, S + n, 0);

    return !(sum % 3) && subsetSum(S, n - 1, sum/3, sum/3, sum/3, lookup);
}

int main()
{
    int n =0;
    cin>>n ;
    int S[n];
    for(int i=0;i<n;i++){
    	cin>>S[i];
    }

    if (partition(S, n))
        cout << "1";
    else
        cout << "0";

    return 0;
}
