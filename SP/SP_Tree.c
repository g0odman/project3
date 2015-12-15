#include <string.h>
#include "SP_Tree.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Create a new empty Tree.
 *
 * Messages:
 * 		SP_TREE_ERROR_ALLOCATION_FAILED - In case allocation failed.
 * 		SP_TREE_SUCCESS - In case creation of the Tree succeeded.
 *
 * @param
 * 		SP_TREE_MSG* msg - Pointer which has the memory location where the message
 * 					   		will be stored. if msg==NULL then the function doesn't
 * 							set the value of *msg.
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
	free(tree);
}

char * getRootStr(SP_TREE *tree){
    int length = (int) (strchr(tree->value,')') - tree->value-1);
    char * ans = malloc(length);
    strncpy(ans,tree->value +1,length);
    return ans;
}

char * getChildAtIndex(SP_TREE *tree,int index){
    char * value = tree->children[index]->value;
    char * ans = malloc(strlen(value));
    strncpy(value,ans,strlen(ans));
    return ans;
}

