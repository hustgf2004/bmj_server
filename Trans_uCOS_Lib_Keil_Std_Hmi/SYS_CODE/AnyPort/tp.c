/****************************************Copyright (c)****************************************************
**                          Beijing Hengfengli Technology CO.,LTD.
**                                      
**                                 http://www.hengfengli.com/
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tp.c
** Latest modified Date:    2013-09-26
** Latest Version:          1.0
** Descriptions:            tmcan module
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
#include    ".\tpCommon.h"
#include    ".\main.h"


/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/
static __TP_LIST                  __GlsTmData[TP_MAX_DEVICE];           /*  用于保存端口链表数据        */
static TP_DRV_INFO_BASE          *__GpdDrvs[TP_MAX_DRIVER];             /*  用于保存网络驱动数据        */
//static TP_DRV                    *__GpdDrvs[TP_MAX_DRIVER];             /*  用于保存网络驱动数据        */
    /*  
     *  用于保存网络驱动数据
     */
TP_DRV_INFO  *const __GptdiDrvs[TP_MAX_DRIVER] ={
                                                    NULL,
                                                    NULL,
                                                   (TP_DRV_INFO* const)&GtdiCanHMIDrvInfo,
                                                    NULL,                                                                                                                 
                                                };          

/*********************************************************************************************************
** Function name:           tpDrvsInit
** Descriptions:            基于AnyPort协议初始化驱动
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void tpDrvsInit (void)
{    
    INT32U  i;
    
    /*
     *  添加通讯驱动
     */

    for (i = 0; i < TP_MAX_DRIVER; i++) {
        tpRemoteDrvAdd((TP_DRV_INFO_BASE*)__GptdiDrvs[i]);
    }

}

/*********************************************************************************************************
** Function name:           tpInit
** Descriptions:            协议栈初始化
** input parameters:        none
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_if.h           
*********************************************************************************************************/
INT32S tpInit (void)
{
    INT32S lRt;                                                         /*  返回值                      */
    
    lRt = tpDevicePortInit(__GlsTmData, TP_MAX_DEVICE);                 /*  功能端口管理初始化          */ 
    if (lRt < 0) {
        return lRt;
    }

    lRt = tpRemoteDrvsInit(__GpdDrvs ,TP_MAX_DRIVER, NULL);
    if (lRt < 0) {
        return lRt;
    }
    
    lRt = tpHostInit();
    if (lRt < 0) {
        return lRt;
    }

    /*lRt = __tmInit();
    if (lRt < 0) {
        return lRt;
    }*/

    lRt = tpIfInit();
    if (lRt < 0) {
        return lRt;
    }

    return (lRt);
}

/*********************************************************************************************************
** Function name:           tpRead
** Descriptions:            端口读
** input parameters:        uiChnl          驱动通道号
**                          ucAddr          端口地址
**                          usLen           数据数目
**                          
** output parameters:       pvData          读到的数据
** Returned value:          >=0             完成的数据数目
**                          负数            错误,绝对值参考sys_if.h          
*********************************************************************************************************/
INT32S tpRead(INT32U uiChnl, INT8U ucAddr, INT16U usLen, void *pvData)
{                                              
    INT8U ucDst = 0, ucSrc = 0;
    INT8U ucFType = TP_NBR_FLAG_CHAR;
    if (uiChnl == TP_DEFAULT_CHNL) {
        return tpReadLocal(uiChnl, ucAddr, usLen, pvData);
    } else {
        return tpReadRemoteEx(uiChnl, ucDst, ucSrc, ucAddr, usLen, pvData, ucFType);
    }
}
INT32S tpReadBus(INT32U uiChnl, INT8U ucDst, INT8U ucSrc, INT8U ucAddr, INT16U usLen, void *pvData)
{     
    INT8U ucFType = TP_BUS_FLAG_CHAR;    
    if (uiChnl == TP_DEFAULT_CHNL) {
        return tpReadLocal(uiChnl, ucAddr, usLen, pvData);
    } else {
        return tpReadRemoteEx(uiChnl, ucDst, ucSrc, ucAddr, usLen, pvData, ucFType);
    }
}
/*********************************************************************************************************
** Function name:           tpWrite
** Descriptions:            端口写
** input parameters:        uiChnl          驱动通道号
**                          ucAddr          端口地址
**                          usLen           数据数目
**                          pvData          数据保存地址
**                          ucAck           0--无回复 1--有回复
** output parameters:       none
** Returned value:          >=0             完成的数据数目
**                          负数            错误,绝对值参考sys_if.h          
*********************************************************************************************************/
INT32S tpWrite(INT32U uiChnl, INT8U ucAddr, INT16U usLen, void *pvData, INT8U ucAck)
{
    INT8U ucDst = 0, ucSrc = 0;
    INT8U ucFType = TP_NBR_FLAG_CHAR;
    if (uiChnl == TP_DEFAULT_CHNL) {
        return tpWriteLocal(uiChnl, ucAddr, usLen, pvData);
    } else {
        return tpWriteRemoteEx(uiChnl, ucDst, ucSrc, ucAddr, usLen, pvData, ucAck, ucFType);
    }
}

