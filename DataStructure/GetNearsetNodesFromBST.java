//http://blog.csdn.net/zhouhao011280s/article/details/8044056
/*
给定key值，在Binary Search Tree中查找最接近该键值的结点集合；还有key值的结点可以不在树中。
*/

public class BinarySearchTreeTest {
  
	public static void main(String[] args) {
		
		/**
		 * Test searching for closest nodes for the given key
		 */
		BinarySearchTree bst1 = new BinarySearchTree(null);
		for(int i=0;i<20;i++){
			bst1.insert(new BSTNode(new Random().nextInt(200)));
			//bst1.insertRecursively(new BSTNode(new Random().nextInt(100)),bst1.getRoot(),null);
		}
		bst1.inOrderWalk(bst1.getRoot());
		System.out.println();
		BSTNode[] nodes = bst1.getClosestNodes(45, 5);
		for (BSTNode bstNode : nodes) {
			System.out.print(bstNode.getKey() + "-");
		}
	}

}

package com.cupid.algorithm.tree;

import java.util.Stack;

public class BinarySearchTree {

  private BSTNode root = null;

	public BSTNode getRoot() {
		return root;
	}

	private void setRoot(BSTNode root) {
		this.root = root;
	}

	public BinarySearchTree(BSTNode root) {
		this.root = root;
	}

	/**
	* Search for the node for the given key.
	* If exists, return it.
	* If not, return the node which contain the nearest key to the given key.
	* For example, there are two nodes with key 40 and 45 in a BST, respectively.
	* Searching for 42 will return 40 and 44 will return 45.
	*/
	public BSTNode searchForNearest(int key) {
		BSTNode node = null;
		BSTNode root = this.getRoot();
		BSTNode nearest = null;
		while (root != null) {
			nearest = root;
			if (key < root.getKey()) {
				root = root.getLeft();
			} else if (key > root.getKey()) {
				root = root.getRight();
			} else {
				node = root;
				root = null;
			}
		}
		if(node!=null){
			return node;
		}else{
			BSTNode n = null;
			if(key < nearest.getKey()){
				n = this.predecessor(nearest);
				if(key-n.getKey() < nearest.getKey() - key)
					nearest = n;
			}
			if(key > nearest.getKey()){
				n = this.successor(nearest);
				if(key- nearest.getKey() > n.getKey() - key)
					nearest = n;
			}
			return nearest;
		}
		
	}
	/**
	 * Get a number of m nodes which contain the closest keys to the given key.
	 * Here, by closest it means the differences between these keys and the given key
	 * is the 1st,2nd,3rd...mth smallest.
	 * Two examples:
	 * The in-order traversal of a BST is 10,20,25,30,40
	 * When calls this method with parameters (25,2), it returns 20,30;
	 * When calls this method with parameters (28,2), it returns 25,30
	 * 
	 * @param key
	 * @param m
	 * @return BSTNode[]
	 */
	public BSTNode[] getClosestNodes(int key, int m) {
		BSTNode[] closestNodes = new BSTNode[m];
		BSTNode me = this.searchForNearest(key);
		int index = 0;
		BSTNode p = null;
		BSTNode s = null;
		// Test whether the returned node contains the given KEY.
		// If not, save the node
		// and move predecessor pointer and successor pointer accordingly.
		if (me.getKey() < key) {
			closestNodes[index] = me;
			index++;
			s = this.successor(me);
			p = this.predecessor(me);
		}else if(me.getKey() > key){
			closestNodes[index] = me;
			index++;
			p = this.predecessor(me);
			s = this.successor(me);
		}else{
			p = this.predecessor(me);
			s = this.successor(me);
		}
		for (;index < m; index++) {
			// When s is null, s actually points to the right-most element of
			// the BST.
			// In such case no more elements' key greater than KEY can be added into
			// result set.
			// Thus continually add elements's key less than KEY into result set until
			// its size reaches m.
			if (p != null && (s == null || key - p.getKey() < s.getKey() - key)) {
				closestNodes[index] = p;
				p = this.predecessor(p);
				// When p is null, p actually points to the left-most element of
				// the BST.
				// In such case no more elements' key less than KEY can be added into
				// result set.
				// Thus continually add elements' key greater than KEY into result set
				// until its size reaches m.
			} else if (s != null && (p == null || key - p.getKey() > s.getKey() - key)) {
				closestNodes[index] = s;
				s = this.successor(s);
			} else {
				if (p != null && s != null) {
					closestNodes[index] = p;
					p = this.predecessor(p);
					index = index + 1;
					if (index < m) {
						closestNodes[index] = s;
						s = this.successor(s);
					}
				}
			}
		}
		return closestNodes;
	}

