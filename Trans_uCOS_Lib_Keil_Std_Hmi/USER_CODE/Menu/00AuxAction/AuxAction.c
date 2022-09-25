/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn  
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               AuxAction.c
** Latest modified Date:    2021-09-22
** Latest Version:          1.0
** Descriptions:            ���������˵�ҳ  
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ����������
** Created date:            2021-09-22
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
#include    ".\00NoneAct\NoneAct.h"
#include    ".\01Rewash\Rewash.h"
#include    ".\02RearConv\RearConv.h"
#include    ".\03TailGirder\TailGirder.h"
#include    ".\04FlashBoard\FlashBoard.h"
#include    ".\05BaseLift\BaseLift.h"
#include    ".\06Rsv1\Rsv1.h"
/*********************************************************************************************************
  �ⲿ����
*********************************************************************************************************/


/*********************************************************************************************************
  ��������
*********************************************************************************************************/
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiiThis);
static INT32S __menuItemDel(MENU_ITEM_INFO *pmiiThis);
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiiThis, INT32U uiKeyCode);
static INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv);

/*********************************************************************************************************
  ȫ�ֱ�������
*********************************************************************************************************/


/*********************************************************************************************************
  �ڲ�ʹ�ñ���
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifAuxAction = {
    __menuItemCreate,
    __menuItemDel,
    __menuItemOnKey,
    __menuItemParamFmt
};
/*********************************************************************************************************
** Function name:           menuItemCreate
** Descriptions:            �����˵�ҳ
** input parameters:        pmpiThis    �˵�ҳ��Ϣ
** output parameters:       none
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�sys_if.h
*********************************************************************************************************/
static INT32S __menuItemCreate (MENU_ITEM_INFO *pmiiThis)
{
    int i;
    INT32S siErr = 0;
    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */
    
    /*
     *  ���μ��ز˵���
     */
    siErr = miAdd(pmiiThis->pmiib, (void *)&__GmiibNoneAct);
    // siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibRewash);
    // siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibRearConv);
    // siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibTailGirder);
    // siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibFlashBoard);
    // siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibBaseLift);
    // siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibRsv1);
    return siErr;
}

/*********************************************************************************************************
** Function name:           menuItemDel
** Descriptions:            ɾ���˵���
** input parameters:        pmiiThis    �˵�����Ϣ
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
** Function name:           menuPageOnKey
** Descriptions:            �˵�ҳ������Ӧ����
** input parameters:        pmiiThis    �˵�����Ϣ
**                          usLen       ���������ݳ���
**                          pvData      ����������ָ��
** output parameters:       none
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�sys_if.h
*********************************************************************************************************/
static INT32S __menuItemOnKey (MENU_ITEM_INFO *pmiiThis, INT32U uiKeyCode)
{  
    /*
     *  ��������
     */
    if (NULL == pmiiThis) {
        return (-SYS_PARA_ERR);
    }

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
  ���������˵����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibAuxAction = {                          /*  �˵�����Ϣ                  */
    "��������",
    (MENU_ITEM_FUNC *)&GmifAuxAction,
    0x0000
};

/*********************************************************************************************************
** Function name:           miAuxActionInit
** Descriptions:            ���������˵�ҳ��ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miAuxActionInit(void)
{ 
    /*
     *  ��Ӳ˵�ҳ
     */
    miAdd(&__GmiibRoot, &__GmiibAuxAction);
}
/*********************************************************************************************************
** Function name:           miAuxActionDel
** Descriptions:            ���������˵�ҳж��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miAuxActionDel(void)
{ 
    /*
     *  ɾ���˵�ҳ
     */
    miDel(&__GmiibAuxAction);
}

/*********************************************************************************************************
** Function name:           miAuxToValve
** Descriptions:            ��������ת��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
INT32U miAuxToValve(TREE_NODE *ptnAuxMenu, INT8U ucIsAuxRight)
{
    INT32U uiValve = 0;
    MENU_ITEM_INFO *pmii;
    if (!ptnAuxMenu) {
        return uiValve;
    }
    pmii = (MENU_ITEM_INFO *)ptnAuxMenu->pvData;
    if (!pmii->pvPara) {
        return uiValve;
    }
    if (pmii->pvPara == NULL) {
        uiValve = 0;
    } else if (ucIsAuxRight) {
        uiValve = ((const INT32U *)pmii->pvPara)[1];
    } else {
        uiValve = ((const INT32U *)pmii->pvPara)[0];
    }
    return uiValve;
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

