/*
copy every node, i.e., duplicate every node, and insert it to the list
copy random pointers for all newly created nodes
break the list to two
*/
typedef struct randomNode{
	int value;
	randomNode *next, *random;
	randomNode(int x):value(x) {}
}randomNode;

randomNode* CopyRandomList(randomNode* head){
	if (head == NULL)
		return NULL;

	// copy the random node and link it to the original list
	randomNode* thead = head;
	while (thead != NULL){
		randomNode* tmp = new randomNode(thead->value);
		tmp->next = thead->next;
		thead->next = tmp;
		thead = tmp->next;
	}

	// assigned the random pointer
	thead = head;
	while (thead){
		if (thead->random)
			thead->next->random = thead->random->next;
		thead = thead->next->next;
	}

	// recover the original list
	thead = head->next;
	while (thead && head){
		head->next = thead->next;
		thead->next = head->next->next;
		head = head->next;
		thead = thead->next;
	}

	return thead;
}

// better solution: HashMap
randomNode* CopyRandomList_V1(randomNode* lhead){
	if (lhead == NULL)
		return NULL;

	unordered_map<randomNode*, randomNode*> map;

	randomNode* head = lhead;
	randomNode* newhead = new randomNode(head->value);
	if (newhead == NULL)
		return NULL;

	randomNode* thead = newhead;
	map.insert(make_pair<randomNode*, randomNode*>(head, thead));

	head = head->next;
	while(head){
		randomNode* pnode = new randomNode(head->value);
		map.insert(make_pair<randomNode*, randomNode*>(head, pnode));
		thead->next = pnode;
		head = head->next;
		thead = thead->next;
	}

	// assign random pointer
	while (lhead){
		if (lhead->random)
			newhead->random = map[lhead->random];
		else
			newhead->random = NULL;

		lhead = lhead->next;
		newhead = newhead->next;
	}

	return newhead;
}
