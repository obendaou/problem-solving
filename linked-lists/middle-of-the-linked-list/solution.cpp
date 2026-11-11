#include "../list-node.h"

ListNode* middleNode(ListNode* head)
{
    if (!head) return nullptr;
    ListNode* fast = head;
    ListNode* slow = head;
    while (slow && fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
