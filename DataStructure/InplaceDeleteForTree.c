//
http://www.keithschwarz.com/interesting/code/?dir=inplace-tree-delete

/******************************************************************************
 * File: InplaceTreeDelete.hh
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * An O(n)-time, O(1)-space algorithm for freeing all of the nodes in a binary
 * search tree.
 *
 * In languages like C or C++ with explicit memory management, all memory
 * allocated for a data structure must be explicitly freed.  When working with
 * linked structures, this often requires additional overhead space to store
 * information about where all of the nodes in a structure live.
 *
 * The algorithm contained here is an O(n)-time, O(1)-space algorithm for
 * freeing all of the nodes in a binary search tree with n nodes.  Its overhead
 * is purely limited to the stack space required to hold a single stack frame
 * with a constant number of pointers.
 *
 * Intuitively, the algorithm is an optimization of an inorder algorithm that
 * deletes all the nodes of the tree in the order in which they would be
 * visited by an inorder traversal.  This is unusual; most algorithms for
 * deleting trees use a postorder traversal so that no node is deleted until
 * all of its children have been freed.
 *
 * Intuitively, the algorithm works by getting a tree like this one:
 *
 *                      Root
 *                     /    \
 *                 Left     Right
 *                Subtree  Subtree
 * 
 * Then recursively freeing the left subtree, then the root, then the right
 * subtree.  An initial implementation of this algorithm is given here:
 *
 *     void DeleteTreeRec(Node* root) {
 *         if (root == nullptr) return;
 *
 *         // Free the left subtree
 *         DeleteTreeRec(root->left);
 *
 *         // Cache a pointer to the right subtree.
 *         Node* toDelete = root->right;
 *
 *         // Delete the root.
 *         delete root;
 *
 *         // Recursively delete the right subtree.
 *         DeleteTreeRec(root->right);
 *    }
 *
 * This approach will successfully delete the entire tree, but its space usage
 * is not very good.  The number of stack frames active at any one point in
 * time can equal the height of the tree, so the space usage is O(h).  In the
 * worst-case, this gives a space usage of O(n) for a degenerate tree, which
 * will almost certainly cause a stack overflow.
 *
 * To address this, we will use a clever trick first I first heard from Leonid
 * Shamis (and have not seen documented elsewhere).  The idea is to delete the
 * nodes of the tree in the same order in which they would have been deleted by
 * this recursive algorithm, but to do so without needing extra stack frames.
 * 
 * The main trick used in this construction is the following observation: if
 * the root of the tree has no left child, then the algorithm would just delete
 * the root, then recursively delete all the nodes from the right subtree.
 * This is shown here:
 *
 *                      Root        <--- Delete this node, ...
 *                        \
 *                       Right      <--- ... then recursively delete this
 *                      Subtree              subtree.
 *
 * Consequently, if we can somehow reshape the tree so that we get it into this
 * configuration, we can very easily remove one node from the tree.
 *
 * To accomplish this, we will use a series of tree rotations to rearrange the
 * nodes in a tree.  Recall that a right rotation is a transformation of a BST
 * that is done as follows:
 *
 *              u                v
 *             / \              / \
 *            v   C    --->    A   u
 *           / \                  / \
 *          A   B                B   C
 *
 * This structural transformation preserves the relative ordering of the nodes
 * in the tree (in that an inorder traversal of the tree before and after the
 * rotation will produce the same sequence of nodes), but decreases the height
 * of the left subtree of the tree by one.  In fact, applying sufficiently
 * many right rotations to the root of a tree will eventually place the
 * leftmost tree node at the root of the tree with no left child.
 *
 * Based on this observation, the algorithm we will use to free a tree in O(1)
 * auxiliary storage space is the following:
 *
 *    1. If the tree root is NULL, we are done.
 *    2. If the tree root has a left child, apply a left rotation.
 *    3. If the tree root has no left child, delete the root and make its right
 *          child the root of the tree.
 *    4. Go to (1)
 * 
 * How does this algorithm follow from our original inorder deletion algorithm?
 * The reason for this is the order in which the nodes in the tree are deleted.
 * We claim that the nodes in the tree will be deleted by both the recursive
 * and the in-place algorithms in the same order.  The proof is done by an
 * induction on the height of the left subtree.
 *
 * As our base case, if the tree is empty (height -1), then both of these
 * algorithms will not delete any nodes.  If the tree is just a single node
 * (height 0), then both of the algorithms will immediately delete the root and
 * do no other deletions.
 *
 * For the inductive step, suppose that we have a tree consisting of a root v
 * node with a left subtree L and a right subtree R.  Suppose that the height
 * of this new tree is h + 1, meaning that the heights of L and R are both at
 * most h.  This means that our tree looks like this:
 *
 *                                 v
 *                                / \
 *                               L   R
 *
 * There are two cases to consider.  First, if L is empty, then the recursive
 * algorithm will recurse on L (making no deletions), then delete v, then
 * delete the nodes in R.  The in-place algorithm will delete v, then delete
 * all the nodes in R.  By our inductive hypothesis, the deletion of the nodes
 * in R will be done the same way by both of the algorithms, so in this case
 * both of the algorithms delete the nodes in the same order.
 *
 * Second, if L is nonempty, then it must consist of a root u with two subtrees
 * A and B.  Since L has height at most h, A and B have heights at most h - 1.
 * This is shown here:
 *
 *                                 v
 *                                / \
 *                               u   R
 *                              / \
 *                             A   B
 *
 * The recursive algorithm will first recurse on the subtree rooted at U.  It
 * then deletes all the nodes in A, then the node u, then all the nodes in B.
 * Then, it deletes v, then the nodes in R.  The deletion order is therefore
 * A, u, B, v, R.
 *
 * The in-place algorithm will do a right rotation to reshape the tree into
 * this tree here:
 *                              
 *              u                v
 *             / \              / \
 *            v   R    --->    A   u
 *           / \                  / \
 *          A   B                B   R
 *
 * Note that the height of the left subtree has decreased by one.  Therefore,
 * by our inductive hypothesis, the recursive deletion algorithm will delete
 * the nodes in this tree in the same order that the in-place algorithm would
 * delete these nodes.  This is in the order A, v, B, u, R.  This matches the
 * order in which the nodes in the original tree would be deleted by the
 * recursive algorithm, so the claim holds for trees of height h + 1, as
 * required.
 *
 * We have now established that this algorithm deletes the nodes in the tree in
 * the same order that they would be deleted by the recursive traversal, and
 * thus can be thought of as a space-optimized version of the recursive
 * algorithm.  However, we have yet to establish any bounds on the runtime of
 * this algorithm.  To do so, we will now prove that the runtime of this
 * algorithm is O(n).
 *
 * First, note that each tree rotation can be done by rearranging a total of
 * O(1) pointers, and each deletion is assumed to take O(1) time.  The in-place
 * algorithm clearly only does O(n) deletions, since it never deletes the same
 * node twice, so we need to put a bound on the number of rotations that this
 * algorithm will ever do.
 * 
 * To do this, we will use the fact that the nodes are deleted in the order in
 * which the recursive in-order traversal algorithm would make the deletions.
 * This means that if we are given a tree with root u and subtrees L and R, we
 * know that the algorithm will delete all of the nodes in L, then the node u,
 * then the nodes in R.
 *
 * We need one more key observation: suppose that we are given a tree like the
 * one above, which is shown here:
 *
 *                                 u
 *                                / \
 *                               L   R
 *
 * We claim that the edge from u to R is never rotated.  We could formalize
 * this using an inductive argument, but the intution is the following: if L
 * is empty, then we will delete the node u, and so the edge ceases to exist
 * without ever being rotated.  On the other hand, if L is not empty, then
 * after doing a rotation, we will end up with this tree:
 *
 *              u                v
 *             / \              / \
 *            v   R    --->    A   u
 *           / \                  / \
 *          A   B                B   R
 *
 * Since the nodes in this tree are deleted in an in-order fashion, we will
 * delete all of A, then delete the node v.  We're now left with a tree with
 * an edge from u to R and a smaller left subtree, so inductively we know that
 * the edge from u to R is never rotated.
 *
 * Given this result, we can start to bound the number of rotations that are
 * going to be done by looking at the number of rotations necessary to delete
 * the left subtree, plus the number of rotations necessary to delete the right
 * subtree.  This works because we never have to worry about doing any
 * rotations that would change the nodes in R until we've done all of the
 * rotations necessary to delete the nodes in L.  For this, we can make a
 * simple inductive argument to show that in an n-node tree, at most n - 1
 * rotations are made.  (We special-case the case where the tree is empty and
 * say that zero rotations are done).
 *
 * As a base case, if the tree has just one node, zero rotations are done, and
 * 0 = 1 - 1.
 *
 * For the inductive step, assume that the tree has n + 1 nodes in it.  If the
 * left subtree is empty, then we delete the root, dropping the number of nodes
 * to n.  We then need at most n - 1 more rotations to delete the remaining
 * tree (by our IH), and n - 1 = (n + 1) - 2 <= (n + 1) - 1, so the claim
 * holds.
 *
 * On the other hand, if the left subtree isn't empty, then we will do a single
 * rotation, as shown here:
 *
 *              u                v
 *             / \              / \
 *            v   R    --->    A   u
 *           / \                  / \
 *          A   B                B   R
 *
 * Let's think about how many rotations are necessary to delete this tree.
 * Since we won't ever rotate the edge from v to u, we can count the number of
 * rotations as the number of rotations necessary to delete the nodes in A,
 * plus the number of rotations necessary to delete the nodes in the subtree
 * rooted at u.  If we denote the number of nodes in a subtree T as #(T), then
 * the number of rotations necessary to free this tree is given by #(A) + #(u).
 * Note that #(A) + #(u) = n - 1, since every node except v is counted here.
 * By the IH, the number of rotations necessary for each step is therefore
 * #(A) - 1 + #(u) - 1 = n - 2.  Adding in the one rotation we did in the first
 * step, this means that a total of at most n - 1 rotations are necessary, so
 * the claim holds in this step.
 *
 * Overall, this means that the algorithm makes at most O(n) rotations and O(n)
 * deletions, and uses only O(1) storage space.  Therefore, the overall
 * algorithm takes time O(n) and uses O(1) space.
 */
