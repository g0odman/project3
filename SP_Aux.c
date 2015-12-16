#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SP_Aux.h"

/**
 *  Main function, parses given input and calculates result. Prints
 *  all necsesary things.
 */
void parse(char * line){
	//check whether exit command:
    if(strncmp(line,"(<>)", 4) == 0 && strlen(line) == 5){
        if(printf("Exiting...\n")!= 0){
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }

    //make tree and validate that they were succesfull:
    bool valid = true;
    SP_TREE *root = split(line);

    //evaluate:
    double out =  spTreeEval(root,&valid);
    if(valid)
        printf("Res = %f\n", out);
    else
        printf("Invalid Result\n");

    spTreeDestroy(root);
}

SP_TREE *split(char *line){
    //Value for node
    SP_TREE *new;

    if((new = spTreeCreate()) == NULL){
        printf("Unexpected error occured!");
        exit(EXIT_SUCCESS);
    }

    //j is the number of brackets seen, i is the current place
    int j = 1,i=1;
    while(j > 0){  //recursively parse children:
        if(line[i] == '(' && (++j) == 2){
        	//if closed brackets on child, parse it:
            if(!spTreePush(new,split(line+i))){
                if(printf("Unexpected error occured!")!=0)
                    exit(EXIT_FAILURE);
                exit(EXIT_SUCCESS);
            }
        }
        //Go up one level
        if(line[i] == ')')
            j--;
        i++;
    }

    //Copy the relevant string for this node:
    int length = 1;
    while(line[length] != '(' && line[length] != ')') { length++; }
    length--;
	char * temp = malloc(length+1);
	strncpy(temp,line +1,length);
    temp[length] = '\0';
    if(!setValue(new,temp))
        exit(EXIT_SUCCESS); //why success?
    free(temp);

    return new;
}

double operate(double x, double y, SP_TREE_TYPE op, bool * valid){
    *valid = (isValid(op,x,y) ? *valid : false);
    //perform relevant op on inputs
    switch (op){
        case PLUS:
            return x + y;
        case MINUS:
            return  x - y;
        case MULTIPLICATION:
            return  x * y;
        case DIVISION:
            return  x / y;
        case DOLLAR:
            return ((y-x+1)*(y+x))/2;
        default :
            return 0;
    }
}

bool isValid(SP_TREE_TYPE op, double x, double y){
	//test relevant case for op:
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

    //leaf, return value:
    if(tree->type == NUMBER){
        return atoi(getRootStr(tree));
    }

    //otherwise, calculate op on first child, first:
    double out = spTreeEval(tree->children[0],valid);

    //In case of negative number
    if(tree->size ==1)
        return operate(0,out,tree->type,valid);

    //then continue recursively calculating children,
    //and performing the op on them
    for(int i=1; i < tree->size; i++){
        double temp = spTreeEval(tree->children[i],valid);
        out = operate(out,temp,tree->type,valid);
    }

    return out;
}
