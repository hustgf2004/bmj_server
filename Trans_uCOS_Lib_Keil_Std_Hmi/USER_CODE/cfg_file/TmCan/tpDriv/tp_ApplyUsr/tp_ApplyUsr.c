/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tp_ApplyUsr.h
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
#include ".\tp_ApplyUsr_cfg.h"

    /*
     *  外部变量声明
     */
extern  INT8U   __GucBufTmp[2][__UPGRADE_PAGE_SIZE];
extern __PRO_SEVER_PARA    __SpspTmp[2];
    /*
     *  外部共享使用变量
     */

INT8U   __GucIsSrc;                                                     /*  程序源标识                  */

    /*
     *  内部使用变量
     */
//static __PRO_SEVER_PARA     __SpspApplyUsr[2]; 

//static INT32U               __SuiErr[TM_MAX_DRIVER][1];                 /*  吸程序错误代码
//                                                                         *  [0] 错误代码
//                                                                         */


static void    (*__SpsysParaGet)(INT32U*);


/*
 *  程序版本信息全局变量
 */
extern INT32U		__SuiTmp[3];

/*********************************************************************************************************
  函数声明
*********************************************************************************************************/
static INT32S __tpCreate(const TM_PORT_INFO *ptpiThis);
static INT32S __tpDel(const TM_PORT_INFO *ptpiThis);
static INT32S __tpRead(const TM_PORT_INFO *ptpiThis, INT8U ucChanle, INT16U usLen, void *pvData);
static INT32S __tpWrite (const TM_PORT_INFO *ptpiThis, INT8U ucChanle, INT16U usLen, void *pvData);
/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/
const TM_PORT_FUNC GtpfApplyUsr = {
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
    TP_APPLYUSR_INFO *pttiPortCase;                                     /*  设备信息                    */
    
    pttiPortCase = (TP_APPLYUSR_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase;
    /*
     *  具体的初始化代码
     */
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
    TP_APPLYUSR_INFO *pttiPortCase;                                     /*  设备信息                    */
    
    pttiPortCase = (TP_APPLYUSR_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase;
    /*
     *  具体的卸载代码
     */
    
    return TM_OK;    
}

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
    
    INT32U uiTmp[3];
    TP_APPLYUSR_INFO *pttiPortCase;                                     /*  设备信息                    */
    pttiPortCase = (TP_APPLYUSR_INFO *)ptpiThis;
    /*
     *  实际写的代码
     */    
    uiTmp[2] = ((INT32U *)pvData)[0];
    if (0xff == ucChanle) {                                             /*  读自身端口                  */
        ucChanle = __GucTmDrivChn[(uiTmp[2] >> 28) & 0x07][(uiTmp[2] >> 25) & 0x07];    
    }
    if ((ucChanle != __GucTmDrivChn[(__PORT_DEF_LEFT >> 3) & 0x07][__PORT_DEF_LEFT & 0x07]) && 
        (ucChanle != __GucTmDrivChn[(__PORT_DEF_RIGHT >> 3)& 0x07][__PORT_DEF_RIGHT& 0x07])) {
                                                                        /*  吸程序只限左右邻架          */
        return 0;
    }
    if (usLen < 4) {                                                    /*  长度限制                    */
        return 0;
    }
    sysSoftParaGetUsr(uiTmp);                                           /*  获取应用程序版本            */
	memcpy(pvData, uiTmp, usLen);                                       /*	将错误代码返回				*/
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
    TP_APPLYUSR_INFO   *pttiPortCase;                                   /*  设备信息                    */
    INT32U              uiTmp;
    INT32U              uiCodePar[3];
    INT8U               ucTaskOn = 0;
    //__PRO_SEVER_PARA    pspTmp;
    void    (*pfSoftParaGet)(INT32U*);
    
    pttiPortCase = (TP_APPLYUSR_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase; 
    
    /*
     *  实际写的代码
     */
    uiTmp = ((INT32U *)pvData)[0];
    tm_ntohl(uiTmp);
    
    if (0xff == ucChanle) {                                             /*  管理程序自升级              */
        ucChanle = __GucTmDrivChn[(uiTmp >> 28) & 0x07][(uiTmp >> 25) & 0x07]; 
    }
    if ((ucChanle != __GucTmDrivChn[(__PORT_DEF_LEFT >> 3) & 0x07][__PORT_DEF_LEFT & 0x07]) && 
        (ucChanle != __GucTmDrivChn[(__PORT_DEF_RIGHT>> 3) & 0x07][__PORT_DEF_RIGHT& 0x07])) {
                                                                        /*  吸程序只限左右邻架          */
        return usLen;
    }
    
    

    if (OS_TASK_RESUME_PRIO != OSTaskResume(TASK1_PRIO)) {
        ucTaskOn |= (1 << 0);
    }
    if (OS_TASK_RESUME_PRIO != OSTaskResume(TASK2_PRIO)) {
        ucTaskOn |= (1 << 1);
    }
    
    if (((ucTaskOn & (1 << 0)) && (ucChanle == __GucTmDrivChn[(__PORT_DEF_LEFT >> 3) & 0x07][__PORT_DEF_LEFT & 0x07])) ||
        ((ucTaskOn & (1 << 1)) && (ucChanle == __GucTmDrivChn[(__PORT_DEF_RIGHT>> 3) & 0x07][__PORT_DEF_RIGHT& 0x07]))){
        return usLen;    
    }
    if (__DLM_CODE_ID == (uiTmp & 0x800000FF)) {                        /*  申请下载管理程序            */
        pfSoftParaGet     = sysSoftParaGet;            
    } else if (__USR_CODE_ID == (uiTmp & 0x800000FF)){                  /*  申请控制器程序              */
        pfSoftParaGet     = sysSoftParaGetUsr;
    } else if (0 != (uiTmp & 0x80000000)) {                             /*  申请外设智能传感            */
        pfSoftParaGet     = sysSoftParaGetEx;
    } else {     
        GUI_ClearSCR();
        GUI_Printf(0, 44, 1, "申请程序不合法！");     
        return usLen; 
    }
    pfSoftParaGet(uiCodePar);                                           /*  获取本机应用程序信息        */
    
    uiCodePar[2] &= ~(1 << 24);                                         /*  默认传单架                  */
    
    if (((uiCodePar[2] & 0x800000ff) != (uiTmp & 0x800000ff)) &&        /*  所需程序未就绪              */
        (uiTmp & 0xff != __USR_CODE_ID)) {                              /*  应用程序除外                */                               
        GUI_ClearSCR();
        GUI_Printf(0, 44, 1, "  申请程序无效！");     
        return usLen;
    }
    if (ioInportLong(__EN_UPGRADE_FLAG0) == 0x12345678) {               /*  本机已启动续传任务          */                                                                               
        return usLen;
    }
    if ((~0 == uiCodePar[0]) || (~0 == uiCodePar[1]) || (0 == (uiCodePar[0] & 0xFF))) { 
                                                                        /*  原有程序无效                */
        if ((__GuiCodeInfo[codeId] & 0x800000FF) != (uiTmp & 0x800000FF)) {/*  本机升级未启动              */         
            return usLen;
        }         
        memcpy (uiCodePar, __GuiCodeInfo, 12);
        tm_htonl(uiCodePar[codeVer]);
        tm_htonl(uiCodePar[codeLen]);
        tm_htonl(uiCodePar[codeId]);
        
        //uiCodePar[2] &=  
        
        if (__GuiChanle == ucChanle) {                                  /*  吸程序通道和升级通道互斥    */  	        
            return usLen;
        }
        
        if (OS_TASK_RESUME_PRIO != OSTaskResume(TASK1_PRIO)) {          /*  续传程序棒任务已启动        */	           
            return usLen;
        }
        
        if (__DLM_CODE_ID == (uiTmp & 0x800000FF)) {                    /*  申请下载管理程序            */            
            __SpspTmp[0].pucSrcAddr = (INT8U*)__UPGRADE_CODES_SRC0;     /*  管理程序升级数据预存地址    */                
        } else if (__USR_CODE_ID == (uiTmp & 0x800000FF)){              /*  申请控制器程序              */            
            __SpspTmp[0].pucSrcAddr = (INT8U*)__UPGRADE_CODES_SRC1;     /*  应用程序升级数据预存地址    */                
        } else {                                                        /*  申请外设智能传感            */
            __SpspTmp[0].pucSrcAddr = (INT8U*)__UPGRADE_CODES_SRC3;     /*  传感器程序升级数据预存地址  */
        } 
        __SpspTmp[0].pucBufTmp  = __GucBufTmp[0];                       /*  升级数据缓存                */
        __SpspTmp[0].uiChn      = ucChanle;                             /*  升级通道                    */    
        __SpspTmp[0].uiXpoint   = 0;
        __SpspTmp[0].uiYpoint   = 24;
                  
                
        __SpspTmp[0].uiCodePar[0] = uiCodePar[0];
        __SpspTmp[0].uiCodePar[1] = uiCodePar[1];
        __SpspTmp[0].uiCodePar[2] = uiCodePar[2]; 
        __SpspTmp[0].ucIsCodePro  = 0; 
           
        GUI_RectangleFill(0, 24, 127, 63, 0);
        if (ucChanle == __GucTmDrivChn[(__PORT_DEF_LEFT >> 3) & 0x07][__PORT_DEF_LEFT & 0x07]) {
            if (__DLM_CODE_ID == (uiTmp & 0xFF)) {
                GUI_Printf(0, 24, 0, "左邻架吸管理程序");
            } else if (__USR_CODE_ID == (uiTmp & 0xFF)) {
                GUI_Printf(0, 24, 0, "左邻架吸应用程序");
            }
        } else if (ucChanle == __GucTmDrivChn[(__PORT_DEF_LEFT >> 3) & 0x07][__PORT_DEF_RIGHT & 0x07]) {
            if (__DLM_CODE_ID == (uiTmp & 0xFF)) {
                GUI_Printf(0, 24, 0, "右邻架吸管理程序");
            } else if (__USR_CODE_ID == (uiTmp & 0xFF)) {
                GUI_Printf(0, 24, 0, "右邻架吸应用程序");
            }
        } else {
            GUI_Printf(0, 24, 0, "传感器开始吸程序");
        }
        OSSchedLock();
        OSTaskCreateExt(Pro_SeverTask,
                        (void *)&__SpspTmp[0],
                        &TASK1_STACK[TASK1_STACK_SIZE-1],
                        TASK1_PRIO,
                        TASK1_ID,
                        &TASK1_STACK[0],
                        TASK1_STACK_SIZE,
                        (void *)0,
                        OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
         OSSchedUnlock();
    } else if ((__GuiCodeInfo[0] != 0x00000000) && 
               (__GuiCodeInfo[0] != 0xFFFFFFFF)) {                    /*  升级已启动                  */
        GUI_Printf(0, 24, 0, "本架升级请稍等！");     
        return usLen;         
    } else {                                                            /*  本机应用程序有效            */
        INT8U ucId = (ucChanle == __GucTmDrivChn[(__PORT_DEF_LEFT >> 3) & 0x07][__PORT_DEF_LEFT & 0x07]) ? 0 : 1;
       
        tm_htonl(uiCodePar[0]);
        tm_htonl(uiCodePar[1]);
        tm_htonl(uiCodePar[2]);
        if (__USR_CODE_ID == (uiTmp & 0x800000FF)) {
            __SpspTmp[ucId].ucIsCodePro = 3;
            __GbParaFlag = TRUE;
        } else {
            __SpspTmp[ucId].ucIsCodePro = 2;
        }
        if (ucTaskOn & 0x03) {
            ;
        } else {
            GUI_ClearSCR();
        }
        if (0 == ucId) {                                                /*  左邻架程序棒任务            */                                                                                    
            if (__DLM_CODE_ID == (uiTmp & 0xFF)) {
                GUI_Printf(0, 00, 0, "左邻架吸管理程序");
            } else if (__USR_CODE_ID == (uiTmp & 0xFF)) {
                GUI_Printf(0, 00, 0, "左邻架吸应用程序");
            }
        } else {                                                        /*  右邻架程序棒任务            */
            if (__DLM_CODE_ID == (uiTmp & 0xFF)) {
                GUI_Printf(0, 32, 0, "右邻架吸管理程序");
            } else if (__USR_CODE_ID == (uiTmp & 0xFF)) {
                GUI_Printf(0, 32, 0, "右邻架吸应用程序");
            }
        }
        __SpspTmp[ucId].pucBufTmp  = __GucBufTmp[ucId];                 /*  应用程序升级数据预存地址    */    
        __SpspTmp[ucId].uiChn      = ucChanle;   
        __SpspTmp[ucId].uiXpoint   = 0;
        __SpspTmp[ucId].uiYpoint   = 32 * ucId;
        
        __SpspTmp[ucId].uiCodePar[0] = uiCodePar[0];
        __SpspTmp[ucId].uiCodePar[1] = uiCodePar[1];
        __SpspTmp[ucId].uiCodePar[2] = uiCodePar[2];           
        
        if (__DLM_CODE_ID == (uiTmp & 0x800000FF)) {                    /*  申请下载管理程序            */
            __SpspTmp[ucId].pucSrcAddr = (INT8U*)__DLM_CODES_SRC;       /*  管理程序升级数据预存地址    */                
        } else if (__USR_CODE_ID == (uiTmp & 0x800000FF)) {             /*  申请控制器程序              */
            __SpspTmp[ucId].pucSrcAddr = (INT8U*)__UPGRADE_CODES_SRC2;  /*  应用程序升级数据预存地址    */                
        } else {                                                        /*  申请外设智能传感            */
            __SpspTmp[ucId].pucSrcAddr = (INT8U*)__UPGRADE_CODES_SRC3;  /*  传感器程序升级数据预存地址  */            
        }    
        __GucIsSrc = TRUE;
        /*
         *	启动程序棒任务
         */
        OSSchedLock();
        
        //tpUpgradeBeginDel();
        __GucUpgradeOk = 0xAA;                                
        if (0 == ucId) {
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
        OSSchedUnlock();
    }
    return usLen;
}
/*********************************************************************************************************
  DEL FILE
*********************************************************************************************************/
