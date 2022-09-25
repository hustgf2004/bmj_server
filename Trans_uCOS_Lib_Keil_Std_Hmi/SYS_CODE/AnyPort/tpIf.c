/****************************************Copyright (c)****************************************************
**                                  Tongxin Microelectronics Co.,Ltd.
**                                      
**                                   http://www.tsinghuaic.com  
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tpIf.c
** Latest modified Date:    2019-01-25
** Latest Version:          2.0
** Descriptions:            AnyPort协议包接收处理接口
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2014-08-25
** Version:                 1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             超人力霸王
** Modified date:           2019-01-25
** Version:                 2.0
** Descriptions:            拆分数据接收线程分为主机接收线程和从机接收线程
**                          使在功能端口中可以发起主机操作
*********************************************************************************************************/
#include    ".\tpCommon.h"   
#include    "main.h"

/*********************************************************************************************************
  以下是为简化协议驱动而添加的变量和函数声明
*********************************************************************************************************/
static INT32U   __GulTpIfHostMsg;                                       /*  主机接收消息队列            */
static INT32U   __GulTpIfDeviceMsg;                                     /*  从机接受消息队列            */
static void     __tpRemoteHostThread(void *pvData);                     /*  声明主机接收任务            */
static void     __tpRemoteDeviceThread(void *pvData);                   /*  声明从机接收任务            */
static OS_STK   TP_HOST_STACK[TP_IF_HOST_THREAD_SIZE];                  /*  定义主机接收任务堆栈        */
static OS_STK   TP_DEVICE_STACK[TP_IF_THREAD_SIZE];                     /*  定义从机接收任务堆栈        */
static OS_STK   TASK_HOST_STACK[TP_POLL_THREAD_SIZE];                   /* 定义任务host 堆栈            */


extern void __tpHostPollTask(void *pdata);

/*********************************************************************************************************
** Function name:           tpHostInit
** Descriptions:            协议主机初始化
** input parameters:        none
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_if.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
INT32S tpHostInit (void)
{
    INT32S siErr;
    siErr = __tpHostInitEx();
    if (siErr != SYS_OK) {
        return (siErr);
    }
    /*
     *  创建主机轮询任务
     */
    if (OSTaskCreate(__tpHostPollTask,
                     (void *)0,
                     &TASK_HOST_STACK[TP_POLL_THREAD_SIZE - 1],
                     TP_POLL_THREAD_PRIO) != OS_NO_ERR) {
        
        return (-SYS_NOT_OK);
    }    
    return SYS_OK;
}


/*********************************************************************************************************
** Function name:           tpIfInit
** Descriptions:            协议处理接口初始化
** input parameters:        none
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S tpIfInit (void)
{
    __GulTpIfHostMsg    = sysMsgCreate(TP_IF_Q_SIZE, sizeof(TP_IF_MSG));
    __GulTpIfDeviceMsg  = sysMsgCreate(TP_IF_Q_SIZE, sizeof(TP_IF_MSG));
    if ((__GulTpIfHostMsg == 0)||(__GulTpIfDeviceMsg == 0)) {
        return (-SYS_NO_MEMORY);
    }
    
    if (OSTaskCreate(__tpRemoteHostThread,
                     (void *)0,
                     &TP_HOST_STACK[TP_IF_HOST_THREAD_SIZE - 1],
                     TP_IF_HOST_THREAD_PRIO) != OS_NO_ERR) {
        sysMsgDel(__GulTpIfHostMsg);
        __GulTpIfHostMsg = 0;
        sysMsgDel(__GulTpIfDeviceMsg);
        __GulTpIfDeviceMsg = 0;
        return (-SYS_PARA_ERR);
    }   
    if (OSTaskCreate(__tpRemoteDeviceThread,
                     (void*)0,
                     &TP_DEVICE_STACK[TP_IF_THREAD_SIZE - 1],
                     TP_IF_THREAD_PRIO) != OS_NO_ERR)
    {
        sysMsgDel(__GulTpIfHostMsg);
        __GulTpIfHostMsg = 0;
        sysMsgDel(__GulTpIfDeviceMsg);
        __GulTpIfDeviceMsg = 0;
        return (-SYS_PARA_ERR);
    }
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           __tpRemoteHostThread
** Descriptions:            主机协议接收处理任务线程
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
static void __tpRemoteHostThread (void *pvData)
{
    TP_IF_MSG imMsg;                                                    /*  消息                        */

    pvData = pvData;
    while (1) {        
        if (sysMsgPend(__GulTpIfHostMsg, (INT8U *)&imMsg, 0) < 0) {
            continue;
        } 

        /*
         *  帧校验
         */
        if (tpPacketCheck(imMsg.ptdibDriverInfo, imMsg.ptphPacketData) == 0) {
            tpHostReceive(imMsg.ptdibDriverInfo, imMsg.ptphPacketData);
			//ADD_COMM_ONCE();
        }
        sysHeapFree(imMsg.ptphPacketData);
    }
}
/*********************************************************************************************************
** Function name:           __tpRemoteHostThread
** Descriptions:            从机协议接收处理任务线程
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
static void __tpRemoteDeviceThread(void * pvData)
{
    TP_IF_MSG imMsg;                                                    /*  消息                        */

    pvData = pvData;
    while (1) {        
        if (sysMsgPend(__GulTpIfDeviceMsg, (INT8U *)&imMsg, 0) < 0) {
            continue;
        }
        /*
         *  帧校验
         */
        if (tpPacketCheck(imMsg.ptdibDriverInfo, imMsg.ptphPacketData) == 0) {
            tpDeviceReceive(imMsg.ptdibDriverInfo, imMsg.ptphPacketData);
        }
        sysHeapFree(imMsg.ptphPacketData);
    }

}
/*********************************************************************************************************
** Function name:           tpRemotePacketReceive
** Descriptions:            协议接收到数据帧
** input parameters:        pdiDriverInfo:      驱动信息
**                          ptphPacketData:     数据帧   
** output parameters:       none
** Returned value:          SYS_OK:             成功
**                          负数:               错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S tpRemotePacketReceive(TP_DRV_INFO_BASE * ptdibDriverInfo, TP_PACKET_HEAD *ptphPacketData)
{
    TP_IF_MSG imMsg;                                                    /*  消息                        */
    imMsg.ptdibDriverInfo   = ptdibDriverInfo;
    imMsg.ptphPacketData    = ptphPacketData;
    
    if ((ptphPacketData->tpHeadBits.Bits.uiRF < TP_RREAD_FLG) ||
        (ptphPacketData->tpHeadBits.Bits.uiRsv == 1)) {
        if (sysMsgPost(__GulTpIfDeviceMsg, (INT8U *)&imMsg, 0) < 0) {
            sysHeapFree(ptphPacketData);
            return (-SYS_PARA_ERR);
        }        
    } else {
        if (sysMsgPost(__GulTpIfHostMsg, (INT8U *)&imMsg, 0) < 0) {
            sysHeapFree(ptphPacketData);
            return (-SYS_PARA_ERR);
        }
    }    
    return SYS_OK;
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

