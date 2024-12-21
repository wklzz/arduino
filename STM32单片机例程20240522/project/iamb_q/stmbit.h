#ifndef __STMBIT_H
#define __STMBIT_H


#include "stm32f10x.h"


    
// 把“位段地址＋位序号”转换别名地址宏
#define BITBAND(addr, bitnum)       ((addr & 0xF0000000) + 0x02000000 + ((addr & 0x000FFFFF) << 5) + (bitnum << 2))
#define MEM_ADDR(addr)              *((volatile unsigned long *)(addr))     // 把该地址转换成一个指针
#define BIT_ADDR(addr, bitnum)      MEM_ADDR(BITBAND(addr, bitnum))




#define GPIOA_ODR_Addr      (GPIOA_BASE + 0x0C)                     // 0x4001 080C
#define GPIOB_ODR_Addr      (GPIOB_BASE + 0x0C)                     // 0x4001 0C0C
#define GPIOC_ODR_Addr      (GPIOC_BASE + 0x0C)                     // 0x4001 100C
#define GPIOD_ODR_Addr      (GPIOD_BASE + 0x0C)                     // 0x4001 140C
#define GPIOE_ODR_Addr      (GPIOE_BASE + 0x0C)                     // 0x4001 180C
#define GPIOF_ODR_Addr      (GPIOF_BASE + 0x0C)                     // 0x4001 1C0C
#define GPIOG_ODR_Addr      (GPIOG_BASE + 0x0C)                     // 0x4001 200C

#define GPIOA_IDR_Addr      (GPIOA_BASE + 0x08)                     // 0x4001 0808
#define GPIOB_IDR_Addr      (GPIOB_BASE + 0x08)                     // 0x4001 0C08
#define GPIOC_IDR_Addr      (GPIOC_BASE + 0x08)                     // 0x4001 1008
#define GPIOD_IDR_Addr      (GPIOD_BASE + 0x08)                     // 0x4001 1408
#define GPIOE_IDR_Addr      (GPIOE_BASE + 0x08)                     // 0x4001 1808
#define GPIOF_IDR_Addr      (GPIOF_BASE + 0x08)                     // 0x4001 1C08
#define GPIOG_IDR_Addr      (GPIOG_BASE + 0x08)                     // 0x4001 2008


#define PA0                 BIT_ADDR(GPIOA_ODR_Addr, 0)             // 输出
#define PA1                 BIT_ADDR(GPIOA_ODR_Addr, 1)             // 输出
#define PA2                 BIT_ADDR(GPIOA_ODR_Addr, 2)             // 输出
#define PA3                 BIT_ADDR(GPIOA_ODR_Addr, 3)             // 输出
#define PA4                 BIT_ADDR(GPIOA_ODR_Addr, 4)             // 输出
#define PA5                 BIT_ADDR(GPIOA_ODR_Addr, 5)             // 输出
#define PA6                 BIT_ADDR(GPIOA_ODR_Addr, 6)             // 输出
#define PA7                 BIT_ADDR(GPIOA_ODR_Addr, 7)             // 输出
#define PA8                 BIT_ADDR(GPIOA_ODR_Addr, 8)             // 输出
#define PA9                 BIT_ADDR(GPIOA_ODR_Addr, 9)             // 输出
#define PA10                BIT_ADDR(GPIOA_ODR_Addr, 10)            // 输出
#define PA11                BIT_ADDR(GPIOA_ODR_Addr, 11)            // 输出
#define PA12                BIT_ADDR(GPIOA_ODR_Addr, 12)            // 输出
#define PA13                BIT_ADDR(GPIOA_ODR_Addr, 13)            // 输出
#define PA14                BIT_ADDR(GPIOA_ODR_Addr, 14)            // 输出
#define PA15                BIT_ADDR(GPIOA_ODR_Addr, 15)            // 输出

