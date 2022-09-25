/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tp_UpBackMaxNum.c
** Latest modified Date:    2014-08-25
** Latest Version:          1.0
** Descriptions:            端口驱动代码文件
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
#include ".\tp_UpBackMaxNum_cfg.h"

    /*
     *  外部共享使用变量
     */
extern INT32U  __GuiIndex;
extern INT8U   __GucUpgradeBuf[];

extern void    (*__GpsysSoftParaGet)(INT32U*);
extern INT32S  (*__GpsysUpgradeBegin)(INT8U*, INT32U);
extern INT32S  (*__GpsysUpgradeDataWrite)(unsigned int);
extern INT32S  (*__GpsysUpgradeEnd)(void);   

   
    /*
     *  内部使用变量
     */
static  INT8U   __SucUpBackMaxNum[3];
     
/*********************************************************************************************************
  函数声明
*********************************************************************************************************/
static INT32S __tpCreate(const TM_PORT_INFO *ptpiThis);
static INT32S __tpDel(const TM_PORT_INFO *ptpiThis);
static INT32S __tpRead(const TM_PORT_INFO *ptpiThis, INT8U ucChanle, INT16U usLen, void *pvData);
static INT32S __tpWrite(const TM_PORT_INFO *ptpiThis, INT8U ucChanle, INT16U usLen, void *pvData);

/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/
const TM_PORT_FUNC GtpfUpBackMaxNum = {
    __tpCreate,
    __tpDel,
    __tpRead,
    __tpWrite
};

/*********************************************************************************************************
** Function name:           __tpCreate
** Descriptions:            创建端口
** input parameters:        ptpiThis: 端口信息
** output parameters:       none
** Returned value:          TM_OK :  成功
**                          负数:    错误,绝对值参考tmcan.h
** Created by:              
** Created Date:            2014-08-25
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT32S __tpCreate (const TM_PORT_INFO *ptpiThis)
{
    TP_UPBACK_MAXNUM_INFO *pttiPortCase;                             /*  设备信息                    */
    
    pttiPortCase = (TP_UPBACK_MAXNUM_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase;
    /*
     *  具体的初始化代码
     */
    __SucUpBackMaxNum[0] = 1;
    __SucUpBackMaxNum[1] = 1; 
    __SucUpBackMaxNum[2] = 1;  
    return TM_OK;
}
/*********************************************************************************************************
** Function name:           __tpDel
** Descriptions:            删除端口
** input parameters:        ptpiThis:  端口信息
** output parameters:       none
** Returned value:          TM_OK :  成功
**                          负数:    错误,绝对值参考tmcan.h
** Created by:              
** Created Date:            2014-08-25
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT32S __tpDel (const TM_PORT_INFO *ptpiThis)
{
    TP_UPBACK_MAXNUM_INFO *pttiPortCase;                             /*  设备信息                    */
    
    pttiPortCase = (TP_UPBACK_MAXNUM_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase;
    /*
     *  具体的卸载代码
     */
    __SucUpBackMaxNum[0] = 1;
    __SucUpBackMaxNum[1] = 1; 
    __SucUpBackMaxNum[2] = 1;   
    return TM_OK;    
}

/*********************************************************************************************************
** Function name:           __tpRead
** Descriptions:            读端口
** input parameters:        ptpiThis: 端口信息
**                          usLen:    读数据个数
** output parameters:       pvData:   数据缓冲区
** Returned value:          >=0 :     数据数目
** Created by:              
** Created Date:            2014-08-25
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT32S __tpRead (const TM_PORT_INFO *ptpiThis, INT8U ucChanle, INT16U usLen, void *pvData)
{
    TP_UPBACK_MAXNUM_INFO *pttiPortCase;                             /*  设备信息                    */
    
    pttiPortCase = (TP_UPBACK_MAXNUM_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase;    
    /*
     *  实际的读代码
     */ 

    memcpy(pvData, __SucUpBackMaxNum, usLen); 
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
** Created by:              
** Created Date:            2014-08-25
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

static INT32S __tpWrite (const TM_PORT_INFO *ptpiThis, INT8U ucChanle, INT16U usLen, void *pvData)
{
    TP_UPBACK_MAXNUM_INFO *pttiPortCase;                             /*  设备信息                    */
    INT32S  siErr;
     
    pttiPortCase = (TP_UPBACK_MAXNUM_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase;    
    
    /*
     *  实际的写代码
     */        
    if (__GucTmDrivChn[(__PORT_DEF_LEFT >> 3) & 0x07][__PORT_DEF_LEFT & 0x07] == ucChanle) {
        __SucUpBackMaxNum[0] = ((INT8U*)pvData)[0];
    } else if (__GucTmDrivChn[(__PORT_DEF_RIGHT >> 3) & 0x07][__PORT_DEF_RIGHT & 0x07] == ucChanle) {
        __SucUpBackMaxNum[1] = ((INT8U*)pvData)[0];
    } else if (1 == usLen){
        __SucUpBackMaxNum[2] = ((INT8U*)pvData)[0];
    } else if (usLen < 4){
        memcpy(__SucUpBackMaxNum, pvData, usLen);
    }
    return usLen;
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
