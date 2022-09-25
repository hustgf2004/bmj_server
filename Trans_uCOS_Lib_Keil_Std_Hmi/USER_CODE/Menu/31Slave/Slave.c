/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Slave.c
** Latest modified Date:    2021-12-28
** Latest Version:          1.0
** Descriptions:            从控菜单界面  
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
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
static const MENU_ITEM_FUNC GmifSlv = {
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
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
    *  ............
    */
    Gds.ucIndicatorFlg.Bits.ucWarn  = 1;
    Gds.uiWarnStartTick             = SEC_TIMER;
    Gds.uiWarnTimeoutTick           = SEC_TIMER;
    Gds.ucIsWarning                 = 1;
    Gds.ucStatus                    = STA_S_SLAVE;                      /*  从控状态                    */  
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
    Gds.ucIndicatorFlg.Bits.ucWarn  = 0;
    Gds.ucIsWarning                 = 0;
    Gds.ucStatus                    = STA_IDLE;                         /*  恢复空闲                    */  
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
    //static INT32U     __SuiWarnTick;
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
            guiPrintf(0, 0, 0, "预警《《");
            //__SuiWarnTick = MS_TIMER;
        //}
        }
    }
    
    return SYS_OK;
}


/*********************************************************************************************************
  自控菜单页定义
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibSlv = {                               /*  菜单项信息                  */
    "预警《《  [从控]",//"皮带自移控制    ",
    (MENU_ITEM_FUNC *)&GmifSlv,
    0x3200
};

/*********************************************************************************************************
** Function name:           miSlvInit
** Descriptions:            从控菜单项初始化
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miSlvInit(void)
{ 
    /*
     *  添加菜单页
     */
    miAdd(&__GmiibRoot, &__GmiibSlv);                                           /*  首菜单节点                  */
}
/*********************************************************************************************************
** Function name:           miSlvDel
** Descriptions:            从控菜单项卸载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miSlvDel(void)
{ 
    /*
     *  删除菜单页
     */
    miDel(&__GmiibSlv);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
