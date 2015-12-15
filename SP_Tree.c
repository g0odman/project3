#include <string.h>
#include "SP_Tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * Create a new empty Tree.
 *
 * @return
 *		A pointer to a new empty Tree, if any error occurred NULL is returned.
 */
SP_TREE* spTreeCreate() {
	
    //allocate pointer:
    SP_TREE *s;
    if((s = (SP_TREE*)malloc(sizeof(SP_TREE)))==NULL)
        return NULL;
    
    //initialize:
    s->children = malloc(sizeof(SP_TREE *)*10);
    s->value = NULL;
    return s;
}
    

/**
 * Free all allocation associated with the Tree.
 * @param
 * SP_TREE* Tree - Pointer to a Tree which will be deleted.
 * 					 After invoking spTreeDestroy, Tree will no longer be valid to use.
 * 					 If Tree==NULL nothing happens.
 */
void spTreeDestroy(SP_TREE* tree) {
	
	//check node isn't null:
	if(tree == NULL) { return; }
	
        for(int i =0;i <10;i++){
            if(tree->children[i] !=NULL)
		spTreeDestroy(tree->children[i]);
        }
        free(tree->children);
        free(tree->value);
	free(tree);
}
/**
 * Pushes a child to the tree.
 * @param
 * SP_TREE* Tree - Pointer to a Tree into which the child will be inserted.
 *
 * SP_TREE *child - child to be inserted.
 *
 * @return -
 *          boolean indicating whether the push was succesful.
 */
void spTreePush(SP_TREE* tree,SP_TREE *child) {
	
    if(child == NULL)
        return false;
    if(tree->size == 10)
        return false;
    tree->children[tree->size] = child;
    tree->size ++;
    return true;
}
/**
 * Returns a copy of the string of the root node.
 *
 * @param
 * SP_TREE* Tree - Pointer to a Tree from which to extract string.
 * 
 * @return
 *              A copy of the substring representing the root.
 */

char * getRootStr(SP_TREE *tree){
    char * close = strchr(tree->value + 1,')'), * open = strchr(tree->value + 1,'(');
    int length = (int)( ( close < open ? close: open )  - tree->value -1);
    if(open == NULL)
        length = (int)(close - tree->value -1);
    char * ans = malloc(length+1);
    strncpy(ans,tree->value +1,length);
    return ans;
}

/**
 * Returns a copy of the string of the index-th child.
 *
 * @param
 * SP_TREE* Tree - Pointer to a Tree from which to take the child.
 *
 * int index - Child for which value is to be returned.
 * 
 * @return
 *              A copy of the substring representing the root.
 */
char * getChildAtIndex(SP_TREE *tree,int index){
    char * value = tree->children[index]->value;
    char * ans = malloc(strlen(value));
    strncpy(value,ans,strlen(ans));
    return ans;
}

