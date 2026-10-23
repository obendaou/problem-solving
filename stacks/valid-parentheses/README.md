# Valid Parentheses

[Original problem on LeetCode](https://leetcode.com/problems/valid-parentheses/)

## Problem

Given a string containing only `(`, `)`, `[`, `]`, `{`, and `}`, determine whether every bracket closes in the correct order.

- Each closing bracket must match an opening bracket of the same type.
- The most recent unmatched opening bracket must close first.
- No opening bracket can remain unmatched at the end.
- The empty string is valid in this exercise.

Examples: `"([{}])"` and `"()[]"` are valid; `"([)]"` and `"("` are invalid.

## My approach

I use a stack to store unmatched opening brackets and scan from left to right.

1. If the character is an opening bracket, push it.
2. For a closing bracket, first check whether the stack is empty. If it is, return false.
3. Compare the closing bracket with the opening bracket at the top. On a match, pop; otherwise, return false.
4. After the scan, return whether the stack is empty.

Checking emptiness before calling `top()` avoids accessing an empty stack.

## How my approach evolved

My initial idea was to check pairs outward from the middle of the string. Odd-length strings cannot be balanced, but even length does not imply that valid brackets mirror the midpoint.

For example, `"()[]"` contains two valid adjacent groups. A midpoint-based approach compares the middle characters `)` and `[` and rejects it incorrectly.

I replaced that approach with a stack, which handles both nested groups and adjacent groups.

## Why a stack fits

A stack is LIFO: last in, first out. A closing bracket must match the **most recent unmatched opening bracket**.

For `"([{}])"`, after reading the three opening brackets, the stack contains `(`, `[`, `{` from bottom to top. The next character is `}`, so it must match `{`, the top entry.

A FIFO queue would expose `(` first and reject that valid input. A queue therefore cannot replace the stack unchanged in this algorithm.

## Dry run

Stack contents are shown from bottom to top.

| Character | Stack before | Action | Stack after |
| --- | --- | --- | --- |
| `(` | Empty | Push opening bracket | `(` |
| `[` | `(` | Push opening bracket | `( [` |
| `{` | `( [` | Push opening bracket | `( [ {` |
| `}` | `( [ {` | Matches top `{`: pop | `( [` |
| `]` | `( [` | Matches top `[`: pop | `(` |
| `)` | `(` | Matches top `(`: pop | Empty |

The stack is empty after processing the complete string, so the result is true.

For `"([)]"`, the character `)` encounters `[` at the top. The mismatch causes an immediate false result; searching deeper would violate nesting order.

## Why it works

After each successfully processed prefix, the stack contains exactly its unmatched opening brackets in their original order.

An opening bracket extends that list. A matching closing bracket removes its most recent entry. If no opening exists, the closing bracket cannot be matched. If the top has a different type, the nesting order is invalid.

At the end, an empty stack means every opening bracket was matched. A nonempty stack means some openings never closed.

## Solution

[Source file](solution.cpp)

```cpp
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
```

This preserves my submitted function, with the required standard headers and explicit namespace declarations added. The final `else` relies on the stated bracket-only input contract: all characters other than the three closing brackets are opening brackets. For a broader input contract, handling non-bracket characters would need to be specified.

The index loop retains a signed/unsigned comparison warning; a range-based `for (char c : s)` is an optional cleanup. For LeetCode, put the function inside its supplied `class Solution`.

## Complexity

Let `n` be the string length.

- **Worst-case time: O(n).** Each character is visited once; each bracket is pushed at most once and popped at most once.
- **Worst-case extra space: O(n).** A string consisting only of opening brackets stores all n characters before being rejected at the end.
- Deeply nested valid input also needs linear extra space, reaching n/2 stored opening brackets.

Early rejection can save work on some inputs, but it does not change the worst-case bound.

## Edge cases

| Input | Expected | Reason |
| --- | --- | --- |
| Empty string | true | Nothing is unmatched |
| `"()[]{}"` | true | Adjacent valid groups |
| `"([{}])"` | true | Proper nesting |
| `")"` | false | Closing bracket with empty stack |
| `"(]"` | false | Wrong bracket type |
| `"([)]"` | false | Incorrect nesting order |
| `"(("` | false | Openings remain after the scan |

## Validation

The saved practice results report that this function was compiled with C++17 and UndefinedBehaviorSanitizer and passed:

- Ten example cases.
- All 55,987 bracket strings of lengths 0–6, compared with an independent adjacent-pair reduction reference.
- Two deep-stack cases.

Those results apply to the submitted function preserved here. This publication received a static review; it was not recompiled during publication because the execution workspace was unavailable.

## What I learned

- Even length is necessary for balanced brackets, but not sufficient.
- Valid bracket strings can contain adjacent groups as well as nested groups.
- LIFO matches the required nesting order.
- Empty-stack, mismatched-type, and leftover-opening checks address different failure cases.
- Worst-case space includes invalid inputs that are rejected only after the scan.

## Practice context

I developed the stack solution after a counterexample exposed the midpoint approach's limitation, then clarified the failure conditions and wrote the implementation. This documents coached practice and my reasoning; independent recall is a separate goal.
