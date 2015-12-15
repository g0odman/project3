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

    //-----------------
//    size_t index_arr[MAX_CHILD_NUM];
//    int str_pos = 1, arr_pos = 0;
//    bool cont = true;
//
//    //find end of first value:
//    while(line[str_pos] != '(' && line[str_pos] != ')'
//    		&& line[str_pos] != '\0') {
//    	str_pos++;
//    }
//    if(line[str_pos] == '\0') {
//    	index_arr[arr_pos] = -1;
//    	cont = false;
//    }
//    else if(line[str_pos] == ')') {
//    	index_arr[arr_pos]=str_pos;
//    	cont = false;
//    }
//    else {
//    	index_arr[arr_pos]=str_pos;
//    }
//
//    //find start and end of each child:
//	for(arr_pos = 1; arr_pos<MAX_CHILD_NUM && cont; arr_pos++){
//		int depth = 1;
//		while(depth > 0){
//			str_pos++;
//			if(line[str_pos] == '(') { depth++; }
//			else if(line[str_pos] == ')') { depth--; }
//			else if(line[str_pos] == '\0') {
//				index_arr[arr_pos] = -1;
//				cont = false;
//			}
//		}
//		str_pos++; //increment once found end
//		index_arr[arr_pos] = str_pos;
//	}
    //-----------------

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
                exit(EXIT_SUCCESS);
            }
        }
        //Go up one level
        if(line[i] == ')')
            j--;
        i++;
    }

    //Copy string
    char *temp = malloc(i+1);
    strncpy(temp,line,i);
    temp[i] = '\0';
    if(!setValue(new,temp))
        exit(EXIT_SUCCESS);

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
