#include <cstddef>
#include <queue>
#include <vector>
#include "../maximum-depth-of-binary-tree/tree-node.h"

std::vector<std::vector<int>> levelOrder(TreeNode* root)
{
    std::vector<std::vector<int>> result;
    if (!root) return result;

    std::queue<TreeNode*> pending;
    pending.push(root);
    result.emplace_back();
    std::size_t levelSize = pending.size();
    while (!pending.empty())
    {
        if (levelSize == 0)
        {
            levelSize = pending.size();
            result.emplace_back();
        }

        TreeNode* node = pending.front();
        pending.pop();
        result.back().push_back(node->val);
        if (node->left) pending.push(node->left);
        if (node->right) pending.push(node->right);
        --levelSize;
    }
    return result;
}
