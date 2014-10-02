////////////////////////////////////////////////////////////////////////////////
// Suppose you are reading in a stream of integers. Periodically, you wish to be able to look up the rank of number x

// Binary search tree + in-order traversal

public class RankNode{
	public int left_size = 0;
	public RankNode left, right;
	public int data = 0;
	public RankNode(int d){
		data = d;
	}
	
	public void insert(int d){
		if (d <= data){
			if (left != null)
				left.insert(d);
			else 
				left = new RankNode(d);
			left_size++;
		} else {
			if (right != null)
				right.insert(d);
			else
				right = new RankNode(d);
		}
	}
	
	public int getRank(int d){
		if (d == data)
			return left_size;
		else if (d < data)
	}
}