#define PA0In               BIT_ADDR(GPIOA_IDR_Addr, 0)             // 输入
#define PA1In               BIT_ADDR(GPIOA_IDR_Addr, 1)             // 输入
#define PA2In               BIT_ADDR(GPIOA_IDR_Addr, 2)             // 输入
#define PA3In               BIT_ADDR(GPIOA_IDR_Addr, 3)             // 输入
#define PA4In               BIT_ADDR(GPIOA_IDR_Addr, 4)             // 输入
#define PA5In               BIT_ADDR(GPIOA_IDR_Addr, 5)             // 输入
#define PA6In               BIT_ADDR(GPIOA_IDR_Addr, 6)             // 输入
#define PA7In               BIT_ADDR(GPIOA_IDR_Addr, 7)             // 输入
#define PA8In               BIT_ADDR(GPIOA_IDR_Addr, 8)             // 输入
#define PA9In               BIT_ADDR(GPIOA_IDR_Addr, 9)             // 输入
#define PA10In              BIT_ADDR(GPIOA_IDR_Addr, 10)            // 输入
#define PA11In              BIT_ADDR(GPIOA_IDR_Addr, 11)            // 输入
#define PA12In              BIT_ADDR(GPIOA_IDR_Addr, 12)            // 输入
#define PA13In              BIT_ADDR(GPIOA_IDR_Addr, 13)            // 输入
#define PA14In              BIT_ADDR(GPIOA_IDR_Addr, 14)            // 输入
#define PA15In              BIT_ADDR(GPIOA_IDR_Addr, 15)            // 输入



#define PB0                 BIT_ADDR(GPIOB_ODR_Addr, 0)             // 输出
#define PB1                 BIT_ADDR(GPIOB_ODR_Addr, 1)             // 输出
#define PB2                 BIT_ADDR(GPIOB_ODR_Addr, 2)             // 输出
#define PB3                 BIT_ADDR(GPIOB_ODR_Addr, 3)             // 输出
#define PB4                 BIT_ADDR(GPIOB_ODR_Addr, 4)             // 输出
#define PB5                 BIT_ADDR(GPIOB_ODR_Addr, 5)             // 输出
#define PB6                 BIT_ADDR(GPIOB_ODR_Addr, 6)             // 输出
#define PB7                 BIT_ADDR(GPIOB_ODR_Addr, 7)             // 输出
#define PB8                 BIT_ADDR(GPIOB_ODR_Addr, 8)             // 输出
#define PB9                 BIT_ADDR(GPIOB_ODR_Addr, 9)             // 输出
#define PB10                BIT_ADDR(GPIOB_ODR_Addr, 10)            // 输出
#define PB11                BIT_ADDR(GPIOB_ODR_Addr, 11)            // 输出
#define PB12                BIT_ADDR(GPIOB_ODR_Addr, 12)            // 输出
#define PB13                BIT_ADDR(GPIOB_ODR_Addr, 13)            // 输出
#define PB14                BIT_ADDR(GPIOB_ODR_Addr, 14)            // 输出
#define PB15                BIT_ADDR(GPIOB_ODR_Addr, 15)            // 输出

#define PB0In               BIT_ADDR(GPIOB_IDR_Addr, 0)             // 输入
#define PB1In               BIT_ADDR(GPIOB_IDR_Addr, 1)             // 输入
#define PB2In               BIT_ADDR(GPIOB_IDR_Addr, 2)             // 输入
#define PB3In               BIT_ADDR(GPIOB_IDR_Addr, 3)             // 输入
#define PB4In               BIT_ADDR(GPIOB_IDR_Addr, 4)             // 输入
#define PB5In               BIT_ADDR(GPIOB_IDR_Addr, 5)             // 输入
#define PB6In               BIT_ADDR(GPIOB_IDR_Addr, 6)             // 输入
#define PB7In               BIT_ADDR(GPIOB_IDR_Addr, 7)             // 输入
#define PB8In               BIT_ADDR(GPIOB_IDR_Addr, 8)             // 输入
#define PB9In               BIT_ADDR(GPIOB_IDR_Addr, 9)             // 输入
#define PB10In              BIT_ADDR(GPIOB_IDR_Addr, 10)            // 输入
#define PB11In              BIT_ADDR(GPIOB_IDR_Addr, 11)            // 输入
#define PB12In              BIT_ADDR(GPIOB_IDR_Addr, 12)            // 输入
#define PB13In              BIT_ADDR(GPIOB_IDR_Addr, 13)            // 输入
#define PB14In              BIT_ADDR(GPIOB_IDR_Addr, 14)            // 输入
#define PB15In              BIT_ADDR(GPIOB_IDR_Addr, 15)            // 输入



