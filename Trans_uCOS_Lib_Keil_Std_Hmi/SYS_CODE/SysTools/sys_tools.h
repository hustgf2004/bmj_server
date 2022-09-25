/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               sys_tools.h
** Latest modified Date:    2014-08-25
** Latest Version:          1.00
** Descriptions:            系统工具函数
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2014-08-25
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
#ifndef __SYS_TOOLS_H
#define __SYS_TOOLS_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
  VIC配置信息定义
*********************************************************************************************************/
struct vic_irq_cfg {
    INT32U      ulChannel;                                              /*  通道                        */
    INT32U      ulPri;                                                  /*  优先级                      */
    INT32U      ulFunctionAddr;                                         /*  ISR地址                     */
    INT32U      ulEnable;                                               /*  使能标识                    */
};

typedef struct vic_irq_cfg  VIC_IRQ_CFG;
typedef struct vic_irq_cfg* PVIC_IRQ_CFG;

/*********************************************************************************************************
  返回值定义
*********************************************************************************************************/
#define SYS_OK                  0                                       /*  操作成功                    */
#define SYS_NOT_OK              1                                       /*  操作失败                    */
#define SYS_PARA_ERR            2                                       /*  参数错误                    */
#define SYS_NO_MEMARY           3                                       /*  内存不足                    */
#define SYS_TIME_OUT            4                                       /*  超时                        */

/*********************************************************************************************************
  64位变量相关定义
*********************************************************************************************************/
#define sysLlAdd(a, b, c) a = (INT64S)(b) + (INT64S)(c)                 /*  64位有符号加法a=b+c         */
#define sysLlSub(a, b, c) a = (INT64S)(b) - (INT64S)(c)                 /*  64位有符号减法a=b-c         */
#define sysLlMul(a, b, c) a = (INT64S)(b) * (INT64S)(c)                 /*  64位有符号乘法a=b*c         */
#define sysLlDiv(a, b, c) a = (INT64S)(b) / (INT64S)(c)                 /*  64位有符号除法a=b/c         */
#define sysLlMod(a, b, c) a = (INT64S)(b) % (INT64S)(c)                 /*  64位有符号除法a=b/c         */
#define sysLlSet(a, b)    a = (INT64S)(b)                               /*  64位有符号赋值              */
#define sysLlIsLess(a, b) ((INT64S)(a) < (INT64S)(b))                   /*  64位有符号小于判定          */
#define sysLlSet32(a, b)  a = (INT32U)(b)                               /*  64位有符号赋值给32位无符号数*/
#define sysLlSet32s(a, b) a = (INT32S)(b)                               /*  64位有符号赋值给32位有符号数*/

/*********************************************************************************************************
** Function name:           sysIfInit
** Descriptions:            接口初始化
** input parameters:        none
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S sysIfInit (void);

/*********************************************************************************************************
** Function name:           __sysIfInit
** Descriptions:            接口初始化
** input parameters:        pvHeap:        堆地址
**                          ulHeapSize:    堆大小
**                          pvDmaHeap:     DMA堆地址
**                          ulDmaHeapSize: DMA堆地址大小
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S __sysIfInit(void *pvHeap, INT32U ulHeapSize, void *pvDrivHooks, INT32U ulHooksSize);

/*********************************************************************************************************
** Function name:           sysHeapMalloc
** Descriptions:            堆分配内存
** input parameters:        ulSize: 内存大小
** output parameters:       none
** Returned value:          内存地址,NULL为不成功
*********************************************************************************************************/
extern void *sysHeapMalloc (INT32U ulSize);

/*********************************************************************************************************
** Function name:           sysHeapFree
** Descriptions:            堆释放内存
** input parameters:        pvPrt:  要释放的内存
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S sysHeapFree (void *pvPrt);

/*********************************************************************************************************
** Function name:           sysIrqDisable
** Descriptions:            进入临界状态
** input parameters:        none
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S sysIrqDisable (void);

/*********************************************************************************************************
** Function name:           sysIrqEnable
** Descriptions:            退出临界状态
** input parameters:        none
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S sysIrqEnable (void);

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
** Function name:           sysMsgCreate
** Descriptions:            创建消息通道
** input parameters:        ulMsgNum:  可以缓存消息数目
**                          ulMsgSize: 消息大小
** output parameters:       none
** Returned value:          消息通道标识
**                          0: 不成功
*********************************************************************************************************/
extern unsigned long sysMsgCreate (INT32S ulMsgNum, INT32U ulMsgSize);

