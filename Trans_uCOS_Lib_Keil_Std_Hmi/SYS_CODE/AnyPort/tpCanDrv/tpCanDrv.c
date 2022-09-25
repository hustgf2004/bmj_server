/****************************************Copyright (c)****************************************************
**                            Beijing TIANDI-MARCO Electro-Hydraulic Control System CO.,LTD.
**                                      
**                                 http://www.tdmarco.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tmcan_driv.c
** Latest modified Date:    2011-04-08
** Latest Version:          1.0
** Descriptions:            CAN网络底层驱动
**
**--------------------------------------------------------------------------------------------------------
** Created by:              LinEnqiang
** Created date:            2011-04-08
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
#include    "..\tpCommon.h"
#include    "main.h"
/*********************************************************************************************************
  函数声明
*********************************************************************************************************/
static INT32S __tpCanDrvCreate(TP_DRV_INFO *ptdiThis);

static INT32S __tpCanDrvDel(TP_DRV_INFO *ptdiThis);

static INT32S __tpCanDrvSend(struct tp_drv_info  *ptdiThis, struct tp_packet_head  *pData);

/*********************************************************************************************************
  外部引入声明
*********************************************************************************************************/ 
//extern const TP_DRV_INFO  *__GptdiDrvs[TP_MAX_DRIVER];


/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/
const TP_DRV_FUNC GtdfRemoteCan = {
    __TP_REMOTE_FUNC_EX,
    __tpCanDrvCreate,
    __tpCanDrvDel,
    __tpCanDrvSend
};
    /*
     *  总线驱动结构体
     */

const TP_DRV_INFO GtdiCanHMIDrvInfo = {
    {
        (TP_DRV_FUNC_BASE *)&GtdfRemoteCan,
        2,
        __TP_CAN_REMOTE_TIMEOUT
    },
    2//__TP_HMI
};

