//Construct a tree from Inorder and Level order traversals
/*
Input: Two arrays that represent Inorder
       and level order traversals of a 
       Binary Tree
in[]    = {4, 8, 10, 12, 14, 20, 22};
level[] = {20, 8, 22, 4, 12, 10, 14};
*/

int getIndex(){
       
       
}

int* getElements(){
       
       
}

TreeNode* buildTreeByInorderLevel(int in[], int level[], int start, int stop){
       if (in == NULL || level == NULL)
              return NULL;
       
       TreeNode* node = new TreeNode(level[start]);
       
       int index = getIndex(in, start, end);
       
       int* pLeft = getElements();
       int* pRight = getElements();
       
       node->left = buildTreeByInorderLevel();
       node->right = buildTreeByInorderLevel();
       
       delete[] pLeft;
       delete[] pRight;
       
       return node;
}
