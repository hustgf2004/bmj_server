/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               SysInfo.c
** Latest modified Date:    2021-09-26
** Latest Version:          1.0
** Descriptions:            系统信息菜单页  
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

#include    "..\..\main.h"   
#include    ".\01HwVer\HwVer.h"
#include    ".\02SwVer\SwVer.h"
#include    ".\03AppRelease\AppRelease.h"
#include    ".\04ParaRelease\ParaRelease.h"
#include    ".\05AppDelete\AppDelete.h"
#include    ".\06PwrGrpId\PwrGrpId.h"
#include    ".\07ObliquitySnrId\ObliquitySnrId.h"
#include    ".\08ObliquityFwDelete\ObliquityFwDelete.h"
#include    ".\09Reset\Reset.h"

/*********************************************************************************************************
  外部声明
*********************************************************************************************************/


/*********************************************************************************************************
  函数声明
*********************************************************************************************************/
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemDel(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiiThis, INT32U uiKeyCode);
//static INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv);

/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/


/*********************************************************************************************************
  内部使用变量
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifSysInfo = {
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
    /*
     *  依次加载菜单项
     */
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibHwVer);
	siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibSwVer); 
//    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibAppRelease);
//    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibParaRelease);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibAppDelete);
//    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibPwrGrpId);
//    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibObliquitySnrId);
//    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibObliquityFwDelete);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibReset);
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
  系统信息菜单页定义
*********************************************************************************************************/
static const MENU_ITEM_INFO_BASE __GmiibSysInfo = {                     /*  菜单页信息                  */
    "系统信息",
    (MENU_ITEM_FUNC *)&GmifSysInfo,
    0x0800
};

/*********************************************************************************************************
** Function name:           miSysInfoInit
** Descriptions:            系统信息菜单页初始化
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miSysInfoInit(void)
{ 
    /*
     *  添加菜单页
     */
    miAdd(&__GmiibRoot, &__GmiibSysInfo);
}
/*********************************************************************************************************
** Function name:           miSysInfoDel
** Descriptions:            系统信息菜单页卸载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miSysInfoDel (void)
{ 
    /*
     *  删除菜单页
     */
    miDel(&__GmiibSysInfo);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
