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

int search(const std::vector<int>& nums, int target)
{
    if (nums.empty()) return -1;
    const int minIndex = findMinIndex(nums);
    int start, end;
    const int last = static_cast<int>(nums.size()) - 1;
    if (minIndex == 0) { start = 0; end = last; }
    else if (target > nums[last]) { start = 0; end = minIndex - 1; }
    else { start = minIndex; end = last; }

    while (start <= end)
    {
        const int mid = start + (end - start) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] > target) end = mid - 1;
        else start = mid + 1;
    }
    return -1;
}
