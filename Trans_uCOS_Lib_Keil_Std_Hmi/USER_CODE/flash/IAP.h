/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               iap.h
** Latest modified Date:    2014-12-23
** Latest Version:          1.0
** Descriptions:            iap�����ӿ�
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2014-12-23
** Version:                 1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
*********************************************************************************************************/
#ifndef __IAP_H
#define	__IAP_H
/*
 *  ����ID
 */
#define     __MCU_LPC2109_ID    0x0201FF01                              /*  LPC2109 ID ��               */   
#define     __MCU_LPC2119_ID    0x0201FF12                              /*  LPC2119 ID ��               */   
#define     __MCU_LPC2129_ID    0x0201FF13                              /*  LPC2129 ID ��               */   
#define     __MCU_LPC2114_ID    0x0101FF12                              /*  LPC2114 ID ��               */   
#define     __MCU_LPC2124_ID    0x0101FF13                              /*  LPC2124 ID ��               */   
#define     __MCU_LPC2194_ID    0x0301FF13                              /*  LPC2194 ID ��               */   
#define     __MCU_LPC2292_ID    0x0401FF13                              /*  LPC2292 ID ��               */   
#define     __MCU_LPC2294_ID    0x0501FF13                              /*  LPC2294 ID ��               */   
#define     __MCU_LPC2214_ID    0x0601FF13                              /*  LPC2214 ID ��               */   
#define     __MCU_LPC2212_ID    0x0401FF12                              /*  LPC2212 ID ��               */   

#define     __MCU_LPC2131_ID    0x0002FF01                              /*  LPC2131 ID ��               */   
#define     __MCU_LPC2132_ID    0x0002FF11                              /*  LPC2132 ID ��               */   
#define     __MCU_LPC2134_ID    0x0002FF12                              /*  LPC2134 ID ��               */   
#define     __MCU_LPC2136_ID    0x0002FF23                              /*  LPC2136 ID ��               */   
#define     __MCU_LPC2138_ID    0x0002FF25                              /*  LPC2138 ID ��               */

/* 
 *  ����IAP������
 */                                     
#define     IAP_PREPARE                                50               /* ѡ������                     */
                                                                        /* ����ʼ�����š����������š�   */                    
#define     IAP_RAMTOFLASH                             51               /* �������� FLASHĿ���ַ       */
                                                                        /* RAMԴ��ַ    ����д���ֽ���  */
                                                                        /* ϵͳʱ��Ƶ�ʡ�               */
#define     IAP_ERASESECTOR                            52               /* ��������    ����ʼ������     */
                                                                        /* ���������š�ϵͳʱ��Ƶ�ʡ�   */
#define     IAP_BLANKCHK                               53               /* �������    ����ʼ�����š�   */
                                                                        /* ���������š�                 */
#define     IAP_READPARTID                             54               /* ������ID    ���ޡ�           */
#define     IAP_BOOTCODEID                             55               /* ��Boot�汾�š��ޡ�           */
#define     IAP_COMPARE                                56               /* �Ƚ�����    ��Flash��ʼ��ַ  */
                                                                        /* RAM��ʼ��ַ����Ҫ�Ƚϵ�      */
                                                                        /* �ֽ�����                     */
/*
 *  ����IAP����״̬��
 */
#define     CMD_SUCCESS                                0
#define     INVALID_COMMAND                            1
#define     SRC_ADDR_ERROR                             2 
#define     DST_ADDR_ERROR                             3
#define     SRC_ADDR_NOT_MAPPED                        4
#define     DST_ADDR_NOT_MAPPED                        5
#define     COUNT_ERROR                                6
#define     INVALID_SECTOR                             7
#define     SECTOR_NOT_BLANK                           8
#define     SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION    9
#define     COMPARE_ERROR                              10
#define     BUSY                                       11
#define     SRC_BUF_NOT_MAPPED                         128


#define IAP_ENTER_ADR   0x7FFFFFF1                                      /* IAP��ڵ�ַ����              */
#define IAP_Entry(a, b) ((void (*)())(IAP_ENTER_ADR))(a, b)

