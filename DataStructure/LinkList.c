//
struct node {
  struct node* next;
  int data;
};
 
void Push(struct node** headRef, int newData){
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	
	new_node->data = newData;
	new_node->next = (*headRef);
	(*headRef) = new_node;
}
 
int Pop(struct node** headRef){
	struct node* current = *headRef;
 
	if (*current != NULL){
		headRef = &((*headRef)->next);
		free(current);
		return current->data;
	}else{
		return 0;
	}
}
 
struct node* BuildWithLocalRef(int listArr[], int listLen){
	struct node* head = NULL;
	struct node** last_ptr_ref = &head;
	int arr_index = 0;
	
	for (arr_index = 0; arr_index < listLen; ++arr_index){
		Push(last_ptr_ref, listArr[arr_index]);
		last_ptr_ref = &((*last_ptr_ref)->next);
	}
 
	return head;
}
 
void DeleteList(struct node** headRef){
	struct node* current = (*headRef);
	struct node* next;
 
	while(current != NULL){
		next = current->next;
		free(current);
		current = next;
	}
 
	*headRef = NULL;
}
 
void DeleteListV1(struct node** headRef){
	struct node** head = (headRef);
 
	while(*head != NULL){
		free(*head);
		head = &((*head)->next);
	}
 
	*headRef = NULL;
}
 
typedef bool (* Remove_fn)(struct node const * v);
struct node* Remove_if(struct node** head, Remove_fn rm){
	for (node** current = head; *current; ){
		struct node* entry = *current;
		if (rm(entry)){
			*current = entry->next;
			free(entry);
		}else{
			current = &(entry->next);
		}
	}
}
 
/*
 * @func: insert one new node into the ordered link list
 */
void SortedInsert1(struct node** headRef, struct node* newNode){
	if (NULL == *headRef || (*headRef)->data > newNode->data){
		newNode->next = *headRef;
		*headRef = newNode;
	}else{
		struct node* current = *headRef;
		while(current->next != NULL && current->next->data < newNode->data){
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
}
 
void SortedInsert2(struct node** headRef, struct node* newNode){
	struct node** current_ref = headRef;
	
	if (*current_ref != NULL && (*current_ref)->data < newNode->data){
		current_ref = &((*current_ref)->next);
	}
	newNode->next = *current_ref;
	*current_ref = newNode;      //key point
}
 
/*
 * @func: Given a list, change it to be in sorted order.
 */
void InsertSort(struct node** headRef){
	struct node* result = NULL;
	struct node* current = *headRef;
	struct node* next;
 
	while (current != NULL){
		next = current->next;
		SortedInsert1(&result, current);
		current = next;
	}
 
	*headRef = result;
}
 
/*
 * @func: append one link list to another link list.
 */
void Append(struct node** aRef, struct node** bRef){
	struct node* current = *aRef;
 
	if (NULL == *aRef){ //special case if aRef is empty.
		*aRef = *bRef;
	}else{
		while(current->next != NULL){
			current = current->next;
		}
		current->next = *bRef;
	}
	
	*bRef = NULL;
}
 
/*
 * @func: split the given list into front and back halves.
 *        if the length is odd, the extra node should go in the front list.
 */
void FrontBackSplit1(struct node* source, struct node** frontRef, struct node** backRef){
	int list_len = 0;
	int list_index = 0;
	struct node* current = source;
 
	*frontRef = source;
	while (current->next != NULL){
		++list_len;
		current = current->next;
	}
 
	if (list_len % 2){
		list_len = list_len/2 + 1;
	}else {
		list_len /= 2;
	}
 
	if (len < 2){
		*backRef = NULL;
	}else {
			current = source;
			while (current->next != NULL){
					++list_index;
					if (list_index == list_len){
							*backRef = current;
							return;
					}else
							current = current->next;
			}
	}
}
 
/*
 * @func: another solution, two pointers, one is fast and another is slow.
 */
void FrontBackSplit2(struct node* source, struct node** frontRef, struct node** backRef){
	struct node* fast = source;
	struct ndoe* slow = source;
 
	*frontRef = source;
	if (NULL == source || NULL == source->next){
		*backRef = NULL;
	}else{
		fast = source->next;
 
		while (fast != NULL){
			fast = fast->next;
			if (fast->next != NULL){
				slow = slow->next;
				fast = fast->next;
			}
		}
		
		*backRef = slow->next;
		slow->next = NULL;
	}
}
 
/*
 * @func: Remove duplicates from a sorted list.
 */
void RemoveDuplicates(struct node* head){
	
}
 
int main(){
	int list_array[] = {2, 3, 4, 5, 8, 1, 9};
	
	struct node* list_head = BuildWithLocalRef(list_array, sizeof(list_array)/sizeof(list_array[0]));
	DeleteListV1(&list_head);
 
	return 0;
}
