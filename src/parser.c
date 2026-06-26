#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "pe.h"

const char *machine_to_string(uint16_t machine) {
      switch (machine) {
	      case 0x14C:
		      return "Intel x86";
	      case 0x8664:
		      return "AMD64 (X64)";
	      case 0x1c0:
		      return "ARM";
	      case 0xaa64:
		      return "ARM64";
	      default:
		      return "Unknown Architecture.";
      }
}

const char *pe_format(uint16_t magic) {
      switch (magic) {
              case 0x10b:
		      return "PE32 (32-bit)";
	      case 0x20b:
		      return "PE32+ (64-bit)";
              default:
		      return "Unknown PE Format.";
      }
}

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
    while(count != 64){
    	printf("%02X ", buffer[count]);
	count++;
	if(count%8 == 0) {
	   printf("\n");
	}
    }
    /*DOS HEADER*/
    IMAGE_DOS_HEADER *dos = (IMAGE_DOS_HEADER *)buffer;

    /*NT HEADERS*/
    unsigned char *pe = (buffer + dos->e_lfanew);
    IMAGE_NT_HEADER *nt = (IMAGE_NT_HEADER *)pe; 
    
    printf("========== %-10s ==========\n", "DOS HEADER");
    printf("\n");
    printf(" %-25s: 0x%X\n","Magic", dos->e_magic);
    printf(" %-25s: 0x%X\n","PE offset",dos->e_lfanew);
    printf("\n");
    printf("========== %-10s ==========\n", "NT HEADER");
    printf("\n");
    printf(" %-25s: 0x%X\n","PE_SIGNATURE", nt->pe_signature);
    printf("\n");
    printf("---------- %-10s ----------\n", "FILE HEADER");
    printf("\n");
    printf(" %-25s: 0x%X (%s)\n","Machine", nt->FileHeader.Machine, machine_to_string(nt->FileHeader.Machine));
    printf(" %-25s: %u\n","NumberOfSections",nt->FileHeader.NumberOfSections);
    printf(" %-25s: 0x%X\n", "TimeDateStamp",nt->FileHeader.TimeDateStamp);
    printf(" %-25s: 0x%X\n","PointerToSymbolTable", nt->FileHeader.PointerToSymbolTable);
    printf(" %-25s: 0x%X\n", "NumberOfSymbols",nt->FileHeader.NumberOfSymbol);
    printf(" %-25s: %u\n","SizeOfOptionalHeader", nt->FileHeader.SizeOfOptionalHeader);
    printf(" %-25s: 0x%X\n","Characteristics", nt->FileHeader.Characteristics);
    printf("\n");
    printf("---------- %-10s ----------\n","OPTIONAL HEADER");
    printf(" %-25s: 0x%X (%s)\n", "Magic", nt->OptionalHeader.Magic, pe_format(nt->OptionalHeader.Magic));
    fclose(fp);
    return 0;
}
