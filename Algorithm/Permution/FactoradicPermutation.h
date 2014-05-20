/******************************************************************************
 * File: FactoradicPermutation.hh
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * An algorithm for manipulating and generating permutations in lexicographic
 * order by using the factoradic number system.
 *
 * The factoradic number system (also called the factorial number system) is a
 * way of writing out numbers in a base system that depends on factorials,
 * rather than powers of numbers.  In the factoradic system, the last digit is
 * always 0 and is in base 0!.  The digit before that is either 0 or 1 and is
 * in base 1!.  The digit before that is either 0, 1, or 2 and is in base 2!.
 * More generally, the nth-to-last digit in always 0, 1, 2, ..., or n and is in
 * base n!.  When writing a number, we usually append a subscript ! to indicate
 * that it's written in factoradic base.  In this (plain-text) C++ source file,
 * I'll denote this by suffixing the number with _!.
 *
 * As an example, the factoradic number 2110_! is equal to
 *
 *      2 x 3! + 1 x 2! + 1 x 1! + 0 x 0!
 *    = 2 x 6  + 1 x 2  + 1 x 1  + 0 x 1
 *    =    12  +     2  +     1  +     0
 *    =    15
 *
 * Similarly, the first few factoradic numbers are
 *
 *     0_!  10_!  100_!  110_!  200_!  210_!  1000_!  1010_!  1100_!  1110_!
 *
 * One reason that the factoradic numbers are so useful is that there's a close
 * connection between factoradic numbers and permutations of distinct values.
 * To understand where this comes from, suppose that we're interested in
 * generating all of the permutations of some collection in lexicographic
 * order.  One way to do this might be to think about generating the first such
 * permutation, then the second, then the third, etc.  In other words, we want
 * to look for some way of mapping the integers onto permutations in a way that
 * allows us to efficiently answer the question "what is the nth permutation of
 * this set?"
 *
 * Let's consider permutations of four elements - a, b, c, and d - and the
 * order in which they're generated.  Here's a table of these permutations:
 *
 *               0  abcd       6 bacd      12 cabd      18 dabc
 *               1  abdc       7 badc      13 cadb      19 dacb
 *               2  acbd       8 bcad      14 cbad      20 dbac
 *               3  acdb       9 bcda      15 cbda      21 dbca
 *               4  adbc      10 bdac      16 cdab      22 dcab
 *               5  adcb      11 bdca      17 cdba      23 dcba
 *
 * Initially, there might not seem to be any pattern relating the numbers to
 * the permutations, but there are a few trends we can spot here.  For example,
 * every sixth permutation starts with a new letter, and 6 = 3!.  The second
 * letter of each permutation changes every two permutations, and 2 = 2!.
 *
 * If we rewrite the above table with the integers in factoradic base, then a
 * more obvious trend starts to appear:
 *
 *          0000_!  abcd  1000_! bacd  2000_! cabd  3000_! dabc
 *          0010_!  abdc  1010_! badc  2010_! cadb  3010_! dacb
 *          0100_!  acbd  1100_! bcad  2100_! cbad  3100_! dbac
 *          0110_!  acdb  1110_! bcda  2110_! cbda  3110_! dbca
 *          0200_!  adbc  1200_! bdac  2200_! cdab  3200_! dcab
 *          0210_!  adcb  1210_! bdca  2210_! cdba  3210_! dcba
 *
 * We noted above that the first letter changes every six permutations, and now
 * we can see that this coincides with the times at which the first digit of
 * the factoradic representation changes.  Similarly, when we noted that the
 * second letter of the permutation changed every two permutations, we can see
 * this is occurring whenever the second digit of the factoradic representation
 * of the index is changing.
 *
 * The connection here is due to a construction called "Lehmer codes," a way of
 * labeling permutations in a way that also allows their construction.  The
 * idea behind Lehmer codes is as follows.  Suppose that you are given a
 * permutation of a totally-ordered set of elements, such as the permutation
 * BEDAC of the letters A-E.  We start off by looking at the first letter of
 * this permutation - in this case, B - and seeing how many elements it's
 * bigger than (in this case, 1).  We then split this letter off of the
 * permutation and record the fact that it was bigger than one element:
 *
 *     B   EDAC
 *     1
 *
 * Now, we repeat this process on EDAC.  Here, E is larger than three of the
 * elements of EDAC (everything except itself), so we write out a three to get
 *
 *     BE  DAC
 *     13
 *
 * Repeating this on D gives us
 *
 *     BED  AC
 *     132
 *
 * And on A gives us
 *
 *     BEDA  C
 *     1320  0
 *
 * And finally on the last C gives us
 *
 *     BEDAC
 *     13200
 *
 * So the Lehmer code for this permutation is (1, 3, 2, 0, 0).  Note that the
 * length of a Lehmer code is equal to the number of elements in the
 * permutation.
 *
 * Given a permutation's Lehmer code, we can generate the permutation it stands
 * for by running this process backwards.  Suppose, for example, that we're
 * given the Lehmer code (3, 1, 0, 0) and want to use it to recover some given
 * permutation of ABCD.  To do this, we'd start off by taking the element of
 * this collection of letters that's bigger than three other elements.  This is
 * equivalent to asking which element is at position 3 using zero-indexing, and
 * gives us D.  So now we have
 *
 *     D    ABC
 *     3
 *
 * and the remaining Lehmer code (1, 0, 0).  Looking at the 1 in the first
 * position of this Lehmer code, we should take the element out of the unused
 * elements at position 1 (which, zero-indexed, is B), giving us
 *
 *     DB   AC
 *     31
 *
 * The rest of our code is (0, 0), so we take the zeroth-largest element of the
 * unused letters (A) and put it next:
 *
 *     DBA  C
 *     310
 *
 * And finally, we use the last part of our code, (0), to select the last
 * element of the permutation, which is C:
 *
 *     DBAC
 *     3100
 *
 * The clincher in all this is that there's a simple, one-to-one mapping
 * between the factoradic numbers and Lehmer codes.  The idea is simple - given
 * a Lehmer code (d0, d1, ..., dn), we just pick the number
 *
 *                                d0 d1 d2 ... dn_!
 *
 * For example, given Lehmer code (3, 1, 0, 0), we'd pick the factoradic number
 * 3100_!.  Similarly, given factoradic number 210_!, we'd pick the Lehmer code
 * (2, 1, 0).
 *
 * In order to convince ourselves that this is even mathematically well-defined
 * we need to see that each of the digits we assign are within the range
 * specified for that digit.  For example, if it were possible that we could
 * have a Lehmer code (1, 4), then we couldn't convert it to the factoradic
 * number 14_!, since the last digit of any factoradic number must be 0.  This
 * is not particularly difficult to see.  Remember that the digits of the
 * Lehmer code are zero-based indices into the list of elements we haven't yet
 * used yet.  Thus the last digit must be zero, since there's only one element
 * remaining; the penultimate digit can be either one or zero since there's
 * two possible choices; the antepenultimate digit can be zero, one or two;
 * etc.
 *
 * Given the bijiective correspondence between Lehmer codes and the factoradic
 * numbers, we have a way of taking a natural number N and mapping it into a
 * permutation of some number of elements.  However, as of now we have no
 * reason to believe that this will list every permutation in lexicographic
 * order.  After all, given some random encoding system for permutations, why
 * should we expect anything special out of our ordering?  Fortunately, though
 * we have the following lemma:
 *
 * Lemma: Given two permutations p_1 and p_2 with Lehmer codes L_1 and L_2,
 * p_1 lexicographically precedes p_2 iff L_1 lexicographically precedes L_2.
 *
 * Corollary: Every permutation has a unique Lehmer code.
 *
 * Before we go into the proof, I should remark that this guarantees that the
 * following algorithm will list all permutations of n elements in order:
 *
 * For i = 0 to n! - 1:
 *    Represent i in factoradic base.
 *    Convert this representation to a Lehmer code.
 *    Generate the permutation based on this Lehmer code.
 *
 * This algorithm works correctly because every permutation has a Lehmer code,
 * and by iterating over all n! different codes we'll hit every permutation.
 * Moreover, our lemma guarantees that no two permutations have the same
 * Lehmer code, we know that we'll get every permutation in order and exactly
 * once.
 */
