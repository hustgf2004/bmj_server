/****************************************Copyright (c)****************************************************
**                               
**                                      
**                                 
**
**--------------------------------------------------------------------------------------------------------
** File name:           ModbusUser.h
** Last modified Date:  2013-11-30
** Last Version:        2.0
** Descriptions:        Modbus软件驱动用户使用的宏定义及部分函数声明。
**
**--------------------------------------------------------------------------------------------------------
** Created by:          
** Created date:        2013-11-30
** Version:             2.0
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:             
** Descriptions:
**
*********************************************************************************************************/
#ifndef __MODBUSUSER_H
#define __MODBUSUSER_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************************************************
    Modbus协议定义的出错代码
*********************************************************************************************************/
#define EXCEPTION_CODE_1              1
#define EXCEPTION_CODE_2              2
#define EXCEPTION_CODE_3              3
#define EXCEPTION_CODE_4              4
#define EXCEPTION_CODE_5              5
#define EXCEPTION_CODE_6              6

/*********************************************************************************************************
    函数返回出错代码
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

/*********************************************************************************************************
    ZY/Modbus协议栈自定义出错代码
*********************************************************************************************************/
#define MB_FUN_NOT_DEF                0x80                              /* 未定义功能代码               */
#define MB_THE_CH_BUSY                0x81                              /* 管道忙，正被使用             */
#define MB_RESPONSE_TIME_OUT          0x82                              /* 应答超时                     */
#define MB_PARAMETER_ERR              0x83                              /* 参数出错                     */
#define MB_INVALID_CH                 0x84                              /* 无效的管道                   */
#define MB_INVALID_MOD                0x85                              /* 无效的模式                   */
#define MB_INVALID_BAUD               0x85                              /* 无效的波特率                 */
#define MB_MALLOC_ERR                 0x86                              /* 分配内存出错                 */
#define MB_OS_EVENT                   0x87                              /* 申请OS资源出错               */

/*********************************************************************************************************
                      以上为出错返回代码
                以下为ZY/Modbus2.0协议栈状态码
*********************************************************************************************************/
#define MB_SENT_REQUEST               0x90                              /* 发送请求                     */
#define MB_WAITE_RESPONSIONING        0x91                              /* 正在处理                     */
#define MB_POLL_DELAY                 0x92
#define MB_WAITING_POLL_DELAY         0x93
#define MB_WAITING_FOR_REPLY          0x94
#define MB_WAITING_SENDING            0x95
#define MB_PROCESSING_REPLY           0x96                              /* 应答处理                     */
#define MB_WAITE_HANDLE               0x97                              /* 等待处理                     */
#define MB_RESPONSIONING_HANDLE       0x98

#define MB_DELETE_EVENT_LIST          0x99                              /* 删除事件列表项               */
#define MB_RECEIVE_EVENT              0xA0                              /* 接收事件                     */
#define MB_RECEIVE_DATA               0xA1                              /* 接收数据                     */
#define MB_RECEIVE_FRAME              0xA2                              /*  从机接收到请求时，与
                                                                            MB_RESPONSIONING_HANDLE
                                                                            是一样的值                  */
#define MB_WAITE_RECEIVE              0xA3                              /* 等待接收数据状态             */
#define MB_SEND_EVENT                 0xA4                              /* 发送事件状态                 */
#define MB_SEND_DATA                  0xA5                              /* 发送数据状态                 */
#define MB_TIME_OUT_HANDLE            0xA6                              /* 超时处理                     */



/*********************************************************************************************************
    定义广播地址
*********************************************************************************************************/
#define    BROADCAST_ADDRESS          0



typedef struct __master_poll {
    OS_EVENT       *pSem;
    INT8U           ucChnl; 
    INT8U           ucId;
    INT8U           ucExceptionCode;
    INT8U         (*pfFunc2PDU)(void *pvPara);
    void          (*pfFuncParse)(INT8U *pucOut, void *pvIn);
    void           *pvPara;
    struct __master_poll *pNext;
    INT8U           ucRsv18;
    
} __MASTER_POLL, *__PMASTER_POLL; 



/*********************************************************************************************************
    PDU帧处理参数结构
*********************************************************************************************************/
typedef struct __PDU_RESPONSE{
    uint8*   PDUDataPtr;                                                /*  请求数据指针,功能代码处理函
                                                                            数必需将处理的数据包存在该
                                                                            指针的开始位始              */
    uint8    PDUByteLength;                                             /* 请求数据数长度               */
    uint8    ExceptionCode;                                             /*  仅为输出错异常代码，
                                                                            正常操作设为0               */
}PDU_RESPONSE;



