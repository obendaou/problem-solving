#include <cstddef>
#include <queue>
#include <vector>
#include "../maximum-depth-of-binary-tree/tree-node.h"

std::vector<int> rightSideView(TreeNode* root)
{
    std::vector<int> result;
    if (!root) return result;

    std::queue<TreeNode*> pending;
    pending.push(root);
    std::size_t levelSize = pending.size();
    while (!pending.empty())
    {
        TreeNode* node = pending.front();
        pending.pop();
        if (node->left) pending.push(node->left);
        if (node->right) pending.push(node->right);

        if (--levelSize == 0)
        {
            result.push_back(node->val);
            levelSize = pending.size();
        }
    }
    return result;
}
