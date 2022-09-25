/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**                                      
**                                 http://www.embedtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               vicControl.h
** Latest modified Date:    2008-04-21
** Latest Version:          1.0
** Descriptions:            VIC控制代码
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Chenmingji
** Created date:            2008-04-21
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

#ifndef _VIC_CONTROL_H_
#define _VIC_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */


/********************************************************************************************************* 
  定义中断部件的ID号 
  用户不可改变下面ID的宏定义 
*********************************************************************************************************/ 
#define VIC_WDT                      0x00                               /*  看门沟                      */ 
#define VIC_TIMER0                   0x04                               /*  定时器0                     */ 
#define VIC_TIMER1                   0x05                               /*  定时器1                     */ 
#define VIC_UART0                    0x06                               /*  串口0                       */ 
#define VIC_UART1                    0x07                               /*  串口1                       */ 
#define VIC_PWM0                     0x08                               /*  PWM0                        */ 
#define VIC_I2C0                     0x09                               /*  I2C0                        */ 
#define VIC_SPI0                     0x0a                               /*  SPI0                        */ 
#define VIC_SPI1                     0x0b                               /*  SPI1/ssp                    */ 
#define VIC_PLL                      0x0c                               /*  锁相环                      */ 
#define VIC_RTC                      0x0d                               /*  实时时钟                    */ 
#define VIC_EINT0                    0x0e                               /*  外部中断0                   */ 
#define VIC_EINT1                    0x0f                               /*  外部中断1                   */ 
#define VIC_EINT2                    0x10                               /*  外部中断2                   */ 
#define VIC_EINT3                    0x11                               /*  外部中断3                   */ 
#define VIC_ADC                      0x12                               /*  AD0控制器                   */ 
#define VIC_CAN_ERR                  0x13
#define VIC_CAN1_TX                  0x14
#define VIC_CAN2_TX                  0x15
#define VIC_CAN3_TX                  0x16
#define VIC_CAN4_TX                  0x17

#define VIC_CAN1_RX                  0x1a
#define VIC_CAN2_RX                  0x1b
#define VIC_CAN3_RX                  0x1c
#define VIC_CAN4_RX                  0x1d



/*********************************************************************************************************
  兼容定义，以后不要使用
*********************************************************************************************************/
#define VIC_Config              VIC_IRQ_CFG
#define pVIC_Config             PVIC_IRQ_CFG

#define SetVICIRQ               vicIrqFuncSet
#define FreeVICIRQ              vicIrqFuncClr
#define ReEnableVICIRQ          vicIrqEnable
#define DisableVICIRQ           vicIrqDisable
#define GetVICIRQState          vicIrqStatusGet
#define SetVICFIQ               vicFiqSet
#define FreeVICFIQ              vicFiqClr
#define SetDefIRQFunction       vicDefIrqFuncSet
#define EnableDefIRQ            vicDefIrqEnable
#define DisableDefIRQ           vicDefIrqDisable
#define EnableSoftInt           vicSoftIntEnable
#define DisableSoftInt          vicSoftIntDisable


/*********************************************************************************************************
  VIC配置信息定义
*********************************************************************************************************/
struct vic_irq_cfg {
    INT32U      ulChannel;                                              /*  通道                        */
    INT32U      ulPri;                                                  /*  优先级                      */
    INT32U      ulFunctionAddr;                                         /*  ISR地址                     */
    INT32U      ulEnable;                                               /*  使能标识                    */
};

typedef struct vic_irq_cfg      VIC_IRQ_CFG;
typedef struct vic_irq_cfg     *PVIC_IRQ_CFG;


/*********************************************************************************************************
** Function name:           swiHandle
** Descriptions:            SWI函数声明
** input parameters:        iHandle: 用于区分功能
**                          其他:    根据功能决定
** output parameters:       根据功能决定
** Returned value:          根据功能决定
*********************************************************************************************************/
__swi(0x01) unsigned int swiHandle (int iHandle, unsigned int, unsigned int, unsigned int);


/*********************************************************************************************************
** Function name:           vicIrqFuncSet
** Descriptions:            设置所选外设的中断优先级、中断服务函数地址，并使能中断
** input parameters:        uiChannel:  外设对应的中断通道号
**                          uiPri:      中断优先级
**                          uiFuncAddr: 中断服务函数地址
** output parameters:       none
** Returned value:          1:          成功
**                          0:          失败
*********************************************************************************************************/
extern unsigned int vicIrqFuncSet (unsigned int uiChannel,
                                     unsigned int uiPri,
                                     unsigned int uiFuncAddr);
                                     


       
