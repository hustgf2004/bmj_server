/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Master.c
** Latest modified Date:    2021-12-27
** Latest Version:          1.0
** Descriptions:            ���ز˵���
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ����������
** Created date:            2021-12-27
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
#include    ".\01Neighbor\Neighbor.h"
#include    ".\02Batch\Batch.h"
/*********************************************************************************************************
  �ⲿ����
*********************************************************************************************************/

/*********************************************************************************************************
  ��������
*********************************************************************************************************/
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiiThis);
static INT32S __menuItemDel(MENU_ITEM_INFO *pmiiThis);
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiiThis, INT32U uiKeyCode);
static INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv);
/*********************************************************************************************************
  ȫ�ֱ�������
*********************************************************************************************************/


/*********************************************************************************************************
  �ڲ�ʹ�ñ���
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifMaster = {
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
    ;
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
    INT8U           ucBuf[8];
    INT32U          uiValveDat;
    const INT32U   *puiValveTbl;
    pmiiThis = pmiiThis;
    /*
     *  ��������
     */
    puiValveTbl = valveTblGet(Gds.ucSlaveNo);
    uiValveDat = keyToAction(uiKeyCode, GpuiKeyTbl, puiValveTbl);
    if ((uiKeyCode & GpuiKeyTbl[KEY_AUX_LEFT]) ||
        (uiKeyCode & GpuiKeyTbl[KEY_AUX_RIGHT])) {
        uiValveDat |= miAuxToValve(__GptnCurMenu, uiKeyCode == GpuiKeyTbl[KEY_AUX_RIGHT]);
    }
    if (uiKeyCode & GpuiKeyTbl[KEY_ABORT]) {
        ucBuf[0] = Gdp.ucShieldNo;
        ucBuf[1] = Gdp.ucShieldNo;
        ledNavi(0xffffffff);
        tpWrite(TP_DEFAULT_CHNL, __TP_ABORT, 2, ucBuf, 0);
    } else if (uiKeyCode & GpuiKeyTbl[KEY_START]) {
        
        //miFlush();
        //mainDisplay();
    } else if (uiValveDat) {                                            /*  ��������                    */
        tp_htonl(uiValveDat);                                           /*  ��С��ת��                  */
        tpWrite(TP_DEFAULT_CHNL, __TP_JOCKEY, 4, &uiValveDat, 0);
    } else {
        //GUI_Rectangle(0, 16, 127, 63, 0);
        //guiPrintf(0, 0, 0, "Ԥ������");
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
**                          ����        ����,����ֵ�ο�sys_if.h
*********************************************************************************************************/
INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv)
{
    //INT32U   uiHwVer;
    /*
     *  ��������
     */
    if (NULL == pmiiThis) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == pvRsv) {
        return (-SYS_PARA_ERR);
    }
    return SYS_OK;
}

/*********************************************************************************************************
  ���ز˵����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibMaster = {                             /*  �˵�����Ϣ                  */
    "",
    (MENU_ITEM_FUNC *)&GmifMaster,
    0x1E00
};

/*********************************************************************************************************
** Function name:           miMasterInit
** Descriptions:            ���ز˵����ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miMasterInit(void)
{ 
    /*
     *  ��Ӳ˵�ҳ
     */
    miAdd(&__GmiibRoot, &__GmiibMaster);                                        /*  �ײ˵��ڵ�                  */
}
/*********************************************************************************************************
** Function name:           miMasterDel
** Descriptions:            ���ز˵���ж��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miMasterDel(void)
{ 
    /*
     *  ɾ���˵�ҳ
     */
    miDel(&__GmiibMaster);
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
