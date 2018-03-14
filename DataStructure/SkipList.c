// skip list introduction
// http://zhangtielei.com/posts/blog-redis-skiplist.html
/*
skiplist的数据结构定义
#define ZSKIPLIST_MAXLEVEL 32
#define ZSKIPLIST_P 0.25

typedef struct zskiplistNode {
    robj *obj;
    double score;
    struct zskiplistNode *backward;
    struct zskiplistLevel {
        struct zskiplistNode *forward;
        unsigned int span;
    } level[];
} zskiplistNode;

typedef struct zskiplist {
    struct zskiplistNode *header, *tail;
    unsigned long length;
    int level;
} zskiplist;
这段代码出自server.h，我们来简要分析一下：

开头定义了两个常量，ZSKIPLIST_MAXLEVEL和ZSKIPLIST_P，分别对应我们前面讲到的skiplist的两个参数：一个是MaxLevel，一个是p。

zskiplistNode定义了skiplist的节点结构。
1. obj字段存放的是节点数据，它的类型是一个string robj。本来一个string robj可能存放的不是sds，而是long型，但zadd命令在将数据插入到skiplist
里面之前先进行了解码，所以这里的obj字段里存储的一定是一个sds。这样做的目的应该是为了方便在查找的时候对数据进行字典序的比较，而且，
skiplist里的数据部分是数字的可能性也比较小。
2. score字段是数据对应的分数。
3. backward字段是指向链表前一个节点的指针（前向指针）。节点只有1个前向指针，所以只有第1层链表是一个双向链表。
4. level[]存放指向各层链表后一个节点的指针（后向指针）。每层对应1个后向指针，用forward字段表示。另外，每个后向指针还对应了一个span值，
它表示当前的指针跨越了多少个节点。span用于计算元素排名(rank)，这正是前面我们提到的Redis对于skiplist所做的一个扩展。需要注意的是，
level[]是一个柔性数组（flexible array member），因此它占用的内存不在zskiplistNode结构里面，而需要插入节点的时候单独为它分配。
也正因为如此，skiplist的每个节点所包含的指针数目才是不固定的，我们前面分析过的结论——skiplist每个节点包含的指针数目平均为1/(1-p)——才能有意义。

zskiplist定义了真正的skiplist结构，它包含：
1. 头指针header和尾指针tail。
2. 链表长度length，即链表包含的节点总数。注意，新创建的skiplist包含一个空的头指针，这个头指针不包含在length计数中。
3. level表示skiplist的总层数，即所有节点层数的最大值。

Redis中sorted set的实现是这样的：

1. 当数据较少时，sorted set是由一个ziplist来实现的。
2. 当数据多的时候，sorted set是由一个dict + 一个skiplist来实现的。简单来讲，dict用来查询数据到分数的对应关系，而skiplist用来根据分数查询数据（可能是范围查找）。

这里sorted set的构成我们在下一章还会再详细地讨论。现在我们集中精力来看一下sorted set与skiplist的关系，：

1. zscore的查询，不是由skiplist来提供的，而是由那个dict来提供的。
2. 为了支持排名(rank)，Redis里对skiplist做了扩展，使得根据排名能够快速查到数据，或者根据分数查到数据之后，也同时很容易获得排名。而且，根据排名的查找，
时间复杂度也为O(log n)。
3. zrevrange的查询，是根据排名查数据，由扩展后的skiplist来提供。
4. zrevrank是先在dict中由数据查到分数，再拿分数到skiplist中去查找，查到后也同时获得了排名。

总结起来，Redis中的skiplist跟前面介绍的经典的skiplist相比，有如下不同：

1. 分数(score)允许重复，即skiplist的key允许重复。这在最开始介绍的经典skiplist中是不允许的。
2. 在比较时，不仅比较分数（相当于skiplist的key），还比较数据本身。在Redis的skiplist实现中，数据本身的内容唯一标识这份数据，而不是由key来唯一标识。
另外，当多个元素分数相同的时候，还需要根据数据内容来进字典排序。
3. 第1层链表不是一个单向链表，而是一个双向链表。这是为了方便以倒序方式获取一个范围内的元素。
4. 在skiplist中可以很方便地计算出每个元素的排名(rank)。
*/

#ifndef __SKIPLIST_H
#define __SKIPLIST_H
 
 #define SKIPLIST_MAXLEVEL 8 
 
 typedef struct skiplistNode {
     double score;
     struct skiplistNode *backward;
     struct skiplistLevel {
         struct skiplistNode *forward;
     }level[];
 }skiplistNode;
 
 typedef struct skiplist {
     struct skiplistNode *header, *tail;
     unsigned long length;
     int level;
 }skiplist;
 
 #endif
 
