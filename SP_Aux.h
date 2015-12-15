#ifndef SP_Aux_H_
#define SP_Aux_H_
#include "SP_Tree.h"


/**
 * Recieve a line and parse it
 *
 *
 * @param
 * 		string line - An input line, check if it is valid.
 * 				If so then parse it and print result, else
 * 				print error.
 * @return
 *              The result of the equation.
 */
void parse(char * line);

/**
 * create SP_TREE from string
 *
 *
 * @param
 * 		string line - An input line, split it according to 
 * 				LISP style brackets.
 * 				print error.
 * @return
 *              A SP_TREE representing the string.
 */
SP_TREE *split(char *line);

/**
 * Perform the given mathematical operation on the two input numbers.
 *
 *
 * @param
 * 		double x - The first number
 * @param
 * 		double y - the second number;
 * @param
 * 		SP_TREE_TYPE op - The operation to perform.
 * @param
 * 		bool *valid- A pointer to a boolean indicating
 * 		    whether or not the operation is valid.
 * @return
 *              The result of the mathematical operation
 */
double operate(double x,double y, SP_TREE_TYPE op, bool * valid);
/**
 * Recieve a string and check its type
 *
 *
 * @param
 * 		char * token - An input token. Checks if it is valid,
 * 				and if so then find its type.
 * @return
 *              The type of the token (as an enum).
 */
SP_TREE_TYPE getType(char *s);
/**
 * Check if a given mathematical operation is valid.
 *
 *
 * @param
 * 		double x - The first number
 * @param
 * 		double y - the second number;
 * @param
 * 		SP_TREE_TYPE op - The operation to perform.
 * @return
 *              Whether the operation was valid or not.
 */

bool isValid(SP_TREE_TYPE op, double x, double y);

/**
 * Recursively evaluate the tree.
 *
 *
 * @param
 * 		SP_TREE *tree - The tree to evaluate.
 * @param
 * 		bool *valid - A boolean checking whether the result was valid or not.
 * @return
 *          The result of the mathematical operation from the tree 
 *                  down.
 */
double spTreeEval(SP_TREE *tree,bool *valid);
#endif /* SP_Aux_H_ */
