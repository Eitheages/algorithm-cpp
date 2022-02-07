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

### 700. Search in a Binary Search Tree `searchBST`

#### Problem

You are given the `root` of a binary search tree (BST) and an integer `val`.

Find the node in the BST that the node's value equals `val` and return the subtree rooted with that node. If such a node does not exist, return `null`.

**Constraints:**

+ The number of nodes in the tree is in the range `[1, 5000]`.
+ `1 <= Node.val <= 107`
+ `root` is a binary search tree.
+ `1 <= val <= 107`

### 701. Insert into a Binary Search Tree `insertIntoBST`

#### Problem

You are given the `root` node of a binary search tree (BST) and a `value` to insert into the tree. Return *the root node of the BST after the insertion*. It is **guaranteed** that the new value does not exist in the original BST.

**Notice** that there may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion. You can return **any of them**.

**Constraints:**

+ The number of nodes in the tree will be in the range `[0, 104]`.
+ `-108 <= Node.val <= 108`
+ All the values `Node.val` are **unique**.
+ `-108 <= val <= 108`
+ It's **guaranteed** that `val` does not exist in the original BST.

### 98. Validate Binary Search Tree `isValidBST`

#### Problem

Given the `root` of a binary tree, *determine if it is a valid binary search tree (BST)*.

A **valid BST** is defined as follows:

+ The left subtree of a node contains only nodes with keys **less than** the node's key.
+ The right subtree of a node contains only nodes with keys **greater than** the node's key.
+ Both the left and right subtrees must also be binary search trees.

**Constraints:**

+ The number of nodes in the tree is in the range `[1, 104]`.
+ `-231 <= Node.val <= 231 - 1`

#### Solution

1. Update upper and lower while recursion.
2. ==For BST, in-order traversal naturally get an increasing sequence.== **Attention!!**

### 653. Two Sum IV - Input is a BST `findTarget`

#### Problem

Given the `root` of a Binary Search Tree and a target number `k`, return *`true` if there exist two elements in the BST such that their sum is equal to the given target*.

**Constraints:**

+ The number of nodes in the tree is in the range `[1, 104]`.
+ `-104 <= Node.val <= 104`
+ `root` is guaranteed to be a **valid** binary search tree.
+ `-105 <= k <= 105`

#### Solution

Hash Table or increasing sequence are both OK.

### 235. Lowest Common Ancestor of a Binary Search Tree `lowestCommonAncestor`

#### Problem

Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.

According to the [definition of LCA on Wikipedia](https://en.wikipedia.org/wiki/Lowest_common_ancestor): “The lowest common ancestor is defined between two nodes `p` and `q` as the lowest node in `T` that has both `p` and `q` as descendants (where we allow **a node to be a descendant of itself**).”

**Constraints:**

+ The number of nodes in the tree is in the range `[2, 105]`.
+ `-109 <= Node.val <= 109`
+ All `Node.val` are **unique**.
+ `p != q`
+ `p` and `q` will exist in the BST.

#### Solution **attention!!**

As for BST, find LCA is easy. We need merely one times of traversal. Maintain the `root` node, if `root->val` is not between `p->val` and `q->val`, it means we should shift the `root` to the correct child (depends on the which one is bigger). On the contrary, if `root->val` is between `p->val` and `q->val` (equal is OK, since the node is regarded as a descendant of itself), it means we have found the "crossing", more specifically, the answer.
