/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn  
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Rewash.c
** Latest modified Date:    2022-01-10
** Latest Version:          1.0
** Descriptions:            辅助动作-反冲洗1/2
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2022-01-10
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
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiiThis, INT32U uiKeyCode);
static INT32S __menuItemParamFmt(MENU_ITEM_INFO *pmiiThis, void *pvRsv);

/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/


/*********************************************************************************************************
  内部使用变量
*********************************************************************************************************/



/*********************************************************************************************************
** Function name:           menuItemCreate
** Descriptions:            创建菜单项
** input parameters:        pmiiThis    菜单项信息
** output parameters:       none
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiiThis)
{
    pmiiThis->pvPara = (void *)&GpuiValveTbl[FILTRATE_1];
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
    INT32S      siErr;
    
    /*
     *  参数过滤
     */
    if (NULL == pmiiThis) {
        return (-SYS_PARA_ERR);
    } 
#if 0    
    if (GpuiKeyTbl[KEY_AUX_LEFT] == uiKeyCode) {                    /*  辅助左键                    */
        Gds.uiValveStatus |= GpuiValveTbl[FILTRATE_1];
    } else if (GpuiKeyTbl[KEY_AUX_RIGHT] == uiKeyCode) {            /*  辅助右键                        */
        Gds.uiValveStatus |= GpuiValveTbl[FILTRATE_2];
    } else {                                                            /*  其他                        */
        Gds.uiValveStatus &= ~(GpuiValveTbl[FILTRATE_1] | GpuiValveTbl[FILTRATE_2]);
    }
#endif
    keyOnMaster(uiKeyCode);
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
    INT32U      uiRecordAddr;
    /*
     *  参数过滤
     */
    if (NULL == pmiiThis) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == pvRsv) {
        return (-SYS_PARA_ERR);
    }
    return SYS_OK;
}

const MENU_ITEM_FUNC GmifRewash = {
    __menuItemCreate,
    __menuItemDel,
    __menuItemOnKey,
    __menuItemParamFmt
};


/*********************************************************************************************************
  辅助动作侧四菜单项定义
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibRewash = {                             /*  菜单项信息                  */
    "反冲洗1  反冲洗2",
    (MENU_ITEM_FUNC *)&GmifRewash,
    0x3205,    
};

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
