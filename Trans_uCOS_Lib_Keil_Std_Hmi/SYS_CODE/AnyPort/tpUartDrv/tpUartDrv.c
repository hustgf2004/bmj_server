/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn                                    
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tpUartDrv.c
** Latest modified Date:    2019-01-24
** Latest Version:          1.0
** Descriptions:            UART网络底层驱动
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2019-01-24
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
#include    "main.h"

#include    "..\tpCommon.h"



/*********************************************************************************************************
  特殊字符定义
*********************************************************************************************************/
#define PACKET_START_CHAR               0xFE
#define PACKET_DLE_CHAR                 0xFD
#define PACKET_DLE_XOR_CHAR             0x42

/*********************************************************************************************************
  函数声明
*********************************************************************************************************/
static INT32S __tpUartDrvCreate(TP_DRV_INFO *ptdiThis);

static INT32S __tpUartDrvDel(TP_DRV_INFO *ptdiThis);

static INT32S __tpUartDrvSend(struct tp_drv_info  *ptdiThis,  struct tp_packet_head *pData);

/*********************************************************************************************************
  外部引入声明
*********************************************************************************************************/ 
extern  TP_DRV_INFO  * const __GptdiDrvs[TP_MAX_DRIVER];
extern void UART0_ISR (void);


/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/
const TP_DRV_FUNC GtdfRemoteUart = {
    __TP_REMOTE_FUNC,
    __tpUartDrvCreate,
    __tpUartDrvDel,
    __tpUartDrvSend
};



