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
#ifndef MEMMOVE
  #define MEMMOVE memmove
  #endif
  
  rettype
  inhibit_loop_to_libcall
  MEMMOVE (a1, a2, len)
  a1const void *a1;
  a2const void *a2;
  size_t len;
  {
  unsigned long int dstp = (long int) dest;
  unsigned long int srcp = (long int) src;
  
  /* This test makes the forward copying code be used whenever possible.
  Reduces the working set. */
  if (dstp - srcp >= len) /* *Unsigned* compare! */
  {
  /* Copy from the beginning to the end. */
  
  #if MEMCPY_OK_FOR_FWD_MEMMOVE
  dest = memcpy (dest, src, len);
  #else
  /* If there not too few bytes to copy, use word copy. */
  if (len >= OP_T_THRES)
  {
  /* Copy just a few bytes to make DSTP aligned. */
  len -= (-dstp) % OPSIZ;
  BYTE_COPY_FWD (dstp, srcp, (-dstp) % OPSIZ);
  
  /* Copy whole pages from SRCP to DSTP by virtual address
  manipulation, as much as possible. */
  
  PAGE_COPY_FWD_MAYBE (dstp, srcp, len, len);
  
  /* Copy from SRCP to DSTP taking advantage of the known
  alignment of DSTP. Number of bytes remaining is put
  in the third argument, i.e. in LEN. This number may
  vary from machine to machine. */
  
  WORD_COPY_FWD (dstp, srcp, len, len);
  
  /* Fall out and copy the tail. */
  }
  
  /* There are just a few bytes to copy. Use byte memory operations. */
  BYTE_COPY_FWD (dstp, srcp, len);
  #endif /* MEMCPY_OK_FOR_FWD_MEMMOVE */
  }
  else
  {
  /* Copy from the end to the beginning. */
  srcp += len;
  dstp += len;
  
  /* If there not too few bytes to copy, use word copy. */
  if (len >= OP_T_THRES)
  {
  /* Copy just a few bytes to make DSTP aligned. */
  len -= dstp % OPSIZ;
  BYTE_COPY_BWD (dstp, srcp, dstp % OPSIZ);
  
  /* Copy from SRCP to DSTP taking advantage of the known
  alignment of DSTP. Number of bytes remaining is put
  in the third argument, i.e. in LEN. This number may
  vary from machine to machine. */
  
  WORD_COPY_BWD (dstp, srcp, len, len);
  
  /* Fall out and copy the tail. */
  }
  
  /* There are just a few bytes to copy. Use byte memory operations. */
  BYTE_COPY_BWD (dstp, srcp, len);
  }
  
  RETURN (dest);
  }
