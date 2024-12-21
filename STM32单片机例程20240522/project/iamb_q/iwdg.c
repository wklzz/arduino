#include "stm32f10x.h"
#include "iwdg.h"









/**
  * @author    b_q 
  * @date      2017/5/11
  * @brief     配置独立看门狗
  * @param     prescaler 分频系数  reload 重载值
  * @retval    
  * @attention 时钟有内部低速时钟提供 30 kHz - 60 KHz
  */
void IwdgInit(uint8_t prescaler, uint16_t reload)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);   // IWDG_PR, IWDG_RLR写使能
    
    IWDG_SetPrescaler(prescaler);                   // 设置分频器为256
    IWDG_SetReload(reload);                         // 设置计数重置值
    IWDG_ReloadCounter();                           // 重置IWDG计数器
    IWDG_Enable();
}




