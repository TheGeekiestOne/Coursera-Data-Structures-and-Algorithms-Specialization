#include <iostream>
#include <vector>
#include <algorithm>


/*********************************
******                      ******
***        Ayran Olckers       ***
**           week 1             **
**           06/2019            **
******                      ******
**********************************/

//Getting an interger overflow, so will need to use a long long

/*Maximum Pairwise Product Problem
Find the maximum product of two distinct numbers in a sequence of non-negative integers.

Input: A sequence of non-negative integers.

Output: The maximum value thatcan be obtained by multiplying
two different elements from the sequence.*/

using namespace std;

long long MaxPairwiseProduct(const vector<int>& numbers) {
    long long max_product = 0;
    int n = numbers.size();

    for (int first = 0; first < n; ++first) {
        for (int second = first + 1; second < n; ++second) {
          if ((long long)numbers[first] * numbers[second] > max_product) {
            //max_product = std::max(max_product,
                max_product = ((long long)numbers[first] * numbers[second]);
          }
        }
    }

    return max_product;
}

//TO DO: Implement a fast algorithm to speed up run time
long long MaxPairwiseProductFast(const vector<int> & numbers){
  int n = numbers.size();

  int max_index1 = -1;
  for (int first = 0; first < n; ++first)
    if ((max_index1 == -1) || (numbers[first] > numbers[max_index1]))
      max_index1 = first;

  int max_index2 = -1;
  for (int second = 0; second < n; ++second)
    if ((second != max_index1) && ((max_index2 == -1) || (numbers[second] > numbers[max_index2])))
      max_index2 = second;

  //cout << max_index1 << ' ' << max_index2 << "\n";

  return ((long long)(numbers[max_index1])) * numbers[max_index2];
}

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    //cout << MaxPairwiseProduct(numbers); << "\n";

    //long long result = MaxPairwiseProduct(numbers);
    long long result = MaxPairwiseProductFast(numbers);
    cout << result << '\n';
    return 0;
}
