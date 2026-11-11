#include <unordered_map>
#include <vector>

int subarraySum(const std::vector<int>& nums, int k)
{
    std::unordered_map<int, int> frequency{{0, 1}};
    int sum = 0;
    int count = 0;
    for (int value : nums)
    {
        sum += value;
        const auto it = frequency.find(sum - k);
        if (it != frequency.end()) count += it->second;
        ++frequency[sum];
    }
    return count;
}
