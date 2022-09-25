/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.embedtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               sys_if.h
** Latest modified Date:    2009-07-23
** Latest Version:          1.00
** Descriptions:            环境接口函数,必须在特权模式运行
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Chenmingji
** Created date:            2009-07-23
** Version:                 1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*********************************************************************************************************/
#ifndef __SYS_IF_H
#define __SYS_IF_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
  返回值定义
*********************************************************************************************************/
#define SYS_OK                  0                                       /*  操作成功                    */
#define SYS_NOT_OK              1                                       /*  操作失败                    */
#define SYS_PARA_ERR            2                                       /*  参数错误                    */
#define SYS_FIND_NO_DEVICE      3                                       /*  没有发现设备                */
#define SYS_NODE_FULL           4                                       /*  节点已满                    */
#define SYS_NO_FIND_FUNCTION    5                                       /*  没有发现指定函数            */
#define SYS_DRIVER_FULL         6                                       /*  驱动节点已满                */
#define SYS_NODE_EXIST          7                                       /*  节点已存在                  */
#define SYS_DRIVER_EXIST        7                                       /*  网络驱动已安装              */
#define SYS_FIND_NO_DRIVER      8                                       /*  没有发现指定驱动            */
#define SYS_NO_PORT             9                                       /*  没有找到端口                */
#define SYS_NO_MEMORY           10                                      /*  内存不足                    */
#define SYS_TIME_OUT            11                                      /*  超时                        */
#define SYS_PACKET_ERR          12                                      /*  数据校验错误                */
#define SYS_NO_NODE             13                                      /*  未找到相应节点              */
#define SYS_NO_FIND_OBJECT      16                                      /*  没有发现对象                */
#define SYS_QUEUE_FULL          17
#define SYS_QUEUE_EMPTY         18


/*********************************************************************************************************
  64位变量相关定义
*********************************************************************************************************/
typedef long long   INT64S;                                             /*  64位有符号数                */

#define sysLlAdd(a, b, c) a = (INT64S)(b) + (INT64S)(c)                  /*  64位有符号加法a=b+c         */
#define sysLlSub(a, b, c) a = (INT64S)(b) - (INT64S)(c)                  /*  64位有符号减法a=b-c         */
#define sysLlMul(a, b, c) a = (INT64S)(b) * (INT64S)(c)                  /*  64位有符号乘法a=b*c         */
#define sysLlDiv(a, b, c) a = (INT64S)(b) / (INT64S)(c)                  /*  64位有符号除法a=b/c         */
#define sysLlMod(a, b, c) a = (INT64S)(b) % (INT64S)(c)                  /*  64位有符号除法a=b/c         */
#define sysLlSet(a, b)    a = (INT64S)(b)                                /*  64位有符号赋值              */
#define sysLlIsLess(a, b) ((INT64S)(a) < (INT64S)(b))                    /*  64位有符号小于判定          */
#define sysLlSet32(a, b)  a = (INT32U)(b)                                /*  64位有符号赋值给32位无符号数*/
#define sysLlSet32s(a, b) a = (INT32S)(b)                                /*  64位有符号赋值给32位有符号数*/
/*********************************************************************************************************
  字节顺序变换
*********************************************************************************************************/
#ifndef sys_ntohl
#define sys_ntohl(x) x = (INT32U)(((INT8U *)&x)[0] << 24 | \
                                 ((INT8U *)&x)[1] << 16 | \
                                 ((INT8U *)&x)[2] << 8  | \
                                 ((INT8U *)&x)[3] << 0)
#endif                                                                  /*  aw_ntohl                    */

#ifndef sys_htonl
#define sys_htonl(x) x = (INT32U)(((INT8U *)&x)[0] << 24 | \
                                 ((INT8U *)&x)[1] << 16 | \
                                 ((INT8U *)&x)[2] << 8  | \
                                 ((INT8U *)&x)[3] << 0)
#endif                                                                  /*  aw_htonl                    */

#ifndef sys_ntohs
#define sys_ntohs(x) x = (INT16U)(((INT8U *)&x)[0] << 8  | \
                                 ((INT8U *)&x)[1] << 0)
#endif                                                                  /*  aw_ntohs                    */

#ifndef sys_htons
#define sys_htons(x) x = (INT16U)(((INT8U *)&x)[0] << 8  | \
                                 ((INT8U *)&x)[1] << 0)
#endif                                                                  /*  aw_htons                    */