/*********************************************************************************************************
    MODBUS设备配置参数数据结构
    应用程序初始化串口时使用该数据结构
*********************************************************************************************************/
typedef struct __MB_CFG{
    INT8U   ch;                                                         /* 配置管道号(0~MB_MAX_CH-1)    */
    INT8U   node_addr;                                                  /* 节点地址(1~255)，值为0表示为 */
                                                                        /* 主设备                       */
    INT8U   modbus_mode;                                                /* 链路层协议,MB_RTU_MODE('R'), */
                                                                        /* MB_ASC                       */
                                                                        /* II_MODE('A'),MB_TCP_MODE('T' */
                                                                        /* )                            */

    ////
    INT32U  BaudRate;                                                   /* 波特率(1200、2400、4800、9600*/
                                                                        /* 19200、38400、57600和115200) */
    ////
    INT8U   bits;                                                       /* 字符长度:00(5位字符)01(6位)10*/
                                                                        /* (7位)11(8位)                 */
    INT8U   parity;                                             /* 奇偶校验:0,无校验；1,奇校验;2,偶校验 */
    INT8U   stops;                                                      /* 停止位:0为1位，1为2位。      */

    INT8U   wr_en;                                                      /* 写使能（保留）               */
    
    ////
    /*
     *   新增数据结构
     */
    INT16U  usADUBufSize;                                               /* ADU缓冲区大小                */
    
    ////
    INT8U   *pucADUPtr;                                                 /* ADU缓冲区指针                */
    
    ////
    INT16U  usQSendSize;                                                /* 底层UART驱动发送缓冲区大小   */
    ////
    INT8U   *puqSendBuf;                                                /* 底层UART驱动发送缓冲区指针   */
    
    ////
    struct __MBDSTR *mbdPtr;                                            /* 驱动信息内存指针             */

    /*
     *   底层驱动信息数据结构
     */
    void    *pvDriver;
    INT8U   (*PortCfg)  (struct __MB_CFG *mb_ch);                       /* 如UART的驱动数据结构         */
    
    void    (*SendData) (INT8U ucCh,INT8U *ucBuf,INT16U usLen);
                                                                        /* 发送数据函数指针             */
    void    (*ExitPort) (void *pDriver);                                /* 退出Modbus配置时使用该函数   */
}MB_CFG;

/*********************************************************************************************************
    Modbus管道信息相关数据结构
*********************************************************************************************************/
typedef struct __MBDSTR {
    INT8U           ucChnl;                                             /*  通道号                      */// 0x00
    INT8U           ucNodeAddr;                                         /*  站号 0: 主站 1~255 从站     */// 0x01    
    INT8U           ucModbusMode;                                       /*  Modbus模式                  */// 0x02
    
    INT32U          uiBaudRate;                                         /*  串口波特率                  */// 0x04
    
    INT8U           ucDataBits;                                         /*  串口数据位                  */// 0x08
    INT8U           ucParity;                                           /*  串口校验方式                */// 0x09
    INT8U           ucStopBits;                                         /*  串口停止位                  */// 0x0A
    INT8U           ucWrEn;                                             /*  写使能                      */// 0x0B
    
    INT8U           ucT15Ticks;                                         /*  T15计数器                   */// 0x0C        
    INT8U           ucT35Ticks;                                         /*  T35计数器                   */// 0x0D
    INT16U          usAsciiRcvLen;                                      /*  ASCII接收长度               */// 0x0E     
    
    INT8U           ucIsAsciiRcvStart;                                  /*  ASCII接收起始标志           */// 0x10    
    INT8U           ucIsAsciiRcvEnd;                                    /*  ASCII接收完成标志           */// 0x11    
    INT8U           ucStatus;                                           /*  接收状态标志                */// 0x12     
    
    INT32U          uiResponseTime;                                     /*  主机请求超时计数器          */// 0x14    
    
    __MASTER_POLL  *pmpCurrent;                                         /*  当前要处理的主机请求        */// 0x18           
    
    void           *pvDriver;                                           /*  指向硬件驱动的指针          */// 0x1C     
                                                                        /*  数据发送函数指针            */// 0x20     
    void          (*pfSendData)(INT8U ucChnl, 
                                INT8U *pucBuf, 
                                INT16U usLen);
    
    //INT8U         (*pfPortCfg)(MB_CFG *pmc);                            /*  硬件端口配置函数指针        */// 0x24          
    void         (*pfExitPort)(void *pDriver);                         /*  硬件端口退出函数指针        */// 0x24   
    
    struct __MBDSTR*pmbdList;                                           /*  待处理的modbus通道          */// 0x28    
    
    INT8U          *pucPduData;                                         /*  PDU数据包指针               */// 0x2C    
    INT8U           ucIsReady;                                          /*  数据就绪标志                */// 0x30    
    INT8U           ucCmdCode;                                          /*  功能码                      */// 0x31    
    INT8U           ucPduDataLen;                                       /*  PDU数据长度                 */// 0x32    
    INT8U           ucExceptionCode;                                    /*  modbus管道异常代码          */// 0x33    
    INT16U          usAduBufSize;                                       /*  ADU数据长度                 */// 0x34    
    
    INT8U          *pucAduData;                                         /*  ADU数据指针                 */// 0x38    
    
    INT8U           ucDstAddr;                                          /*  数据请求目标站号            */// 0x3C     
    
    INT16U          usRtuRcvLen;                                        /*  RTU接收长度                 */// 0x3E    
    
    INT8U           ucIsRtuRcvStart;                                    /*  RTU接收起始标志             */// 0x40    
    INT8U           ucIsRtuRcvEnd;                                      /*  RTU接收完成标志             */// 0x41    
    
    __MASTER_POLL  *pmpList;                                            /*  主机请求的链表              */// 0x44     
    
    
    struct __MBDSTR*pNext;                                              /*  modbus通道双向链表的下一个  */// 0x48    
    struct __MBDSTR*pPrev;                                              /*  modbus通道双向链表的前一个  */// 0x4C    
    
}MBDSTR, *PMBDSTR;

