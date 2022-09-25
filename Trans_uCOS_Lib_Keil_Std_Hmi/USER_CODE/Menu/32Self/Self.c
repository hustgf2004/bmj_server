/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Self.c
** Latest modified Date:    2021-10-02
** Latest Version:          1.0
** Descriptions:            �Կز˵�ҳ  
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ����������
** Created date:            2021-10-02
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
#include    ".\01Side1\Side1.h"
#include    ".\02Side2\Side2.h"
#include    ".\03Side3\Side3.h"
#include    ".\04Side4\Side4.h"
#include    ".\05Rewash\Rewash.h"
#include    ".\06BasePusher\BasePusher.h"
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
const MENU_ITEM_FUNC GmifSelf = {
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
    INT32S siErr;
    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */ 
    ledNavi(NAVI_A & NAVI_C & NAVI_F & NAVI_G & NAVI_I & NAVI_J & NAVI_1 & NAVI_2 & NAVI_3 & NAVI_4 & NAVI_B & NAVI_E & NAVI_K & NAVI_M);
    Gds.ucIndicatorFlg.Bits.ucWarn  = 1;
    Gds.uiWarnStartTick             = SEC_TIMER;
    Gds.uiWarnTimeoutTick           = SEC_TIMER;
    Gds.ucIsWarning                 = 1;
    Gds.ucStatus                    = STA_HOST;
    siErr = miAdd(pmiiThis->pmiib, (void *)&__GmiibBasePusher);
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
    
    if (OS_TASK_RESUME_PRIO != OSTaskResume(TASK3_PRIO)) {
        OSTaskDelReq(TASK3_PRIO);
    }
    ledNavi(0xffffffff);
    Gds.ucIndicatorFlg.Bits.ucWarn  = 0;
    Gds.ucIsWarning                 = 0;
    Gds.ucStatus                    = STA_IDLE;
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
    INT32U              uiValveDat;
    static INT32U     __SuiWarnTick;
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
    if (uiKeyCode) {
        Gds.uiWarnTimeoutTick = SEC_TIMER;                              /*  Ԥ����ʱ����λ              */
    }
    if (OS_TASK_RESUME_PRIO != OSTaskResume(TASK3_PRIO)) {
        guiPrintf(0, 0, 0, "  �Զ��Ƽܿ���  ");
        return;
    } 
    uiValveDat = keyToAction(uiKeyCode, GpuiKeyTbl, GpuiValveTbl);
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
        OSTaskCreate(thrdAsqAuto, (void *)&Gdp.ucAsqWarnT, &TASK3_STACK[TASK3_STACK_SIZE - 1], TASK3_PRIO);
        ledNavi(NAVI_E);
        //miFlush();
        //mainDisplay();
    } else if (uiValveDat) {                                            /*  ��������                    */
        tp_htonl(uiValveDat);                                           /*  ��С��ת��                  */
        tpWrite(TP_DEFAULT_CHNL, __TP_JOCKEY, 4, &uiValveDat, 0);
    } else {
        if (SEC_TIMER - Gds.uiWarnTimeoutTick >= Gdp.usMasterTime >> 3) {
            if (__GptnCurMenu) {
                miFlush();
                mainDisplay();
            }
        } else if (MS_TIMER - __SuiWarnTick >= 500) {
            //GUI_Rectangle(0, 16, 127, 63, 0);
            Gds.uiValveStatus = 0;
            //guiPrintf(0, 0, 0, "����  Ԥ������");
            mpHome();
            __SuiWarnTick = MS_TIMER;
        }
    }
    
    return SYS_OK;
}


/*********************************************************************************************************
  �Կز˵�ҳ����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibSelf = {                               /*  �˵�����Ϣ                  */
    "����            ",//"Ƥ�����ƿ���    ",
    (MENU_ITEM_FUNC *)&GmifSelf,
    0x3200
};

/*********************************************************************************************************
** Function name:           miSelfInit
** Descriptions:            �Կز˵����ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miSelfInit(void)
{ 
    /*
     *  ��Ӳ˵�ҳ
     */
    miAdd(&__GmiibRoot, &__GmiibSelf);                                          /*  �ײ˵��ڵ�                  */
}
/*********************************************************************************************************
** Function name:           miSelfDel
** Descriptions:            �Կز˵���ж��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miSelfDel(void)
{ 
    /*
     *  ɾ���˵�ҳ
     */
    miDel(&__GmiibSelf);
}

/*********************************************************************************************************
** Function name:           keyOnMaster
** Descriptions:            ���ؽ��水����Ӧ
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void keyOnMaster(INT32U uiKeyCode)
{
    INT8U               ucBuf[8];
    INT32U              uiValveDat;
    static INT32U     __SuiWarnTick;
    if (uiKeyCode) {
        Gds.uiWarnTimeoutTick = SEC_TIMER;                              /*  Ԥ����ʱ����λ              */
    }
    if (OS_TASK_RESUME_PRIO != OSTaskResume(TASK3_PRIO)) {
        guiPrintf(0, 0, 0, "  �Զ��Ƽܿ���  ");
        return;
    } 
    uiValveDat = keyToAction(uiKeyCode, GpuiKeyTbl, GpuiValveTbl);
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
        OSTaskCreate(thrdAsqAuto, (void *)&Gdp.ucAsqWarnT, &TASK3_STACK[TASK3_STACK_SIZE - 1], TASK3_PRIO);
        ledNavi(NAVI_E);
        //miFlush();
        //mainDisplay();
    } else if (uiValveDat) {                                            /*  ��������                    */
        tp_htonl(uiValveDat);                                           /*  ��С��ת��                  */
        tpWrite(TP_DEFAULT_CHNL, __TP_JOCKEY, 4, &uiValveDat, 0);
    } else {
        if (SEC_TIMER - Gds.uiWarnTimeoutTick >= Gdp.usMasterTime >> 3) {
            if (__GptnCurMenu) {
                miFlush();
                mainDisplay();
            }
        } else /*if (MS_TIMER - __SuiWarnTick >= 500)*/ {
            //GUI_Rectangle(0, 16, 127, 63, 0);
            if (Gds.uiValveStatus) {
                INT32U   uiIndex = 0;
                Gds.uiValveStatus = 0;
                //guiPrintf(0, 0, 0, "����  Ԥ������");
                //mpHome();
                if (miGetIndex(__GptnCurMenu, &uiIndex) < 0) {
                    uiIndex = 0;
                }
                if (uiIndex & 0x01) {
                    uiIndex -= 1;
                }
                mpDisplayEx(__GptnCurMenu->ptnParent, uiIndex );
                //mpDisplay(__GptnCurMenu->ptnParent);
            }
            __SuiWarnTick = MS_TIMER;
        }
    }
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
