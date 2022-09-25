/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tp_UpDataEnd.c
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
#include ".\tp_UpDataEnd_cfg.h"

    /*
     *  外部共享使用变量
     */
extern INT32U  __GuiIndex;
extern INT8U   __GucUpgradeBuf[];
extern INT32U  __GuiBackupAddr;

extern void    (*__GpsysSoftParaGet)(INT32U*);
extern INT32S  (*__GpsysUpgradeBegin)(INT8U*, INT32U);
extern INT32S  (*__GpsysUpgradeDataWrite)(unsigned int);
extern INT32S  (*__GpsysUpgradeEnd)(void);   


    /*
     *  内部使用变量
     */
extern INT8U  __GucFlagOnce;     


/*********************************************************************************************************
  函数声明
*********************************************************************************************************/
static INT32S __tpWrite(const TM_PORT_INFO *ptpiThis, INT8U ucChanle, INT16U usLen, void *pvData);
static INT32S __tpCreate (const TM_PORT_INFO *ptpiThis);
/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/
const TM_PORT_FUNC GtpfUpDataEnd = {
    __tpCreate,
    NULL,
    NULL,
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
    TP_UPDATA_END_INFO *pttiPortCase;                                   /*  设备信息                    */
    
    pttiPortCase = (TP_UPDATA_END_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase;
    /*
     *  具体的初始化代码
     */
   
    
    
    return TM_OK;
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
    TP_UPDATA_END_INFO *pttiPortCase;                               /*  设备信息                    */
    INT32S                  siErr;
    MD5_CTX                 md5_check;
    //static __PARAM_STRUCT   __SpsTmp;         
    pttiPortCase = (TP_UPDATA_END_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase;    
    
    /*
     *  实际的写代码
     */        
    if ((__GuiIndex >= ((512* 1024)/__UPGRADE_PAGE_SIZE)) || (NULL == __GpsysUpgradeDataWrite) || (__GuiChanle != ucChanle) ||
        (((__GuiIndex + 1) * __UPGRADE_PAGE_SIZE) < __GuiCodeInfo[codeLen]) || (((__GuiIndex - 1) * __UPGRADE_PAGE_SIZE) >= __GuiCodeInfo[codeLen])
        ) {
        return 0;
    }
    if (0 == __GucFlagOnce) {
      	MD5Init(&md5_check);
        MD5Update(&md5_check, (INT8U*)__GuiBackupAddr, __GuiCodeInfo[codeLen] - 16);
        MD5Final(__GucUpgradeBuf, &md5_check);
        
      	memcpy(__GucUpgradeBuf + 16, (INT8U*)(__GuiBackupAddr + __GuiCodeInfo[codeLen] - 16), 16);   
        if (memcmp(__GucUpgradeBuf, __GucUpgradeBuf + 16, 16) != 0) {        	
        	
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
        	__GucUpgradeOk = 0x55;
        	GUI_Printf(__GucXPoint, __GucYPoint, 1, "校验码错误！    ");
        	__GuiIndex = 0;    	 
        	return 0x0F;
        } else {
            GUI_Printf(__GucXPoint, __GucYPoint, 1, "校验码正确！    ");
        }
        __GucUpgradeOk = 0xAA;
        __GucFlagOnce = 1;
    }    
  	if ((OS_TASK_NOT_EXIST != OSTaskDelReq(TASK1_PRIO)) || 
        (OS_TASK_NOT_EXIST != OSTaskDelReq(TASK2_PRIO))
        ) {
        return 0;
    }    
    
    sysIrqDisable();
    OSSchedLock(); 
    siErr = __GpsysUpgradeEnd(); 
    OSSchedUnlock();       
    sysIrqEnable();
    /*
     *  升级过程中程序总长度如果被擦除，升级无法结束
     *  解决办法：
     *  1、直接由管理程序做结束操作，而不再经过boot。
     *  2、管理程序重新写入有效的程序总长度值，
     *     等再次进入升级结束命令时，经过boot正常结束。
     */
    if (siErr == -COUNT_ERROR) {      
        if (__GpsysUpgradeEnd == sysUpgradeEnd) {                               /*  擦除管理程序                */
    	    if (((__PARAM_STRUCT *)__PARAM_ADDR0)->uiCodeLenRsv != __GuiCodeInfo[codeLen]) {
    	        memcpy(__GucUpgradeBuf, (void *)__PARAM_ADDR0, sizeof(__PARAM_STRUCT));
    	        
    	        ((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLen = __GuiCodeInfo[codeLen];
    	        ((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLenRsv1 = __GuiCodeInfo[codeLen];

                sysIrqDisable(); 
                OSSchedLock();
                sysSectorPrepare (1, 1);                                        /* 扇区准备						*/
                sysSectorErase (1, 1);	                                        /* 擦除扇区						*/

                sysSectorPrepare (1, 1);                                        /* 扇区准备						*/						
                sysRamToFlash(__PARAM_ADDR0,(INT32U)__GucUpgradeBuf, 512); 
                siErr = sysDataCompare(__PARAM_ADDR0,(INT32U)__GucUpgradeBuf, 512);
                
                OSSchedUnlock();
                sysIrqEnable(); 
                if (0 != siErr) {
                    return 0;
                }
            }
            if (((__PARAM_STRUCT *)__PARAM_ADDR1)->uiCodeLenRsv != __GuiCodeInfo[codeLen]) {
    	        memcpy(__GucUpgradeBuf, (void *)__PARAM_ADDR1, sizeof(__PARAM_STRUCT));
    	        
    	        ((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLen = __GuiCodeInfo[codeLen];
    	        ((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLenRsv1 = __GuiCodeInfo[codeLen];

                sysIrqDisable(); 
                OSSchedLock();
                sysSectorPrepare (2, 2);                                        /* 扇区准备						*/
                sysSectorErase (2, 2);	                                        /* 擦除扇区						*/

                sysSectorPrepare (2, 2);                                        /* 扇区准备						*/						
                sysRamToFlash(__PARAM_ADDR1,(INT32U)__GucUpgradeBuf, 512); 
                siErr = sysDataCompare(__PARAM_ADDR1,(INT32U)__GucUpgradeBuf, 512);
                OSSchedUnlock();  
                sysIrqEnable();  
                
            }
    	} else if (sysUpgradeEndUsr == __GpsysUpgradeEnd) {         /*  擦除应用程序                */
    	    if (((__PARAM_STRUCT *)__PARAM_ADDR_EX0)->uiCodeLenRsv1 != __GuiCodeInfo[codeLen]) {
    	        memcpy(__GucUpgradeBuf, (void *)__PARAM_ADDR_EX0, sizeof(__PARAM_STRUCT));
    	        
    	        ((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLen = __GuiCodeInfo[codeLen];
    	        ((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLenRsv1 = __GuiCodeInfo[codeLen];

                sysIrqDisable(); 
                OSSchedLock();
                
                sysWordProgramEx(__PARAM_ADDR_EX0 + (INT32U)(&((__PARAM_STRUCT *)0)->uiCodeLenRsv1) + 0,
                                (((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLen >> 0) & 0xFFFF);
                sysWordProgramEx(__PARAM_ADDR_EX0 + (INT32U)(&((__PARAM_STRUCT *)0)->uiCodeLenRsv1) + 2, 
                                (((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLen >> 16) & 0xFFFF);
                
                
                
                OSSchedUnlock();
                sysIrqEnable(); 
                
            }
            if (((__PARAM_STRUCT *)__PARAM_ADDR_EX1)->uiCodeLenRsv1 != __GuiCodeInfo[codeLen]) {
    	        memcpy(__GucUpgradeBuf, (void *)__PARAM_ADDR_EX1, sizeof(__PARAM_STRUCT));
    	        
    	        ((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLen = __GuiCodeInfo[codeLen];
    	        ((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLenRsv1 = __GuiCodeInfo[codeLen];

                sysIrqDisable(); 
                OSSchedLock();
                sysWordProgramEx(__PARAM_ADDR_EX1 + (INT32U)(&((__PARAM_STRUCT *)0)->uiCodeLenRsv1) + 0,
                                (((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLen >> 0) & 0xFFFF);
                sysWordProgramEx(__PARAM_ADDR_EX1 + (INT32U)(&((__PARAM_STRUCT *)0)->uiCodeLenRsv1) + 2, 
                                (((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLen >> 16) & 0xFFFF);
                OSSchedUnlock();  
                sysIrqEnable();  
                
            }   
    	} else {                                                    /*  擦除外设程序                */
            if (((__PARAM_STRUCT *)__PARAM_ADDR_EX2)->uiCodeLenRsv1 != __GuiCodeInfo[codeLen]) {
    	        memcpy(__GucUpgradeBuf, (void *)__PARAM_ADDR_EX0, sizeof(__PARAM_STRUCT));
    	        
    	        ((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLen = __GuiCodeInfo[codeLen];
    	        ((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLenRsv1 = __GuiCodeInfo[codeLen];

                sysIrqDisable(); 
                OSSchedLock();
                
                sysWordProgramEx(__PARAM_ADDR_EX2 + (INT32U)(&((__PARAM_STRUCT *)0)->uiCodeLenRsv1) + 0,
                                (((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLen >> 0) & 0xFFFF);
                sysWordProgramEx(__PARAM_ADDR_EX2 + (INT32U)(&((__PARAM_STRUCT *)0)->uiCodeLenRsv1) + 2, 
                                (((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLen >> 16) & 0xFFFF);
                OSSchedUnlock();
                sysIrqEnable(); 
               
            }
            if (((__PARAM_STRUCT *)__PARAM_ADDR_EX3)->uiCodeLenRsv1 != __GuiCodeInfo[codeLen]) {
    	        memcpy(__GucUpgradeBuf, (void *)__PARAM_ADDR_EX1, sizeof(__PARAM_STRUCT));
    	        
    	        ((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLen = __GuiCodeInfo[codeLen];
    	        ((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLenRsv1 = __GuiCodeInfo[codeLen];

                sysIrqDisable(); 
                OSSchedLock();
                sysWordProgramEx(__PARAM_ADDR_EX3 + (INT32U)(&((__PARAM_STRUCT *)0)->uiCodeLenRsv1) + 0,
                                (((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLen >> 0) & 0xFFFF);
                sysWordProgramEx(__PARAM_ADDR_EX3 + (INT32U)(&((__PARAM_STRUCT *)0)->uiCodeLenRsv1) + 2, 
                                (((__PARAM_STRUCT *)__GucUpgradeBuf)->uiCodeLen >> 16) & 0xFFFF);
                OSSchedUnlock();  
                sysIrqEnable(); 
            }   
    	}
    	return 0;  	
    } else if (siErr < 0) {
        usLen  = 0;
    } else {
        GUI_Printf(__GucXPoint, __GucYPoint, 1, "升级进度:100%%   "); 
        OSTaskDelReq(TASK0_PRIO);            
    } 
    return usLen;
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/