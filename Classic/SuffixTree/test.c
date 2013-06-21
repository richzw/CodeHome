#include "suffix_tree.h"
#include <stdio.h>

int main()
{
  /*Will hold the position of the substring if exists in the tree.*/
	DBL_WORD position;
	
	/*Create the suffix tree*/
	SUFFIX_TREE* tree = ST_CreateTree("mississippi", 11);
	
	/*Print the suffix tree.*/
	ST_PrintTree(tree);

	/*Search for a substring in the tree and return its position if exists.*/
	position = ST_FindSubstring(tree, "ssis", 4);
	
	/*Print the position of the substring*/
	printf("\nPosition of ssis in mississippi is %ld.\n\n", position);
	
	/*Delete the tree and all its nodes.*/
	ST_DeleteTree(tree);
}
