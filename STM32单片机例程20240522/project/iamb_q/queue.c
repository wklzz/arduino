#include "queue.h"



// ������ն�ͷ�ظ����ݻ������
// �����ڴ���䣬������� 4K 
static uint8_t rspbuff[4096] = {0}; 

Queue_Type rsp_queue_t = {.size = 4096, .buff = rspbuff}; 






/**
  * @author    b_q
  * @date      2016/12/17
  * @brief     ��ջ
  * @param
  * @retval
  * @attention �κ�ʱ��������ջ
  */
uint32_t QueueIn(Queue_Type *que_t, uint8_t byte)
{
    if(que_t->rear >= que_t->size)
        que_t->rear = 0; 
    
    que_t->buff[que_t->rear] = byte; 
    que_t->rear              = que_t->rear + 1; 
    
    return 0;
} 


/**
  * @author    b_q
  * @date      2016/12/17
  * @brief     ��ջ
  * @param
  * @retval    0 ������ 1 ������
  * @attention
  */
uint32_t QueueOut(Queue_Type *que_t, uint8_t *byte)
{
    if(que_t->front == que_t->rear) 
        return 1; 
    
    if(que_t->front >= que_t->size)
        que_t->front = 0; 
    
    // out
    *byte        = que_t->buff[que_t->front];
    que_t->front = que_t->front + 1;
    
    return 0;
}


/**
  * @author    b_q
  * @date      2016/12/17
  * @brief     ʹ����
  * @param
  * @retval    0 ������ 1 ������
  * @attention
  */
uint32_t QueueUsing(Queue_Type *que_t)
{ 
    if(que_t->rear >= que_t->front) 
    { 
        return (que_t->rear - que_t->front); 
    } 
    else 
    { 
        return (que_t->size + que_t->rear - que_t->front); 
    } 
} 