#define PC0                 BIT_ADDR(GPIOC_ODR_Addr, 0)             // 输出
#define PC1                 BIT_ADDR(GPIOC_ODR_Addr, 1)             // 输出
#define PC2                 BIT_ADDR(GPIOC_ODR_Addr, 2)             // 输出
#define PC3                 BIT_ADDR(GPIOC_ODR_Addr, 3)             // 输出
#define PC4                 BIT_ADDR(GPIOC_ODR_Addr, 4)             // 输出
#define PC5                 BIT_ADDR(GPIOC_ODR_Addr, 5)             // 输出
#define PC6                 BIT_ADDR(GPIOC_ODR_Addr, 6)             // 输出
#define PC7                 BIT_ADDR(GPIOC_ODR_Addr, 7)             // 输出
#define PC8                 BIT_ADDR(GPIOC_ODR_Addr, 8)             // 输出
#define PC9                 BIT_ADDR(GPIOC_ODR_Addr, 9)             // 输出
#define PC10                BIT_ADDR(GPIOC_ODR_Addr, 10)            // 输出
#define PC11                BIT_ADDR(GPIOC_ODR_Addr, 11)            // 输出
#define PC12                BIT_ADDR(GPIOC_ODR_Addr, 12)            // 输出
#define PC13                BIT_ADDR(GPIOC_ODR_Addr, 13)            // 输出
#define PC14                BIT_ADDR(GPIOC_ODR_Addr, 14)            // 输出
#define PC15                BIT_ADDR(GPIOC_ODR_Addr, 15)            // 输出

#define PC0In               BIT_ADDR(GPIOC_IDR_Addr, 0)             // 输入
#define PC1In               BIT_ADDR(GPIOC_IDR_Addr, 1)             // 输入
#define PC2In               BIT_ADDR(GPIOC_IDR_Addr, 2)             // 输入
#define PC3In               BIT_ADDR(GPIOC_IDR_Addr, 3)             // 输入
#define PC4In               BIT_ADDR(GPIOC_IDR_Addr, 4)             // 输入
#define PC5In               BIT_ADDR(GPIOC_IDR_Addr, 5)             // 输入
#define PC6In               BIT_ADDR(GPIOC_IDR_Addr, 6)             // 输入
#define PC7In               BIT_ADDR(GPIOC_IDR_Addr, 7)             // 输入
#define PC8In               BIT_ADDR(GPIOC_IDR_Addr, 8)             // 输入
#define PC9In               BIT_ADDR(GPIOC_IDR_Addr, 9)             // 输入
#define PC10In              BIT_ADDR(GPIOC_IDR_Addr, 10)            // 输入
#define PC11In              BIT_ADDR(GPIOC_IDR_Addr, 11)            // 输入
#define PC12In              BIT_ADDR(GPIOC_IDR_Addr, 12)            // 输入
#define PC13In              BIT_ADDR(GPIOC_IDR_Addr, 13)            // 输入
#define PC14In              BIT_ADDR(GPIOC_IDR_Addr, 14)            // 输入
#define PC15In              BIT_ADDR(GPIOC_IDR_Addr, 15)            // 输入



