/****************************************Copyright (c)**************************************************
**                               
**                                      
**                                 
**
**--------------File Info-------------------------------------------------------------------------------
** File name:           MB_BSP_LPC2000.c
** Last modified Date:  2013-11-30
** Last Version:        2.0
** Descriptions:        ModbusӲ����
**
**------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:             
** Descriptions:        
**
********************************************************************************************************/
#include "..\..\..\USER_CODE\main.h"

void MB_BSP_SendData (INT8U ucCh, INT8U *ucBuf, INT16U usLen);
INT8U BSP_MB_PortCfg (MB_CFG *mb_ch);
void BSP_MB_TmrInit (INT32U time);

#define __USE_MODBUS 1

#if __USE_MODBUS

#define TEMP_BUF_SIZE   512 

MB_CFG mcMBch;
INT8U   GucUart0ADUBuf[TEMP_BUF_SIZE]; 
MBDSTR  GmbdCH0Data; 

void  MB_CFGInit(void)
{                                                          
    mcMBch.ch           = MB_UART0_CH;                                  /*  ���ùܵ�                    */
    mcMBch.node_addr    = 0;                                            /*  ����Modbus����              */
    mcMBch.modbus_mode  = MB_RTU_MODE;                                  /*  ����ģʽ                    */
    mcMBch.BaudRate     = 9600;                                         /*  ������                      */
    mcMBch.bits         = 8;                                            /*  8λ�ַ�                     */
    mcMBch.parity       = 0;                                            /*  ��У��                      */
    mcMBch.stops        = 1;                                            /*  1��ֹͣλ                   */
    mcMBch.usADUBufSize = sizeof(GucUart0ADUBuf);
    mcMBch.pucADUPtr    = GucUart0ADUBuf;
    mcMBch.usQSendSize  = TEMP_BUF_SIZE+20;
   // mcMBch.puqSendBuf   = NULL;
    mcMBch.mbdPtr       = &GmbdCH0Data;
    //mcMBch.pvDriver     = NULL;                                         /*  UART������Ҫ�����ݽṹ      */
    mcMBch.PortCfg      = BSP_MB_PortCfg;
    mcMBch.SendData     = MB_BSP_SendData;
    //mcMBch.ExitPort     = NULL; 
    BSP_MB_TmrInit(500);
}

/*********************************************************************************************************
** Function name:           MB_BSP_SendData
** Descriptions:            ����֡����Ϊ�ײ��ַ����ʹ���������ZY/MODBUS Э��ջ��ʹ�øú�������֡����
**                          
** input parameters:        ucCh,ͨ����
**                          buff���������ݻ�����ָ��
**                          len,�������ݳ���
** output parameters:       none
** Returned value:          none
** Created by:              
** Created Date:            2013-11-30
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void MB_BSP_SendData (INT8U ucCh, INT8U *ucBuf, INT16U usLen)
{
    uartWrite(ucCh, ucBuf, usLen);      //  д��������

}
/*********************************************************************************************************
** Function name:           uartReviceHook
** Descriptions:            UART�ַ����չ��Ӻ���,���������յ�һ���ַ�,�����øú���һ��.
** input parameters:        pudInfo:  ָ��uart��Ϣ�ṹ���ָ��
**                          ucRbr,���յ����ַ�.
** output parameters:       none
** Returned value:          none
** Created by:              
** Created Date:            2013-11-30
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/     
void uartReviceHook (void *pudInfo, INT8U ucRbr, INT8U ucLsr)
{
    MB_UartReceOneChar(UART0,ucRbr,0);                          /*  ����ZY/Modbus�����ַ�������
                                                                  ����ÿһ���ַ�              */
}

