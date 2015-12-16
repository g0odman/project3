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
        exit(EXIT_SUCCESS);
    }

    //j is the number of brackets seen, i is the current place
    int j = 1,i=1;

    while(j > 0){
        //recursively parse children:
        if(line[i] == '(' && (++j) == 2){
            if(!spTreePush(new,split(line+i))){
                if(printf("Unexpected error occured!")!=0)
                    exit(EXIT_FAILURE);
                exit(EXIT_SUCCESS); //why is this a success?
            }
        }
        //Go up one level
        if(line[i] == ')')
            j--;
        i++;
    }

    //Copy the relevant string only:
    char * close = strchr(line + 1,')'), * open = strchr(line,'(');
	int length = (int)( ( close < open ? close: open )  - line +1);
	if(open == NULL)
		length = (int)(close - line +1);
	char * temp = malloc(length+1);
	strncpy(temp,line +1,length);
    temp[length] = '\0';
    if(!setValue(new,temp))
        exit(EXIT_SUCCESS); //why success?
    free(temp);  //need to free!!

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
    if(tree->type == NUMBER){
        return atoi(getRootStr(tree));
    }

    //calculate op on children:
    double out = spTreeEval(tree->children[0],valid);

    //In case of negative number
    if(tree->size ==1)
        return operate(0,out,tree->type,valid);

    for(int i=1; i < tree->size; i++){
        double temp = spTreeEval(tree->children[i],valid);
        out = operate(out,temp,tree->type,valid);
    }

    return out;
}
