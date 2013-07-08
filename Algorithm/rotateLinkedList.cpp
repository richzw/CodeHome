/*
给定一个单向链表，设计一个算法实现链表向右旋转K个位置。K是非负的整数。这题看起来简单，可真编程实现有陷阱啰。

举例：

给定：1->2->3->4->5->6->null 并且K=3，则有：4->5->6->1->2->3->null。 
*/

/*
1.     当K=0时，怎么办？
2.     当K等于链表长度时，怎么办？
3.     当K大于链表长度时，怎么办？

除了K=0，显然，我们需要知道尾指针。那么，第一步，扫描链表得到尾指针tail和链表的长度M。如果M=0，完毕。
接下来，计算需要移动的步数得到新的头指针之前的节点，就是，(K-1) % M，假设指向这个节点的指针为p。
那么将tail的next指向head，然后将head指向p的next，然后将p的next指向null。

这个解法可能需要扫描链表两次。如果我们事先知道链表的长度M的话，也许我们可以用双指针法：

有两个指针，第一个指针先走 M-(K % M)-1 步，然后第一个和第二个指针一起走，直到第一个指针指到终点，这个时候：
1.     第二个指针所指的next节点设置为新的头节点
2.     将第二个指针所指节点的next指针指向null
3.     将第一个指针所指的节点的next指针指向旧的头节点
*/
typedef struct list_node{
  int data;
	list_node* next;
}list_node;

list_node* rotate_list(list_node* head, int k){
	//first of all, tranverse the list to get the number of list.
	list_node* tmp = head;
	list_node* tmp_tail = NULL;
	int length = 1;
	for (; tmp != NULL; tmp = tmp->next){
		++length;
		tmp_tail = tmp;
	}

	if (k == 0){
		return head;
	}else if (k == length){
		tmp_tail = NULL;
		tmp->next = head;
		return tmp;
	}else {
		list_node* new_head = head;
		for (int len = 1; len <= (k-1)%length; ++len){
			new_head = new_head->next;
		}
		new_head->next = NULL;
		tmp->next = head;

		return new_head;
	}
}
