def mergeSortList(List):
    if List is None:
        return None

    leftList, rightList = _splitList(List)

    mergeSortList(leftList)
    mergeSortList(rightList)

    theList = _sortList(leftList, rightList)
    return theList

def _splitList(List):
    fast = List
    mid = List

    if fast is not None:
        fast = fast.next
        if fast is not None:
            fast = fast.next
            mid = mid.next
    
    rightList = mid.next
    mid.next = None
    return List, rightList

def _sortList(leftList, rightList):
    if leftList is None or rightList is None:
        return None

    newList = ListNode()
    newList.next = None
    if leftList is not None and rightList is not None:
        if leftList.data < rightList.data:
            newList.next = leftList
            leftList = leftList.next
        else:
            newList.next = rightList
            rightList = rightList.next
        newList = newList.next
    
    if leftList.next is not None:
        newList.next = leftList
    if rightList.next is not None:
        newList.next = rightList

    return newList.next
