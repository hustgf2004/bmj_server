/****************************************Copyright (c)****************************************************
**                            
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Date.c
** Latest modified Date:    2015-05-25
** Latest Version:          1.0
** Descriptions:            �������ò˵���
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
extern __DEV_INFO GdiDevInfo;
extern INT8U __SucIndex;
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
const MENU_ITEM_FUNC GmifDate = {
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
** Created Date:            2015-05-25
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT32S __menuItemCreate (MENU_ITEM_INFO *pmiiThis)
{
    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */
    pmiiThis->pvPara = &GdsDevStatus.pdTime;
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
** Created Date:            2015-05-25
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
** Created by:              
** Created Date:            2015-05-25
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT32S __menuItemOnKey (MENU_ITEM_INFO *pmiiThis, INT16U usLen, void *pvData)
{    
    INT32U         *puiKeyCode;
    static char   __SscParamFmt[16] = {0};
    //static INT8U  __SucIndex = 0; 
    INT32U          uiX, uiY;
    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */
    uiX = pmiiThis->ucX + strlen(pmiiThis->pmiib->pcTitle) * FONT_XSIZE8;
    uiY = pmiiThis->ucY;
    
    
    /*
     *  ��������
     */
    if ((NULL == pmiiThis) || (NULL == pvData) || (0 == usLen)) {
        return (-SYS_PARA_ERR);
    }
    
    puiKeyCode = pvData;
    if (!puiKeyCode[0]) {
        return SYS_OK;
    }
    if ((!__GucEntered) && (puiKeyCode[0] == KEY_ENTER)) {
        pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, __SscParamFmt);
        __SscParamFmt[0] = '?';
        guiPrintf(uiX, uiY, 1, "%s", __SscParamFmt);
        return SYS_OK;
    }
    if ((KEY_ESC == puiKeyCode[0]) ||
        ((KEY_ENTER == puiKeyCode[0]) && (0 == __SucIndex))) {          /*  �˳�                        */
        pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, __SscParamFmt);
        guiPrintf(uiX, uiY, 1, "%s", __SscParamFmt); 
        __SucIndex = 0;
        return SYS_OK;
    }
    if (KEY_ENTER == puiKeyCode[0]) {
        INT32U          uiTemp[3];
        INT32U          uiRtn;
        uiRtn = sscanf(__SscParamFmt, "?%d/%d/%d", &uiTemp[0], &uiTemp[1], &uiTemp[2]);
        if ((uiTemp[2] < 2017) ||
            (uiTemp[0] > 12) ||
            (uiTemp[0] < 1) ||
            (uiTemp[1] > 31) ||
            (uiTemp[1] < 1) ||
            (uiRtn < 3)) {            

        } else {
            GdsDevStatus.pdTime.year     = uiTemp[2];
            GdsDevStatus.pdTime.month    = uiTemp[0];//__SrtcTime.month;
            GdsDevStatus.pdTime.day      = uiTemp[1];
            pcf8563Set(&GdsDevStatus.pdTime);
        }
        pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, __SscParamFmt);
        guiPrintf(uiX, uiY, 1, "%s", __SscParamFmt); 
        __SucIndex = 0;        
        return SYS_OK;       
    }
    if (__SucIndex > 10) {                                              /*  ���볬��                    */
        return SYS_OK;
    }
    switch (__SucIndex) {
        case 0:
            __SscParamFmt[__SucIndex] = '?';
            __SucIndex++;
            __SscParamFmt[__SucIndex] = kbd2Ascii(puiKeyCode[0]);
            __SscParamFmt[__SucIndex + 1] = ' ';
            __SucIndex++;
            
        break;
        case 2:
        case 5:
            __SscParamFmt[__SucIndex] = kbd2Ascii(puiKeyCode[0]);
            __SucIndex++;
            __SscParamFmt[__SucIndex] = '/';
            __SucIndex++;
        break;
        
        case 7:
            __SscParamFmt[__SucIndex+1] = ' ';
            __SscParamFmt[__SucIndex+2] = ' ';
            __SscParamFmt[__SucIndex+3] = ' ';
            __SscParamFmt[__SucIndex] = kbd2Ascii(puiKeyCode[0]);            
            __SucIndex++;
            break;
        //case 1:
        case 4:
            __SscParamFmt[__SucIndex+1] = ' ';
            //__SscParamFmt[__SucIndex] = kbd2Ascii(puiKeyCode[0]);            
            //__SucIndex++;
            //break;
        default:
            __SscParamFmt[__SucIndex] = kbd2Ascii(puiKeyCode[0]);
            __SucIndex++;
        break;
    }
    guiPrintf(uiX, uiY, 1, "%s", __SscParamFmt);
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
** Created Date:            2015-05-25
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv)
{
    PCF8563_DATE   *prtcTime;
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
    prtcTime = (PCF8563_DATE *)pmiiThis->pvPara;
    sprintf(pvRsv, ":%02d/%02d/%4d ", prtcTime->month, prtcTime->day, prtcTime->year);
    return SYS_OK;
}

/*********************************************************************************************************
  ���ڲ˵����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibDate = {                               /*  �˵�����Ϣ                  */
    "����",
    (MENU_ITEM_FUNC *)&GmifDate,
    0x0601
};


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
