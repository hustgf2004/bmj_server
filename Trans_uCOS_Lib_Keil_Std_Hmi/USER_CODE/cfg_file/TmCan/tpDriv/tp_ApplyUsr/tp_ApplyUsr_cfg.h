/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tp_ApplyUsr_cfg.h
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
#ifndef __TP_APPLYUSR_CFG_H
#define __TP_APPLYUSR_CFG_H

/*********************************************************************************************************
  引入的头文件
*********************************************************************************************************/
#include    "..\..\..\config.h"
#include    ".\tp_ApplyUsr.h"

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
  添加自己的配置信息
*********************************************************************************************************/


#define __APPLYE_OK                 0x00                                  /*  申请吸程序成功              */
#define __APPLY_PRO_NOMATCH_ERR     0x11                                  /*  申请吸程序项目不匹配        */
#define __APPLY_PRO_VERLOW_ERR      0x12                                  /*  申请吸程序版本太低          */
#define __APPLY_PRO_TOOLONG_ERR     0x13                                  /*  申请吸程序长度超长          */
#define __APPLY_PRO_BEGIN_ERR       0x14                                  /*  启动吸程序失败              */
#define __APPLY_PRO_BEING_ERR       0x15                                  /*  吸程序进行中                */
#define __APPLY_PRO_VALID_ERR       0x16                                  /*  控制器自身程序有效          */ 
#define __APPLY_PRO_TYPE_ERR        0x17                                  /*  吸程序类型错误              */

#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */
#endif                                                                  /*  __TP_APPLYUSR_CFG_H         */

/*********************************************************************************************************
  DEL FILE
*********************************************************************************************************/
