/*
 * Coursera/Algorithms on Strings/Week 2/Problem 1:
 * Construct the Burrows–Wheeler Transform of a String
 * 
 * Author: Ayran Olckers @ The Geekiest One
 * Site: http://ayran.dev
 * Respect Coursera Honor Code
 * Copyright © 2019. All rights reserved
 *
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string BWT(const string& text)
{
    string result = "";

    vector<string> rotations(text.size());

    for (int i = 0; i < text.size(); ++i)
        rotations[i] = text.substr(text.size() - i, string::npos) + text.substr(0, text.size() - i);

    std::sort(rotations.begin(), rotations.end());

    for (auto& s : rotations)
        result += s.back();

    return result;
}

int main()
{
    string text;
    cin >> text;
    cout << BWT(text) << endl;
    return 0;
}