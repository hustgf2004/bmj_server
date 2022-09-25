/****************************************Copyright (c)****************************************************
**                           
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tmUart2Can.c
** Latest modified Date:    2011-04-08
** Latest Version:          1.0
** Descriptions:            UART网络底层驱动
**
**--------------------------------------------------------------------------------------------------------
** Created by:               
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
#include    "main.h"

/*********************************************************************************************************
  特殊字符定义
*********************************************************************************************************/
#define PACKET_START_CHAR               0xFA
#define PACKET_DLE_CHAR                 0xF9
#define PACKET_DLE_XOR_CHAR             0x42

/*********************************************************************************************************
** Function name:           uartReceiveHook
** Descriptions:            UART 网络驱动的中断接收函数
** input parameters:        pRsv:   保留参数
**                          ucRbr:  接收到的UART 帧
** output parameters:       none
** Returned value:          none
** Created by:               
** Created date:            2011-04-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void uartReceiveHook (void *pRsv, INT8U ucRbr, INT8U ucLsr)
{       
    static __SERIAL_FRAME_DEL SsfdPacket[1] = {{0, NULL, 0, 0, 0}};
    INT8U               ucChn;
    CANFRAME canFrame;

    ucLsr = ucLsr;
    ucChn = 0;
    if (ucRbr == PACKET_START_CHAR) {                                   /*  接收到帧起始字符            */
        if ((SsfdPacket[ucChn].pfrPacket != NULL)) {
            //sysHeapFree(SsfdPacket[ucChn].pfrPacket);
            //SsfdPacket[ucChn].pfrPacket = NULL; 
        }        
        SsfdPacket[ucChn].ucXor     = 0;
        SsfdPacket[ucChn].usLen     = 1;
        SsfdPacket[ucChn].ulId      = 0;      
        return;
    }

    if (ucRbr == PACKET_DLE_CHAR) {                                     /*  接收到转义字符              */
        SsfdPacket[ucChn].ucState = PACKET_DLE_XOR_CHAR;        
        return;
    }
    
    ucRbr = (INT8U)(ucRbr ^ SsfdPacket[ucChn].ucState);                 /*  真正的字符                  */
    SsfdPacket[ucChn].ucState = 0;
    
    switch (SsfdPacket[ucChn].usLen) {    
        case 0:            
            return;
        case 1:    
            SsfdPacket[ucChn].ulId      |= ucRbr << 24;
            SsfdPacket[ucChn].ucXor     ^= ucRbr;
            
            SsfdPacket[ucChn].usLen++;
            return;
        case 2:
            SsfdPacket[ucChn].ulId      |= ucRbr << 16;
            SsfdPacket[ucChn].ucXor     ^= ucRbr;
            
            SsfdPacket[ucChn].usLen++;
            return;
        case 3:
            SsfdPacket[ucChn].ulId      |= ucRbr << 8;
            SsfdPacket[ucChn].ucXor     ^= ucRbr;
            
            SsfdPacket[ucChn].usLen++;           
            return;
        case 4:    
            SsfdPacket[ucChn].ulId      |= ucRbr;
            SsfdPacket[ucChn].ucXor     ^= ucRbr;
                        
            SsfdPacket[ucChn].usLen++;
            return;
        case 5:
            if ((SsfdPacket[ucChn].pfrPacket == NULL)) {
                SsfdPacket[ucChn].pfrPacket = (__FRAME_PACKET*)sysHeapMalloc(sizeof(__FRAME_PACKET));
            }     
            
            if (NULL == SsfdPacket[ucChn].pfrPacket) {
                SsfdPacket[ucChn].ucXor     = 0;
                SsfdPacket[ucChn].usLen     = 1;
                SsfdPacket[ucChn].ulId      = 0;      
                return;
            }
            memset(SsfdPacket[ucChn].pfrPacket, 0x00, sizeof(__FRAME_PACKET));
            SsfdPacket[ucChn].pfrPacket->ulId.ulDWord = SsfdPacket[ucChn].ulId;
            SsfdPacket[ucChn].pfrPacket->ucDataLen  = ucRbr - 1;
            
            SsfdPacket[ucChn].ucXor ^= ucRbr;
            if ((0 == ucRbr) || (ucRbr > 9)) {
                SsfdPacket[ucChn].ulId      = 0;
                SsfdPacket[ucChn].ucXor     = 0;
                SsfdPacket[ucChn].usLen     = 0;              
            }
            SsfdPacket[ucChn].usLen++; 
            return;
        default:            
            break;
    }
    if (SsfdPacket[ucChn].usLen < SsfdPacket[ucChn].pfrPacket->ucDataLen + 6) {
        SsfdPacket[ucChn].pfrPacket->ucBuf[SsfdPacket[ucChn].usLen - 6] = ucRbr;
        SsfdPacket[ucChn].usLen++;   
        SsfdPacket[ucChn].ucXor ^= ucRbr; 
    } else {
        if (SsfdPacket[ucChn].ucXor == ucRbr){ 
            //tmRemotePacketReceive(0,(TM_PACKET_HEAD*)SsfdPacket[ucChn].pfrPacket);
            canFrame.ucIsRemote = ((__FRAME_PACKET*)SsfdPacket[ucChn].pfrPacket)->ulId.ulBits.ucIsRemote;
            canFrame.ucIsExtend = ((__FRAME_PACKET*)SsfdPacket[ucChn].pfrPacket)->ulId.ulBits.ucIsExtend;
            canFrame.ulId = ((__FRAME_PACKET*)SsfdPacket[ucChn].pfrPacket)->ulId.ulDWord & ~(0x07<<29);
            canFrame.ucDataLen = ((__FRAME_PACKET*)SsfdPacket[ucChn].pfrPacket)->ucDataLen;
            memcpy(canFrame.ucBuf, ((__FRAME_PACKET*)SsfdPacket[ucChn].pfrPacket)->ucBuf, canFrame.ucDataLen);
           	//canFrame.ucIsExtend = 0x01;
		    CanFrmProcess(CAN_PORT_RIGHT, canFrame);
        }
        SsfdPacket[ucChn].ucXor     = 0;
        SsfdPacket[ucChn].usLen     = 0;
        SsfdPacket[ucChn].ulId      = 0;   
        //sysHeapFree(SsfdPacket[ucChn].pfrPacket);
        //SsfdPacket[ucChn].pfrPacket = NULL;
        
    }
    return;
}
/*********************************************************************************************************
** Function name:           __tmUartDrivSend
** Descriptions:            UART 网络驱动发送函数
** input parameters:        pData：  数据帧 
** output parameters:       none
** Returned value:          非零 :    读写的数据字节数目
**                            零:     错误
** Created by:               
** Created date:            2011-04-08
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
extern volatile INT32U	GuiPacketSendNum[];
INT32S uart2CanSend (INT8U  ucChn, struct __frame_packet   *pData)
{    
    INT8U           ucSegNum;
    INT8U           ucLastNum;
    INT8U           ucXor;
    INT8U           i;
    INT32U          ulId;
    INT8U          *pucData; 
    INT32U          uiLen;
    INT32U          uiSend;
    INT32U          uiLenTmp;
    __FRAME_PACKET *ptpPacketBrd;
    
    if (pData == NULL) {
        return 0;
    }
    ptpPacketBrd = (__FRAME_PACKET*)pData;
    ucLastNum    = ptpPacketBrd->ucDataLen;
    
    pucData = (INT8U *)sysHeapMalloc((ptpPacketBrd->ucDataLen + 6) * 2 + 1);
    if (pucData == NULL) {
        return 0;
    }
    
    ucXor = 0;
    uiLenTmp = ucLastNum + 1;
    ulId = ptpPacketBrd->ulId.ulDWord;
    tm_htonl(ulId);    
    ucXor = (ucXor ^ ((INT8U *)&ulId)[0] ^ ((INT8U *)&ulId)[1] ^ ((INT8U *)&ulId)[2] ^ ((INT8U *)&ulId)[3]);
    ucXor ^= uiLenTmp;
    
    pucData[0] = PACKET_START_CHAR;
    uiLen = 1;
    
    for (i = 0; i < 4; i++) {
        if (((INT8U *)&ulId)[i] == PACKET_START_CHAR || ((INT8U *)&ulId)[i] == PACKET_DLE_CHAR) {
            pucData[uiLen++] = PACKET_DLE_CHAR;
            pucData[uiLen++] = (INT8U)(((INT8U *)&ulId)[i] ^ PACKET_DLE_XOR_CHAR);
        } else {
            pucData[uiLen++] = ((INT8U *)&ulId)[i];
        }        
    } 
    if (uiLenTmp == PACKET_START_CHAR || uiLenTmp == PACKET_DLE_CHAR) {
        pucData[uiLen++] = PACKET_DLE_CHAR;
        pucData[uiLen++] = (INT8U)(uiLenTmp ^ PACKET_DLE_XOR_CHAR);
    } else {
        pucData[uiLen++] = uiLenTmp;
    }              
    for (i = 0; i < uiLenTmp; i++) {
        if (i == ucLastNum) {                  
            if (ucXor == PACKET_START_CHAR || ucXor == PACKET_DLE_CHAR) {
                pucData[uiLen++] = PACKET_DLE_CHAR;
                pucData[uiLen++] = (INT8U)(ucXor ^ PACKET_DLE_XOR_CHAR);
            } else {
                pucData[uiLen++] = ucXor;
            }
            break;
        }
        ucXor ^= ptpPacketBrd->ucBuf[i];
        if (ptpPacketBrd->ucBuf[i] == PACKET_START_CHAR || 
            ptpPacketBrd->ucBuf[i] == PACKET_DLE_CHAR) {
            pucData[uiLen++] = PACKET_DLE_CHAR;
            pucData[uiLen++] = (INT8U)(ptpPacketBrd->ucBuf[i] ^ PACKET_DLE_XOR_CHAR);
        } else {
            pucData[uiLen++] = ptpPacketBrd->ucBuf[i];
        }
    }
    
    uiSend = 0;
    do {          
        uiSend += uartWrite (ucChn, pucData + uiSend, (uiLen - uiSend));
        if (uiSend == uiLen) {            
            GuiPacketSendNum[0] ++;
			break; 
        } else {
            OSTimeDly(1);
        }
        
    } while (1);  

    sysHeapFree(pucData);
    return ptpPacketBrd->ucDataLen;
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
