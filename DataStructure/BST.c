//http://cslibrary.stanford.edu/110/BinaryTrees.html
 
#include <limits.h>
struct node{
   int data;
   struct node*    left;
   struct node*    right;
};
/*
* Compute the number of nodes in a tree
*/
int size(struct node* node){
   if (NULL == node)
       return 0;
   else
       return size(node->left) + 1 + size(node->right);
}
/*
* Compute the maxDepth of a tree
*/
int maxDepth(struct node* node){
   if (NULL == node)
       return 0;
   else{
       int lDepth = maxDepth(node->left);
       int rDepth = maxDepth(node->right);
       if (lDepth > rDepth)
           return lDepth + 1;
       else
           return rDepth + 1;
   }
}
/*
* Get the min value of the BST
*/
int minValue(struct node* node){
   struct node* curr = node;
   while(curr->left != NULL)
       curr = curr->left;
   return curr->data;
}
/*
* Get the max value of the BST
*/
int maxValue(struct node* node){
   struct node* curr = node;
   while(curr->right != NULL)
       curr = curr->right;
   return curr->data;
}

// Get the count of nodes in BST in range [low, high]
int getCount(struct node* root, int low, int high)
{
	if (root == NULL)
		return 0;
	if (root->data == low && root->data == high)
		return 1;
		
	if (root->data >= low && root->data <= high)
		return 1 + getCount(root->left, low, high) + getCount(root->right, low, high);
	else if (root->data < low)
		return getCount(root->right, low, high);
	else 
		return getCount(root->left, low, high);
}

// Get count of nodes whose subtree is in range from low to hgih. 
bool getSubtreeCount(struct node* root, int low, int high, int* count)
{
	if (root == NULL)
		return true;
	
	bool l = (root->left)? getSubtreeCount(root->left, low, high, count): true;
	bool r = (root->right)? getSubtreeCount(root->right, low, high, count): true;
	
	if (l && r && (root->data >= low && root->data <= high))
	{
		++*count;
		return true;
	}
	return false;
}

// find ceil of a given input in BST. If input is more
// than the max key in BST, return -1
int Ceil(struct node* root, int input)
{
	if (root == NULL)
		return -1;
	if (root->data == input)
		return input;
	if (root->data < input)
		return Ceil(root->right, input);
	
	int ceil = Ceil(root->left, input);
	return (ceil >= input)? ceil: root->data;
}

/*
* Given a tree and a sum, return true if there is a path from the root
* down to a leaf, such that adding up all the values along the path
* equals the given sum.
*/
int hasPathSum(struct node* node, int sum){
   if (NULL == node)
       return (sum == 0);
   else{
       int subSum = sum - node->data;
       return (hasPathSum(node->left, subSum) ||
               hasPathSum(node->right, subSum));
   }
}
/*
* Given a binary tree, print out all of its root-to-leaf paths.
*/
void printPaths(struct node* node){
   int path[1000];
   printPathsRecur(node, path, 0);
}
void printPathsRecur(struct node* node, int path[], int pathLen){
   if (NULL == node)
       return ;
   path[pathLen] = node->data;
   pathLen++;
   if (NULL == node->left && NULL == node->right){
       for (int index = 0; index < pathLen; ++pathLen)
           cout << path[index] << " ";
       cout << endl;
   }else{
       printPathsRecur(node->left, path, pathLen);
       printPathsRecur(node->right, path, pathLen);
   }
}
/*
* Change a tree so that the roles of the left and right pointers
* are swapped at every node
*/
void mirror(struct node* node){
   if (NULL == node)
       return ;
   else{
       mirror(node->left);
       mirror(node->right);
       //swap the nodes
       struct node* tmp;
       tmp = node->left;
       node->left = node->right;
       node->right = tmp;
   }
}
/*
* For each node in a BSTs, create a new duplicate node and
* insert the duplicate node as the left child of the original node
*/
void doubleTree(struct node* node){
   if (NULL == node)
       return;
   else{
       doubleTree(node->left);
       doubleTree(node->right);
       struct node* oldNode;
       oldNode = node->left;
       node->left = newNode(node->data);
       node->left->left = oldNode;
   }
}
/*
*  Given two trees, return true if they are identical.
*/
bool sameTree(struct node* a, struct node* b){
   if (NULL == a && NULL == b)
       return true;
   else if(a != NULL && b != NULL){
       return a->data == b->data &&
               sameTree(a->left, b->left) &&
               sameTree(a->right, b->right);
   } else
       return false;
}
/*
* For the key values 1...numKeys,
* how many structurally unique binary search trees are possible
* that store those keys.
*
* Strategy: consider that each value could be the root.
*/
int countTrees(int numKeys){
   if (numKeys <= 1){
       return 1;
   }else{
       int sum = 0;
       int left, right, root;
       for (root = 1; root <= numkeys; ++root){
           left = countTrees(root - 1);
           right = countTrees(numKeys - root);
           // number of possible trees with this root = left*right
           sum += left*right;
       }
       return sum;
   }
}

