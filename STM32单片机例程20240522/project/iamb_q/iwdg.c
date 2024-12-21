#include "stm32f10x.h"
#include "iwdg.h"









/**
  * @author    b_q 
  * @date      2017/5/11
  * @brief     ���ö������Ź�
  * @param     prescaler ��Ƶϵ��  reload ����ֵ
  * @retval    
  * @attention ʱ�����ڲ�����ʱ���ṩ 30 kHz - 60 KHz
  */
void IwdgInit(uint8_t prescaler, uint16_t reload)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);   // IWDG_PR, IWDG_RLRдʹ��
    
    IWDG_SetPrescaler(prescaler);                   // ���÷�Ƶ��Ϊ256
    IWDG_SetReload(reload);                         // ���ü�������ֵ
    IWDG_ReloadCounter();                           // ����IWDG������
    IWDG_Enable();
}




