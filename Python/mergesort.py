from array import Array
def pythonMergeSort(List):
    length = len(List)

    if length == 1:
        return List

    mid = length // 2
    leftList = pythonMergeSort(List[:mid])
    rightList = pythonMergeSort(List[mid:])

    sortList = combineSortedList(leftList, rightList)
    return sortList

# improvement version of merge sort
def mergeSort(List):
    length = len(List)
    array = Array(length)

    recvMergeSort(List, 0, length-1, array)

def recvMergeSort(List, left, right, tmpList):
    if right == left:
        return

    mid = (left + right)//2
    recvMergeSort(List, left, mid, tmpList)
    recvMergeSort(List, mid+1, right, tmpList)

    merge(List, left, mid+1, right+1, tmpList)

def merge(List, left, mid, right, tmpList):
    index = 0
    tmp_index = 0
    
    while left+index < mid and mid+index < right:
        if List[left+index] < List[right+index]:
            tmpList[tmp_index] = List[left+index]
        else:
            tmpList[tmp_index] = List[right+index]
        index += 1
        tmp_index += 1

    while left+index < mid:
        tmpList[tmp_index] = List[left+index]
        index += 1
        tmp_index += 1

    while mid+index < right:
        tmpList[tmp_index] = List[mid+index]
        index += 1
        tmp_index += 1

    #copy the element from tmplist into list
    for i in range(right-left):
        List[left+i] = tmpList[i]