/*********************************************************************************************************
** Function name:           __tpUartDrvReceiveHook
** Descriptions:            UART 网络驱动的中断接收函数
** input parameters:        pRsv:               保留参数
**                          ucRbr:              接收到的UART数据
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
static void __tpUartDrivReceiveHook (void *pRsv, INT8U ucRbr, INT8U ucLsr)
{       
    static __SERIAL_FRAME_DEL SsfdPacket[2] = {{0, NULL, 0, 0, 0, 0},{0, NULL, 0, 0, 0, 0}};

    TP_PACKET_HEAD      tpHead;
    INT8U               ucChnl;
    static INT8U      __SucIndex;    
    static INT8U      __SucBuf[8];     
    static INT8U      __SucHandshakeIndex;    
    static INT32U       GuiUpdateTick;
    static INT8U        GucIsUpdating;
    ucLsr = ucLsr;
   
    switch (((INT32U*)pRsv)[0]) {                                       /*  获取驱动通道号              */
        case 0x40011000:
            ucChnl = 0x00;
            break;
        case 0x40004400:
            ucChnl = 0x01;
            break;
        
        case 0x40004800:
            ucChnl = 0x02;
        break;
        case 0x40004C00:
            ucChnl = 0x03;
        break;
        case 0x40005000:
            ucChnl = 0x04;
        break;
        case 0x40011400:
            ucChnl = 0x05;
        break;
        case 0x40007800:
            ucChnl = 0x06;
        break;
        default:
            return;
            break;
    }
    if (GucIsUpdating) {                                               /*  已启动升级                  */        
        if (MS_TIMER - GuiUpdateTick >= 60000) {
            GucIsUpdating = FALSE;
        }
    }
        
    /*
     *  2021.05.03添加
     *  增升级加握手帧的处理
     */
    switch (__SucHandshakeIndex) {
        case    0x00:
            if (0x20 == ucRbr) {
                __SucHandshakeIndex++;
            }
            break;
        case    0x01:
            if (0x06 == ucRbr) {
                __SucHandshakeIndex++;
            } else {
                __SucHandshakeIndex = 0;
                if (0x20 == ucRbr) {
                    __SucHandshakeIndex++;
                }                
            }
            break;
        case    0x02:
            if (0x00 == ucRbr) {
                __SucHandshakeIndex++;
            } else {
                __SucHandshakeIndex = 0;
                if (0x20 == ucRbr) {
                    __SucHandshakeIndex++;
                }
            }
            break;
        case    0x03:
            if (0x00 == ucRbr) {
                __SucHandshakeIndex++;
            } else {
                __SucHandshakeIndex = 0;
                if (0x20 == ucRbr) {
                    __SucHandshakeIndex++;
                }
            }
            break;
        case    0x04:            
        case    0x05:            
        case    0x06:
            if ((0x55 == ucRbr) || (0xaa == ucRbr)) {
                __SucHandshakeIndex++;
            } else {
                __SucHandshakeIndex = 0;
                if (0x20 == ucRbr) {
                    __SucHandshakeIndex++;
                }
            }
            break;
        case    0x07:
            if ((0x55 == ucRbr) || (0xaa == ucRbr)) {                
                GucIsUpdating = TRUE;
                GuiUpdateTick = MS_TIMER;
            } else {
                __SucHandshakeIndex = 0;
                if (0x20 == ucRbr) {
                    __SucHandshakeIndex++;
                }
            }
            break;
        default:
            break;
    }
    

    if (!GucIsUpdating) {
    /*
     * 以下是应用程序正常处理
     *
     */
    switch (__SucIndex) {
        case    0x00:                                                   /*  帧头                        */
            if (0x5a == ucRbr) {                        
                __SucBuf[__SucIndex] = ucRbr;
                __SucIndex++;
            }
            break;
        case    0x01:                                                   /*  命令码                      */
            __SucBuf[__SucIndex] = ucRbr;
            __SucIndex++;
            break;
        
        default:
            __SucBuf[__SucIndex] = ucRbr;
            __SucIndex++;
            if (__SucIndex >= 8) {                                      /*  完成指令接收                 */
                INT16U usCrcChk;
                usCrcChk = CRC16_X25(__SucBuf, 6);
                if (usCrcChk == ((__SucBuf[__SucIndex - 1] << 0) | (__SucBuf[__SucIndex - 2] << 8))) {
                    //memcpy(GucDat, __SucBuf, __SucIndex);
                    //GucTaskFlag |= 0x01;                                /*  主控命令处理任务            */
                    sysMsgPost(GulKeyMsg, __SucBuf, 0);
                }
                __SucIndex = 0;
            }
            break;
    }
    } else {
    
    
    if (ucRbr == PACKET_START_CHAR) {                                   /*  接收到帧起始字符            */
        if ((SsfdPacket[ucChnl].ptpPacket != NULL)) {
            if(((0 != (SsfdPacket[ucChnl].usLen                                                              % 
                      ((SsfdPacket[ucChnl].ptpPacket->tpHead.ucDatLen * (SsfdPacket[ucChnl].usLenTmep / 6))  + 
                       SsfdPacket[ucChnl].usLenTmep)))                                                           && 
                (SsfdPacket[ucChnl].ptpPacket->tpHead.tpHeadBits.Bits.uiSegPolo < 0x03))                          ||
               (SsfdPacket[ucChnl].ptpPacket->tpHead.tpHeadBits.Bits.uiSegPolo == 0x03)) {
               
                sysHeapFree(SsfdPacket[ucChnl].ptpPacket);
                SsfdPacket[ucChnl].ptpPacket = NULL; 
                
                SsfdPacket[ucChnl].ucXor     = 0;
                SsfdPacket[ucChnl].usLen     = 1;
                SsfdPacket[ucChnl].usLenTmep = 1;  
            } else {
                SsfdPacket[ucChnl].usLenTmep ++;
                SsfdPacket[ucChnl].usLen ++;
            }
           
        } else {
            SsfdPacket[ucChnl].ucXor     = 0;
            SsfdPacket[ucChnl].usLen     = 1;
            SsfdPacket[ucChnl].usLenTmep = 1;  
        }  
        SsfdPacket[ucChnl].ulId      = 0;      
        return;
    }

    if (ucRbr == PACKET_DLE_CHAR) {                                     /*  接收到转义字符              */
        SsfdPacket[ucChnl].ucState = PACKET_DLE_XOR_CHAR;        
        return;
    }
    
    ucRbr = (INT8U)(ucRbr ^ SsfdPacket[ucChnl].ucState);                 /*  真正的字符                  */
    SsfdPacket[ucChnl].ucState = 0;
    
    switch (SsfdPacket[ucChnl].usLenTmep % 6) {    
        case 0:
            if (SsfdPacket[ucChnl].usLenTmep != 0) {
                tpHead.tpHeadBits.uiWord  = SsfdPacket[ucChnl].ulId; 
                break;
            }
            return;
        case 1:    
            SsfdPacket[ucChnl].ulId      |= ucRbr << 24;
            SsfdPacket[ucChnl].ucXor     ^= ucRbr;
            
            SsfdPacket[ucChnl].usLen++;
            SsfdPacket[ucChnl].usLenTmep++;
            return;
        case 2:
            SsfdPacket[ucChnl].ulId      |= ucRbr << 16;
            SsfdPacket[ucChnl].ucXor     ^= ucRbr;
            
            SsfdPacket[ucChnl].usLen++;
            SsfdPacket[ucChnl].usLenTmep++;
            return;
        case 3:
            SsfdPacket[ucChnl].ulId      |= ucRbr << 8;
            SsfdPacket[ucChnl].ucXor     ^= ucRbr;
            
            SsfdPacket[ucChnl].usLen++;
            SsfdPacket[ucChnl].usLenTmep++;            
            return;
        case 4:    
            SsfdPacket[ucChnl].ulId      |= ucRbr;
            SsfdPacket[ucChnl].ucXor     ^= ucRbr;
            
            tpHead.tpHeadBits.uiWord  = SsfdPacket[ucChnl].ulId;  
            if (TP_FLAG_CHAR != tpHead.tpHeadBits.Bits.uiFtype) {
                if ((SsfdPacket[ucChnl].ptpPacket != NULL)) {
                    sysHeapFree(SsfdPacket[ucChnl].ptpPacket);
                    SsfdPacket[ucChnl].ptpPacket = NULL;
                }
                SsfdPacket[ucChnl].ulId      = 0;
                SsfdPacket[ucChnl].ucXor     = 0;
                SsfdPacket[ucChnl].usLen     = 0;
                SsfdPacket[ucChnl].usLenTmep = 0;  
                return;
            }    
            
            SsfdPacket[ucChnl].usLen++;
            SsfdPacket[ucChnl].usLenTmep++;
            return;
        case 5:
            tpHead.tpHeadBits.uiWord  = SsfdPacket[ucChnl].ulId;  
            tpHead.ucDatLen  = ucRbr;
            SsfdPacket[ucChnl].ucXor ^= ucRbr;
            SsfdPacket[ucChnl].ulId = tpHead.tpHeadBits.uiWord;
            
            if (TP_READ_FLG != tpHead.tpHeadBits.Bits.uiRF) {
                if (0x00 == tpHead.tpHeadBits.Bits.uiSegPolo) {/*  通讯帧无分段                */                    
                    if (1 == ucRbr) {
                        SsfdPacket[ucChnl].ulId      = 0;
                        SsfdPacket[ucChnl].ucXor     = 0;
                        SsfdPacket[ucChnl].usLen     = 0;
                        SsfdPacket[ucChnl].usLenTmep = 0;  
                        return;
                    }
                    SsfdPacket[ucChnl].ptpPacket = (TP_PACKET*)sysHeapMalloc(sizeof(TP_PACKET) + ucRbr);
                    if (NULL != SsfdPacket[ucChnl].ptpPacket) {
                        memset(SsfdPacket[ucChnl].ptpPacket, 0, (sizeof(TP_PACKET) + ucRbr));
                        SsfdPacket[ucChnl].ptpPacket->usDatLen = 0;
                    }
                } else if (0x01 == 
                           tpHead.tpHeadBits.Bits.uiSegPolo) { /*  通讯帧有分段                */ 
                    
                    SsfdPacket[ucChnl].ptpPacket = (TP_PACKET*)sysHeapMalloc(sizeof(TP_PACKET) + 
                                                   (ucRbr * (tpHead.tpHeadBits.Bits.uiSegNum + 1)));
                    if (NULL != SsfdPacket[ucChnl].ptpPacket) {
                        memset(SsfdPacket[ucChnl].ptpPacket, 0, (sizeof(TP_PACKET) + 
                                                   (ucRbr * (tpHead.tpHeadBits.Bits.uiSegNum + 1))));
                         
                    }
                    SsfdPacket[ucChnl].ptpPacket->usDatLen = 0;
                }
                if (NULL == SsfdPacket[ucChnl].ptpPacket) {
                    SsfdPacket[ucChnl].ulId      = 0;
                    SsfdPacket[ucChnl].ucXor     = 0;
                    SsfdPacket[ucChnl].usLen     = 0;
                    SsfdPacket[ucChnl].usLenTmep = 0;  
                    return;
                } else {                    
                    SsfdPacket[ucChnl].ptpPacket->tpHead    = tpHead;
                    SsfdPacket[ucChnl].ptpPacket->ucChnl    = ucChnl + __UART_CHNL_BASE;  
                    SsfdPacket[ucChnl].ptpPacket->pucDat    = ((INT8U*)(SsfdPacket[ucChnl].ptpPacket)) + sizeof(TP_PACKET);   
                }
                SsfdPacket[ucChnl].usLen++;
                SsfdPacket[ucChnl].usLenTmep++;
                if (0x03 == tpHead.tpHeadBits.Bits.uiSegPolo) { /*  通讯帧有分段                */ 
                    SsfdPacket[ucChnl].usLen = SsfdPacket[ucChnl].usLen - SsfdPacket[ucChnl].usLenTmep +\
                                              SsfdPacket[ucChnl].ptpPacket->tpHead.ucDatLen;

                }    
            } else {
                SsfdPacket[ucChnl].usLen++;
                SsfdPacket[ucChnl].usLenTmep++;
            }
            return;
        default:            
            break;
    }
    if (TP_READ_FLG == (tpHead.tpHeadBits.Bits.uiRF)) {        
        if (6 == SsfdPacket[ucChnl].usLen) {
            SsfdPacket[ucChnl].usBufLenRd    = 0;
            SsfdPacket[ucChnl].usBufLenRd    |= (ucRbr << 0x08);
            SsfdPacket[ucChnl].ucXor         ^= ucRbr;
            SsfdPacket[ucChnl].usLen++;
        } else if (7 == SsfdPacket[ucChnl].usLen) {
            SsfdPacket[ucChnl].usBufLenRd    |= (ucRbr << 0x00);
            SsfdPacket[ucChnl].ucXor         ^= ucRbr;
            SsfdPacket[ucChnl].usLen++;
        } else {
            if (SsfdPacket[ucChnl].ucXor != ucRbr){
                ucRbr = SYS_PACKET_ERR;
                SsfdPacket[ucChnl].usBufLenRd = 1;
                tpHead.tpHeadBits.Bits.uiRF += TP_RFREAD_FLG;
                tpHead.tpHeadBits.Bits.uiSegPolo = 0x03;
            }
            if (NULL != SsfdPacket[ucChnl].ptpPacket) {
                sysHeapFree(SsfdPacket[ucChnl].ptpPacket);
                SsfdPacket[ucChnl].ptpPacket = NULL;
            }
            SsfdPacket[ucChnl].ptpPacket = (TP_PACKET*)sysHeapMalloc(sizeof(TP_PACKET) + SsfdPacket[ucChnl].usBufLenRd);
            if (NULL != SsfdPacket[ucChnl].ptpPacket) {
                memset(SsfdPacket[ucChnl].ptpPacket, 0, (sizeof(TP_PACKET) + SsfdPacket[ucChnl].usBufLenRd));
                SsfdPacket[ucChnl].ptpPacket->usDatLen =  SsfdPacket[ucChnl].usBufLenRd;
                SsfdPacket[ucChnl].ptpPacket->tpHead    = tpHead;
                SsfdPacket[ucChnl].ptpPacket->ucChnl    = ucChnl + __UART_CHNL_BASE;   
                SsfdPacket[ucChnl].ptpPacket->pucDat    = ((INT8U*)(SsfdPacket[ucChnl].ptpPacket)) + sizeof(TP_PACKET);   
                SsfdPacket[ucChnl].ptpPacket->pucDat[0] = ucRbr;
                
                tpRemotePacketReceive((TP_DRV_INFO_BASE*)__GptdiDrvs[SsfdPacket[ucChnl].ptpPacket->ucChnl], 
                                          (TP_PACKET_HEAD*)SsfdPacket[ucChnl].ptpPacket); 
                SsfdPacket[ucChnl].ptpPacket = NULL;   
                SsfdPacket[ucChnl].ulId      = 0;
                SsfdPacket[ucChnl].ucXor     = 0;
                SsfdPacket[ucChnl].usLen     = 0;
                SsfdPacket[ucChnl].usLenTmep = 0;  
            }
            return;
        }        
    } else {
        if (0x00 == (SsfdPacket[ucChnl].ptpPacket->tpHead.tpHeadBits.Bits.uiSegPolo)) {/*  通讯帧无分段                */ 
            if (SsfdPacket[ucChnl].ptpPacket->usDatLen < (SsfdPacket[ucChnl].ptpPacket->tpHead.ucDatLen - 1)) {
                SsfdPacket[ucChnl].ptpPacket->pucDat[SsfdPacket[ucChnl].ptpPacket->usDatLen++] = ucRbr;
                SsfdPacket[ucChnl].usLen++;   
                SsfdPacket[ucChnl].ucXor ^= ucRbr; 
            } else {
                if (SsfdPacket[ucChnl].ucXor != ucRbr) {
                    if ((SsfdPacket[ucChnl].ptpPacket->tpHead.tpHeadBits.Bits.uiRF < TP_NREAD_FLG)) {
                        SsfdPacket[ucChnl].ptpPacket->tpHead.tpHeadBits.Bits.uiRF += TP_RFREAD_FLG;
                        SsfdPacket[ucChnl].ptpPacket->tpHead.tpHeadBits.Bits.uiRsv = 1;
                        SsfdPacket[ucChnl].ptpPacket->tpHead.tpHeadBits.Bits.uiSegPolo = 0x03;
                        
                        SsfdPacket[ucChnl].ptpPacket->pucDat[0] = SYS_PACKET_ERR;
                        SsfdPacket[ucChnl].ptpPacket->usDatLen  = 1;
                    } else {
                        sysHeapFree(SsfdPacket[ucChnl].ptpPacket);  
                        SsfdPacket[ucChnl].ptpPacket = NULL;
                        SsfdPacket[ucChnl].ulId      = 0;
                        SsfdPacket[ucChnl].ucXor     = 0;
                        SsfdPacket[ucChnl].usLen     = 0;
                        SsfdPacket[ucChnl].usLenTmep = 0;
                        return;
                    }
                }
                tpRemotePacketReceive((TP_DRV_INFO_BASE*)__GptdiDrvs[SsfdPacket[ucChnl].ptpPacket->ucChnl], 
                                          (TP_PACKET_HEAD*)SsfdPacket[ucChnl].ptpPacket); 
                SsfdPacket[ucChnl].ptpPacket = NULL;
                SsfdPacket[ucChnl].ulId      = 0;
                SsfdPacket[ucChnl].ucXor     = 0;
                SsfdPacket[ucChnl].usLen     = 0;
                SsfdPacket[ucChnl].usLenTmep = 0;                  
            }
        } else if (SsfdPacket[ucChnl].ptpPacket->tpHead.tpHeadBits.Bits.uiSegPolo < 0x03){
            SsfdPacket[ucChnl].ptpPacket->pucDat[SsfdPacket[ucChnl].ptpPacket->usDatLen++] = ucRbr;
            SsfdPacket[ucChnl].usLen++;   
            SsfdPacket[ucChnl].ucXor ^= ucRbr; 
        } else {
            if (SsfdPacket[ucChnl].ptpPacket->usDatLen < SsfdPacket[ucChnl].usLen - 1) {
                SsfdPacket[ucChnl].ptpPacket->pucDat[SsfdPacket[ucChnl].ptpPacket->usDatLen++] = ucRbr;
                SsfdPacket[ucChnl].ucXor ^= ucRbr; 
            } else {
                if (SsfdPacket[ucChnl].ucXor != ucRbr){
                    if (SsfdPacket[ucChnl].ptpPacket->tpHead.tpHeadBits.Bits.uiRF < TP_NREAD_FLG) {
                        SsfdPacket[ucChnl].ptpPacket->tpHead.tpHeadBits.Bits.uiRF += TP_RFREAD_FLG;
                        SsfdPacket[ucChnl].ptpPacket->tpHead.tpHeadBits.Bits.uiSegPolo = 0x03;
                        SsfdPacket[ucChnl].ptpPacket->pucDat[0] = SYS_PACKET_ERR;
                        SsfdPacket[ucChnl].ptpPacket->usDatLen = 1;
                    } else {
                        sysHeapFree(SsfdPacket[ucChnl].ptpPacket);  
                        SsfdPacket[ucChnl].ptpPacket = NULL;
                        SsfdPacket[ucChnl].ulId      = 0;
                        SsfdPacket[ucChnl].ucXor     = 0;
                        SsfdPacket[ucChnl].usLen     = 0;
                        SsfdPacket[ucChnl].usLenTmep = 0;
                        return;
                    }
                }
                tpRemotePacketReceive((TP_DRV_INFO_BASE*)__GptdiDrvs[SsfdPacket[ucChnl].ptpPacket->ucChnl], 
                                          (TP_PACKET_HEAD*)SsfdPacket[ucChnl].ptpPacket); 
                SsfdPacket[ucChnl].ptpPacket = NULL;
                SsfdPacket[ucChnl].ulId      = 0;
                SsfdPacket[ucChnl].ucXor     = 0;
                SsfdPacket[ucChnl].usLen     = 0;
                SsfdPacket[ucChnl].usLenTmep = 0;
            }             
        }       
    }
    }
}

