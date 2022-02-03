#ifndef SOLU
#define SOLU

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    struct NodeVal
    {
        TreeNode *node;
        int sum;
        NodeVal(TreeNode *p, int x): node(p), sum(x){}
    };

    // bfs
    bool hasPathSum(TreeNode* root, int targetSum) {
        queue<struct NodeVal*> q;
        struct NodeVal *tmp;
        if (root)
            q.push(new NodeVal(root, root->val));

        while (!q.empty())
        {
            tmp = q.front(), q.pop();

            if (!tmp->node->left && !tmp->node->right)
                if (tmp->sum == targetSum)
                    return true;
                else
                    continue;
            if (tmp->node->left)
                q.push(new struct NodeVal(tmp->node->left, tmp->sum + tmp->node->left->val));
            if (tmp->node->right)
                q.push(new struct NodeVal(tmp->node->right, tmp->sum + tmp->node->right->val));
            delete tmp;
        }
        return false;
    }

    TreeNode* searchBST(TreeNode* root, int val) {
        while (root && root->val != val)
            root = root->val > val? root->left: root->right;
        return root;
    }

    TreeNode* insertIntoBST(TreeNode* root, int val) {
        using Node = struct TreeNode;
        if (!root)
            root = new Node(val);
        else if (root->val < val)
            root->right = insertIntoBST(root->right, val);
        else
            root->left = insertIntoBST(root->left, val);
        return root;
    }
};

#endif