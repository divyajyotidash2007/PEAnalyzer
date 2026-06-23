#include <stdio.h>
#include <stdlib.h>

int parse_file(const char *filepath){
    FILE* fp = fopen(filepath, "rb");

    if(fp == NULL){
      perror("fopen");
      return 1;
    }
    
    printf("File opened successfully\n");
     
    fseek(fp,0,SEEK_END);
    size_t filesize = ftell(fp);
    rewind(fp);
    printf("File size: %zu\n", filesize);
    
    /*Allocating memory buffer to copy the contents of executable as bytes*/
    unsigned char *buffer = malloc(filesize);
    
    fread(buffer,1,filesize,fp);

    /*verifying bytes*/
    int count = 0;
    while(count != 32){
    	printf("%02X ", buffer[count]);
count++;
	if(count%4 == 0) {
	   printf("\n");
	}
    }


    fclose(fp);
    return 0;
}
