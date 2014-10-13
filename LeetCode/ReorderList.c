/* Reorder List
Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
*/

list_node* reorder_list(list_node* head){
	if (head == NULL)
		return NULL;

	// advance to the middle node
	list_node* fast = head;
	list_node* slow = head;
	while (fast != NULL && fast->next != NULL && fast->next->next != NULL){
		fast = fast->next->next;
		slow = slow->next;
	}

	if (slow == NULL)
		return NULL;

	// reverse the second half list
	list_node* second = slow->next;
	list_node* pre = second;
	list_node* cur = second->next;
	while (cur != NULL){
		list_node* tmp = cur->next;
		cur->next = pre;
		pre = cur;
		cur = tmp;
	}
	second->next = NULL;

	// merge those two list
	list_node* p1 = head;
	list_node* p2 = pre;
	while (p2 != NULL) {
		list_node* tmp1 = p1->next;
		list_node* tmp2 = p2->next;

		p1->next = p2;
		p2->next = tmp1;

		p1 = tmp1;
		p2 = tmp2;
	}
}
