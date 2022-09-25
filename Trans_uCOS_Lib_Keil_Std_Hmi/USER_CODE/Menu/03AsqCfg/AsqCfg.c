/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn                              
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               AsqCfg.c
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

#include    "..\..\main.h"   
#include    ".\01AsqWarnTime\AsqWarnTime.h"
#include    ".\02FlipOutStartTime\FlipOutStartTime.h"
#include    ".\03FlipOutActTime\FlipOutActTime.h"
#include    ".\04PusherOutStartTime\PusherOutStartTime.h"
#include    ".\05PusherOutActTime\PusherOutActTime.h"
#include    ".\06FlipInStartTime\FlipInStartTime.h"
#include    ".\07FlipInActTime\FlipInActTime.h"
#include    ".\08PusherInStartTime\PusherInStartTime.h"
#include    ".\09PusherInActTime\PusherInActTime.h"

#include    ".\10LiftOutStartTime\LiftOutStartTime.h"
#include    ".\11LiftOutActTime\LiftOutActTime.h"
#include    ".\12LiftInStartTime\LiftInStartTime.h"
#include    ".\13LiftInActTime\LiftInActTime.h"
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
const MENU_ITEM_FUNC GmifAsqCfg = {
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
    INT32S      siErr = 0;
    
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
    *  ............
    */
    //if (GdsDevStatus.ucAuthorityLevel == DEVELOPER_LEVEL) {
        //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibPressureChargingEn); 
        //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibAlarmType);
        //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibLowLimit); 
        //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibUpperLimit);
        //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibPressureRange);
        //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibMidPCheckThreshold);
        //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibRamp);
        //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibTripleLineEn);
        
    //}
    siErr = miAdd(pmiiThis->pmiib, (void *)&__GmiibAsqWarnTime);  
    //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibFlipOutStartTime);
    //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibFlipOutActTime);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibLiftOutStartTime);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibLiftOutActTime);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibPusherOutStartTime);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibPusherOutActTime);
    //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibFlipInStartTime);
    //siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibFlipInActTime);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibLiftInStartTime);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibLiftInActTime);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibPusherInStartTime);
    siErr += miAdd(pmiiThis->pmiib, (void *)&__GmiibPusherInActTime);

    return siErr;
}

/*********************************************************************************************************
** Function name:           menuItemDel
** Descriptions:            删除菜单项
** input parameters:        pmiiThis    菜单页信息
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
** Function name:           menuItemOnKey
** Descriptions:            菜单项按键响应函数
** input parameters:        pmiiThis    菜单页信息
**                          usLen       待处理数据长度
**                          pvData      待处理数据指针
** output parameters:       none
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考sys_if.h
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
  自动移架参数菜单页定义
*********************************************************************************************************/
static const MENU_ITEM_INFO_BASE __GmiibAsqCfg = {            /*  菜单页信息                  */
    "自动移架",
    (MENU_ITEM_FUNC *)&GmifAsqCfg,
    0x0300
};

/*********************************************************************************************************
** Function name:           miAsqCfgInit
** Descriptions:            自动移架设置菜单页初始化
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miAsqCfgInit (void)
{ 
    /*
     *  添加菜单页
     */
    miAdd(&__GmiibRoot, &__GmiibAsqCfg);
}
/*********************************************************************************************************
** Function name:           miAsqCfqDel
** Descriptions:            自动移架设置菜单页卸载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miAsqCfgDel (void)
{ 
    /*
     *  删除菜单页
     */
    miDel(&__GmiibAsqCfg);
}


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
