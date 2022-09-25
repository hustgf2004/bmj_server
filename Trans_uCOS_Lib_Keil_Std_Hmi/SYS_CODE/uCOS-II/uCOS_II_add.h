/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               uCOS_II_add.h
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
#ifndef __uCOS_II_ADD_H 
#define __uCOS_II_ADD_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** Function name:           OSPrioGet
** Descriptions:            返回当前任务的优先级
** input parameters:        none
** ouput parameters: 		none
** Returned value:          优先级
*********************************************************************************************************/
extern INT8U OSPrioGet(void);

/*********************************************************************************************************
** Function name:           OSTCBCurGet
** Descriptions:            返回当前任务的控制块
** input parameters:        none
** ouput parameters: 		none
** Returned value:          任务控制块
*********************************************************************************************************/
extern OS_TCB *OSTCBCurGet(void);

/*********************************************************************************************************
** Function name:           OSCPUUsageGet
** Descriptions:            返回当前CPU占有率
** input parameters:        none
** ouput parameters: 		none
** Returned value:          CPU占有率
*********************************************************************************************************/
extern INT8S OSCPUUsageGet(void);

/*********************************************************************************************************
** Function name:           OSIntNestingGet
** Descriptions:            返回中断嵌套层次
** input parameters:        none
** ouput parameters: 		none
** Returned value:          OSIntNesting
*********************************************************************************************************/
extern INT8U OSIntNestingGet(void);

/*********************************************************************************************************
** Function name:           OSTCBPrioTblGet
** Descriptions:            返回任务优先级列表
** input parameters:        none
** Returned value:          任务优先级列表
*********************************************************************************************************/
extern OS_TCB **OSTCBPrioTblGet(void);

/*********************************************************************************************************
** Function name:           OSTaskCreateHookSet
** Descriptions:            设置任务创建钩子函数
** input parameters:        pfucTaskIdleHook: 任务创建钩子函数
** ouput parameters: 		none
** Returned value:          none
*********************************************************************************************************/
extern void OSTaskCreateHookSet(void (* pfucOSTaskCreateHook)(OS_TCB *ptcb));

/*********************************************************************************************************
** Function name:           OSTaskDelHookSet
** Descriptions:            设置任务删除钩子函数
** input parameters:        pfucTaskIdleHook: 任务删除钩子函数
** ouput parameters: 		none
** Returned value:          none
*********************************************************************************************************/
extern void OSTaskDelHookSet(void (* pfucOSTaskDelHook)(OS_TCB *ptcb));

/*********************************************************************************************************
** Function name:           OSTaskStatHookSet
** Descriptions:            设置任务状态钩子函数
** input parameters:        pfucTaskIdleHook: 任务状态钩子函数
** ouput parameters: 		none
** Returned value:          none
*********************************************************************************************************/
extern void OSTaskStatHookSet(void (* pfucTaskStatHook)(void));

/*********************************************************************************************************
** Function name:           OSTimeTickHookSet
** Descriptions:            设置时钟节拍钩子函数
** input parameters:        pfucTimeTickHook: 时钟节拍钩子函数
** Returned value:          none
*********************************************************************************************************/
extern void OSTimeTickHookSet(void (* pfucTimeTickHook)(void));

/*********************************************************************************************************
** Function name:           OSTaskIdleHookSet
** Descriptions:            设置空闲任务钩子函数
** input parameters:        pfucTaskIdleHook: 空闲任务钩子函数
** ouput parameters: 		none
** Returned value:          none
*********************************************************************************************************/
extern void OSTaskIdleHookSet(void (* pfucTaskIdleHook)(void));

/*********************************************************************************************************
** Function name:           OSTimeLag
** Descriptions:            等待时间间隔
** input parameters:        usTicks: 与上次调用本函数之间间隔的时钟节拍数目
** ouput parameters: 		none
** Returned value:          none
*********************************************************************************************************/
extern void  OSTimeLag(INT16U usTicks);

#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */
#endif                                                                  /*  __uCOS_II_ADD_H             */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