/*********************************************************************************************************
** Function name:           __tpUartDrvCreate
** Descriptions:            UART 网络驱动初始化函数
** input parameters:        ptdiThis:           驱动信息
** output parameters:       none
** Returned value:          SYS_OK:              成功
**                          负数:               错误,绝对值参考tp.h
*********************************************************************************************************/
static INT32S __tpUartDrvCreate (TP_DRV_INFO *ptdiThis)
{   
    //char  ucUartArg[] = "BaudRate=9600 TxBufSize=512 TxDmaChannel=2";
    UART_HOOKS uartHooks;
    DMA_HOOKS  dmaHooks;
    if (ptdiThis == NULL) {
        return -SYS_PARA_ERR;
    }
    memset(&uartHooks, 0x00, sizeof(UART_HOOKS));   
    uartHooks.pReceive =  __tpUartDrivReceiveHook;
    switch(ptdiThis->ucId) {
        case UART1:                                                     /*  uart1                       */
            if (uartInit(UART1, "BaudRate=9600 TxBufSize=512 FifoLen=64", &uartHooks) < 0) { 
            //if (uartInit(UART1, "BaudRate=9600 TxBufSize=512", &uartHooks) < 0) {             
                                                                        /* UART控制器初始化             */
                return -SYS_NOT_OK;
            }
            vicIrqFuncSet(UART1_IRQ_CHN, PRIO_FIVE, (INT32U)USART1_ISR);
            if (dmaInit(DMA1_CHNL2, "Priority=1 Width=0 MemInc=1 PeripheralInc=0 Mode=0 Dir=1", NULL) < 0) {
                while (1);
            }
            vicIrqFuncSet(DMA1_CHNL2_IRQ, PRIO_FOUR, (INT32U)DMA1_CHNL2_ISR);
            uartLinkDma(UART1, TX_FIFO, DMA1_CHNL2, NULL); 
            
            if (dmaInit(DMA1_CHNL3, "Priority=1 Width=0 MemInc=1 PeripheralInc=0 Mode=0 Dir=0", NULL) < 0) {
                while (1);
            }
            vicIrqFuncSet(DMA1_CHNL3_IRQ, PRIO_FOUR, (INT32U)DMA1_CHNL3_ISR);
            uartLinkDma(UART1, RX_FIFO, DMA1_CHNL3, NULL); 
        break;
        
        case UART2:                                                     /*  uart2                       */
            if (uartInit(UART2, "BaudRate=115200 TxBufSize=512", &uartHooks) < 0) {          
                                                                        /* UART控制器初始化             */
                return -SYS_NOT_OK;
            }
            vicIrqFuncSet(UART2_IRQ_CHN, PRIO_FOUR, (INT32U)USART2_ISR);
            #if 1
            if (dmaInit(DMA1_CHNL1, "Priority=1 Width=0 MemInc=1 PeripheralInc=0 Mode=0 Dir=1", NULL) < 0) {
                while (1);
            }
            vicIrqFuncSet(DMA1_CHNL1_IRQ, PRIO_FOUR, (INT32U)DMA1_CHNL1_ISR);
            uartLinkDma(UART2, TX_FIFO, DMA1_CHNL1, NULL);
            #endif
        break;
        case UART3:
        break;
        
        default:
            return -SYS_PARA_ERR;
        break;
    }
    
    return SYS_OK;
}


