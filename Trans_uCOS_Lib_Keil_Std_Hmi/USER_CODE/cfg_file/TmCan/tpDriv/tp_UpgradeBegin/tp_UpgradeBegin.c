/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tp_UpgradeBegin.c
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
#include ".\tp_UpgradeBegin_cfg.h"

    /*
     *  外部共享使用变量
     */

INT8U   __GucBufTmp[2][__UPGRADE_PAGE_SIZE];                            /*  升级传递缓冲区              */
INT8U   __GucUpgradeBuf[__UPGRADE_PAGE_SIZE];                           /*  升级缓冲区                  */

INT32U  __GuiIndex;                                                     /*  升级成功扇区号              */
INT32U  __GuiChanle;                                                    /*  升级通讯通道号记录          */

INT8U   __GucXPoint;
INT8U   __GucYPoint;
INT32U  __GuiBackupAddr;

void    (*__GpsysSoftParaGet)(INT32U*);
INT32S  (*__GpsysUpgradeBegin)(INT8U*, INT32U);
INT32S  (*__GpsysUpgradeDataWrite)(unsigned int);
INT32S  (*__GpsysUpgradeEnd)(void);   

INT8U   __GucUpgradeOk;
INT8U   __GucFlagOnce;
volatile INT8U  __GucIsCanBusUpdate;                                    /*  总线升级传感器标识          */
/*
 *  程序版本信息全局变量
 */
INT32U  __GuiCodeInfo[3];                                
    /*
     *  内部使用变量
     */
