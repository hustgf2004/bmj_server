/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn  
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               SwDel.c
** Latest modified Date:    2022-09-23
** Latest Version:          1.0
** Descriptions:            ����ɾ���˵���
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

#include    "..\..\..\main.h"

/*********************************************************************************************************
  �ⲿ����
*********************************************************************************************************/
extern DEV_PARA Gdp;

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
const MENU_ITEM_FUNC GmifSwDel = {
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
    *  �����û�����        
    *  ............
    */
    //pmiiThis->pvPara = &Gdp.usGblFaceMax;
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
    *  �����û�����        
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
    char            scParamFmt[32] = {0};
    INT32U          uiX, uiY;
    INT32U          uiRtn;
    INT8U           ucErr;
    pmiiThis = pmiiThis;
   /*  
    *  �����û�����        
    *  ............
    */
    uiX = pmiiThis->ucX + strlen(pmiiThis->pmiib->pcTitle) * FONT_XSIZE8;
    uiY = pmiiThis->ucY;
    /*
     *  ��������
     */
    if (NULL == pmiiThis) {
        return (-SYS_PARA_ERR);
    }
    ucErr = inputInt(uiKeyCode, pmiiThis, &uiRtn);
    if (INPUT_UNCOMPLETED == ucErr) {
        return SYS_OK;
    }

    if (INPUT_COMPLETED == ucErr) {                                     /*  �����������                */
        OSSchedLock();
        sysIrqDisable(); 				        
        sysChangeToSysMode();
       
        sysWordProgramEx(0x80100000, 0x00000000);
        sysWordProgramEx(0x80100002, 0x00000000);	   
        sysWordProgramEx(0x80100004, 0x00000000);	   
        sysWordProgramEx(0x80100006, 0x00000000);	   

        //switchDLM_Handler();
        sysChangeToUsrMode();
        sysIrqEnable();
        OSSchedUnlock();
    } else if (INPUT_QUIT == ucErr) {                                   /*  �˳�����                    */                              
        ;
    } else if (INPUT_UNREASONABLE == ucErr) {                           /*  ����Ƿ�                    */
        ;
    } else {                                                            /*  ����δ�������              */
        ;
    }
    pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, scParamFmt);
    guiClrRectangle(uiX, uiY, GUI_LCM_XMAX, uiY + FONT_YSIZE16);
    guiPrintf(uiX, uiY, 1, "%s", scParamFmt);
    __GucEntered = FALSE;
    return SYS_OK;    
}
/*********************************************************************************************************
** Function name:           menuItemParamFmt
** Descriptions:            �˵�����ʾ����
** input parameters:        pmiiThis        �˵�����Ϣ
**                          usFocus         ���������ݳ���
**                          pvRsv           ����������ָ��
** output parameters:       none
** Returned value:          SYS_OK          �ɹ�
**                          ����            ����,����ֵ�ο�sys_if.h
*********************************************************************************************************/
INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv)
{
    INT8U   ucMBSAddr;
    pmiiThis = pmiiThis;
   /*  
    *  �����û�����        
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
    ucMBSAddr = *((INT8U *)pmiiThis->pvPara);
    sprintf(pvRsv, ":%6d ", ucMBSAddr);
    return SYS_OK;
}

/*********************************************************************************************************
  ����ɾ���˵����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibSwDel = {                              /*  �˵�����Ϣ                  */
    "����ɾ��",
    (MENU_ITEM_FUNC *)&GmifSwDel,
    0x0103,
    (1 << 7) | (PARA_SCOPE_GLOBAL << 4) | PARA_TYPE_VALUE
};


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/