/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               PwdInput.c
** Latest modified Date:    2021-12-30
** Latest Version:          1.0
** Descriptions:            密码输入菜单页  
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2021-12-30
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

/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/


/*********************************************************************************************************
  内部使用变量
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifPwdInput = {
    __menuItemCreate,
    __menuItemDel,
    __menuItemOnKey,
    NULL
};


static INT8U __SucPassword[6];                                    
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
    memset(__SucPassword, 0x00, sizeof(__SucPassword));
    Gds.ucIsAuthorized = FALSE;
    ledNavi(NAVI_1 & NAVI_2 & NAVI_3 & NAVI_4 & NAVI_5 & NAVI_6 & NAVI_7 & NAVI_8 & NAVI_9 & NAVI_0 & NAVI_Q & NAVI_E);
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
    if (strcmp("7910", __SucPassword) == 0) {                           /*  密码正确                    */
        Gds.ucIsAuthorized = TRUE;
        Gds.uiAuthorizedTimeoutTick = SEC_TIMER;
    }
    __GucEntered = 0;
    ledNavi(0xffffffff);
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
    INT8U           ucErr;
    INT32U          uiIdx;
    //static INT8U __SucPassword[6];
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

    ucErr = inputPwd(0, 16, uiKeyCode, 6, __SucPassword);
    if (INPUT_QUIT == ucErr) {                                          /*  退出输入                    */
        memset(__SucPassword, 0x00, sizeof(__SucPassword));
        miDel(&__GmiibPwdInput);
        //mpHome(); 
        __GptnCurMenu = __GptnCurMenu->ptnParent;                       /*  恢复原有菜单项              */
        if (miGetIndex(__GptnCurMenu, &uiIdx) < 0) {
            uiIdx = 0;
        }
        if (uiIdx & 0x01) {
            uiIdx -= 1;
        }
        mpDisplayEx(__GptnCurMenu->ptnParent, uiIdx);                   /*  显示当前菜单                */
    } else if (INPUT_COMPLETED == ucErr) {                              /*  密码输入完成                */
        miDel(&__GmiibPwdInput);
        //mpHome();
        __GptnCurMenu = __GptnCurMenu->ptnParent;
        if (miGetIndex(__GptnCurMenu, &uiIdx) < 0) {
            uiIdx = 0;
        }
        if (uiIdx & 0x01) {
            uiIdx -= 1;
        }
        mpDisplayEx(__GptnCurMenu->ptnParent, uiIdx);                   /*  显示当前菜单                */
    }
    return SYS_OK;
}


/*********************************************************************************************************
  密码输入菜单页定义
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibPwdInput = {                    /*  菜单项信息                  */
    "请输入密码",
    (MENU_ITEM_FUNC *)&GmifPwdInput,
    0x6300
};

/*********************************************************************************************************
** Function name:           miPwdInputInit
** Descriptions:            密码输入菜单项初始化
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miPwdInputInit(void)
{ 
    /*
     *  添加菜单页
     */
    miAdd(NULL, &__GmiibPwdInput);
}
/*********************************************************************************************************
** Function name:           miPwdInputDel
** Descriptions:            密码输入菜单项卸载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void mpPwdInputDel (void)
{ 
    /*
     *  删除菜单页
     */
    miDel(&__GmiibPwdInput);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
