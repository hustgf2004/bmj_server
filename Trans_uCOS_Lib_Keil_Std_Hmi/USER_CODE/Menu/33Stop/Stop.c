/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Stop.c
** Latest modified Date:    2021-10-07
** Latest Version:          1.0
** Descriptions:            ��ͣ�˵�ҳ  
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ����������
** Created date:            2021-10-07
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

/*********************************************************************************************************
  �ⲿ����
*********************************************************************************************************/
extern TREE_NODE      *__GptnCurMenu;                                   /*  ��ǰ�˵��ڵ�                */
extern TREE_NODE      *__GptnRootMenu;                                  /*  �˵����ڵ�                  */

/*********************************************************************************************************
  ��������
*********************************************************************************************************/
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemDel(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiibThis, INT32U uiKeyCode);
//static INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv);

/*********************************************************************************************************
  ȫ�ֱ�������
*********************************************************************************************************/


/*********************************************************************************************************
  �ڲ�ʹ�ñ���
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifStop = {
    __menuItemCreate,
    __menuItemDel,
    __menuItemOnKey,
    NULL
};
                                 
/*********************************************************************************************************
** Function name:           menuItemCreate
** Descriptions:            �����˵���
** input parameters:        pmiiThis    �˵�ҳ��Ϣ
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
//    guiClrScr();
//    guiPrintf(0, 16, 0, "%s", __GmiibStop.pcTitle); 
    if ((Gds.ucIsStop) || (Gds.ucIsLock)) {
        Gds.ucStatus = STA_H_LOCK;                                 /*  �ܡ�����״̬��־��Ӳ������  */
    } else {
        Gds.ucStatus = STA_S_LOCK;
    }
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           menuItemDel
** Descriptions:            ɾ���˵�ҳ
** input parameters:        pmiiThis    �˵�ҳ��Ϣ
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
    if ((Gds.ucIsLock) || (Gds.ucIsStop)) {
        mpHome();
    } else {
        sysIrqDisable();
        OSSchedLock();
        Gds.ucStatus = STA_IDLE;
        OSSchedUnlock();
        sysIrqEnable();
    }
    return SYS_OK;    
}

/*********************************************************************************************************
** Function name:           menuItemOnKey
** Descriptions:            �˵������Ӧ����
** input parameters:        pmiiThis    �˵�ҳ��Ϣ
**                          usLen       ���������ݳ���
**                          pvData      ����������ָ��
** output parameters:       none
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�sys_if.h
*********************************************************************************************************/
static INT32S __menuItemOnKey (MENU_ITEM_INFO *pmiiThis, INT32U uiKeyCode)
{
    INT8U   ucErr;
    INT32U  uiValveDat;
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


    return SYS_OK;
}


/*********************************************************************************************************
  �Կز˵�ҳ����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibStop = {                               /*  �˵�����Ϣ                  */
    "    ���ܼ�ͣ    ",
    (MENU_ITEM_FUNC *)&GmifStop,
    0x3300
};

/*********************************************************************************************************
** Function name:           miStopInit
** Descriptions:            ��ͣ�˵����ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miStopInit(void)
{ 
    /*
     *  ��Ӳ˵�ҳ
     */
    miAdd(&__GmiibRoot, &__GmiibStop);                                  /*  �ײ˵��ڵ�                  */
}
/*********************************************************************************************************
** Function name:           miStopDel
** Descriptions:            ��ͣ�˵���ж��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miStopDel(void)
{ 
    /*
     *  ɾ���˵�ҳ
     */
    miDel(&__GmiibStop);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
