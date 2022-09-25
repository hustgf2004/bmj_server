/****************************************Copyright (c)**************************************************
**
**
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           uart.h
** Last modified Date:  2013-03-15
** Last Version:        1.00
** Descriptions:        uart驱动外部头函数
**--------------------------------------------------------------------------------------------------------
** Created by:          
** Created date:        2013-03-15
** Version:             1.00
** Descriptions:        The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
*********************************************************************************************************/
#ifndef __UART_H
#define __UART_H
#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
  UART 相关索引
*********************************************************************************************************/
#define  UART0              0                                           /*  UART0 ID 号                 */
#define  UART1              1                                           /*  UART1 ID 号                 */
#define  UART2              2                                           /*  UART2 ID 号                 */
#define  UART3              3                                           /*  UART3 ID 号                 */
#define  UART4              4                                           /*  UART4 ID 号                 */
#define  UART5              5                                           /*  UART5 ID 号                 */
/*********************************************************************************************************
    UART设备中断通道号
*********************************************************************************************************/
#define  UART0_IRQ_CHN      6                                           /*  UART0中断通道号             */
#define  UART1_IRQ_CHN      7                                           /*  UART1中断通道号             */

/*********************************************************************************************************
  UART 模式配置命令
*********************************************************************************************************/
#define  SET_BAUDRATE       0                                           /*  串口波特率                  */
#define  SET_CTRLMODE       1                                           /*  串口模式                    */
#define  SET_TIMEOUT        2                                           /*  超时设置                    */
#define  SET_MODEM          3                                           /*  UART1 Modem功能             */
#define  SET_RS485          4                                           /*  RS485设置                   */
#define  SET_FLOWTYPE       5                                           /*  设置流控制类型              */
#define  SET_SPRINGCH       6                                           /*  重新设置触发字符            */
#define  SET_SPRINGPT       7                                           /*  重新设置接收中断触发点      */

/*********************************************************************************************************
  用户可调用的钩子函数
*********************************************************************************************************/
struct uartHooks {
    /*
     *  钩子函数流
     */
    void        (*pModemState)(void *pRsv, INT8U ucMsr);                /*  Modem状态变化调用的函数     */
                                                                        /*  pRsv: 保留,用户不要操作     */
                                                                        /*  ucMsr:   MSR寄存器的值      */

    void        (*pSendEnd)(void *pRsv);                                /*  数据包发送结束调用的函数    */
                                                                        /*  pRsv: 保留,用户不要操作     */

    void        (*pReceive)(void *pRsv,INT8U ucRbr, INT8U ucLsr);       /*  接收到字符调用的函数        */
                                                                        /*  pRsv:  保留,用户不要操作    */
                                                                        /*  ucRbr: 接收到的字符         */
                                                                        
    void        (*pLineErr)(void *pRsv, INT8U ucLcr);
                                                                        /*  线路状态出错中断调用的函数  */
                                                                        /*  pRsv: 保留,用户不要操作     */
                                                                        /*  ucLcr: 线路状态寄存器的内容 */

    /*
     *  触发设置
     */
    char        cSpringChar;                                            /*  触发的字符                  */
    void      (*pSpringFunction)(void *pRsv);                           /*  接收到触发的字符后调用的函数*/
                                                                        /*  pRsv: 保留,用户不要操作     */
};
typedef struct uartHooks    UART_HOOKS;
typedef struct uartHooks*   PUART_HOOKS;


/*********************************************************************************************************  
** Function name:           uartInit  
** Descriptions:            串口初始化及中断设置  
** input parameters:        uiId            子设备号  
**                          pcArg           字符串指针  
**                          pRsv            保留参数  
** Output parameters:       NONE  
** Returned value:          OPERATE_SUCCESS 操作成功  
**                          -OPERATE_FAIL   操作失败  
** Example:                 char pcArg[]="BaudRate=9600,DataBits=8,StopBits=1,Parity=NONE,RtsControl=NONE";   
**                          uartInit(0,pcArg,0);   
*********************************************************************************************************/ 
extern INT32S uartInit(INT32U ulId, char *pucArg, void *pvRsv);

