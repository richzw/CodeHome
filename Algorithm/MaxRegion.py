'''
Given a matrix of integers and coordinates of a rectangular region within the matrix, 
find the sum of numbers falling inside the rectangle.
'''
# O(MN)
def matrixRegionSum1(matrix, A, D):
    if len(matrix)==0:
        return totalSum=0
    for i in range(A[0], D[0]+1):
        for j in range(A[1], D[1]+1):
            totalSum+=matrix[i][j]
    return totalSum 
