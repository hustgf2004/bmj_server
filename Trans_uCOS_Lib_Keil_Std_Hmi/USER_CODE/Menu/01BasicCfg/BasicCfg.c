/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn  
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               BasicCfg.c
** Latest modified Date:    2022-09-17
** Latest Version:          1.0
** Descriptions:            基本设置菜单页  
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2022-09-17
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
#include    ".\01MinNo\MinNo.h"
#include    ".\02MaxNo\MaxNo.h"
#include    ".\03MasterTime\MasterTime.h"
#include    ".\04AddrDir\AddrDir.h"
#include    ".\05ShieldNo\ShieldNo.h"
#include    ".\06ServerEn\ServerEn.h"
#include    ".\07IrUploadEn\IrUploadEn.h"
#include    ".\08IrUploadTime\IrUploadTime.h"
#include    ".\09OpUploadEn\OpUploadEn.h"
#include    ".\10NetChkTime\NetChkTime.h"
#include    ".\11GateWayEn\GateWayEn.h"
#include    ".\12GateWayDir\GatewayDir.h"
#include    ".\13StartNo\StartNo.h"
#include    ".\14ScreenSave\ScreenSave.h"
#include    ".\15SnrUploadTime\SnrUploadTime.h"
#include    ".\16Lightness\Lightness.h"
#include    ".\17SwVer\SwVer.h"
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
const MENU_ITEM_FUNC GmifBasic = {
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
     
    siErr = miAdd(pmiiThis->pmiib, (void *)&__GmiibMinNo);
    siErr+= miAdd(pmiiThis->pmiib, (void *)&__GmiibMaxNo);
    siErr+= miAdd(pmiiThis->pmiib, (void *)&__GmiibMasterTime);
    siErr+= miAdd(pmiiThis->pmiib, (void *)&__GmiibShieldNo);
    siErr+= miAdd(pmiiThis->pmiib, &__GmiibServerEn);
    siErr+= miAdd(pmiiThis->pmiib, &__GmiibIrUploadEn);
    siErr+= miAdd(pmiiThis->pmiib, &__GmiibIrUploadTime);
    siErr+= miAdd(pmiiThis->pmiib, &__GmiibOpUploadEn);
    siErr+= miAdd(pmiiThis->pmiib, &__GmiibNetChkTime);
    siErr+= miAdd(pmiiThis->pmiib, &__GmiibGatewayEn);
    siErr+= miAdd(pmiiThis->pmiib, &__GmiibGatewayDir);
    siErr+= miAdd(pmiiThis->pmiib, &__GmiibStartNo);
    siErr+= miAdd(pmiiThis->pmiib, &__GmiibScreenSave);
    siErr+= miAdd(pmiiThis->pmiib, &__GmiibSnrUploadTime);
    siErr+= miAdd(pmiiThis->pmiib, &__GmiibSwVer);
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
  通信参数设置菜单页定义
*********************************************************************************************************/
static const MENU_ITEM_INFO_BASE __GmiibBasic = {                       /*  菜单页信息                  */
    "基本设置",
    (MENU_ITEM_FUNC *)&GmifBasic,
    0x0100
};

/*********************************************************************************************************
** Function name:           miBasicCfgInit
** Descriptions:            基本参数设置菜单页初始化
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miBasicCfgInit(void)
{ 


    /*
     *  添加菜单页
     */
    miAdd(&__GmiibRoot, &__GmiibBasic);
}
/*********************************************************************************************************
** Function name:           miBasicCfgDel
** Descriptions:            基本参数设置菜单页卸载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miBasicCfgDel (void)
{ 
    /*
     *  删除菜单页
     */
    miDel(&__GmiibBasic);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
