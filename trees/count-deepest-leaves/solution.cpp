#include "../maximum-depth-of-binary-tree/tree-node.h"

namespace {
void countAtDepth(TreeNode* root, int& count, int currDepth, int& maxDepth)
{
    if (!root) return;
    ++currDepth;
    if (currDepth == maxDepth)
        ++count;
    else if (currDepth > maxDepth)
    {
        count = 1;
        maxDepth = currDepth;
    }

    countAtDepth(root->left, count, currDepth, maxDepth);
    countAtDepth(root->right, count, currDepth, maxDepth);
}
}

int countDeepestLeaves(TreeNode* root)
{
    int count = 0, maxDepth = 0;
    countAtDepth(root, count, 0, maxDepth);
    return count;
}
