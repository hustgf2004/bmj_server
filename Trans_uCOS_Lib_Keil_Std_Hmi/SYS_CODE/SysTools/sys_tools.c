/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               sys_tools.c
** Latest modified Date:    2014-08-25
** Latest Version:          1.00
** Descriptions:            系统工具函数
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
#include    "..\..\USER_CODE\cfg_file\config.h"

/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/
#if 0
static unsigned int __GuisysHeapBuf[SYS_HEAP_SIZE / sizeof(int)];       /*  堆所需要的空间              */
#endif                                                                  /*  0                           */

/*********************************************************************************************************
** Function name:           sysIfInit
** Descriptions:            接口初始化
** input parameters:        none
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_if.h
** Created by:              
** Created date:            2010-12-13
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
INT32S sysIfInit (void)
{
#if 0
    extern INT32U *pulDmaHeap;

    if (__sysIfInit(__GuisysHeapBuf, SYS_HEAP_SIZE, (void*)&__GDrivHooks, sizeof(DRIVER_HOOKS))< 0) {    
        return -SYS_NOT_OK;
    }
#else
    void *pvTmp;
    
    sysIrqDisable();
    pvTmp = malloc(SYS_HEAP_SIZE);
    sysIrqEnable();

    if (__sysIfInit(pvTmp, SYS_HEAP_SIZE, (void*)&GdhDrvHooksTbl, sizeof(DRIVER_HOOKS)) < 0) {
        sysIrqDisable();
        free(pvTmp);
        sysIrqEnable();
        return -SYS_NOT_OK;
    }
#endif                                                                  /*  0                           */

    return SYS_OK;
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