/*********************************************************************************************************
** Function name:           vicIrqFuncClr
** Descriptions:            清除所选外设的IRQ资源
** input parameters:        uiChannel:  外设对应的中断通道号
** output parameters:       none
** Returned value:          1:          成功
**                          0:          失败
*********************************************************************************************************/
extern unsigned int vicIrqFuncClr (unsigned int uiChannel);

/*********************************************************************************************************
** Function name:           vicIrqEnable
** Descriptions:            使能相应外设的中断
** input parameters:        uiChannel:  外设对应的中断通道号
** output parameters:       none
** Returned value:          1:          成功
**                          0:          失败
*********************************************************************************************************/
extern unsigned int vicIrqEnable (unsigned int uiChannel);

/*********************************************************************************************************
** Function name:           vicIrqDisable
** Descriptions:            禁止相应外设的中断
** input parameters:        uiChannel:  外设对应的中断通道号
** output parameters:       none
** Returned value:          1:          成功
**                          0:          失败
*********************************************************************************************************/
extern unsigned int vicIrqDisable (unsigned int uiChannel);

/*********************************************************************************************************
** Function name:           vicIrqStatusGet
** Descriptions:            获取所选外设的中断通道号、优先级、中断服务函数地址及中断使能状态
** input parameters:        uiChannel:  外设对应的中断通道号
** output parameters:       pvicInfo:   配置信息
** Returned value:          1:          成功
**                          0:          失败
*********************************************************************************************************/
extern unsigned int vicIrqStatusGet (unsigned int uiChannel, PVIC_IRQ_CFG pvicInfo);

/*********************************************************************************************************
** Function name:           vicFiqSet
** Descriptions:            设置并使能所选中断通道号为FIQ中断
** input parameters:        uiChannel:  外设对应的中断通道号
** output parameters:       none
** Returned value:          1:          成功
**                          0:          失败
*********************************************************************************************************/
extern unsigned int vicFiqSet (unsigned int uiChannel);

/*********************************************************************************************************
** Function name:           vicFiqClr
** Descriptions:            清除所选中断通道号的FIQ中断
** input parameters:        uiChannel:  外设对应的中断通道号
** output parameters:       none
** Returned value:          1:          成功
**                          0:          失败
*********************************************************************************************************/
extern unsigned int vicFiqClr (unsigned int uiChannel);

/*********************************************************************************************************
** Function name: DefIrqFuncSet
** Descriptions: 设置非向量中断服务程序地址
** input parameters: uiFuncAddr  :中断服务程序（普通C语言函数）
** output parameters:       none
** Returned value: 1:          成功
**                          0:          失败
*********************************************************************************************************/
extern unsigned int vicDefIrqFuncSet(unsigned int uiFuncAddr);

/*********************************************************************************************************
** Function name: DefIrqEnable
** Descriptions: 使能所选中断通道号的非向量中断
** input parameters: uiChannel   ：外设对应的中断通道号
** output parameters:       none
** Returned value: 1:          成功
**                          0:          失败
*********************************************************************************************************/
extern unsigned int  vicDefIrqEnable(unsigned int uiChannel);
/*********************************************************************************************************
** Function name: DefIrqDisable
** Descriptions: 释放所选中断通道号的非向量中断
** input parameters: uiChannel     ：外设对应的中断通道号
** output parameters:       none
** Returned value: 1:          成功
**                          0:          失败
*********************************************************************************************************/
extern unsigned int  vicDefIrqDisable(unsigned int uiChannel);

/*********************************************************************************************************
** Function name: SoftIntEnable
** Descriptions: 使能所选中断通道号的向量软中断
** input parameters: uiChannel     ：外设对应的中断通道号
** output parameters:       none
** Returned value: 1:          成功
**                          0:          失败
*********************************************************************************************************/
extern unsigned int  vicSoftIntEnable(unsigned int uiChannel);

/*********************************************************************************************************
** Function name: SoftIntDisable
** Descriptions: 禁止所选中断通道号的向量软中断
** input parameters: uiChannel     ：外设对应的中断通道号
** output parameters:       none
** Returned value: 1:          成功
**                          0:          失败
*********************************************************************************************************/
extern unsigned int  vicSoftIntDisable(unsigned int uiChannel);




/*********************************************************************************************************
  允许中断嵌套宏定义
*********************************************************************************************************/
#define     OS_ENABLE_NESTING       OS_EXIT_CRITICAL
#define     OS_DISABLE_NESTING      OS_ENTER_CRITICAL

#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __TARGET_H                  */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

