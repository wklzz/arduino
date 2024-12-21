#include "magicrf.h"
#include "usart.h"
#include "queue.h"
#include "stmbit.h"



#define READER_EN                   PA7

#define Send2MagicRF(str, len)     {UsartSendString(USART1, str, len); }




static uint8_t magicrfbuff[256] = {0};          // 读头返回数据缓存


MagicRF_Type * const magicrf_t = (MagicRF_Type *)magicrfbuff; 



// 计算校验和
uint8_t CalSum(const uint8_t *pbuf, uint32_t len) 
{ 
    uint8_t sum = 0; 
    
    for (uint32_t i = 0; i < len; i++) 
    { 
        sum += *pbuf++; 
    }
    
    return sum; 
}



/**
  * @author    b_q 
  * @date      2018/5/10
  * @brief     获取读头回复
  * @param     
  * @retval    
  * @attention -1 未收到回复  -2 回复超时  0 收到回复
  */
int GetRespone(void) 
{ 
    static uint8_t loc = 0; 
    static uint32_t ltick = 0;              // 回复超时判断
    
    
    uint8_t tmp = 0; 
    while(QueueOut(&rsp_queue_t, &tmp) == 0) 
    { 
        magicrfbuff[loc++] = tmp; 
        ltick = system_t.tick; 
        
        
        // 帧头符合
        if((loc == 1) && (tmp != 0xBB)) 
        { 
            loc = 0; 
        }
        
        // 长度符合
        if((loc > 6) && (loc > (magicrf_t->length[1] + 6))) 
        { 
            // 结尾符合
            if(tmp == 0x7E) 
            { 
                // 可进一步比较校验和
                Log("\r\n <- "); 
                LogHex(magicrfbuff, loc); 
                loc = 0; 
                
                return 0; 
            }
            
            loc = 0; 
        }
        
    }
    
    // 指令回复超时判断
    if((loc > 0) && (system_t.tick - ltick > 10)) 
    { 
        loc = 0; 
        Error("\r\n !!! Return Timeout "); 
        return -2; 
    }
    
    
    return -1; 
}


/**
  * @author    b_q
  * @date      2016/11/5
  * @brief     等待读头回复，超时跳过
  * @param
  * @retval    
  * @attention -1 超时
  */
int WaitRespone(uint32_t xms)
{ 
    while(xms--)
    {
        delay_ms(1);
        if(GetRespone() == 0)  
            return 0;
    }
    
    return -1;
}



/**
  * @author    b_q 
  * @date      2018/5/10
  * @brief     读头初始化
  * @param     
  * @retval    
  * @attention 
  */
int MagicRFInit(void) 
{ 
    Log("\r\n %s ... ", __FUNCTION__); 
    
    // 读头使能 PA11
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_7; 
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    READER_EN = 0; 
    
    // 初始化外设
    Usart1Init(115200);                         // 读头连接到 usart1, 使能了接收中断，读头回复的数据在中断里入队列
    
    delay_ms(100); 
    READER_EN = 1;                              // 使能读头
    
    delay_ms(1500);                             // 等待 1500ms，读头启动需要 1000+ ms
    
    
    const uint8_t gethardv[] = {0xBB, 0x00, 0x03, 0x00, 0x01, 0x00, 0x04, 0x7E}; 
    
    WaitRespone(10); 
    WaitRespone(10); 
    WaitRespone(10); 
    
    
    
    int retry = 0; 
    
    // 确保识别成功
    do 
    { 
        
        Send2MagicRF((uint8_t *)gethardv, sizeof(gethardv)); 
        
        if(WaitRespone(100) == 0) 
        { 
            if((magicrf_t->type == 0x01) && (magicrf_t->command == 0x03) 
                && (magicrf_t->data[0] == 0x00)) 
            { 
                char ibuf[32] = {0}; 
                for(int i = 1; i < magicrf_t->length[1]; i++) 
                { 
                    ibuf[i - 1] = magicrf_t->data[i]; 
                }
                Log("%s", ibuf); 
                
                return 0; 
            }
        }
        
    } while (retry++ < 5); 
    
    
    
    return -1; 
}




/**
  * @author    b_q
  * @date      2018/7/2
  * @brief     设置功率
  * @param
  * @retval    -1 失败
  * @attention
  */
