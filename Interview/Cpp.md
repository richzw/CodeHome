对容器的操作影响了元素的存放位置，称为迭代器失效。下面是一些常见的迭代器失效情况

- vector
  - 插入一个元素后，end操作方位的迭代器失效。
  - 插入一个元素后，capacity返回值发生变化，first和end操作返回的迭代器都会失效。
  - 进行删除操作后，指向删除点的迭代器将失效，指向删除点后面的元素的迭代器也将失效。
- deque
  - 在容器首部和尾部插入元素不会使迭代器失效。
  - 在首部或尾部删除元素会使指向被删除元素的迭代器失效。
  - 在容器的任何位置插入或删除操作将会使指向该容器元素的所有迭代器失效
- list/set/multiset/map/multimap
  - 删除元素时，指向该元素的迭代器失效。
  
  https://interview.huihut.com/#/
  
