/*
 Q: rebuild the binary tree, according to preorder and inorder.

*/

 typedef struct node{
     node*   left;
     node*   right;
     char        data;
 }node;

 /*
  * @func: rebuild the binary tree, according to preorder and inorder.
  * @params: pre {int*}, the preorder list of binary tree
  *          mid {int*}, the inorder list of binary tree
  *          cnt {int}, the element count of binary tree
  * @return: node*, the root of binary tree
  */
 node* build_binary_tree(const int* pre, const int* mid, const int cnt){
     if (pre == NULL || mid == NULL || cnt == 0)
             return NULL;

     node* root = new node;
     root->data = pre[0];

     int left_len = 0;
     while(mid[left_len] != root->data)
             ++left_len;
     int right_len = cnt - left_len - 1;

     root->left = build_binary_tree(pre+1, mid, left_len);
     root->right = build_binary_tree(pre+left_len+1, mid+left_len+1, right_len);

     return root;
 }

 void tranverse_tree_preorder(node* root){
     if (root == NULL)
             return;
     cout << root->data << " ";
     tranverse_tree_preorder(root->left);
     tranverse_tree_preorder(root->right);
 }

 void destroy_tree(node* root){
     if (root == NULL)
             return;
     destroy_tree(root->left);
     destroy_tree(root->right);
     delete root;
 }

 int main(){
     int preorder[] = {'A', 'B', 'D', 'J', 'K', 'E', 'L', 'C', 'F', 'H', 'M'};
     int inorder[] = {'J', 'D', 'K', 'B', 'E', 'L', 'A', 'F', 'C', 'M', 'H'};

     node* root = build_binary_tree(preorder, inorder, sizeof(inorder)/sizeof(inorder[0]));
     tranverse_tree_preorder(root);
     cout << endl;
 }

