// Merge sort for List
void splitList(LNode* source, LNode** pfrontList, LNode** pbackList) {
	if (source == NULL || source->next == NULL) {
		*pfrontList = source;
		*pbackList = NULL;
	}
	else
	{
		LNode* fast = source;
		LNode* slow = source;

		//while (fast != NULL && fast->next != NULL) {
		//	fast = fast->next->next;
		//	slow = slow->next;
		//}

		// Fixme: advance `fast` first, then advance `slow` node
		while (fast != NULL) {
			fast = fast->next;
			if (fast != NULL) {
				fast = fast->next;
				slow = slow->next;
			}
		}

		*pfrontList = source;
		*pbackList = slow->next;

		// break the source list
		slow->next = NULL;
	}
}

LNode* sortMerge(LNode* pfrontList, LNode* pbackList) {
	if (pfrontList == NULL)
		return pbackList;
	else if (pbackList == NULL)
		return pfrontList;

	LNode* ret = NULL;

	if (pfrontList->val <= pbackList->val) {
		ret = pfrontList;
		ret->next = sortMerge(pfrontList->next, pbackList);
	}
	else
	{
		ret = pbackList;
		ret->next = sortMerge(pfrontList, pbackList->next);
	}

	return ret;
}

void mergeSortForList(LNode** phead) {
	LNode* head = *phead;
	LNode* a;
	LNode* b;

	if (head == NULL || head->next == NULL)
		return;

	splitList(head, &a, &b);
	
	mergeSortForList(&a);
	mergeSortForList(&b);

	*phead = sortMerge(a, b);
}

///////////////////////////////////////////////////////////////////////////////////

class Solution {
public:
    ListNode *sortList(ListNode *head) {
        if (head == NULL)
            return NULL;
        else if (head->next == NULL)
            return head;
        
        return MergeSortRecur(head);
    }
    
    ListNode* MergeSortRecur(ListNode* head){
        if (head == NULL)
            return NULL;
        else if (head->next == NULL)
            return head;
            
        ListNode* pfront = NULL;
        ListNode* pback = NULL;
        FrontBackSplit(head, &pfront, &pback);
        
        return SortedMerge(MergeSortRecur(pfront), MergeSortRecur(pback));
    }
    
    ListNode* SortedMerge(ListNode* a, ListNode* b){
        if (a == NULL && b == NULL)
            return NULL;
        else if (a == NULL && b != NULL)
            return b;
        else if (a != NULL && b == NULL)
            return a;
        
        ListNode dummy(0);
        ListNode* pdummy = &dummy;
        pdummy->next = NULL;
        
        while(true){
            if (a == NULL){
                pdummy->next = b;
                break;
            }else if (b == NULL){
                pdummy->next = a;
                break;
            }else if (a->val <= b->val){
                pdummy->next = a; 
                a = a->next;
            }else if (a->val > b->val){
                pdummy->next = b; 
                b = b->next;
            }
            pdummy = pdummy->next;
        }
        return dummy.next;
    }
    
    void FrontBackSplit(ListNode* source, ListNode** frontRef, ListNode** backRef){
    	int list_len = 0;
    	int list_index = 0;
    	ListNode* current = source;
     
    	*frontRef = source;
    	while (current->next != NULL){
    		++list_len;
    		current = current->next;
    	}
    	++list_len;
     
    	if (list_len % 2){
    		list_len = list_len/2 + 1;
    	}else {
    		list_len /= 2;
    	}
     
    	if (list_len < 1){
    		*backRef = NULL;
    	}else {
    			current = source;
    			while (current->next != NULL){
    					++list_index;
    					if (list_index == list_len){
    							*backRef = current->next;
    							current->next = NULL;
    							return;
    					}else
    							current = current->next;
    			}
    	}
    }
};
