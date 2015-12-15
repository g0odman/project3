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
 * Recieve a string token and check its type
 *
 *
 * @param
 * 		char * token - An input token. Checks if it is valid,
 * 				and if so then find its type.
 * @return
 *              The type of the token (as an enum).
 */
SP_TREE_TYPE getType(char *s);

bool isNumber(char * s);
/**
 * Perform the given mathematical operation on the two input numbers.
 *
 *
 * @param
 * 		double x - The first number
 * @param
 * 		double y - the second number;
 * @param
 * 		SP_STACK_ELEMENT_TYPE op - The operation to perform.
 * @param
 * 		double * ans - A pointer into which to store the result.
 * @return
 *              If the operation was valid, then return true, and store result
 *              		in *ans. Otherwise return false.
 */
double operate(double x,double y, SP_TREE_TYPE op);

/**
 * Performs a single mathematical operation on the two stacks, as described in
 * the assignement guidelines.
 *
 *
 * @param
 * 		SP_STACK ** numbers - A (pointer to) stack containing the numbers
 * @param
 * 		SP_STACK ** operations - A (pointer to) stack containing the operations.
 * @return
 *              Perform the top operation in operations, on the top two values in numbers
 *                                  If it was a succes return true, else false.
 */
double spTreeEval(SP_TREE *tree,bool *valid);
SP_TREE *split(char *line);
#endif /* SP_Aux_H_ */
