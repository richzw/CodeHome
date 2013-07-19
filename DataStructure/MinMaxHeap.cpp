

template <class Type>
void MinMaxHeap<Type>::Insert(const Element<Type>&x ) {
   if (n == MaxSize ) { MinMaxFull( ); return;}
   n++;
   int p = n/2;    // p是新结点的双亲
   if (!p) {h[1] = x; return;} 	// 插入初始时为空的堆
   switch (level(p)) {
      case MIN:
         if (x.key < h[p].key) { 	// 沿着最小层检查
            h[n]=h[p];
            VerifyMin(p, x);
         }
         else VerifyMax(n, x); 	// 沿着最大层检查
         break;
      case MAX:
         if (x.key > h[p].key) { 	// 沿着最大层检查
            h[n]=h[p];
            VerifyMax(p, x);
         }
         else VerifyMin(n, x); 	// 沿着最小层检查
   } 		// switch结束
} 	// Insert结束  

template <class Type>
void MinMaxHeap<Type>::VerifyMax (int i, const Element<KeyType>&x ) {   // 沿着从最大结点i
                                                               // 到根结点的路径检查最大结点，将x插入正确位置
   for (int gp = i/4; gp && (x.key > h[gp].key); gp /=4) { 	// gp是 i的祖父
      h[i] = h[gp];	            // 将h[gp]移到h[i]
      i = gp;
   }
   h[i] = x;         // 将x插入结点i
} 

template <class Type>
Element<Type>* MinMaxHeap<Type>::  DeleteMin(Element<Type>&y) {
    // 从最小最大堆中删除并返回最小元素
   if (!n) { MinMaxEmpty( ); return 0; }
   y = h[1];   // 保存根元素
   Element<Type> x = h[n--]; 		
   int i = 1, j = n/2; 	// 为重新插入x作初始化，寻找插入x的位置
   while (i <= j) {	// i 有子女，情况(2)
      int k = MinChildGrandChild(i); 
      if (x.key <= h[k].key) 
         break;	// 情况 2(a)，可将x 插入h[i]
   else { 	// 情况2(b) 或 (c) 
         h[i] = h[k];
         if (k <= 2*i+1) {  // k 是i的子女，情况2(b)
            i = k;		// 可将x插入h[k]
            break;
         }
         else { 	// k是i的孙子女，情况2(c)
            int p = k/2; 	// p是k的双亲 
            if (x.key > h[p].key) {
               Element<Type> t = h[p]; h[p] = x; x = t;
            }
         } 	// if (k<=2*i+1)结束
         i = k; 
      } 	// if (x.key<=h[k].key)结束
} 	// while结束
   h[i] = x; 	// 注意，即使现在n == 0，对h[1] 赋值也没错，这样简化边界判断
   return &y; 
}
