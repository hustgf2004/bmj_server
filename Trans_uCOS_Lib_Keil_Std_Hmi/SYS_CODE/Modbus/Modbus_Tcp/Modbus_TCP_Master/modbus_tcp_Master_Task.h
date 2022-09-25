/****************************************Copyright (c)**************************************************
**                               Guangzou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File Name:           modbus_tcp_Master_Task.h
** Last modified Date:  2008-3-17
** Last Version:        1.0
** Descriptions:        MODBUS_TCP_CLIENT HEAD FILE
**
**------------------------------------------------------------------------------------------------------
** Created By:          liudikai
** Created date:        2008-3-17
** Version:             1.0
** Descriptions:        First version
**
**------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
********************************************************************************************************/
#ifndef __MODBUS_TCP_MASTER_TASK_H
#define __MODBUS_TCP_MASTER_TASK_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MODBUS_TCP_GLOBALS
#define MODBUS_TCP_EXT
#else
#define MODBUS_TCP_EXT extern
#endif
/*******************************************************************************************************
**                             modbus功能码
*******************************************************************************************************/
#define READ_COILS                                1
#define READ_DIS_INPUT                            2
#define READ_MUL_REGS                             3
#define READ_INPUT_REG                            4
#define WRITE_SING_COIL                           5
#define WRITE_SING_REG                            6
#define WRITE_MULT_COIL                           15
#define WRITE_MULT_REG                            16
#define MASK_WRITE_REG                            22
#define READ_WRITE_REG                            23
/********************************************************************************************************
**                          MODBUS/TCP主机功能使能
********************************************************************************************************/
#define MODBUS_TCP_MASTER_INSIDE_EN               1
#if MODBUS_TCP_MASTER_INSIDE_EN
#define    MB_TCP_READ_COILS_EN                   1                     /* 读线圈                       */
#define    MB_TCP_READ_DIS_INPUT_EN               1                     /* 读离散量输入                 */
#define    MB_TCP_READ_HOLD_REG_EN                1                     /* 读保持寄存器                 */
#define    MB_TCP_READ_INPUT_REG_EN               1                     /* 读输入寄存器                 */
#define    MB_TCP_WRITE_SING_COIL_EN              1                     /* 写单个线圈                   */
#define    MB_TCP_WRITE_SING_REG_EN               1                     /* 写单个寄存器                 */
#define    MB_TCP_WRITE_MULT_COIL_EN              1                     /* 写多个线圈                   */
#define    MB_TCP_WRITE_MULT_REG_EN               1                     /* 写多个寄存器                 */
#define    MB_TCP_MASK_WRITE_REG_EN               1                     /* 处理屏蔽寄存器指令           */
#define    MB_TCP_READ_WRITE_REG_EN               1                     /* 读写多个寄存器               */
#endif
/********************************************************************************************************
**                          MODBUS/TCP主机出错码
********************************************************************************************************/
#define MB_NO_ERR                                 0x00                  /* 无错误                       */
#define ILLEGAL_FUNCTION                          0x01                  /* 无效功能代码                 */
#define ILLEGAL_DATA_ADDR                         0x02                  /* 无效地址                     */
#define ILLEGAL_DATA_VALUE                        0x03                  /* 无效数据值                   */
#define SLAVE_DEVICE_FAILURE                      0x04                  /* 从设备出错                   */
#define ACKNOWLEDGE                               0x05                  /* 确认                         */
#define SLAVE_DEVICE_BUSY                         0x06                  /* 从设备忙                     */
#define MEMORY_PARITY_ERR                         0x08                  /* 存储效验失败                 */
#define GATEWAY_PATH_UNABLE                       0x0A                  /* 网关路径不可用               */
#define GATEWAY_TARGET_DEV_FAIL                   0x0B                  /* 网关目标设备响应失败         */
                                                                        /* ZY/ModbusTcp协议栈定义出错代 */
                                                                        /* 码                           */
