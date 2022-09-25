/****************************************Copyright (c)****************************************************
**                            
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tpIf.h
** Latest modified Date:    2014-08-25
** Latest Version:          1.0
** Descriptions:            协议包接收处理接口头文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2014-08-25
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
#ifndef __TP_IF_H
#define __TP_IF_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
  接口消息
*********************************************************************************************************/
struct tp_if_msg {
    TP_DRV_INFO_BASE    *ptdibDriverInfo;                               /*  驱动信息                    */
    TP_PACKET_HEAD      *ptphPacketData;                                /*  数据帧                      */
};
typedef  struct tp_if_msg      TP_IF_MSG;

/*********************************************************************************************************
** Function name:           tpIfInit
** Descriptions:            接口初始化
** input parameters:        none
** output parameters:       none
** Returned value:          TP_OK:              成功
**                          负数:               错误,绝对值参考tp.h
*********************************************************************************************************/
extern INT32S tpIfInit(void);

/*********************************************************************************************************
** Function name:           tpRemotePacketReceive
** Descriptions:            协议接收到数据帧
** input parameters:        pdiDriverInfo:  驱动信息
**                          ptphPacketData: 数据帧   
** output parameters:       none
** Returned value:          TP_OK:          成功
**                          负数:           错误,绝对值参考tp.h
*********************************************************************************************************/
extern INT32S tpRemotePacketReceive(TP_DRV_INFO_BASE * pdibDriverInfo, TP_PACKET_HEAD *pzphPacketData);

#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __TP_IF_H                   */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
