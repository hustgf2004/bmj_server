/****************************************Copyright (c)**************************************************
**                               
**                                      
**                                 
**
**--------------File Info-------------------------------------------------------------------------------
** File name:           RequestFun.h
** Last modified Date:  2013-11-30
** Last Version:        2.0
** Descriptions:
**
**------------------------------------------------------------------------------------------------------
** Created by:          
** Created date:        2013-11-30
** Version:             2.0
** Descriptions:
**
**------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
********************************************************************************************************/
#ifndef __REQUESTFUN_H
#define __REQUESTFUN_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************************************************
    Modbus 主机请求参数数据结构
*********************************************************************************************************/
typedef struct __request_data {
    INT8U               ucChnl;                                         /*  请求硬件通道号              */
    INT16U              usRStartAddr;                                   /*  数据读地址                  */
    
    INT16U              usRSize;                                        /*  读数据个数                  */
    INT16U              usWStartAddr;                                   /*  数据写地址                  */
    
    INT16U              usWSize;                                        /*  写数据个数                  */
    void               *pvData;                                         /*  读写数据存放地址            */     
}__REQUEST_DATA, __PREQUEST_DATA;


/*********************************************************************************************************
** Function name:           MB_UartReadCoils
**
** Descriptions:            读取线圈值。0x01
**
** input parameters:        ch,Modbus通讯管道
**                          ID，从机地址
**                          StartAddress，线圈起始地址
**                          Quantity，线圈数量
**                          ReaValuePtr，保存线圈值的指针
** Returned value:          完成代码：(见modbus.h文件的异常代码表)
**
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern INT8U MB_UartReadCoils01(INT8U  ch,
                  INT8U  ID,
                  INT16U StartAddress,
                  INT16U Quantity,
                  INT8U *ReaValuePtr);

#define  OSReadCoils    MB_UartReadCoils01

/*********************************************************************************************************
** Function name:           MB_UartReadDisInputs02
**
** Descriptions:            读取离散输入量。0x02
**
** input parameters:        ch,Modbus通讯管道
**                          ID，从机地址
**                          StartAddress，离散输入量起始地址
**                          Quantity，离散输入量个数
**                          ReaValuePtr，保存离散输入量值的指针
** Returned value:          完成代码：(见modbus.h文件的异常代码表)
**
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U MB_UartReadDisInputs02(INT8U  ch,
                      INT8U  ID,
                      INT16U StartAddress,
                      INT16U Quantity,
                      INT8U *ReaValuePtr);
                      
#define OSReadDisInputs        MB_UartReadDisInputs02

/*********************************************************************************************************
** Function name:           MB_UartReadHoldReg03
**
** Descriptions:            读取保持寄存器值，指令代码为：0x03。
**
** input parameters:        ch,Modbus通讯管道
**                          ID，从机地址
**                          StartAddress，寄存器起始地址
**                          Quantity，寄存器数量
**                          ReaValuePtr，保存读出寄存器值的指针
** Returned value:          完成代码：(见modbus.h文件的异常代码表)
**
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern INT8U MB_UartReadHoldReg03(INT8U ch,
                    INT8U ID,
                    INT16U StartAddress,
                    INT16U Quantity,
                    INT16U *ReaValuePtr);                               /* 读保持寄存器                 */

#define OSReadHoldReg    MB_UartReadHoldReg03