#define PD0                 BIT_ADDR(GPIOD_ODR_Addr, 0)             // 输出
#define PD1                 BIT_ADDR(GPIOD_ODR_Addr, 1)             // 输出
#define PD2                 BIT_ADDR(GPIOD_ODR_Addr, 2)             // 输出
#define PD3                 BIT_ADDR(GPIOD_ODR_Addr, 3)             // 输出
#define PD4                 BIT_ADDR(GPIOD_ODR_Addr, 4)             // 输出
#define PD5                 BIT_ADDR(GPIOD_ODR_Addr, 5)             // 输出
#define PD6                 BIT_ADDR(GPIOD_ODR_Addr, 6)             // 输出
#define PD7                 BIT_ADDR(GPIOD_ODR_Addr, 7)             // 输出
#define PD8                 BIT_ADDR(GPIOD_ODR_Addr, 8)             // 输出
#define PD9                 BIT_ADDR(GPIOD_ODR_Addr, 9)             // 输出
#define PD10                BIT_ADDR(GPIOD_ODR_Addr, 10)            // 输出
#define PD11                BIT_ADDR(GPIOD_ODR_Addr, 11)            // 输出
#define PD12                BIT_ADDR(GPIOD_ODR_Addr, 12)            // 输出
#define PD13                BIT_ADDR(GPIOD_ODR_Addr, 13)            // 输出
#define PD14                BIT_ADDR(GPIOD_ODR_Addr, 14)            // 输出
#define PD15                BIT_ADDR(GPIOD_ODR_Addr, 15)            // 输出

#define PD0In               BIT_ADDR(GPIOD_IDR_Addr, 0)             // 输入
#define PD1In               BIT_ADDR(GPIOD_IDR_Addr, 1)             // 输入
#define PD2In               BIT_ADDR(GPIOD_IDR_Addr, 2)             // 输入
#define PD3In               BIT_ADDR(GPIOD_IDR_Addr, 3)             // 输入
#define PD4In               BIT_ADDR(GPIOD_IDR_Addr, 4)             // 输入
#define PD5In               BIT_ADDR(GPIOD_IDR_Addr, 5)             // 输入
#define PD6In               BIT_ADDR(GPIOD_IDR_Addr, 6)             // 输入
#define PD7In               BIT_ADDR(GPIOD_IDR_Addr, 7)             // 输入
#define PD8In               BIT_ADDR(GPIOD_IDR_Addr, 8)             // 输入
#define PD9In               BIT_ADDR(GPIOD_IDR_Addr, 9)             // 输入
#define PD10In              BIT_ADDR(GPIOD_IDR_Addr, 10)            // 输入
#define PD11In              BIT_ADDR(GPIOD_IDR_Addr, 11)            // 输入
#define PD12In              BIT_ADDR(GPIOD_IDR_Addr, 12)            // 输入
#define PD13In              BIT_ADDR(GPIOD_IDR_Addr, 13)            // 输入
#define PD14In              BIT_ADDR(GPIOD_IDR_Addr, 14)            // 输入
#define PD15In              BIT_ADDR(GPIOD_IDR_Addr, 15)            // 输入



#define PE0                 BIT_ADDR(GPIOE_ODR_Addr, 0)             // 输出
#define PE1                 BIT_ADDR(GPIOE_ODR_Addr, 1)             // 输出
#define PE2                 BIT_ADDR(GPIOE_ODR_Addr, 2)             // 输出
#define PE3                 BIT_ADDR(GPIOE_ODR_Addr, 3)             // 输出
#define PE4                 BIT_ADDR(GPIOE_ODR_Addr, 4)             // 输出
#define PE5                 BIT_ADDR(GPIOE_ODR_Addr, 5)             // 输出
#define PE6                 BIT_ADDR(GPIOE_ODR_Addr, 6)             // 输出
#define PE7                 BIT_ADDR(GPIOE_ODR_Addr, 7)             // 输出
#define PE8                 BIT_ADDR(GPIOE_ODR_Addr, 8)             // 输出
#define PE9                 BIT_ADDR(GPIOE_ODR_Addr, 9)             // 输出
#define PE10                BIT_ADDR(GPIOE_ODR_Addr, 10)            // 输出
#define PE11                BIT_ADDR(GPIOE_ODR_Addr, 11)            // 输出
#define PE12                BIT_ADDR(GPIOE_ODR_Addr, 12)            // 输出
#define PE13                BIT_ADDR(GPIOE_ODR_Addr, 13)            // 输出
#define PE14                BIT_ADDR(GPIOE_ODR_Addr, 14)            // 输出
#define PE15                BIT_ADDR(GPIOE_ODR_Addr, 15)            // 输出

