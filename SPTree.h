/*
 * SPTree.h
 *
 * Represents a tree data structure, with string values
 *
 */

#ifndef SPTREE_H_
#define SPTREE_H_

/**
 * Defines an error messaging mechanism for SPTree. each
 * operation will receive a pointer to SPTREE_ERROR_MSG,
 * and will return the error message in it.
 */
typedef enum {
	SUCCESS = 0,
	INVALID_ARG = -1,
	UNKNOWN_ERROR = -2
} SPTREE_ERROR_MSG;

/**
 * Represents the tree data structure. Define struct sp_tree
 * in SPTree.c
 */
typedef struct sp_tree SPTREE;


/**
 * Creates a new tree, and returns a pointer to it. The input msg
 * is a pointer to SPTREE_ERROR_MSG, if it is NULL it will be ignored,
 * otherwise its value will contain the relevant error msg.
 *
 */
SPTREE* spCreateTree(SPTREE_ERROR_MSG* msg);

/**
 * Frees all memory associated with the input tree, and it will no
 * longer be valid for use. If input is NULL, no effect.
 */
void spDestroyTree(SPTREE* tree);

/**
 *bla
 */
char* spGetValue(SPTREE* tree, SPTREE_ERROR_MSG* msg);

//TODO getChild(index)

//TODO insertChild(child)

//TODO deleteChild(index)

#endif /* SPTREE_H_ */
