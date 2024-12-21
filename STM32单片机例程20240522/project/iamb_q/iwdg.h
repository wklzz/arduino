#ifndef __IWDG_H
#define __IWDG_H



#include "stm32f10x.h"


#define   FeedDog()              IWDG_ReloadCounter()

     
void IwdgInit(uint8_t IWDG_Prescaler, uint16_t reload);



#endif

