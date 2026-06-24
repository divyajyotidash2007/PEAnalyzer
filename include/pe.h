#ifndef PE_H
#define PE_H

#include <stdint.h>

typedef struct _IMAGE_DOS_HEADER {
    uint16_t e_magic;
    uint8_t reserved[58]; 
    uint32_t e_lfanew;
} IMAGE_DOS_HEADER;

typedef struct _IMAGE_FILE_HEADER {
    uint16_t Machine;
    uint16_t NumberOfSections;
    uint32_t TimeDateStamp;
    uint32_t PointerToSymbolTable;
    uint32_t NumberOfSymbol;
    uint16_t SizeOfOptionalHeader;
    uint16_t Characteristics;
} IMAGE_FILE_HEADER;

typedef struct _IMAGE_OPTIONAL_HEADER {
    /*Standar Fields*/
    uint16_t Magic;
    uint8_t MajorLinkerVersion;
    uint8_t MinorLinkerVersion;
    uint32_t SizeOfCode;
    uint32_t SizeOfInitializedData;
    uint32_t SizeOfUninitializedData;
    uint32_t AddressOfEntryPoint;
    uint32_t BaseOfCode;
} IMAGE_OPTIONAL_HEADER;

typedef struct _IMAGE_NT_HEADER {
    uint32_t pe_signature;
    IMAGE_FILE_HEADER FileHeader;
    IMAGE_OPTIONAL_HEADER OptionalHeader;
} IMAGE_NT_HEADER; 






#endif
