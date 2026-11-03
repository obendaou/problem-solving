#include <algorithm>
#include <vector>

std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
{
    std::vector<std::vector<int>> result;
    const int n = static_cast<int>(nums.size());
    if (n < 3) return result;

    std::sort(nums.begin(), nums.end());
    for (int i = 0; i < n - 2; ++i)
    {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        if (static_cast<long long>(nums[i]) + nums[n - 1] + nums[n - 2] < 0)
            continue;

        int left = i + 1;
        int right = n - 1;
        while (left < right)
        {
            const long long sum = static_cast<long long>(nums[i]) + nums[left] + nums[right];
            if (sum < 0) ++left;
            else if (sum > 0) --right;
            else
            {
                result.push_back({nums[i], nums[left], nums[right]});
                const int low = nums[left];
                const int high = nums[right];
                while (left < right && nums[left] == low) ++left;
                while (left < right && nums[right] == high) --right;
            }
        }
    }
    return result;
}
