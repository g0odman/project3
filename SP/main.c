#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "SP_Aux.h"

#define MAX_LINE_LENGTH 1024

int main(){
	
	//allocate buffer to read to:
    char *line = (char*)malloc(MAX_LINE_LENGTH +1);
    
    //main loop:
    while (fgets(line,MAX_LINE_LENGTH,stdin)!=NULL){

        parse(line); //see SP_Aux
        
    }
    
    printf("Exiting...\n");
    free(line);
    return 0;
}
