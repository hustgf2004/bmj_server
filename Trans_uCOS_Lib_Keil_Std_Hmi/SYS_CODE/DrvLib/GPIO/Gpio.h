/****************************************Copyright (c)****************************************************
**                                                       
**                                     
**                               
**
**--------------File Info---------------------------------------------------------------------------------
**  File name:              GPIO.h
**  Last modified Date:
**  Last Version:           V1.0
**  Descriptions:           LPC2200系列CPU引脚GPIO驱动
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2012-12-31
** Version: V1.0
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:
** Descriptions:            
**
*********************************************************************************************************/
#ifndef __GPIO_H_
#define __GPIO_H_
#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */
/*********************************************************************************************************
  P0
*********************************************************************************************************/
#define P0       100000
#define P0_00         0  
#define P0_01         1
#define P0_02         2
#define P0_03         3
#define P0_04         4
#define P0_05         5
#define P0_06         6
#define P0_07         7
#define P0_08         8
#define P0_09         9
#define P0_10        10
#define P0_11        11
#define P0_12        12       
#define P0_13        13        
#define P0_14        14       
#define P0_15        15

#define P0_16        16
#define P0_17        17
#define P0_18        18
#define P0_19        19
#define P0_20        20
#define P0_21        21
#define P0_22        22
#define P0_23        23
#define P0_24        24
#define P0_25        25
/*  #define P0_26     26        //（LPC2220中此位为无效位）*/
#define P0_27        27
#define P0_28        28
#define P0_29        29
#define P0_30        30
/*  #define P0_31     31      //（LPC2220中此位为无效位）*/

/*********************************************************************************************************
  P1
*********************************************************************************************************/

#define P1        110000
#define P1_00        100
#define P1_01        101

/*********************************************************************************************************
  以下位在LPC2220中为无效位
*********************************************************************************************************/
/*  #define P1_02      102 */     
/*  #define P1_03      103 */     
/*  #define P1_04      104 */
/*  #define P1_05      105 */    
/*  #define P1_06      106 */   
/*  #define P1_07      107 */   
/*  #define P1_08      108 */
/*  #define P1_09      109 */
/*  #define P1_10      110 */
/*  #define P1_11      111 */    
/*  #define P1_12      112 */   
/*  #define P1_13      113 */    
/*  #define P1_14      114 */
/*  #define P1_15      115 */

#define P1_16        116
#define P1_17        117
#define P1_18        118
#define P1_19        119
#define P1_20        120
#define P1_21        121
#define P1_22        122
#define P1_23        123
#define P1_24        124
#define P1_25        125
#define P1_26        126
#define P1_27        127
#define P1_28        128
#define P1_29        129
#define P1_30        130
#define P1_31        131

/*********************************************************************************************************
  P2
*********************************************************************************************************/

#define P2        120000
#define P2_00        200
#define P2_01        201
#define P2_02        202
#define P2_03        203
#define P2_04        204
#define P2_05        205
#define P2_06        206
#define P2_07        207
#define P2_08        208
#define P2_09        209
#define P2_10        210
#define P2_11        211
#define P2_12        212
#define P2_13        213
#define P2_14        214     
#define P2_15        215    

#define P2_16        216    
#define P2_17        217     
#define P2_18        218     
#define P2_19        219     
#define P2_20        220     
#define P2_21        221     
#define P2_22        222     
#define P2_23        223     
#define P2_24        224     
#define P2_25        225     
#define P2_26        226     
#define P2_27        227     
#define P2_28        228     
#define P2_29        229     
#define P2_30        230     
#define P2_31        231     

/*********************************************************************************************************
  P3
*********************************************************************************************************/

#define P3        130000
#define P3_00        300       
#define P3_01        301       
#define P3_02        302        
#define P3_03        303        
#define P3_04        304        
#define P3_05        305        
#define P3_06        306        
#define P3_07        307       
#define P3_08        308      
#define P3_09        309      
#define P3_10        310     
#define P3_11        311      
#define P3_12        312     
#define P3_13        313    
#define P3_14        314    
#define P3_15        315     

#define P3_16        316     
#define P3_17        317     
#define P3_18        318     
#define P3_19        319      
#define P3_20        320      
#define P3_21        321     
#define P3_22        322     
#define P3_23        323
#define P3_24        324
#define P3_25        325
#define P3_26        326
#define P3_27        327     
#define P3_28        328      
#define P3_29        329     
#define P3_30        330     
#define P3_31        331     


