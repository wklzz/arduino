#ifndef __MAGICRF_H
#define __MAGICRF_H




#include "main.h"






typedef struct {
    uint8_t prefix;
    uint8_t type;
    uint8_t command;
    uint8_t length[2];
    uint8_t data[250]; 
} MagicRF_Type;                 // 读头层协议



typedef struct {
    uint8_t ant;
    int8_t  rssi;
    uint8_t pc[2];
    uint8_t epc[32];
} Tag_Type;                 // 读头层协议




int MagicRFInit(void); 
int MagicRFTest(void); 




#endif /* __MAGICRF_H */

