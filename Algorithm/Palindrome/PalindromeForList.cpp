// by stack
bool isPalindromeList_stack(list_node* head){
	list_node* fast = head;
	list_node* slow = head;

	stack<int> list_stack;

	// find the mid node of the list
	while (fast != NULL && fast->next != NULL){
		list_stack.push(slow->data);
		slow = slow->next;
		fast = fast->next->next;
	}

	// odd number case
	if (fast != NULL)
		slow = slow->next;

	while (slow != NULL){
		if ( slow->data != list_stack.top())
			return false;
		slow = slow->next;
		list_stack.pop();
	}

	return true;
}

// recursive method
int getListLength(list_node* head){
	int len = 0;

	while (head != NULL){
		len++;
		head = head->next;
	}

	return len;
}

bool isPalindrome_recur(list_node* head, list_node*& tail, int len){
	if (len == 0 || head == NULL)
		return true;
	if (len == 1){  // odd count
		tail = head->next;
		return true;
	}
	if (len == 2){ // even count
		tail = head->next->next;
		return head->data == head->next->data;
	}

	bool bret = isPalindrome_recur(head->next, tail, len-2);

	if (!bret || head->data != tail->data)
		return false;
	else{
		tail = tail->next;
		return true;
	}
}

bool isPalindromeList(list_node* head){
	int len = getListLength(head);

	list_node* tail = NULL;
	return isPalindrome_recur(head, tail, len);
}
