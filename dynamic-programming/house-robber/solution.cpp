#include <algorithm>
#include <vector>

// Nonnegative amounts; input length and achievable totals fit in int.
int rob(const std::vector<int>& nums)
{
    const int n = static_cast<int>(nums.size());
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    if (n == 2) return std::max(nums[0], nums[1]);

    int a = nums[0];
    int b = nums[1];
    int c = nums[0] + nums[2];
    for (int i = 3; i < n; ++i)
    {
        const int current = std::max(a, b) + nums[i];
        a = b;
        b = c;
        c = current;
    }
    return std::max(b, c);
}
