/****************************************Copyright (c)****************************************************
**                            
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               PressureSnr.c
** Latest modified Date:    2017-04-03
** Latest Version:          1.0
** Descriptions:            ѹ�����������ò˵�
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2017-04-03
** Version:                 1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

#include    "..\..\main.h"   
#include    ".\01LowPressureEn\LowPressureEn.h"
#include    ".\02LowPressureRange\LowPressureRange.h"
#include    ".\03MidPressureEn\MidPressureEn.h"
#include    ".\04MidPressureRange\MidPressureRange.h"
#include    ".\05HighPressureEn\HighPressureEn.h"
#include    ".\06HighPressureRange\HighPressureRange.h"
#include    ".\07ChargingPressureEn\ChargingPressureEn.h"
#include    ".\08ChargingPressureRange\ChargingPressureRange.h"
#include    ".\09LowPressureSample\LowPressureSample.h"
#include    ".\10MidPressureSample\MidPressureSample.h"
#include    ".\11HighPressureSample\HighPressureSample.h"
#include    ".\12ChargingPressureSample\ChargingPressureSample.h"
#include    ".\13LowPDeltaThreshold\LowPDeltaThreshold.h"
#include    ".\14MidPDeltaThreshold\MidPDeltaThreshold.h"
#include    ".\15HighPDeltaThreshold\HighPDeltaThreshold.h"
#include    ".\16ClosePDeltaThreshold\ClosePDeltaThreshold.h"
/*********************************************************************************************************
  �ⲿ����
*********************************************************************************************************/


/*********************************************************************************************************
  ��������
*********************************************************************************************************/
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemDel(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiibThis, INT16U usLen, void *pvData);
static INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv);

/*********************************************************************************************************
  ȫ�ֱ�������
*********************************************************************************************************/


/*********************************************************************************************************
  �ڲ�ʹ�ñ���
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifPressureSnr = {
    __menuItemCreate,
    __menuItemDel,
    __menuItemOnKey,
    __menuItemParamFmt
};
const  char *const __SscEnStr[2] = {"��",      "��"};

INT8U    __SucEnFlag;
/*********************************************************************************************************
** Function name:           menuItemCreate
** Descriptions:            �����˵���
** input parameters:        pmiiThis    �˵�����Ϣ
** output parameters:       none
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�afxMenu.h
** Created by:              
** Created Date:            2017-04-03
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT32S __menuItemCreate (MENU_ITEM_INFO *pmiiThis)
{
    INT32S      siErr = 0;
    
    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */
    if (GdsDevStatus.ucAuthority.ucAuthorityLevel == DEVELOPER_LEVEL) {
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibLowPressureEn); 
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibLowPressureRange);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibLowPDeltaThreshold);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibMidPressureEn); 
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibMidPressureRange);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibMidPDeltaThreshold);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibHighPressureEn);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibHighPressureRange);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibHighPDeltaThreshold);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibChargingPressureEn);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibChargingPressureRange);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibClosePDeltaThreshold);
    }
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibLowPressureSample);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibMidPressureSample);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibHighPressureSample);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibChargingPressureSample);
    
    return siErr;
}

/*********************************************************************************************************
** Function name:           menuItemDel
** Descriptions:            ɾ���˵���
** input parameters:        pmiiThis    �˵�ҳ��Ϣ
** output parameters:       none
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�afxMenu.h
** Created by:              
** Created Date:            2017-04-03
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT32S __menuItemDel (MENU_ITEM_INFO *pmiiThis)
{

    /*
     *
     */
    return SYS_OK;    
}

/*********************************************************************************************************
** Function name:           menuItemOnKey
** Descriptions:            �˵������Ӧ����
** input parameters:        pmiiThis    �˵�ҳ��Ϣ
**                          usLen       ���������ݳ���
**                          pvData      ����������ָ��
** output parameters:       none
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�afxMenu.h
** Created by:              
** Created Date:            2017-04-03
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT32S __menuItemOnKey (MENU_ITEM_INFO *pmiiThis, INT16U usLen, void *pvData)
{
    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */
    return SYS_OK;  
}

/*********************************************************************************************************
** Function name:           menuItemParamFmt
** Descriptions:            �˵�����ʾ����
** input parameters:        pmiiThis    �˵�����Ϣ
**                          
**                                
** output parameters:       pvRsv       �ַ������ָ��
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�afxMenu.h
** Created by:              
** Created Date:            2017-04-03
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv)
{
    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */
    return SYS_OK;
}

/*********************************************************************************************************
  ѹ���������˵�ҳ����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibPressureSnr = {                 /*  �˵�ҳ��Ϣ                  */
    "ѹ������������",
    (MENU_ITEM_FUNC *)&GmifPressureSnr,
    0x1400
};

/*********************************************************************************************************
** Function name:           miPressureSnrInit
** Descriptions:            ѹ�����������ò˵�ҳ��ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miPressureSnrInit (void)
{ 
    /*
     *  ��Ӳ˵�ҳ
     */
    miAdd(&__GmiibRoot, &__GmiibPressureSnr);
}
/*********************************************************************************************************
** Function name:           miPressureSnrDel
** Descriptions:            ѹ�����������ò˵�ҳж��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miPressureSnrDel (void)
{ 
    /*
     *  ɾ���˵�ҳ
     */
    miDel(&__GmiibPressureSnr);
}


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