int SetPower(uint32_t power)
{ 
    Log("\r\n %s ... ", __FUNCTION__); 
    
    // BB 00 B6 00 02 07 D0 8F 7E
    uint8_t rcmd[16] = {0};
    
    rcmd[0] = 0xBB; 
    rcmd[1] = 0x00; 
    rcmd[2] = 0xB6; 
    rcmd[3] = 0x00; 
    rcmd[4] = 0x02; 
    rcmd[5] = power >> 8; 
    rcmd[6] = power; 
    rcmd[7] = rcmd[1] + rcmd[2] + rcmd[3] + rcmd[4] + rcmd[5] + rcmd[6];
    rcmd[8] = 0x7E;
    
    int retry = 0; 
    do 
    {
        Send2MagicRF(rcmd, 9); 
        
        if(WaitRespone(100) == 0) 
        { 
            if((magicrf_t->command == 0xB6) && (magicrf_t->type == 0x01) && (magicrf_t->data[0] == 0x00))
            {
                Success("OK");
                return 0; 
            }
        }
        
        WaitRespone(10); 
        WaitRespone(10); 
    } 
    while(retry++ < 5); 
    
    Error("Err");
    
    return -1; 
}





/**
  * @author    b_q
  * @date      2018/7/11
  * @brief     停止连续寻卡
  * @param
  * @retval    
  * @attention
  */
void StartReading(void)
{ 
    const uint8_t read[] = {0xBB, 0x00, 0x27, 0x00, 0x03, 0x22, 0x00, 0x00, 0x4C, 0x7E}; 
    
    Log("\r\n %s ... ", __FUNCTION__); 
    
    uint8_t retry = 0; 
    
    do 
    { 
        Send2MagicRF((uint8_t *)read, sizeof(read)); 
        
        // 任意回复退出
        if(WaitRespone(100) == 0) 
        { 
            break; 
        }
        
        WaitRespone(10); 
        WaitRespone(10); 
    } 
    while(retry++ < 5); 
}



/**
  * @author    b_q
  * @date      2018/7/11
  * @brief     停止连续寻卡
  * @param
  * @retval    
  * @attention
  */
void StopReading(void)
{ 
    const uint8_t stop[] = {0xBB, 0x00, 0x28, 0x00, 0x00, 0x28, 0x7E}; 
    
    Log("\r\n %s ... ", __FUNCTION__); 
    
    uint8_t retry = 0; 
    
    do 
    { 
        Send2MagicRF((uint8_t *)stop, sizeof(stop)); 
        
        if(WaitRespone(100) == 0) 
        { 
            if((magicrf_t->command == 0x28) && (magicrf_t->type == 0x01) && (magicrf_t->data[0] == 0x00))
            { 
                Success("OK"); 
                break; 
            }
        }
        
        WaitRespone(10); 
        WaitRespone(10); 
        WaitRespone(10); 
        WaitRespone(10); 
        WaitRespone(10); 
    } 
    while(retry++ < 5); 
}




#include "iwdg.h"

// 自动测试
int MagicRFTest(void) 
{ 
    
    
    uint32_t readt = 0; 
    uint32_t stopt = 0; 
    uint32_t feedt = 0; 
    int working = 0; 
    
    SetPower(2000); 
    while(1) 
    { 
        if(working == 0) 
        { 
            // 停 1 s
            if(system_t.tick - stopt > 1000) 
            { 
                StartReading(); 
                working = 1; 
                readt = system_t.tick; 
            }
        } 
        else 
        { 
            // 读 5s 
            if(system_t.tick - readt > 5000) 
            { 
                StopReading(); 
                working = 0; 
                stopt = system_t.tick; 
            }
        }
        
        
        // 收到回复立马解析
        if(GetRespone() == 0) 
        { 
            // BB 02 22 00 12 CD 34 00 E2 00 47 15 51 A0 64 26 5C B7 01 0B B3 7D 01 40 7E
            // 提取标签数据
            
            if((magicrf_t->command == 0x22) && (magicrf_t->type == 0x02)) 
            { 
                
                Tag_Type tag_t = {0}; 
                uint8_t loc = 0; 
                
                tag_t.rssi = magicrf_t->data[loc++]; 
                
                tag_t.pc[0] = magicrf_t->data[loc++]; 
                tag_t.pc[1] = magicrf_t->data[loc++]; 
                
                uint8_t epclen = (tag_t.pc[0] >> 3) << 1; 
                
                for(uint8_t i = 0; i < epclen; i++) 
                { 
                    tag_t.epc[i] = magicrf_t->data[loc++]; 
                }
                
                loc++; 
                loc++; 
                
                tag_t.ant = magicrf_t->data[loc++]; 
                
                
                Log("\r\n     Rssi: %d", tag_t.rssi); 
                Log("\r\n      Ant: %d", tag_t.ant); 
                Log("\r\n PC + EPC: %02X %02X   ", tag_t.pc[0], tag_t.pc[1]); 
                LogHex(tag_t.epc, epclen); 
                
            }
            
        }
        
        if(system_t.tick - feedt > 100) 
        { 
            feedt = system_t.tick; 
            FeedDog(); 
        }
    }
    
    
    
    return 0; 
} 





