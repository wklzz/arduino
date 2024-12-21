#include "main.h"

#include "iwdg.h"
#include "magicrf.h"


// 优化等级 -o1 或更高时，必须定义为 volatile 
volatile System_Type system_t = {0}; 





/**
  * @author    b_q 
  * @date      2018/5/10
  * @brief     系统滴答时钟
  * @param     
  * @retval    
  * @attention 
  */
void SystickInit(uint32_t freq)
{
    RCC_ClocksTypeDef rcc_clock; 
    RCC_GetClocksFreq(&rcc_clock); 
    
    SysTick_Config(rcc_clock.HCLK_Frequency / freq); 
} 



/**
  * @author    b_q 
  * @date      2018/5/10
  * @brief     系统滴答时钟
  * @param     
  * @retval    
  * @attention 
  */
void delay_ms(uint32_t xms)
{ 
    uint32_t tick = system_t.tick + xms; 
    
    FeedDog(); 
    while(system_t.tick < tick) 
    { 
        // 定时喂狗
        if((system_t.tick & 0x3F) == 0)
            FeedDog(); 
    }
}





/**
  * @author    b_q
  * @date      2020/2/21
  * @brief     主程序入口
  * @param     
  * @retval    
  * @attention 
  */
int main(void) 
{ 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    SystickInit(1000);                                      // 启用系统时钟
    LogInit();                                              // 初始化 RTT 日志，通过jlink工具可查看运行数据
    
    IwdgInit(IWDG_Prescaler_128, 0x64);                     // 开启看门狗
    
    Log("\r\n\n\n %s %s", __DATE__, __TIME__); 
    
    Log("\r\n Checking Reader ... "); 
    if(MagicRFInit() == 0) 
    { 
        Success("Pass"); 
    }
    else 
    { 
        Error("Fail"); 
    }
    
    
    for( ; ; ) 
    { 
        MagicRFTest(); 
    } 
    
}


