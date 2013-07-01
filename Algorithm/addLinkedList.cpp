//Q:两个单链表，每个节点存储一个0-9的数字，那么一个单链表就表示一个大数。 从高位到低位存，
//即表头对应的是这个大数的最高位。两个链表的长度相等， 我们要返回一个新的单链表，是这两个输入链表代表的数的和。
//我们不能使用递归， 不能使用额外的存储空间，即空间复杂度是O(1)。只遍历输入链表一次， 输出链表也是单链表(没有前向指针)。

/*
输入链表1： 1 2 3
输入链表2： 1 2 8
输出链表：  2 4 
两个指针：    p q

输入链表1： 1 2 3 4 5
输入链表2： 1 7 6 5 9
输出链表：  2 9 9 9
两个指针：  p       q
*/

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
