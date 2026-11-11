#include "../list-node.h"

ListNode* swapPairs(ListNode* head)
{
    if (!head || !head->next) return head;
    ListNode* one = head;
    ListNode* two = head->next;
    ListNode* newHead = two;
    ListNode* lastPair = nullptr;
    while (one && two)
    {
        if (lastPair) lastPair->next = two;
        ListNode* tmp = two->next;
        two->next = one;
        one->next = tmp;
        lastPair = one;
        one = tmp;
        two = one ? one->next : nullptr;
    }
    return newHead;
}