/*********************************************************************************************************
** Function name:           __tpUartDrvDel
** Descriptions:            UART 网络驱动删除函数
** input parameters:        ptdiThis:           驱动信息
** output parameters:       none
** Returned value:          SYS_OK:              成功
**                          负数:               错误,绝对值参考tp.h
*********************************************************************************************************/
static INT32S __tpUartDrvDel (TP_DRV_INFO *ptdiThis)
{
    return SYS_OK;
}

/*********************************************************************************************************  
** Function name:           __tpUartDrvSend
** Descriptions:            AnyPort数据发送驱动
** Input parameters:        uiId:               USART驱动号
**                          pciPacket:          数据
**
** Output parameters:       pucOutDatRtn:       返回数据指针
** Returned value:          >=0                 成功
**                          <0                  错误,绝对值参考tp.h  
*********************************************************************************************************/
#define __PACKET_LENTH  129
static volatile INT8U __SucSendMutex;
INT32S __tpUartDrvSend(TP_DRV_INFO *ptdiThis, TP_PACKET_HEAD *ptpPacket) 
{    
    TP_PACKET   *ptpPacketBrd;
    INT32U        ucSegNum;
    INT32U        ucLastNum;
    INT8U        ucXor;
    INT8U        i;
    INT32U       j;
    __HEADBITS   headbits;
    INT32U       ulId;
    INT8U       *pucData; 
    INT32U       uiLen;
    INT32U       uiSend;
    INT32U       uiLenTmp;
    
    
    if (ptdiThis == NULL) {
        return -SYS_PARA_ERR;
    }
    if (ptpPacket == NULL) {
        return -SYS_PARA_ERR;
    }
    
    while(1 == __SucSendMutex) {
        OSTimeDly(OS_TICKS_PER_SEC / 100);
    }
	sysIrqDisable(); 
    OSSchedLock();
    __SucSendMutex = 1;
 	OSSchedUnlock();  
    sysIrqEnable();
    
    
    ptpPacketBrd = (TP_PACKET*)ptpPacket;

    ucSegNum     = ptpPacketBrd->usDatLen / __PACKET_LENTH;
    ucLastNum    = ptpPacketBrd->usDatLen % __PACKET_LENTH;
    
    if (ucSegNum > 0) {
        pucData = (INT8U *)sysHeapMalloc((__PACKET_LENTH + 6) * 2 + 1);
    } else {
        pucData = (INT8U *)sysHeapMalloc((ucLastNum + 6) * 2 + 1);
    }    
    if (pucData == NULL) {
        return -SYS_NO_MEMORY;
    }
    ucXor = 0;
    for(i = 0; i < ucSegNum + 1; i++) {        
        headbits.uiWord = ptpPacket->tpHeadBits.uiWord;        
        if (0 == ucSegNum) {
            headbits.Bits.uiSegPolo = 0x00;
            uiLenTmp = ucLastNum + 1;
        } else if (0 == i) {
            headbits.Bits.uiSegPolo = 0x01;
            uiLenTmp = __PACKET_LENTH;
        } else if (i != ucSegNum) {
            headbits.Bits.uiSegPolo = 0x02;
            uiLenTmp = __PACKET_LENTH;
        } else {
            headbits.Bits.uiSegPolo = 0x03;
            uiLenTmp = ucLastNum + 1;
        }
        headbits.Bits.uiSegNum  = (ucSegNum - i);
        
        ulId = headbits.uiWord;
        tp_htonl(ulId);    
        ucXor = (ucXor ^ ((INT8U *)&ulId)[0] ^ ((INT8U *)&ulId)[1] ^ ((INT8U *)&ulId)[2] ^ ((INT8U *)&ulId)[3]);
        ucXor ^= uiLenTmp;
        
        pucData[0] = PACKET_START_CHAR;
        uiLen = 1;
        
        for (j = 0; j < 4; j++) {
            if (((INT8U *)&ulId)[j] == PACKET_START_CHAR || ((INT8U *)&ulId)[j] == PACKET_DLE_CHAR) {
                pucData[uiLen++] = PACKET_DLE_CHAR;
                pucData[uiLen++] = (INT8U)(((INT8U *)&ulId)[j] ^ PACKET_DLE_XOR_CHAR);
            } else {
                pucData[uiLen++] = ((INT8U *)&ulId)[j];
            }        
        } 
        if (uiLenTmp == PACKET_START_CHAR || uiLenTmp == PACKET_DLE_CHAR) {
            pucData[uiLen++] = PACKET_DLE_CHAR;
            pucData[uiLen++] = (INT8U)(uiLenTmp ^ PACKET_DLE_XOR_CHAR);
        } else {
            pucData[uiLen++] = uiLenTmp;
        }              
        for (j = 0; j < uiLenTmp; j++) {
            if ((j == ucLastNum) && (i == ucSegNum)) {                  /*  最后一包数据                */
                if (ucXor == PACKET_START_CHAR || ucXor == PACKET_DLE_CHAR) {
                    pucData[uiLen++] = PACKET_DLE_CHAR;
                    pucData[uiLen++] = (INT8U)(ucXor ^ PACKET_DLE_XOR_CHAR);
                } else {
                    pucData[uiLen++] = ucXor;
                }
                break;
            }
            ucXor ^= ptpPacketBrd->pucDat[j + (i *__PACKET_LENTH)];
            if (ptpPacketBrd->pucDat[j + (i *__PACKET_LENTH)] == PACKET_START_CHAR || 
                ptpPacketBrd->pucDat[j + (i *__PACKET_LENTH)] == PACKET_DLE_CHAR) {
                pucData[uiLen++] = PACKET_DLE_CHAR;
                pucData[uiLen++] = (INT8U)(ptpPacketBrd->pucDat[j + (i *__PACKET_LENTH)] ^ PACKET_DLE_XOR_CHAR);
            } else {
                pucData[uiLen++] = ptpPacketBrd->pucDat[j + (i *__PACKET_LENTH)];
            }
        }
        
        uiSend = 0;
        //OSSchedLock();
        do {          
            uiSend += uartWrite (ptdiThis->ucId, pucData + uiSend, (uiLen - uiSend));
            if (uiSend == uiLen) {            
                break; 
            } else {
                //OSTimeDly(1);
            }
            
        } while (1); 
        //OSSchedUnlock();   
    }

    sysIrqDisable(); 
    OSSchedLock();
    __SucSendMutex = 0;
 	OSSchedUnlock();  
    sysIrqEnable();
    sysHeapFree(pucData);
    return ptpPacketBrd->usDatLen;
}


    /*
     *  UART1驱动结构体
     */
