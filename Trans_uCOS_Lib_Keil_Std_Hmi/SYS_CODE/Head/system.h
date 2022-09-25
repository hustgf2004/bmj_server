/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               system.h
** Latest modified Date:    2010-12-13
** Latest Version:          1.0
** Descriptions:            环境接口配置文件，抽取原先的config.h文件中关于 
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2010-12-13
** Version:                 1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
*********************************************************************************************************/


#ifndef __SYSTEM_H 
#define __SYSTEM_H
#ifdef  __cplusplus
extern "C" {
#endif

#ifndef TRUE
#define TRUE  1
#endif                                                                  /*  TRUE                        */

#ifndef FALSE
#define FALSE 0
#endif                                                                  /*  FALSE                       */

typedef unsigned char  uint8;                                           /*  无符号8位整型变量           */
typedef signed   char  int8;                                            /*  有符号8位整型变量           */
typedef unsigned short uint16;                                          /*  无符号16位整型变量          */
typedef signed   short int16;                                           /*  有符号16位整型变量          */
typedef unsigned int   uint32;                                          /*  无符号32位整型变量          */
typedef signed   int   int32;                                           /*  有符号32位整型变量          */
typedef float          fp32;                                            /*  单精度浮点数（32位长度）    */
typedef double         fp64;                                            /*  双精度浮点数（64位长度）    */

typedef unsigned char  INT8U;                                           /*  无符号8位整型变量           */
typedef signed   char  INT8S;                                           /*  有符号8位整型变量           */
typedef unsigned short INT16U;                                          /*  无符号16位整型变量          */
typedef signed   short INT16S;                                          /*  有符号16位整型变量          */
typedef unsigned int   INT32U;                                          /*  无符号32位整型变量          */
typedef signed   int   INT32S;                                          /*  有符号32位整型变量          */
typedef long long      INT64S;                                          /*  有符号64位整型变量          */
typedef float          FP32;                                            /*  单精度浮点数（32位长度）    */
typedef double         FP64;                                            /*  双精度浮点数（64位长度）    */

typedef unsigned long long      INT64U;                                 /*  无符号64位整型变量          */

/*********************************************************************************************************
  uC/OS-II specital code
  uC/OS-II的特殊代码
*********************************************************************************************************/
#include    "..\uCOS-II\Includes.h"


/*********************************************************************************************************
  ARM的特殊代码
  ARM specital code
*********************************************************************************************************/
#include    "..\Head\target.h"
#include    "..\Head\LPC2200.h"

#include    "..\firmware\firmware.h"
#include    "..\Head\vicControl.h"


#include    "..\..\SYS_CODE\sysIf\sys_If.h"
#include    "..\DataStructure\List\List.h"
#include    "..\DataStructure\Tree\Tree.h"

#include    "..\uCOS-II\uCOS_II_add.h"
#include    "..\DrvLib\Driver2200.h"
   
#include    "..\SysTools\IO\io.h"
#include    "..\OsHeap\OsHeap.h"

//#include    "..\ZLG_GUI\GUI_CONFIG.H"
#include    "..\ZLG_GUI\GUI.H" 

#include    "..\AnyPort\tpCommon.h"

//#include    "..\Modbus\Modbus_Uart\ModbusUser.h"
//#include    "..\Modbus\Modbus_Uart\RequestFun.h"
//#include    "..\Modbus\Modbus_Uart\MB_USER_Data.h"
/*********************************************************************************************************
  应用程序配置
  Application Program Configurations
*********************************************************************************************************/
#include    <stdio.h>
#include    <ctype.h>
#include    <stdlib.h>
#include    <stdarg.h>
#include    <setjmp.h>
#include    <rt_sys.h>
#include    <rt_misc.h>

#ifdef __cplusplus
    }
#endif                                                                  /*  __cplusplus                 */
#endif                                                                  /*  __SYSTEM_H                  */ 
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
