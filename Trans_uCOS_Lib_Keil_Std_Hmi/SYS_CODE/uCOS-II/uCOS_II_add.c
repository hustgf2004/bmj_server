/****************************************Copyright (c)****************************************************
**                 
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               uCOS_II_add.c
** Latest modified Date:    2013-09-26
** Latest Version:          1.0
** Descriptions:            OS辅助功能函数声明
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2013-09-26
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

#ifndef  OS_MASTER_FILE
#include "includes.h"
#endif

extern void (*pOSTaskCreateHook)(OS_TCB *);                             /*  创建任务钩子函数指针        */
extern void (*pOSTaskDelHook)(OS_TCB *);                                /*  删除任务钩子函数指针        */
extern void (*pOSTaskStatHook)(void);                                   /*  统计任务钩子函数指针        */
extern void (*pOSTimeTickHook)(void);                                   /*  系统时钟钩子函数指针        */
extern void (*pOSTaskIdleHook)(void);                                   /*  空闲任务钩子函数指针        */

/*********************************************************************************************************
** Function name:           OSPrioGet
** Descriptions:            返回当前任务的优先级
** input parameters:        none
** ouput parameters: 		none
** Returned value:          优先级
*********************************************************************************************************/
INT8U OSPrioGet(void)
{
    return OSPrioCur;
}
/*********************************************************************************************************
** Function name:           OSCPUUsageGet
** Descriptions:            返回当前CPU占有率
** input parameters:        none
** ouput parameters: 		none
** Returned value:          CPU占有率
*********************************************************************************************************/
INT8S OSCPUUsageGet(void)
{
    return OSCPUUsage;
}

/*********************************************************************************************************
** Function name:           OSIntNestingGet
** Descriptions:            返回中断嵌套层次
** input parameters:        none
** ouput parameters: 		none
** Returned value:          OSIntNesting
*********************************************************************************************************/
INT8U OSIntNestingGet(void)
{
    return OSIntNesting;    
}
/*********************************************************************************************************
** Function name:           OSTCBCurGet
** Descriptions:            返回当前任务的控制块
** input parameters:        none
** ouput parameters: 		none
** Returned value:          任务控制块
*********************************************************************************************************/
OS_TCB *OSTCBCurGet(void)
{
    return OSTCBCur;
}





/*********************************************************************************************************
** Function name:           OSTCBPrioTblGet
** Descriptions:            返回任务优先级列表
** input parameters:        none
** Returned value:          任务优先级列表
*********************************************************************************************************/
OS_TCB **OSTCBPrioTblGet(void)
{
    return OSTCBPrioTbl;
}

/*********************************************************************************************************
** Function name:           OSTaskCreateHookSet
** Descriptions:            设置任务创建钩子函数
** input parameters:        pfuncTaskIdleHook: 任务创建钩子函数
** ouput parameters: 		none
** Returned value:          none
*********************************************************************************************************/
void OSTaskCreateHookSet(void (* pfuncOSTaskCreateHook)(OS_TCB *ptcb))
{
    /*
     *  参数过滤
     */
    if (NULL == pfuncOSTaskCreateHook) {
        return;
    }
    pOSTaskCreateHook = pfuncOSTaskCreateHook;
}

/*********************************************************************************************************
** Function name:           OSTaskDelHookSet
** Descriptions:            设置任务删除钩子函数
** input parameters:        pfuncTaskIdleHook: 任务删除钩子函数
** ouput parameters: 		none
** Returned value:          none
*********************************************************************************************************/
void OSTaskDelHookSet(void (* pfuncOSTaskDelHook)(OS_TCB *ptcb))
{
    /*
     *  参数过滤
     */
    if (NULL == pfuncOSTaskDelHook) {
        return;
    }
    pOSTaskDelHook = pfuncOSTaskDelHook;
}

/*********************************************************************************************************
** Function name:           OSTaskStatHookSet
** Descriptions:            设置任务状态钩子函数
** input parameters:        pfuncTaskIdleHook: 任务状态钩子函数
** ouput parameters: 		none
** Returned value:          none
*********************************************************************************************************/
void OSTaskStatHookSet(void (* pfuncTaskStatHook)(void))
{
    /*
     *  参数过滤
     */
    if (NULL == pfuncTaskStatHook) {
        return;
    }
    pOSTaskStatHook = pfuncTaskStatHook;    
}

/*********************************************************************************************************
** Function name:           OSTimeTickHookSet
** Descriptions:            设置时钟节拍钩子函数
** input parameters:        pfuncTimeTickHook: 时钟节拍钩子函数
** Returned value:          none
*********************************************************************************************************/
void OSTimeTickHookSet(void (* pfuncTimeTickHook)(void))
{
    /*
     *  参数过滤
     */
    if (NULL == pfuncTimeTickHook) {
        return;
    }
    pOSTimeTickHook = pfuncTimeTickHook;    
}

/*********************************************************************************************************
** Function name:           OSTaskIdleHookSet
** Descriptions:            设置空闲任务钩子函数
** input parameters:        pfuncTaskIdleHook: 空闲任务钩子函数
** ouput parameters: 		none
** Returned value:          none
*********************************************************************************************************/
void OSTaskIdleHookSet(void (* pfuncTaskIdleHook)(void))
{
    /*
     *  参数过滤
     */
    if (NULL == pfuncTaskIdleHook) {
        return;
    }
    pOSTaskIdleHook = pfuncTaskIdleHook;  
}

/*********************************************************************************************************
** Function name:           OSTimeLag
** Descriptions:            等待时间间隔
** input parameters:        usTicks: 与上次调用本函数之间间隔的时钟节拍数目
** ouput parameters: 		none
** Returned value:          none
*********************************************************************************************************/
void  OSTimeLag(INT16U usTicks)
{
    /*
     *  参数过滤
     */
    if (0 == usTicks) {
        return;
    }

    OS_ENTER_CRITICAL();                                                /*  关中断                      */

    if ((OSTime - OSTCBCur->OSTCBTimeLag) >= usTicks) {
        OSTCBCur->OSTCBTimeLag = OSTime; 
    } else {
        OSTCBCur->OSTCBTimeLag += usTicks;
        if ((OSRdyTbl[OSTCBCur->OSTCBY] &= ~OSTCBCur->OSTCBBitX) == 0) {   
            OSRdyGrp &= ~OSTCBCur->OSTCBBitY;         
        }
        OSTCBCur->OSTCBDly = OSTCBCur->OSTCBTimeLag - OSTime;
        OS_EXIT_CRITICAL();                                             /*  开中断                      */
        OS_Sched();
        return;
    } 
    OS_EXIT_CRITICAL();                                                 /*  开中断                      */
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
