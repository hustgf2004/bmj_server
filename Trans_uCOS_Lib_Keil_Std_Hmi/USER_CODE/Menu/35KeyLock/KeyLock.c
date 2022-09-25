/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               KeyLock.c
** Latest modified Date:    2021-12-26
** Latest Version:          1.0
** Descriptions:            键盘闭锁菜单页  
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2021-12-26
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
const MENU_ITEM_FUNC GmifKeyLock = {
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
    guiClrScr();
    guiPrintf(0, 16, 0, "%s", __GmiibLock.pcTitle); 
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
    return SYS_OK;    
}
/*********************************************************************************************************
** Function name:       keyShow
** Descriptions:        键盘闭锁时的键值显示
** input parameters:    uiKeyCode               按键值
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void keyShow(INT32U uiKeyCode)
{
    if (!uiKeyCode) {
        return;
    }
    guiClrScr();
    guiPrintf(0, 16, 0,"    键盘闭锁  ");
    if (uiKeyCode == JP_A) {             
        guiPrintf(0, 16 * 2, 0,"    A号键按下  ");            
    } else if (uiKeyCode == JP_D) {
        guiPrintf(0, 16 * 2, 0,"    D号键按下  "); 
    } else if (uiKeyCode == JP_1) {
        guiPrintf(0, 16 * 2, 0,"    1号键按下  "); 
    } else if (uiKeyCode == JP_2) {
        guiPrintf(0, 16 * 2, 0,"    2号键按下  "); 
    } else if (uiKeyCode == JP_3) {
        guiPrintf(0, 16 * 2, 0,"    3号键按下  "); 
    } else if (uiKeyCode == JP_4) {
        guiPrintf(0, 16 * 2, 0,"    4号键按下  "); 
    } else if (uiKeyCode == JP_5) {
        guiPrintf(0, 16 * 2, 0,"    5号键按下  "); 
    } else if (uiKeyCode == JP_6) {
        guiPrintf(0, 16 * 2, 0,"    6号键按下  "); 
    } else if (uiKeyCode == JP_7) {
        guiPrintf(0, 16 * 2, 0,"    7号键按下  "); 
    } else if (uiKeyCode == JP_8) {
        guiPrintf(0, 16 * 2, 0,"    8号键按下  "); 
    } else if (uiKeyCode == JP_P) {
        guiPrintf(0, 16 * 2, 0,"    P号键按下  "); 
    } else if (uiKeyCode == JP_N) {
        guiPrintf(0, 16 * 2, 0,"    N号键按下  "); 
    } else if (uiKeyCode == JP_9) {
        guiPrintf(0, 16 * 2, 0,"    9号键按下  "); 
    } else if (uiKeyCode == JP_0) {
        guiPrintf(0, 16 * 2, 0,"    0号键按下  "); 
    } else if (uiKeyCode == JP_U) {
        guiPrintf(0, 16 * 2, 0,"    U号键按下  "); 
    } else if (uiKeyCode == JP_K) {
        guiPrintf(0, 16 * 2, 0,"    K号键按下  "); 
    } else if (uiKeyCode == JP_M) {
        guiPrintf(0, 16 * 2, 0,"    M号键按下  "); 
    } else if (uiKeyCode == JP_D) {
        guiPrintf(0, 16 * 2, 0,"    D号键按下  "); 
    } else if (uiKeyCode == JP_B) {
        guiPrintf(0, 16 * 2, 0,"    B号键按下  "); 
    } else if (uiKeyCode == JP_E) {
        guiPrintf(0, 16 * 2, 0,"    E号键按下  "); 
    } else if (uiKeyCode == JP_L) {
        guiPrintf(0, 16 * 2, 0,"    L号键按下  "); 
    } else if (uiKeyCode == JP_R) {
        guiPrintf(0, 16 * 2, 0,"    R号键按下  "); 
    } else {
        //guiPrintf(0, 16 * 2, 0,"   未知键按下  "); 
    }
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
    static INT8U   __SucPwdIndex;
    INT32U  uiValveDat;
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
    if (uiKeyCode == JP_A) {             
        guiPrintf(0, 24, 0,"    A号键按下  ");            
    } else if (uiKeyCode == JP_D) {
        guiPrintf(0, 24, 0,"    D号键按下  "); 
    } else if (uiKeyCode == JP_1) {
        guiPrintf(0, 24, 0,"    1号键按下  "); 
    } else if (uiKeyCode == JP_2) {
        guiPrintf(0, 24, 0,"    2号键按下  "); 
    } else if (uiKeyCode == JP_3) {
        guiPrintf(0, 24, 0,"    3号键按下  "); 
    } else if (uiKeyCode == JP_4) {
        guiPrintf(0, 24, 0,"    4号键按下  "); 
    } else if (uiKeyCode == JP_5) {
        guiPrintf(0, 24, 0,"    5号键按下  "); 
    } else if (uiKeyCode == JP_6) {
        guiPrintf(0, 24, 0,"    6号键按下  "); 
    } else if (uiKeyCode == JP_7) {
        guiPrintf(0, 24, 0,"    7号键按下  "); 
    } else if (uiKeyCode == JP_8) {
        guiPrintf(0, 24, 0,"    8号键按下  "); 
    } else if (uiKeyCode == JP_P) {
        guiPrintf(0, 24, 0,"    P号键按下  "); 
    } else if (uiKeyCode == JP_N) {
        guiPrintf(0, 24, 0,"    N号键按下  "); 
    } else if (uiKeyCode == JP_9) {
        guiPrintf(0, 24, 0,"    9号键按下  "); 
    } else if (uiKeyCode == JP_0) {
        guiPrintf(0, 24, 0,"    0号键按下  "); 
    } else if (uiKeyCode == JP_U) {
        guiPrintf(0, 24, 0,"    U号键按下  "); 
    } else if (uiKeyCode == JP_K) {
        guiPrintf(0, 24, 0,"    K号键按下  "); 
    } else if (uiKeyCode == JP_M) {
        guiPrintf(0, 24, 0,"    M号键按下  "); 
    } else if (uiKeyCode == JP_D) {
        guiPrintf(0, 24, 0,"    D号键按下  "); 
    } else if (uiKeyCode == JP_B) {
        guiPrintf(0, 24, 0,"    B号键按下  "); 
    } else if (uiKeyCode == JP_E) {
        guiPrintf(0, 24, 0,"    E号键按下  "); 
    } else if (uiKeyCode == JP_L) {
        guiPrintf(0, 24, 0,"    L号键按下  "); 
    } else if (uiKeyCode == JP_R) {
        guiPrintf(0, 24, 0,"    R号键按下  "); 
    } else {
        ;guiPrintf(0, 24, 0,"   未知键按下  "); 
    }
    switch(__SucPwdIndex) {
        case 0:
            if (uiKeyCode == JP_R) {
                __SucPwdIndex++;
            }
        break;

        case 1:
            if (uiKeyCode == JP_E) {
                __SucPwdIndex++;
            } else if (uiKeyCode == JP_R) {
                __SucPwdIndex = 1;
            } else {
                __SucPwdIndex = 0;
            }
        break;

        case 2:
            if (uiKeyCode == JP_L) {
                //__SucPwdIndex++;
                miFlush(); 
                mainDisplay();
            } else if (uiKeyCode == JP_R) {
                __SucPwdIndex = 1;
            } else {
                __SucPwdIndex = 0;
            }
        break;

        default:
            __SucPwdIndex = 0;
        break;
    }
    return SYS_OK;
}


/*********************************************************************************************************
  键盘锁定菜单页定义
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibKeyLock = {                            /*  菜单项信息                  */
    "    键盘闭锁    ",
    (MENU_ITEM_FUNC *)&GmifKeyLock,
    0x3500
};

/*********************************************************************************************************
** Function name:           miKeyLockInit
** Descriptions:            键盘闭锁菜单初始化
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miKeyLockInit(void)
{ 
    /*
     *  添加菜单页
     */
    miAdd(&__GmiibRoot, &__GmiibKeyLock);                                          /*  首菜单节点                  */
}
/*********************************************************************************************************
** Function name:           miKeyLockDel
** Descriptions:            按键闭锁菜单卸载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miKeyLockDel(void)
{ 
    /*
     *  删除菜单页
     */
    miDel(&__GmiibKeyLock);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
