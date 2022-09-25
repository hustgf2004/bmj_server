/****************************************Copyright (c)****************************************************
**                            
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               HighPressureEn.c
** Latest modified Date:    2017-04-03
** Latest Version:          1.0
** Descriptions:            高压传感器使能菜单项
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2017-04-03
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
extern __DEV_INFO GdiDevInfo;
extern const  char *const __SscEnStr[];
extern INT8U    __SucEnFlag;
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
const MENU_ITEM_FUNC GmifHighPressureEn = {
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
**                          负数        错误,绝对值参考afxMenu.h
** Created by:              
** Created Date:            2017-04-03
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT32S __menuItemCreate (MENU_ITEM_INFO *pmiiThis)
{
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
    *  ............
    */
    pmiiThis->pvPara = (void *)&GdiDevInfo.uiEnFlag;
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           menuItemDel
** Descriptions:            删除菜单项
** input parameters:        pmiiThis    菜单项信息
** output parameters:       none
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考afxMenu.h
** Created by:              
** Created Date:            2017-04-03
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
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
**                          负数        错误,绝对值参考afxMenu.h
** Created by:              
** Created Date:            2017-04-03
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
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
        case KEY_UP:
        case KEY_0:
            __SucEnFlag = 0;
            uiLen = strlen(pmiiThis->pmiib->pcTitle);
            guiPrintf(pmiiThis->ucX + uiLen * 8, pmiiThis->ucY, 1, "?%s", __SscEnStr[__SucEnFlag]);
        break;
        case KEY_DOWN:
        case KEY_1:
            __SucEnFlag = 1;
            uiLen = strlen(pmiiThis->pmiib->pcTitle);
            guiPrintf(pmiiThis->ucX + uiLen * 8, pmiiThis->ucY, 1, "?%s", __SscEnStr[__SucEnFlag]);    
        break;
        
        case KEY_ENTER:
            if (!__GucEntered) {
                __SucEnFlag = (((INT32U *)pmiiThis->pvPara)[0] >> EN_HIGH_P_SNR) & 0x01; 
                guiPrintf(uiX, uiY, 1, "?");
                break;
            }
            if (__SucEnFlag) {
                ((INT32U *)pmiiThis->pvPara)[0] |= (1 << EN_HIGH_P_SNR);
            } else {
                ((INT32U *)pmiiThis->pvPara)[0] &= ~(1 << EN_HIGH_P_SNR);
            }
            //GdiDevInfo.ucPressureEn[2] = __SucEnFlag;
            if (dsSaveParam(&GdiDevInfo) < 0) {                         /*  参数保存失败                */
                //提示保存参数错误
                dsRecoverParam(&GdiDevInfo);
            } else {
 
            }
            pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, scParamFmt);
            guiPrintf(uiX, uiY, 1, "%s", scParamFmt);
        break;
        case KEY_ESC:
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
** input parameters:        pmiiThis    菜单项信息
**                          usFocus     待处理数据长度
**                          pvRsv       待处理数据指针
** output parameters:       none
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考afxMenu.h
** Created by:              
** Created Date:            2017-04-03
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv)
{
    INT32U ucPressureEn;
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
    ucPressureEn = ((INT32U *)pmiiThis->pvPara)[0];
    sprintf(pvRsv, ":%s", __SscEnStr[(ucPressureEn >> EN_HIGH_P_SNR) & 0x01]);
    return SYS_OK;
}

/*********************************************************************************************************
  高压传感器使能菜单项定义
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibHighPressureEn = {                     /*  菜单项信息                  */
    "高压瓶压力",
    (MENU_ITEM_FUNC *)&GmifHighPressureEn,
    0x0805
};


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