/*********************************************************************************************************
    定义函数指针类型
*********************************************************************************************************/
typedef void  (*fptr)       (uint8  ch,PDU_RESPONSE *Response);
typedef uint8 (*f2pduptr)   (void  *ParameterPtr);
typedef void  (*f2parseptr) (uint8 *PDUPtr,void *ParameterPtr);


/*********************************************************************************************************
    Modsub从机自定义的功能码结构
    Modbus Slaver Protocol Stack use.
*********************************************************************************************************/
typedef struct _SUD_FUN_CODE{
    uint8     Code;                                                     /* 请求代码编号                 */
    void     *NextPtr;                                                  /*指向下一个用户定义功能代码指针*/
    void     (*Function)(uint8 ch,PDU_RESPONSE *Response);              /* 主机请求帧PCU数据处理函数    */
}SUD_FUN_CODE;

/*********************************************************************************************************
    Modsub主机自定义的功能码结构
    Modbus Master Protocol Stack use.
*********************************************************************************************************/
typedef struct _MUD_FUN_CODE{
    uint8     Code;                                                     /* 功能请求代码                 */
    void     *NextPtr;                                                  /* 指向下个用户定义功能代码指针 */
    uint8   (*f2pdu)( void *ParameterPtr );                             /* 封装请求帧的PDU数据函数指针  */
    void    (*f2parse)(uint8 *PDUPtr,void *ParameterPtr);
                                                                        /* 解析应答帧的PDU数据函数指针  */
}MUD_FUN_CODE;

/*********************************************************************************************************
    Modbus从机数据处理函数的函数指针数据结构
*********************************************************************************************************/
typedef struct __DATA_HANDLE_FUN {
    uint8 (*GetDiscrete)     (uint8 ch,uint8  *DisInputsV,uint16 Address);
    uint8 (*GetCoils)        (uint8 ch,uint8  *DisInputsV,uint16 Address);
    uint8 (*SetCoil)         (uint8 ch,uint16  Address,   uint8  CoilValue);
    uint8 (*GetInputRegValue)(uint8 ch,uint16 *ValuePtr,  uint16 Address);
    uint8 (*GetRegValue)     (uint8 ch,uint16 *ValuePtr,  uint16 Address);
    uint8 (*SetRegValue)     (uint8 ch,uint16  Address,   uint16 Value);
} DATA_HANDLE_FUN;

