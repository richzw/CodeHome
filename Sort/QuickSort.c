/*

Cutoff to insertion sort for small subarrays
Partitioning scheme: 3-way partitioning
Partitioning item.
- small array: middle entry
- medium arrays: median of 3
- large arrays: Tukey's ninther
          Median of median of 3 samples, each of 3 entries.
          - approximates the median of 9
          - uses at most 12 compares.
*/

// Rule: shuffling is needed for performance guarantee
// Reason:Quick sort performs poorly on a partially sorted data due to the above said pivot choosing logic. 
//However, if the input set is completely shuffled, the probability of a pivot being chosen ineffective is the least.
//That is the reason Shuffle makes it faster if not ideal.
