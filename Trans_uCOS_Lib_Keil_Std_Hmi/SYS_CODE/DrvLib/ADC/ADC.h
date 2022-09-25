/****************************************Copyright (c)****************************************************
**                              
**
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           adc.h
** Last modified Date:  2013-03-15
** Last Version:        1.0
** Descriptions:        adc驱动外部头文件
**--------------------------------------------------------------------------------------------------------
** Created by:          
** Created date:        2013-03-15
** Version:             V1.0
** Descriptions:        The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
*********************************************************************************************************/
#ifndef _ADC_H_
#define _ADC_H_
#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
  ADC 相关索引
*********************************************************************************************************/
#define   ADC0              0                                           /*  ADC ID 号                   */

/*********************************************************************************************************
  ADC 中断通道号
*********************************************************************************************************/
#define   ADC0_IRQ_CHN      18                                          /*  ADC中断通道号               */

/*********************************************************************************************************
  ADC 模式配置命令
*********************************************************************************************************/
#define SET_SPEED           0                                           /*  更改ADC转换时钟             */
#define SET_POWERDWN        1                                           /*  设置ADC省电模式             */
#define SET_CTRLCHN         2                                           /*  设置特定模式下的所有参数命令*/

/*********************************************************************************************************  
** Function name:           adcInit  
**  
** Descriptions:            用户初始化接口函数,解释用户的字符串命令,并对ADC初始化及设置中断  
** Input parameters:        uiId            adc器件号
**                          pcArg           字符串参数指针
**                             
**  
**                          pRsv            保留指针参数,可输入NULL.  
** Output parameters:    
** Returned value:          OPERATE_SUCCESS 操作成功  
**                          -OPERATE_FAIL   操作失败
** Using example :          char *pcArg = "Chn=1 ADCClk=100000"; adcInit(0,pcArg,NULL);  
**
**********************************************************************************************************/   
extern INT32S adcInit (INT32U uiId, char  *pcArg, void  *pRsv);

/*********************************************************************************************************
** Function name:       adcSetMode
** Descriptions:        设置PWM参数、模式
** input parameters:    ulId    : 子设备号
**                      ulCmd   : 命令参数
**                      pucArg  : 配置参数字符窜指针
** output parameters:   None               
** Returned value:      操作成功:OPERATE_SUCCESS;
**                      操作失败:-OPERATE_FAIL
*********************************************************************************************************/
extern INT32S adcSetMode (INT32U ulId, INT32U ulCmd, char *pucArg);

/*********************************************************************************************************  
** Function name:      adcStart  
**  
** Descriptions:       启动ADC  
** input parameters:   uiId      --部件设备号:0-ADC0  
**                     pRsv      --保留指针参数,可输入NULL.  
** Output parameters:  OPERATE_FAIL    -- 操作失败  
** Returned value:     OPERATE_SUCCESS -- 操作成功  
** Notice :            启动之前,必须先进行ADC初始化.  
*********************************************************************************************************/   
extern INT32S adcStart (INT32U uiId);

/*********************************************************************************************************  
** Function name:           adcStop  
**  
** Descriptions:            停止adc
** input parameters:        uiId            adc器件号
**                      
** Output parameters:  
** Returned value:          OPERATE_SUCCESS 操作成功 
**                          -OPERATE_FAIL   操作失败  
**   
*********************************************************************************************************/   
extern INT32S adcStop (INT32U uiId);

/*********************************************************************************************************  
** Function name:           adcRead
**  
** Descriptions:            读取adc转换结果  
** input parameters:        uiId            adc器件号:0-ADC0  
**                          uiChnFlg        要读取结果的通道标识  
**                          pRsv            保留指针参数,可输入NULL.  
** Output parameters:        
** Returned value:          读取的通道标识  操作成功  
**                          -OPERATE_FAIL   操作失败
** 
** Using example :       
*********************************************************************************************************/   
extern INT32S adcRead (INT32U uiId, INT32S *puiBuf, INT8U ucChnFlg, void *pRsv);
                         
/*********************************************************************************************************  
** Function name:           adcSetMode  
**  
** Descriptions:            参数设置函数,解释用户的字符串命令,并对ADC进行设置及设置中断  
** input parameters:        uiId            adc器件号
**                          uiCmd           设置命令码
**                          SET_SPEED       更改ADC转换时钟
**                          SET_POWERDWN    设置ADC省电模式
**                          SET_CTRLCHN     设置特定模式下的所有参数命令
**                          pcArg           字符串参数指针   
**  
**                          pRsv            保留指针参数,可输入NULL.  
** Output parameters:         
** Returned value:          OPERATE_SUCCESS 操作成功  
**                          -OPERATE_FAIL   操作失败
**
** Using example :          char *pcArg = "Chn=1 ADCClk=100000"; adcSetMode(0,pcArg,NULL);   
*********************************************************************************************************/   
extern INT32S adcSetMode (INT32U uiId, INT32U uiCmd, char  *pcArg);

/*********************************************************************************************************  
** Function name:           adcIsr  
** Descriptions:            adc中断服务程序  
** input parameters:        无  
** Returned value:          无  
*********************************************************************************************************/   
extern void adcIsr (INT32U uiId);
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */
#endif                                                                  /*  _ADC_H_                     */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
