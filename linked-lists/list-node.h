#ifndef PROBLEM_SOLVING_LIST_NODE_H
#define PROBLEM_SOLVING_LIST_NODE_H

// Local equivalent of the node type supplied by LeetCode.
struct ListNode
{
    int val;
    ListNode* next;

    explicit ListNode(int value = 0, ListNode* nextNode = nullptr)
        : val(value), next(nextNode) {}
};

#endif
