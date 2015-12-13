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
 * bla
 */
SPTREE* parseStringToTree(char* string, PARSING_MSG* msg);

/**
 * bla
 */
double calcTreeValue(SPTREE* tree, PARSING_MSG* msg);

#endif /* AUX_H_ */
