/***********************************************Copyright (c)********************************************* 
**                                
**                                      
**                                       
** 
**--------------File Info--------------------------------------------------------------------------------- 
** File name:               adc_in.c 
** Last modified Date:      2013-03-15 
** Last Version:            1.0 
** Descriptions:            adc驱动内部头文件
** 
**-------------------------------------------------------------------------------------------------------- 
** Created by:              
** Created date:            2013-03-15 
** Version:                 1.0 
** Descriptions:            
** 
**-------------------------------------------------------------------------------------------------------- 
** Modified by:             
** Modified Date:           
** Version:                 
** Descriptions:            
** 
*********************************************************************************************************/ 
#ifndef __ADC_IN_H                                                      
#define __ADC_IN_H 
#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */ 
/********************************************************************************************************* 
   操作参数返回,用户不可修改 
*********************************************************************************************************/ 
#define ADC_OK                          OPERATE_SUCCESS                 /*  ADC操作成功                 */                 
#define ADC_NOK                         OPERATE_FAIL                    /*  ADC操作失败                 */
#define ADC_PARA_ERR                    0xFE
#define ADC_PIN_ERR                     0xFD                            /*  管脚设置错误                */ 
/********************************************************************************************************* 
  ADC 最大个数定义 
*********************************************************************************************************/ 

#define __ADC_CHN_NUM                   8                               /*  LPC22xx 最多ADC采样通道数   */ 

#define __ADC_BASE_ADDR                 0xE0034000                      /*  ADC控制器寄存器基址         */   
#define __ADC0_BASE_ADDR                0xE0034000
          
/********************************************************************************************************* 
  ADC 寄存器偏移地址  
*********************************************************************************************************/ 
#define __B_ADC_CR                      0x00 
#define __B_ADC_DR                      0x01 
 
/********************************************************************************************************* 
  ADC 寄存器字长偏移地址宏参数 
*********************************************************************************************************/ 
#define __ADC_OFFSET_BASE               0 


/********************************************************************************************************* 
  ADC 采样最大速度 
*********************************************************************************************************/
#define __ADC_MAX_SPEED                 4500000                   

/*********************************************************************************************************
  ADC 采样通道号
*********************************************************************************************************/
#define ADC_AIN0            0
#define ADC_AIN1            1
#define ADC_AIN2            2
#define ADC_AIN3            3
#define ADC_AIN4            4
#define ADC_AIN5            5
#define ADC_AIN6            6
#define ADC_AIN7            7

/*********************************************************************************************************
  ADC 获取状态定义
*********************************************************************************************************/
#define ADC_GET_START       40
#define ADC_GET_STARTMODE   41
#define ADC_GET_USECHN      42
#define ADC_GET_DONECHN     43
#define ADC_GET_STATE       44

/*********************************************************************************************************
  ADC 读取转换结果操作方式定义
*********************************************************************************************************/
#define ADC_BUSY            10
#define ADC_IDLE            11

#define ADC_ERR             13
#define ADC_PAUSE           14
#define ADC_BUF_FULL        15  

#define ADC_STOP            20
#define ADC_START           21

#define ADC_SOFE            30
#define ADC_BURST           31 
#if 0
/********************************************************************************************************* 
  ADC 设备信息结构体 
*********************************************************************************************************/ 

struct __adc_info { 
    
    volatile    INT32U *puiBaseAddr;                                    /*  ADC寄存器基地址             */  
                INT32U  uiOffset;                                   /*  ADC寄存器偏移地址           */             
                INT32U  uiADCID;                                        /*  模数转换器ID编号            */ 
                 
                INT32U  uiAdcState;                                     /*  ADC状态标志.下面是状态标识  */ 
                                                                        /*  ADC_BUSY   :   通道工作忙   */ 
                                                                        /*  ADC_IDLE   :   通道空闲     */ 
                                                                        /*  ADC_OK     :   操作成功     */ 
                                                                        /*  ADC_ERR    :   操作失败     */ 
                                                                        /*  ADC_PAUSE  :   Burst转换暂停*/ 
                                                                        /*  ADC_BUF_FULL:  队列满       */ 
        
                INT32U  uiBurst;                                        /*  是否采用Burst模式           */ 
                INT32U  uiStart;                                        /*  是否已启动ADC               */ 
                                                                    
    volatile    INT8U   ucUseChn[__ADC_CHN_NUM];                        /*  记录已打开的采样通道        */ 
    volatile    INT8U   ucDoneFlg[__ADC_CHN_NUM];                       /*  对应通道是否已一次转换完成  */ 
                INT32U  uiChnNum;                                       /*  记录通道号个数值            */ 
 

                                                                         
//         __PDATA_QUEUE  AdcQueAddr;                                     /*  ADC采样结果缓冲队列指针     */ 
 
 
}; 
 
