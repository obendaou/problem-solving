#ifndef PROBLEM_SOLVING_TREE_NODE_H
#define PROBLEM_SOLVING_TREE_NODE_H

// Local equivalent of the node type supplied by LeetCode.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    explicit TreeNode(int value = 0,
                      TreeNode* leftChild = nullptr,
                      TreeNode* rightChild = nullptr)
        : val(value), left(leftChild), right(rightChild) {}
};

#endif
