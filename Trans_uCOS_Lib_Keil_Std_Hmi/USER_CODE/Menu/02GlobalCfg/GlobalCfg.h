/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn                              
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               GlobalCfg.h
** Latest modified Date:    2021-12-27
** Latest Version:          1.0
** Descriptions:            整体设置菜单头文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2021-12-27
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
#ifndef __GLOBAL_CFG_H
#define __GLOBAL_CFG_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */
/*********************************************************************************************************
** Function name:           miGlobalCfgInit
** Descriptions:            整体设置菜单项初始化
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miGlobalCfgInit (void);

/*********************************************************************************************************
** Function name:           miGlobalCfgDel
** Descriptions:            整体设置菜单项卸载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miGlobalCfgDel (void);

#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __GLOBAL_CFG_H              */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
