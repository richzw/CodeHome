//////////////////////////////////////////////////////////////////////////
// LIS - Longest Increasing Subsequence
ArrayList<HtWt> getIncreaseingSubsequence(ArrayList<HtWt> items){
	Collections.sort(items);
	return longestIncreasingSubsequence(items);
}

ArrayList<HtWt> longestIncreasingSubsequence(ArrayList<HtWt> array){
	ArrayList<HtWt>[] solutions = new ArrayList[array.size()];

	longestIncreasingSubsequence(array, solutions, 0);
	ArrayList<HtWt> best_sequence = null;
	for (int i = 0; i < array.size(); ++i){
		best_sequence = sequenceWithMaxLength(best_sequence, solutions[i]);
	}
	
	return best_sequence;
}

void longestIncreasingSubsequence(ArrayList<HtWt> array, ArrayList<HtWt>[] solutions, int current_index){
	if (current_index >= array.size() || current_index < 0)
		return;
	
	HtWt current_element = array.get(current_index);
	
	// find longest sequence cur
	ArrayList<HtWt> best_sequence = null;
	for (int i = 0; i < current_index; ++i){
		if (array.get(i).isBefore(current_element)){
			best_sequence = sequenceWithMaxLength(best_sequence, solutions[i]);
		}
	}
	
	// append current_element
	ArrayList<HtWt> new_solution = new ArrayList<HtWt>();
	if (best_sequence != null){
		new_solution.addAll(best_sequence);
	}
	new_solution.add(current_element);
	
	solution[current_index] = new_solution;
	longestIncreasingSubsequence(array, solutions, current_index+1);
}

ArrayList<HtWt> seqWithMaxLength(ArrayList<HtWt> seq1, ArrayList<HtWt> seq2){
	if (seq1 == null) return seq2;
	if (seq2 == null) return seq1;
	
	return seq1.size() > seq2.size() ? seq1: seq2;
}

public class HtWt implements Comparable {
	/* declarations etc */
	
	public int compareTo(Object s){
		HtWt second = (HtWt)s;
		if (this.Ht != second.Ht){
			return ((Integer)this.Ht).compareTo(second.Ht);
		} else {
			return ((Integer)this.Wt).compareTo(second.Wt);
		}
	}
	
	public boolean isBefore(HtWt other){
		if (this.Ht < other.Ht && this.Wt < other.Wt)
			return true;
		else
			return false;
	}
}