#ifndef FactoradicPermutation_Included
#define FactoradicPermutation_Included

#include <iterator>   // For std::iterator_traits
#include <algorithm>  // For std::sort, std::rotate, std::count_if
#include <functional> // For std::less, std::bind2nd

/**
 * Function: NthPermutation(RandomIterator begin, RandomIterator end,
 *                          Integer n);
 * Usage: NthPermutation(v.begin(), v.end(), n);
 * ----------------------------------------------------------------------------
 * Given a range of iterators [begin, end) and an integer n, rearranges the
 * values in [begin, end) so that they are in the nth lexicographically
 * smallest permutation.  It is assumed that n is large enough to hold
 * (end - begin)! without overflow.
 */
template <typename RandomIterator, typename Integer>
void NthPermutation(RandomIterator begin, RandomIterator end, Integer n);

/**
 * Function: PermutationIndex(RandomIterator begin, RandomIterator end);
 * Usage: size_t n = PermutationIndex<size_t>(begin, end);
 * ----------------------------------------------------------------------------
 * Given a range of iterators spanning a permutation of distinct values,
 * returns the number of that permutation in the lexicographical ordering of
 * permutations.
 */
template <typename Integer, typename RandomIterator>
Integer PermutationIndex(RandomIterator begin, RandomIterator end);

/**
 * Function: NthPermutation(RandomIterator begin, RandomIterator end,
 *                          Integer n, Comparator comp);
 * Usage: NthPermutation(v.begin(), v.end(), n, std::greater<int>());
 * ----------------------------------------------------------------------------
 * Given a range of iterators [begin, end) and an integer n, rearranges the
 * values in [begin, end) so that they are in the nth lexicographically
 * smallest permutation.  It is assumed that n is large enough to hold
 * (end - begin)! without overflow.  Comparisons are done using the provided
 * comparator comp.
 */
