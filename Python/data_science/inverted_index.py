import MapReduce
import sys


mr = MapReduce.MapReduce()

# =============================
# Do not modify above this line

def remove_duplicate(_list):
  return list(set(_list))

def mapper(record):
    key = record[0]
    value = record[1]
    words = value.split()
    words_non_dup = remove_duplicate(words)
    for w in words_non_dup:
      mr.emit_intermediate(w, key)

def reducer(key, list_of_values):
    #total = 0
    #for v in list_of_values:
    #  total += v
    mr.emit((key, list_of_values))

# Do not modify below this line
# =============================
if __name__ == '__main__':
  inputdata = open(sys.argv[1])
  mr.execute(inputdata, mapper, reducer)
