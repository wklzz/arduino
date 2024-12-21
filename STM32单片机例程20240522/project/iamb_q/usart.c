#include "usart.h"






//重定义fputc函数
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, ch);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
    
    return ch; 
}





/**
  * @author    b_q
  * @date      2020/4/20
  * @brief     串口1初始化
  * @param     
  * @retval
  * @attention
  */
void Usart1Init(uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    
    // usart1           PA9    PA10
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_9; 
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_IN_FLOATING; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    
    USART_DeInit(USART1); 
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
    
    USART_InitTypeDef USART_InitStructure;
    
    USART_InitStructure.USART_BaudRate            = baudrate;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b; 
    USART_InitStructure.USART_StopBits            = USART_StopBits_1; 
    USART_InitStructure.USART_Parity              = USART_Parity_No; 
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx; 
    USART_Init(USART1, &USART_InitStructure); 
    
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);
    USART_ClearFlag(USART1, USART_FLAG_TC); 
    
    
    
    NVIC_InitTypeDef NVIC_Structure; 
    
    NVIC_Structure.NVIC_IRQChannel                   = USART1_IRQn; 
    NVIC_Structure.NVIC_IRQChannelPreemptionPriority = 0; 
    NVIC_Structure.NVIC_IRQChannelSubPriority        = 0; 
    NVIC_Structure.NVIC_IRQChannelCmd                = ENABLE; 
    NVIC_Init(&NVIC_Structure); 
}







/**
  * @author    b_q
  * @date      2020/4/20
  * @brief     串口2初始化
  * @param     
  * @retval
  * @attention
  */
void Usart2Init(uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    
    // usart2           PA2    PA3
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    
    
    USART_DeInit(USART2); 
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 
    
    USART_InitTypeDef USART_InitStructure; 
    
    USART_InitStructure.USART_BaudRate            = baudrate;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b; 
    USART_InitStructure.USART_StopBits            = USART_StopBits_1; 
    USART_InitStructure.USART_Parity              = USART_Parity_No; 
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx; 
    USART_Init(USART2, &USART_InitStructure); 
    
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART2, ENABLE);
    USART_ClearFlag(USART2, USART_FLAG_TC); 
    
    
    
    NVIC_InitTypeDef NVIC_Structure; 
    
    NVIC_Structure.NVIC_IRQChannel                   = USART2_IRQn; 
    NVIC_Structure.NVIC_IRQChannelPreemptionPriority = 0; 
    NVIC_Structure.NVIC_IRQChannelSubPriority        = 0; 
    NVIC_Structure.NVIC_IRQChannelCmd                = ENABLE; 
    NVIC_Init(&NVIC_Structure); 
}








/**
  * @author    b_q
  * @date      2020/4/20
  * @brief     串口3初始化
  * @param     
  * @retval
  * @attention
  */
void Usart3Init(uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,  ENABLE); 
    
    
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    
    // usart3           PB10   PB11
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure); 
    
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_IN_FLOATING;  
    GPIO_Init(GPIOB, &GPIO_InitStructure); 
    
    
    
    USART_DeInit(USART3); 
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 
    
    USART_InitTypeDef USART_InitStructure; 
    
    USART_InitStructure.USART_BaudRate            = baudrate;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b; 
    USART_InitStructure.USART_StopBits            = USART_StopBits_1; 
    USART_InitStructure.USART_Parity              = USART_Parity_No; 
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx; 
    USART_Init(USART3, &USART_InitStructure); 
    
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART3, ENABLE);
    USART_ClearFlag(USART3, USART_FLAG_TC); 
    
    
    
    NVIC_InitTypeDef NVIC_Structure; 
    
    NVIC_Structure.NVIC_IRQChannel                   = USART3_IRQn; 
    NVIC_Structure.NVIC_IRQChannelPreemptionPriority = 0; 
    NVIC_Structure.NVIC_IRQChannelSubPriority        = 0; 
    NVIC_Structure.NVIC_IRQChannelCmd                = ENABLE; 
    NVIC_Init(&NVIC_Structure); 
}







/**
  * @author    b_q
  * @date      2016/11/7
  * @brief     发送一个字节
  * @param     USARTx 串口  c 发送的字节
  * @retval    
  * @attention 
  */
void UsartSendByte(USART_TypeDef* USARTx, uint8_t byte)
{
    USART_SendData(USARTx, byte);
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET); 
}




/**
  * @author    b_q
  * @date      2016/11/7
  * @brief     发送一串字符
  * @param     USARTx 串口  c 发送的字节
  * @retval
  * @attention
  */
void UsartSendString(USART_TypeDef *USARTx, uint8_t *buf, uint32_t len) 
{ 
    do
    {
        UsartSendByte(USARTx, *buf++); 
    }
    while(--len); 
}
