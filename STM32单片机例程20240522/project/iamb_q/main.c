#include "main.h"

#include "iwdg.h"
#include "magicrf.h"


// �Ż��ȼ� -o1 �����ʱ�����붨��Ϊ volatile 
volatile System_Type system_t = {0}; 





/**
  * @author    b_q 
  * @date      2018/5/10
  * @brief     ϵͳ�δ�ʱ��
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
  * @brief     ϵͳ�δ�ʱ��
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
        // ��ʱι��
        if((system_t.tick & 0x3F) == 0)
            FeedDog(); 
    }
}





/**
  * @author    b_q
  * @date      2020/2/21
  * @brief     ���������
  * @param     
  * @retval    
  * @attention 
  */
int main(void) 
{ 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    SystickInit(1000);                                      // ����ϵͳʱ��
    LogInit();                                              // ��ʼ�� RTT ��־��ͨ��jlink���߿ɲ鿴��������
    
    IwdgInit(IWDG_Prescaler_128, 0x64);                     // �������Ź�
    
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


