/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn                          
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               PwdDeveloper.c
** Latest modified Date:    2015-05-25
** Latest Version:          1.0
** Descriptions:            �����������޸Ĳ˵���
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2015-05-25
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

#include    "..\..\..\main.h"

/*********************************************************************************************************
  �ⲿ����
*********************************************************************************************************/


/*********************************************************************************************************
  ��������
*********************************************************************************************************/
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemDel(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiibThis, INT32U uiKeyCode);
static INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv);

/*********************************************************************************************************
  ȫ�ֱ�������
*********************************************************************************************************/


/*********************************************************************************************************
  �ڲ�ʹ�ñ���
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifPwdDeveloper = {
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
    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */
    //pmiiThis->pvPara = (void *)Gdp.ucPwdDeveloper;
    return SYS_OK;
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
    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */
    return SYS_OK;    
}

/*********************************************************************************************************
** Function name:           menuItemOnKey
** Descriptions:            �˵������Ӧ����
** input parameters:        pmiiThis    �˵�����Ϣ
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
    /*
     *  ��������
     */
    if (NULL == pmiiThis) {
        return (-SYS_PARA_ERR);
    }
    return pwdChgOnKey(pmiiThis, uiKeyCode);
}
/*********************************************************************************************************
** Function name:           menuItemParamFmt
** Descriptions:            �˵�����ʾ����
** input parameters:        pmiiThis    �˵�����Ϣ
**                          usFocus     ���������ݳ���
**                          pvRsv       ����������ָ��
** output parameters:       none
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�afxMenu.h
*********************************************************************************************************/
INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv)
{
    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */
    /*
     *  ��������
     */
    if (NULL == pmiiThis) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == pvRsv) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == pmiiThis->pvPara) {
        return (-SYS_NOT_OK);
    }        
    //uiSwVer = *((INT32U *)pmiiThis->pvPara);
    sprintf(pvRsv, ":******");
    return SYS_OK;
}

/*********************************************************************************************************
  �����������޸Ĳ˵����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibPwdDeveloper = {                       /*  �˵�����Ϣ                  */
    "������",
    (MENU_ITEM_FUNC *)&GmifPwdDeveloper,
    0x0201,
    (1 << 7) | (PARA_SCOPE_GLOBAL << 4) | PARA_TYPE_VALUE
};


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
