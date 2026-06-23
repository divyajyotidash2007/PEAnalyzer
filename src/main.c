#include <stdio.h>
#include "parser.h"

#define SUCCESS 0
#define FAILURE 1


int main(int argc,char *argv[]) {
    if(argc == 1){
      printf("Usage: ./main.c <filepath>\n");
      return 1;
    }

    if(parse_file(argv[1]) != SUCCESS){
      printf("Failure to parse file.\n");
      return 1;  
    }

    return 0;
}


