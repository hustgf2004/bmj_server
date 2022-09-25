/***********************************************Copyright (c)********************************************* 
**                                
**                                      
**                                       
** 
**--------------File Info--------------------------------------------------------------------------------- 
** File name:               adc_in.c 
** Last modified Date:      2013-03-15 
** Last Version:            1.0 
** Descriptions:            adc�����ڲ�ͷ�ļ�
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
   ������������,�û������޸� 
*********************************************************************************************************/ 
#define ADC_OK                          OPERATE_SUCCESS                 /*  ADC�����ɹ�                 */                 
#define ADC_NOK                         OPERATE_FAIL                    /*  ADC����ʧ��                 */
#define ADC_PARA_ERR                    0xFE
#define ADC_PIN_ERR                     0xFD                            /*  �ܽ����ô���                */ 
/********************************************************************************************************* 
  ADC ���������� 
*********************************************************************************************************/ 

#define __ADC_CHN_NUM                   8                               /*  LPC22xx ���ADC����ͨ����   */ 

#define __ADC_BASE_ADDR                 0xE0034000                      /*  ADC�������Ĵ�����ַ         */   
#define __ADC0_BASE_ADDR                0xE0034000
          
/********************************************************************************************************* 
  ADC �Ĵ���ƫ�Ƶ�ַ  
*********************************************************************************************************/ 
#define __B_ADC_CR                      0x00 
#define __B_ADC_DR                      0x01 
 
/********************************************************************************************************* 
  ADC �Ĵ����ֳ�ƫ�Ƶ�ַ����� 
*********************************************************************************************************/ 
#define __ADC_OFFSET_BASE               0 


/********************************************************************************************************* 
  ADC ��������ٶ� 
*********************************************************************************************************/
#define __ADC_MAX_SPEED                 4500000                   

/*********************************************************************************************************
  ADC ����ͨ����
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
  ADC ��ȡ״̬����
*********************************************************************************************************/
#define ADC_GET_START       40
#define ADC_GET_STARTMODE   41
#define ADC_GET_USECHN      42
#define ADC_GET_DONECHN     43
#define ADC_GET_STATE       44

/*********************************************************************************************************
  ADC ��ȡת�����������ʽ����
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
  ADC �豸��Ϣ�ṹ�� 
*********************************************************************************************************/ 

struct __adc_info { 
    
    volatile    INT32U *puiBaseAddr;                                    /*  ADC�Ĵ�������ַ             */  
                INT32U  uiOffset;                                   /*  ADC�Ĵ���ƫ�Ƶ�ַ           */             
                INT32U  uiADCID;                                        /*  ģ��ת����ID���            */ 
                 
                INT32U  uiAdcState;                                     /*  ADC״̬��־.������״̬��ʶ  */ 
                                                                        /*  ADC_BUSY   :   ͨ������æ   */ 
                                                                        /*  ADC_IDLE   :   ͨ������     */ 
                                                                        /*  ADC_OK     :   �����ɹ�     */ 
                                                                        /*  ADC_ERR    :   ����ʧ��     */ 
                                                                        /*  ADC_PAUSE  :   Burstת����ͣ*/ 
                                                                        /*  ADC_BUF_FULL:  ������       */ 
        
                INT32U  uiBurst;                                        /*  �Ƿ����Burstģʽ           */ 
                INT32U  uiStart;                                        /*  �Ƿ�������ADC               */ 
                                                                    
    volatile    INT8U   ucUseChn[__ADC_CHN_NUM];                        /*  ��¼�Ѵ򿪵Ĳ���ͨ��        */ 
    volatile    INT8U   ucDoneFlg[__ADC_CHN_NUM];                       /*  ��Ӧͨ���Ƿ���һ��ת�����  */ 
                INT32U  uiChnNum;                                       /*  ��¼ͨ���Ÿ���ֵ            */ 
 

                                                                         
//         __PDATA_QUEUE  AdcQueAddr;                                     /*  ADC��������������ָ��     */ 
 
 
}; 
 
