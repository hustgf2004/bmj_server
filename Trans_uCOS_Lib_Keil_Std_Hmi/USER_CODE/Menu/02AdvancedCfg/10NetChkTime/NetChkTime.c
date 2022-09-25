/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn  
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               NetChkTime.c
** Latest modified Date:    2022-09-18
** Latest Version:          1.0
** Descriptions:            网络检测间隔设置菜单项
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2022-09-18
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
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemDel(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiibThis, INT16U usLen, void *pvData);
static INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv);

/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/


/*********************************************************************************************************
  内部使用变量
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifNetChkTime = {
    __menuItemCreate,
    __menuItemDel,
    __menuItemOnKey,
    __menuItemParamFmt
};

/*********************************************************************************************************
** Function name:           menuItemCreate
** Descriptions:            创建菜单项
** input parameters:        pmiiThis    菜单项信息
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
    //pmiiThis->pvPara = (void *)&Gdp.ucDir;
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           menuItemDel
** Descriptions:            删除菜单项
** input parameters:        pmpiThis    菜单项信息
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
** Descriptions:            菜单项按键响应函数
** input parameters:        pmiiThis    菜单项信息
**                          usLen       待处理数据长度
**                          pvData      待处理数据指针
** output parameters:       none
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __menuItemOnKey (MENU_ITEM_INFO *pmiiThis, INT16U usLen, void *pvData)
{    
    //static INT8U    __SucEnFlag = 0;
    unsigned int    uiLen;    
    INT32U         *puiKeyCode;
    
    char            scParamFmt[32] = {0};
    INT32U          uiX, uiY;
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
    *  ............
    */
    uiX = pmiiThis->ucX + strlen(pmiiThis->pmiib->pcTitle) * FONT_XSIZE8;
    uiY = pmiiThis->ucY;
    
    puiKeyCode = pvData;

    switch(puiKeyCode[0]) {        
        case KEY_ENTER:

        break;
        case KEY_ABORT:
            pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, scParamFmt);
            guiPrintf(uiX, uiY, 1, "%s", scParamFmt);
        break;
        default:
        break;
    }
    return SYS_OK;  
}
/*********************************************************************************************************
** Function name:           menuItemParamFmt
** Descriptions:            菜单项显示函数
** input parameters:        pmiiThis        菜单项信息
**                          usFocus         待处理数据长度
**                          pvRsv           待处理数据指针
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv)
{
    INT16U      usWarnTime;
    INT8U      *pucPara;
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
    if (NULL == pvRsv) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == pmiiThis->pvPara) {
        return (-SYS_NOT_OK);
    }
    pucPara = (INT8U *)pmiiThis->pvPara;     
    usWarnTime = pucPara[0] | (pucPara[1] << 8);
    sprintf(pvRsv, ":%4d.%dS", usWarnTime / 10, usWarnTime % 10);
    return SYS_OK;
}

/*********************************************************************************************************
  网络检测间隔菜单项定义
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibNetChkTime = {                           /*  菜单项信息                  */
    "网络检测",
    (MENU_ITEM_FUNC *)&GmifNetChkTime,
    0x010A,
    (1 << 7) | (PARA_SCOPE_GLOBAL << 4) | PARA_TYPE_VALUE
};


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
