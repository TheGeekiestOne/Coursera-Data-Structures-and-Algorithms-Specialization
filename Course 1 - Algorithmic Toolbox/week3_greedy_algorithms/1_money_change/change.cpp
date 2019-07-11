/**
 * The goal in this problem is to find the minimum number of coins needed to
 * change the input value (an integer) into coins with specified denominations.
 */



#include <limits>
#include <set>
#include <unordered_map>

using namespace std;

int money_change(int total, set<int> const& coins, unordered_map<int, int>& cache) {
    if (cache.find(total) != cache.end()) {
        return cache[total];
    }
    if (total == 0) {
        return 0;
    }
    if (total < 0) {
        throw invalid_argument("not defined for negative sum");
    }
    for (int coin : coins) {
        if (total - coin < 0) {
            continue;
        }
        if (total - coin == 0) {
            cache[total] = 1;
            break;
        }
        int coins_count = 1 + money_change(total - coin, coins, cache);
        if (cache.find(total) != cache.end()) {
            cache[total] = min(cache[total], coins_count);
        } else {
            cache[total] = coins_count;
        }
    }
    if (cache.find(total) != cache.end()) {
        return cache[total];
    } else {
        throw invalid_argument("no way to change " + to_string(total) + " coins");
    }
}

int money_change(int total, set<int> const& coins) {
    unordered_map<int, int> cache;
    return money_change(total, coins, cache);
}