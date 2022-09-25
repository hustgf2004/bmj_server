/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tp_UpgradeBegin_cfg.h
** Latest modified Date:    2014-08-25
** Latest Version:          1.0
** Descriptions:            端口驱动配置文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2014-08-25
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
#ifndef __TP_UPGRADEBEGIN_CFG_H
#define __TP_UPGRADEBEGIN_CFG_H

/*********************************************************************************************************
  引入的头文件
*********************************************************************************************************/
#include    "..\..\..\config.h"
#include    ".\tp_UpgradeBegin.h"


#ifndef __UPGRADE_PAGE_SIZE
#define __UPGRADE_PAGE_SIZE     (1 * 512)
#endif

#if     __UPGRADE_PAGE_SIZE % 512 != 0
	#error  "__UPGRADE_PAGE_SIZE is must multiple of 512"
#endif

#if     __UPGRADE_PAGE_SIZE > 4096
	#error  "__UPGRADE_PAGE_SIZE is must less than 4096"
#endif

#define __UPGRADE_OK                0x00                                /*  升级程序校验通过            */
#define __UPGRADE_PRO_NOMATCH_ERR   0x01                                /*  升级程序项目不匹配          */
#define __UPGRADE_PRO_VERLOW_ERR    0x02                                /*  升级程序版本太低            */
#define __UPGRADE_PRO_TOOLONG_ERR   0x03                                /*  升级程序长度超长            */
#define __UPGRADE_PRO_BEGIN_ERR     0x04                                /*  升级程序启动失败            */
#define __UPGRADE_PRO_BEING_ERR     0x05                                /*  升级程序进行中              */


#define __UPGRADE_PRO_TYPE_ERR      0x06                                /*  升级程序类型错误            */
    /*
     *  程序信息配置，同时需要在Startup.s中作相应修改
     */
#ifdef __EN_PRO                                                  
    #define __DLM_CODE_ID   0x10                                        /*  程序棒下载管理程序类型      */
    #define __USR_CODE_ID   0xFF                                        
#endif

#ifdef __EN_CTRL                                                      
    #define __DLM_CODE_ID   0x11                                        /*  控制器下载管理程序类型      */
    #define __USR_CODE_ID   0x12                                        /*  控制器应用程序类型          */
#endif

#ifdef __EN_SRV
    #define __DLM_CODE_ID   0x13                                        /*  服务器下载管理程序类型      */
    #define __USR_CODE_ID   0x14                                        /*  服务器应用程序类型          */
#endif
    #define __DLM_CODE_LEN  0x1A000 
    #define __USR_CODE_LEN  0x80000
    #define __MAX_CODE_LEN  0x80000 
#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
  添加自己的配置信息
*********************************************************************************************************/

#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */
#endif                                                                  /*  __TP_UPGRADEBEGIN_CFG_H     */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
