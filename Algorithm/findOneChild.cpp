/*
  Q: Given binary tree, find those nodes which has only one child node
*/

#include <queue>

using namespace std;


typedef struct{
    node*   left;
    node*   right;
    int     data;
}node;

int findOneChild(node* root){
    if (root == NULL)
        return 0;

    int cnt = 0;
    queue<node*> tree_queue;
    tree_queue.push(root);

    while (!tree_queue.empty()){
        int child_cnt = 0;
        node* elem = tree_queue.front();

        if (elem->left != NULL){
            ++child_cnt;
            tree_queue.push(elem->left);
        }else if (elem->right != NULL){
            ++child_cnt;
            tree_queue.push(elem->right);
        }

        if (child_cnt == 1)
            ++cnt;

        tree_queue.pop();
    }

    return cnt;
}
