/****************************************Copyright (c)****************************************************
**
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Driver2200.c
** Last modified Date:  2012-12-31
** Last Version:        1.0
** Descriptions:        参数配置信息
**--------------------------------------------------------------------------------------------------------
** Created by:          
** Created date:        2012-12-31
** Version:             1.0
** Descriptions:        The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:
** Descriptions:        
*********************************************************************************************************/

//#include    "..\USER_CODE\cfg_file\config.h" 
#include    "..\Head\system.h"
/* 供驱动库内部调用 用户不得删除 */
/*********************************************************************************************************
** Function name:           Dir_Set
** Descriptions:            清零RS-485控制引脚,供用户RS485钩子函数调用
** input parameters:        Dir  : RS-485控制引脚编号值
** output parameters:       None
** Returned value:          None
*********************************************************************************************************/
void RS485Dir_Out (INT32U Dir)
{
    gpioSet(Dir);
}
/*********************************************************************************************************
** Function name:           Dir_Clr
** Descriptions:            清零RS-485控制引脚,供用户RS485钩子函数调用
** input parameters:        Dir  : RS-485控制引脚编号值
** output parameters:       None
** Returned value:          None
*********************************************************************************************************/
void RS485Dir_In (INT32U Dir)
{
    gpioClr(Dir);
}

/*********************************************************************************************************
** Function name:           UartVicEnable
** Descriptions:            退出临界状态
** input parameters:        None
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
void UartVicEnable(void)
{
    sysIrqEnable();     
}

/*********************************************************************************************************
** Function name:           UartVicDisable
** Descriptions:            进入临界状态
** input parameters:        None
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
void UartVicDisable(void)
{
    sysIrqDisable();
}

/*********************************************************************************************************
** Function name:           SpiCS_Enable
** Descriptions:            SPI片选使能
** input parameters:        None
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
void SpiCsEnable(INT32U Dir)
{
    gpioClr(Dir);
}
/*********************************************************************************************************
** Function name:           SpiCS_Disable
** Descriptions:            SPI片选禁能
** input parameters:        None
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
void SpiCsDisable(INT32U Dir)
{
    gpioSet(Dir);
}

/*********************************************************************************************************
** Function name:           SpiVicEnable
** Descriptions:            退出临界状态
** input parameters:        None
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
void SpiVicEnable(void)
{
    sysIrqEnable();     
}

/*********************************************************************************************************
** Function name:           SpiVicDisable
** Descriptions:            进入临界状态
** input parameters:        None
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
void SpiVicDisable(void)
{
    sysIrqDisable();
}

/*********************************************************************************************************
** Function name:           I2cVicEnable
** Descriptions:            退出临界状态
** input parameters:        None
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
void I2cVicEnable(void)
{
    sysIrqEnable();     
}

/*********************************************************************************************************
** Function name:           I2cVicDisable
** Descriptions:            进入临界状态
** input parameters:        None
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
void I2cVicDisable(void)
{
    sysIrqDisable();
}

/*********************************************************************************************************
** Function name:           WdtVicEnable
** Descriptions:            退出临界状态
** input parameters:        None
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
void WdtVicEnable(void)
{
    sysIrqEnable();     
}

/*********************************************************************************************************
** Function name:           WdtVicDisable
** Descriptions:            进入临界状态
** input parameters:        None
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
void WdtVicDisable(void)
{
    sysIrqDisable();
}

/*********************************************************************************************************
** Function name:           CanVicEnable
** Descriptions:            退出临界状态
** input parameters:        None
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
void CanVicEnable(void)
{
    sysIrqEnable();     
}

/*********************************************************************************************************
** Function name:           CanVicDisable
** Descriptions:            进入临界状态
** input parameters:        None
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
void CanVicDisable(void)
{
    sysIrqDisable();
}

/*********************************************************************************************************
** Function name:           AdcVicEnable
** Descriptions:            退出临界状态
** input parameters:        None
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
void AdcVicEnable(void)
{
    sysIrqEnable();     
}

/*********************************************************************************************************
** Function name:           AdcVicDisable
** Descriptions:            进入临界状态
** input parameters:        None
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
void AdcVicDisable(void)
{
    sysIrqDisable();
}

/*********************************************************************************************************
** Function name:           RtcVicEnable
** Descriptions:            退出临界状态
** input parameters:        None
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
void RtcVicEnable(void)
{
    sysIrqEnable();     
}

/*********************************************************************************************************
** Function name:           RtcVicDisable
** Descriptions:            进入临界状态
** input parameters:        None
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
void RtcVicDisable(void)
{
    sysIrqDisable();
}

/*********************************************************************************************************
** Function name:           TimerVicEnable
** Descriptions:            退出临界状态
** input parameters:        None
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
void TimerVicEnable(void)
{
    sysIrqEnable();     
}

/*********************************************************************************************************
** Function name:           RtcVicDisable
** Descriptions:            进入临界状态
** input parameters:        None
** output parameters:       None
** Returned value:          无
*********************************************************************************************************/
void TimerVicDisable(void)
{
    sysIrqDisable();
}

const DRIVER_HOOKS GdhDrvHooksTbl = {
                                    RS485Dir_Out,RS485Dir_In,SpiCsEnable,SpiCsDisable,malloc,free,
                                    UartVicEnable,UartVicDisable,SpiVicEnable,SpiVicDisable,I2cVicEnable,
                                    I2cVicDisable,WdtVicEnable,WdtVicDisable,CanVicEnable,CanVicDisable,
                                    AdcVicEnable,AdcVicDisable,RtcVicEnable,RtcVicDisable,
                                    TimerVicEnable, TimerVicDisable
                                  };

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

