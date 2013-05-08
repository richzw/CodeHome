/*
  An XOR linked list compresses the same information into one address field 
  by storing the bitwise XOR of the address for previous and the address for next in one field:
 ...  A        B         C         D         E  ...
         <–>  A⊕C  <->  B⊕D  <->  C⊕E  <->

More:
     Addition Link List
     Subtraction Link List
*/

 struct xorlist{
    int data;
    struct xorlist* next;
};


/* @func: create xorlist according to input array.
 * @params: an array that need to transform to xorlist.
 * @ret: the header of xor list
 */
xorlist* create_xorlist(int arr[], int count){
    int index = 0;
    if (NULL == arr)
         return NULL;

    xorlist* head = NULL;
    xorlist* prevnode = NULL;
    xorlist* node = NULL;
    xorlist* nextnode = NULL;

    head = node = (xorlist*)malloc(sizeof(xorlist));
    node->data = arr[index];
    --count;

    while (count){
        ++index;
        nextnode = (xorlist*)malloc(sizeof(xorlist));
        nextnode->data = arr[index];
        node->next = (xorlist*)((int)prevnode ^ (int)nextnode);
        prevnode = node;
        node = nextnode;
        --count;
    };

    node->next = prevnode;

    return head;
}
 /* @func: delete the xorlist
 * @params: the header of xorlist that need to be deleted
 *
 */
void destroy_xorlist(xorlist* head){
    if (NULL == head)
        return;
    xorlist* prevnode = NULL;
    xorlist* node = NULL;
    xorlist* nextnode = NULL;

    node = head;
    while (nextnode = (xorlist*)((int)node->next ^ (int)prevnode)){
        free(prevnode);
        prevnode = node;
        node = nextnode;
    }
    free(node);
    free(prevnode);
}

/* @func: insert one element into xorlist
 * @params: the new xorlist element
 * @ret: the header of the xorlist
 */
xorlist* insert_xorlist(xorlist* head, int value){
    if (NULL == head)
        return NULL;
    xorlist* prevnode = NULL;
    xorlist* node = NULL;
    xorlist* nextnode = NULL;

    node = head;
    while (nextnode = (xorlist*)((int)(node->next)^(int)prevnode)){
        prevnode = node;
        node = nextnode;
    }
    xorlist* tail = (xorlist*)malloc(sizeof(xorlist));
    node->next = (xorlist*)((int)prevnode ^ (int)tail);
    tail->data = value;
    tail->next = node; //namely xor zero

    return head;
}

/* @func: delete one element from xorlist
 * @params: the value of element that should be deleted
 * @ret: the header of the xorlist
 */
xorlist* delete_xorlist(xorlist* head, int value){
    if (NULL == head)
        return NULL;
     xorlist* prevnode = NULL;
     xorlist* node = NULL;
     xorlist* nextnode = NULL;

     node = head;
     while (nextnode = (xorlist*)((int)node->next^(int)prevnode)){
         if (value == node->data){
             if (node == head){
                 nextnode->next = (xorlist*)((int)node ^ (int)nextnode->next);
                 head = nextnode;
             } else {
                 prevnode->next = (xorlist*)(((int)node^(int)prevnode->next)^(int)nextnode);
                 nextnode->next = (xorlist*)((int)prevnode ^ ((int)node^(int)nextnode->next));
             }

             free(node);
             break;
         }
         prevnode = node;
         node = nextnode;
     }
     //delete the tail node
     if (node->data == value){
         prevnode->next = (xorlist*)((int)node ^ (int)prevnode->next);
         free(node);
     }
     return head;
 }

 /* @func: tranverse the xorlist.
  * @params: the header of xorlist.
  * @ret: return the header of xorlist.
  */
 xorlist* tranverse_xorlist(xorlist* head){
     if (NULL == head)
         return NULL;
     xorlist* prevnode = NULL;
     xorlist* node = NULL;
     xorlist* nextnode = NULL;

     node = head;
     while (nextnode = (xorlist*)((int)node->next^(int)prevnode)){
         printf(" %d ", node->data);
         prevnode = node;
         node = nextnode;
     }
     printf(" %d \n", node->data);
     return head;
 }

 int main(){
     int array[] = {3, 4, 8, 9, 1, 7, 5, 6, 11};
     xorlist* head = create_xorlist(array,  sizeof(array)/sizeof(array[0]));
     head = tranverse_xorlist(head);
     head = insert_xorlist(head, 2);
     head = tranverse_xorlist(head);
     head = delete_xorlist(head, 1);
     head = tranverse_xorlist(head);

     destroy_xorlist(head);
     return 0;
 }
