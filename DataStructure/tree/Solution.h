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

    bool isValidBST(TreeNode* root) {
        return isValidBSTNode(root, (long)(-0x7fffffff-2), (long)(0x7fffffff+1));
    }

    bool isValidBSTNode(TreeNode *p, long low, long high)
    {
        bool f1 = 1, f2 = 1;
        if (p->left)
        {
            int val = p->left->val;
            f1 = val > low && val < p->val && isValidBSTNode(p->left, low, p->val);
        }
        if (!f1) // a simple optimization
            return false;
        if (p->right)
        {
            int val = p->right->val;
            f2 = val > p->val && val < high && isValidBSTNode(p->right, p->val, high);
        }
        return f1 && f2;
    }

    bool findTarget(TreeNode* root, int k) {
        typedef struct TreeNode* pNode;
        unordered_set<int> s;
        pNode tmp;
        stack<pNode> stk;
        if (root)
            stk.push(root);

        while (!stk.empty())
        {
            tmp = stk.top(), stk.pop();
            s.insert(tmp->val);
            if (tmp->right)
                stk.push(tmp->right);
            if (tmp->left)
                stk.push(tmp->left);
        }

        auto it = s.cend();
        for (const int &val: s)
            if (val << 1 != k && s.find(k-val) != it)
                return true;
        return false;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int lower = p->val > q->val? q->val: p->val;
        int upper = p->val + q->val - lower;

        while (1)
        {
            if (root->val < lower)
                root = root->right;
            else if (root->val > upper)
                root = root->left;
            else
                break;
        }

        return root;

    }
};

#endif