#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;

int lengthOfLongestSubstring(const string& s)
{
    unordered_map<char, int> seen;
    int count = 0;
    int max = 0;
    for (int i = 0; i < s.length(); i++)
    {
        auto it = seen.find(s[i]);
        if (it != seen.end())
        {
            if (i - it->second > count)
                count++;
            else
                count = i - it->second;
            it->second = i;
        }
        else
        {
            count++;
            seen[s[i]] = i;
        }
        if (count > max)
            max = count;
    }
    return max;
}
