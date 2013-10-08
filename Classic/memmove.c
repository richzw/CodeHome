/*
实现void memcpy(char *des,char *src,int n); 

src是const没问题啊，只要dst不是const就行。无论有没有重叠， 都是从src拷贝到dst，永远不会用src指针改变内存。 
  
 内存重叠有两种情况： 
一种是src的尾部和dst的头部重叠，这时候如果不做处理，src的尾部在还没有复制到就会被头部内容覆盖 
另一种是src的头部和dst的尾部重叠，这种情况没有问题不需要特殊处理。 
解决方法很简单，只要倒着拷贝就行了，从src的最后一个字节倒着向前拷贝到dst，就可以避免覆盖 
  
 glibc memmove的源码 http://fossies.org/dox/glibc-2.18/string_2memmove_8c_source.html 
一旦发现 if (dstp - srcp >= len) 即有重叠，就把srcp += len; dstp += len; 倒着拷贝。
*/