const TP_DRV_INFO GtdiUart1DrvInfo = {
    {
        (TP_DRV_FUNC_BASE *)&GtdfRemoteUart,
        __TP_UART1,
        __TPUART_REMOTE_TIMEOUT
    },
    UART1
};
    /*
     *  UART2驱动结构体
     */
const TP_DRV_INFO GtdiUart2DrvInfo = {
    {
        (TP_DRV_FUNC_BASE *)&GtdfRemoteUart,
        __TP_UART2,
        __TPUART_REMOTE_TIMEOUT
    },
    UART2
};
    /*
     *  UART3驱动结构体
     */
const TP_DRV_INFO GtdiUart3DrvInfo = {
    {
        (TP_DRV_FUNC_BASE *)&GtdfRemoteUart,
        __TP_UART3,
        __TPUART_REMOTE_TIMEOUT
    },
    UART3
};
    /*
     *  UART4驱动结构体
     */
const TP_DRV_INFO GtdiUart4DrvInfo = {
    {
        (TP_DRV_FUNC_BASE *)&GtdfRemoteUart,
        __TP_UART4,
        __TPUART_REMOTE_TIMEOUT
    },
    UART4
};
    /*
     *  UART5驱动结构体
     */
const TP_DRV_INFO GtdiUart5DrvInfo = {
    {
        (TP_DRV_FUNC_BASE *)&GtdfRemoteUart,
        __TP_UART5,
        __TPUART_REMOTE_TIMEOUT
    },
    UART5
};
    /*
     *  UART6驱动结构体
     */
const TP_DRV_INFO GtdiUart6DrvInfo = {
    {
        (TP_DRV_FUNC_BASE *)&GtdfRemoteUart,
        __TP_UART6,
        __TPUART_REMOTE_TIMEOUT
    },
    UART6
};
    /*
     *  UART3驱动结构体
     */
const TP_DRV_INFO GtdiUart7DrvInfo = {
    {
        (TP_DRV_FUNC_BASE *)&GtdfRemoteUart,
        __TP_UART7,
        __TPUART_REMOTE_TIMEOUT
    },
    UART7
};
    /*
     *  UART8驱动结构体
     */
const TP_DRV_INFO GtdiUart8DrvInfo = {
    {
        (TP_DRV_FUNC_BASE *)&GtdfRemoteUart,
        __TP_UART8,
        __TPUART_REMOTE_TIMEOUT
    },
    UART8
};
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

