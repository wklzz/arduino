#ifndef __QUEUE_H
#define __QUEUE_H



#include "stm32f10x.h"



typedef struct
{
    uint32_t front; 
    uint32_t rear; 
    const uint32_t size; 
    uint8_t * const buff; 
} Queue_Type; 




extern Queue_Type rsp_queue_t; 


uint32_t QueueIn(Queue_Type *que_t, uint8_t byte);
uint32_t QueueOut(Queue_Type *que_t, uint8_t *byte);
uint32_t QueueUsing(Queue_Type *que_t); 



#endif

