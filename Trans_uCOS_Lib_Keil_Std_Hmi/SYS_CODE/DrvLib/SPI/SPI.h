/****************************************Copyright (c)****************************************************
**                              
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           SPI.h
** Last modified Date:  2013-08-22
** Last Version:        1.0
** Descriptions:        LPC2200 SPI驱动
**--------------------------------------------------------------------------------------------------------
** Created by:          
** Created date:        2013-08-22
** Version:             V1.0
** Descriptions:        The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
*********************************************************************************************************/

#ifndef __SPI_H
#define __SPI_H
#ifdef  __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
  SPI 相关索引
*********************************************************************************************************/
#define   SPI0              0                                           /*  SPI ID 号                   */
#define   SPI1              1                                           /*  SPI ID 号                   */
/*********************************************************************************************************
  SPI中断通道号
*********************************************************************************************************/
#define   SPI0_IRQ_CHN      10                                          /*  SPI中断通道号               */
#define   SPI1_IRQ_CHN      11                                          /*  SPI中断通道号               */

#define   RX_BUF            0                                           /*  接收缓冲索引                */
#define   TX_BUF            1                                           /*  发送缓冲索引                */

/*********************************************************************************************************
  SPI 模式配置命令
*********************************************************************************************************/
#define   SET_SPEED         0                                           /*  SPI速率                     */
#define   SET_CTRLMODE      1                                           /*  SPI其他模式配置             */
#define   SET_MSMODE        2                                           /*  SPI主、从机设置             */
#define   SET_CSPIN         3                                           /*  SPI片选                     */
#define   SET_RWMODE        4                                           /*  SPI主机回读模式选择         */
  
struct spi_hooks {                                                      /*  钩子函数流                  */
                                                                            
    void          (*pReceive)(void *pRsv,INT8U ucRbr);                  /*  接收到字符调用的函数        */
                                                                        /*  pRsv: 保留,用户不要操作     */  
};
typedef struct spi_hooks    SPI_HOOKS;
typedef struct spi_hooks*   PSPI_HOOKS;
/*********************************************************************************************************
** Function name:           spiInit
** Descriptions:            spi初始化
** input parameters:        uiId            spi器件号
**                          pcArg           参数格式化字符串指针
**                          pRsv            保留参数
** output parameters:       None
** Returned value:          OPERATE_SUCCESS 操作成功
**                          -OPERATE_FAIL   操作失败
*********************************************************************************************************/
extern INT32S spiInit(INT32U ulId, char *pucArg, void *pvRsv);
                         
/*********************************************************************************************************
** Function name:           spiSetMode
** Descriptions:            设置SPI的模式
** input parameters:        uiId            spi器件号
**                          uiCmd           设置命令码
**                          pcArg           配置参数字符窜指针
** output parameters:       None
** Returned value:          OPERATE_SUCCESS 操作成功
**                          -OPERATE_FAIL   操作失败
*********************************************************************************************************/
extern INT32S spiSetMode(INT32U uiId, INT32U uiCmd, char *pcArg);

/*********************************************************************************************************
** Function name:           spiWrite
** Descriptions:            发送数据,把数据写入spi发送队列
** input parameters:        uiId            spi器件号
**                          pucBuf          发送数据指针
**                          uiSize          发送字节个数
** output parameters:       None
** Returned value:          成功发送字节个数
*********************************************************************************************************/
extern INT32S spiWrite(INT32U ulId, INT8U *pucBuf, INT32U ulSize); 

/*********************************************************************************************************
** Function name:           spiDirectWrite
** Descriptions:            向SPI设备直接发送数据
** input parameters:        ulId            spi器件号
**                          pucBuf          数据存放地址
**                          ulSize          发送字节个数
** output parameters:       None
** Returned value:          成功发送字节个数
*********************************************************************************************************/
extern INT32S spiDirectWrite(INT32U ulId, INT8U *pucBuf, INT32U ulSize); 

/*********************************************************************************************************
** Function name:           spiRead
** Descriptions:            读取spi缓冲中的数据
** input parameters:        ulId            spi器件号
**                          pucBuf          数据存放地址
**                          ulSize          读取字节个数
** output parameters:       None
** Returned value:          成功读取字节个数
*********************************************************************************************************/
extern INT32S spiRead(INT32U ulId, INT8U *pucBuf, INT32U ulSize);

/*********************************************************************************************************
** Function name:           spiFifoState
** Descriptions:            获取Queue队列的状态
** input parameters:        uiId            spi器件号
**                          ucFifo          TX_BUF-发送队列
**                                          RX_BUF-接收队列
** output parameters:       None
** Returned value:          发送队列中可操作的空间大小，或接收队列中可用数据个数
*********************************************************************************************************/
extern INT32S spiFifoState(INT32U ulId, INT8U ucFifo);

/*********************************************************************************************************
** Function name:           spiFifoFlush
** Descriptions:            清空发送或接收Queue队列
** input parameters:        uiId            spi器件号
**                          ucFifo          TX_BUF-发送队列;
**                                          RX_BUF-接收队列
** output parameters:       None
** Returned value:          发送队列中可操作的空间大小，或接收队列中可用数据个数
*********************************************************************************************************/
extern INT32S spiFifoFlush(INT32U ulId, INT8U ucFifo);

/*********************************************************************************************************
** Function name:           spiIsr
** Descriptions:            SPI中断服务程序
** input parameters:        uiId            spi器件号
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
extern void spiIsr(INT32U ulId);

#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */      
#endif                                                                  /*  __SPI_H                     */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
