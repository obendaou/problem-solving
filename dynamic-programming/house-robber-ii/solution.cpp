#include <algorithm>
#include <vector>

// Nonnegative amounts; input length and achievable totals fit in int.
namespace {
int robRange(const std::vector<int>& nums, int start, int end)
{
    // Precondition: 0 <= start <= end < nums.size().
    const int length = end - start + 1;
    if (length == 1) return nums[start];
    if (length == 2) return std::max(nums[start], nums[start + 1]);

    int a = nums[start];
    int b = nums[start + 1];
    int c = nums[start] + nums[start + 2];
    for (int i = start + 3; i <= end; ++i)
    {
        const int current = std::max(a, b) + nums[i];
        a = b;
        b = c;
        c = current;
    }
    return std::max(b, c);
}
}

int rob(const std::vector<int>& nums)
{
    const int n = static_cast<int>(nums.size());
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    return std::max(robRange(nums, 0, n - 2),
                    robRange(nums, 1, n - 1));
}
