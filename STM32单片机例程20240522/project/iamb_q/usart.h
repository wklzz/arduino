#ifndef __USART_H
#define __USART_H





#include "stm32f10x.h"
#include "stdio.h"


void Usart1Init(uint32_t baudrate); 
void Usart2Init(uint32_t baudrate); 
void Usart3Init(uint32_t baudrate); 


void UsartSendByte(USART_TypeDef* USARTx, uint8_t byte); 
void UsartSendString(USART_TypeDef *USARTx, uint8_t *buf, uint32_t len); 


#endif

