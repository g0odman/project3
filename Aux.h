/*
 * Aux.h
 *
 * contains auxillary functions, for main.c
 *
 */

#ifndef AUX_H_
#define AUX_H_
#include "SPTree.h"

/**
 * Defines error mechanism for parsing functions. Each function
 * will receive an optional pointer to a PARSING_MSG object,
 * in which it will return whether operation was succesfull.
 */
typedef enum {
	SUCCESS = 0,
	UNKNOWN_ERROR = -1
} PARSING_MSG;

/**
 * Parses given string, assuming it is in lisp-style format.
 * Creates the corresponding tree, and returns a pointer to it
 * if successful, otherwise NULL.
 *
 * If the input msg isn't NULL, will contain the relevant PARSING_MSG,
 * otherwise it won't be affected.
 *
 */
SPTREE* parseStringToTree(char* string, PARSING_MSG* msg);

/**
 * Calculates the given tree's value, as described in the homework
 * assignment. If successful, returns the value.
 *
 * The input msg is used to report errors if they occur, if it isn't
 * NULL, it will contain the relevant PARSING_MSG at the end.
 *
 */
double calcTreeValue(SPTREE* tree, PARSING_MSG* msg);

#endif /* AUX_H_ */
