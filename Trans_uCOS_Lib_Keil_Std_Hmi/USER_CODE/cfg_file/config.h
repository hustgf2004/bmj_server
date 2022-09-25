/****************************************Copyright (c)****************************************************
**                         Guangzhou ZHIYUAN electronics Co.,LTD.                               
**                                     
**                               http://www.embedtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           config.h
** Last modified Date:  2004-09-17
** Last Version:        1.0
** Descriptions:        User Configurable File
**
**--------------------------------------------------------------------------------------------------------
** Created By:          Chenmingji
** Created date:        2004-09-17
** Version: 1.0
** Descriptions:        First version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*********************************************************************************************************/
#ifndef __CONFIG_H
#define __CONFIG_H

#ifdef  __cplusplus
extern "C" {
#endif
/*********************************************************************************************************
  应用程序配置
  Application Program Configurations
*********************************************************************************************************/
#include    "..\..\SYS_CODE\Head\system.h" 
#include    "..\..\USER_CODE\cfg_file\SysTools\sys_tools_cfg.h"

#include    "..\AnyPort\tpPorts\tpPorts.h"
#include    "..\Menu\afxMenu.h"
#include    "..\Menu\MenuPage_target.h"
    
/*********************************************************************************************************
  本例子的配置,不可以更改
  Configuration of the example，Don't Change Please!
*********************************************************************************************************/
#if 0
#define FOSC            11059200
#define FCCLK           (4 * FOSC)
#define FCCO            (4 * FCCLK)
#define FPCLK           ((FCCLK / 4) * 1)

#else
#define FOSC            12000000
#define FCCLK           (4 * FOSC)
#define FCCO            (4 * FCCLK)
#define FPCLK           ((FCCLK / 4) * 1)
#endif

#ifdef __cplusplus
    }
#endif                                                                  /*  __cplusplus                 */
#endif                                                                  /*  __CONFIG_H                  */ 
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
