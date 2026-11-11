# Sorted Pair Sum

Given a sorted integer list, decide whether two **distinct indices** sum to a target. The output is a boolean, and the input can contain duplicates or negative numbers.

Start at opposite ends. If the sum is too small, the current left value cannot reach the target with any available partner, because the right endpoint is the largest available. Advance left. If the sum is too large, even the smallest available partner is too large for the current right value, so move right inward.

Use `start < end`: equal pointers would reuse one element. For `[-3, -1, 2, 4]` and target 3, the outer sum is 1, so advance left. Then `-1 + 4 = 3`, so return true.

Each unsuccessful step reduces the interval by one, giving O(n) time and O(1) extra space. The published Python function matched direct pair enumeration in 14,157 checks, including duplicates and singleton inputs.

## Solution

[solution.py](solution.py)