#define MODBUS_TCP_FUN_NOT_DEF                    0x90                  /* 未定义功能代码               */
#define MODBUS_TCP_PARAMETER_ERR                  0x91                  /* 参数出错                     */
#define MODBUS_TCP_THE_CH_BUSY                    0x92                  /* 管道忙，正被使用             */
#define MODBUS_TCP_RESPONSE_TIME_OUT              0x93                  /* 应答超时                     */
#define MODBUS_TCP_PARITY_FUN_ERR                 0x94                  /* 应答功能码出错               */
#define MODBUS_TCP_SEND_ERROR                     0x95                  /* 发送请求帧失败               */
#define MODBUS_TCP_RECV_ERROR                     0x96                  /* 接收应答帧失败               */

/********************************************************************************************************
**                          MODBUS/TCP主机状态码
********************************************************************************************************/
                                                                        /* #define COIL_OFF  0          */
                                                                        /* #define COIL_ON   0xff00     */


#define MB_TCP_WAITE_HANDLE                       0xB0                  /* 空闲状态                     */
#define MB_TCP_RECEIVE_DATA                       0xB1                  /* 接收应答数据                 */
#define MB_TCP_SEND_DATA                          0xB2                  /* 发送请求                     */
#define MB_TCP_TIME_OUT_HANDLE                    0xB3                  /* 响应超时                     */
#define MB_TCP_WAITING_FOR_REPLY                  0xB4                  /* 等待应答                     */
#define MB_TCP_REPLY_RIGHT                        0xB5                  /* 应答正确                     */
#define MB_TCP_DELETE_EVENT_HANDLE                0xB6                  /* 删除该事件                   */
#define MB_TCP_WAITE_FOR_DELETE                   0xB7                  /* 等待删除该事件               */

/********************************************************************************************************
**                          MODBUS/TCP主机处理任务
********************************************************************************************************/
#define TASK_MB_TCP_MASTER_ID                     6
#define TASK_MB_TCP_MASTER_PRIO                   6
#define TASK_MB_TCP_MASTER_STACK_SIZE             128
    MODBUS_TCP_EXT OS_STK task_mb_tcp_master_stack[TASK_MB_TCP_MASTER_STACK_SIZE];
/********************************************************************************************************
**                             Structure Define
********************************************************************************************************/
typedef struct
{
    uint8     Link_Num;                                                 /* modbus_tcp连接号             */
    uint8     state;                                                    /* modbus通道状态               */
    uint8     resent_id;                                                /* 当前ID号                     */
    uint8     function;                                                 /* 当前功能码                   */
    uint16    unit_id_num;                                              /* modbus_tcp事务处理标识符     */
    uint16    timeout;                                                  /* modbus_tcp超时时间值         */
    uint16    Time_Tick;                                                /* modbus_tcp超时应答计时，     */
                                                                        /* 单位：ms(毫秒)               */
    uint8     Modbus_Tcp_RecBuf[MAX_MB_TCP_REC_BUF_SIZE];               /* modbus_tcp接收缓存区         */
    uint8     Modbus_Tcp_SenBuf[MAX_MB_TCP_SEN_BUF_SIZE];               /* modbus_tcp发送缓存区         */
    uint8    *user_buf_ptr;                                             /* modbus_tcp用户保存数据地址指 */
                                                                        /* 针                           */
    uint16    send_len;                                                 /* modbus_tcp发送帧长度         */
    uint8     ret;                                                      /* modbus_tcp返回值             */
    OS_EVENT  *mbm_handle_event_ptr;                                    /* modbus_tcp访问信号量         */
    OS_EVENT  *mbm_handle_event_over_ptr;                               /* modbus_tcp等待回应信号量     */

    uint16    RStartAddr;                                               /* 读起始地址                   */
    uint16    RQuantity;                                                /* 读数量                       */
    uint16    WStartAddr;                                               /* 写起始地址                   */
    uint16    WQuantity;                                                /* 写数量                       */
}MODBUS_TCP_S;

    MODBUS_TCP_EXT INT8U  Modbus_Tcp_MasterInit(void);

    MODBUS_TCP_EXT void   MB_TCP_TimeHandle(void);
#ifdef __cplusplus
    extern "}"
#endif
#endif
/********************************************************************************************************
**                              End Of File
********************************************************************************************************/