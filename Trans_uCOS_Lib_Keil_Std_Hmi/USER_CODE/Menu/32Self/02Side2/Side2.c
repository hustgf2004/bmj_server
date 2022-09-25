/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn  
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Side2.c
** Latest modified Date:    2022-01-04
** Latest Version:          1.0
** Descriptions:            ��������-���
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ����������
** Created date:            2022-01-04
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


/*********************************************************************************************************
** Function name:           menuItemCreate
** Descriptions:            �����˵���
** input parameters:        pmiiThis    �˵�����Ϣ
** output parameters:       none
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�sys_if.h
*********************************************************************************************************/
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiiThis)
{
    pmiiThis->pvPara = (void *)&GpuiValveTbl[SIDE_2_OUT];
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
    INT32S      siErr;
    
    /*
     *  ��������
     */
    if (NULL == pmiiThis) {
        return (-SYS_PARA_ERR);
    } 
#if 0    
    if (GpuiKeyTbl[KEY_AUX_LEFT] == uiKeyCode) {                    /*  �������                    */
        Gds.uiValveStatus |= GpuiValveTbl[SIDE_2_OUT];
    } else if (GpuiKeyTbl[KEY_AUX_RIGHT] == uiKeyCode) {            /*  �����Ҽ�                        */
        Gds.uiValveStatus |= GpuiValveTbl[SIDE_2_IN];
    } else {                                                            /*  ����                        */
        Gds.uiValveStatus &= ~(GpuiValveTbl[SIDE_2_OUT] | GpuiValveTbl[SIDE_2_IN]);
    }
#endif
    keyOnMaster(uiKeyCode);
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
    INT32U      uiRecordAddr;
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

const MENU_ITEM_FUNC GmifSide2 = {
    __menuItemCreate,
    __menuItemDel,
    __menuItemOnKey,
    __menuItemParamFmt
};


/*********************************************************************************************************
  ������������˵����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibSide2 = {                             /*  �˵�����Ϣ                  */
    "�����  �����",
    (MENU_ITEM_FUNC *)&GmifSide2,
    0x3202,    
};

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
