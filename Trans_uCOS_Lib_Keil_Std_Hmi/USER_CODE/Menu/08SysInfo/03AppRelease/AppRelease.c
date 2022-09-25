/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               AppRelease.c
** Latest modified Date:    2021-09-26
** Latest Version:          1.0
** Descriptions:            Ӧ�ó��򷢲��˵���
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

#include    "..\..\..\main.h"

/*********************************************************************************************************
  �ⲿ����
*********************************************************************************************************/


/*********************************************************************************************************
  ��������
*********************************************************************************************************/
//static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemDel(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiiThis, INT32U uiKeyCode);
//static INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv);

/*********************************************************************************************************
  ȫ�ֱ�������
*********************************************************************************************************/


/*********************************************************************************************************
  �ڲ�ʹ�ñ���
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifAppRelease = {
    NULL,
    __menuItemDel,
    __menuItemOnKey,
    NULL
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
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           menuItemDel
** Descriptions:            ɾ���˵���
** input parameters:        pmpiThis    �˵�����Ϣ
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
    INT32U     *puiKeyCode;
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
    if ((GpuiKeyTbl[KEY_ENTER] == uiKeyCode)) {                                 /*  ȷ�Ϸ�����                  */
        if (!__GucEntered) {
            guiPrintf(pmiiThis->ucX, pmiiThis->ucY, 1, "ȷ�Ϸ���?");
            pmiiThis->pvPara = NULL;
            __GucEntered = TRUE;
        } else {                                                                    /*  ȷ��                        */
            GUI_ClearSCR();
            sysIrqDisable();
            //д��ʶ
            sysChangeToSysMode();
            switchBoot_Handler();
        }
    } else if ((__GucEntered) &&  (GpuiKeyTbl[KEY_ABORT] == uiKeyCode)) {         /*  �˳�                        */
        guiPrintf(pmiiThis->ucX, pmiiThis->ucY, 1, "%s", pmiiThis->pmiib->pcTitle);
        pmiiThis->pvPara = (void *)0x10008000;   
    } 
}


/*********************************************************************************************************
  Ӧ�ó��򷢲��˵����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibAppRelease = {                         /*  �˵�����Ϣ                  */
    "Ӧ�ó��򷢲�",
    (MENU_ITEM_FUNC *)&GmifAppRelease,
    0x0803,
    (1 << 7) | (PARA_SCOPE_LOCAL << 4) | PARA_TYPE_OPERATE
};


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
