/****************************************Copyright (c)**************************************************
**                               Guangzou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File Name:           MODBUS_TCP_TASK.h
** Last modified Date:  2006-9-13
** Last Version:        1.0
** Descriptions:        modbus_tcp_Slave_task HEAD FILE
**
**------------------------------------------------------------------------------------------------------
** Created By:     liudikai
** Created date:   2006-11-16
** Version:        1.0
** Descriptions:   First version
**
**------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
********************************************************************************************************/
#ifndef  __MODBUS_TCP_TASK
#define  __MODBUS_TCP_TASK

#ifdef  MODBUS_TCP_TASK_GLOBALS
#define MODBUS_TCP_TASK_EXT
#else
#define MODBUS_TCP_TASK_EXT extern
#endif

/********************************************************************************************************
**                             modbus_tcp主任务相关配置
********************************************************************************************************/
#define         MODBUS_TCP_TASK_ID        10
#define         MODBUS_TCP_TASK_PRIO      MODBUS_TCP_TASK_ID
#define         MODBUS_TCP_TASK_SIZE      500
/********************************************************************************************************
**                             modbus_tcp从任务相关配置
********************************************************************************************************/
#define MAX_MB_TCP_TASK MAX_MB_TCP_LINK
#define MAX_MB_TCP_TASK_PRIO      (MODBUS_TCP_TASK_PRIO - MAX_MB_TCP_LINK)
#define MB_TCP_TASK_STACK_SIZE    128
#define MAX_MB_TCP_REC_BUF_SIZE   900
#define MAX_MB_TCP_SEN_BUF_SIZE   260
/********************************************************************************************************
**                             modbus_tcp连接配置
********************************************************************************************************/
#define MAX_MB_TCP_LINK           2
#define MAX_MB_LINK_PER_IP        2
#define MB_TCP_LINK_TIMEOUT       75000


/********************************************************************************************************
**                             Structure Define
********************************************************************************************************/
typedef struct
{
    uint8   Modbus_Num;
    uint8   Task_Prio;
    uint8   Link_Num;
    uint8   Task_sta;
    uint8   ip[4];
    uint32  Time_tick;
}MODBUS_TCB_S;

/********************************************************************************************************
**                             VARIABLES Define
********************************************************************************************************/
MODBUS_TCP_EXT OS_STK     modbus_tcp_stack[MODBUS_TCP_TASK_SIZE];
                                                                        /* modbus_tcp主任务堆栈         */
MODBUS_TCP_EXT MODBUS_TCB_S MODBUS_TCP_SEV[MAX_MB_TCP_TASK];
MODBUS_TCP_EXT OS_STK modbus_tcp_task_stack[MAX_MB_TCP_TASK][MB_TCP_TASK_STACK_SIZE];
MODBUS_TCP_EXT uint8  MB_Rec_Buf[MAX_MB_TCP_TASK][MAX_MB_TCP_REC_BUF_SIZE];
MODBUS_TCP_EXT uint8  MB_Sen_Buf[MAX_MB_TCP_TASK][MAX_MB_TCP_SEN_BUF_SIZE];

/********************************************************************************************************
**                             FUNCTIONS Define
********************************************************************************************************/
MODBUS_TCP_EXT INT8U Modbus_Tcp_SlaveInit(uint8* IDRange);
MODBUS_TCP_EXT void  Modbus_Tcp_task(void *pdata);

#endif                                                                  /* __MODBUS_TCP_TASK            */