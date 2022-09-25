/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tpKey.c
** Latest modified Date:    2022-09-17
** Latest Version:          1.0
** Descriptions:            按键功能端口实现
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2022-09-17
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
#include ".\main.h"

/*********************************************************************************************************
  函数声明
*********************************************************************************************************/
static INT32S __tpCreate(const TP_PORT_INFO *ptpiThis);
static INT32S __tpDel(const TP_PORT_INFO *ptpiThis);
static INT32S __tpRead(const TP_PORT_INFO *ptpiThis, INT8U ucChanle, INT16U usLen, void *pvData);
static INT32S __tpWrite(const TP_PORT_INFO *ptpiThis, INT8U ucChanle, INT16U usLen, void *pvData);

/*********************************************************************************************************
  功能部件信息
*********************************************************************************************************/
struct tp_key_info {
    TP_PORT_INFO tp;                                                    /*  功能部件基本信息            */
    /*
     *  此驱动需要附加的信息
     */        
};

typedef  struct tp_key_info  TP_KEY_INFO;

/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/
const TP_PORT_FUNC __GtpfKey = {
    __tpCreate,
    __tpDel,
    __tpRead,
    __tpWrite
};

/*********************************************************************************************************
  端口定义
*********************************************************************************************************/
static const TP_KEY_INFO __GtpiKey = {                                  /*  端口信息                    */
    {
        (TP_PORT_FUNC *)&__GtpfKey,
      __TP_KEY,
        TRUE
    }
};

extern unsigned long  GulKeyMsg;
/*********************************************************************************************************
** Function name:           tpKeyInit
** Descriptions:            端口加载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void tpKeyInit(void)
{ 
    /*
     *  添加端口
     */
    tpDevicePortAdd((TP_PORT_INFO *)&__GtpiKey);
}
/*********************************************************************************************************
** Function name:           tpKeyDel
** Descriptions:            端口卸载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void tpKeyDel(void)
{ 
    /*
     *  添加端口
     */
    tpDevicePortDel((TP_PORT_INFO *)&__GtpiKey);
}

/*********************************************************************************************************
** Function name:           __tpCreate
** Descriptions:            创建端口
** input parameters:        ptpiThis: 端口信息
** output parameters:       none
** Returned value:          SYS_OK:  成功
**                          负数:    错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __tpCreate(const TP_PORT_INFO *ptpiThis)
{    
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           __tpDel
** Descriptions:            删除端口
** input parameters:        ptpiThis:  端口信息
** output parameters:       none
** Returned value:          SYS_OK:  成功
**                          负数:    错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __tpDel(const TP_PORT_INFO *ptpiThis)
{
    return SYS_OK;    
}

/*********************************************************************************************************
** Function name:           __tpRead
** Descriptions:            读端口
** input parameters:        ptpiThis: 端口信息
**                          usLen:    读数据个数
** output parameters:       pvData:   数据缓冲区
** Returned value:          >=0 :     数据数目
*********************************************************************************************************/
static INT32S __tpRead (const TP_PORT_INFO *ptpiThis, INT8U ucChnl, INT16U usLen, void *pvDat)
{
    TP_KEY_INFO        *ptti;                                           /*  设备信息                    */
    INT32S              siErr;
    INT8U              *pucDat = pvDat;


    ptti = (TP_KEY_INFO *)ptpiThis;
    ptti = ptti;   
    

    /*
     *  实际的写代码
     */
   
    return usLen;
}

/*********************************************************************************************************
** Function name:           __tpWrite
** Descriptions:            写端口。
** input parameters:        ptpiThis: 端口信息
**                          usLen:    写数据个数
**                          pvData:   数据缓冲区
** output parameters:       none
** Returned value:          >=0 :     数据数目
*********************************************************************************************************/
static INT32S __tpWrite (const TP_PORT_INFO *ptpiThis, INT8U ucChnl, INT16U usLen, void *pvDat)
{
    TP_KEY_INFO        *ptti;                                           /*  设备信息                    */
    INT32S              siErr;
    INT32U              uiValue;
    const INT32U       *puiValveTbl;

    INT8U               ucBuf[8];
    ptti = (TP_KEY_INFO *)ptpiThis;
    ptti = ptti;    
    /*
     *  实际的写代码
     */        
    if (3 == usLen) {
//        if (0 == memcmp(ucKeyData, pvData, 3))
        sysMsgPost(GulKeyMsg, pvDat, 0);
    }
    return usLen;
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
