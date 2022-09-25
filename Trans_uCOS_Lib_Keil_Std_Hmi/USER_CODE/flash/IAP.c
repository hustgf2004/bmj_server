#include "main.h"

/* 
 *  ����CCLKֵ��С����λΪKHz 
 */
#define  IAP_FCCLK            (48000)
#define  IAP_ENTER_ADR        0x7FFFFFF1                                /*  IAP��ڵ�ַ����             */

/*
 *  ���庯��ָ��  
 */
INT32U  paramIn[8];                                                     /*  IAP��ڲ���������           */
INT32U  paramOut[8];                                                    /*  IAP���ڲ���������           */

/*********************************************************************************************************
** Function name:       sysSectorPrepare
** Descriptions:        IAP��������ѡ���������50
** input parameters:    sec1:           ��ʼ����
**                      sec2:           ��ֹ����
** output parameters:   paramOut[0]:    IAP����״̬��,IAP����ֵ     
** Returned value:      paramOut[0]:    IAP����״̬��,IAP����ֵ                     
*********************************************************************************************************/
INT32U  iapSectorPrepare (INT8U sec1, INT8U sec2)
{     
    paramIn[0] = IAP_PREPARE;                                           /*  ����������                  */
    paramIn[1] = sec1;                                                  /*  ���ò���                    */
    paramIn[2] = sec2;                            
    IAP_Entry(paramIn, paramOut);                                       /*  ����IAP�������             */
   
    return (paramOut[0]);                                               /*  ����״̬��                  */
}

/*********************************************************************************************************
** Function name:       ramCopy
** Descriptions:        ����RAM�����ݵ�FLASH���������51
** input parameters:    dst:            Ŀ���ַ����FLASH��ʼ��ַ����512�ֽ�Ϊ�ֽ�
**                      src:            Դ��ַ����RAM��ַ����ַ�����ֶ���
**                      no:             �����ֽڸ�����Ϊ512/1024/4096/8192
** output parameters:   paramOut[0]:    IAP����״̬��,IAP����ֵ     
** Returned value:      paramOut[0]:    IAP����״̬��,IAP����ֵ                     
*********************************************************************************************************/
INT32U  iapRamToFlash (INT32U dst, INT32U src, INT32U no)
{  
    paramIn[0] = IAP_RAMTOFLASH;                                        /*  ����������                  */
    paramIn[1] = dst;                                                   /*  ���ò���                    */
    paramIn[2] = src;
    paramIn[3] = no;
    paramIn[4] = IAP_FCCLK;
    IAP_Entry(paramIn, paramOut);                                       /*  ����IAP�������             */
    
    return (paramOut[0]);                                               /*  ����״̬��                  */
}

/*********************************************************************************************************
** Function name:       sysSectorErase
** Descriptions:        �����������������52
** input parameters:    sec1            ��ʼ����
**                      sec2            ��ֹ����92
** output parameters:   paramOut[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      paramOut[0]:    IAP����״̬��,IAP����ֵ                     
*********************************************************************************************************/
INT32U  iapSectorErase (INT8U sec1, INT8U sec2)
{  
    paramIn[0] = IAP_ERASESECTOR;                                       /*  ����������                  */
    paramIn[1] = sec1;                                                  /*  ���ò���                    */
    paramIn[2] = sec2;
    paramIn[3] = IAP_FCCLK;
    IAP_Entry(paramIn, paramOut);                                       /*  ����IAP�������             */
   
    return (paramOut[0]);                                               /*  ����״̬��                  */
}

/*********************************************************************************************************
** Function name:       blankChk
** Descriptions:        ������գ��������53
** input parameters:    sec1:           ��ʼ����
**                      sec2:           ��ֹ����92
** output parameters:   paramOut[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      paramOut[0]:    IAP����״̬��,IAP����ֵ                     
*********************************************************************************************************/
INT32U  iapBlankChk (INT8U sec1, INT8U sec2)
{  
    paramIn[0] = IAP_BLANKCHK;                                          /*  ����������                  */
    paramIn[1] = sec1;                                                  /*  ���ò���                    */
    paramIn[2] = sec2;
    IAP_Entry(paramIn, paramOut);                                       /*  ����IAP�������             */

    return (paramOut[0]);                                               /*  ����״̬��                  */
}

/*********************************************************************************************************
** Function name:       parIdRead
** Descriptions:        ������գ��������54
** input parameters:    ��
** output parameters:   paramOut[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      paramOut[0]:    IAP����״̬��,IAP����ֵ                     
*********************************************************************************************************/
INT32U  iapParIdRead (void)
{  
    paramIn[0] = IAP_READPARTID;                                        /*  ����������                  */
    IAP_Entry(paramIn, paramOut);                                       /*  ����IAP�������             */

    return (paramOut[1]);                                               /*  ����״̬��                  */
}

/*********************************************************************************************************
** Function name:       codeIdBoot
** Descriptions:        ������գ��������55
** input parameters:    ��
** output parameters:   paramOut[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      paramOut[0]:    IAP����״̬��,IAP����ֵ                     
*********************************************************************************************************/
INT32U  iapCodeIdBoot (void)
{  
    paramIn[0] = IAP_BOOTCODEID;                                        /*  ����������                  */
    IAP_Entry(paramIn, paramOut);                                       /*  ����IAP�������             */

    return (paramOut[1]);                                               /*  ����״̬��                  */
}

/*********************************************************************************************************
** Function name:       dataCompare
** Descriptions:        У�����ݣ��������56
** input parameters:    dst:            Ŀ���ַ����RAM/FLASH��ʼ��ַ����ַ�����ֶ���
**                      src:            Դ��ַ����FLASH/RAM��ַ����ַ�����ֶ���
**                      no:             �����ֽڸ����������ܱ�4����
** output parameters:   paramOut[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      paramOut[0]:    IAP����״̬��,IAP����ֵ                     
*********************************************************************************************************/
INT32U  iapDataCompare (INT32U dst, INT32U src, INT32U no)
{  
    paramIn[0] = IAP_COMPARE;                                           /*  ����������                  */
    paramIn[1] = dst;                                                   /*  ���ò���                    */
    paramIn[2] = src;
    paramIn[3] = no;
    IAP_Entry(paramIn, paramOut);                                       /*  ����IAP�������             */

    return (paramOut[0]);                                               /*  ����״̬��                  */
}
