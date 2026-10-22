#include <string>
#include <vector>

// Precondition: ASCII input, length at most 50,000.
int lengthOfLongestSubstring(const std::string& s)
{
    std::vector<int> seen(128, -1);
    int count = 0;
    int best = 0;
    for (int i = 0; i < static_cast<int>(s.length()); ++i)
    {
        const unsigned char character = static_cast<unsigned char>(s[i]);
        if (seen[character] != -1)
        {
            if (i - seen[character] > count)
                count++;
            else
                count = i - seen[character];
        }
        else
            count++;
        seen[character] = i;
        if (count > best)
            best = count;
    }
    return best;
}
