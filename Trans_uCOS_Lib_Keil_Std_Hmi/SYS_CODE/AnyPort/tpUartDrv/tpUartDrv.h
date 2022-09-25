/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn                                   
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tpUartDrv.h
** Latest modified Date:    2019-01-25
** Latest Version:          1.0
** Descriptions:            UART 网络驱动接口文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2019-01-25
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
#ifndef __TPUART_DRV_H
#define __TPUART_DRV_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
  配置信息
*********************************************************************************************************/
#define       __UART_CHNL_BASE          2                               /*  UART通道标识                */
#define       __TP_UART1              __UART_CHNL_BASE + UART1          /*  UART1通道标识               */
#define       __TP_UART2              __UART_CHNL_BASE + UART2          /*  UART2通道标识               */
#define       __TP_UART3              __UART_CHNL_BASE + UART3          /*  UART3通道标识               */
#define       __TP_UART4              __UART_CHNL_BASE + UART4          /*  UART4通道标识               */
#define       __TP_UART5              __UART_CHNL_BASE + UART5          /*  UART5通道标识               */
#define       __TP_UART6              __UART_CHNL_BASE + UART6          /*  UART6通道标识               */
#define       __TP_UART7              __UART_CHNL_BASE + UART7          /*  UART7通道标识               */
#define       __TP_UART8              __UART_CHNL_BASE + UART8          /*  UART8通道标识               */

    
#define     __TPUART_REMOTE_TIMEOUT     1000                             /*  远程访问超时时间(ms)        */

    /*
     *  内部处理结构
     */
struct __serial_frame_del {
    INT8U       ucXor;
    TP_PACKET  *ptpPacket;  
    INT16U      usLen;
    INT16U      usLenTmep;
    INT16U      usBufLenRd;
    INT32U      ulId;
    INT8U       ucState;
};
typedef struct __serial_frame_del   __SERIAL_FRAME_DEL;
typedef struct __serial_frame_del  *__PSERIAL_FRAME_DEL;


/*********************************************************************************************************
  接口函数列表
*********************************************************************************************************/

extern const TP_DRV_INFO  GtdiUart1DrvInfo;
extern const TP_DRV_INFO  GtdiUart2DrvInfo;
extern const TP_DRV_INFO  GtdiUart3DrvInfo;
extern const TP_DRV_INFO  GtdiUart4DrvInfo;
extern const TP_DRV_INFO  GtdiUart5DrvInfo;
extern const TP_DRV_INFO  GtdiUart6DrvInfo;
extern const TP_DRV_INFO  GtdiUart7DrvInfo;
extern const TP_DRV_INFO  GtdiUart8DrvInfo;
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __TPUART_DRV_H              */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

