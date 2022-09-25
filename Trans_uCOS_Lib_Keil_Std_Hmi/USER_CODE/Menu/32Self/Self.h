/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Self.h
** Latest modified Date:    2021-10-03
** Latest Version:          1.0.0
** Descriptions:            自控菜单页头文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2021-10-03
** Version:                 1.0.0
** Descriptions:            The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#ifndef __SELF_H
#define __SELF_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** Function name:           miSelfInit
** Descriptions:            自控菜单页初始化
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miSelfInit(void);

/*********************************************************************************************************
** Function name:           miSelfDel
** Descriptions:            自控菜单页卸载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miSelfDel(void);

/*********************************************************************************************************
** Function name:           keyOnMaster
** Descriptions:            主控界面按键响应
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void keyOnMaster(INT32U uiKeyCode);

extern const MENU_ITEM_INFO_BASE __GmiibSelf;
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __SELF_H                    */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
