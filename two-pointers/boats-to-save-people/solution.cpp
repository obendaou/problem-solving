#include <algorithm>
#include <vector>

// Positive weights, each <= limit; each boat carries at most two people.
int numRescueBoats(std::vector<int>& people, int limit)
{
    std::sort(people.begin(), people.end());
    int left = 0;
    int right = static_cast<int>(people.size()) - 1;
    int boats = 0;
    while (left <= right)
    {
        if (left < right &&
            static_cast<long long>(people[left]) + people[right] <= limit)
            ++left;
        --right;
        ++boats;
    }
    return boats;
}