/*********************************************************************************************************
  复位模式
*********************************************************************************************************/
#define SYS_POWER_RESET      0                                           /*  上电复位                    */
#define SYS_HARD_RESET       1                                           /*  硬件复位                    */
#define SYS_SOFT_RESET       2                                           /*  软件复位                    */
/*********************************************************************************************************
** Function name:           sysInit
** Descriptions:            系统参数初始化
** input parameters:        uiFosc:     系统外部时钟
**                          uiFcclk:    系统内核时钟
**                          uiFcco:     倍频时钟
**                          uiFpclk:    外设时钟
**                          uiOsticks:  系统节拍
** output parameters:       none
** Returned value:          读到的数据
*********************************************************************************************************/
extern void sysInit (INT32U uiFosc, INT32U uiFcclk, INT32U uiFcco, INT32U uiFpclk, INT32U uiOsticks);
/*********************************************************************************************************
** Function name:           sysIfInit
** Descriptions:            接口初始化
** input parameters:        none
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysIfInit(void);


/*********************************************************************************************************
** Function name:           sysIrqDisable
** Descriptions:            禁止中断
** input parameters:        none
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysIrqDisable(void);

/*********************************************************************************************************
** Function name:           sysIrqEnable
** Descriptions:            允许中断
** input parameters:        none
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysIrqEnable(void);
/*********************************************************************************************************
** Function name:           sysFiqDisable
** Descriptions:            关闭全局FIQ中断
** input parameters:        none
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S sysFiqDisable (void);

/*********************************************************************************************************
** Function name:           sysFiqEnable
** Descriptions:            打开全局FIQ中断
** input parameters:        none
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S sysFiqEnable (void);

/*********************************************************************************************************
** Function name:           sysChangeToSysMode
** Descriptions:            任务切换到系统模式 
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S sysChangeToSysMode (void);

/*********************************************************************************************************
** Function name:           sysChangeToUsrMode
** Descriptions:            任务切换到用户模式 
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S sysChangeToUsrMode (void);

/*********************************************************************************************************
** Function name:           sysIsrSet
** Descriptions:            设置中断服务程序
** input parameters:        uiChannel:  中断通道号
**                          ulFunction: 中断服务程序地址
**                          uiPrio:     中断优先级
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysIsrSet(unsigned int uiChannel, unsigned long ulFunction, unsigned int uiPrio);

/*********************************************************************************************************
** Function name:           sysIsrClr
** Descriptions:            清除中断服务程序
** input parameters:        uiChannel:  中断通道号
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysIsrClr(unsigned int uiChannel);

/*********************************************************************************************************
** Function name:           sysIsrDisable
** Descriptions:            禁止指定中断
** input parameters:        uiChannel:  中断通道号
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysIsrDisable(unsigned int uiChannel);

/*********************************************************************************************************
** Function name:           sysIsrEnable
** Descriptions:            允许指定中断
** input parameters:        uiChannel:  中断通道号
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysIsrEnable(unsigned int uiChannel);

/*********************************************************************************************************
** Function name:           sysHeapMalloc
** Descriptions:            堆分配内存
** input parameters:        ulSize: 内存大小
** output parameters:       none
** Returned value:          内存地址,NULL为不成功
*********************************************************************************************************/
extern void *sysHeapMalloc(INT32U ulSize);

/*********************************************************************************************************
** Function name:           sysHeapMallocAlign
** Descriptions:            堆分配内存
** input parameters:        ulSize:         内存大小
**                          uiAlign:        对其字节数
** output parameters:       none
** Returned value:          内存地址,NULL为不成功
** Created by:              Chenmingji
** Created Date:            2009-07-23
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
extern void *sysHeapMallocAlign (INT32U ulSize, INT32U uiAlign);

/*********************************************************************************************************
** Function name:           sysHeapFree
** Descriptions:            堆释放内存
** input parameters:        pvPrt: 要释放的内存
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysHeapFree(void *pvPrt);

/*********************************************************************************************************
** Function name:           sysThreadCreate
** Descriptions:            建立线程
** input parameters:        pvThreedMain: 线程主程序
**                          pvArg:        线程主程序参数
**                          uiPrio:       线程优先级
**                          ulSize:       堆栈大小
** output parameters:       none
** Returned value:          线程ID,0为不成功
*********************************************************************************************************/
extern unsigned long sysThreadCreate(void *pvThreedMain, void *pvArg, unsigned int uiPrio, INT32U ulSize);

