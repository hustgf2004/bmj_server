/****************************************Copyright (c)**************************************************
**                               
**                                      
**                                 
**
**--------------File Info-------------------------------------------------------------------------------
** File name:           MB_BSP_LPC2000.c
** Last modified Date:  2013-11-30
** Last Version:        2.0
** Descriptions:        Modbus硬件层
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
    mcMBch.ch           = MB_UART0_CH;                                  /*  配置管道                    */
    mcMBch.node_addr    = 0;                                            /*  配置Modbus主机              */
    mcMBch.modbus_mode  = MB_RTU_MODE;                                  /*  传输模式                    */
    mcMBch.BaudRate     = 9600;                                         /*  波特率                      */
    mcMBch.bits         = 8;                                            /*  8位字符                     */
    mcMBch.parity       = 0;                                            /*  无校验                      */
    mcMBch.stops        = 1;                                            /*  1个停止位                   */
    mcMBch.usADUBufSize = sizeof(GucUart0ADUBuf);
    mcMBch.pucADUPtr    = GucUart0ADUBuf;
    mcMBch.usQSendSize  = TEMP_BUF_SIZE+20;
   // mcMBch.puqSendBuf   = NULL;
    mcMBch.mbdPtr       = &GmbdCH0Data;
    //mcMBch.pvDriver     = NULL;                                         /*  UART驱动需要的数据结构      */
    mcMBch.PortCfg      = BSP_MB_PortCfg;
    mcMBch.SendData     = MB_BSP_SendData;
    //mcMBch.ExitPort     = NULL; 
    BSP_MB_TmrInit(500);
}

/*********************************************************************************************************
** Function name:           MB_BSP_SendData
** Descriptions:            发送帧函数为底层字符发送处理函数，ZY/MODBUS 协议栈中使用该函数发送帧数据
**                          
** input parameters:        ucCh,通道号
**                          buff，发送数据缓冲区指针
**                          len,发送数据长度
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
    uartWrite(ucCh, ucBuf, usLen);      //  写串口数据

}
/*********************************************************************************************************
** Function name:           uartReviceHook
** Descriptions:            UART字符接收钩子函数,当驱动接收到一个字符,将调用该函数一次.
** input parameters:        pudInfo:  指向uart信息结构体的指针
**                          ucRbr,接收到的字符.
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
    MB_UartReceOneChar(UART0,ucRbr,0);                          /*  调用ZY/Modbus接收字符函数，
                                                                  接收每一个字符              */
}

/*********************************************************************************************************
** Function name:           BSP_MB_PortCfg
** Descriptions:            该函数被MB_CfgCh()调用，用于配置串行通讯口，根据mb_ch->ch参数判断所需配置的
**                          串口。
** input parameters:        *mb_ch,串口设置参数指针；
** output parameters:       none
** Returned value:          正常返回MB_NO_ERR;
**                          出错返回MB_PARAMETER_ERR(无效参数)。
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
    *   参数检查
    */
    if (mb_ch == (void*)0) {
        return MB_PARAMETER_ERR;
    }
    
    if ((mb_ch->modbus_mode != MB_RTU_MODE) &&                      /*  用户根据管道支持的模式设置  */
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
    *  如果使用RS485请执行下个函数
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
** Descriptions:            定时器初始化函数,根据提供的参数设定定时器中断产生的频率
** input parameters:        time，定时器频率，最小值为25uS
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
    timerInit(TIMER1,"Mode=0",NULL);                                    /*  定时器1初始化               */
    /* 
    ** 设置定时器1的工作模式为定时模式：
    ** Time=500：定时时间为500us 
    ** ActCtrl=3：匹配后将T1TC复位,并产生中断 
    */
    timerSetMode(TIMER1,SET_TIMERMODE,TmrArg);
                                                                   
    vicIrqFuncSet(TIMER1_IRQ_CHN,7,(uint32)TIMER1_ISR);         /*  设置中断，一定要在中断函数中
                                                                            添加MB_TmrUpdate()函数      */
    timerStart(TIMER1);                                            /*  开启定时器                  */
}

/*********************************************************************************************************
**  End
**********************************************************************************************************/
