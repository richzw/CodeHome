/×
  MaxVal - maximum value which will have non-zero frequency
  f[i] - frequency of value with index i, i = 1 .. MaxVal
  c[i] - cumulative frequency for index i (f[1] + f[2] + ... + f[i])
  tree[i] - sum of frequencies stored in BIT with index i (latter will be described what index means); 
            sometimes we will write tree frequency instead sum of frequencies stored in BIT
  num¯ - complement of integer num (integer where each binary digit is inverted: 0 -> 1; 1 -> 0 )

  idx is some index of BIT. r is a position in idx of the last digit 1 (from left to right) in binary notation.
  tree[idx] is sum of frequencies from index (idx - 2^r + 1) to index idx
*/

int read(int idx){
        int sum = 0;
        while (idx > 0){
                sum += tree[idx];
                idx -= (idx & -idx);
        }
        return sum;
}
void update(int idx ,int val){
        while (idx <= MaxVal){
                tree[idx] += val;
                idx += (idx & -idx);
        }
}
int readSingle(int idx){
  int sum = tree[idx]; // sum will be decreased
	if (idx > 0){ // special case
       		int z = idx - (idx & -idx); // make z first
        	idx--; // idx is no important any more, so instead y, you can use idx
        	while (idx != z){ // at some iteration idx (y) will become z
                		sum -= tree[idx]; 
// substruct tree frequency which is between y and "the same path"
                		idx -= (idx & -idx);
        	}
	}
	return sum;
}
int find(int cumFre){
        int idx = 0; // this var is result of function
        
        while ((bitMask != 0) && (idx < MaxVal)){ // nobody likes overflow :)
                int tIdx = idx + bitMask; // we make midpoint of interval
                if (cumFre == tree[tIdx]) // if it is equal, we just return idx
                        return tIdx;
                else if (cumFre > tree[tIdx]){ 
                        // if tree frequency "can fit" into cumFre,
                        // then include it
                        idx = tIdx; // update index 
                        cumFre -= tree[tIdx]; // set frequency for next loop 
                }
                bitMask >>= 1; // half current interval
        }
        if (cumFre != 0) // maybe given cumulative frequency doesn't exist
                return -1;
        else
                return idx;
}



// if in tree exists more than one index with a same
// cumulative frequency, this procedure will return the greater one
int findG(int cumFre){
        int idx = 0;
        
        while ((bitMask != 0) && (idx < MaxVal)){
                int tIdx = idx + bitMask;
                if (cumFre >= tree[tIdx]){ 
                        // if current cumulative frequency is equal to cumFre, 
                        // we are still looking for higher index (if exists)
                        idx = tIdx;
                        cumFre -= tree[tIdx];
                }
                bitMask >>= 1;
        }
        if (cumFre != 0)
                return -1;
        else
                return idx;
}