typedef struct __adc_info         __ADC_INFO;                           /*  ����ṹ������              */ 
typedef        __ADC_INFO        *__PADC_INFO;                          /*  ����ṹ��ָ������          */ 

/********************************************************************************************************* 
  ADC �������ݽṹ�� 
*********************************************************************************************************/  
struct __adc_data { 
 
                INT8U   ucMode;                                         /*  ADC����ģʽ                 */
                INT8U   ucChnFlg;                                       /*  ������Ч��ʶ                */
                INT8U   ucActCtrl;                                      /*  ADC��������ģʽ����������   */ 
                INT32U  uiData[__ADC_CHN_NUM];                          /*  ADC����ͨ����������         */
                
}; 
 
typedef struct __adc_data         __ADC_DATA;                           /*  ����ṹ������              */ 
typedef        __ADC_DATA        *__PADC_DATA;                          /*  ����ṹ��ָ������          */  
 
#endif

/*********************************************************************************************************  
** Function name:         __adcInit  
**  
** Descriptions:          ��ʼ��ģ��ת�����豸�ṹ�壬�ú���������ʼ�����ܺ�������  
** Input parameters:      uiId              adc������  
**                        puiParaData       ����ָ��  
**                        pRsv              ����ָ�����,������NULL.  
** Output parameters:     TRUE              ����ʧ��  
** Returned value:        FALSE             �����ɹ�  
**                       
**  
**                 
*********************************************************************************************************/   
extern BOOLEAN    __adcInit (INT32U  uiId, INT32U *puiParaData, void *pRsv);

/*********************************************************************************************************  
** Function name:      __adcIsr 
**  
** Descriptions:       adc�жϷ����ڲ����� 
** input parameters:   uiId                 adc������  
**                     pRsv                 ����ָ�����,������NULL.  
** Output parameters:  NONE
** Returned value:     NONE
**   
*********************************************************************************************************/   
extern void __adcIsr (uint32 uiId, void *pRsv);   

/*********************************************************************************************************  
** Function name:         __adcSetSpeed  
**  
** Descriptions:          ����ADC����ʱ�� 
** Input parameters:      uiId              adc������  
**                        puiParaData       ��������ָ��  
**                        pRsv              ����ָ�����,������NULL.  
** Output parameters:     NONE  
** Returned value:        TRUE              �����ɹ�  
**                        FALSE             ����ʧ��  
**                    
*********************************************************************************************************/   
extern BOOLEAN __adcSetSpeed (INT32U uiId, INT32U *puiParaData, void *pRsv);

/*********************************************************************************************************  
** Function name:         __adcSetPdn  
**  
** Descriptions:          ����ADC����ģʽ 
** Input parameters:      uiId              adc������  
**                        puiParaData       ��������ָ��  
**                        pRsv              ����ָ�����,������NULL.  
** Output parameters:     NONE  
** Returned value:        TRUE              �����ɹ�  
**                        FALSE             ����ʧ��  
**                  
*********************************************************************************************************/   
extern BOOLEAN __adcSetPdn (INT32U uiId, INT32U *puiParaData, void *pRsv);

/*********************************************************************************************************  
** Function name:         __adcSetCtrlChn  
**  
** Descriptions:          ����ADCͨ�� ���� ������ʽ
** Input parameters:      uiId              adc������  
**                        puiParaData       ��������ָ��  
**                        pRsv              ����ָ�����,������NULL.  
** Output parameters:     NONE  
** Returned value:        TRUE              �����ɹ�  
**                        FALSE             ����ʧ��  
**                     
*********************************************************************************************************/   
extern BOOLEAN __adcSetCtrlChn(INT32U uiId, INT32U *puiParaData, void *pRsv);

/*********************************************************************************************************  
** Function name:         __adcSetPreci  
**  
** Descriptions:          ����ADC����
** Input parameters:      uiId              adc������  
**                        puiParaData       ��������ָ��  
**                        pRsv              ����ָ�����,������NULL.  
** Output parameters:     NONE  
** Returned value:        TRUE              �����ɹ�  
**                        FALSE             ����ʧ��  
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