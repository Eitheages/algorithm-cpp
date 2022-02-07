## Heap

### Leftist Heap

Leftist heap is a binary tree, but not complete (not to mention perfect). So creating a leftist heap by an array can be very hard. Generally, leftist heap is created with linked nodes just like we did when creating a common binary tree.
We create a leftist heap to support merge operation between two heap.

#### Null Path Length `npl`

The original definition: Let the `npl` of a null node be `-1`. For every node `x` in the tree, we have:
$$
\mbox{npl}(x)=1+\min\{\mbox{npl(x.left), npl(x.right)}\}
$$
It's a recursive definition, which is difficult to understand. Based on this, we make some equivalent definitions.

1. $\mbox{npl}(x)= $​ min distance to a descendant with 0 or 1 children.
   This definition is good. We can see that the `npl` of a node without 2 children is `0`.
2. $\mbox{npl}(x)= $​​ the height of the largest perfect binary tree that is both itself rooted at x and contained within the subtree rooted at x.
   This definition makes a transition between "max" and "min". In fact, when discussing about a tree, a "min path" is naturally associated with a "max height of perfect binary tree".

#### Property of Leftist Heap

+ Order property
  Firstly, leftist heap is a heap. Therefore, pick min-heap as an example, the parent's priority value <= the children's priority value.
+ Structure property
  Secondly, we make some structure constraints. That is, for every node `x`, `npl(x.left) >= npl(x.right)`.
  The result: tree is at least as “heavy” on the left as the right.
  (Terminology: we will say a leftist heap’s tree is a leftist tree.)

#### Conclusion

+ Right Path (the path towards a leaf) is the Shortest.

  Based on the original definition of `npl` and the structure property of the leftist tree, this conclusion is naturally established (the length of right path beginning with root = `npl(root)`)
  Or by contradiction. Assume we have a path (`D1`) shorter than the right path (`D2`). Say it diverges from right path at node `x`. We have: 1. `npl(x.left) <= D1-1` (otherwise the `npl` is not minimum); 2. `npl(x.right) == D2-1`, since every node has the leftist property. Meanwhile we have `D1 < D2`. Above all, the leftist property at `x` violated! So the conclusion is right.
  In the other hand, we define $rChain(x)$: the right path (ended at leaf) beginning with node `x`. We know that  the length of $rChain(x)$​ = min length of path beginning with node `x`. Specially, the destination of `rChain(root)` is the shallowest leaf of the leftist tree. This is quite useful.

+ If the right path has $r$ nodes, then the tree has at least $2^r-1$​ nodes.

  Based on the second definition of `npl`, the tree contains a max prefect tree with height $r$. Thus there are at least $2^r-1$ nodes.
  
+ If a leftist tree has $n$​​​​​ nodes, then the number of nodes on the right path of the root $r\leqslant \left[\log_2{(n+1)}\right]=\mathcal{O}(\log n)$​​​​.
  This fact is the principle why leftist heap efficiently support merge operation.
  
+ Never exist a node, which own a right child but a left child.
  Obviously.