/*********************************************************************************************************
** Function name:           MB_UartReadInputReg04
**
** Descriptions:            读取输入寄存器值，指令代码为：0x04。
**
** input parameters:        ch,Modbus通讯管道
**                          ID，从机地址
**                          StartAddress，输入寄存器起始地址
**                          Quantity，输入寄存器数量
**                          ReaValuePtr，保存读出输入寄存器值的指针
** Returned value:          完成代码：(见modbus.h文件的异常代码表)
**
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern INT8U MB_UartReadInputReg04( INT8U  ch,
                      INT8U  ID,
                      INT16U StartAddress,
                      INT16U Quantity,
                      INT16U *ReaValuePtr);
 #define OSReadInputReg        MB_UartReadInputReg04

/*********************************************************************************************************
** Function name:           MB_UartWriteSingleCoil05
**
** Descriptions:            写单线圈操作，指令代码为：0x04。
**
** input parameters:        ch,Modbus通讯管道
**                          ID，从机地址
**                          OutAddress，写入线圈的地址(0x0000~0xffff)
**                          OutValue，写入线圈的值COIL_OFF、COIL_ON
** Returned value:          完成代码：(见modbus.h文件的异常代码表)
**
** Created by:              ZhouLishan
** Created Date:            2006/06/06
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern INT8U MB_UartWriteSingleCoil05(INT8U ch,
                        INT8U  ID,
                        INT16U OutAddress,
                        INT16U OutValue);
 #define OSWriteSingleCoil    MB_UartWriteSingleCoil05
 
/*********************************************************************************************************
** Function name:           MB_UartWriteSingleReg06
**
** Descriptions:            写单寄存器操作。0x06
**
** input parameters:        ch,Modbus通讯管道
**                          ID，从机地址
**                          OutAddress，写入的地址(0x0000~0xffff)
**                          OutValue，写入的值(0x0000~0xffff)
** Returned value:          完成代码：(见modbus.h文件的异常代码表)
**
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern INT8U MB_UartWriteSingleReg06(INT8U ch,
                       INT8U  ID,
                       INT16U OutAddress,
                       INT16U OutValue);



/*********************************************************************************************************
** Function name:           MB_UartWriteMultipleCoils15
**
** Descriptions:            写多线圈操作。0x0f
**
** input parameters:        ch,Modbus通讯管道
**                          ID，从机地址
**                          StartAddress，写入线圈的起始地址(0x0000~0xffff)
**                          Quantity，写入的线圈的数量
**                          *ValuePtr，写入数据的指针
** Returned value:          完成代码：(见modbus.h文件的异常代码表)
**
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern INT8U  MB_UartWriteMultipleCoils15(INT8U ch,
                            INT8U ID,
                            INT16U StartAddress,
                            INT16U Quantity,
                            INT8U *ValuePtr);
                            
#define WriteMultipleCoils0f     MB_UartWriteMultipleCoils15
#define WriteMultipleCoils0F     MB_UartWriteMultipleCoils15
#define OSWriteMultipleCoils     MB_UartWriteMultipleCoils15

/*********************************************************************************************************
** Function name:           MB_UartWriteMultipleReg16
**
** Descriptions:            写多寄存器操作。0x10
**
** input parameters:        ch,Modbus通讯管道
**                          ID，从机地址
**                          StartAddress，写入寄存器的起始地址(0x0001~0xffff)
**                          Quantity，写入寄存器的数量(0x0001~0x0078)
**                          *ValuePtr，写入寄存器数据的指针
** Returned value:          完成代码：(见modbus.h文件的异常代码表)
**
** Created by:              ZhouLishan
** Created Date:            2006/06/06
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern INT8U  MB_UartWriteMultipleReg16(INT8U  ch,
                          INT8U  ID,
                          INT16U StartAddress,
                          INT16U Quantity,
                          INT16U *ValuePtr)    ;


/*********************************************************************************************************
** Function name:           MB_UartMaskWriteReg22
**
** Descriptions:            屏蔽写寄存器操作。如果Or_Mask值为零，那么结果是当前内容和And_Mask的简单
**                          逻辑AND（与）；如果And_Mask值为零，结果等于Or_Mask值。0x16
**
** input parameters:        ch,Modbus通讯管道
**                          ID，从机地址
**                          Addr，写入寄存器的地址(0x0001~0xffff)
**                          And_Mask，屏蔽写与数据
**                          Or_Mask，屏蔽写或数据
** Returned value:          完成代码：(见modbus.h文件的异常代码表)
**
** Created by:              ZhouLishan
** Created Date:            2006/06/06
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern INT8U  MB_UartMaskWriteReg22(INT8U  ch,
                      INT8U  ID,
                      INT16U Addr,
                      INT16U And_Mask,
                      INT16U Or_Mask);
                      
#define OSMaskWriteReg     MB_UartMaskWriteReg22
#define MaskWriteReg16     MB_UartMaskWriteReg22


/*********************************************************************************************************
** Function name:           ReadWriteMultipleReg23
**
** Descriptions:            同时写读多寄存器操作，先写入后读出。0x17
**
** input parameters:        ch,Modbus通讯管道
**                          ID，从机地址
**                          WStartAddr，写入寄存器的起始地址(0x0001~0xffff)
**                          WQuantity，写入寄存器的数量
**                          RStartAddr，读出寄存器的起始地址(0x0001~0xffff)
**                          RQuantity，读出寄存器的数量
**                          *DataPtr，写入寄存器的指针和读出数据存放指针
** Returned value:          完成代码：(见modbus.h文件的异常代码表)
**
** Created by:              ZhouLishan
** Created Date:            2006/06/06
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U  ReadWriteMultipleReg23(INT8U   ch,
                              INT8U   ID,
                              INT16U  WStartAddr,
                              INT16U  WQuantity,
                              INT16U  RStartAddr,
                              INT16U  RQuantity,
                              INT16U *DataPtr);
                              
#define OSReadWriteMultipleReg     ReadWriteMultipleReg23
#define ReadWriteMultipleReg17     ReadWriteMultipleReg23

#ifdef __cplusplus
}
#endif                                                                  /* __cplusplus                  */
#endif                                                                  /* __REQUESTFUN_H               */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
