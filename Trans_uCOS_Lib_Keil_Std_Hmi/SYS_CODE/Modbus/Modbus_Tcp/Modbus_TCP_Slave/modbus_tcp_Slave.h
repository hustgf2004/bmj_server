/****************************************Copyright (c)**************************************************
**                               Guangzou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File Name:           MODBUS_TCP.h
** Last modified Date:  2006-9-13
** Last Version:        1.0
** Descriptions:        MODBUS_TCP HEAD FILE
**
**------------------------------------------------------------------------------------------------------
** Created By: liudikai
** Created date:   2006-11-10
** Version: 1.0
** Descriptions: First version
**
**------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
********************************************************************************************************/
#ifndef __MODBUS_TCP_SLAVE_H
#define __MODBUS_TCP_SLAVE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MODBUS_TCP_GLOBALS
#define MODBUS_TCP_EXT
#else
#define MODBUS_TCP_EXT extern
#endif


/*********************************************************************************************************
**                       modbus 功能配置选项
*********************************************************************************************************/
#define MODBUS_SERVER_INSIDE_EN         1

#if MODBUS_SERVER_INSIDE_EN

/*********************************************************************************************************
** Define which Function code be use in the Modbus Master Protocol Stac
*********************************************************************************************************/                                                                        /* k .                          */
#define    TCP_READ_COILS_EN            1                               /* 读线圈                       */
#define    TCP_READ_DIS_INPUT_EN        1                               /* 读离散量输入                 */
#define    TCP_READ_HOLD_REG_EN         1                               /* 读保持寄存器                 */
#define    TCP_READ_INPUT_REG_EN        1                               /* 读输入寄存器                 */
#define    TCP_WRITE_SING_COIL_EN       1                               /* 写单个线圈                   */
#define    TCP_WRITE_SING_REG_EN        1                               /* 写单个寄存器                 */
#define    TCP_WRITE_MULT_COIL_EN       1                               /* 写多个线圈                   */
#define    TCP_WRITE_MULT_REG_EN        1                               /* 写多个寄存器                 */
#define    TCP_MASK_WRITE_REG_EN        1                               /* 处理屏蔽寄存器指令           */
#define    TCP_READ_WRITE_REG_EN        1                               /* 读写多个寄存器               */

#endif


/*********************************************************************************************************
** modbus 功能码
*********************************************************************************************************/    
#define READ_COILS                      1
#define READ_DIS_INPUT                  2
#define READ_MUL_REGS                   3
#define READ_INPUT_REG                  4
#define WRITE_SING_COIL                 5
#define WRITE_SING_REG                  6
#define WRITE_MULT_COIL                 15
#define WRITE_MULT_REG                  16
#define MASK_WRITE_REG                  22
#define READ_WRITE_REG                  23

/*********************************************************************************************************
** 函数返回出错代码  Modbus协议定义的出错代码
*********************************************************************************************************/ 
#define MB_NO_ERR                     0x00                              /* 无错误                       */
#define ILLEGAL_FUNCTION              0x01                              /* 无效功能代码                 */
#define ILLEGAL_DATA_ADDR             0x02                              /* 无效地址                     */
#define ILLEGAL_DATA_VALUE            0x03                              /* 无效数据值                   */
#define SLAVE_DEVICE_FAILURE          0x04                              /* 从设备出错                   */
#define ACKNOWLEDGE                   0x05
#define SLAVE_DEVICE_BUSY             0x06
#define MEMORY_PARITY_ERR             0x08
#define GATEWAY_PATH_UNABLE           0x0A
#define GATEWAY_TARGET_DEV_FAIL       0x0B
#define MB_TREATED_WRONG              -1

/*********************************************************************************************************
** 设置用户访问函数 (由用户编写)
*********************************************************************************************************/ 
#define MODBUS_SLAVER_INSIDE_EN        1

extern  uint8 MB_TCP_GetDiscrete (uint8 ch,uint8 *DisInputsV,uint16 Address);   /* 获取线圈值           */
extern  uint8 MB_TCP_GetCoils    (uint8 ch,uint8 *DisInputsV,uint16 Address);   /* 获取线圈值           */
extern  uint8 MB_TCP_SetCoil     (uint8 ch,uint16 Address,uint8 CoilValue);     /* 设置线圈值           */
extern  uint8 MB_TCP_GetInputRegValue(uint8 ch,uint16 *ValuePtr,uint16 Address);/* 读输入寄存器值       */                                                                      
extern  uint8 MB_TCP_GetRegValue (uint8 ch,uint16 *ValuePtr,uint16 Address);    /* 读保持寄存器值       */                                                                       
extern  uint8 MB_TCP_SetRegValue (uint8 ch,uint16 Address,uint16 Value);        /* 写保持寄存器值       */
                                                                        
/********************************************************************************************************
**                             Structure Define
********************************************************************************************************/

typedef struct __RW_PARAMET
{
    uint8      ch;                                                      /* ch,Modbus通讯管道            */
    uint16     RStartAddr;                                              /* 读起始地址                   */
    uint16     RQuantity;                                               /* 读数量                       */
    uint16     WStartAddr;                                              /* 写起始地址                   */
    uint16     WQuantity;                                               /* 写数量                       */
                                                                  /* uint16 *DataPtr; 保存或设置值的指针*/

}RW_PARAMET,READ_PARAMET,WRITE_PARAMET;

typedef struct
{
    int16    Treated_len;
    int16    Send_len;
}MOD_LEN;

/*********************************************************************************************************
** MODBUS_TCP任务函数
*********************************************************************************************************/ 
    MODBUS_TCP_EXT MOD_LEN ModbusTcp_Server_Process(uint8 *modbus_req,uint8 *modbus_resp);
#ifdef __cplusplus
    extern "}"
#endif
#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
