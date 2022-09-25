/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tpHooks.h
** Latest modified Date:    2014-08-25
** Latest Version:          1.0.0
** Descriptions:            系统接口函数集
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2014-08-25
** Version:                 1.0.0
** Descriptions:            The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#ifndef __TP_HOOKS_H
#define __TP_HOOKS_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

    /*********************************************************************************************************
** Function name:           tpOSQueueCreate
** Descriptions:            队列创建
** input parameters:        pv                  消息队列内存
**                          uiSize              消息队列深度
** output parameters:       none
** Returned value:          消息指针            成功
**                          NULL                失败
*********************************************************************************************************/
extern void *tpOSQueueCreate(void *pv, INT32U uiSize);
    
/*********************************************************************************************************
** Function name:           tpOSQueueDel
** Descriptions:            队列删除
** input parameters:        pv                  消息队列
**                          
** output parameters:       pucErr              错误代码
** Returned value:          NULL                成功
**                          消息指针            失败
*********************************************************************************************************/
extern void *tpOSQueueDel(void *pv, INT8U *pucErr);
    
/*********************************************************************************************************
** Function name:           tpOSQueuePend
** Descriptions:            队列等待
** input parameters:        pv                  消息队列
**                          uiTimeOut           等待超时因子
**                          
** output parameters:       pucErr              返回错误代码
** Returned value:          消息指针            成功
**                          
*********************************************************************************************************/
extern void *tpOSQueuePend(void *pv, INT32U uiTimeOut, INT8U *pucErr);

/*********************************************************************************************************
** Function name:           tpOSQueuePend
** Descriptions:            队列等待
** input parameters:        pv                  消息队列
**                          msg                 消息指针
**                          
** output parameters:       none
** Returned value:          OS_NO_ERR           成功
**                          参考ucos_ii.h错误代码
**                          
*********************************************************************************************************/
extern INT8U tpOSQueuePost(void *pv, void *msg);

/*********************************************************************************************************
** Function name:           tpOSSemCreate
** Descriptions:            信号量创建
** input parameters:        usCnt               信号量初始值
**                          
**                          
**
**                       
** output parameters:       none
** Returned value:          信号量指针          成功
**                          NULL                失败
*********************************************************************************************************/
extern void *tpOSSemCreate(INT16U usCnt);

/*********************************************************************************************************
** Function name:           tpOSSemDel
** Descriptions:            信号量删除
** input parameters:        pSem                信号量指针
**                          
**                          
**                       
** output parameters:       pucErr              错误代码存放地址
**                          参考ucos_ii.h错误代码
** Returned value:          信号量指针          失败
**                          NULL                成功
*********************************************************************************************************/
extern void *tpOSSemDel(void *pSem, INT8U *pucErr);

/*********************************************************************************************************
** Function name:           tpOSSemPend
** Descriptions:            信号量等待
** input parameters:        pSem                信号量指针
**                          usTimeOut           等待超时因子
**                          
**
**                       
** output parameters:       pucErr              错误代码存放地址
**                          参考ucos_ii.h错误代码
** Returned value:          none
**                          
**                          
*********************************************************************************************************/
extern void tpOSSemPend(void *pSem, INT16U usTimeOut, INT8U *pucErr);

/*********************************************************************************************************
** Function name:           tpOSSemPost
** Descriptions:            信号量发送
** input parameters:        pSem                信号量指针
**                          
** output parameters:       none
** Returned value:          OS_NO_ERR           成功
**                          参考ucos_ii.h错误代码
**                          
*********************************************************************************************************/
extern INT8U tpOSSemPost(void *pSem);



/*********************************************************************************************************
** Function name:           tpOSTimeDly
** Descriptions:            系统延时
** input parameters:        usTicks             延时ticks
**                          
** output parameters:       none
** Returned value:          none
**                          
**                          
*********************************************************************************************************/
extern void tpOSTimeDly(INT16U usTicks);

/*********************************************************************************************************
** Function name:           tpOSHeapMalloc
** Descriptions:            堆分配内存
** input parameters:        ulSize:             内存大小
** output parameters:       none
** Returned value:          内存地址,NULL为不成功
** Created by:              
** Created Date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
extern void *tpOSHeapMalloc (INT32U ulSize);



/*********************************************************************************************************
** Function name:           tpEnterCritical
** Descriptions:            禁止中断
** input parameters:        none
** output parameters:       none
** Returned value:          TP_OK:              成功
**                          负数:               错误,绝对值参考tp.h
** Created by:              
** Created Date:            2014-08-25
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
extern INT32S tpEnterCritical(void);

/*********************************************************************************************************
** Function name:           tpExitCritical
** Descriptions:            允许中断
** input parameters:        none
** output parameters:       none
** Returned value:          TP_OK:              成功
**                          负数:               错误,绝对值参考tp.h
** Created by:              
** Created Date:            2014-08-25
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
extern INT32S tpExitCritical(void);


#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __TP_HOOKS_H                */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
