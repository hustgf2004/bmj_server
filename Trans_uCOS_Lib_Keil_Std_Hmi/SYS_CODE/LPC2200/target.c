/****************************************Copyright (c)****************************************************
**                              
**
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           target.c
** Last modified Date:  2012-12-31
** Last Version:        1.0
** Descriptions:        lpc22xx（飞利浦的ARM）目标板特殊的代码，包括异常处理程序和目标板初始化程序
**                      每个工程应当具有这个文件的拷贝，用户根据程序的需要修改本文件。
**--------------------------------------------------------------------------------------------------------
** Created by:          
** Created date:        2012-12-31
** Version:             V1.0
** Descriptions:        The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
*********************************************************************************************************/
#define IN_TARGET
#include    "..\..\USER_CODE\main.h"

#define     __SD2405    0x64

/*
 *  数据转换
 */
#define    BCD_TO_HEC(b)    ((((b) >> 4) * 10) + ((b) & 0x0f))
#define    HEC_TO_BCD(h)    ((((h) / 10) << 4) | ((h) % 10))

/*********************************************************************************************************
** Function name:           upSysTime
** Descriptions:            Update the system time 
** input parameters:        None
** output parameters:       None
** Returned value:          None
** Created by:              LinEnqiang
** Created Date:            2011-01-18
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void upSysTime (void)
{    
    INT8U ucTimeBuff[7];
    INT8U ucAddr;
    INT8U ucAck;
    INT8S scArg[64] = {0};
    /*
     *  读时间
     */
    ucAddr = 0;
    memset(ucTimeBuff,0,sizeof(ucTimeBuff));
    i2cRead(I2C0, __SD2405, &ucAddr, 0, ucTimeBuff, 7,NULL);            /* 读数据                        */
    do {
        OSTimeDly(1);
        ucAck = i2cGetFlag(I2C0);
        if (((I2C_NOT_GET_BUS | I2C_ACK_ERR) & ucAck) != 0) {
            break;
        }
    } while((I2C_READ_END & ucAck) == 0);
    ucTimeBuff[0] = (INT8U)BCD_TO_HEC((ucTimeBuff[0]&0x7f));                  /* 秒                           */
    ucTimeBuff[1] = (INT8U)BCD_TO_HEC((ucTimeBuff[1]&0x7f));                  /* 分                           */
    ucTimeBuff[2] = (INT8U)BCD_TO_HEC((ucTimeBuff[2]&0x3f));                  /* 小时                         */
    ucTimeBuff[3] = (INT8U)BCD_TO_HEC((ucTimeBuff[3]&0x07));                  /* 星期                         */
    ucTimeBuff[4] = (INT8U)BCD_TO_HEC((ucTimeBuff[4]&0x3f));                  /* 日                           */
    ucTimeBuff[5] = (INT8U)BCD_TO_HEC((ucTimeBuff[5]&0x1f));                  /* 月                           */
    ucTimeBuff[6] = (INT8U)(BCD_TO_HEC(ucTimeBuff[6]));                 /* 年为20XX                     */
    
     snprintf(scArg, 64, "Year=%4d Month=%d Day=%d Week=%d Hour=%d Min=%d Sec=%d", ucTimeBuff[6] +2000, ucTimeBuff[5], ucTimeBuff[4], ucTimeBuff[3], ucTimeBuff[2], ucTimeBuff[1], ucTimeBuff[0]);
     rtcInit(RTC0, scArg, NULL);
    
}

