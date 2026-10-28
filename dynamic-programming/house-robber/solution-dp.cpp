#include <algorithm>
#include <vector>

// dp[i] includes house i. Amounts are nonnegative and totals fit in int.
int robWithTable(const std::vector<int>& nums)
{
    const int n = static_cast<int>(nums.size());
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    if (n == 2) return std::max(nums[0], nums[1]);

    std::vector<int> dp(n);
    dp[0] = nums[0];
    dp[1] = nums[1];
    dp[2] = nums[0] + nums[2];
    for (int i = 3; i < n; ++i)
        dp[i] = std::max(dp[i - 2], dp[i - 3]) + nums[i];
    return std::max(dp[n - 2], dp[n - 1]);
}
