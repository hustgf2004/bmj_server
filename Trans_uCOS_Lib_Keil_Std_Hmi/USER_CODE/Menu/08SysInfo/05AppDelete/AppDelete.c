/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               AppDelete.c
** Latest modified Date:    2021-09-26
** Latest Version:          1.0
** Descriptions:            Ӧ�ó���ɾ���˵���
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
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiiThis);
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiibThis, INT32U uiKeyCode);


/*********************************************************************************************************
  ȫ�ֱ�������
*********************************************************************************************************/


/*********************************************************************************************************
  �ڲ�ʹ�ñ���
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifAppDelete = {
    __menuItemCreate,
    NULL,
    __menuItemOnKey,
    NULL
};


/*********************************************************************************************************
** Function name:           menuItemCreate
** Descriptions:            �����˵���
** input parameters:        pmiiThis    �˵�����Ϣ
** output parameters:       none
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�afxMenu.h
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
    INT32U         *puiKeyCode;

    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */

    if ((GpuiKeyTbl[KEY_ENTER] == uiKeyCode)) {                                 /*  ȷ�Ϸ�����                  */
        if (!__GucEntered) {
            guiPrintf(pmiiThis->ucX, pmiiThis->ucY, 1, "ȷ��ɾ��?");
            pmiiThis->pvPara = NULL;
            __GucEntered = TRUE;
        } else {                                                                    /*  ȷ��                        */
            guiClrScr();
            sysIrqDisable();

            OSSchedLock(); 
            //Initext(0x80000000, 12000000, 2);       // Initialize Flash Programming Functions //   Device Base Address = 0//   Clock Frequency = 12MHz
            WordProgramEx(0x80100000, 0x00000000);
            WordProgramEx(0x80100002, 0x00000000);
            WordProgramEx(0x80100004, 0x00000000);
            WordProgramEx(0x80100006, 0x00000000);                    
            vicIrqDisable(4);
            vicIrqDisable(5);
            timerStop(0);              // ֹͣ��ʱ/������1
            timerStop(1);              // ֹͣ��ʱ/������1                                    

            sysChangeToSysMode();
            switchBoot_Handler();
        }
    } else if ((__GucEntered) &&  (GpuiKeyTbl[KEY_ABORT] == uiKeyCode)) {         /*  �˳�                        */
        guiPrintf(pmiiThis->ucX, pmiiThis->ucY, 1, "%s", pmiiThis->pmiib->pcTitle);
        pmiiThis->pvPara = (void *)0x10008000;   
    } 

    return SYS_OK;  
}


/*********************************************************************************************************
  Ӧ�ó���ɾ���˵����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibAppDelete = {                          /*  �˵�����Ϣ                  */
    "Ӧ�ó���ɾ��",
    (MENU_ITEM_FUNC *)&GmifAppDelete,
    0x0805,
    (1 << 7) | (PARA_SCOPE_OPTIONAL << 4) | PARA_TYPE_OPERATE
};


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
