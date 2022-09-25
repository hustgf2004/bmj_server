/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn  
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               AdvancedCfg.c
** Latest modified Date:    2022-09-23
** Latest Version:          1.0
** Descriptions:            �������ò˵�ҳ  
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ����������
** Created date:            2022-09-23
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
#include    ".\01PwdAdmin\PwdAdmin.h"
#include    ".\02PwdDeveloper\PwdDeveloper.h"
#include    ".\03SwDel\SwDel.h"
/*********************************************************************************************************
  �ⲿ����
*********************************************************************************************************/


/*********************************************************************************************************
  ��������
*********************************************************************************************************/
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemDel(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiibThis, INT32U uiKeyCode);
//static INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv);

/*********************************************************************************************************
  ȫ�ֱ�������
*********************************************************************************************************/


/*********************************************************************************************************
  �ڲ�ʹ�ñ���
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifAdvanced = {
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
     
    siErr = miAdd(pmiiThis->pmiib, (void *)&__GmiibPwdAdmin);
    siErr+= miAdd(pmiiThis->pmiib, &__GmiibSwDel);
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
  �߼����ò˵�ҳ����
*********************************************************************************************************/
static const MENU_ITEM_INFO_BASE __GmiibAdvanced = {                    /*  �˵�ҳ��Ϣ                  */
    "�߼�����",
    (MENU_ITEM_FUNC *)&GmifAdvanced,
    0x0100
};

/*********************************************************************************************************
** Function name:           miAdvancedCfgInit
** Descriptions:            �߼����ò˵�ҳ��ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miAdvancedCfgInit(void)
{
    /*
     *  ��Ӳ˵�ҳ
     */
    miAdd(&__GmiibRoot, &__GmiibAdvanced);
}
/*********************************************************************************************************
** Function name:           miAdvancedCfgDel
** Descriptions:            �߼����ò˵�ҳж��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miAdvancedCfgDel (void)
{ 
    /*
     *  ɾ���˵�ҳ
     */
    miDel(&__GmiibAdvanced);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
