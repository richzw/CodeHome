//

// 1. two queues
class MyQueue//Our data structure
{
    deque D;//We need 2 deque objects
    deque Min;

    push(element)//pushing element to MyQueue
    {
        D.push_back(element);
        while(Min.is_not_empty() and Min.back()>element)
             Min.pop_back();
        Min.push_back(element);
    }
    pop()//poping MyQueue
    {
         if(Min.front()==D.front() )
            Min.pop_front();
         D.pop_front();
    }

    min()
    {
         return Min.front();
    }
}

// 2. 
/*
You can implement a stack with O(1) pop(), push() and get_min(): just store the current minimum together with each element. 
So, for example, the stack [4,2,5,1] (1 on top) becomes [(4,4), (2,2), (5,2), (1,1)].

Then you can use two stacks to implement the queue. Push to one stack, pop from another one; 
if the second stack is empty during the pop, move all elements from the first stack to the second one.

E.g for a pop request, moving all the elements from first stack [(4,4), (2,2), (5,2), (1,1)],
the second stack would be [(1,1), (5,1), (2,1), (4,1)]. and now return top element from second stack.

To find the minimum element of the queue, look at the smallest two elements of the individual min-stacks, 
then take the minimum of those two values. (Of course, there's some extra logic here is case one of the stacks is empty, 
but that's not too hard to work around).

It will have O(1) get_min() and push() and amortized O(1) pop().
*/