typedef struct __adc_info         __ADC_INFO;                           /*  定义结构体类型              */ 
typedef        __ADC_INFO        *__PADC_INFO;                          /*  定义结构体指针类型          */ 

/********************************************************************************************************* 
  ADC 采样数据结构体 
*********************************************************************************************************/  
struct __adc_data { 
 
                INT8U   ucMode;                                         /*  ADC工作模式                 */
                INT8U   ucChnFlg;                                       /*  数据有效标识                */
                INT8U   ucActCtrl;                                      /*  ADC软件控制模式的启动控制   */ 
                INT32U  uiData[__ADC_CHN_NUM];                          /*  ADC各个通道采样数据         */
                
}; 
 
typedef struct __adc_data         __ADC_DATA;                           /*  定义结构体类型              */ 
typedef        __ADC_DATA        *__PADC_DATA;                          /*  定义结构体指针类型          */  
 
#endif

/*********************************************************************************************************  
** Function name:         __adcInit  
**  
** Descriptions:          初始化模数转换器设备结构体，该函数被个初始化功能函数调用  
** Input parameters:      uiId              adc器件号  
**                        puiParaData       参数指针  
**                        pRsv              保留指针参数,可输入NULL.  
** Output parameters:     TRUE              操作失败  
** Returned value:        FALSE             操作成功  
**                       
**  
**                 
*********************************************************************************************************/   
extern BOOLEAN    __adcInit (INT32U  uiId, INT32U *puiParaData, void *pRsv);

/*********************************************************************************************************  
** Function name:      __adcIsr 
**  
** Descriptions:       adc中断服务内部函数 
** input parameters:   uiId                 adc器件号  
**                     pRsv                 保留指针参数,可输入NULL.  
** Output parameters:  NONE
** Returned value:     NONE
**   
*********************************************************************************************************/   
extern void __adcIsr (uint32 uiId, void *pRsv);   

/*********************************************************************************************************  
** Function name:         __adcSetSpeed  
**  
** Descriptions:          设置ADC采样时钟 
** Input parameters:      uiId              adc器件号  
**                        puiParaData       参数数组指针  
**                        pRsv              保留指针参数,可输入NULL.  
** Output parameters:     NONE  
** Returned value:        TRUE              操作成功  
**                        FALSE             操作失败  
**                    
*********************************************************************************************************/   
extern BOOLEAN __adcSetSpeed (INT32U uiId, INT32U *puiParaData, void *pRsv);

/*********************************************************************************************************  
** Function name:         __adcSetPdn  
**  
** Descriptions:          设置ADC掉电模式 
** Input parameters:      uiId              adc器件号  
**                        puiParaData       参数数组指针  
**                        pRsv              保留指针参数,可输入NULL.  
** Output parameters:     NONE  
** Returned value:        TRUE              操作成功  
**                        FALSE             操作失败  
**                  
*********************************************************************************************************/   
extern BOOLEAN __adcSetPdn (INT32U uiId, INT32U *puiParaData, void *pRsv);

/*********************************************************************************************************  
** Function name:         __adcSetCtrlChn  
**  
** Descriptions:          设置ADC通道 精度 启动方式
** Input parameters:      uiId              adc器件号  
**                        puiParaData       参数数组指针  
**                        pRsv              保留指针参数,可输入NULL.  
** Output parameters:     NONE  
** Returned value:        TRUE              操作成功  
**                        FALSE             操作失败  
**                     
*********************************************************************************************************/   
extern BOOLEAN __adcSetCtrlChn(INT32U uiId, INT32U *puiParaData, void *pRsv);

/*********************************************************************************************************  
** Function name:         __adcSetPreci  
**  
** Descriptions:          设置ADC精度
** Input parameters:      uiId              adc器件号  
**                        puiParaData       参数数组指针  
**                        pRsv              保留指针参数,可输入NULL.  
** Output parameters:     NONE  
** Returned value:        TRUE              操作成功  
**                        FALSE             操作失败  
**                      
*********************************************************************************************************/   
extern BOOLEAN __adcSetPreci (INT32U uiId, INT32U *puiParaData, void *pRsv);  

extern const INT32U     __GuiAdcBaseAddrTab[__ADC_MAX_NUM];
extern       BOOLEAN    __GucIsBurst[__ADC_MAX_NUM];                               
extern       INT8U      __GucDoneFlag[__ADC_MAX_NUM]; 
extern       INT8U      __GucActCtrl[__ADC_MAX_NUM];                                   
extern       INT32U     __GuiAdcDat[__ADC_MAX_NUM][__ADC_CHN_NUM];                   
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */
#endif                                                                  /*  __ADC_IN_H             */ 
/********************************************************************************************************* 
  END FILE 
*********************************************************************************************************/  