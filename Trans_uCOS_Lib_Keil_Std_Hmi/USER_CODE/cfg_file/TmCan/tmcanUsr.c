/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tmcan_usr.c
** Latest modified Date:    2014-08-25
** Latest Version:          1.0
** Descriptions:            
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2014-08-25
** Version:                 1.0
** Descriptions:            The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#include "..\config.h"

/*********************************************************************************************************
** Function name:           tmUsrInit
** Descriptions:            用户TMCan初始化
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              
** Created Date:            2014-08-25
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
extern void tmTick(void);
void tmUsrInit (void)
{
    
    OSTimeTickHookSet(tmTick);

    /*
     *  添加功能端口取驱动
     */     
    if (ioInportLong(__EN_UPGRADE_FLAG0) != 0x87654321) {
        
        tpUpgradeBeginInit();
        tpUpDataDelInit();
    }
    tpUpBackMaxNumInit();
    tpHandShakeInit();
    /*
     *  添加通讯驱动
     */
    tmCanDrivInit();
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
