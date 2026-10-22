#include <unordered_map>
#include <vector>

long long countPairs(const std::vector<int>& nums, int target)
{
    std::unordered_map<int, int> seen;
    long long count = 0;

    for (int num : nums)
    {
        auto it = seen.find(target - num);
        if (it != seen.end())
            count += it->second;
        seen[num]++;
    }
    return count;
}

#ifdef COUNT_PAIRS_DEMO
#include <cassert>
#include <iostream>

int main()
{
    assert(countPairs({3, 3, 3}, 6) == 3);
    assert(countPairs({1, 5, 5}, 6) == 2);
    assert(countPairs({1, 1, 5, 5}, 6) == 4);
    assert(countPairs({-3, 3, 0, 0}, 0) == 2);
    assert(countPairs({0, 0, 0, 0}, 0) == 6);
    assert(countPairs({1, 2, 3}, 100) == 0);
    assert(countPairs({}, 6) == 0);
    assert(countPairs({3}, 6) == 0);
    assert(countPairs({2, 4}, 6) == 1);
    assert(countPairs(std::vector<int>(100000, 0), 0) == 4999950000LL);
    std::cout << "10 cases passed\n";
}
#endif
