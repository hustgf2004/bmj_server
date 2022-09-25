/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn  
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               AuxAction.c
** Latest modified Date:    2021-09-22
** Latest Version:          1.0
** Descriptions:            辅助动作菜单页  
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2021-09-22
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
#include    ".\00NoneAct\NoneAct.h"
#include    ".\01Rewash\Rewash.h"
#include    ".\02RearConv\RearConv.h"
#include    ".\03TailGirder\TailGirder.h"
#include    ".\04FlashBoard\FlashBoard.h"
#include    ".\05BaseLift\BaseLift.h"
#include    ".\06Rsv1\Rsv1.h"
/*********************************************************************************************************
  外部声明
*********************************************************************************************************/


/*********************************************************************************************************
  函数声明
*********************************************************************************************************/
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiiThis);
static INT32S __menuItemDel(MENU_ITEM_INFO *pmiiThis);
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiiThis, INT32U uiKeyCode);
static INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv);

/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/


/*********************************************************************************************************
  内部使用变量
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifAuxAction = {
    __menuItemCreate,
    __menuItemDel,
    __menuItemOnKey,
    __menuItemParamFmt
};
/*********************************************************************************************************
** Function name:           menuItemCreate
** Descriptions:            创建菜单页
** input parameters:        pmpiThis    菜单页信息
** output parameters:       none
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __menuItemCreate (MENU_ITEM_INFO *pmiiThis)
{
    int i;
    INT32S siErr = 0;
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
    *  ............
    */
    
    /*
     *  依次加载菜单项
     */
    siErr = miAdd(pmiiThis->pmiib, (void *)&__GmiibNoneAct);
    // siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibRewash);
    // siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibRearConv);
    // siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibTailGirder);
    // siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibFlashBoard);
    // siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibBaseLift);
    // siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibRsv1);
    return siErr;
}

/*********************************************************************************************************
** Function name:           menuItemDel
** Descriptions:            删除菜单项
** input parameters:        pmiiThis    菜单项信息
** output parameters:       none
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __menuItemDel (MENU_ITEM_INFO *pmiiThis)
{

    /*
     *
     */
    return SYS_OK;    
}

/*********************************************************************************************************
** Function name:           menuPageOnKey
** Descriptions:            菜单页按键响应函数
** input parameters:        pmiiThis    菜单项信息
**                          usLen       待处理数据长度
**                          pvData      待处理数据指针
** output parameters:       none
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __menuItemOnKey (MENU_ITEM_INFO *pmiiThis, INT32U uiKeyCode)
{  
    /*
     *  参数过滤
     */
    if (NULL == pmiiThis) {
        return (-SYS_PARA_ERR);
    }

    return SYS_OK;
}
/*********************************************************************************************************
** Function name:           menuItemParamFmt
** Descriptions:            菜单项显示函数
** input parameters:        pmiiThis    菜单项信息
**                          
**                                
** output parameters:       pvRsv       字符串输出指针
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv)
{
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
    *  ............
    */
    return SYS_OK;
}

/*********************************************************************************************************
  辅助动作菜单项定义
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibAuxAction = {                          /*  菜单项信息                  */
    "辅助动作",
    (MENU_ITEM_FUNC *)&GmifAuxAction,
    0x0000
};

/*********************************************************************************************************
** Function name:           miAuxActionInit
** Descriptions:            辅助动作菜单页初始化
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miAuxActionInit(void)
{ 
    /*
     *  添加菜单页
     */
    miAdd(&__GmiibRoot, &__GmiibAuxAction);
}
/*********************************************************************************************************
** Function name:           miAuxActionDel
** Descriptions:            辅助动作菜单页卸载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miAuxActionDel(void)
{ 
    /*
     *  删除菜单页
     */
    miDel(&__GmiibAuxAction);
}

/*********************************************************************************************************
** Function name:           miAuxToValve
** Descriptions:            辅助动作转换
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
INT32U miAuxToValve(TREE_NODE *ptnAuxMenu, INT8U ucIsAuxRight)
{
    INT32U uiValve = 0;
    MENU_ITEM_INFO *pmii;
    if (!ptnAuxMenu) {
        return uiValve;
    }
    pmii = (MENU_ITEM_INFO *)ptnAuxMenu->pvData;
    if (!pmii->pvPara) {
        return uiValve;
    }
    if (pmii->pvPara == NULL) {
        uiValve = 0;
    } else if (ucIsAuxRight) {
        uiValve = ((const INT32U *)pmii->pvPara)[1];
    } else {
        uiValve = ((const INT32U *)pmii->pvPara)[0];
    }
    return uiValve;
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

