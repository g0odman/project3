#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SP_Aux.h"

/**
 *  Main function, parses given input and calculates result. Prints
 *  all necsesary things.
 */
void parse(char * line){
    if(strncmp(line,"(<>)", 4) == 0 && strlen(line) == 5){
        if(printf("Exiting...\n")!= 0){
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    bool * valid = malloc(sizeof(bool));
    *valid = true;
    //make trees and validate that they were succesfull:
    SP_TREE *root = split(line);
    double out =  spTreeEval(root,valid);
    if(*valid)
        printf("Res = %f\n", out);
    else
        printf("Invalid Result\n");
    spTreeDestroy(root);
    free(valid);
}

SP_TREE *split(char *line){
    //Value for node
    SP_TREE *new;

    if((new = spTreeCreate()) == NULL){
        printf("Unexpected error occured!");
        exit(EXIT_FAILURE);
    }

    //j is the number of brackets seen, i is the current place
    int j = 1,i=1;

    while(j > 0){
        //recursively parse children:
        if(line[i] == '('){
        	j++;
        	if(j == 1)
        		spTreePush(new,split(line+i)); //test whether this works!
        }
        //Go up one level
        if(line[i] == ')')
            j--;
        i++;
    }

    //Copy string
    new->value = malloc(i+1);
    strncpy(new->value,line,i);

    //update type
    new->type = getType(getRootStr(new));
    return new;
}

double operate(double x, double y, SP_TREE_TYPE op,bool * valid){
    *valid = (isValid(op,x,y) ? *valid : false);
    switch (op){
        case PLUS:
            return x+y;
        case MINUS:
            return  x - y;
        case MULTIPLICATION:
            return  x * y;
        case DIVISION:
            return  x/y;
        case DOLLAR:
            return ((y-x+1)*(y+x))/2;
        default :
            return 0;
    }
}

SP_TREE_TYPE getType(char *s){
    
	//Check if it is a number
    if(strlen(s)!=1 || (s[0] >= '0' && s[0] <= '9')) { return NUMBER; }
    
    //return the correct value
    switch(s[0]) {
        case '+'  :
             return PLUS;
        case '-'  :
             return MINUS;
        case '$'  :
             return DOLLAR;
        case '*'  :
             return MULTIPLICATION;
        case '/'  :
             return DIVISION;
        default : /* Optional */
             return UNKNOWN;
    }
}

bool isValid(SP_TREE_TYPE op, double x, double y){
    switch(op){
        case PLUS:
        case MINUS:
        case MULTIPLICATION:
            return  true;
        case DIVISION:
            return  y != 0;
        case DOLLAR:
            return y >= x;
        default :
            return false;
    }
}

double spTreeEval(SP_TREE *tree, bool * valid){
    //leaf:
    if(tree->type == NUMBER && tree->size == 0)
        return atoi(getRootStr(tree));

    //calculate op on children:
    double out = atoi(getRootStr(tree->children[0]));
    if(tree->size ==1)
        return operate(0,out,tree->type,valid);

    for(int i=1; i < tree->size; i++){
        out = operate(out,spTreeEval(tree->children[i],valid),tree->type,valid);
    }
    return out;
}