#include "skiplist.h"
 #include <stdlib.h>
 #include <stdio.h>
 
 skiplistNode *slCreateNode(int level, double score) {
     skiplistNode * sn = malloc(sizeof(*sn) + level*sizeof(struct skiplistLevel));
     sn->score = score;
     return sn;
 }
 
 skiplist *slCreate(void) {
     int j;
     skiplist *sl;
 
     sl = malloc(sizeof(*sl));
     sl->level = 1;
     sl->length = 0;
     sl->header = slCreateNode(SKIPLIST_MAXLEVEL, 0);
     for(j = 0; j < SKIPLIST_MAXLEVEL; j++) {
         sl->header->level[j].forward = NULL;
     }
     sl->header->backward = NULL;
     sl->tail = NULL;
     return sl;
 }
 
 void slFreeNode(skiplistNode *sn) {
     free(sn);
 }
 
 void slFree(skiplist *sl) {
     skiplistNode *node = sl->header->level[0].forward, *next;
 
     free(sl->header);
     while(node) {
         next = node->level[0].forward;
         slFreeNode(node);
         node = next;
     }
     free(sl);
 }
 
 int slRandomLevel(void) {
     int level = 1;
     while((rand()&0xFFFF) < (0.5 * 0xFFFF)) 
         level += 1;
     return (level < SKIPLIST_MAXLEVEL) ? level : SKIPLIST_MAXLEVEL;
 }
 
 skiplistNode *slInsert(skiplist *sl, double score) {
     skiplistNode *update[SKIPLIST_MAXLEVEL];
     skiplistNode *node;
 
     node = sl->header;
     int i, level;
     for ( i = sl->level-1; i >= 0; i--) {
         while(node->level[i].forward && node->level[i].forward->score < score) {
             node = node->level[i].forward;
         }
         update[i] = node;
     }
     level = slRandomLevel();
     if (level > sl->level) {
         for (i = sl->level; i< level ;i++) {
             update[i] = sl->header;
         }
         sl->level = level;
     }
     node = slCreateNode(level, score);
     for (i = 0; i < level; i++) {
         node->level[i].forward = update[i]->level[i].forward;
         update[i]->level[i].forward = node;
     }
 
     node->backward = (update[0] == sl->header? NULL : update[0]);
     if (node->level[0].forward)
         node->level[0].forward->backward = node;
     else
         sl->tail = node;
     sl->length++;
     return node;
 }
 
 void slDeleteNode(skiplist *sl, skiplistNode *x, skiplistNode **update){
     int i;
     for (i = 0; i < sl->level; i++) {
         if (update[i]->level[i].forward == x) {
             update[i]->level[i].forward = x->level[i].forward;
         }
     }
     if (x->level[0].forward) {
         x->level[0].forward->backward = x->backward;
     } else {
         sl->tail = x->backward;
     }
     while (sl->level > 1 && sl->header->level[sl->level-1].forward == NULL) 
         sl->level--;
     sl->length--;
 }
 
 int slDelete(skiplist *sl, double score) {
     skiplistNode *update[SKIPLIST_MAXLEVEL], *node;
     int i;
 
     node = sl->header;
     for(i = sl->level-1; i >= 0; i--) {
         while (node->level[i].forward && node->level[i].forward->score < score) {
             node = node->level[i].forward;
         }
         update[i] = node;
     }
     node = node->level[0].forward;
     if (node && score == node->score) {
         slDeleteNode(sl, node, update);
         slFreeNode(node);
         return 1;
     } else {
         return 0;
     }
     return 0;
 }
 
 int slSearch(skiplist *sl, double score) {
     skiplistNode *node;
     int i;
 
     node = sl->header;
     for (i = sl->level-1; i >= 0 ;i--) {
         while(node->level[i].forward && node->level[i].forward->score < score) {
             node = node->level[i].forward;
         }
     }
     node = node->level[0].forward;
     if (node && score == node->score) {
         printf("Found %d\n",(int)node->score);
         return 1;
     } else {
         printf("Not found %d\n", (int)score);
         return 0;
     }
 }
 
 void slPrint(skiplist *sl) {
     skiplistNode *node;
     int i;
     for (i = 0; i < SKIPLIST_MAXLEVEL; i++) {
         printf("LEVEL[%d]: ", i);
         node = sl->header->level[i].forward;
         while(node) {
             printf("%d -> ", (int)(node->score));
             node = node->level[i].forward;
         }
         printf("NULL\n");
     }
 }
 
 #ifdef SKIP_LIST_TEST_MAIN
 int main() {
     srand((unsigned)time(0));
     int count = 20, i;
 
     printf("### Function Test ###\n");
 
     printf("=== Init Skip List ===\n");
     skiplist * sl = slCreate();
     for ( i = 0; i < count; i++) {
         slInsert(sl,i);
     }
     printf("=== Print Skip List ===\n");
     slPrint(sl);
 
     printf("=== Search Skip List ===\n");
     for (i = 0; i < count; i++) {
         int value = rand()%(count+10);
         slSearch(sl, value);
     }
     printf("=== Delete Skip List ===\n");
     for (i = 0; i < count+10; i+=2) {
         printf("Delete[%d]: %s\n", i, slDelete(sl, i)?"SUCCESS":"NOT FOUND");
     }
     slPrint(sl);
 
     slFree(sl);
     sl = NULL;
 }
 #endif
