/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn                              
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               PusherInStartTime.c
** Latest modified Date:    2021-12-26
** Latest Version:          1.0
** Descriptions:            自动移架参数配置菜单
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
 
#include    "..\..\..\main.h"
/*********************************************************************************************************
  外部声明
*********************************************************************************************************/
extern DEV_PARA Gdp;

/*********************************************************************************************************
  函数声明
*********************************************************************************************************/
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemDel(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiibThis, INT32U uiKeyCode);
static INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv);

/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/


/*********************************************************************************************************
  内部使用变量
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifPusherInStartTime = {
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
    pmiiThis->pvPara = (void *)&Gdp.ucPusherInStartT;
    return SYS_OK;
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
static INT32S __menuItemOnKey (MENU_ITEM_INFO *pmiiThis, INT32U uiKeyCode)
{
    static INT8U    __SucAlarmType;
    unsigned int    uiLen;    
    INT32U         *puiKeyCode;
    INT8U           ucErr;
    char            scParamFmt[32] = {0};
    INT32U          uiX, uiY;
    INT32U          uiRtn;
    pmiiThis = pmiiThis;
    uiX = pmiiThis->ucX + strlen(pmiiThis->pmiib->pcTitle) * FONT_XSIZE8;
    uiY = pmiiThis->ucY;
   /*  
    *  添加用户代码        
    *  ............
    */
    
    ucErr = inputInt(uiKeyCode, pmiiThis, &uiRtn);
    
    if (INPUT_UNCOMPLETED == ucErr) {
        return SYS_OK;
    }
    if (INPUT_COMPLETED == ucErr) {                                     /*  参数输入完成                */
        if (uiRtn <= 60) {
            Gdp.ucPusherInStartT = uiRtn;
            eepromWrite(0, (INT8U *)&Gdp, sizeof(DEV_PARA));
//        if (dsSaveParam(&GdiDevInfo) < 0) {                             /*  参数保存失败                */
//            dsRecoverParam(&GdiDevInfo);
//        } else {
//            ;
//        };  
        }            
    } else if (INPUT_QUIT == ucErr) {                                   /*  退出输入                    */                              
        ;
    } else if (INPUT_UNREASONABLE == ucErr) {                           /*  输入非法                    */
        ;
    } else {                                                            /*  参数未完成输入              */
        ;
    }
    pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, scParamFmt);
    GUI_RectangleFill(uiX, uiY, GUI_LCM_XMAX, uiY + FONT_YSIZE16, 0);
    guiPrintf(uiX, uiY, 1, "%s", scParamFmt);
    __GucEntered = FALSE;
    return SYS_OK; 
}


    
/*********************************************************************************************************
** Function name:           menuItemParamFmt
** Descriptions:            菜单项显示函数
** input parameters:        pmiiThis    菜单项信息
**                          usFocus     待处理数据长度
**                          pvRsv       待处理数据指针
** output parameters:       none
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv)
{
    INT16U      usWarnTime;
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
    usWarnTime = *((INT8U *)pmiiThis->pvPara);
    sprintf(pvRsv, ":%4dS", usWarnTime);
    return SYS_OK;
}
/*********************************************************************************************************
  推移收开始时间菜单项定义
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibPusherInStartTime = {                  /*  菜单项信息                  */
    "推移收开始",
    (MENU_ITEM_FUNC *)&GmifPusherInStartTime,
    0x0308,
    (1 << 7) | (PARA_SCOPE_GLOBLE << 4) | PARA_TYPE_VALUE
};
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
