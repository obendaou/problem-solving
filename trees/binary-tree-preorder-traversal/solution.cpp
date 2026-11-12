#include <vector>
#include "../maximum-depth-of-binary-tree/tree-node.h"

namespace {
void collectPreorder(TreeNode* root, std::vector<int>& result)
{
    if (!root) return;
    result.push_back(root->val);
    collectPreorder(root->left, result);
    collectPreorder(root->right, result);
}
}

std::vector<int> preorderTraversal(TreeNode* root)
{
    std::vector<int> result;
    collectPreorder(root, result);
    return result;
}
