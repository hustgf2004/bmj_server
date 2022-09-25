/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               AppDelete.c
** Latest modified Date:    2021-09-26
** Latest Version:          1.0
** Descriptions:            应用程序删除菜单项
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2021-09-26
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
  外部声明
*********************************************************************************************************/

/*********************************************************************************************************
  函数声明
*********************************************************************************************************/
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiiThis);
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiibThis, INT32U uiKeyCode);


/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/


/*********************************************************************************************************
  内部使用变量
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifAppDelete = {
    __menuItemCreate,
    NULL,
    __menuItemOnKey,
    NULL
};


/*********************************************************************************************************
** Function name:           menuItemCreate
** Descriptions:            创建菜单项
** input parameters:        pmiiThis    菜单项信息
** output parameters:       none
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考afxMenu.h
*********************************************************************************************************/
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiiThis)
{
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
    *  ............
    */
    pmiiThis->pvPara = (void *)0x10008000;

    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           menuItemOnKey
** Descriptions:            菜单项按键响应函数
** input parameters:        pmiiThis    菜单项信息
**                          usLen       待处理数据长度
**                          pvData      待处理数据指针
** output parameters:       none
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __menuItemOnKey (MENU_ITEM_INFO *pmiiThis, INT32U uiKeyCode)
{    
    INT32U         *puiKeyCode;

    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
    *  ............
    */

    if ((GpuiKeyTbl[KEY_ENTER] == uiKeyCode)) {                                 /*  确认发布？                  */
        if (!__GucEntered) {
            guiPrintf(pmiiThis->ucX, pmiiThis->ucY, 1, "确认删除?");
            pmiiThis->pvPara = NULL;
            __GucEntered = TRUE;
        } else {                                                                    /*  确认                        */
            guiClrScr();
            sysIrqDisable();

            OSSchedLock(); 
            //Initext(0x80000000, 12000000, 2);       // Initialize Flash Programming Functions //   Device Base Address = 0//   Clock Frequency = 12MHz
            WordProgramEx(0x80100000, 0x00000000);
            WordProgramEx(0x80100002, 0x00000000);
            WordProgramEx(0x80100004, 0x00000000);
            WordProgramEx(0x80100006, 0x00000000);                    
            vicIrqDisable(4);
            vicIrqDisable(5);
            timerStop(0);              // 停止定时/计数器1
            timerStop(1);              // 停止定时/计数器1                                    

            sysChangeToSysMode();
            switchBoot_Handler();
        }
    } else if ((__GucEntered) &&  (GpuiKeyTbl[KEY_ABORT] == uiKeyCode)) {         /*  退出                        */
        guiPrintf(pmiiThis->ucX, pmiiThis->ucY, 1, "%s", pmiiThis->pmiib->pcTitle);
        pmiiThis->pvPara = (void *)0x10008000;   
    } 

    return SYS_OK;  
}


/*********************************************************************************************************
  应用程序删除菜单项定义
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibAppDelete = {                          /*  菜单项信息                  */
    "应用程序删除",
    (MENU_ITEM_FUNC *)&GmifAppDelete,
    0x0805,
    (1 << 7) | (PARA_SCOPE_OPTIONAL << 4) | PARA_TYPE_OPERATE
};


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
