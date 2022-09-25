/****************************************Copyright (c)****************************************************
**                            
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               MidPDeltaThreshold.c
** Latest modified Date:    2017-04-20
** Latest Version:          1.0
** Descriptions:            中压->高压切换压差阈值菜单项
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2017-04-20
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
const MENU_ITEM_FUNC GmifMidPDeltaThreshold = {
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
** Created Date:            2017-04-20
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
    pmiiThis->pvPara = (FP32 *)&GdiDevInfo.fpDeltaPThreshold[1];
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
** Created Date:            2017-04-06
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
** Created Date:            2017-04-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT32S __menuItemOnKey (MENU_ITEM_INFO *pmiiThis, INT16U usLen, void *pvData)
{
    INT32U         *puiKeyCode;    
    FP32            fpRtn;
    char            scParamFmt[32] = {0};
    INT32U          uiX, uiY;
    INT8U           ucErr;
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
    *  ............
    */
    uiX = pmiiThis->ucX + strlen(pmiiThis->pmiib->pcTitle) * FONT_XSIZE8;
    uiY = pmiiThis->ucY;
    /*
     *  参数过滤
     */
    if (NULL == pmiiThis) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == pvData) {
        return (-SYS_PARA_ERR);
    }
    puiKeyCode = pvData;
    ucErr = inputFloat(puiKeyCode[0], pmiiThis, &fpRtn);
    if (INPUT_UNCOMPLETED == ucErr) {
        return SYS_OK;
    }
    if ((INPUT_COMPLETED == ucErr) &&                                   /*  参数输入完成                */
        ((fpRtn > 0.0f) &&
        (fpRtn <= 99.9f))) {                                            /*  合理数值                    */
        GdiDevInfo.fpDeltaPThreshold[1] = fpRtn;
        if (dsSaveParam(&GdiDevInfo) < 0) {                             /*  参数保存失败                */
            dsRecoverParam(&GdiDevInfo);
        } else {
            ;
        };    
    } else if (INPUT_QUIT == ucErr) {                                   /*  退出输入                    */                              
        ;
    } else if (INPUT_UNREASONABLE == ucErr) {                           /*  输入非法                    */
        ;
    } else {                                                            /*  参数未完成输入              */
        ;
    }
    pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, scParamFmt);
    guiRectangleFill(uiX, uiY, GUI_LCM_XMAX, uiY + FONT_YSIZE16, 0);
    guiPrintf(uiX, uiY, 1, "%s", scParamFmt);
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
** Created Date:            2017-04-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv)
{
    FP32 fpPressureRange;
    INT32S siErr = 0;     
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
    fpPressureRange = *((FP32 *)pmiiThis->pvPara);
    fpPressureRange += 0.05;                                            /*  小数四舍五入                */
    siErr = (INT32S)fpPressureRange;
    //sprintf(pvRsv, ":%-1.2fMPa", fpPressureRange);
    sprintf(pvRsv, ":%2d.%01dMPa", siErr, (INT32U)((fpPressureRange * 10.0) - siErr * 10.0));  
    return SYS_OK;
}

/*********************************************************************************************************
  中压->高压切换压差阈值菜单项定义
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibMidPDeltaThreshold = {                 /*  菜单项信息                  */
    "中压阈值",
    (MENU_ITEM_FUNC *)&GmifMidPDeltaThreshold,
    0x140E
};

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
