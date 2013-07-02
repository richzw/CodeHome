 /*
 In order for the nodes to be inserted at the correct place, we would need to output the NULL nodes using 
 some kind of sentinel (Here, we use ‘#‘ as the sentinel) as we are doing pre-order traversal.

Assume we have a binary tree below:

    _30_ 
   /    \    
  10    20
 /     /  \ 
50    45  35

Using pre-order traversal, the algorithm should write the following to a file:

30 10 50 # # # 20 45 # # 35 # #

 */
 
 #include <iostream>
 #include <string>
 using namespace std;

 typedef struct node {
     int data;
     node* left;
     node* right;
 }node;

 void writeBinaryTree(node* root, ostream &out){
     if (!root){
         out << "# ";
     }else{
         out << root->data << " ";
         writeBinaryTree(root->left, out);
         writeBinaryTree(root->right, out);
     }
 }

 bool is_number(const string& s){
     return !s.empty() && find_if(s.begin(), s.end(),
                     [](char c){return !isdigit(c);}) == s.end();
 }

 void readBinaryTree(node* root, ifstream &fin){
     string val;
     fin >> val;

     if(val == "#")
         return;
     else if (is_number(val)){
         node* pnode = new node();
         // how convert string to int in C
         // solution1, atoi
         // solution2, sscanf
         // solution3, strtol
         pnode->data = strtol(val, &val, 10);
         readBinaryTree(pnode->left, fin);
         readBinaryTree(pnode->right, fin);
     }
 }