INT32S tpWriteBus(INT32U uiChnl, INT8U ucDst, INT8U ucSrc, INT8U ucAddr, INT16U usLen, void *pvData, INT8U ucAck)
{
    INT8U ucFType = TP_BUS_FLAG_CHAR;
    if (uiChnl == TP_DEFAULT_CHNL) {
        return tpWriteLocal(uiChnl, ucAddr, usLen, pvData);
    } else {
        return tpWriteRemoteEx(uiChnl, ucDst, ucSrc, ucAddr, usLen, pvData, ucAck, ucFType);
    }
}



/*********************************************************************************************************
** Function name:           tpTick
** Descriptions:            时钟节拍处理
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void tpTick (void)
{ 
    __tpTick();                                                         /*  TP_HOST_EN                  */
}

/*********************************************************************************************************
** Function name:           tpPacketCheck
** Descriptions:            检测网络帧
** input parameters:        pdibThis:   底层驱动
**                          ptphPacket: 数据帧
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S tpPacketCheck(TP_DRV_INFO_BASE *pdibThis, TP_PACKET_HEAD *ptphPacket)
{
    TP_PACKET *ptp = (TP_PACKET *)ptphPacket;
    /* 
     *  参数过滤
     */
    if (NULL == pdibThis) {
        return (-SYS_NOT_OK);
    }
    if (NULL == ptphPacket) {
        return (-SYS_NOT_OK);
    }
    
    if (NULL == ptp->pucDat) {                                          /*  数据有效性检测              */
        return (-SYS_PACKET_ERR);
    }
    if ((ptphPacket->tpHeadBits.Bits.uiFtype != TP_NBR_FLAG_CHAR) &&
        (ptphPacket->tpHeadBits.Bits.uiFtype != TP_BUS_FLAG_CHAR)) {    /*  协议类型检测                */         
        return (-SYS_PACKET_ERR);
    }
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           tpRemoteRecieve
** Descriptions:            接收帧处理
** input parameters:        ptdibThis:  网络驱动标识
**                          ptphPacket: 数据帧
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_if.h
*********************************************************************************************************/
//INT32S tmReceive(TP_DRV_INFO_BASE *ptdibThis, TP_PACKET_HEAD *ptphPacket)
//{
//  __HEADBITS_BUS hbb;
//    hbb.uiWord = ptphPacket->tpHeadBits.uiWord;
//    if ((ptphPacket->tpHeadBits.Bits.uiRF < TP_RREAD_FLG)    || 
//        ((ptphPacket->tpHeadBits.Bits.uiRF >= TP_RFREAD_FLG) &&
//         (ptphPacket->tpHeadBits.Bits.uiSegPolo == 0x03) &&
//         (ptphPacket->tpHeadBits.Bits.uiFtype == TMNBR_FLAG_CHAR)) ||
//        ((ptphPacket->tpHeadBits.Bits.uiRF >= TP_RFREAD_FLG) &&
//         (hbb.Bits.uiSrcMacId == GetShieldNum()) &&
//         (ptphPacket->tpHeadBits.Bits.uiFtype == TMBUS_FLAG_CHAR))) {
//        return tpDeviceReceive(ptdibThis, ptphPacket);
//    } else {
//        return tpHostReceive(ptdibThis, ptphPacket);
//    }
//}