/*********************************************************************************************************  
** Function name:           uartSetMode  
** Descriptions:            设置串口的参数  
** input parameters:        uiId            子设备号  
**                          uiCmd           设置命令宏
**                          SET_BAUDRATE    串口波特率
**                          SET_CTRLMODE    串口模式
**                          SET_TIMEOUT     超时设置
**                          SET_MODEM       UART1 Modem功能
**                          SET_RS485       RS485设置
**                          SET_FLOWTYPE    设置流控制类型
**                          SET_SPRINGCH    重新设置触发字符
**                          SET_SPRINGPT    重新设置接收中断触发点
**                          pcArg           字符串指针  
** Output parameters:       NONE  
** Returned value:          OPERATE_SUCCESS 操作成功  
**                          -OPERATE_FAIL   操作失败      
** Examples:                char pUart[]="DataBits=8 StopBits=1 Parity=NONE RtsControl=NONE";  
**                              
*********************************************************************************************************/   
extern INT32S uartSetMode(INT32U ulId, INT32U ulCmd, char *pucArg);

/*********************************************************************************************************  
** Function name:           uartGetState  
** Descriptions:            获取当前串口的参数  
** input parameters:        uiId            子设备号  
**                          pcArg           字符串指针  
** Output parameters:       pcArg           输出字符串参数  
** Returned value:          OPERATE_SUCCESS 操作成功  
**                          -OPERATE_FAIL   操作失败  
*********************************************************************************************************/   
extern INT32S uartGetState (INT32U uiId, char * pcArg);

/*********************************************************************************************************  
** Function name:           rs485Input  
** Descriptions:            rs485置接收状态 
** input parameters:        uiId            子设备号  
**                          
** Output parameters:       
** Returned value:          OPERATE_SUCCESS 操作成功  
**                          -OPERATE_FAIL   操作失败  
*********************************************************************************************************/   
extern INT32S rs485Input(INT32U uiId);

/*********************************************************************************************************  
** Function name:           rs485Output  
** Descriptions:            rs485置发送状态 
** input parameters:        uiId            子设备号  
**                          
** Output parameters:       
** Returned value:          OPERATE_SUCCESS 操作成功  
**                          -OPERATE_FAIL   操作失败  
*********************************************************************************************************/   
extern INT32S rs485Output(INT32U uiId);

   
/*********************************************************************************************************  
** Function name:           uartFifoFlush  
** Descriptions:            清空接收或发送Queue队列  
** input parameters:        uiId            UART子设备号  
**                          uiWhichFifo     TX_FIFO-发送队列
**                                          RX_FIFO-接收队列  
** Output parameters:       NONE  
** Returned value:          OPERATE_SUCCESS 操作成功  
**                          -OPERATE_FAIL   操作失败  
*********************************************************************************************************/   
extern INT32S uartFifoFlush (INT32U uiId, INT32U uiWhichFifo);

/*********************************************************************************************************  
** Function name:           uartRead  
** Descriptions:            从串口设备读取数据  
** input parameters:        uiId            子设备号
**                          uiSize          读取的数据个数  
**                           
** Output parameters:       pucBuf          保存返回数据的字符串指针地址    
** Returned value:          实际读取的数据个数  
*********************************************************************************************************/   
extern INT32S uartRead (INT32U uiId, INT8U *pucBuf, INT32U uiSize);

/*********************************************************************************************************  
** Function name:           uartWrite  
** Descriptions:            向串口设备写数据  
** input parameters:        uiId            子设备号  
**                          pucBuf          输出数据的字符串指针地址  
**                          uiSize          一次写入的数据个数  
**                            
** Output parameters:       NONE  
** Returned value:          实际发送的数据个数  
*********************************************************************************************************/
extern INT32S uartWrite(INT32U ulId, INT8U *pucBuf, INT32U ulSize); 
                           
/*********************************************************************************************************  
** Function name:           uartDirectWrite  
** Descriptions:            向串口设备直接发送数据  
** input parameters:        uiId            子设备号  
**                          pucBuf          发送数据的缓存
**                          uiSize          发送数据个数                              
** Output parameters:       NONE  
** Returned value:          实际发送的数据个数
*********************************************************************************************************/  
extern INT32S uartDirectWrite(INT32U ulId, INT8U *pucBuf, INT32U ulSize);

/*********************************************************************************************************  
** Function name:           uartIsr  
** Descriptions:            UART中断服务程序  
** input parameters:        uiId            子设备号  
** Output parameters:       NONE  
** Returned value:          无  
*********************************************************************************************************/  
extern void uartIsr(INT32U ulId);

#ifdef __cplusplus
    }
#endif                                                                  /*  __cplusplus                 */
#endif                                                                  /*  __UART_H                    */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
