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
