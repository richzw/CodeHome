/*
1.查找key值最接近指定key值的结点，保存至me中
2.中序遍历BST，在此过程中将结点保存至一个大小为m的队列中。
1) 当结点的key值小于me.key时，入队/出队，维持队列大小为m
2）当结点就是me时，判断me.key是否等于指定的key；是，不入队，否，入队
3) 当结点的key值大于me.key，比较其键值与key的差值 和 key与队首结点键值的差值，
如果小，入队，否则终止遍历。这时队列中的结点就是所求集合。

*/

public BSTNode[] getClosestNodesWithQueue(int myKey,int m){
  	// Declare a queue of size m to save the result set
		Queue<BSTNode> q = new LinkedList<BSTNode>();
		// Rather than walking tree recursively,
		// use a stack as auxiliary data structure for in-order traversal within while loop.
		Stack<BSTNode> s = new Stack<BSTNode>();
		// Get the node with closest key to the given key first.
		// Its key may or may not be the same as myKey. 
		BSTNode me = this.searchForNearest(myKey);
		BSTNode root = this.getRoot();
		// Do in-order traversal, during which enqueue or dequeue nodes appropriately.
		while(!s.empty() || root!=null){
			while(root!=null){
				s.push(root);
				root = root.getLeft();
			}
			if(!s.empty()){
				// Get the first node in the stack.
				root = s.pop();
				// Save the biggest mth nodes which are less than the closest key.
				if(root.getKey() < me.getKey()){
					if(q.size()>=m){
						q.poll();
					}	
					q.add(root);
				// Once we encounter the ME node with closest key,
				// we judge that whether its key equals the given myKey.
				// If yes, skip and do not save it in the queue.
				// If no, since it's the nearest node, we have no point in not saving it!
				}else if(root.getKey() == me.getKey() && me.getKey()!= myKey){
					if(q.size()>=m){
						q.poll();
					}	
					q.add(root);
				// We will encounter those nodes with greater key (than myKey) at some point during traversal.
				}else if(root.getKey() > me.getKey()){
					// If the size of queue is still less than m,
					// simply save the node.
					if(q.size()<m){
						q.add(root);
					// If the size of queue is >= m,
					// we judge that whether the difference between its key and myKey is less than
					// the difference between head's key and myKey.
					// If yes, remove the head of queue and save current node.
					// If no, we have got all m nodes with keys less than myKey.
					// Break the traversal.
					}else if(myKey - q.peek().getKey() > root.getKey() - myKey){
						q.poll();
						q.add(root);
					}else{
						break;
					}
				}
				root = root.getRight();
			}
		}
		return q.toArray(new BSTNode[0]);
	}