/*********************************************************************************************************
 P4
 LPC2220中无P4口
*********************************************************************************************************/
/*  #define P4      140000 */
/*  #define P4_00      400 */       
/*  #define P4_01      401 */      
/*  #define P4_02      402 */     
/*  #define P4_03      403 */     
/*  #define P4_04      404 */    
/*  #define P4_05      405 */      
/*  #define P4_06      406 */      
/*  #define P4_07      407 */     
/*  #define P4_08      408 */       
/*  #define P4_09      409 */     
/*  #define P4_10      410 */      
/*  #define P4_11      411 */      
/*  #define P4_12      412 */     
/*  #define P4_13      413 */     
/*  #define P4_14      414 */      
/*  #define P4_15      415 */     

/*  #define P4_16      416 */    
/*  #define P4_17      417 */  
/*  #define P4_18      418 */   
/*  #define P4_19      419 */  
/*  #define P4_20      420 */    
/*  #define P4_21      421 */     
/*  #define P4_22      422 */   
/*  #define P4_23      423 */     
/*  #define P4_24      424 */      
/*  #define P4_25      425 */     
/*  #define P4_26      426 */    
/*  #define P4_27      427 */    
/*  #define P4_28      428 */
/*  #define P4_29      429 */
/*  #define P4_30      430 */      
/*  #define P4_31      431 */       




 
/********************************************************************************************************* 
** Function name:           gpioSet 
** Descriptions:            GPIO设备输出高电平 
** Input parameters:        uiArg           GPIO设备引脚宏定义(端口引用名称) 
**                                          P0_00 ~ P0_31         
**                                          P1_16 ~ P1_31  
** Output parameters:       NONE 
** Returned value:          OPERATE_SUCCESS 操作成功
**                          -OPERATE_FAIL   操作失败                          
** Example:                 gpioSet( P0_00 );                        
*********************************************************************************************************/ 
INT32S gpioSet (INT32U uiArg); 
 
/********************************************************************************************************* 
** Function name:           gpioClr 
** Descriptions:            GPIO设备输出低电平 
** Input parameters:        uiArg           GPIO设备引脚宏定义(端口引用名称) 
**                                          P0_00 ~ P0_31         
**                                          P1_16 ~ P1_31  
** Output parameters:       NONE 
** Returned value:          OPERATE_SUCCESS 操作成功
**                          -OPERATE_FAIL   操作失败
** Example:                 gpioClr( P0_00 );                        
*********************************************************************************************************/ 
INT32S gpioClr (INT32U uiArg); 
 
/********************************************************************************************************* 
** Function name:           gpioGet 
** Descriptions:            获取GPIO设备端口电平 
** Input parameters:        uiArg           GPIO设备引脚宏定义(端口引用名称) 
**                                          P0_00 ~ P0_31         
**                                          P1_16 ~ P1_31  
** Output parameters:       NONE 
** Returned value:          1               高电平 
**                          0               低电平 
**                          -OPERATE_FAIL   操作失败 
** Example:                 gpioGet( P0_00 );                        
*********************************************************************************************************/ 
INT32S gpioGet (INT32U uiArg); 
 
/********************************************************************************************************* 
** Function name:           gpioCpl 
** Descriptions:            取反GPIO设备端口电平 
** Input parameters:        uiArg           GPIO设备引脚宏定义(端口引用名称) 
**                                          P0_00 ~ P0_31         
**                                          P1_16 ~ P1_31  
** Output parameters:       NONE 
** Returned value:          OPERATE_SUCCESS 操作成功
**                          -OPERATE_FAIL   操作失败  
** Example:                 gpioCpl( P0_00 );                        
*********************************************************************************************************/ 
INT32S gpioCpl (INT32U uiArg); 

/*********************************************************************************************************  
** Function name:           gpioDirOut  
** Descriptions:            设置GPIO口为输出状态  
** Input parameters:        uiArg           GPIO设备引脚宏定义(端口引用名称)  
**                                          P0_00 ~ P0_31          
**                                          P1_16 ~ P1_31   
** Output parameters:       NONE  
** Returned value:          OPERATE_SUCCESS 操作成功
**                          -OPERATE_FAIL   操作失败    
** Example:                 gpioCpl( P0_00 );                         
*********************************************************************************************************/   
extern INT32S gpioDirOut (INT32U uiArg);

/*********************************************************************************************************  
** Function name:           gpioDirIn  
** Descriptions:            设置GPIO口为输入状态  
** Input parameters:        uiArg           GPIO设备引脚宏定义(端口引用名称)  
**                                          P0_00 ~ P0_31          
**                                          P1_16 ~ P1_31   
** Output parameters:       NONE  
** Returned value:          OPERATE_SUCCESS 操作成功
**                          -OPERATE_FAIL   操作失败   
** Example:                 gpioCpl( P0_00 );                         
*********************************************************************************************************/   
extern INT32S gpioDirIn (INT32U uiArg);
#ifdef __cplusplus
}
#endif 
#endif                                                                  /* __GPIO_H                     */ 
/*********************************************************************************************************  
   END FILE  
*********************************************************************************************************/ 
