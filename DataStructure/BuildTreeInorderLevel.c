//Construct a tree from Inorder and Level order traversals
/*
Input: Two arrays that represent Inorder
       and level order traversals of a 
       Binary Tree
in[]    = {4, 8, 10, 12, 14, 20, 22};
level[] = {20, 8, 22, 4, 12, 10, 14};
*/

int getIndex(int target, int in[], int start, int stop){
       if (in == NULL)
              return 0;
       
       for (int index = start; index < stop; ++index){
              if (in[index] == target)
                     return index;
       }
       
       return -1;
}

int* getElements(int in[], int left, int right){
       int pnew = new int[right-left+1];
       for (int index = left; index < right; ++index)
              pnew[index-left] = in[index];
       
       return pnew;
}

TreeNode* buildTreeByInorderLevel(int in[], int level[], int start, int stop){
       if (in == NULL || level == NULL)
              return NULL;
       
       TreeNode* node = new TreeNode(level[start]);
       
       int index = getIndex(node->data, in, start, stop);
       
       int* pLeft = getElements(in, start, index-1);
       int* pRight = getElements(in, index+1, stop);
       
       node->left = buildTreeByInorderLevel(pLeft, level, start, index-1);
       node->right = buildTreeByInorderLevel(pRight, level, index+1, stop);
       
       delete[] pLeft;
       delete[] pRight;
       
       return node;
}
