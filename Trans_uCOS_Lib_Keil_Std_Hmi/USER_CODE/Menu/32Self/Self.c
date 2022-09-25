/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Self.c
** Latest modified Date:    2021-10-02
** Latest Version:          1.0
** Descriptions:            自控菜单页  
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
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
  外部声明
*********************************************************************************************************/
extern TREE_NODE      *__GptnCurMenu;                                   /*  当前菜单节点                */
extern TREE_NODE      *__GptnRootMenu;                                  /*  菜单根节点                  */

/*********************************************************************************************************
  函数声明
*********************************************************************************************************/
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemDel(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiibThis, INT32U uiKeyCode);
//static INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv);

/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/


/*********************************************************************************************************
  内部使用变量
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifSelf = {
    __menuItemCreate,
    __menuItemDel,
    __menuItemOnKey,
    NULL
};
                                 
/*********************************************************************************************************
** Function name:           menuItemCreate
** Descriptions:            创建菜单项
** input parameters:        pmiiThis    菜单页信息
** output parameters:       none
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __menuItemCreate (MENU_ITEM_INFO *pmiiThis)
{
    INT32S siErr;
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
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
** Descriptions:            删除菜单页
** input parameters:        pmiiThis    菜单页信息
** output parameters:       none
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __menuItemDel (MENU_ITEM_INFO *pmiiThis)
{
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
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
** Descriptions:            菜单项按键响应函数
** input parameters:        pmiiThis    菜单页信息
**                          usLen       待处理数据长度
**                          pvData      待处理数据指针
** output parameters:       none
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __menuItemOnKey (MENU_ITEM_INFO *pmiiThis, INT32U uiKeyCode)
{
    INT8U               ucBuf[8];
    INT32U              uiValveDat;
    static INT32U     __SuiWarnTick;
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
    *  ............
    */
    
    /*
     *  参数过滤
     */
    if (NULL == pmiiThis) {
        return (-SYS_PARA_ERR);
    }
    if (uiKeyCode) {
        Gds.uiWarnTimeoutTick = SEC_TIMER;                              /*  预警计时器复位              */
    }
    if (OS_TASK_RESUME_PRIO != OSTaskResume(TASK3_PRIO)) {
        guiPrintf(0, 0, 0, "  自动移架控制  ");
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
    } else if (uiValveDat) {                                            /*  动作按键                    */
        tp_htonl(uiValveDat);                                           /*  大小端转换                  */
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
            //guiPrintf(0, 0, 0, "本架  预警《《");
            mpHome();
            __SuiWarnTick = MS_TIMER;
        }
    }
    
    return SYS_OK;
}


/*********************************************************************************************************
  自控菜单页定义
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibSelf = {                               /*  菜单项信息                  */
    "本架            ",//"皮带自移控制    ",
    (MENU_ITEM_FUNC *)&GmifSelf,
    0x3200
};

/*********************************************************************************************************
** Function name:           miSelfInit
** Descriptions:            自控菜单项初始化
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miSelfInit(void)
{ 
    /*
     *  添加菜单页
     */
    miAdd(&__GmiibRoot, &__GmiibSelf);                                          /*  首菜单节点                  */
}
/*********************************************************************************************************
** Function name:           miSelfDel
** Descriptions:            自控菜单项卸载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miSelfDel(void)
{ 
    /*
     *  删除菜单页
     */
    miDel(&__GmiibSelf);
}

/*********************************************************************************************************
** Function name:           keyOnMaster
** Descriptions:            主控界面按键响应
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
        Gds.uiWarnTimeoutTick = SEC_TIMER;                              /*  预警计时器复位              */
    }
    if (OS_TASK_RESUME_PRIO != OSTaskResume(TASK3_PRIO)) {
        guiPrintf(0, 0, 0, "  自动移架控制  ");
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
    } else if (uiValveDat) {                                            /*  动作按键                    */
        tp_htonl(uiValveDat);                                           /*  大小端转换                  */
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
                //guiPrintf(0, 0, 0, "本架  预警《《");
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
