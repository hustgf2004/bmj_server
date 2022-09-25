/****************************************Copyright (c)****************************************************
**                            
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               HighPressureEn.c
** Latest modified Date:    2017-04-03
** Latest Version:          1.0
** Descriptions:            ��ѹ������ʹ�ܲ˵���
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2017-04-03
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
extern const  char *const __SscEnStr[];
extern INT8U    __SucEnFlag;
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
const MENU_ITEM_FUNC GmifHighPressureEn = {
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
** Created Date:            2017-04-03
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
    pmiiThis->pvPara = (void *)&GdiDevInfo.uiEnFlag;
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
** Created Date:            2017-04-03
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
** Created Date:            2017-04-03
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT32S __menuItemOnKey (MENU_ITEM_INFO *pmiiThis, INT16U usLen, void *pvData)
{    
    //static INT8U    __SucEnFlag = 0;
    unsigned int    uiLen;    
    INT32U         *puiKeyCode;
    
    char            scParamFmt[32] = {0};
    INT32U          uiX, uiY;
    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */
    uiX = pmiiThis->ucX + strlen(pmiiThis->pmiib->pcTitle) * FONT_XSIZE8;
    uiY = pmiiThis->ucY;
    
    puiKeyCode = pvData;

    switch(puiKeyCode[0]) {
        case KEY_UP:
        case KEY_0:
            __SucEnFlag = 0;
            uiLen = strlen(pmiiThis->pmiib->pcTitle);
            guiPrintf(pmiiThis->ucX + uiLen * 8, pmiiThis->ucY, 1, "?%s", __SscEnStr[__SucEnFlag]);
        break;
        case KEY_DOWN:
        case KEY_1:
            __SucEnFlag = 1;
            uiLen = strlen(pmiiThis->pmiib->pcTitle);
            guiPrintf(pmiiThis->ucX + uiLen * 8, pmiiThis->ucY, 1, "?%s", __SscEnStr[__SucEnFlag]);    
        break;
        
        case KEY_ENTER:
            if (!__GucEntered) {
                __SucEnFlag = (((INT32U *)pmiiThis->pvPara)[0] >> EN_HIGH_P_SNR) & 0x01; 
                guiPrintf(uiX, uiY, 1, "?");
                break;
            }
            if (__SucEnFlag) {
                ((INT32U *)pmiiThis->pvPara)[0] |= (1 << EN_HIGH_P_SNR);
            } else {
                ((INT32U *)pmiiThis->pvPara)[0] &= ~(1 << EN_HIGH_P_SNR);
            }
            //GdiDevInfo.ucPressureEn[2] = __SucEnFlag;
            if (dsSaveParam(&GdiDevInfo) < 0) {                         /*  ��������ʧ��                */
                //��ʾ�����������
                dsRecoverParam(&GdiDevInfo);
            } else {
 
            }
            pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, scParamFmt);
            guiPrintf(uiX, uiY, 1, "%s", scParamFmt);
        break;
        case KEY_ESC:
            pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, scParamFmt);
            guiPrintf(uiX, uiY, 1, "%s", scParamFmt);
        break;
        default:
        break;
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
** Created Date:            2017-04-03
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv)
{
    INT32U ucPressureEn;
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
    ucPressureEn = ((INT32U *)pmiiThis->pvPara)[0];
    sprintf(pvRsv, ":%s", __SscEnStr[(ucPressureEn >> EN_HIGH_P_SNR) & 0x01]);
    return SYS_OK;
}

/*********************************************************************************************************
  ��ѹ������ʹ�ܲ˵����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibHighPressureEn = {                     /*  �˵�����Ϣ                  */
    "��ѹƿѹ��",
    (MENU_ITEM_FUNC *)&GmifHighPressureEn,
    0x0805
};


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
