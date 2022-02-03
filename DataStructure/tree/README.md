# Tree

### 112. Path Sum  `hasPathSum`

#### Problem

Given the `root` of a binary tree and an integer `targetSum`, return `true` if the tree has a **root-to-leaf** path such that adding up all the values along the path equals `targetSum`.

A **leaf** is a node with no children.

#### Solution

1. BFS. Create two queues, one maintains every level of tree node and the other maintains the path sum of every node. Or create struct to maintain these two data.

2. DFS. Recursion model is

   ```cpp
   bool hasPathSum(TreeNode* root, int targetSum)
   {
       if (!root)
           return false;
       if (!root->left && !root->right)
           return root->val == targetSum;
       return root->left && hasPathSum(root->left, targetSum-root->val) ||
                  root->right && hasPathSum(root->right, targetSum-root->val);
   }
   ```

   