/*********************************************************************************************************
** Function name:       sysSectorPrepare
** Descriptions:        IAP��������ѡ���������50
** input parameters:    sec1:           ��ʼ����
**                      sec2:           ��ֹ����
** output parameters:   paramout[0]:    IAP����״̬��,IAP����ֵ     
** Returned value:      paramout[0]:    IAP����״̬��,IAP����ֵ                     
*********************************************************************************************************/
extern INT32U  iapSectorPrepare (INT8U sec1, INT8U sec2);

/*********************************************************************************************************
** Function name:       sysRamToFlash
** Descriptions:        ����RAM�����ݵ�FLASH���������51
** input parameters:    dst:            Ŀ���ַ����FLASH��ʼ��ַ����512�ֽ�Ϊ�ֽ�
**                      src:            Դ��ַ����RAM��ַ����ַ�����ֶ���
**                      no:             �����ֽڸ�����Ϊ512/1024/4096/8192
** output parameters:   paramout[0]:    IAP����״̬��,IAP����ֵ     
** Returned value:      paramout[0]:    IAP����״̬��,IAP����ֵ                     
*********************************************************************************************************/
extern INT32U  iapRamToFlash (INT32U dst, INT32U src, INT32U no);

/*********************************************************************************************************
** Function name:       sysSectorErase
** Descriptions:        �����������������52
** input parameters:    sec1            ��ʼ����
**                      sec2            ��ֹ����92
** output parameters:   paramout[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      paramout[0]:    IAP����״̬��,IAP����ֵ                     
*********************************************************************************************************/
extern INT32U  iapSectorErase (INT8U sec1, INT8U sec2);

/*********************************************************************************************************
** Function name:       sysBlankChk
** Descriptions:        ������գ��������53
** input parameters:    sec1:           ��ʼ����
**                      sec2:           ��ֹ����92
** output parameters:   paramout[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      paramout[0]:    IAP����״̬��,IAP����ֵ                     
*********************************************************************************************************/
extern INT32U  iapBlankChk (INT8U sec1, INT8U sec2);

/*********************************************************************************************************
** Function name:       sysParIdRead
** Descriptions:        ������ID���������54
** input parameters:    ��
** output parameters:   paramout[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      paramout[0]:    IAP����״̬��,IAP����ֵ                     
*********************************************************************************************************/
extern  INT32U  iapParIdRead (void);

/*********************************************************************************************************
** Function name:       sysCodeIdBoot
** Descriptions:        ��Boot�汾���������55
** input parameters:    ��
** output parameters:   paramout[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      paramout[0]:    IAP����״̬��,IAP����ֵ                     
*********************************************************************************************************/
extern INT32U  iapCodeIdBoot (void);

/*********************************************************************************************************
** Function name:       sysDataCompare
** Descriptions:        У�����ݣ��������56
** input parameters:    dst:            Ŀ���ַ����RAM/FLASH��ʼ��ַ����ַ�����ֶ���
**                      src:            Դ��ַ����FLASH/RAM��ַ����ַ�����ֶ���
**                      no:             �����ֽڸ����������ܱ�4����
** output parameters:   paramout[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      paramout[0]:    IAP����״̬��,IAP����ֵ                     
*********************************************************************************************************/
extern INT32U  iapDataCompare (INT32U dst, INT32U src, INT32U no);
typedef struct __param_flash {
    INT32U  uiParamSector0;                                             /*  ����0����                   */
    INT32U  uiParamSector1;                                             /*  ����1����                   */
    INT32U  uiParamAddr0;                                               /*  ����0�׵�ַ                 */
    INT32U  uiParamAddr1;                                               /*  ����1�׵�ַ                 */
    INT32U  uiUsrCodeStartSector;                                       /*  �û�������ʼ����            */
    INT32U  uiUsrCodeEndSector;                                         /*  �û������������            */
    INT32U  uiRsvCodeStartSector;                                       /*  ����������ʼ����            */
    INT32U  uiRsvCodeEndSector;                                         /*  ���������������            */
    INT32U  uiRsvCodeSectorSize;                                        /*  ����������������            */
    INT32U  uiUsrCodeAddr;                                              /*  �û������׵�ַ              */
    INT32U  uiRsvCodeAddr;                                              /*  ���������׵�ַ              */
    INT32U  uiUsrCodeMaxLen;
} __PARAM_FLASH, *__PPARAM_FLASH;

#endif

