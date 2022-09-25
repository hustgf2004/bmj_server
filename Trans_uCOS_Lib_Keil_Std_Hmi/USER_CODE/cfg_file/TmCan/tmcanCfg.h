/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tmcan_cfg.h
** Latest modified Date:    2014-08-25
** Latest Version:          1.0.0
** Descriptions:            tmcan 配置头文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2014-08-25
** Version:                 1.0.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*********************************************************************************************************/
#ifndef __TMCAN_CFG_H
#define __TMCAN_CFG_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
  代码裁剪
*********************************************************************************************************/

/*********************************************************************************************************
  资源配置
*********************************************************************************************************/
#define     TM_MAX_DEVICE           255                                 /*  最大本地设备数目            */

#define     TM_POLL_TASK_PRIO       2                                   /*  协议处理线程优先级(不可更改)*/
#define     TM_POLL_TASK_SIZE       512                                 /*  接收处理线程堆栈(不可更改)  */

#define     TM_MAX_DRIVER           12                                   /*  最大本地驱动数目(不可更改)  */ 

/*********************************************************************************************************
  接口宏定义
*********************************************************************************************************/
#define     TM_IF_THREAD_SIZE       256                                 /*  接收处理线程堆栈大小        */
#define     TM_IF_THREAD_ID         8                                   /*  接收处理线程优先级(不可更改)*/
#define     TM_IF_Q_SIZE            16                                  /*  接收处理线程数据队列大小    */


/*********************************************************************************************************
  TASK_HOST 任务ID、优先级、堆栈设置及函数声明                                
*********************************************************************************************************/
#define     TASK_HOST_ID            2                                   /* 任务的ID                     */
#define     TASK_HOST_PRIO          TASK_HOST_ID                        /* 任务的优先级                 */
#define     TASK_HOST_STACK_SIZE    384                                 /* 定义用户堆栈长度             */



#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */
#endif                                                                  /*  __TMCAN_CFG_H               */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
