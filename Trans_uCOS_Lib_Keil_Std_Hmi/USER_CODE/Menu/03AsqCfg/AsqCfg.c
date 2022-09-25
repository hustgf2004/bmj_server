/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn                              
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               AsqCfg.c
** Latest modified Date:    2021-12-26
** Latest Version:          1.0
** Descriptions:            �Զ��Ƽܲ������ò˵�
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ����������
** Created date:            2021-12-26
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
#include    ".\01AsqWarnTime\AsqWarnTime.h"
#include    ".\02FlipOutStartTime\FlipOutStartTime.h"
#include    ".\03FlipOutActTime\FlipOutActTime.h"
#include    ".\04PusherOutStartTime\PusherOutStartTime.h"
#include    ".\05PusherOutActTime\PusherOutActTime.h"
#include    ".\06FlipInStartTime\FlipInStartTime.h"
#include    ".\07FlipInActTime\FlipInActTime.h"
#include    ".\08PusherInStartTime\PusherInStartTime.h"
#include    ".\09PusherInActTime\PusherInActTime.h"

#include    ".\10LiftOutStartTime\LiftOutStartTime.h"
#include    ".\11LiftOutActTime\LiftOutActTime.h"
#include    ".\12LiftInStartTime\LiftInStartTime.h"
#include    ".\13LiftInActTime\LiftInActTime.h"
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
const MENU_ITEM_FUNC GmifAsqCfg = {
    __menuItemCreate,
    __menuItemDel,
    __menuItemOnKey,
    __menuItemParamFmt
};

/*********************************************************************************************************
** Function name:           menuItemCreate
** Descriptions:            �����˵���
** input parameters:        pmiiThis    �˵�����Ϣ
** output parameters:       none
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�sys_if.h
*********************************************************************************************************/
static INT32S __menuItemCreate (MENU_ITEM_INFO *pmiiThis)
{
    INT32S      siErr = 0;
    
    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */
    //if (GdsDevStatus.ucAuthorityLevel == DEVELOPER_LEVEL) {
        //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibPressureChargingEn); 
        //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibAlarmType);
        //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibLowLimit); 
        //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibUpperLimit);
        //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibPressureRange);
        //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibMidPCheckThreshold);
        //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibRamp);
        //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibTripleLineEn);
        
    //}
    siErr = miAdd(pmiiThis->pmiib, (void *)&__GmiibAsqWarnTime);  
    //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibFlipOutStartTime);
    //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibFlipOutActTime);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibLiftOutStartTime);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibLiftOutActTime);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibPusherOutStartTime);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibPusherOutActTime);
    //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibFlipInStartTime);
    //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibFlipInActTime);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibLiftInStartTime);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibLiftInActTime);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibPusherInStartTime);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibPusherInActTime);

    return siErr;
}

/*********************************************************************************************************
** Function name:           menuItemDel
** Descriptions:            ɾ���˵���
** input parameters:        pmiiThis    �˵�ҳ��Ϣ
** output parameters:       none
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�sys_if.h
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
**                          ����        ����,����ֵ�ο�sys_if.h
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
**                          ����        ����,����ֵ�ο�sys_if.h
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
  �Զ��Ƽܲ����˵�ҳ����
*********************************************************************************************************/
static const MENU_ITEM_INFO_BASE __GmiibAsqCfg = {            /*  �˵�ҳ��Ϣ                  */
    "�Զ��Ƽ�",
    (MENU_ITEM_FUNC *)&GmifAsqCfg,
    0x0300
};

/*********************************************************************************************************
** Function name:           miAsqCfgInit
** Descriptions:            �Զ��Ƽ����ò˵�ҳ��ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miAsqCfgInit (void)
{ 
    /*
     *  ��Ӳ˵�ҳ
     */
    miAdd(&__GmiibRoot, &__GmiibAsqCfg);
}
/*********************************************************************************************************
** Function name:           miAsqCfqDel
** Descriptions:            �Զ��Ƽ����ò˵�ҳж��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miAsqCfgDel (void)
{ 
    /*
     *  ɾ���˵�ҳ
     */
    miDel(&__GmiibAsqCfg);
}


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
