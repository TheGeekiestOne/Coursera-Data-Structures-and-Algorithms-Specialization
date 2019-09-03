#include <iostream>
#include <vector>
#include <deque>

using std::vector;
using std::deque;

class solution
{
  public:
    vector<int> maxSlidingWindow(const vector<int> & nums, int k) {
        vector<int> result;
        deque<int> indx;
        int id = 0;
        indx.push_front(id);
        id++;
        for (;id < k;id++) {
            if (nums[id] >= nums[indx.front()])
                indx.push_front(id);
            else {
                while(nums[indx.back()] < nums[id])
                    indx.pop_back();
                indx.push_back(id);
            }
        }
        result.push_back(nums[indx.front()]);

        while ((size_t)id < nums.size()) {
            while (id-indx.front() >= 3)
                indx.pop_front();
            if (nums[id] >= nums[indx.front()])
                indx.push_front(id);
            else {
                while(nums[indx.back()] < nums[id])
                    indx.pop_back();
                indx.push_back(id);
            }
            id++;
            result.push_back(nums[indx.front()]);
        }

        return result;
    }
};

int main() {
    // vector<int> nums{1,3,-1,-3,5,3,6,7};
    // vector<int> nums{1,2,3,1,4,5,2,3,6};
    // vector<int> nums{8,5,10,7,9,4,15,12,90,13};
    vector<int> nums{12, 1, 78, 90, 57, 89, 56};
    int windowsize = 3;

    solution soln;
    auto res = soln.maxSlidingWindow(nums, windowsize);

    std::cout << "The maximum sliding window is:\n";
    for (auto i : res)
        std::cout << i << " ";
    std::cout << std::endl;
}
