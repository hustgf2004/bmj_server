/****************************************Copyright (c)****************************************************
**                            
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tmUart2Can.h
** Latest modified Date:    2011-04-17
** Latest Version:          1.0
** Descriptions:            UART 网络驱动接口文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:               
** Created date:            2011-04-17
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
#ifndef __TMUART_DRIV_H
#define __TMUART_DRIV_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

    /*********************************************************************************************************
  字节顺序变换
*********************************************************************************************************/
#ifndef tm_ntohl
#define tm_ntohl(x) x = (INT32U)(((INT8U *)&(x))[0] << 24 | \
                                 ((INT8U *)&(x))[1] << 16 | \
                                 ((INT8U *)&(x))[2] << 8  | \
                                 ((INT8U *)&(x))[3] << 0)
#endif                                                                  /*  tm_ntohl                    */

#ifndef tm_htonl
#define tm_htonl(x) x = (INT32U)(((INT8U *)&(x))[0] << 24 | \
                                 ((INT8U *)&(x))[1] << 16 | \
                                 ((INT8U *)&(x))[2] << 8  | \
                                 ((INT8U *)&(x))[3] << 0)
#endif                                                                  /*  tm_htonl                    */

#ifndef tm_ntohs
#define tm_ntohs(x) x = (INT16U)(((INT8U *)&(x))[0] << 8  | \
                                 ((INT8U *)&(x))[1] << 0)
#endif                                                                  /*  tm_ntohs                    */

#ifndef tm_htons
#define tm_htons(x) x = (INT16U)(((INT8U *)&(x))[0] << 8  | \
                                 ((INT8U *)&(x))[1] << 0)
#endif                                                                  /*  tm_htons                    */

/*********************************************************************************************************
    协议帧信息结构体定义
*********************************************************************************************************/
struct __frame_packet
{
    union {
        unsigned long    ulDWord;
        struct {                    
            unsigned int ulSrc      :8;                                 /*  源地址位域                  */
            unsigned int ulDst      :8;                                 /*  目的地址位域                */
            unsigned int ulRsv      :2;                                 /*  保留位域                    */
            unsigned int ulDir      :2;                                 /*  方向码位域                  */
            unsigned int ulAck      :2;                                 /*  响应码位域                  */
            unsigned int ulCmd      :4;                                 /*  命令码位域                  */
            unsigned int ulPri      :3;                                 /*  优先级位域                  */
            unsigned int ucIsRemote :1;                                 /*  是否是远程帧                */
            unsigned int ucIsExtend :1;                                 /*  是否是扩展帧                */
        }ulBits;
    }ulId;                                                              /*  帧ID                        */
    INT8U   ucDataLen;                                                  /*  数据长度                    */
    INT8U   ucBuf[8];                                                   /*  帧数据                      */
};
typedef struct __frame_packet   __FRAME_PACKET;
typedef struct __frame_packet  *__PFRAME_PACKET;

    /*
     *  内部处理结构
     */
struct __serial_frame_del {    
    __FRAME_PACKET  *pfrPacket; 
    INT8U            ucXor; 
    INT16U           usLen;
    INT32U           ulId;
    INT8U            ucState;
};
typedef struct __serial_frame_del   __SERIAL_FRAME_DEL;
typedef struct __serial_frame_del  *__PSERIAL_FRAME_DEL;
 

/*********************************************************************************************************
  接口函数列表
*********************************************************************************************************/
extern void uartReceiveHook (void *pRsv, INT8U ucRbr, INT8U ucLsr);
extern INT32S uart2CanSend (INT8U  ucChn, struct __frame_packet   *pData);

#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __TMUART_DRIV_H              */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
