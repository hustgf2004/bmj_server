/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tp_UpData.c
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
#include ".\tp_UpData_cfg.h"

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
     
/*********************************************************************************************************
  函数声明
*********************************************************************************************************/
static INT32S __tpWrite(const TM_PORT_INFO *ptpiThis, INT8U ucChanle, INT16U usLen, void *pvData);

/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/
const TM_PORT_FUNC GtpfUpData = {
    NULL,
    NULL,
    NULL,
    __tpWrite
};

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
    TP_UPDATA_INFO *pttiPortCase;                                   /*  设备信息                    */
    INT32S  siErr;
    INT32U	uiTmp;
     
    pttiPortCase = (TP_UPDATA_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase;    
    
    /*
     *  实际的写代码
     */        
    if (((__GuiIndex * __UPGRADE_PAGE_SIZE) >= __GuiCodeInfo[codeLen]) || (NULL == __GpsysUpgradeDataWrite) || (__GuiChanle != ucChanle)) {
        return 0;
    }
    
    memcpy(__GucUpgradeBuf, pvData, usLen);
    
    sysIrqDisable(); 
    OSSchedLock(); 
    siErr = __GpsysUpgradeDataWrite(__GuiIndex);
    OSSchedUnlock();       
    sysIrqEnable();
     
    if (siErr < 0) {
        usLen  = 0;
    } else {
        __GuiIndex ++;
        if ((__GucXPoint < 128) && (__GucYPoint < 64)) {
            if ((__GuiIndex * __UPGRADE_PAGE_SIZE) >= __GuiCodeInfo[codeLen]) {
                GUI_Printf(__GucXPoint, __GucYPoint, 1, "升级进度: 99%%   ");
            } else {
                GUI_Printf(__GucXPoint, __GucYPoint, 1, "升级进度:%3d%%   ",
                           (INT8U)((__GuiIndex * __UPGRADE_PAGE_SIZE * 100) / __GuiCodeInfo[codeLen])); 
            }
        }
    } 
    return usLen;
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