template <typename RandomIterator, typename Integer, typename Comparator>
void NthPermutation(RandomIterator begin, RandomIterator end, Integer n,
                    Comparator comp);

/**
 * Function: PermutationIndex(RandomIterator begin, RandomIterator end,
 *                            Comparator comp);
 * Usage: size_t n = PermutationIndex<size_t>(begin, end, std::greater<int>());
 * ----------------------------------------------------------------------------
 * Given a range of iterators spanning a permutation of distinct values,
 * returns the number of that permutation in the lexicographical ordering of
 * permutations.  The specified comparator is used to determine the ordering of
 * individual values in the sequence.
 */
template <typename Integer, typename RandomIterator, typename Comparator>
Integer PermutationIndex(RandomIterator begin, RandomIterator end,
                         Comparator comp);

/* * * * * Implementation Below This Point * * * * */
template <typename RandomIterator, typename Integer, typename Comparator>
void NthPermutation(RandomIterator begin, RandomIterator end, Integer n, 
                    Comparator comp) {
  /* Sort the elements into ascending order according to the comparator.  The
   * logic for Lehmer encoding requires this.
   */
  std::sort(begin, end, comp);

  /* We now need to convert the integer n into something in factoradic base.
   * To do this, we attempt to recover the factoradic digits one at a time much
   * in the way that you would recover the digits of, say, a digital or binary
   * number.  In particular, if the range has size k, we compute (k - 1)!, then
   * divide n by that number to yield the most significant factoradic digit.
   * We then divide (k - 1)! by k - 1 to get (k - 2)! and repeat this process
   * one digit at a time.
   *
   * As a first step, compute k and (k - 1)!.
   */
  const Integer k(end - begin);

  /* Compute (k - 1)!. */
  Integer radix = Integer(1);
  for (Integer i = Integer(2); i < k; ++i)
    radix *= i;

  /* This loop holds the invariant that on entry, radix is equal to i!, where
   * i is the factoradic digit being considered right now.
   *
   * We also hold the invariant that the range [out, out + k) is the unsorted
   * part of the permutation, while the elements before this are the generated
   * portion of the permutation.
   *
   * Again, to avoid integer underflow, we count upward rather than downward.
   */
  for (Integer i = 0; i < k; ++i) {
    /* Recover the next factoradic digit by dividing n by the current radix. */
    Integer digit = n / radix;

    /* We now want to pick that element as the next term of the permutation.
     * After we do this, we need to shuffle all the elements after that element
     * down a spot.  This is equivalent to rotating all of the elements in the
     * range [out, out + digit) one spot to the right.  For example, given this
     * setup where we want to put 3 as the first element of the permutation:
     *
     *                                1 2 3 4 5
     *                                    ^
     * we do a cyclic right shift to get
     *
     *                                3 1 2 4 5
     */
    std::rotate(begin, begin + digit, begin + digit + 1);

    /* Set up for the next iteration.  We need to move the output iterator
     * forward a step so that it writes to the next location.
     */
    ++ begin;

    /* We also need to remove the contribution of the current radix to n by
     * modding it out.
     */
    n %= radix;

    /* Finally, we need to divide the radix by our index so that on the next
     * iteration it has the correct value.  However, if this is the final
     * iteration, then this would be a divide-by-zero, and so we don't do the
     * divide.
     */
    if (i + 1 != k)
      radix /= (k - i - 1);
  }
}

/* To determine the index of a permutation, we determine the order of each
 * element in the range - that is, the number of elements smaller than it -
 * then scale those values up by the appropriate base in the factoradic
 * representation.
 */
template <typename Integer, typename RandomIterator, typename Comparator>
Integer PermutationIndex(RandomIterator begin, RandomIterator end,
                         Comparator comp) {
  /* As in the generating permutations case, compute k and (k - 1)!. */
  const Integer k(end - begin);

  Integer radix = Integer(1);
  for (Integer i = Integer(2); i < k; ++i)
    radix *= i;

  /* Loop across the elements, computing the order of each and scaling it by
   * the appropriate factorial base.
   */
  Integer result = Integer(0);
  for (; begin != end; ++begin) {
    /* Compute the order of the element by seeing how many elements in the
     * range are less than the value.
     */
    result += radix * std::count_if(begin, end, std::bind2nd(comp, *begin));

    /* Scale down the radix, unless this is the very last iteration. */
    if (begin + 1 != end)
      radix /= (end - begin) - 1;
  }

  return result;
}

/* Non-comparator versions implemented in terms of comparator. */
template <typename RandomIterator, typename Integer>
void NthPermutation(RandomIterator begin, RandomIterator end, Integer n) {
  NthPermutation
    (begin, end, n,
     std::less<typename std::iterator_traits<RandomIterator>::value_type>());
}

template <typename Integer, typename RandomIterator>
Integer PermutationIndex(RandomIterator begin, RandomIterator end) {
  return PermutationIndex<Integer>
    (begin, end,
     std::less<typename std::iterator_traits<RandomIterator>::value_type>());
}

#endif
