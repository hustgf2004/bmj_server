/****************************************Copyright (c)****************************************************
**                            
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tpHooks.c
** Latest modified Date:    2014-08-25
** Latest Version:          1.0
** Descriptions:            系统接口层函数集
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2014-08-25
** Version:                 1.0
** Descriptions:            初始版本
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#include    "..\tpCommon.h"

    /*
     *  外部共享使用变量
     */


    /*
     *  内部使用变量
     */


    /*
     *  函数声明
     */

/*********************************************************************************************************
** Function name:           tpOSQueueCreate
** Descriptions:            队列创建
** input parameters:        pv                  消息队列内存
**                          uiSize              消息队列深度
** output parameters:       none
** Returned value:          消息指针            成功
**                          NULL                失败
*********************************************************************************************************/
void *tpOSQueueCreate(void *pv, INT32U uiSize)
{
    
    return OSQCreate(pv, uiSize);                                       /*  创建消息队列                */
}


/*********************************************************************************************************
** Function name:           tpOSQueueDel
** Descriptions:            队列删除
** input parameters:        pv                  消息队列
**                          
** output parameters:       pucErr              错误代码
** Returned value:          NULL                成功
**                          消息指针            失败
*********************************************************************************************************/
void *tpOSQueueDel(void *pv, INT8U *pucErr)
{
    
    return OSQDel(pv, OS_DEL_ALWAYS, pucErr);                           /*  删除消息队列                */
}


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
void *tpOSQueuePend(void *pv, INT32U uiTimeOut, INT8U *pucErr)
{
    
    return OSQPend(pv, uiTimeOut, pucErr);
}

/*********************************************************************************************************
** Function name:           OSQueuePost
** Descriptions:            队列等待
** input parameters:        pv                  消息队列
**                          msg                 消息指针
**                          
** output parameters:       none
** Returned value:          OS_NO_ERR       成功
**                          参考ucos_ii.h错误代码
**                          
*********************************************************************************************************/
INT8U tpOSQueuePost(void *pv, void *msg)
{
    return OSQPost(pv, msg);
}

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
void *tpOSSemCreate(INT16U usCnt)
{
    return OSSemCreate(usCnt);
}

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
void *tpOSSemDel(void *pSem, INT8U *pucErr)
{
    return OSSemDel(pSem, OS_DEL_ALWAYS, pucErr);
}

/*********************************************************************************************************
** Function name:           tpOSSemPend
** Descriptions:            信号量等待
** input parameters:        pSem            信号量指针
**                          usTimeOut       等待超时因子
**                          
**
**                       
** output parameters:       pucErr          错误代码存放地址
**                          参考ucos_ii.h错误代码
** Returned value:          none
**                          
**                          
*********************************************************************************************************/
void tpOSSemPend(void *pSem, INT16U usTimeOut, INT8U *pucErr)
{
    OSSemPend(pSem, usTimeOut, pucErr);
}

/*********************************************************************************************************
** Function name:           tpOSSemPost
** Descriptions:            信号量发送
** input parameters:        pSem            信号量指针
**                          
** output parameters:       none
** Returned value:          OS_NO_ERR       成功
**                          参考ucos_ii.h错误代码
**                          
*********************************************************************************************************/
INT8U tpOSSemPost(void *pSem)
{
    return OSSemPost(pSem);    
}

/*********************************************************************************************************
** Function name:           tpOSTimeDly
** Descriptions:            系统延时
** input parameters:        usMsTicks           延时ms
**                          
** output parameters:       none
** Returned value:          none                         
*********************************************************************************************************/
void tpOSTimeDly(INT16U usMsTicks)
{
    INT16U usTicks;
    usTicks = (usTicks * __GuiOS_TICKS_PER_SEC + 999) / 1000;
        
    OSTimeDly(usTicks);
}

/*********************************************************************************************************
** Function name:           tpOSHeapMalloc
** Descriptions:            堆分配内存
** input parameters:        ulSize:             内存大小
** output parameters:       none
** Returned value:          内存地址,NULL为不成功
*********************************************************************************************************/
void *tpOSHeapMalloc (INT32U ulSize)
{
    return sysHeapMalloc(ulSize);
}

/*********************************************************************************************************
** Function name:           tpEnterCritical
** Descriptions:            禁止中断
** input parameters:        none
** output parameters:       none
** Returned value:          SYS_OK:             成功
**                          负数:               错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S tpEnterCritical(void)
{
    OS_ENTER_CRITICAL();
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           tpExitCritical
** Descriptions:            允许中断
** input parameters:        none
** output parameters:       none
** Returned value:          TP_OK:              成功
**                          负数:               错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S tpExitCritical(void)
{
    OS_EXIT_CRITICAL();
    return SYS_OK;
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

