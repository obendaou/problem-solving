#include <stack>
#include <string>

using std::stack;
using std::string;

bool isValid(const string& s)
{
    stack<char> S;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '}') {
            if (S.empty()) return false;
            if (S.top() == '{') S.pop(); else return false;
        } else if (s[i] == ']') {
            if (S.empty()) return false;
            if (S.top() == '[') S.pop(); else return false;
        } else if (s[i] == ')') {
            if (S.empty()) return false;
            if (S.top() == '(') S.pop(); else return false;
        } else S.push(s[i]);
    }
    return S.empty();
}
