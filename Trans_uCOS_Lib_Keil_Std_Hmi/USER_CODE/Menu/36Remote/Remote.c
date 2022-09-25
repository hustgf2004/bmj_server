/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Remote.c
** Latest modified Date:    2022-01-02
** Latest Version:          1.0
** Descriptions:            无线遥控菜单页  
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2022-01-02
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
static const MENU_ITEM_FUNC GmifRemote = {
    __menuItemCreate,
    __menuItemDel,
    __menuItemOnKey,
    NULL
};


// void __GUI_Printf(unsigned int uiXPoint, unsigned int uiYPoint, INT8U ucIsAnti, char * pcString,...)
// {
//     char    cStr[160];
//     va_list ap;
//     if (NULL == pcString) {
//         return;
//     }
//     va_start(ap,pcString);
//     vsprintf(cStr+3,pcString,ap);
//     va_end(ap); 
//     cStr[0] =  uiXPoint;
//     cStr[1] =  uiYPoint; 
//     cStr[2] =  ucIsAnti;
//     pcString =  cStr; 
//     tpWrite(__TP_UART_EXT_CHN2, 0x21, strlen(pcString + 3) + 4, pcString, 0);
// }

// void __GUI_ClearSCR(void)
// {
//     INT8U ucChar = 0x01;
//     tpWrite(__TP_UART_EXT_CHN2, 0x22, 1, &ucChar, 0);
// }
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
    INT32U      uiDummyKey;
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
    *  ............
    */ 
    //Gds.ucIsRemoteReady     = TRUE;
    Gds.uiMasterTimeoutTick = MS_TIMER;
    gpioSet(__LED1_CONTROL_RED);
    gpioSet(__LED2_CONTROL_BLUE);
    //Gds.ucStatus            = STA_S_SLAVE;
    //__GUI_ClearSCR();
    
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
    Gds.ucIsRemoteReady     = FALSE;
    Gds.ucStatus            = STA_IDLE;
    gpioClr(__LED1_CONTROL_RED);
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
    INT32S              siErr;
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
    if (uiKeyCode) {                                                    /*  有按键                      */
        Gds.uiRemoteTimeoutTick = SEC_TIMER;                            /*  复位遥控器连接超时计时器    */
    } else {                                                            /*  无按键                      */
        ucBuf[0] = Gdp.ucShieldNo;
        ucBuf[1] = 0xaa;
        ucBuf[2] = 0xff;
        ucBuf[3] = Gdp.usGblFaceMax;
        ucBuf[4] = Gds.ucStatus;
        siErr = tpWrite(__TP_UART_EXT_CHN2, __TP_REMOTE_CONFIRM, 5, ucBuf, 1);
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
        static AUTO_PARA __Sap;
        __Sap.ucFlipInActT      = Gdp.ucFlipInActT;
        __Sap.ucFlipInStartT    = Gdp.ucFlipInStartT;
        __Sap.ucFlipOutActT     = Gdp.ucFlipOutActT;
        __Sap.ucFlipOutStartT   = Gdp.ucFlipOutStartT;
        __Sap.ucPusherInActT    = Gdp.ucPusherInActT;
        __Sap.ucPusherInStartT  = Gdp.ucPusherInStartT;
        __Sap.ucPusherOutActT   = Gdp.ucPusherOutActT;
        __Sap.ucPusherOutStartT = Gdp.ucPusherOutStartT;
        __Sap.ucAsqWarnT        = Gdp.ucAsqWarnT;
        __Sap.ucLiftInStartT    = Gdp.ucLiftInStartT;
        __Sap.ucLiftInActT      = Gdp.ucLiftInActT;
        __Sap.ucLiftOutStartT   = Gdp.ucLiftOutStartT;
        __Sap.ucLiftOutActT     = Gdp.ucLiftOutActT;
        OSTaskCreate(thrdAsqAuto, (void *)&__Sap, &TASK3_STACK[TASK3_STACK_SIZE - 1], TASK3_PRIO);
        //miFlush();
        //mainDisplay();
    } else if (uiValveDat) {                                            /*  动作按键                    */
        tp_htonl(uiValveDat);                                           /*  大小端转换                  */
        tpWrite(TP_DEFAULT_CHNL, __TP_JOCKEY, 4, &uiValveDat, 0);        
    } else {
        if (OS_TASK_RESUME_PRIO != OSTaskResume(TASK3_PRIO)) {
            ;
        } else if (SEC_TIMER - Gds.uiRemoteTimeoutTick >= Gdp.usMasterTime >> 3) {
            ucBuf[0] = Gdp.ucShieldNo;
            ucBuf[1] = 0x55;
            ucBuf[2] = 0xff;
            ucBuf[3] = Gdp.usGblFaceMax;
            ucBuf[4] = Gds.ucStatus;
            siErr = tpWrite(__TP_UART_EXT_CHN2, __TP_CONNECT, 5, ucBuf, 1);
            if (siErr >= 0) {
                ;
            } else {
                //Gds.ucIsReceiverReady = FALSE;
            }
            if (__GptnCurMenu) {
                miFlush();
                mainDisplay();
            }
        } else {
            ucBuf[0] = Gdp.ucShieldNo;
            ucBuf[1] = 0xAA;
            ucBuf[2] = 0xff;
            ucBuf[3] = Gdp.usGblFaceMax;
            ucBuf[4] = Gds.ucStatus;
            siErr = tpWrite(__TP_UART_EXT_CHN2, __TP_CONNECT, 5, ucBuf, 1);
        }
    }
    
    return SYS_OK;
}


/*********************************************************************************************************
  遥控菜单页定义
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibRemote = {                             /*  菜单项信息                  */
    "遥控操作",
    (MENU_ITEM_FUNC *)&GmifRemote,
    0x3600
};

/*********************************************************************************************************
** Function name:           miRemoteInit
** Descriptions:            遥控菜单项初始化
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miRemoteInit(void)
{ 
    /*
     *  添加菜单页
     */
    miAdd(&__GmiibRoot, &__GmiibRemote);                                        /*  首菜单节点                  */
}
/*********************************************************************************************************
** Function name:           miRemotefDel
** Descriptions:            遥控菜单项卸载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miRemoteDel(void)
{ 
    /*
     *  删除菜单页
     */
    miDel(&__GmiibRemote);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
