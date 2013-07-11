# Map-reduce matrix
# the new element of matrix is the mean value of 8 neighbor nodes of the original matrix

# input: element is the key value pair of matrix
#        type:    [row, column, value, totle_row, totle_column]
def mapper(elem):
    row = elem[0]
    col = elem[1]
    val = elem[2]
    t_row = elem[3]
    t_col = elem[4]

    if (row == 0):
        if (col == 0):
            mr.emit_intermediate(str("0,1"), val)
            mr.emit_intermediate(str("1,0"), val)
            mr.emit_intermediate(str("1,1"), val)
        elif (col == t_col - 1):
            mr.emit_intermediate(str("0,")+str(t_col-2), val)
            mr.emit_intermediate(str("1,")+str(t_col-1), val)
            mr.emit_intermediate(str("1,")+str(t_col-2), val)
        else:
            mr.emit_intermediate(str("0,")+str(col-1), val)
            mr.emit_intermediate(str("0,")+str(col+1), val)
            mr.emit_intermediate(str("1,")+str(col), val)
            mr.emit_intermediate(str("1,")+str(col-1), val)
            mr.emit_intermediate(str("1,")+str(col+1), val)
    elif (row == t_row - 1):
        if (col == 0):
            mr.emit_intermediate(str(row-1)+str(col), val)
            mr.emit_intermediate(str(row)+str(col+1), val)
            mr.emit_intermediate(str(row-1)+str(col+1), val)
        elif (col == t_col - 1)
            mr.emit_intermediate(str(row)+str(col-1), val)
            mr.emit_intermediate(str(row-1)+str(col), val)
            mr.emit_intermediate(str(row-1)+str(col-1), val)
        else:
            mr.emit_intermediate(str(row)+str(col-1), val)
            mr.emit_intermediate(str(row)+str(col+1), val)
            mr.emit_intermediate(str(row-1)+str(col), val)
            mr.emit_intermediate(str(row-1)+str(col-1), val)
            mr.emit_intermediate(str(row-1)+str(col+1), val)
    else:
            mr.emit_intermediate(str(row-1)+str(col-1), val)
            mr.emit_intermediate(str(row-1)+str(col), val)
            mr.emit_intermediate(str(row-1)+str(col+1), val)
            mr.emit_intermediate(str(row)+str(col-1), val)
            mr.emit_intermediate(str(row)+str(col+1), val)
            mr.emit_intermediate(str(row+1)+str(col), val)
            mr.emit_intermediate(str(row+1)+str(col-1), val)
            mr.emit_intermediate(str(row+1)+str(col+1), val)

def reducer(key, list_of_values):
    arithmetic_mean = float(sum(list_of_values))/len(list_of_values)
    ret = [int(x) for x in key.split(",")]
    ret.append(arithmetic_mean)
    mr.emit(ret)

