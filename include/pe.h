#ifndef PE_H
#define PE_H

#include <stdint.h>

typedef struct{
    uint16_t e_magic;
    uint8_t reserved[58]; 
    uint32_t e_lfanew;
} IMAGE_DOS_HEADER;




#endif
