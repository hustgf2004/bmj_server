/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Slave.c
** Latest modified Date:    2021-12-28
** Latest Version:          1.0
** Descriptions:            �ӿز˵�����  
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ����������
** Created date:            2021-12-28
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
static const MENU_ITEM_FUNC GmifSlv = {
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
    Gds.ucIndicatorFlg.Bits.ucWarn  = 1;
    Gds.uiWarnStartTick             = SEC_TIMER;
    Gds.uiWarnTimeoutTick           = SEC_TIMER;
    Gds.ucIsWarning                 = 1;
    Gds.ucStatus                    = STA_S_SLAVE;                      /*  �ӿ�״̬                    */  
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
    Gds.ucIndicatorFlg.Bits.ucWarn  = 0;
    Gds.ucIsWarning                 = 0;
    Gds.ucStatus                    = STA_IDLE;                         /*  �ָ�����                    */  
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
    INT8U               ucBuf[8];
    //static INT32U     __SuiWarnTick;
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
    if (OS_TASK_RESUME_PRIO != OSTaskResume(TASK3_PRIO)) {
        ;
    } else if (SEC_TIMER - Gds.uiWarnTimeoutTick >= (Gdp.usMasterTime >> 3)) {
        if (__GptnCurMenu) {
            miFlush();
            mainDisplay();
        }
    } else if (SEC_TIMER - Gds.uiWarnTimeoutTick >= 1)  /*(MS_TIMER - __SuiWarnTick >= 500)*/ {
        if (Gds.uiValveStatus) {
            Gds.uiValveStatus = 0;
        //if (Gds.uiValveStatus == 0) {
            guiClrRectangle(0, 16, 127, 63);
            Gds.uiValveStatus = 0;
            guiPrintf(0, 0, 0, "Ԥ������");
            //__SuiWarnTick = MS_TIMER;
        //}
        }
    }
    
    return SYS_OK;
}


/*********************************************************************************************************
  �Կز˵�ҳ����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibSlv = {                               /*  �˵�����Ϣ                  */
    "Ԥ������  [�ӿ�]",//"Ƥ�����ƿ���    ",
    (MENU_ITEM_FUNC *)&GmifSlv,
    0x3200
};

/*********************************************************************************************************
** Function name:           miSlvInit
** Descriptions:            �ӿز˵����ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miSlvInit(void)
{ 
    /*
     *  ��Ӳ˵�ҳ
     */
    miAdd(&__GmiibRoot, &__GmiibSlv);                                           /*  �ײ˵��ڵ�                  */
}
/*********************************************************************************************************
** Function name:           miSlvDel
** Descriptions:            �ӿز˵���ж��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miSlvDel(void)
{ 
    /*
     *  ɾ���˵�ҳ
     */
    miDel(&__GmiibSlv);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