/*********************************************************************************************************
** Function name:           BSP_MB_PortCfg
** Descriptions:            �ú�����MB_CfgCh()���ã��������ô���ͨѶ�ڣ�����mb_ch->ch�����ж��������õ�
**                          ���ڡ�
** input parameters:        *mb_ch,�������ò���ָ�룻
** output parameters:       none
** Returned value:          ��������MB_NO_ERR;
**                          ��������MB_PARAMETER_ERR(��Ч����)��
** Created by:              
** Created Date:            2013-11-30
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/ 
INT8U BSP_MB_PortCfg (MB_CFG *mb_ch)
{
    char       UartArg[60];
    UART_HOOKS uarthook;
    uint8      UartIRQCh;
    /*
    *   �������
    */
    if (mb_ch == (void*)0) {
        return MB_PARAMETER_ERR;
    }
    
    if ((mb_ch->modbus_mode != MB_RTU_MODE) &&                      /*  �û����ݹܵ�֧�ֵ�ģʽ����  */
        (mb_ch->modbus_mode != MB_ASCII_MODE)) {
        return MB_PARAMETER_ERR;
    }   
    
    
    memset(&uarthook,0,sizeof(UART_HOOKS));
    uarthook.pReceive = uartReviceHook;


    sprintf (UartArg, "BaudRate=%d RxBufSize=50 TxBufSize=%d FifoLen=8", mb_ch->BaudRate, mb_ch->usQSendSize );
    if (OPERATE_FAIL == uartInit(mb_ch->ch, (char *)UartArg, &uarthook)) {
        while (1);
    }
    if(MB_RTU_MODE == mb_ch->modbus_mode)
        uartSetMode(mb_ch->ch,SET_SPRINGPT,"SpringPoint=1");
    switch(mb_ch->ch)
    {
        case 0:
            UartIRQCh = UART0_IRQ_CHN;
            break;
        case 1:
            UartIRQCh = UART1_IRQ_CHN;
            break;

        default:
            break;
    }
    vicIrqFuncSet(UartIRQCh,6,(uint32)UART0_ISR);
    if((mb_ch->bits != MB_UART_8BIT)     || 
       (mb_ch->parity != MB_NONE_PARITY) || 
       (mb_ch->stops != MB_UART_1STOP)     ) {
       sprintf (UartArg, "DataBits=%d StopBits=%d Parity=%d", mb_ch->bits, mb_ch->stops, mb_ch->parity); 
       uartSetMode (mb_ch->ch, SET_CTRLMODE,UartArg);
    }
    
    /*
    *  ���ʹ��RS485��ִ���¸�����
    */
  #if 0
    if (OPERATE_FAIL == uartSetMode(mb_ch->ch,SET_RS485,"RS485Dir=213")) {
        while (1);
    }
  #endif
    return MB_NO_ERR;
}

void CPU_ENTER_CRITICAL (void) 
{
    sysIrqDisable();
}


void CPU_EXIT_CRITICAL (void)
{
    sysIrqEnable();
}
#endif
/*********************************************************************************************************
** Function name:           BSP_MB_TmrInit
** Descriptions:            ��ʱ����ʼ������,�����ṩ�Ĳ����趨��ʱ���жϲ�����Ƶ��
** input parameters:        time����ʱ��Ƶ�ʣ���СֵΪ25uS
** output parameters:       none
** Returned value:          none
** Created by:              
** Created Date:            2013-11-30
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/ 
void BSP_MB_TmrInit (INT32U time)
{
    char TmrArg[50];
    
    sprintf(TmrArg, "Time=%d ActCtrl=3",time);
    timerInit(TIMER1,"Mode=0",NULL);                                    /*  ��ʱ��1��ʼ��               */
    /* 
    ** ���ö�ʱ��1�Ĺ���ģʽΪ��ʱģʽ��
    ** Time=500����ʱʱ��Ϊ500us 
    ** ActCtrl=3��ƥ���T1TC��λ,�������ж� 
    */
    timerSetMode(TIMER1,SET_TIMERMODE,TmrArg);
                                                                   
    vicIrqFuncSet(TIMER1_IRQ_CHN,7,(uint32)TIMER1_ISR);         /*  �����жϣ�һ��Ҫ���жϺ�����
                                                                            ����MB_TmrUpdate()����      */
    timerStart(TIMER1);                                            /*  ������ʱ��                  */
}

/*********************************************************************************************************
**  End
**********************************************************************************************************/