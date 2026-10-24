#include <vector>

// nums is sorted in ascending order, has distinct values,
// and contains at most 100,000 elements.
int binarySearch(const std::vector<int>& nums, int target)
{
    int start = 0;
    int end = static_cast<int>(nums.size()) - 1;

    while (start <= end)
    {
        const int mid = start + (end - start) / 2;
        if (nums[mid] == target)
            return mid;
        if (nums[mid] > target)
            end = mid - 1;
        else
            start = mid + 1;
    }
    return -1;
}
