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

// shuffling is needed for performance guarantee
