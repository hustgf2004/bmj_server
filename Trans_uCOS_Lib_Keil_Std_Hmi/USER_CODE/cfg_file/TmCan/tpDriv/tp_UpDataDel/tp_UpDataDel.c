/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tp_UpDataDel.c
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
#include ".\tp_UpDataDel_cfg.h"

    /*
     *  外部共享使用变量
     */
   
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
const TM_PORT_FUNC GtpfUpDataDel = {
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
    TP_UPDATA_DEL_INFO *pttiPortCase;                               /*  设备信息                    */
    INT8U   ucChn;
    INT8U   ucData[4] = {0xaa,0x11,0x55,0x22}; 
    pttiPortCase = (TP_UPDATA_DEL_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase;    
    
    /*
     *  实际的写代码
     */        
    
    if (__GucTmDrivChn[(__PORT_DEF_RIGHT >> 3) & 0x07][__PORT_DEF_RIGHT & 0x07] == ucChanle) {                                 /*  设置转发通道                */                
        ucChn = __GucTmDrivChn[(__PORT_DEF_LEFT >> 3) & 0x07][__PORT_DEF_LEFT & 0x07]; 
    } else {
        ucChn = __GucTmDrivChn[(__PORT_DEF_RIGHT >> 3) & 0x07][__PORT_DEF_RIGHT & 0x07];
    }          
    if (memcmp(ucData, pvData, 4) == 0) {        
        sysCodeEraseUsr();        
        OSTaskDelReq(TASK0_PRIO);  
        return (tmWrite(ucChn, 0x02, 4, ucData, 1));         
    } else {
        if (__GpsysUpgradeEnd == sysUpgradeEnd) {                   /*  擦除管理程序                */
    	    sysIrqDisable(); 
            OSSchedLock();
        	sysSectorPrepare (1, 2);                                /*  扇区准备					*/
            sysSectorErase (1, 2);	                                /*  擦除扇区					*/      
        	OSSchedUnlock();  
            sysIrqEnable(); 
    	} else if (sysUpgradeEndUsr == __GpsysUpgradeEnd) {         /*  擦除应用程序                */
    	    sysIrqDisable(); 
            OSSchedLock();
            sysWordProgramEx(0x80100018,0x0000);
            sysWordProgramEx(0x8010001A,0x0000);
            sysWordProgramEx(0x80101018,0x0000);
            sysWordProgramEx(0x8010101A,0x0000);
         	OSSchedUnlock();  
            sysIrqEnable(); 
    	} else {                                                    /*  擦除外设程序                */
    	    sysIrqDisable(); 
            OSSchedLock();
            sysCodeEraseEx();
         	OSSchedUnlock();  
            sysIrqEnable();    
    	
    	}
        // 显示"校验失败，请重新升级"
        __GucUpgradeOk = 0x55;
        GUI_Printf(__GucXPoint, __GucYPoint, 1, "升级失败,请重启!");
        return usLen;
    }
    return usLen;
}

/*********************************************************************************************************
  DEL FILE
*********************************************************************************************************/