/*********************************************************************************************************
** Function name:           sd2405Init
** Descriptions:            Initialize the system time
** input parameters:        The system time
** output parameters:       None
** Returned value:          None
** Created by:              LinEnqiang
** Created Date:            2011-01-18
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void sd2405Init (SD2405_TIME *pTime)
{
    INT8U ucTimeBuff[7];
    INT8U ucAddr;
    INT8U ucAck;
    
    /*
     *  允许写操作
     */
    ucAddr = 0x10;
    ucTimeBuff[0] = 0x80;    
    i2cWrite(I2C0, __SD2405, &ucAddr, 1, ucTimeBuff, 1,NULL); 
    do {
        OSTimeDly(1);
        ucAck = i2cGetFlag(I2C0);
        if (((I2C_NOT_GET_BUS | I2C_ACK_ERR) & ucAck) != 0) {
            break;
        }
    } while((I2C_WRITE_END & ucAck) == 0);  
  
    ucAddr = 0x0F;
    ucTimeBuff[0] = 0x84;    
    i2cWrite(I2C0, __SD2405, &ucAddr, 1, ucTimeBuff, 1,NULL); 
    do {
        OSTimeDly(1);
        ucAck = i2cGetFlag(I2C0);
        if (((I2C_NOT_GET_BUS | I2C_ACK_ERR) & ucAck) != 0) {
            break;
        }
    } while((I2C_WRITE_END & ucAck) == 0);
    
    /*
     *  转化为BCD码
     */
    ucTimeBuff[0] = (INT8U)HEC_TO_BCD(pTime->ucSecond);                 /* 转化秒                       */
    ucTimeBuff[1] = (INT8U)HEC_TO_BCD(pTime->ucMinute);                 /* 转化分                       */
    ucTimeBuff[2] = (INT8U)HEC_TO_BCD(pTime->ucHour);                   /* 转化小时                     */
    ucTimeBuff[2] =  ucTimeBuff[2] | 0x80;                              /* 24小时制                     */
    
    ucTimeBuff[3] = (INT8U)HEC_TO_BCD(pTime->ucWeek);                   /* 转化星期                     */
    ucTimeBuff[4] = (INT8U)HEC_TO_BCD(pTime->ucDay);                    /* 转化日                       */
    ucTimeBuff[5] = (INT8U)HEC_TO_BCD(pTime->ucMonth);                  /* 转化月                       */
    ucTimeBuff[6] = (INT8U)HEC_TO_BCD(pTime->usYear - 2000);            /* 转化年                       */

    ucAddr = 0x00;  
    i2cWrite(I2C0, __SD2405, &ucAddr, 1, ucTimeBuff, 7,NULL); 
    do {
        OSTimeDly(1);
        ucAck = i2cGetFlag(I2C0);
        if (((I2C_NOT_GET_BUS | I2C_ACK_ERR) & ucAck) != 0) {
            break;
        }
    } while((I2C_WRITE_END & ucAck) == 0);
    
    /*
     *  禁止写操作
     */
    ucAddr = 0x0F;
    ucTimeBuff[0] = 0x00; 
    ucTimeBuff[1] = 0x00;    
    i2cWrite(I2C0, __SD2405, &ucAddr, 1, ucTimeBuff, 2,NULL); 
    do {
        OSTimeDly(1);
        ucAck = i2cGetFlag(I2C0);
        if (((I2C_NOT_GET_BUS | I2C_ACK_ERR) & ucAck) != 0) {
            break;
        }
    } while((I2C_WRITE_END & ucAck) == 0);
    upSysTime();
    return;
}

/*********************************************************************************************************
** Function name:           sd2405Read
** Descriptions:            read the system time
** input parameters:        The system time point
** output parameters:       The system time
** Returned value:          成功： OPERATE_SUCCESS
**                          失败： -OPERATE_FAIL
** Created by:              LinEnqiang
** Created Date:            2011-01-18
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
INT32S sd2405Read (SD2405_TIME *pTime)
{
    INT8U ucTimeBuff[7];
    INT8U ucAddr;
    INT8U ucAck;
    /*
     *  读时间
     */
    ucAddr = 0;
    memset(ucTimeBuff,0,sizeof(ucTimeBuff));
    i2cRead(I2C0, __SD2405, &ucAddr, 0, ucTimeBuff, 7,NULL);           /* 读数据                       */
    do {
        OSTimeDly(1);
        ucAck = i2cGetFlag(I2C0);
        if (((I2C_NOT_GET_BUS | I2C_ACK_ERR) & ucAck) != 0) {
            break;
        }
    } while((I2C_READ_END & ucAck) == 0);
    if (I2C_READ_END != ucAck) {
        return -OPERATE_FAIL;
    }
    pTime->ucSecond = (INT8U)BCD_TO_HEC((ucTimeBuff[0]&0x7f));          /* 秒                           */
    pTime->ucMinute = (INT8U)BCD_TO_HEC((ucTimeBuff[1]&0x7f));          /* 分                           */
    pTime->ucHour   = (INT8U)BCD_TO_HEC((ucTimeBuff[2]&0x3f));          /* 小时                         */
    pTime->ucWeek   = (INT8U)BCD_TO_HEC((ucTimeBuff[3]&0x07));          /* 星期                         */
    pTime->ucDay    = (INT8U)BCD_TO_HEC((ucTimeBuff[4]&0x3f));          /* 日                           */
    pTime->ucMonth  = (INT8U)BCD_TO_HEC((ucTimeBuff[5]&0x1f));          /* 月                           */
    pTime->usYear   = (INT32U)(BCD_TO_HEC(ucTimeBuff[6])+2000);         /* 年为20XX                     */
    return OPERATE_SUCCESS;
}

