#include <algorithm>
#include <limits>
#include <vector>

// Positive target and positive array elements; length fits in int.
int minSubArrayLen(int target, const std::vector<int>& nums)
{
    const int n = static_cast<int>(nums.size());
    int start = 0, i = 0;
    int best = std::numeric_limits<int>::max();
    long long sum = 0;
    while (i <= n)
    {
        if (sum >= target)
        {
            best = std::min(best, i - start);
            sum -= nums[start++];
        }
        else if (i < n)
            sum += nums[i++];
        else
            break;
    }
    return best == std::numeric_limits<int>::max() ? 0 : best;
}
