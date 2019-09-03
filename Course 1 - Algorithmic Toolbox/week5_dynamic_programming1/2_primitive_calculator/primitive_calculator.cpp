
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

////////////////////////////////////////////////////////////////////////////////
// Created By Ayran Olckers
//
//
// Reversi
////////////////////////////////////////////////////////////////////////////////

std::list<int32_t> optimal_sequence(int number)
{
std::vector<int32_t> min_steps(number + 1);
std::vector<int32_t> predecessor(number + 1);

for (int32_t i = 2; i <= number; i++)
{
    min_steps[i] = min_steps[i-1] + 1;
    predecessor[i] = i - 1;
    if (i % 3 == 0)
        if (min_steps[i/3] < min_steps[i])
        {
            min_steps[i] = min_steps[i/3] + 1;
            predecessor[i] = i/3;
        }
    if (i % 2 == 0)
        if (min_steps[i/2] < min_steps[i])
        {
            min_steps[i] = min_steps[i/2] + 1;
            predecessor[i] = i/2;
        }
}

std::list<int32_t> sequence;
for (int32_t i = number; i != 0; i = predecessor[i]) {
    sequence.push_front(i);
}

std::cout << min_steps[number] << std::endl;
return sequence;
}

int main() {
int n;
std::cin >> n;
std::list<int> sequence = optimal_sequence(n);
while (!sequence.empty())
{
    std::cout << sequence.front() << " ";
    sequence.pop_front();
}
return 0;
}