/*********************************************************************************************************
** 函数名称: Timer0_Exception
** 功能描述: 定时器0中断服务程序
** 输　入: 无
**
** 输　出: 无
**         
** 全局变量: 无
** 调用模块: OSTimeTick
**
** 作　者: 陈明计
** 日　期: 2004年2月2日
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

 static void __osTimerIsr (void)
{
    T0IR = 0x01;
    VICVectAddr = 0;                                                    /*  通知中断控制器中断结束      */
    OSTimeTick();
  
}
/*********************************************************************************************************
** 函数名称: Timer0Init
** 功能描述: 定时器0初始化
** 输　入: 无
**
** 输　出: 无
**         
** 全局变量: 无
** 调用模块: 无
**
** 作　者: 陈明计
** 日　期: 2002年4月4日
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void __osTimerInit(void)
{
    T0IR  = 0xffffffff;
    T0TCR = 0x03;
    T0TC  = 0;
    T0MCR = 0x03;
    T0MR0 = (FPCLK / OS_TICKS_PER_SEC);
    T0TCR = 0x01;
    vicIrqFuncSet(TIMER0_IRQ_CHN, 0, (INT32U)__osTimerIsr);
 }

/*********************************************************************************************************
** 函数名称: TargetInit
** 功能描述: 目标板初始化代码，在需要的地方调用，根据需要改变
** 输　入: 无
**
** 输　出: 无
**         
** 全局变量: 无
** 调用模块: 无
**
** 作　者: 陈明计
** 日　期: 2004年2月2日
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void targetInit(void)
{
    /*
     *  系统参数初始化
     */    
    if (SYS_OK != sysIfInit()) {
        while (1) {
            ;
        }
    }
    
    sysInit(FOSC, FCCLK, FCCO, FPCLK, OS_TICKS_PER_SEC);                                                 
    __osTimerInit();                                                    /*  系统时钟初始化              */
    
    //srand((uint32) targetInit);

    i2cInit(I2C0, "Speed=400000", NULL);                             /*  I2C初始化                   */
    vicIrqFuncSet(I2C0_IRQ_CHN, 6, (INT32U)I2C0_ISR);
      
    //eintInit(EINT2, SET_INTMODE, "Mode=0");                          /*  下降沿触发中断              */        
    //vicIrqFuncSet(EINT2_IRQ_CHN, 5, (INT32U)EINT2_ISR);
    
    //gpioSet(P0_10);                                                     /*  键盘进入工作                */
    //gpioSet(P1_25);                                                     /*  开启数字传感器电源          */     
    //gpioSet(P2_21);                                                     /*  开启电磁阀&模拟传感器电源   */
    //adcInit(ADC0, "Mode=1 Channel=0x3F Preci=10 Speed=100000", NULL);
    //vicIrqFuncSet(ADC0_IRQ_CHN,13,(INT32U)ADC0_ISR);
    //adcStart(ADC0);
    /*
     *  设备初始化
     */ 
    tpInit();
    tpUsrInit();
    

}


/*********************************************************************************************************
  以下为一些与系统相关的库函数的实现
  具体作用请ads的参考编译器与库函数手册
  用户可以根据自己的要求修改
*********************************************************************************************************/
/*********************************************************************************************************
  The implementations for some library functions
  For more details, please refer to the ADS compiler handbook and The library
  function manual
  User could change it as needed
*********************************************************************************************************/
#pragma import(__use_no_semihosting_swi)
#pragma import(__use_two_region_memory)

void _ttywrch (int ch)
{
    ch = ch;
}

/*********************************************************************************************************
  End File
*********************************************************************************************************/
