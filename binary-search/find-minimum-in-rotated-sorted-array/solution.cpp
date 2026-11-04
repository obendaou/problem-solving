#include <vector>

int findMinIndex(const std::vector<int>& nums)
{
    // Requires a nonempty rotated ascending array of distinct values.
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;
    while (left < right)
    {
        const int mid = left + (right - left) / 2;
        if (nums[mid] > nums[right]) left = mid + 1;
        else right = mid;
    }
    return right;
}

// LeetCode asks for the minimum value, not its index.
int findMin(const std::vector<int>& nums)
{
    return nums[findMinIndex(nums)];
}
