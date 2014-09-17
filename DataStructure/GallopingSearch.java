/**
* If the length of the array is unknown for some reason, the galloping search can identify the initial range of the search scope.
* This algorithm starts at the first element and keeps doubling the upper limit of the search range until the value 
* there is larger than the searched key. After this, depending on the implementation, 
* the search either falls back to a standard binary search on the selected range, or restarts another galloping search. 
* The former one guarantees an O(log(n)) runtime, the latter one is closer to O(n) runtime.
* 
* Galloping search is efficient if we expect to find the element closer to the beginning of the array
*
*/

public class Gallop {
    public long accessed;

    public int search(final int[] arr, final int val, int left, int right) {
        if (arr == null || arr.length == 0 || arr[left] > val || arr[right - 1] < val) {
            return -1;
        }

        int jump = 1;

        while (left <= right) {
            final int curr = arr[left];
            accessed++;

            if (curr == val) {
                return left;
            }

            final int next = left + jump;

            if (curr > val || next > right) {
                if (curr > val) {
                    right = left;
                }

                left -= jump / 2;
                left++;
                jump = 1;
                continue;
            }

            left = next;
            jump *= 2;
        }

        return -1;
    }

    public long getAccessed() {
        final long old = accessed;
        accessed = 0;
        return old;
    }
}
