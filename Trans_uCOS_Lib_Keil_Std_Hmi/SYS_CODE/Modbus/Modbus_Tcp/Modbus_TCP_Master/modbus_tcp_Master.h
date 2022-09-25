/****************************************Copyright (c)**************************************************
**                               Guangzou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:           MODBUS_TCP_MASTER.h
** Last modified Date:  2008-3-17
** Last Version:        1.0
** Descriptions:        modbus_tcp_client_function source file
**------------------------------------------------------------------------------------------------------
** Created by:          liudikai
** Created date:        2008-3-17
** Version:             1.0
** Descriptions:        The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
********************************************************************************************************/
#ifndef __MODBUS_TCP_MASTER_H
#define __MODBUS_TCP_MASTER_H

#ifdef __cplusplus
extern "C" {
#endif


#ifdef MODBUS_TCP_GLOBALS
#define MODBUS_TCP_EXT

#else
#define MODBUS_TCP_EXT extern
#endif

#if MODBUS_TCP_MASTER_INSIDE_EN
/*********************************************************************************************************
** Function name:           MB_TCP_ReadCoils
**
** Descriptions:            读取线圈值。0x01
**
** input parameters:        Link_num,       TCP连接号
**                          ID，            从机地址
**                          StartAddress，  线圈起始地址
**                          Quantity，      线圈数量
**                          ReaValuePtr，   保存线圈值的指针
**                          time_out，      响应超时时间，单位ms
** Returned value:          完成代码：      (见modbus.h文件的异常代码表)
**
** Created by:              Liudikai
** Created Date:            2008-03-18
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#if    MB_TCP_READ_COILS_EN
MODBUS_TCP_EXT uint8  MB_TCP_ReadCoils( uint8  Link_num,
                                        uint8  ID,
                                        uint16 StartAddress,
                                        uint16 Quantity,
                                        uint8  *ReaValuePtr,
                                        uint16 time_out );
#endif
/*********************************************************************************************************
** Function name:           MB_TCP_ReadDisInputs
**
** Descriptions:            读取离散输入量。0x02
**
** input parameters:        Link_num,       TCP连接号
**                          ID，            从机地址
**                          StartAddress，  离散输入量起始地址
**                          Quantity，      离散输入量个数
**                          ReaValuePtr，   保存离散输入量值的指针
**                          time_out，      响应超时时间，单位ms
** Returned value:          完成代码：      (见modbus.h文件的异常代码表)
**
** Created by:              Liudikai
** Created Date:            2008-03-18
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#if    MB_TCP_READ_DIS_INPUT_EN
MODBUS_TCP_EXT uint8  MB_TCP_ReadDisInputs( uint8  Link_num,
                                            uint8  ID,
                                            uint16 StartAddress,
                                            uint16 Quantity,
                                            uint8  *ReaValuePtr,
                                            uint16 time_out );
#endif
/*********************************************************************************************************
** Function name:           MB_TCP_ReadHoldReg
**
** Descriptions:            读取保持寄存器值，指令代码为：0x03。
**
** input parameters:        Link_num,        TCP连接号
**                          ID，             从机地址
**                          StartAddress，   寄存器起始地址
**                          Quantity，       寄存器数量
**                          ReaValuePtr，    保存读出寄存器值的指针
**                          time_out，       响应超时时间，单位ms
** Returned value:          完成代码：       (见modbus.h文件的异常代码表)
**
** Created by:              Liudikai
** Created Date:            2008-03-18
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#if    MB_TCP_READ_HOLD_REG_EN
MODBUS_TCP_EXT  uint8  MB_TCP_ReadHoldReg(  uint8  Link_num,
                                            uint8  ID,
                                            uint16 StartAddress,
                                            uint16 Quantity,
                                            uint16 *ReaValuePtr,
                                            uint16 time_out );
#endif
/*********************************************************************************************************
** Function name:           MB_TCP_ReadInputReg
**
** Descriptions:            读取输入寄存器值，指令代码为：0x04。
**
** input parameters:        Link_num,         TCP连接号
**                          ID，              从机地址
**                          StartAddress，    输入寄存器起始地址
**                          Quantity，        输入寄存器数量
**                          ReaValuePtr，     保存读出输入寄存器值的指针
**                          time_out，        响应超时时间，单位ms
** Returned value:          完成代码：        (见modbus.h文件的异常代码表)
**
** Created by:              Liudikai
** Created Date:            2008-03-18
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#if    MB_TCP_READ_INPUT_REG_EN
MODBUS_TCP_EXT  uint8  MB_TCP_ReadInputReg( uint8  Link_num,
                                            uint8  ID,
                                            uint16 StartAddress,
                                            uint16 Quantity,
                                            uint16 *ReaValuePtr,
                                             uint16 time_out );
#endif
/*********************************************************************************************************
** Function name:           MB_TCP_WriteSingleCoil
**
** Descriptions:            写单线圈操作，指令代码为：0x05。
**
** input parameters:        Link_num,       TCP连接号
**                          ID，            从机地址
**                          OutAddress，    写入线圈的地址(0x0000~0xffff)
**                          OutValue，      写入线圈的值COIL_OFF、COIL_ON
**                          time_out，      响应超时时间，单位ms
** Returned value:          完成代码：      (见modbus.h文件的异常代码表)
**
** Created by:              Liudikai
** Created Date:            2008-03-18
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#if    MB_TCP_WRITE_SING_COIL_EN
MODBUS_TCP_EXT  uint8  MB_TCP_WriteSingleCoil(  uint8  Link_num,
                                                uint8  ID,
                                                uint16 OutAddress,
                                                uint16 OutValue,
                                                uint16 time_out );
#endif
/*********************************************************************************************************
** Function name:           MB_TCP_WriteSingleReg
**
** Descriptions:            写单寄存器操作。0x06
**
** input parameters:        Link_num,       TCP连接号
**                          ID，            从机地址
**                          OutAddress，    写入的地址(0x0000~0xffff)
**                          OutValue，      写入的值(0x0000~0xffff)
**                          time_out，      响应超时时间，单位ms
** Returned value:          完成代码：      (见modbus.h文件的异常代码表)
**
** Created by:              Liudikai
** Created Date:            2008-03-18
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#if    MB_TCP_WRITE_SING_REG_EN
MODBUS_TCP_EXT uint8  MB_TCP_WriteSingleReg(  uint8  Link_num,
                                              uint8  ID,
                                              uint16 OutAddress,
                                              uint16 OutValue,
                                              uint16 time_out );
#endif
/*********************************************************************************************************
** Function name:           MB_TCP_WriteMultipleCoils
**
** Descriptions:            写多线圈操作。0x0f
**
** input parameters:        Link_num,         TCP连接号
**                          ID，              从机地址
**                          StartAddress，    写入线圈的起始地址(0x0000~0xffff)
**                          Quantity，        写入的线圈的数量
**                         *ValuePtr，        写入数据的指针
**                          time_out，        响应超时时间，单位ms
** Returned value:          完成代码：        (见modbus.h文件的异常代码表)
**
** Created by:              Liudikai
** Created Date:            2008-03-18
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#if    MB_TCP_WRITE_MULT_COIL_EN
MODBUS_TCP_EXT  uint8  MB_TCP_WriteMultipleCoils( uint8  Link_num,
                                                  uint8  ID,
                                                  uint16 StartAddress,
                                                  uint16 Quantity,
                                                  uint8  *ValuePtr,
                                                  uint16 time_out );
#endif
/*********************************************************************************************************
** Function name:           MB_TCP_WriteMultipleReg
**
** Descriptions:            写多寄存器操作。0x10
**
** input parameters:        Link_num,         TCP连接号
**                          ID，              从机地址
**                          StartAddress，    写入寄存器的起始地址(0x0001~0xffff)
**                          Quantity，        写入寄存器的数量(0x0001~0x0078)
**                         *ValuePtr，        写入寄存器数据的指针
**                          time_out，        响应超时时间，单位ms
** Returned value:          完成代码：        (见modbus.h文件的异常代码表)
**
** Created by:              Liudikai
** Created Date:            2008-03-18
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#if    MB_TCP_WRITE_MULT_REG_EN
MODBUS_TCP_EXT  uint8  MB_TCP_WriteMultipleReg( uint8  Link_num,
                                                uint8  ID,
                                                uint16 StartAddress,
                                                uint16 Quantity,
                                                uint16 *ValuePtr,
                                                uint16 time_out );
#endif
/*********************************************************************************************************
** Function name:           MB_TCP_MaskWriteReg
**
** Descriptions:            屏蔽写寄存器操作。如果Or_Mask值为零，那么结果是当前内容和And_Mask的简单
**                          逻辑AND（与）；如果And_Mask值为零，结果等于Or_Mask值。0x16
**
** input parameters:        Link_num,        TCP连接号
**                          ID，             从机地址
**                          Addr，           写入寄存器的地址(0x0001~0xffff)
**                          And_Mask，       屏蔽写与数据
**                          Or_Mask，        屏蔽写或数据
**                          time_out，       响应超时时间，单位ms
** Returned value:          完成代码：       (见modbus.h文件的异常代码表)
**
** Created by:              Liudikai
** Created Date:            2008-03-18
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#if    MB_TCP_MASK_WRITE_REG_EN
MODBUS_TCP_EXT  uint8  MB_TCP_MaskWriteReg( uint8  Link_num,
                                            uint8  ID,
                                            uint16 Addr,
                                            uint16 And_Mask,
                                            uint16 Or_Mask,
                                            uint16 time_out );
#endif
/*********************************************************************************************************
** Function name:           MB_TCP_ReadWriteMultipleReg
**
** Descriptions:            同时写读多寄存器操作，先写入后读出。0x17
**
** input parameters:        Link_num,        TCP连接号
**                          ID，             从机地址
**                          WStartAddr，     写入寄存器的起始地址(0x0001~0xffff)
**                          WQuantity，      写入寄存器的数量
**                          RStartAddr，     读出寄存器的起始地址(0x0001~0xffff)
**                          RQuantity，      读出寄存器的数量
**                         *DataPtr，        写入寄存器的指针和读出数据存放指针
**                          time_out，       响应超时时间，单位ms
** Returned value:          完成代码：       (见modbus.h文件的异常代码表)
**
** Created by:              Liudikai
** Created Date:            2008-03-18
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#if    MB_TCP_READ_WRITE_REG_EN
MODBUS_TCP_EXT  uint8  MB_TCP_ReadWriteMultipleReg( uint8 Link_num,
                                                    uint8 ID,
                                                    uint16 WStartAddr,
                                                    uint16 WQuantity,
                                                    uint16 RStartAddr,
                                                    uint16 RQuantity,
                                                    uint16 *DataPtr,
                                                    uint16 time_out );
#endif
#endif

#ifdef __cplusplus
    extern "}"
#endif
#endif
/********************************************************************************************************
**                                            End Of File
********************************************************************************************************/