#define PE0In               BIT_ADDR(GPIOE_IDR_Addr, 0)             // 输入
#define PE1In               BIT_ADDR(GPIOE_IDR_Addr, 1)             // 输入
#define PE2In               BIT_ADDR(GPIOE_IDR_Addr, 2)             // 输入
#define PE3In               BIT_ADDR(GPIOE_IDR_Addr, 3)             // 输入
#define PE4In               BIT_ADDR(GPIOE_IDR_Addr, 4)             // 输入
#define PE5In               BIT_ADDR(GPIOE_IDR_Addr, 5)             // 输入
#define PE6In               BIT_ADDR(GPIOE_IDR_Addr, 6)             // 输入
#define PE7In               BIT_ADDR(GPIOE_IDR_Addr, 7)             // 输入
#define PE8In               BIT_ADDR(GPIOE_IDR_Addr, 8)             // 输入
#define PE9In               BIT_ADDR(GPIOE_IDR_Addr, 9)             // 输入
#define PE10In              BIT_ADDR(GPIOE_IDR_Addr, 10)            // 输入
#define PE11In              BIT_ADDR(GPIOE_IDR_Addr, 11)            // 输入
#define PE12In              BIT_ADDR(GPIOE_IDR_Addr, 12)            // 输入
#define PE13In              BIT_ADDR(GPIOE_IDR_Addr, 13)            // 输入
#define PE14In              BIT_ADDR(GPIOE_IDR_Addr, 14)            // 输入
#define PE15In              BIT_ADDR(GPIOE_IDR_Addr, 15)            // 输入



#define PF0                 BIT_ADDR(GPIOF_ODR_Addr, 0)             // 输出
#define PF1                 BIT_ADDR(GPIOF_ODR_Addr, 1)             // 输出
#define PF2                 BIT_ADDR(GPIOF_ODR_Addr, 2)             // 输出
#define PF3                 BIT_ADDR(GPIOF_ODR_Addr, 3)             // 输出
#define PF4                 BIT_ADDR(GPIOF_ODR_Addr, 4)             // 输出
#define PF5                 BIT_ADDR(GPIOF_ODR_Addr, 5)             // 输出
#define PF6                 BIT_ADDR(GPIOF_ODR_Addr, 6)             // 输出
#define PF7                 BIT_ADDR(GPIOF_ODR_Addr, 7)             // 输出
#define PF8                 BIT_ADDR(GPIOF_ODR_Addr, 8)             // 输出
#define PF9                 BIT_ADDR(GPIOF_ODR_Addr, 9)             // 输出
#define PF10                BIT_ADDR(GPIOF_ODR_Addr, 10)            // 输出
#define PF11                BIT_ADDR(GPIOF_ODR_Addr, 11)            // 输出
#define PF12                BIT_ADDR(GPIOF_ODR_Addr, 12)            // 输出
#define PF13                BIT_ADDR(GPIOF_ODR_Addr, 13)            // 输出
#define PF14                BIT_ADDR(GPIOF_ODR_Addr, 14)            // 输出
#define PF15                BIT_ADDR(GPIOF_ODR_Addr, 15)            // 输出

