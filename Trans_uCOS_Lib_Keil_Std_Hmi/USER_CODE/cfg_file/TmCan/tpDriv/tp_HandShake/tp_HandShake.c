/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tpHandShake.c
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
#include ".\tp_HandShake_cfg.h"

    /*
     *  外部共享使用变量
     */
   
    /*
     *  内部使用变量
     */
/*********************************************************************************************************
  函数声明
*********************************************************************************************************/
static INT32S __tpRead(const TM_PORT_INFO *ptpiThis, INT8U ucChanle, INT16U usLen, void *pvData);
static INT32S __tpWrite (const TM_PORT_INFO *ptpiThis, INT8U ucChanle, INT16U usLen, void *pvData);
/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/
const TM_PORT_FUNC GtpfHandShake = {
    NULL,
    NULL,
    __tpRead,
    __tpWrite
};
/*********************************************************************************************************
** Function name:           __tpRead
** Descriptions:            读端口。
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

static INT32S __tpRead (const TM_PORT_INFO *ptpiThis, INT8U ucChanle, INT16U usLen, void *pvData)
{
    TP_HANDSHAKE_INFO *pttiPortCase;                               /*  设备信息                    */
    INT32U   uiDlmCodeId[3];
    pttiPortCase = (TP_HANDSHAKE_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase;    
    sysSoftParaGet(uiDlmCodeId);
     
    /*
     *  实际的写代码
     */        
    memcpy(pvData, (INT8U*)&uiDlmCodeId, usLen); 
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
    TP_HANDSHAKE_INFO *pttiPortCase;                                    /*  设备信息                    */
    INT8U   ucKey[4] = {0xaa,0x11,0x55,0x22};                           /*  复位密钥                    */ 
     
    pttiPortCase = (TP_HANDSHAKE_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase;    
    
    /*
     *  实际的写代码
     */ 
    
    if (!memcmp(ucKey, pvData, 4)) {                                    /*  复位                        */         
        OSTaskDelReq(TASK0_PRIO);
        return usLen;
    }
     
    if ((usLen <= 8) && (ioInportLong(__EN_UPGRADE_FLAG0) != 0x87654321)) {
        memcpy((void *)__EN_UPGRADE_FLAG0, pvData, usLen);
        tpApplyUsrInit();
    }
    return usLen;
}

/*********************************************************************************************************
  DEL FILE
*********************************************************************************************************/
