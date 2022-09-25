/****************************************Copyright (c)****************************************************
**                            
**
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               os_cpu.h
** Latest modified Date:    2012-12-31
** Latest Version:          1.0
** Descriptions:            μCOS-II在ARM7上的移植代码CPU配置部分，用ADS1.2编译
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2012-12-31
** Version:                 1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#ifndef __OS_CPU_H
#define __OS_CPU_H
#ifdef  __cplusplus
extern "C" {
#endif
/*********************************************************************************************************
  定义与编译器无关的数据类型
*********************************************************************************************************/
typedef unsigned char  BOOLEAN;                                         /*  布尔变量                    */
typedef unsigned char  INT8U;                                           /*  无符号8位整型变量           */
typedef signed   char  INT8S;                                           /*  有符号8位整型变量           */
typedef unsigned short INT16U;                                          /*  无符号16位整型变量          */
typedef signed   short INT16S;                                          /*  有符号16位整型变量          */
typedef unsigned int   INT32U;                                          /*  无符号32位整型变量          */
typedef signed   int   INT32S;                                          /*  有符号32位整型变量          */
typedef float          FP32;                                            /*  单精度浮点数（32位长度）    */
typedef double         FP64;                                            /*  双精度浮点数（64位长度）    */

typedef INT32U         OS_STK;                                          /*  堆栈是32位宽度              */

/*********************************************************************************************************
  以下是兼容UC/OS V1.XX的数据类型，在uC/OS-II没有使用
*********************************************************************************************************/
#define BYTE           INT8S
#define UBYTE          INT8U
#define WORD           INT16S
#define UWORD          INT16U
#define LONG           INT32S
#define ULONG          INT32U


/*********************************************************************************************************
  与ARM7体系结构相关的一些定义
*********************************************************************************************************/
#define OS_CRITICAL_METHOD      2                                       /*  选择开、关中断的方式        */
#define OS_STK_GROWTH           1                                       /*  堆栈是从上往下长的          */

/*********************************************************************************************************
** Function name:           OsSwiHandle1
** Descriptions:            SWI函数声明
** input parameters:        iHandle: 用于区分功能
**                          其他:    根据功能决定
** output parameters:       根据功能决定
** Returned value:          根据功能决定
*********************************************************************************************************/
__swi(0x00) void OsSwiHandle1(int iHandle);
__swi(0x01) void *OsSwiHandle2(int iHandle, int iIndex);

/*********************************************************************************************************
** Function name:           OS_TASK_SW
** Descriptions:            任务级任务切换函数
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void OS_TASK_SW (void)
{
	OsSwiHandle1(0);
}

/*********************************************************************************************************
** Function name:           OSStartHighRdy
** Descriptions:            运行优先级最高的任务
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void OSStartHighRdy (void)
{
	OsSwiHandle1(1);
}

/*********************************************************************************************************
** Function name:           OS_ENTER_CRITICAL
** Descriptions:            关中断
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void OS_ENTER_CRITICAL (void)
{
	OsSwiHandle1(2);
}

__inline void IrqDisable(void)
{
    OsSwiHandle1(2);
}

/*********************************************************************************************************
** Function name:           OS_EXIT_CRITICAL
** Descriptions:            开中断 
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void OS_EXIT_CRITICAL (void)
{
	OsSwiHandle1(3);
}
__inline void IrqEnable(void)
{
    OsSwiHandle1(3);
}
/*********************************************************************************************************
** Function name:           ChangeToSYSMode
** Descriptions:            任务切换到系统模式 
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void ChangeToSYSMode (void)
{
	OsSwiHandle1(4);
}

/*********************************************************************************************************
** Function name:           ChangeToUSRMode
** Descriptions:            任务切换到用户模式 
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void ChangeToUSRMode (void)
{
	OsSwiHandle1(5);
}

/*********************************************************************************************************
** Function name:           OSISRBegin
** Descriptions:            中断开始处理
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void OSISRBegin (void)
{
	OsSwiHandle1(6);
}

/*********************************************************************************************************
** Function name:           OSISRNeedSwap
** Descriptions:            判断中断是否需要切换 
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void OSISRNeedSwap (void)
{
	OsSwiHandle1(7);
}

/*********************************************************************************************************
** Function name:           ENTER_FIQ
** Descriptions:            关快速 中断
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void ENTER_FIQ (void)
{
	OsSwiHandle1(8);
}

__inline void FiqDisable(void)
{
    OsSwiHandle1(8);
}

/*********************************************************************************************************
** Function name:           EXIT_FIQ
** Descriptions:            开中断 
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void EXIT_FIQ (void)
{
	OsSwiHandle1(9);
}
__inline void FiqEnable(void)
{
    OsSwiHandle1(9);
}

#ifdef __cplusplus
    }
#endif
#endif                                                                  /*  __OS_CPU_H                  */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
