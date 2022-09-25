/****************************************Copyright (c)****************************************************
**                            
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               PressureSnr.c
** Latest modified Date:    2017-04-03
** Latest Version:          1.0
** Descriptions:            压力传感器设置菜单
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

#include    "..\..\main.h"   
#include    ".\01LowPressureEn\LowPressureEn.h"
#include    ".\02LowPressureRange\LowPressureRange.h"
#include    ".\03MidPressureEn\MidPressureEn.h"
#include    ".\04MidPressureRange\MidPressureRange.h"
#include    ".\05HighPressureEn\HighPressureEn.h"
#include    ".\06HighPressureRange\HighPressureRange.h"
#include    ".\07ChargingPressureEn\ChargingPressureEn.h"
#include    ".\08ChargingPressureRange\ChargingPressureRange.h"
#include    ".\09LowPressureSample\LowPressureSample.h"
#include    ".\10MidPressureSample\MidPressureSample.h"
#include    ".\11HighPressureSample\HighPressureSample.h"
#include    ".\12ChargingPressureSample\ChargingPressureSample.h"
#include    ".\13LowPDeltaThreshold\LowPDeltaThreshold.h"
#include    ".\14MidPDeltaThreshold\MidPDeltaThreshold.h"
#include    ".\15HighPDeltaThreshold\HighPDeltaThreshold.h"
#include    ".\16ClosePDeltaThreshold\ClosePDeltaThreshold.h"
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
const MENU_ITEM_FUNC GmifPressureSnr = {
    __menuItemCreate,
    __menuItemDel,
    __menuItemOnKey,
    __menuItemParamFmt
};
const  char *const __SscEnStr[2] = {"×",      "√"};

INT8U    __SucEnFlag;
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
    INT32S      siErr = 0;
    
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
    *  ............
    */
    if (GdsDevStatus.ucAuthority.ucAuthorityLevel == DEVELOPER_LEVEL) {
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibLowPressureEn); 
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibLowPressureRange);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibLowPDeltaThreshold);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibMidPressureEn); 
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibMidPressureRange);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibMidPDeltaThreshold);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibHighPressureEn);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibHighPressureRange);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibHighPDeltaThreshold);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibChargingPressureEn);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibChargingPressureRange);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibClosePDeltaThreshold);
    }
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibLowPressureSample);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibMidPressureSample);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibHighPressureSample);
        siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibChargingPressureSample);
    
    return siErr;
}

/*********************************************************************************************************
** Function name:           menuItemDel
** Descriptions:            删除菜单项
** input parameters:        pmiiThis    菜单页信息
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

    /*
     *
     */
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
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
    *  ............
    */
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
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
    *  ............
    */
    return SYS_OK;
}

/*********************************************************************************************************
  压力传感器菜单页定义
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibPressureSnr = {                 /*  菜单页信息                  */
    "压力传感器设置",
    (MENU_ITEM_FUNC *)&GmifPressureSnr,
    0x1400
};

/*********************************************************************************************************
** Function name:           miPressureSnrInit
** Descriptions:            压力传感器设置菜单页初始化
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miPressureSnrInit (void)
{ 
    /*
     *  添加菜单页
     */
    miAdd(&__GmiibRoot, &__GmiibPressureSnr);
}
/*********************************************************************************************************
** Function name:           miPressureSnrDel
** Descriptions:            压力传感器设置菜单页卸载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miPressureSnrDel (void)
{ 
    /*
     *  删除菜单页
     */
    miDel(&__GmiibPressureSnr);
}


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
