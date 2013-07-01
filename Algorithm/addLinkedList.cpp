struct node{
    int data;
    node* next;
};

node* addLinkedList(node* list1, node* list2){
    if (list1 == NULL || list2 == NULL)
        return NULL;

    node *ret = NULL, *cur = NULL, *pre = NULL;
    node *q = NULL; // record the last node which is not 9

    int top_digit = list1->data + list2->data;
    if (top_digit >= 9){
        ret = new node();
        pre = new node();

        pre->data = top_digit % 10;
        ret->next = pre;
        if (top_digit > 9){
            ret->data = 1;
            q = pre;
        }else{
            ret->data = 0;
            q = ret;
        }
    }else { // less than 9
        ret = new node();
        ret->data = top_digit;
        pre = q = ret;
    }

    // handling the rest of list1 and list2
    while ((list1 = list1->next) && (list2 = list2->next)){
        cur = new node();
        pre->next = cur;
        int part_sum = list1->data + list2->data;
        cur->data = part_sum % 10;

        if (part_sum > 9){
            q->data += 1;
            for (q; q != cur; q= q->next)
                q->data = 0;          // set the node to 0 between q and cur
        } else if (part_sum < 9){
            q = cur;
        }

        pre = cur;
    }

    if (ret->data == 0)
        ret = ret->next;

    return ret;
}