#ifndef InplaceTreeDelete_Included
#define InplaceTreeDelete_Included

/**
 * Function: DeleteTreeInPlace(TreeNode* root, 
 *                             TreeNode* TreeNode::* left  = &TreeNode::left,
 *                             TreeNode* TreeNode::* right = &TreeNode::right);
 * Usage: DeleteTreeInPlace(root, &Node::less, &Node::more);
 *        DeleteTreeInPlace(root);
 * ----------------------------------------------------------------------------
 * Deletes all nodes in the tree rooted at root using O(1) storage space and
 * O(n) time.  The algorithm will use the member pointers provided as inputs to
 * determine which pointers store the left and right subtrees.
 */
template <typename TreeNode>
void DeleteTreeInPlace(TreeNode* root,
                       TreeNode* TreeNode::* left  = &TreeNode::left,
                       TreeNode* TreeNode::* right = &TreeNode::right) {
  /* Keep deleting nodes while there are nodes to delete. */
  while (root != nullptr) {
    /* If there is a left child, do a left rotate. */
    if (root->*left != nullptr) {
      /* Store the root's left child, which will become the new root. */
      TreeNode* leftNode = root->*left;

      /* Make the left subtree's right subtree the left subtree of the root. */
      root->*left = root->*left->*right;

      /* Make the new root node have the old root as a right child. */
      leftNode->*right = root;

      /* Make the root the old left subtree. */
      root = leftNode;      
      
    } 
    /* Otherwise, delete the root and descend into the right subtree. */
    else {
      TreeNode* rightTree = root->*right;
      delete root;
      root = rightTree;
    }
  }
}


#endif
