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
