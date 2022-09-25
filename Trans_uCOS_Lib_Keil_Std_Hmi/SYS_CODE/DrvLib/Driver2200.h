/****************************************Copyright (c)**************************************************
**
**
**--------------File Info-------------------------------------------------------------------------------
** File name:           Driver2200.h
** Last modified Date:  2012-12-31
** Last Version:        1.0
** Descriptions:        外设参数配置信息
**------------------------------------------------------------------------------------------------------
** Created by:          
** Created date:        2012-12-31
** Version:             1.00
** Descriptions:        The original version
**------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:             
** Descriptions:        
********************************************************************************************************/

#ifndef __DRIVER2200_H
#define __DRIVER2200_H

/*********************************************************************************************************
  外设配置信息头文件
*********************************************************************************************************/
#include "..\DrvLib\GPIO\GPIO.h"
#include "..\DrvLib\Uart\uart.h"
#include "..\DrvLib\I2C\I2C.h"
#include "..\DrvLib\Timer\Timer.h"
#include "..\DrvLib\SPI\SPI.h"         

#include "..\DrvLib\PWM\PWM.h"
#include "..\DrvLib\ADC\ADC.h"

#include "..\DrvLib\EINT\EINT.h"
#include "..\DrvLib\RTC\RTC.h"
#include "..\DrvLib\WDT\WDT.h"
#include "..\DrvLib\PLL\PLL.h"
#include "..\DrvLib\Power\Power.h"
#include "..\DrvLib\CAN\CAN.h" 

#include "..\DrvLib\CAN\FullCANAF.h" 
#include "..\DrvLib\EMC\EMC.h"

/*********************************************************************************************************
  基础驱动库HOOKS结构体定义
*********************************************************************************************************/
struct driver_hooks{
    void (*pRS485Dir_Out)   (INT32U ulPinCtl);                          /*   RS-485输出控制调用的函数   */
                                                                        /*   ulPinCtl: 控制引脚编码     */
    void (*pRS485Dir_In)    (INT32U ulPinCtl);                          /*   RS-485输入控制调用的函数   */
                                                                        /*   ulPinCtl: 控制引脚编码     */                                                                    

    void (*pSpiCsEnable)    (INT32U ulPinCtl);                          /*   SPI片选使能调用的函数      */
                                                                        /*   ulPinCtl: 控制引脚编码     */
    void (*pSpiCsDisable)   (INT32U ulPinCtl);                          /*   SPI片选禁能调用的函数      */
                                                                        /*   ulPinCtl: 控制引脚编码     */  
    void*(*pSysHeapMalloc)  (INT32U ulSize);                            /*   内存缓冲区分配调用的函数   */
                                                                        /*   ulSize: 分配字节大小       */
    void (*pSysHeapFree)    (void *pvPrt);                              /*   内存缓冲区释放调用的函数   */
                                                                        /*   pvPrt: 缓冲指针            */    
  
    void (*pUartVicEnable)  (void);                                     /*   Uart中断使能调用的函数     */
    void (*pUartVicDisable) (void);                                     /*   Uart中断禁能调用的函数     */
    
    void (*pSpiVicEnable)   (void);                                     /*   Spi中断使能调用的函数      */
    void (*pSpiVicDisable)  (void);                                     /*   Spi中断禁能调用的函数      */
    
    void (*pI2cVicEnable)   (void);                                     /*   I2c中断使能调用的函数      */
    void (*pI2cVicDisable)  (void);                                     /*   I2c中断禁能调用的函数      */
    
    void (*pWdtVicEnable)   (void);                                     /*   Wdt中断使能调用的函数      */
    void (*pWdtVicDisable)  (void);                                     /*   Wdt中断禁能调用的函数      */

    void (*pCanVicEnable)   (void);                                     /*   Can中断使能调用的函数      */
    void (*pCanVicDisable)  (void);                                     /*   Can中断禁能调用的函数      */

    void (*pAdcVicEnable)   (void);                                     /*   Adc中断使能调用的函数      */
    void (*pAdcVicDisable)  (void);                                     /*   Adc中断禁能调用的函数      */
    
    void (*pRtcVicEnable)   (void);                                     /*   Rtc中断使能调用的函数      */
    void (*pRtcVicDisable)  (void);                                     /*   Rtc中断禁能调用的函数      */
    
    void (*pTimerVicEnable)   (void);                                   /*   Timer中断使能调用的函数    */
    void (*pTimerVicDisable)  (void);                                   /*   Timer中断禁能调用的函数    */
};

typedef struct driver_hooks  DRIVER_HOOKS;
typedef struct driver_hooks* PDRIVER_HOOKS;

/*********************************************************************************************************
  供驱动库内部调用 用户不得删除
*********************************************************************************************************/
#define OPERATE_SUCCESS     0
#define OPERATE_FAIL        0xFF
    /*
     *  驱动库版本号
     */
#define __uiGDriver2200_Ver 0x10081732                                  /*  V3.2版本                   */
    /*
     *  驱动库HOOK函数
     */
extern const DRIVER_HOOKS GdhDrvHooksTbl;
extern const DRIVER_HOOKS __GdhDrvHooks;
/*********************************************************************************************************
** Function name:           sysDriveLibVerGet
** Descriptions:            获得驱动版本号
** input parameters:        None
** output parameters:       None
** Returned value:          驱动版本号
*********************************************************************************************************/
INT32U sysDriveLibVerGet(void);

#endif                                                                  /*  __DEVICECONFIG_H            */ 
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
