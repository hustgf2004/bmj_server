/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn  
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               BaseLift.c
** Latest modified Date:    2021-09-22
** Latest Version:          1.0
** Descriptions:            ��������-̧��
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ����������
** Created date:            2021-09-22
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
static const  char *const __SscBaseLiftStr[] = {    
    "̧����    ����1"};

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
    const INT32U   *puiValveTbl;
    puiValveTbl = valveTblGet(Gds.ucSlaveNo);
    pmiiThis->pvPara = (void *)&puiValveTbl[BASE_LIFT_SET];
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
    INT32U     *puiKeyCode;
    INT32S      siErr;
    
    /*
     *  ��������
     */
    if (NULL == pmiiThis) {
        return (-SYS_PARA_ERR);
    }
    
    if (GpuiKeyTbl[KEY_AUX_LEFT] == uiKeyCode) {                    /*  �������                    */
        
    } else if (GpuiKeyTbl[KEY_AUX_RIGHT] == uiKeyCode) {            /*  �����Ҽ�                        */
        
    } else {                                                            /*  ����                        */
        ;
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

    sprintf(pvRsv, "%s", __SscBaseLiftStr[0]);

    return SYS_OK;
}

const MENU_ITEM_FUNC GmifBaseLift = {
    __menuItemCreate,
    __menuItemDel,
    __menuItemOnKey,
    __menuItemParamFmt
};


/*********************************************************************************************************
  ��������̧�ײ˵����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibBaseLift = {                           /*  �˵�����Ϣ                  */
    "",
    (MENU_ITEM_FUNC *)&GmifBaseLift,
    0x0005,    
};

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/