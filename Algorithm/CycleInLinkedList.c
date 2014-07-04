/*
Detect cycle in a linked list.
*/
typedef struct ListNode{
	int val;
	ListNode* next;
}ListNode;

bool hasCircle(ListNode* head, ListNode* &encounter){
	// assert head != NULL
	ListNode* fast = head;
	ListNode* slow = head;

	while(fast && fast->next){
		fast = fast->next->next;
		slow = slow->next;

		if (fast == slow){
			encounter = fast
			return true;
		}
	}

	encounter = NULL;
	return false;
}

ListNode* findEntry(ListNode* head, ListNode* encounter)){
	// assert head != NULL && encounter != NULL
	ListNode* cur = head;

	while (cur != encounter){
		cur = cur->next;
		encounter = encounter->next;
	}

	return cur;
}
