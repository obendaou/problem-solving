#include <string>
#include <vector>

// Lowercase English letters only; empty s1 matches an empty window.
bool checkInclusion(const std::string& s1, const std::string& s2)
{
    if (s1.size() > s2.size()) return false;
    std::vector<int> target(26, 0), window(26, 0);
    const std::size_t m = s1.size();
    for (std::size_t i = 0; i < m; ++i)
    {
        ++target[s1[i] - 'a'];
        ++window[s2[i] - 'a'];
    }
    for (std::size_t start = 0; start <= s2.size() - m; ++start)
    {
        if (start > 0)
        {
            --window[s2[start - 1] - 'a'];
            ++window[s2[start + m - 1] - 'a'];
        }
        if (target == window) return true;
    }
    return false;
}
