/*
 * Interpolation search implementation.
 * The interpolation search supposed to be the “smartest” among the tested algorithms.
 * It resembles the way humans are using phonebooks, as it tries to guess the location of the element by assuming that
 * the elements are evenly distributed in the array.
 * As a first step it samples the beginning and the end of the search space and then guesses the element’s location. 
 * It keeps repeating this step until the element is found. If the guesses are accurate, 
 * the number of comparisons can be around O(log(log(n)), runtime around O(log(n)), 
 * but unlucky guesses easily push it up to O(n).
 */
public class Interpolation implements Search {
    public long accessed;

    public int search(final int[] arr, final int val, int left, int right) {
        if (arr == null || arr.length == 0 || arr[left] > val || arr[right - 1] < val) {
            return -1;
        }

        while (left < right && left >= 0 && right <= arr.length) {
            final int leftValue = arr[left];
            accessed++;
            final int rightValue = arr[right - 1];
            accessed++;

            final float average = ((float) rightValue - leftValue) / (right - left);
            int midpoint = left;
            if (average != 0) {
                final int diff = val - leftValue;
                final int steps = (int) (diff / average);
                midpoint = left + steps;

                // Overshoots.
                if (midpoint >= right) {
                    midpoint = (left + right) / 2;
                }
            }

            final int mid = arr[midpoint];
            accessed++;

            if (mid == val) {
                return midpoint;
            } else if (val < mid) {
                right = midpoint - 1;
            } else {
                left = midpoint + 1;
            }
        }

        if (arr[left] == val) {
            return left;
        }

        return -1;
    }

    public long getAccessed() {
        final long old = accessed;
        accessed = 0;
        return old;
    }
}
