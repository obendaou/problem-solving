#include <algorithm>
#include <stack>
#include <vector>

class MinStack {
public:
    void push(int value) {
        if (s.empty())
            s.push({value, value});
        else
            s.push({value, std::min(s.top()[1], value)});
    }

    void pop() {
        s.pop();
    }

    int top() {
        return s.top()[0];
    }

    int getMin() {
        return s.top()[1];
    }

private:
    std::stack<std::vector<int>> s;
};
