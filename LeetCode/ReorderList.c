/* Reorder List
Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
*/

class Solution {
public:
    void reorderList(ListNode *head) {
        if (head == NULL || head->next == NULL || head->next->next == NULL)
            return ;
            
    	// advance to the middle node
    	ListNode* fast = head;
    	ListNode* slow = head;
    	while (fast != NULL && fast->next != NULL && fast->next->next != NULL){
    		fast = fast->next->next;
    		slow = slow->next;
    	}
    
    	// split list
    	ListNode* second = slow->next;
    	slow->next = NULL;
    	
    	// reverse the second half list
    	ListNode* pre = second;
    	ListNode* cur = second->next;
    	while (cur != NULL){
    		ListNode* tmp = cur->next;
    		cur->next = pre;
    		pre = cur;
    		cur = tmp;
    	}
    	second->next = NULL;
    
    	// merge those two lists
    	ListNode* p1 = head;
    	ListNode* p2 = pre;
    	while (p2 != NULL) {
    		ListNode* tmp1 = p1->next;
    		ListNode* tmp2 = p2->next;
    
    		p1->next = p2;
    		p2->next = tmp1;
    
    		p1 = tmp1;
    		p2 = tmp2;
    	}        
        
    }
};
