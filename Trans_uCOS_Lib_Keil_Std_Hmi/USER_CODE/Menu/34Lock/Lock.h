/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Lock.h
** Latest modified Date:    2021-10-07
** Latest Version:          1.0.0
** Descriptions:            闭锁菜单页头文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2021-10-07
** Version:                 1.0.0
** Descriptions:            The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#ifndef __LOCK_H
#define __LOCK_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** Function name:           miLockInit
** Descriptions:            闭锁菜单页初始化
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miLockInit(void);

/*********************************************************************************************************
** Function name:           miLockDel
** Descriptions:            闭锁菜单页卸载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miLockDel(void);

extern const MENU_ITEM_INFO_BASE __GmiibLock;
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __LOCK_H                    */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
