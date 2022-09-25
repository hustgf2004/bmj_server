/****************************************Copyright (c)****************************************************
**                            
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               MidPDeltaThreshold.c
** Latest modified Date:    2017-04-20
** Latest Version:          1.0
** Descriptions:            ��ѹ->��ѹ�л�ѹ����ֵ�˵���
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2017-04-20
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
const MENU_ITEM_FUNC GmifMidPDeltaThreshold = {
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
** Created Date:            2017-04-20
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
    pmiiThis->pvPara = (FP32 *)&GdiDevInfo.fpDeltaPThreshold[1];
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
** Created Date:            2017-04-06
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
** Created Date:            2017-04-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT32S __menuItemOnKey (MENU_ITEM_INFO *pmiiThis, INT16U usLen, void *pvData)
{
    INT32U         *puiKeyCode;    
    FP32            fpRtn;
    char            scParamFmt[32] = {0};
    INT32U          uiX, uiY;
    INT8U           ucErr;
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
    if (NULL == pmiiThis) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == pvData) {
        return (-SYS_PARA_ERR);
    }
    puiKeyCode = pvData;
    ucErr = inputFloat(puiKeyCode[0], pmiiThis, &fpRtn);
    if (INPUT_UNCOMPLETED == ucErr) {
        return SYS_OK;
    }
    if ((INPUT_COMPLETED == ucErr) &&                                   /*  �����������                */
        ((fpRtn > 0.0f) &&
        (fpRtn <= 99.9f))) {                                            /*  ������ֵ                    */
        GdiDevInfo.fpDeltaPThreshold[1] = fpRtn;
        if (dsSaveParam(&GdiDevInfo) < 0) {                             /*  ��������ʧ��                */
            dsRecoverParam(&GdiDevInfo);
        } else {
            ;
        };    
    } else if (INPUT_QUIT == ucErr) {                                   /*  �˳�����                    */                              
        ;
    } else if (INPUT_UNREASONABLE == ucErr) {                           /*  ����Ƿ�                    */
        ;
    } else {                                                            /*  ����δ�������              */
        ;
    }
    pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, scParamFmt);
    guiRectangleFill(uiX, uiY, GUI_LCM_XMAX, uiY + FONT_YSIZE16, 0);
    guiPrintf(uiX, uiY, 1, "%s", scParamFmt);
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
** Created Date:            2017-04-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv)
{
    FP32 fpPressureRange;
    INT32S siErr = 0;     
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
    fpPressureRange = *((FP32 *)pmiiThis->pvPara);
    fpPressureRange += 0.05;                                            /*  С����������                */
    siErr = (INT32S)fpPressureRange;
    //sprintf(pvRsv, ":%-1.2fMPa", fpPressureRange);
    sprintf(pvRsv, ":%2d.%01dMPa", siErr, (INT32U)((fpPressureRange * 10.0) - siErr * 10.0));  
    return SYS_OK;
}

/*********************************************************************************************************
  ��ѹ->��ѹ�л�ѹ����ֵ�˵����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibMidPDeltaThreshold = {                 /*  �˵�����Ϣ                  */
    "��ѹ��ֵ",
    (MENU_ITEM_FUNC *)&GmifMidPDeltaThreshold,
    0x140E
};

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
