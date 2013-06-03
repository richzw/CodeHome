import MapReduce
import sys


mr = MapReduce.MapReduce()

# =============================
# Do not modify above this line

def mapper(record):
  matrix = record[0]
	row = record[1]
	col = record[2]
	if matrix == "a":
		mr.emit_intermediate(str(row)+str(",0"), record)
		mr.emit_intermediate(str(row)+str(",1"), record)
		mr.emit_intermediate(str(row)+str(",2"), record)
		mr.emit_intermediate(str(row)+str(",3"), record)
		mr.emit_intermediate(str(row)+str(",4"), record)
	elif matrix == "b":
		mr.emit_intermediate(str("0,")+str(col), record)
		mr.emit_intermediate(str("1,")+str(col), record)
		mr.emit_intermediate(str("2,")+str(col), record)
		mr.emit_intermediate(str("3,")+str(col), record)
		mr.emit_intermediate(str("4,")+str(col), record)


def reducer(key, list_of_values):
	total_sum = 0
	A = []
	B = []
	for val in list_of_values:
		if val[0] == "a":
			A.append(val)
		elif val[0] == "b":
			B.append(val)
	for a in A:
		col = a[2]
		for b in B:
			if b[1] == col:
				total_sum += a[3]*b[3]
	ret = [int(x) for x in key.split(",")]
	ret.append(total_sum)
	mr.emit(ret)

# Do not modify below this line
# =============================
if __name__ == '__main__':
  inputdata = open(sys.argv[1])
  mr.execute(inputdata, mapper, reducer)
