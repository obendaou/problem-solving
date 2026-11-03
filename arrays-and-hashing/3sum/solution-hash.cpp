#include <algorithm>
#include <set>
#include <unordered_set>
#include <vector>

std::vector<std::vector<int>> threeSumHash(const std::vector<int>& nums)
{
    std::set<std::vector<int>> unique;
    for (std::size_t i = 0; i < nums.size(); ++i)
    {
        std::unordered_set<long long> seen;
        for (std::size_t j = i + 1; j < nums.size(); ++j)
        {
            const long long complement = -static_cast<long long>(nums[i]) - nums[j];
            if (seen.count(complement))
            {
                const int a = nums[i], b = nums[j], c = static_cast<int>(complement);
                const int low = std::min({a, b, c}), high = std::max({a, b, c});
                const int middle = static_cast<int>(-static_cast<long long>(low) - high);
                unique.insert({low, middle, high});
            }
            seen.insert(nums[j]);
        }
    }
    return {unique.begin(), unique.end()};
}