/*********************************************************************************************************
** Function name:           __tpCanDrvReceiveHook
** Descriptions:            CAN 网络驱动的中断接收函数
** input parameters:        pRsv:       保留参数
**                          canFrame:   接收到的CAN 帧
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
static void __tpCanDrvReceiveHook (void *pRsv,CANFRAME canFrame)
{       
    static INT8U        SucXor[8];
    static TP_PACKET   *Sptp[8];  
    TP_PACKET_HEAD      tpHead;

    INT32U              ulId;
    INT8U               i;
    INT8U               ucChn = ((INT8U*)pRsv)[0];
    tpHead.tpHeadBits.uiWord = canFrame.ulId;               
    tpHead.ucDatLen          = canFrame.ucDataLen; 
    ulId = canFrame.ulId; 
    tm_htonl(ulId);  
    switch (tpHead.tpHeadBits.Bits.uiFtype) {
        case TP_NBR_FLAG_CHAR:
            if (tpHead.tpHeadBits.Bits.uiRF < TP_RREAD_FLG) {
                ucChn *= 2;
            } else {
                ucChn = 2 * ucChn + 1;
            }
                
            if (0x00 == tpHead.tpHeadBits.Bits.uiSegPolo) {    /*  通讯帧无分段                */                                           
                
                SucXor[ucChn] = 0;
                SucXor[ucChn] = (SucXor[ucChn] ^ ((INT8U *)&ulId)[0] ^ ((INT8U *)&ulId)[1] ^ ((INT8U *)&ulId)[2] ^ ((INT8U *)&ulId)[3]);
                SucXor[ucChn] ^= tpHead.ucDatLen;
                for (i = 0; i < canFrame.ucDataLen - 1; i++) {
                    SucXor[ucChn] ^= canFrame.ucBuf[i];
                }
                if (SucXor[ucChn] != canFrame.ucBuf[i]) {
                    tpHead.ucDatLen = 2;
                    ulId = 1;
                    if (tpHead.tpHeadBits.Bits.uiRF < TP_NREAD_FLG) {
                        tpHead.tpHeadBits.Bits.uiRF += TP_RFREAD_FLG;
                        tpHead.tpHeadBits.Bits.uiSegPolo = 0x03;
                        canFrame.ucBuf[0] = SYS_PACKET_ERR;
                    } else {
                        return;
                    }
                } else if (TP_READ_FLG == tpHead.tpHeadBits.Bits.uiRF) {
                    ulId = (canFrame.ucBuf[0] << 8) | canFrame.ucBuf[1];
                } else {
                    ulId = tpHead.ucDatLen - 1;
                }
                if (NULL != Sptp[ucChn]) {
                     sysHeapFree(Sptp[ucChn]);
                }                  
                Sptp[ucChn] = (TP_PACKET*)sysHeapMalloc(sizeof(TP_PACKET) + ulId + 1);
                if (NULL != Sptp[ucChn]) {
                    memset(Sptp[ucChn], 0, (sizeof(TP_PACKET) + ulId));
                    Sptp[ucChn]->tpHead     = tpHead;
                    Sptp[ucChn]->usDatLen   = ulId;
                    Sptp[ucChn]->ucChnl     = ucChn / 2;  
                    Sptp[ucChn]->pucDat     = ((INT8U*)Sptp[ucChn]) + sizeof(TP_PACKET);   
                    memcpy(Sptp[ucChn]->pucDat, &canFrame.ucBuf[0], tpHead.ucDatLen - 1); 
                    
                                                                        /*  帧处理                      */              
                    tpRemotePacketReceive((TP_DRV_INFO_BASE*)__GptdiDrvs[Sptp[ucChn]->ucChnl], 
                                          (TP_PACKET_HEAD*)Sptp[ucChn]); 
                    Sptp[ucChn] = NULL;             
                }
            } else {                                                    /*  通讯帧有分段                */   
                
                if (0x01 == tpHead.tpHeadBits.Bits.uiSegPolo) {
                    if (NULL != Sptp[ucChn]) {
                        sysHeapFree(Sptp[ucChn]);  
                        Sptp[ucChn] = NULL; 
                    }
                    Sptp[ucChn] = (TP_PACKET*)sysHeapMalloc(sizeof(TP_PACKET) + 
                                                          (8 * (tpHead.tpHeadBits.Bits.uiSegNum + 1)));
                    if (NULL != Sptp[ucChn]) {
                        memset(Sptp[ucChn], 0, (sizeof(TP_PACKET) + 
                                                          (8 * (tpHead.tpHeadBits.Bits.uiSegNum + 1))));
                        Sptp[ucChn]->usDatLen = 0;
                        Sptp[ucChn]->pucDat   = ((INT8U*)Sptp[ucChn]) + sizeof(TP_PACKET);
                        SucXor[ucChn] = 0; 
                    }
                } 
                if (NULL == Sptp[ucChn]) {
                    break;                       
                }
                SucXor[ucChn] = (SucXor[ucChn] ^ ((INT8U *)&ulId)[0] ^ ((INT8U *)&ulId)[1] ^ ((INT8U *)&ulId)[2] ^ ((INT8U *)&ulId)[3]);
                SucXor[ucChn] ^= tpHead.ucDatLen;

                memcpy((Sptp[ucChn]->pucDat + Sptp[ucChn]->usDatLen), 
                       &canFrame.ucBuf[0], 
                       tpHead.ucDatLen);   

                Sptp[ucChn]->usDatLen += tpHead.ucDatLen;
                if (0x03 == tpHead.tpHeadBits.Bits.uiSegPolo){                            
                    for (i = 0; i < canFrame.ucDataLen - 1; i++) {
                        SucXor[ucChn] ^= canFrame.ucBuf[i];
                    } 
                    if (SucXor[ucChn] != canFrame.ucBuf[i]) {
                        if (tpHead.tpHeadBits.Bits.uiRF < TP_NREAD_FLG) {
                            tpHead.tpHeadBits.Bits.uiRF += TP_RFREAD_FLG;
                            tpHead.tpHeadBits.Bits.uiSegPolo = 0x03;
                            Sptp[ucChn]->pucDat[0] = SYS_PACKET_ERR;
                            Sptp[ucChn]->usDatLen = 2;
                        } else {
                            sysHeapFree(Sptp[ucChn]);  
                            Sptp[ucChn] = NULL;
                            return;
                        }
                    }     
                    Sptp[ucChn]->usDatLen  -= 1;
                    Sptp[ucChn]->tpHead     = tpHead;        /*  帧处理                      */
                    Sptp[ucChn]->ucChnl     = ucChn / 2;                    
                    tpRemotePacketReceive((TP_DRV_INFO_BASE*)__GptdiDrvs[Sptp[ucChn]->ucChnl], 
                                          (TP_PACKET_HEAD*)Sptp[ucChn]);
                    Sptp[ucChn] = NULL; 
                    break;                   
                }
                for (i = 0; i < canFrame.ucDataLen; i++) {
                    SucXor[ucChn] ^= canFrame.ucBuf[i];
                }            
            }
            break;
        default :  
            break;
    }
}
/*********************************************************************************************************
** Function name:           __tpCanDrvCreate
** Descriptions:            CAN 网络驱动初始化函数
** input parameters:        ptdiThis: 驱动信息
** output parameters:       none
** Returned value:          SYS_OK:  成功
**                          负数:    错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __tpCanDrvCreate (TP_DRV_INFO *ptdiThis)
{  
    char  ucCanArg[] = "BaudRate=33300 Mode=1";// Fpclk=11059200";
    CAN_HOOKS canHooks;
    
    if (ptdiThis == NULL) {
        return -SYS_PARA_ERR;
    }    
    canHooks.pReceive =  __tpCanDrvReceiveHook;
    if (canInit(ptdiThis->ucId, ucCanArg, &canHooks) < 0) {           /* CAN控制器初始化             */
        return -SYS_NOT_OK;
    }
    if( CAN3 == ptdiThis->ucId) {
        vicDefIrqFuncSet((INT32U)CAN_ISR);                              /* 设置中断服务函数             */
        //vicDefIrqEnable(19);    
    }
    vicDefIrqEnable(20 + ptdiThis->ucId);
    vicDefIrqEnable(26 + ptdiThis->ucId);   
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           __tmCanDrivDel
** Descriptions:            CAN 网络驱动删除函数
** input parameters:        ptdiThis: 驱动信息
** output parameters:       none
** Returned value:          TM_OK:   成功
**                          负数:    错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __tpCanDrvDel (TP_DRV_INFO *ptdiThis)
{
    return SYS_OK;
}
/*********************************************************************************************************
** Function name:           __tpCanDrvSend
** Descriptions:            CAN 网络驱动发送函数
** input parameters:        ptdiThis: 驱动信息
**                          pData：  数据帧 
** output parameters:       none
** Returned value:          >=0 :     读写的数据字节数目
**                          负数:     错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __tpCanDrvSend (TP_DRV_INFO *pdiThis, TP_PACKET_HEAD *ptph)
{
    TP_PACKET   *ptpBrd;
    CANFRAME     canFrame;
    INT8U        ucSegNum;
    INT8U        ucLastNum;
    INT8U        ucXor;
    INT8U        i;
    INT32U       j;
    __HEADBITS   headbits;
    INT32U       ulId;
    INT8U        ucTryNum;
    if (pdiThis == NULL) {
        return -SYS_PARA_ERR;
    }
    if (ptph == NULL) {
        return -SYS_PARA_ERR;
    }
    ptpBrd      = (TP_PACKET*)ptph;
    
    ucSegNum    = ptpBrd->usDatLen / 8;
    ucLastNum   = ptpBrd->usDatLen % 8;
    
    canFrame.ucIsRemote = FALSE;
    canFrame.ucIsExtend = TRUE;
    canFrame.ucDataLen  = 8;
    ucXor = 0;
    for(i = 0; i < ucSegNum; i++) {        
        headbits.uiWord = ptph->tpHeadBits.uiWord;        
        if(0 == i) {
            headbits.Bits.uiSegPolo = 0x01;
        } else {
            headbits.Bits.uiSegPolo = 0x02;
        }
        headbits.Bits.uiSegNum = (ucSegNum - i);
        
        canFrame.ulId = headbits.uiWord;
        ulId = canFrame.ulId;
        tm_htonl(ulId);    
        ucXor = (ucXor ^ ((INT8U *)&ulId)[0] ^ ((INT8U *)&ulId)[1] ^ ((INT8U *)&ulId)[2] ^ ((INT8U *)&ulId)[3]);
        ucXor ^= canFrame.ucDataLen;
        
        memcpy(canFrame.ucBuf, ((ptpBrd->pucDat) + 8 * i), 8);        
        ucTryNum = 0;
        while (0 == canWrite (pdiThis->ucId, &canFrame, 1)) {
            if (++ucTryNum > 1) {
                return -SYS_FIND_NO_DEVICE; 
            }    
            OSTimeDly(1);
        }         
        for (j = 0; j < 8; j++) {
            ucXor ^= canFrame.ucBuf[j];
        }        
    }
    headbits.uiWord = ptph->tpHeadBits.uiWord;  
    if(0 == i) {
        headbits.Bits.uiSegPolo = 0x00;
    } else {
        headbits.Bits.uiSegPolo = 0x03;
    }
    ptpBrd->tpHead.tpHeadBits.Bits.uiSegNum = 0x00;    
    canFrame.ulId = headbits.uiWord;
    canFrame.ucDataLen = ucLastNum + 1;
    
    ulId = canFrame.ulId;
    tm_htonl(ulId);    
    
	ucXor = (ucXor ^ ((INT8U *)&ulId)[0] ^ ((INT8U *)&ulId)[1] ^ ((INT8U *)&ulId)[2] ^ ((INT8U *)&ulId)[3]);                 
    ucXor ^= canFrame.ucDataLen;
    if (ucLastNum > 0) { 
        memcpy(canFrame.ucBuf, ((ptpBrd->pucDat) + 8 * i), ucLastNum);
    }
    for (j = 0; j < canFrame.ucDataLen - 1; j++) {
        ucXor ^= canFrame.ucBuf[j];
    }
    canFrame.ucBuf[j] = ucXor;
    ucTryNum = 0;
    while (0 == canWrite (pdiThis->ucId, &canFrame, 1)) {
        if (++ucTryNum > 1) {
            return -SYS_FIND_NO_DEVICE; 
        }    
        OSTimeDly(1);
    }         
    return ptpBrd->usDatLen;
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
