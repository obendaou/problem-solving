#include "../list-node.h"

ListNode* reverseList(ListNode* head)
{
    ListNode* curr = head;
    ListNode* last = nullptr;
    while (curr)
    {
        ListNode* tmp = curr->next;
        curr->next = last;
        last = curr;
        curr = tmp;
    }
    return last;
}
