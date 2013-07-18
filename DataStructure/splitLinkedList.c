/*
Q: 给一个链表，将它分拆成两个链表，一个是前半部分，另一个是后半部分。如果有奇数个节点，
多出的节点放到第一个由前半部分节点构成的链表。 
比如，对于链表{1, 3, 5, 7, 11}，应该输出链表{1, 3, 5}和{7, 11}。
*/

typedef struct node {
  int data;
  node* next;
}node;

// method 1: compute the length of linked list
void split_list(node* head, node** last_list)
{
  int len = 0;
  for (node* elem = head; elem != NULL; elem= elem->next, ++len);
  
  node* tail = head;
  for (int i = 1; i < (len+1)/2; tail = tail->next);
  *last_list = tail->next;
  tail->next = NULL;
}

// method2: two pointers, one is slow, the other is faster.
void split_list(node* head, node** last_list)
{
  node* slow = head;
  node* fast = head;
  
  while (slow->next != NULL && fast->next->next != NULL){
    slow = slow->next;
    fast = fast->next->next;
  }
  *last_node = slow->next;
  slow->next = NULL;
}