#define PF0In               BIT_ADDR(GPIOF_IDR_Addr, 0)             // 输入
#define PF1In               BIT_ADDR(GPIOF_IDR_Addr, 1)             // 输入
#define PF2In               BIT_ADDR(GPIOF_IDR_Addr, 2)             // 输入
#define PF3In               BIT_ADDR(GPIOF_IDR_Addr, 3)             // 输入
#define PF4In               BIT_ADDR(GPIOF_IDR_Addr, 4)             // 输入
#define PF5In               BIT_ADDR(GPIOF_IDR_Addr, 5)             // 输入
#define PF6In               BIT_ADDR(GPIOF_IDR_Addr, 6)             // 输入
#define PF7In               BIT_ADDR(GPIOF_IDR_Addr, 7)             // 输入
#define PF8In               BIT_ADDR(GPIOF_IDR_Addr, 8)             // 输入
#define PF9In               BIT_ADDR(GPIOF_IDR_Addr, 9)             // 输入
#define PF10In              BIT_ADDR(GPIOF_IDR_Addr, 10)            // 输入
#define PF11In              BIT_ADDR(GPIOF_IDR_Addr, 11)            // 输入
#define PF12In              BIT_ADDR(GPIOF_IDR_Addr, 12)            // 输入
#define PF13In              BIT_ADDR(GPIOF_IDR_Addr, 13)            // 输入
#define PF14In              BIT_ADDR(GPIOF_IDR_Addr, 14)            // 输入
#define PF15In              BIT_ADDR(GPIOF_IDR_Addr, 15)            // 输入



#define PG0                 BIT_ADDR(GPIOG_ODR_Addr, 0)             // 输出
#define PG1                 BIT_ADDR(GPIOG_ODR_Addr, 1)             // 输出
#define PG2                 BIT_ADDR(GPIOG_ODR_Addr, 2)             // 输出
#define PG3                 BIT_ADDR(GPIOG_ODR_Addr, 3)             // 输出
#define PG4                 BIT_ADDR(GPIOG_ODR_Addr, 4)             // 输出
#define PG5                 BIT_ADDR(GPIOG_ODR_Addr, 5)             // 输出
#define PG6                 BIT_ADDR(GPIOG_ODR_Addr, 6)             // 输出
#define PG7                 BIT_ADDR(GPIOG_ODR_Addr, 7)             // 输出
#define PG8                 BIT_ADDR(GPIOG_ODR_Addr, 8)             // 输出
#define PG9                 BIT_ADDR(GPIOG_ODR_Addr, 9)             // 输出
#define PG10                BIT_ADDR(GPIOG_ODR_Addr, 10)            // 输出
#define PG11                BIT_ADDR(GPIOG_ODR_Addr, 11)            // 输出
#define PG12                BIT_ADDR(GPIOG_ODR_Addr, 12)            // 输出
#define PG13                BIT_ADDR(GPIOG_ODR_Addr, 13)            // 输出
#define PG14                BIT_ADDR(GPIOG_ODR_Addr, 14)            // 输出
#define PG15                BIT_ADDR(GPIOG_ODR_Addr, 15)            // 输出

#define PG0In               BIT_ADDR(GPIOG_IDR_Addr, 0)             // 输入
#define PG1In               BIT_ADDR(GPIOG_IDR_Addr, 1)             // 输入
#define PG2In               BIT_ADDR(GPIOG_IDR_Addr, 2)             // 输入
#define PG3In               BIT_ADDR(GPIOG_IDR_Addr, 3)             // 输入
#define PG4In               BIT_ADDR(GPIOG_IDR_Addr, 4)             // 输入
#define PG5In               BIT_ADDR(GPIOG_IDR_Addr, 5)             // 输入
#define PG6In               BIT_ADDR(GPIOG_IDR_Addr, 6)             // 输入
#define PG7In               BIT_ADDR(GPIOG_IDR_Addr, 7)             // 输入
#define PG8In               BIT_ADDR(GPIOG_IDR_Addr, 8)             // 输入
#define PG9In               BIT_ADDR(GPIOG_IDR_Addr, 9)             // 输入
#define PG10In              BIT_ADDR(GPIOG_IDR_Addr, 10)            // 输入
#define PG11In              BIT_ADDR(GPIOG_IDR_Addr, 11)            // 输入
#define PG12In              BIT_ADDR(GPIOG_IDR_Addr, 12)            // 输入
#define PG13In              BIT_ADDR(GPIOG_IDR_Addr, 13)            // 输入
#define PG14In              BIT_ADDR(GPIOG_IDR_Addr, 14)            // 输入
#define PG15In              BIT_ADDR(GPIOG_IDR_Addr, 15)            // 输入


#endif

