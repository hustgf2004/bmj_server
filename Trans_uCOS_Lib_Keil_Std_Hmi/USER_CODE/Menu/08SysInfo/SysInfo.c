/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               SysInfo.c
** Latest modified Date:    2021-09-26
** Latest Version:          1.0
** Descriptions:            ϵͳ��Ϣ�˵�ҳ  
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ����������
** Created date:            2021-09-26
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
#include    ".\01HwVer\HwVer.h"
#include    ".\02SwVer\SwVer.h"
#include    ".\03AppRelease\AppRelease.h"
#include    ".\04ParaRelease\ParaRelease.h"
#include    ".\05AppDelete\AppDelete.h"
#include    ".\06PwrGrpId\PwrGrpId.h"
#include    ".\07ObliquitySnrId\ObliquitySnrId.h"
#include    ".\08ObliquityFwDelete\ObliquityFwDelete.h"
#include    ".\09Reset\Reset.h"

/*********************************************************************************************************
  �ⲿ����
*********************************************************************************************************/


/*********************************************************************************************************
  ��������
*********************************************************************************************************/
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemDel(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiiThis, INT32U uiKeyCode);
//static INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv);

/*********************************************************************************************************
  ȫ�ֱ�������
*********************************************************************************************************/


/*********************************************************************************************************
  �ڲ�ʹ�ñ���
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifSysInfo = {
    __menuItemCreate,
    __menuItemDel,
    __menuItemOnKey,
    NULL
};
/*********************************************************************************************************
** Function name:           menuItemCreate
** Descriptions:            �����˵�ҳ
** input parameters:        pmiiThis    �˵�ҳ��Ϣ
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
    /*
     *  ���μ��ز˵���
     */
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibHwVer);
	siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibSwVer); 
//    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibAppRelease);
//    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibParaRelease);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibAppDelete);
//    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibPwrGrpId);
//    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibObliquitySnrId);
//    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibObliquityFwDelete);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibReset);
    return siErr;
}

/*********************************************************************************************************
** Function name:           menuItemDel
** Descriptions:            ɾ���˵�ҳ
** input parameters:        pmiiThis    �˵�ҳ��Ϣ
** output parameters:       none
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�sys_if.h
*********************************************************************************************************/
static INT32S __menuItemDel (MENU_ITEM_INFO *pmiiThis)
{
    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */

    return SYS_OK;    
}

/*********************************************************************************************************
** Function name:           menuItemOnKey
** Descriptions:            �˵�ҳ������Ӧ����
** input parameters:        pmiiThis    �˵�ҳ��Ϣ
**                          usLen       ���������ݳ���
**                          pvData      ����������ָ��
** output parameters:       none
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�sys_if.h
*********************************************************************************************************/
static INT32S __menuItemOnKey (MENU_ITEM_INFO *pmiiThis, INT32U uiKeyCode)
{
    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */
    
    return SYS_OK;
}


/*********************************************************************************************************
  ϵͳ��Ϣ�˵�ҳ����
*********************************************************************************************************/
static const MENU_ITEM_INFO_BASE __GmiibSysInfo = {                     /*  �˵�ҳ��Ϣ                  */
    "ϵͳ��Ϣ",
    (MENU_ITEM_FUNC *)&GmifSysInfo,
    0x0800
};

/*********************************************************************************************************
** Function name:           miSysInfoInit
** Descriptions:            ϵͳ��Ϣ�˵�ҳ��ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miSysInfoInit(void)
{ 
    /*
     *  ��Ӳ˵�ҳ
     */
    miAdd(&__GmiibRoot, &__GmiibSysInfo);
}
/*********************************************************************************************************
** Function name:           miSysInfoDel
** Descriptions:            ϵͳ��Ϣ�˵�ҳж��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miSysInfoDel (void)
{ 
    /*
     *  ɾ���˵�ҳ
     */
    miDel(&__GmiibSysInfo);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
