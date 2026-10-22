#include <unordered_map>
#include <vector>

std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> seen;
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        auto it = seen.find(target - nums[i]);
        if (it != seen.end())
            return {it->second, i};
        seen[nums[i]] = i;
    }
    return {};
}

#ifdef TWO_SUM_DEMO
#include <cassert>
#include <iostream>

int main() {
    struct Case { std::vector<int> nums; int target; };
    std::vector<Case> cases = {
        {{3, 3}, 6}, {{0, 0}, 0},
        {{-3, 4, 3, 90}, 0}, {{3, 2, 4}, 6}
    };
    for (auto& test : cases) {
        const auto indices = twoSum(test.nums, test.target);
        assert(indices.size() == 2);
        assert(indices[0] != indices[1]);
        assert(indices[0] >= 0 && indices[1] >= 0);
        assert(static_cast<std::size_t>(indices[0]) < test.nums.size());
        assert(static_cast<std::size_t>(indices[1]) < test.nums.size());
        assert(test.nums[indices[0]] + test.nums[indices[1]] == test.target);
    }
    std::cout << "4 cases passed\n";
}
#endif
