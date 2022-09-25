/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               KeyLock.h
** Latest modified Date:    2021-12-26
** Latest Version:          1.0.0
** Descriptions:            按键闭锁菜单页头文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2021-12-26
** Version:                 1.0.0
** Descriptions:            The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#ifndef __KEY_LOCK_H
#define __KEY_LOCK_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** Function name:           miKeyLockInit
** Descriptions:            按键闭锁菜单初始化
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miKeyLockInit(void);

/*********************************************************************************************************
** Function name:           miKeyLockDel
** Descriptions:            按键闭锁菜单卸载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miKeyLockDel(void);

extern const MENU_ITEM_INFO_BASE __GmiibKeyLock;                        /*  菜单项信息                  */
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __KEY_LOCK_H                */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