/*********************************************************************************************************
    Modbus 配置相关宏定义
*********************************************************************************************************/
#define   MB_UART0_CH                0                                  /* Modbus UART0管道             */
#define   MB_UART1_CH                1                                  /* Modbus UART1管道             */
#define   MB_UART2_CH                2                                  /* Modbus UART2管道             */
#define   MB_UART3_CH                3                                  /* Modbus UART3管道             */

#define   MB_UART_8BIT               8                                  /* 数据位为8位                  */
#define   MB_UART_7BIT               7                                  /* 数据位为8位                  */
#define   MB_UART_1STOP              1                                  /* 1位停止位                    */
#define   MB_NONE_PARITY             0                                  /* 无奇偶校验位                 */

#define   MB_RTU_MODE                'R'                                /* Modbus RTU模式               */
#define   MB_TCP_MODE                'T'                                /* Modbus TCP模式               */
#define   MB_ASCII_MODE              'A'                                /* Modbus ASCII模式             */


#define   COIL_ON                     0xff00                            /* 写入线圈值为1的宏定义        */
#define   COIL_OFF                    0x0000                            /* 写入线圈值为0的宏定义        */
/*********************************************************************************************************
** Function name:           MB_UartInit
**
** Descriptions:            Modbus协议栈驱动初始化
**
** input parameters:        None
** Returned value:          None
**
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**-------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern void MB_UartInit(void);


/*********************************************************************************************************
** Function name:           MB_UartChCfg
**
** Descriptions:            配置Modbus管道。
**
** input parameters:        mb_ch，从机描述信息数据结构指针
** Returned value:          配置成功返回MB_NO_ERR(0)，出错返回非零值。
**
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**-------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern uint8 MB_UartChCfg(MB_CFG *mb_ch);

/********************************************************************************************************
** Function name:           MB_UartExitCfg
**
** Descriptions:            调用该函数将释放Modbus管道占用的资源。
**
** input parameters:        ch,释放的管道号
** Returned value:          None
**
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**-------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
extern void MB_UartExitCfg(uint8 ch );

/*********************************************************************************************************
** Function name:           MB_UartReceOneChar
**
** Descriptions:            接收一个字符处理
**                          要求:接收到一个字符后立即传入该函数处理。
**
** input parameters:        ch,接收到数据的管道号
**                          ReceCharacter,接收到的字符
**                          err,非零值表时接收字符出错，如奇偶效验出错。
** Returned value:          None
**
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**-------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern void MB_UartReceOneChar(uint8 ch,uint8 ReceCharacter,uint8 err);



/*********************************************************************************************************
** Function name:           MB_UartTmrUpdate
**
** Descriptions:            Modbus时间处理，处理T15、T13的事件和协栈状态事件。
**                          该函数需要在500uS被调用一次。
** input parameters:        None
** Returned value:          None
**
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern void MB_UartTmrUpdate(void);


/********************************************************************************************************
** Function name:           MBS_UDFCodeAdd
**
** Descriptions:            Modbus从机栈初始化用户自定义功能代码,该函数使用了动态分配内存。
**
** input parameters:        code_ptr,用户自定义功能代码结构指针
** Returned value:          正常添加自定义功能代码返回0，出错返回出错代码
**
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**-------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
extern uint8 MBS_UDFCodeAdd(SUD_FUN_CODE * code_ptr);


/********************************************************************************************************
** Function name:           MBM_UDFCodeAdd
**
** Descriptions:            Modbus主机栈初始化用户自定义功能代码,该函数使用了动态分配内存。
**
** input parameters:        request_ptr,用户自定义功能代码结构指针
** Returned value:          正常添加自定义功能代码返回0，出错返回出错代码
**
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**-------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
extern uint8 MBM_UDFCodeAdd(MUD_FUN_CODE *request_ptr);




/********************************************************************************************************
** Function name:           MB_UartMServe
**
** Descriptions:            Modbus主机栈服务任务函数,基于uC/OS-II系统下使用。
**
** input parameters:        *pdata，任务参数指针，不使用。
** Returned value:          None
**
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**-------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
extern void MB_UartMServe    (void *pdata);


/********************************************************************************************************
** Function name:           MB_UartSServe
**
** Descriptions:            Modbus从机栈服务任务函数,基于uC/OS-II系统下使用。
**
** input parameters:        *pdata，任务参数指针，不使用。
** Returned value:          None
**
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**-------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
extern void MB_UartSServe    (void *pdata);


#ifdef __cplusplus
}
#endif                                                                  /* __cplusplus                  */
#endif                                                                  /* __MODBUSUSER_H               */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
