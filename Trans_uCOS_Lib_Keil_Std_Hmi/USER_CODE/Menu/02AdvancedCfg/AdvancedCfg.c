/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn  
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               AdvancedCfg.c
** Latest modified Date:    2022-09-23
** Latest Version:          1.0
** Descriptions:            基本设置菜单页  
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2022-09-23
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
#include    ".\01PwdAdmin\PwdAdmin.h"
#include    ".\02PwdDeveloper\PwdDeveloper.h"
#include    ".\03SwDel\SwDel.h"
/*********************************************************************************************************
  外部声明
*********************************************************************************************************/


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
const MENU_ITEM_FUNC GmifAdvanced = {
    __menuItemCreate,
    __menuItemDel,
    __menuItemOnKey,
    NULL
};
/*********************************************************************************************************
** Function name:           menuItemCreate
** Descriptions:            创建菜单页
** input parameters:        pmiiThis    菜单页信息
** output parameters:       none
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __menuItemCreate (MENU_ITEM_INFO *pmiiThis)
{
    INT32S      siErr = 0;
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
    *  ............
    */
     
    siErr = miAdd(pmiiThis->pmiib, (void *)&__GmiibPwdAdmin);
    siErr+= miAdd(pmiiThis->pmiib, &__GmiibSwDel);
    return siErr;
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
** Function name:           menuItemOnKey
** Descriptions:            菜单页按键响应函数
** input parameters:        pmiiThis    菜单页信息
**                          usLen       待处理数据长度
**                          pvData      待处理数据指针
** output parameters:       none
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __menuItemOnKey (MENU_ITEM_INFO *pmiiThis, INT32U uiKeyCode)
{
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
    *  ............
    */
    
    return SYS_OK;
}


/*********************************************************************************************************
  高级设置菜单页定义
*********************************************************************************************************/
static const MENU_ITEM_INFO_BASE __GmiibAdvanced = {                    /*  菜单页信息                  */
    "高级设置",
    (MENU_ITEM_FUNC *)&GmifAdvanced,
    0x0100
};

/*********************************************************************************************************
** Function name:           miAdvancedCfgInit
** Descriptions:            高级设置菜单页初始化
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miAdvancedCfgInit(void)
{
    /*
     *  添加菜单页
     */
    miAdd(&__GmiibRoot, &__GmiibAdvanced);
}
/*********************************************************************************************************
** Function name:           miAdvancedCfgDel
** Descriptions:            高级设置菜单页卸载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miAdvancedCfgDel (void)
{ 
    /*
     *  删除菜单页
     */
    miDel(&__GmiibAdvanced);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
