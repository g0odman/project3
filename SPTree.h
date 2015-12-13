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


#endif /* SPTREE_H_ */
