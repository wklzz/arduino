/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H



#include "stm32f10x.h"
#include "b_qlog.h"
#include "usart.h"




typedef struct 
{ 
    uint32_t tick; 
    uint32_t beept; 
} System_Type; 



extern volatile System_Type system_t; 

void delay_ms(uint32_t xms); 


#endif