/*********************************************************************************************************
** Function name:           tpDrvCreate
** Descriptions:            网络驱动程序初始化
** input parameters:        ptdibThis:          网络标识
** output parameters:       none
** Returned value:          SYS_OK:             成功
**                          负数:               错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S tpDrvCreate (TP_DRV_INFO_BASE *ptdibThis)
{
    return __tmCreate(ptdibThis);
}

/*********************************************************************************************************
** Function name:           tpDrvDel
** Descriptions:            删除网络驱动程序
** input parameters:        ptdibThis:          网络标识
** output parameters:       none
** Returned value:          SYS_OK:             成功
**                          负数:               错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S tpDrvDel (TP_DRV_INFO_BASE *ptdibThis)
{
    return __tmDel(ptdibThis);
}

/*********************************************************************************************************
** Function name:           tpDrvWrite
** Descriptions:            网络驱动写操作
** input parameters:        ptdibThis:          网络标识
**                          ucAddr:             端口地址
**                          usLen:              数据数目
**                          pvData:             数据保存地址
** output parameters:       none
** Returned value:          >=0:                完成的数据数目
**                          负数:               错误,绝对值参考sys_if.h          
*********************************************************************************************************/
INT32S tpDrvWrite(TP_DRV_INFO_BASE     *ptdibThis,
                  INT8U                 ucAddr,
                  INT16U                usLen,
                  void                 *pvData,
                  INT8U                 ucAck)
{
    return  __tmWriteEx(ptdibThis, 0, 0, ucAddr, usLen, pvData, ucAck, TP_NBR_FLAG_CHAR);
}

INT32S tpDrvWriteEx(TP_DRV_INFO_BASE     *ptdibThis,
                  INT8U                 ucDst,
                  INT8U                 ucSrc,
                  INT8U                 ucAddr,
                  INT16U                usLen,
                  void                 *pvData,
                  INT8U                 ucAck,
                  INT8U                 ucFType)
{
    return  __tmWriteEx(ptdibThis, ucDst, ucSrc, ucAddr, usLen, pvData, ucAck, ucFType);
}
/*********************************************************************************************************
** Function name:           tpDrvRead
** Descriptions:            网络驱动读操作
** input parameters:        ptdibThis:          网络标识
**                          ucDstAddr:          目的地址
**                          ucSrcAddr:          源地址
**                          ucAddr:             端口地址
**                          usLen:              数据数目
** output parameters:       pvDat:              数据
** Returned value:          >=0:                完成的数据数目
**                          负数:               错误,绝对值参考sys_if.h          
*********************************************************************************************************/
INT32S tpDrvRead (TP_DRV_INFO_BASE     *ptdibThis,
                  INT8U                 ucAddr,
                  INT16U                usLen,
                  void                 *pvDat)
{
    return  __tmReadEx(ptdibThis, 0, 0, ucAddr, usLen, pvDat, TP_NBR_FLAG_CHAR);
}
INT32S tpDrvReadEx(TP_DRV_INFO_BASE     *ptdibThis,
                  INT8U                 ucDst,
                  INT8U                 ucSrc,
                  INT8U                 ucAddr,
                  INT16U                usLen,
                  void                 *pvDat,
                  INT8U                 ucFType)
{
    return  __tmReadEx(ptdibThis, ucDst, ucSrc, ucAddr, usLen, pvDat, ucFType);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