	public void insert(BSTNode node) {
		BSTNode child = this.getRoot();
		BSTNode parent = null;
		while (child != null) {
			parent = child;
			if (node.getKey() < child.getKey()) {
				child = child.getLeft();
			} else {
				child = child.getRight();
			}
		}
		node.setParent(parent);
		if (parent == null) {
			setRoot(node);
		} else if (node.getKey() < parent.getKey()) {
			parent.setLeft(node);
		} else {
			parent.setRight(node);
		}
	}

	// If node's key is the largest,
	// this method will return NULL (the parent of root node).
	public BSTNode successor(BSTNode node) {
		if (node.getRight() != null) {
			node = node.getRight();
			while (node.getLeft() != null) {
				node = node.getLeft();
			}
			return node;
		}
		BSTNode parent = node.getParent();
		while (parent != null && parent.getRight() == node) {
			node = parent;
			parent = parent.getParent();
		}
		return parent;
	}

	// If node's key is the smallest,
	// this method will return NULL (the parent of root node).
	public BSTNode predecessor(BSTNode node) {
		if (node.getLeft() != null) {
			node = node.getLeft();
			while (node.getRight() != null) {
				node = node.getRight();
			}
			return node;
		}
		BSTNode parent = node.getParent();
		while (parent != null && parent.getLeft() == node) {
			node = parent;
			parent = parent.getParent();
		}
		return parent;
	}

	// Recursive in-order traversal
	public void inOrderWalk(BSTNode node) {
		if (node != null) {
			inOrderWalk(node.getLeft());
			System.out.print(node.getKey() + "-");
			inOrderWalk(node.getRight());
		}
	}

	// Recursive post-order traversal
	public void postOrderWalk(BSTNode node) {
		if (node != null) {
			postOrderWalk(node.getLeft());
			postOrderWalk(node.getRight());
			System.out.print(node.getKey() + "-");
		}
	}

	// Recursive pre-order traversal
	public void preOrderWalk(BSTNode node) {
		if (node != null) {
			System.out.print(node.getKey() + "-");
			preOrderWalk(node.getLeft());
			preOrderWalk(node.getRight());
		}
	}

}

package com.cupid.algorithm.tree;

public class BSTNode {
  
	private BSTNode parent = null;
	private BSTNode left = null;
	private BSTNode right = null;
	private int key = Integer.MIN_VALUE;
	private  boolean visited = false;
	
	public BSTNode(BSTNode p,BSTNode l,BSTNode r,int k){
		this.parent = p;
		this.left = l;
		this.right = r;
		this.key = k;
	}
	
	public BSTNode(int k){
		this.key = k;
	}

	public void setParent(BSTNode parent) {
		this.parent = parent;
	}

	public void setLeft(BSTNode left) {
		this.left = left;
	}

	public void setRight(BSTNode right) {
		this.right = right;
	}

	public void setKey(int key) {
		this.key = key;
	}

	public BSTNode getParent() {
		return parent;
	}

	public BSTNode getLeft() {
		return left;
	}

	public BSTNode getRight() {
		return right;
	}

	public int getKey() {
		return key;
	}

	public boolean isVisited() {
		return visited;
	}

	public void setVisited(boolean visited) {
		this.visited = visited;
	}
	
}
