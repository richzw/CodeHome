/*
Clone linked list with random pointer
*/
typedef struct Node{
	string item;
	Node next;
	Node random;
}Node;

Node* copy_list(Node* head){
	// assert(head != NULL);
	Node* tmp = head;

	// insert nodes between two nodes of orginal list
	while (tmp->next){
		Node* node = new Node;
		node->item = tmp->item;
		node->next = tmp->next;
		tmp->next = node;
		tmp = tmp->next->next;
	}
	// copy the tail
	Node* node = new Node;
	node->item = tmp->item;
	tmp->next = node;
	node->next = NULL;

	// assign the random pointer 
	tmp = head;
	while (tmp->next){
		tmp->next->random = tmp->random->next;
		tmp = tmp->next->next;
	}

	// split the new list from the original list
	tmp = head;
	Node* new_head = tmp->next;
	Node* h = new_head;
	while (tmp->next->next){
		tmp->next = tmp->next->next;
		h->next = tmp->next->next;
		tmp = tmp->next;
		h = h->next;
	}
	tmp->next = NULL;
	h->next = NULL;

	return new_head;
}
