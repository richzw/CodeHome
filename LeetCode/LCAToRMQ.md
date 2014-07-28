
Reduce LCA to RMQ
==========

**On an input tree T, we build 3 arrays**.

- Euler[1,..,2n-1] – The nodes visited in an Euler tour of T. Euler[i] is the label of the i-th node visited in the tour.

- Level[1,..2n-1] – The level of the nodes we got in the tour. Level[i]  is the level of node Euler[i]. (level is defined to be the distance from the root)

- Representative[1,..n] – Representative[i] will hold the index of the first occurrence of node i in Euler[].


**To compute LCAT(x,y)**:

+ All nodes in the Euler tour between the first visits to x and y are E[R[x],..,R[y]] (assume R[x] < R[y])

+ The shallowest node in this subtour is at index RMQL(R[x],R[y]), since L[i] stores the level of the node at E[i].

+ RMQ will return the index, thus we output the node at E[RMQL(R[x],R[y])] as LCAT(x,y).


![Demo](https://cloud.githubusercontent.com/assets/1590890/3715927/34bbbf72-15fb-11e4-9527-079376a1eade.png)