//remove all the half nodes (which has only one child)
struct node* removeHalfNode(struct node* root) {
	if (root == NULL)
		return NULL;
	
	root->left = removeHalfNode(root->left);
	root->right = removeHaflNode(root->right);
	
	if (root->left == NULL && root->right == NULL)
		return root;
	
	if (root->left == NULL) {
		struct node* new_node = root->right;
		free(root);
		return new_node;
	}
	
	if (root->right == NULL) {
		struct node* new_node = root->left;
		free(root);
		return new_node;
	}
	
	return root;
}

/*
* Return true if a binary tree is BST
*/
bool isBST(struct node* node){
   if (NULL == node)
       return true;
   // false if the max of the left is > current node
   if (node->left != NULL && maxValue(node->left) > node->data)
       return false;
   // false if the min of the right is <= current node
   if (node->right != NULL && minValue(node->right) <= node->data)
       return false;
   // false if , recursively, the left or right is not a BST
   if (!isBST(node->left) || !isBST(node->right))
       return false;
   return true;
}

/*
* Return true if the tree is symmetric
*/
bool isSynmmectricRecv(struct node* root1, struct node* root2){
  if (root1 == NULL || root2 == NULL)
    return false;
  else if (root1 != NULL && root2 != NULL){
    if (root1->data == root2->data && 
        isSynmmectricRecv(root1->left, root1->right) &&
        isSynmmectricRecv(root2->left, root2->right))
       return true;
    else
       return false;
  }else
    return false;
}

bool isSynmmetric(struct node* head){
  if (head == NULL)
   return false;
  
  return isSynmmectricRecv(head->left, head->right);
}

/*
* Return true if the binary tree is BST (efficient version)
*/
bool isBST_e(struct node* node){
   return isBSTUtil(node, INT_MIN, INT_MAX);
}
bool isBSTUtil(struct node* node, int min, int max){
   if (NULL == node)
       return true;
   // false if this node violates the min/max constraint
   if (node->data < min || node->data > max)
       return false;
   // otherwise check the subtree recrusively
   return isBSTUtil(node->left, min, node->data) &&
           isBSTUtil(node->right, node->data+1, max);
}

bool isBSTUtil_1(struct node* node, int min, int max){
   if (node->left != NULL){
       if (node->left->data < min || !isBSTUtil_1(node->left, min, node->value))
          return false;
   }
   if (node->right != NULL){
       if (node->right->data > max || !isBSTUtil_1(node->right, node->value, max))
          return false;
   }
   return true;
}


void printLevelOrder(struct node *root) {
  if (!root) return;
  queue<BinaryTree*> nodesQueue;
  int nodesInCurrentLevel = 1;
  int nodesInNextLevel = 0;
  nodesQueue.push(root);
  while (!nodesQueue.empty()) {
    BinaryTree *currNode = nodesQueue.front();
    nodesQueue.pop();
    nodesInCurrentLevel--;
    if (currNode) {
      cout << currNode->data << " ";
      nodesQueue.push(currNode->left);
      nodesQueue.push(currNode->right);
      nodesInNextLevel += 2;
    }
    if (nodesInCurrentLevel == 0) {
      cout << endl;
      nodesInCurrentLevel = nodesInNextLevel;
      nodesInNextLevel = 0;
    }
  }
}

void getHD(Node* root, int hd, map<int, vector<int>> &hmap)
{
	if (root == nullptr)
		return;
	
	// store current node in hash map
	hmap[hd].push_back(root->val);

	getHD(root->left, hd-1, hmap);

	getHD(root->right, hd+1, hmap);
}

void printVerticalOrder(Node* root)
{
	map<int, vector<int>> hmap;
	getHD(root, 0, hmap);

	for (auto it = std::begin(hmap), en = std::end(hmap); it != en; ++it)
	{
		for (auto v : it->second)
			cout << v << " ";
		cout << endl;
	}
}
/*
What the interviewer probably meant is to pass a linked list down the tree and 
give each node a pointer to the list element that represents its column.

Just imagine the linked list to be infinite in both directions, you can easily extend it whenever you hit an end. 
Every item of the list is in turn a list of nodes:

function traverse(tree_node, list_node):
    if tree_node is NIL:
        return
    list_node.add(tree_node)
    traverse(tree_node.left, list_node.prev)
    traverse(tree_node.right, list_node.next)
*/
