/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn                              
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               PusherInStartTime.c
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
const MENU_ITEM_FUNC GmifPusherInStartTime = {
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
    pmiiThis->pvPara = (void *)&Gdp.ucPusherInStartT;
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
    static INT8U    __SucAlarmType;
    unsigned int    uiLen;    
    INT32U         *puiKeyCode;
    INT8U           ucErr;
    char            scParamFmt[32] = {0};
    INT32U          uiX, uiY;
    INT32U          uiRtn;
    pmiiThis = pmiiThis;
    uiX = pmiiThis->ucX + strlen(pmiiThis->pmiib->pcTitle) * FONT_XSIZE8;
    uiY = pmiiThis->ucY;
   /*  
    *  ����û�����        
    *  ............
    */
    
    ucErr = inputInt(uiKeyCode, pmiiThis, &uiRtn);
    
    if (INPUT_UNCOMPLETED == ucErr) {
        return SYS_OK;
    }
    if (INPUT_COMPLETED == ucErr) {                                     /*  �����������                */
        if (uiRtn <= 60) {
            Gdp.ucPusherInStartT = uiRtn;
            eepromWrite(0, (INT8U *)&Gdp, sizeof(DEV_PARA));
//        if (dsSaveParam(&GdiDevInfo) < 0) {                             /*  ��������ʧ��                */
//            dsRecoverParam(&GdiDevInfo);
//        } else {
//            ;
//        };  
        }            
    } else if (INPUT_QUIT == ucErr) {                                   /*  �˳�����                    */                              
        ;
    } else if (INPUT_UNREASONABLE == ucErr) {                           /*  ����Ƿ�                    */
        ;
    } else {                                                            /*  ����δ�������              */
        ;
    }
    pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, scParamFmt);
    GUI_RectangleFill(uiX, uiY, GUI_LCM_XMAX, uiY + FONT_YSIZE16, 0);
    guiPrintf(uiX, uiY, 1, "%s", scParamFmt);
    __GucEntered = FALSE;
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
**                          ����        ����,����ֵ�ο�sys_if.h
*********************************************************************************************************/
INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv)
{
    INT16U      usWarnTime;
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
    usWarnTime = *((INT8U *)pmiiThis->pvPara);
    sprintf(pvRsv, ":%4dS", usWarnTime);
    return SYS_OK;
}
/*********************************************************************************************************
  �����տ�ʼʱ��˵����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibPusherInStartTime = {                  /*  �˵�����Ϣ                  */
    "�����տ�ʼ",
    (MENU_ITEM_FUNC *)&GmifPusherInStartTime,
    0x0308,
    (1 << 7) | (PARA_SCOPE_GLOBLE << 4) | PARA_TYPE_VALUE
};
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
