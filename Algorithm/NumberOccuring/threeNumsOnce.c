//Q: In a sequence of length n, where n=2k+3, that is there are k unique numbers appeared twice and three numbers appeared only once.

/*
1)	If there is one number appeared only once, we can apply XOR to the sequence to find it.
2)	If there are two, we can first apply XOR to the sequence, then separate the sequence into 2 parts by one bit of the result that is 1, and again apply XOR to the 2 parts, and we will find the answer.
Method A: Bloom filter
Create two Bloom filters. The first (A) contains numbers that have been found at least one, and the second (B) contains numbers that have been found twice.
A = empty
B = empty

foreach x in the list
  if x in A
    add x to B
  else
    add x to A

foreach x in the list
  if x in A
    if !(x in B)
      print x

method B: bit xor operation
We need two integers for each bit of the numbers (e.g. 32 bits). For each number, if that bit is zero, XOR the first integer with it. otherwise, XOR the second integer with it.
Also, keep count of how many times you find a 1 or 0 in each position (we only need to check if this is even or odd, so keep a boolean).

After iterating through, our pairs of integers will be one of the following. The first number here represents an even count, the second an odd.
0, a^b^c
a^b, c
a^c, b
b^c, a

For each pair, check the even count integer. If it is zero, then we know the other integer is a^b^c, since no two of our results will be equal.
Otherwise, we've found a value at the odd count integer.
*/
void find3(int list[], int len) {
	int xors[32][2] = {0};
	bool counts[32] = {false};
    for (int j = 0; j < len; ++j) {
        for (int i = 0; i < 32; i++) {
            xors[i][(list[j] & (1 << i)) >> i] ^= list[j];
            counts[i] ^= ((list[j] & (1 << i)) == (1 << i));
        }
    }

    int ret[3] = {0};
    int found = 0;
    for (int i = 0; i < 32; i++) {
        int oddCount = xors[i][counts[i] ? 1 : 0];
        int evenCount = xors[i][counts[i] ? 0 : 1];
        if (evenCount != 0) { // avoid the 0, a^b^c case.
            if (found == 0) {
                ret[0] = oddCount;// a
                ret[2] = evenCount;// b^c for now
                found++;
            } else if (found == 1 && ret[0] != oddCount) {
                ret[1] = oddCount;// b
                ret[2] ^= oddCount;// (b^c)^b == c
                break;
            }
        }
    }
}