/*********************************************************************************************************
** Function name:           sysMsgDel
** Descriptions:            删除消息通道
** input parameters:        ulMsg:  sysMsgCreate返回值
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S sysMsgDel (unsigned long ulMsg);

/*********************************************************************************************************
** Function name:           sysMsgAccept
** Descriptions:            无等待获得消息
** input parameters:        ulMsg:  sysMsgCreate返回值
** output parameters:       pucMsg: 保存获得的消息
** Returned value:          SYS_OK:  成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S sysMsgAccept(unsigned long ulMsg, INT8U *pucMsgRt);

/*********************************************************************************************************
** Function name:           sysMsgPend
** Descriptions:            等待消息
** input parameters:        ulMsg:  sysMsgCreate返回值
**                          ulDly: 最长等待时间,毫秒为单位
** output parameters:       pucMsgRt: 保存获得的消息
** Returned value:          SYS_OK: 成功
**                          负数:  错误,绝对值参考sys_tools.h
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
**                          负数:  错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S sysMsgPost(unsigned long ulMsg, INT8U *pucMsgSend, INT8U ucMod);

/*********************************************************************************************************
** Function name:           vicIrqFuncSet
** Descriptions:            设置中断服务程序
** input parameters:        uiChannel:  中断通道号
**                          uiPrio:     中断优先级
**                          ulFunction: 中断服务程序地址
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S vicIrqFuncSet(unsigned int uiChannel, unsigned int uiPrio, unsigned long ulFunction);

/*********************************************************************************************************
** Function name:           vicIrqFuncClr
** Descriptions:            清除中断服务程序
** input parameters:        uiChannel:  中断通道号
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S vicIrqFuncClr(unsigned int uiChannel);

/*********************************************************************************************************
** Function name:           vicIrqEnable
** Descriptions:            允许指定通道中断
** input parameters:        uiChannel:  中断通道号
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S vicIrqEnable(unsigned int uiChannel);
/*********************************************************************************************************
** Function name:           vicIrqDisable
** Descriptions:            禁止指定通道中断
** input parameters:        uiChannel:  中断通道号
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S vicIrqDisable(unsigned int uiChannel);

/*********************************************************************************************************
** Function name:           vicIrqStatusGet
** Descriptions:            获取所选外设的中断通道号、优先级、中断服务函数地址及中断使能状态
** input parameters:        uiChannel:  中断通道号
** output parameters:       pvicInfo:   配置信息
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S vicIrqStatusGet (unsigned int uiChannel, PVIC_IRQ_CFG pvicInfo);

/*********************************************************************************************************
** Function name:           vicFiqEnable
** Descriptions:            允许指定通道快速中断
** input parameters:        uiChannel:  中断通道号
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S vicFiqEnable(unsigned int uiChannel);

/*********************************************************************************************************
** Function name:           vicFiqDisable
** Descriptions:            禁止指定通道快速中断
** input parameters:        uiChannel:  中断通道号
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S vicFiqDisable(unsigned int uiChannel);

/*********************************************************************************************************
** Function name:           vicDefIrqFuncSet
** Descriptions:            设置非向量中断服务程序
** input parameters:        ulFunction: 中断服务程序地址
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S vicDefIrqFuncSet(unsigned long ulFunction);

/*********************************************************************************************************
** Function name:           vicDefIrqEnable
** Descriptions:            允许指定通道非向量中断
** input parameters:        uiChannel:  中断通道号
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S vicDefIrqEnable(unsigned int uiChannel);

/*********************************************************************************************************
** Function name:           vicDefIrqDisable
** Descriptions:            禁止指定通道非向量中断
** input parameters:        uiChannel:  中断通道号
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S vicDefIrqDisable(unsigned int uiChannel);

/*********************************************************************************************************
** Function name:           vicSoftIntEnable
** Descriptions:            使能所选中断通道号的向量软中断
** input parameters:        uiChannel:  中断通道号
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S vicSoftIntEnable(unsigned int uiChannel);

/*********************************************************************************************************
** Function name:           vicSoftIntDisable
** Descriptions:            禁止所选中断通道号的向量软中断
** input parameters:        uiChannel:  中断通道号
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_tools.h
*********************************************************************************************************/
extern INT32S vicSoftIntDisable(unsigned int uiChannel);


#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __SYS_TOOLS_H               */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
