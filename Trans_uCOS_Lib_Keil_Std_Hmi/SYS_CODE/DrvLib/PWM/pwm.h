/****************************************Copyright (c)****************************************************
**                              
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Pwm.h
** Last modified Date:  2013-08-22
** Last Version:        1.0
** Descriptions:        LPC2200 PWM驱动
**--------------------------------------------------------------------------------------------------------
** Created by:          
** Created date:        2013-08-22
** Version:             V1.0
** Descriptions:        The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
*********************************************************************************************************/
#ifndef _PWM_H_
#define _PWM_H_
#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                */

/*********************************************************************************************************
  PWM 相关索引
*********************************************************************************************************/
#define PWM0                0                                           /*  PWM0 ID号                   */

#define PWM0_IRQ_CHN        8                                           /*  PWM0中断通道号              */

/*********************************************************************************************************
  PWM 模式配置命令
*********************************************************************************************************/
#define SET_TIMERMODE       0                                           /*  定时模式设置                */
#define SET_PWMMODE         3                                           /*  PWM模式设置                 */
#define SET_MRX             4                                           /*  设置匹配值命令              */

/*********************************************************************************************************
** Function name:           pwmInit
** Descriptions:            pwm初始化
** input parameters:        uiId            pwm器件号
**                          pcArg           配置参数字符串指针                                         
**                          pRsv            保留参数
** output parameters:       None
** Returned value:          OPERATE_SUCCESS 操作成功 
**                          -OPERATE_FAIL   操作失败
*********************************************************************************************************/
extern INT32S pwmInit(INT32U uiId, char *pcArg, void *pRsv);

/*********************************************************************************************************
** Function name:           pwmSetMode
** Descriptions:            pwm模式设置
** input parameters:        uiId            pwm器件号
**                          uiCmd           设置命令码
**                          pucArg          配置参数字符串指针
** output parameters:       None
** Returned value:          OPERATE_SUCCESS 操作成功 
**                          -OPERATE_FAIL   操作失败
*********************************************************************************************************/
extern INT32S pwmSetMode(INT32U uiId, INT32U uiCmd, char *pcArg);

/*********************************************************************************************************
** Function name:           pwmStart
** Descriptions:            pwm启动
** input parameters:        uiId            pwm器件号
**                                                          
**                      
** output parameters:       None
** Returned value:          OPERATE_SUCCESS 操作成功 
**                          -OPERATE_FAIL   操作失败
*********************************************************************************************************/
extern INT32S pwmStart(INT32U uiId);

/*********************************************************************************************************
** Function name:           pwmStop
** Descriptions:            pwm停止
** input parameters:        uiId            pwm器件号  
**                                                          
**                      
** output parameters:       None
** Returned value:          OPERATE_SUCCESS 操作成功 
**                          -OPERATE_FAIL   操作失败
*********************************************************************************************************/
extern INT32S pwmStop(INT32U uiId);

/*********************************************************************************************************
** Function name:           pwmReset
** Descriptions:            pwm复位
** input parameters:        uiId            pwm器件号
**                                                          
**                      
** output parameters:       None
** Returned value:          OPERATE_SUCCESS 操作成功 
**                          -OPERATE_FAIL   操作失败
*********************************************************************************************************/
extern INT32S pwmReset(INT32U uiId);

/*********************************************************************************************************
** Function name:           pwmGetTc
** Descriptions:            获得当前计数值
** input parameters:        uiId            pwm器件号
**                                                          
**                      
** output parameters:       None
** Returned value:          OPERATE_SUCCESS 操作成功 
**                          -OPERATE_FAIL   操作失败
*********************************************************************************************************/
extern INT32S pwmGetTc(INT32U uiId);

/*********************************************************************************************************
** Function name:       pwmIsr 
** Descriptions:        中断退出处理函数
** input parameters:    ulId    : 设备标示  
** output parameters:   None
** Returned value:      无
*********************************************************************************************************/
extern void pwmIsr(INT32U ulId);

#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */
#endif                                                                  /*  _PWM_H_                     */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
