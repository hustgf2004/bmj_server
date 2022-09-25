/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Signature.c
** Latest modified Date:    2017-04-21
** Latest Version:          1.0
** Descriptions:            ������λ�˵���
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2017-04-21
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
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiiThis, INT32U uiKeyCode);
static INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv);

/*********************************************************************************************************
  ȫ�ֱ�������
*********************************************************************************************************/


/*********************************************************************************************************
  �ڲ�ʹ�ñ���
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifReset = {
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
**                          ����        ����,����ֵ�ο�afxMenu.h
** Created by:              
** Created Date:            2017-04-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiiThis)
{
    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */
    pmiiThis->pvPara = (void *)0x10008000;

    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           menuItemDel
** Descriptions:            ɾ���˵���
** input parameters:        pmiiThis    �˵�����Ϣ
** output parameters:       none
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�afxMenu.h
** Created by:              
** Created Date:            2017-04-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
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
**                          ����        ����,����ֵ�ο�afxMenu.h
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

    if ((GpuiKeyTbl[KEY_ENTER] == uiKeyCode)) {                                 /*  ȷ�ϸ�λ��                  */
        if (!__GucEntered) {
            guiPrintf(pmiiThis->ucX, pmiiThis->ucY, 1, "ȷ�ϸ�λ?");
            pmiiThis->pvPara = NULL;
            __GucEntered = TRUE;
        } else {                                                        /*  ȷ��                        */
            guiClrScr();
            sysIrqDisable();
            sysChangeToSysMode();
            switchBoot_Handler();
        }
    } else if ((__GucEntered) &&  (GpuiKeyTbl[KEY_ABORT] == uiKeyCode)) {         /*  �˳�                        */
        guiClrRectangle(pmiiThis->ucX, pmiiThis->ucY, 128, 16);
        guiPrintf(pmiiThis->ucX, pmiiThis->ucY, 1, "%s", pmiiThis->pmiib->pcTitle);
        __GucEntered = 0;
        //pmiiThis->pvPara = (void *)0x10008000;   
    }
    return SYS_OK;
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
** Created by:              
** Created Date:            2017-04-21
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
    sprintf(pvRsv, "");
    return SYS_OK;
}

/*********************************************************************************************************
  ������λ�˵����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibReset = {                              /*  �˵�����Ϣ                  */
    "������λ",
    (MENU_ITEM_FUNC *)&GmifReset,
    0x0809,
    (1 << 7) | (PARA_SCOPE_LOCAL << 4) | PARA_TYPE_OPERATE
};


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
