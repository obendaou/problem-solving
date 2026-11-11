#include <vector>

std::vector<int> sortedSquares(const std::vector<int>& nums)
{
    const int n = static_cast<int>(nums.size());
    int start = 0, end = n;
    while (start < end)
    {
        const int mid = start + (end - start) / 2;
        if (nums[mid] < 0) start = mid + 1;
        else end = mid;
    }

    int left = start - 1, right = start;
    std::vector<int> result(n);
    for (int& square : result)
    {
        if (right == n || (left >= 0 && nums[left] * nums[left] < nums[right] * nums[right]))
        {
            square = nums[left] * nums[left];
            --left;
        }
        else
        {
            square = nums[right] * nums[right];
            ++right;
        }
    }
    return result;
}
