/*
Describe a queue data structure that is implemented using stacks
*/

//solution: using two stacks: one is incoming stack and the other is outgoing stack

stack in;
stack out;

void enqueue(int value){
	while (!out.empty())
		in.push(out.pop());
	in.push(value);
}

int dequeue(){
	while (!in.empty())
		out.push(in.pop());
	return out.pop();
}
