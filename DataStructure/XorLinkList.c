/*
  An XOR linked list compresses the same information into one address field 
  by storing the bitwise XOR of the address for previous and the address for next in one field:
 ...  A        B         C         D         E  ...
         <–>  A⊕C  <->  B⊕D  <->  C⊕E  <->

More:
     Addition Link List
     Subtraction Link List
*/

//互斥或連結串列結點結構
typedef struct XorNode {
    char data;
    struct XorNode *LRPtr;
}
XorNode, *XorPointer;
//互斥或指標雙向連結串列結構
typedef struct XorLinkedList {
    XorPointer left, right;
}
XorLinkedList;

//互斥或操作
XorPointer xor(XorPointer a, XorPointer b) {
    return (XorPointer)((unsigned long)(a) ^ (unsigned long)(b));
}

//建立互斥或雙向連結串列
void createXorLinkedList(XorLinkedList *list) {
    char ch;
    XorPointer lastNode = NULL;
    int isFirstNode = 1;
    while ((ch = getchar()) != '\n') {
        XorPointer newNode = (XorPointer) malloc(sizeof(XorNode));
        newNode -> data = ch;
        newNode -> LRPtr = NULL;
        if (lastNode) {
            newNode -> LRPtr = xor(lastNode, NULL);
            lastNode -> LRPtr = xor(xor(lastNode -> LRPtr, NULL), newNode);
        }
        lastNode = newNode;
        if (isFirstNode) {
            isFirstNode = 0;
            list -> left = newNode;
        }
    }
    list -> right = lastNode;
}

//按任意方向依次輸出各結點值
void print(XorPointer a, XorPointer b) {
    XorPointer nullFirst = a == NULL ? a : b;
    XorPointer nonNullFirst = a != NULL ? a : b;
    XorPointer tmp = NULL;
    do {
        printf("%c ", nonNullFirst -> data);
        tmp = nonNullFirst;
        nonNullFirst = xor(nullFirst, nonNullFirst -> LRPtr);
        nullFirst = tmp;
    } while (nonNullFirst != NULL);
}

//在第i個結點之前插入一個結點
void XorLinkedListInsert(XorLinkedList *list, int pos, char data) {
    XorPointer node = list -> left, tmp = NULL;
    XorPointer last = NULL;
    XorPointer newNode = NULL;
    int i = 1;
    while (i < pos && node != NULL) {
        tmp = node;
        node = xor(last, node -> LRPtr);
        last = tmp;
        i++;
    }
    newNode = (XorPointer) malloc(sizeof(XorNode));
    newNode -> data = data;
    newNode -> LRPtr = xor(last, node);
    if (node != NULL) {
        node -> LRPtr = xor(newNode, xor(last, node -> LRPtr));
    }
    if (last != NULL) {
        last -> LRPtr = xor(xor(last -> LRPtr, node), newNode);
    }
    if (pos == 1) {
        list -> left = newNode;
    }
}
// 刪除第i個結點
void XorLinkedListDelete(XorLinkedList *list, int pos) {
    XorPointer node = list -> left, last = NULL, next = NULL, tmp = NULL;
    int i = 1;
    while (i < pos && node != NULL) {
        i++;
        tmp = node;
        node = xor(last, node -> LRPtr);
        last = tmp;
    }
    next = xor(last, node -> LRPtr);
    if (last != NULL) {
        last -> LRPtr = xor(xor(last -> LRPtr, node), next);
    }
    if (next != NULL) {
        next -> LRPtr = xor(last, xor(node, next -> LRPtr));
    } else {
        list -> right = last; //删除了最后一个结点
    }
    if (pos == 1) {
        list -> left = next;
    }
    free(node);
}