static  INT32U      __SuiErr[2];                                        /*  升级开始返回值              */
__PRO_SEVER_PARA    __SpspTmp[2];
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
const TM_PORT_FUNC GtpfUpgradeBegin = {
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
    TP_UPGRADEBEGIN_INFO *pttiPortCase;                                     /*  设备信息                    */
    
    pttiPortCase = (TP_UPGRADEBEGIN_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase;
    /*
     *  具体的初始化代码
     */    
    
    __GuiIndex      = ~0;
    __GuiChanle     = ~0;
    memset(__SuiErr, 0xFF, sizeof(__SuiErr));
    memset(__SpspTmp, 0x00, 2 * sizeof(__PRO_SEVER_PARA));
    memset(__GuiCodeInfo, 0x00, sizeof(__GuiCodeInfo));
    __GpsysSoftParaGet = NULL;
    __GpsysUpgradeBegin = NULL;
    __GpsysUpgradeDataWrite = NULL;
    __GpsysUpgradeEnd = NULL;
    
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
    TP_UPGRADEBEGIN_INFO *pttiPortCase;                                 /*  设备信息                    */
    
    pttiPortCase = (TP_UPGRADEBEGIN_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase;
    /*
     *  具体的卸载代码
     */    
    
    __GuiIndex      = ~0;
    __GuiChanle     = ~0;    
    memset(__SuiErr, 0xFF, sizeof(__SuiErr));    
    memset(__SpspTmp, 0x00, 2*sizeof(__PRO_SEVER_PARA));
    memset(__GuiCodeInfo, 0x00, sizeof(__GuiCodeInfo));
    __GpsysSoftParaGet = NULL;
    __GpsysUpgradeBegin = NULL;
    __GpsysUpgradeDataWrite = NULL;
    __GpsysUpgradeEnd = NULL;
    
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
    TP_UPGRADEBEGIN_INFO *pttiPortCase;                                 /*  设备信息                    */
    if (usLen > 8) {
        return 0;
    }
    pttiPortCase = (TP_UPGRADEBEGIN_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase;    
    
    memcpy(pvData, __SuiErr, usLen);       
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
    TP_UPGRADEBEGIN_INFO   *pttiPortCase;                               /*  设备信息                    */
    INT32U                  uiTmp;
    INT32U                  uiCodePar[3];
    INT32U                  uiCodeVer;
    INT8U                   ucNum;
    
    pttiPortCase = (TP_UPGRADEBEGIN_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase;    
    
    
    /*
     *  实际的写代码
     */        

    if (__GucIsSrc) {
        __SuiErr[0] = 0x01;
        __SuiErr[1] = __UPGRADE_PRO_BEGIN_ERR;   	                    /*  升级启动失败                */
        return usLen;
    }
    uiTmp = ((INT32U*)pvData)[2];
    tm_ntohl(uiTmp);                                                    /*  获取新程序的类别            */
    
    
    if((~0 != __GuiChanle)) {                                           /*  升级已启动                  */
        if ((ucChanle != __GuiChanle)) {                                /*  升级通道不同                */
	        __SuiErr[0] = 0x01;
	        __SuiErr[1] = __UPGRADE_PRO_BEING_ERR;   	                /*  升级程序进行中              */
	        return usLen;
	    }
	    memcpy(uiCodePar, pvData, 12);
	    tm_ntohl(uiCodePar[codeVer]);
	    tm_ntohl(uiCodePar[codeLen]);
	    tm_ntohl(uiCodePar[codeId]);
	    if ((__GuiCodeInfo[codeVer] != uiCodePar[codeVer]) ||
	        (__GuiCodeInfo[codeLen] != uiCodePar[codeLen]) ||
	        (__GuiCodeInfo[codeId] != uiCodePar[codeId] )) {             /*  升级程序不同                */   
    		__SuiErr[0] = 0x01;
        	__SuiErr[1] = __UPGRADE_PRO_BEING_ERR; 	                    /*  升级程序进行中              */	
    		return usLen;
    	}
    } else {                                                            /*  升级首次启动                */
        GUI_ClearSCR();
    }
    if (__DLM_CODE_ID == (uiTmp & 0x800000FF)) {                        /*  下载管理程序升级            */
        __GpsysSoftParaGet      = sysSoftParaGet;
        __GpsysUpgradeBegin     = sysUpgradeBegin;  
        __GpsysUpgradeDataWrite = sysUpgradeDataWrite; 
        __GpsysUpgradeEnd       = sysUpgradeEnd;   
        __SpspTmp[0].pucSrcAddr = (INT8U*)__UPGRADE_CODES_SRC0;         /*  管理程序升级数据预存地址    */
        __SpspTmp[0].pucBufTmp  = __GucBufTmp[0];
        __GuiBackupAddr = __UPGRADE_CODES_SRC0;
        __GucXPoint = 0;
        __GucYPoint = 44; 
        GUI_Printf(0, 4, 1, "下载管理程序升级"); 
        #if 0
        /*
         *  去掉断点续传功能
         */
        if ((~0 == __GuiChanle) || (__GucUpgradeOk == 0x55)) {
            sysIrqDisable(); 
            OSSchedLock();
        	sysSectorPrepare (1, 2);                                    /* 扇区准备						*/
            sysSectorErase (1, 2);	                                    /* 擦除扇区						*/      
        	OSSchedUnlock();  
            sysIrqEnable();
        }
        #endif 
    } else if (__USR_CODE_ID == (uiTmp & 0x800000FF)) {                 /*  控制器程序升级              */
        __GpsysSoftParaGet      = sysSoftParaGetUsr;
        __GpsysUpgradeBegin     = sysUpgradeBeginUsr;        
        __GpsysUpgradeDataWrite = sysUpgradeDataWriteUsr; 
        __GpsysUpgradeEnd       = sysUpgradeEndUsr;
        __SpspTmp[0].pucSrcAddr = (INT8U*)__UPGRADE_CODES_SRC1;         /*  应用程序升级数据预存地址    */
        __SpspTmp[0].pucBufTmp  = __GucBufTmp[0];
        __GuiBackupAddr = __UPGRADE_CODES_SRC1;
        __GucXPoint = 0;
        __GucYPoint = 44; 
        GUI_Printf(0, 4, 1, "  应用程序升级  "); 
        #if 0
        /*
         *  去掉断点续传功能
         */
        if ((~0 == __GuiChanle) || (__GucUpgradeOk == 0x55)) {
            sysIrqDisable(); 
            OSSchedLock();
            sysWordProgramEx(0x80100018,0x0000);
            sysWordProgramEx(0x8010001A,0x0000);
            sysWordProgramEx(0x80101018,0x0000);
            sysWordProgramEx(0x8010101A,0x0000);
         	OSSchedUnlock();  
            sysIrqEnable(); 
        }
        #endif
    } else if (0 != (uiTmp & 0x80000000)) {                             /*  外设智能传感升级            */
        __GpsysSoftParaGet      = sysSoftParaGetEx;
        __GpsysUpgradeBegin     = sysUpgradeBeginEx;        
        __GpsysUpgradeDataWrite = sysUpgradeDataWriteEx; 
        __GpsysUpgradeEnd       = sysUpgradeEndEx;
        
        __SpspTmp[0].pucSrcAddr = (INT8U*)__UPGRADE_CODES_SRC3;         /*  智能传感升级数据预存地址    */
        __SpspTmp[1].pucSrcAddr = (INT8U*)__UPGRADE_CODES_SRC3;         /*  智能传感升级数据预存地址    */
        __SpspTmp[0].pucBufTmp  = __GucBufTmp[0];
        __SpspTmp[1].pucBufTmp  = __GucBufTmp[1];

        __GuiBackupAddr = __UPGRADE_CODES_SRC3;
        __GucXPoint = 0;
        __GucYPoint = 16;
        GUI_Printf(0, 0, 1, "智能传感程序升级");
        #if 0
        /*
         *  去掉断点续传功能
         */
        if ((~0 == __GuiChanle) || (__GucUpgradeOk == 0x55)) {
            sysCodeEraseEx();  
        }
        #endif  
    } else {
        __GuiChanle = ~0;
        usLen = 0;        
        ioOutportLong(0x0, __EN_UPGRADE_FLAG0);
        ioOutportLong(0x0, __EN_UPGRADE_FLAG1);  
        OSTaskDelReq(TASK0_PRIO);
        GUI_Printf(0, 24, 1, "程序类型不合法！");     
        return usLen; 
    }
    
    __GpsysSoftParaGet(uiCodePar);                                      /*  获得当前程序参数            */
    
    uiCodePar[codeLen] = ((INT32U*)pvData)[codeLen];                    /*  获取新程序的长度            */
    tm_ntohl(uiCodePar[codeLen]);
    
    uiCodeVer = ((INT32U*)pvData)[codeVer];                             /*  获取新程序的版本信息        */
    tm_ntohl(uiCodeVer); 
   
    if (((uiCodePar[codeLen] > __USR_CODE_LEN) && (__USR_CODE_ID == (uiTmp & 0x800000FF))) ||
        ((uiCodePar[codeLen] > __DLM_CODE_LEN) && (__DLM_CODE_ID == (uiTmp & 0x800000FF))) ||
        (uiCodePar[codeLen] > __MAX_CODE_LEN)) {
        __SuiErr[0] = 0x01;
        __SuiErr[1] = __UPGRADE_PRO_TOOLONG_ERR;                        /*  新程序的长度太长            */
        __GuiChanle = ~0;
        GUI_Printf(0, 24, 1, "程序长度不合法！");
        ioOutportLong(0x0, __EN_UPGRADE_FLAG0);
        ioOutportLong(0x0, __EN_UPGRADE_FLAG1);  
        OSTaskDelReq(TASK0_PRIO);
        return usLen; 
    }
    if (((0 != (uiTmp & 0x80000000))) && ((uiTmp & 0x800000FF) != (uiCodePar[codeId] & 0x800000FF))) {                  
        sysCodeEraseEx();                                               /*  擦除参数区域                */            
        uiCodePar[codeVer]  = ~0;
        uiCodePar[codeLen]  = ~0;
        uiCodePar[codeId]   = ~0;
    } 
    
    if((~0 == uiCodePar[codeVer]) || (0 == (uiCodePar[codeVer] & 0xFF))){
        uiCodePar[codeVer] = uiCodeVer - 1;
    }
    if ((~0 == uiCodePar[codeId])) {
        uiCodePar[codeId] = uiTmp;
    }
    if ((~0 == uiCodePar[codeLen])) {
        uiCodePar[codeLen] = ((INT32U*)pvData)[codeLen];                /*  获取新程序的长度            */
        tm_ntohl(uiCodePar[codeLen]);
    }
    
#if 0                                                                   /*  去掉项目版本限制            */ 
    if ((uiCodeVer >> 8) != (uiCodePar[codeVer] >> 8)) {
        __SuiErr[0] = 0x01;
        __SuiErr[1] = __UPGRADE_PRO_NOMATCH_ERR;                        /*  新程序的项目不匹配          */
        __GuiChanle = ~0;
        GUI_Printf(0, 24, 1, "程序项目不匹配！"); 
        ioOutportLong(0x0, __EN_UPGRADE_FLAG0);
        ioOutportLong(0x0, __EN_UPGRADE_FLAG1); 
        OSTaskDelReq(TASK0_PRIO);
        return usLen; 
    } else if ((((((uiCodeVer >> 4) & 0x0F) < (((uiCodePar[codeVer] >> 4) & 0x0F) - 1))&&(0 != (uiCodePar[codeVer] & 0xF0)))) && 
               ((uiTmp & 0x800000FF) == (uiCodePar[codeId] & 0x800000FF))) {
        __SuiErr[0] = 0x01;
        __SuiErr[1] = __UPGRADE_PRO_VERLOW_ERR;                         /*  新程序的版本太低            */
        __GuiChanle = ~0;
        GUI_Printf(0, 24, 1, "发布程序版本低！");
        ioOutportLong(0x0, __EN_UPGRADE_FLAG0);
        ioOutportLong(0x0, __EN_UPGRADE_FLAG1);  
        OSTaskDelReq(TASK0_PRIO);
        return usLen; 
    }                                                               
#endif
    
    /*  
     *  新程序的信息校验通过        
     */
    memcpy(__GucUpgradeBuf, pvData, usLen);
    /*
     *  架号信息不携带
     */
    ucNum = __GucUpgradeBuf[9]; 
    __GucUpgradeBuf[9] = 0;
    
    
    /*
     *  相同版本进行全擦除
     */
    if ((__USR_CODE_ID == (uiTmp & 0x800000FF)) && ((uiCodeVer & 0xFF) == (uiCodePar[codeVer] & 0xFF))) {
    	sysIrqDisable(); 
    	OSSchedLock();
    	sysSectorEraseEx(256);
    	sysSectorEraseEx(257);
    	OSSchedUnlock(); 
    	sysIrqEnable();
    }

    
    sysIrqDisable(); 
    OSSchedLock();
    __SuiErr[1] = __GpsysUpgradeBegin(__GucUpgradeBuf, __UPGRADE_PAGE_SIZE);
    OSSchedUnlock(); 
    sysIrqEnable();
   
    if(__SuiErr[1] > -128) {
        __SuiErr[0] = 0x01;
        __SuiErr[1] = __UPGRADE_PRO_BEGIN_ERR;                          /*  升级程序启动失败            */
        __GuiChanle = ~0;
        return usLen;
    }
    
    __GucUpgradeOk  = 0;
    __GucFlagOnce   = 0;
    
    memcpy(__GuiCodeInfo, pvData, usLen);
    tm_ntohl(__GuiCodeInfo[codeVer]);
    tm_ntohl(__GuiCodeInfo[codeLen]);
    tm_ntohl(__GuiCodeInfo[codeId]);
    __SuiErr[0] = 0x00; 
    
    if (__SuiErr[1] > __GuiCodeInfo[codeLen]) {
        __GuiIndex = (0 == (__GuiCodeInfo[codeLen] % __UPGRADE_PAGE_SIZE))?\
                           (__GuiCodeInfo[codeLen] / __UPGRADE_PAGE_SIZE):\
                           ((__GuiCodeInfo[codeLen] / __UPGRADE_PAGE_SIZE) + 1);
        __SuiErr[1] = __GuiCodeInfo[codeLen];
    } else {       
        __GuiIndex = (__SuiErr[1] / __UPGRADE_PAGE_SIZE);
    }
    

    if ((~0 == __GuiChanle)) { 
        __GuiChanle = ucChanle;
        
        if ((__DLM_CODE_ID == (uiTmp & 0x800000FF)) ||
            (__USR_CODE_ID == (uiTmp & 0x800000FF))) {                  /*  控制器程序                  */
            if (0 == (uiTmp & (1 << 24))) {
                tpUpDataEndInit();
                tpUpDataInit(); 
                tpUpParaInit();                
                GUI_Printf(0, 24, 0, "  单架升级中！  ");
                return usLen; 
            } else if (ucNum == 1) {                                    /*  终点架                      */
                tpUpDataEndInit();
                tpUpDataInit();
                tpUpParaInit();
                GUI_Printf(0, 24, 0, " 本次升级末架！ ");
                return usLen;
            } else {
                ;
            }
        } else {
            if (0 == (uiTmp & (1 << 24))) {
                GUI_Printf(0, 16, 0, "  单架升级中！  ");
            } else if (ucNum == 1) {                                    /*  终点架                      */
                GUI_Printf(0, 16, 0, " 本次升级末架！ ");
            } else {
                ;
            }
        } 
    } else {                                                            /*  避免重复创建任务            */
        
        return usLen;
    }       
    if (sysUpgradeBeginEx == __GpsysUpgradeBegin) {
        if (__GuiIndex * __UPGRADE_PAGE_SIZE == uiCodePar[codeLen]) {
            GUI_Printf(0, 16, 1, "升级进度: 99%%   ");
        } else {
            GUI_Printf(0, 16, 1, "升级进度:%3d%%   ",
                       (INT8U)(((__SuiErr[1]) * 100) / uiCodePar[codeLen])); 
        }
    } else {
        if (__GuiIndex * __UPGRADE_PAGE_SIZE == uiCodePar[codeLen]) {
            GUI_Printf(0, 44, 1, "升级进度: 99%%   ");
        } else {
            GUI_Printf(0, 44, 1, "升级进度:%3d%%   ",
                       (INT8U)(((__SuiErr[1]) * 100) / uiCodePar[codeLen])); 
        }
                    
        
    }
    if ((__DLM_CODE_ID == (uiTmp & 0x800000FF)) ||
        (__USR_CODE_ID == (uiTmp & 0x800000FF))) {                      /*  控制器程序                  */
        __SpspTmp[0].uiXpoint = 0;
        __SpspTmp[0].uiYpoint = 24;                  
    
    } else {                                                            /*  智能传感器程序              */
        __SpspTmp[0].uiXpoint = 0;
        __SpspTmp[0].uiYpoint = 0;            
        __SpspTmp[1].uiXpoint = 0;
        __SpspTmp[1].uiYpoint = 32;          
    }
    __SpspTmp[0].ucIsCodePro = 0;                                       /*  程序棒任务仅用来续传        */
    __SpspTmp[1].ucIsCodePro = 0;                                       /*  程序棒任务仅用来续传        */
    
    if (__GucTmDrivChn[(__PORT_DEF_RIGHT >> 3)&0x07][__PORT_DEF_RIGHT & 0x07] == ucChanle) {
                                                                        /*  设置续传通道                */                
        __SpspTmp[0].uiChn    = __PORT_DEF_LEFT;  
    } else {
        __SpspTmp[0].uiChn    = __PORT_DEF_RIGHT;
    }
    
    if (uiTmp & (1 << 31)) {                                            /*  设置传感器转发通道          */
        __SpspTmp[1].uiChn    = (uiTmp >> 25) & 0x3F;    
        tmRemoteDriversAdd((TM_DRIVER_INFO_BASE*)__GpdiTmDrivrers[__GucTmDrivChn[(uiTmp >> 28) & 0x07][(uiTmp >> 25) & 0x07]]);
    }
    if (ucNum == 0) {                                                   /*  无限制续传                  */
        ;
    } else if (ucNum == 1) {                                            /*  终点架                      */
        ;   
    } else {                                                            /*  架数递减                    */
        ;   
    }
    
    /*
     *  传递架数
     */
    memcpy((INT8U*)(__SpspTmp[0].uiCodePar), pvData, usLen);
    memcpy((INT8U*)(__SpspTmp[1].uiCodePar), pvData, usLen);
    if (ucNum > 0) {        
        ((INT8U*)__SpspTmp[0].uiCodePar)[9] = ucNum - 1;                /*  续传架数                    */
        ((INT8U*)__SpspTmp[1].uiCodePar)[9] = 0;                        /*  本架传感器数量不限          */
    } 
    
        
    /*
     *  传控制器应用程序、DLM程序时，判断是否传单架
     */  
    if ((0 == (uiTmp & 0x80000000))) {      
        if ((__USR_CODE_ID == (uiTmp & 0x800000FF)) || 
            (__DLM_CODE_ID == (uiTmp & 0x800000FF))) {}
    } else {
        ;
    }

    OSSchedLock();
    
    tpUpDataEndDel();
    tpUpDataDel();
    tpUpParaDel(); 
    tpApplyUsrDel();                  
    if (((uiTmp & 0x800000FF) == __DLM_CODE_ID || (__USR_CODE_ID == (uiTmp & 0x800000FF)))) {
        OSTaskCreateExt(Pro_SeverTask,
            (void *)&__SpspTmp[0],
            &TASK1_STACK[TASK1_STACK_SIZE-1],
            TASK1_PRIO,
            TASK1_ID,
            &TASK1_STACK[0],
            TASK1_STACK_SIZE,
            (void *)0,
            OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR); 
    } else {
        if (0 != (uiTmp & (1 << 24))) {                                 /*  发布                        */
            OSTaskCreateExt(Pro_SeverTask,
                            (void *)&__SpspTmp[0],
                            &TASK1_STACK[TASK1_STACK_SIZE-1],
                            TASK1_PRIO,
                            TASK1_ID,
                            &TASK1_STACK[0],
                            TASK1_STACK_SIZE,
                            (void *)0,
                            OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR); 
           
        }                                                               /*  本架外设转发任务            */

        OSTaskCreateExt(Pro_SeverTask,
                        (void *)&__SpspTmp[1],
                        &TASK2_STACK[TASK2_STACK_SIZE-1],
                        TASK2_PRIO,
                        TASK2_ID,
                        &TASK2_STACK[0],
                        TASK2_STACK_SIZE,
                        (void *)0,
                        OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
    }       

    tpUpDataEndInit();
    tpUpDataInit();
    tpUpParaInit();
    OSSchedUnlock(); 
     
    return usLen;
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