/*********************************************************************************************************
** Function name:           sysThreadDel
** Descriptions:            删除线程
** input parameters:        ulThreadId: 线程ID
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysThreadDel(unsigned long ulThreadId);

/*********************************************************************************************************
** Function name:           sysThreadSuspendSelf
** Descriptions:            挂起线程自身
** input parameters:        none
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysThreadSuspendSelf(void);

/*********************************************************************************************************
** Function name:           sysThreadResume
** Descriptions:            恢复线程
** input parameters:        ulThreadId: 线程ID
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysThreadResume(unsigned long ulThreadId);

/*********************************************************************************************************
** Function name:           sysThreadGetCurId
** Descriptions:            获得当前线程ID
** input parameters:        none
** output parameters:       none
** Returned value:          线程ID
*********************************************************************************************************/
extern unsigned long sysThreadGetCurId(void);

/*********************************************************************************************************
** Function name:           sysThreadSuspendCheck
** Descriptions:            检查线程是否确实被挂起
** input parameters:        ulThreadId: 线程ID
** output parameters:       none
** Returned value:          SYS_OK:      挂起
**                          -SYS_NOT_OK: 未挂起
**                          其它负数:   错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysThreadSuspendCheck(unsigned long ulThreadId);

/*********************************************************************************************************
** Function name:           sysThreadDelay
** Descriptions:            当前线程延时
** input parameters:        ulTimes: 以毫秒为单位等待时间
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysThreadDelay(unsigned long ulTimes);

/*********************************************************************************************************
** Function name:           sysSemCreate
** Descriptions:            创建信号量
** input parameters:        ulCnt:  信号量初始值
** output parameters:       none
** Returned value:          信号量标识
**                          0: 不成功
*********************************************************************************************************/
extern unsigned long sysSemCreate(INT32S ulCnt);

/*********************************************************************************************************
** Function name:           sysSemDel
** Descriptions:            删除信号量
** input parameters:        ulSem: sysSemCreate返回值
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysSemDel(unsigned long ulSem);

/*********************************************************************************************************
** Function name:           sysSemAccept
** Descriptions:            无等待获得信号量
** input parameters:        ulSem: sysSemCreate返回值
** output parameters:       none
** Returned value:          >=0:   信号量当前值
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysSemAccept(unsigned long ulSem);

/*********************************************************************************************************
** Function name:           sysSemPend
** Descriptions:            等待信号量
** input parameters:        ulSem: sysSemCreate返回值
**                          ulDly: 最长等待时间,毫秒为单位
** output parameters:       none
** Returned value:          >=0:   信号量当前值
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysSemPend(unsigned long ulSem, INT32U ulDly);

/*********************************************************************************************************
** Function name:           sysSemPost
** Descriptions:            允许指定中断
** input parameters:        ulSem: sysSemCreate返回值
**                          ucMod: 发送模式,一般为0
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysSemPost(unsigned long ulSem, INT8U ucMod);

/*********************************************************************************************************
** Function name:           sysMsgCreate
** Descriptions:            创建消息通道
** input parameters:        ulMsgs:    可以缓存消息数目
**                          ulMsgSize: 消息大小
** output parameters:       none
** Returned value:          消息通道标识
**                          0: 不成功
*********************************************************************************************************/
extern unsigned long sysMsgCreate(INT32S ulMsgs, INT32U ulMsgSize);

/*********************************************************************************************************
** Function name:           sysMsgDel
** Descriptions:            删除消息通道
** input parameters:        ulMsg:  sysMsgCreate返回值
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysMsgDel(unsigned long ulMsg);

/*********************************************************************************************************
** Function name:           sysMsgAccept
** Descriptions:            无等待获得消息
** input parameters:        ulMsg:  sysMsgCreate返回值
** output parameters:       pucMsg: 保存获得的消息
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysMsgAccept(unsigned long ulMsg, INT8U *pucMsgRt);

/*********************************************************************************************************
** Function name:           sysMsgPend
** Descriptions:            等待消息
** input parameters:        ulMsg:  sysMsgCreate返回值
**                          ulDly: 最长等待时间,毫秒为单位
** output parameters:       pucMsgRt: 保存获得的消息
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysMsgPend(unsigned long ulMsg, INT8U *pucMsgRt, INT32U ulDly);

/*********************************************************************************************************
** Function name:           sysMsgPost
** Descriptions:            发送消息
** input parameters:        ulMsg:      sysMsgCreate返回值
**                          pucMsgSend: 要发送的消息
**                          ucMod:      发送模式,一般为0
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysMsgPost(unsigned long ulMsg, INT8U *pucMsgSend, INT8U ucMod);




extern INT32U __GuiFpclk, __GuiFosc, __GuiFcclk,__GuiFcco;
extern INT32U __GuiOS_TICKS_PER_SEC;

#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __SYS_IF_H                   */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
