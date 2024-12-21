#ifndef __B_QLOG_H
#define __B_QLOG_H

#include "SEGGER_RTT.h"


//*** <<< Use Configuration Wizard in Context Menu >>> ***

// <h> RTT 日志配置
// <i> 定义各种日志打印样式


/*********************************************************/
// <q> Log 函数使能
// <i> 样式: 背景黑色，字体白色
// <i> 应用: 常规日志打印
 
#ifndef USINGLOG
#define USINGLOG                1
#endif


// <q> HighLight 函数使能
// <i> 样式: 背景白色，字体蓝色
// <i> 应用: 日志高亮显示，特殊事件标记
 
#ifndef USINGHIGHLIGHT
#define USINGHIGHLIGHT          1
#endif


// <q> Success 函数使能
// <i> 样式: 背景绿色，字体红色
// <i> 应用: 事件执行成功日志打印
 
#ifndef USINGSUCCESS
#define USINGSUCCESS            1
#endif


// <q> Warning 函数使能
// <i> 样式: 背景黄色，字体蓝色
// <i> 应用: 事件执行警告日志打印
 
#ifndef USINGWARNING
#define USINGWARNING            1
#endif


// <q> Error 函数使能
// <i> 样式: 背景红色，字体白色
// <i> 应用: 事件执行失败日志打印
 
#ifndef USINGERROR
#define USINGERROR              1
#endif


// <q> LogHex 函数使能
// <i> 样式: 背景黑色，字体白色
// <i> 应用: 打印过程数据
 
#ifndef USINGSHOWHEX
#define USINGSHOWHEX            1
#endif


// </h> 
/*********************************************************/

//*** <<< end of configuration section >>>    ***



#if (USINGLOG || USINGHIGHLIGHT || USINGSUCCESS || USINGWARNING || USINGERROR || USINGSHOWHEX)
    #define LogInit                     SEGGER_RTT_Init
#else
    #define LogInit()                   {   } 
#endif


#if USINGLOG
    #define Log(...)                    SEGGER_RTT_printf(0, RTT_CTRL_RESET __VA_ARGS__)
#else
    #define Log(...)                    {   } 
#endif



#if USINGSUCCESS
    #define Success(...)                SEGGER_RTT_printf(0, RTT_CTRL_BG_BRIGHT_GREEN RTT_CTRL_TEXT_RED __VA_ARGS__)
#else
    #define Success(...)                {   }
#endif




#if USINGWARNING
    #define Warning(...)                SEGGER_RTT_printf(0, RTT_CTRL_BG_BRIGHT_YELLOW RTT_CTRL_TEXT_BLUE __VA_ARGS__)
#else
    #define Warning(...)                {   }
#endif



#if USINGERROR
    #define Error(...)                  SEGGER_RTT_printf(0, RTT_CTRL_BG_BRIGHT_RED RTT_CTRL_TEXT_BRIGHT_WHITE __VA_ARGS__)
#else
    #define Error(...)                  {   }
#endif



#if USINGHIGHLIGHT
    #define HighLight(...)              SEGGER_RTT_printf(0, RTT_CTRL_BG_BRIGHT_WHITE RTT_CTRL_TEXT_BLUE __VA_ARGS__)
#else
    #define HighLight(...)              {   }
#endif



#if USINGSHOWHEX
    #define LogHex(hex, len)                        \
    {                                               \
        for(uint32_t iii = 0; iii < len; iii++)     \
        {                                           \
            SEGGER_RTT_printf(0, "%02X ", hex[iii]);\
        }                                           \
    }
#else
    #define LogHex(...)                 {   }
#endif








#endif







