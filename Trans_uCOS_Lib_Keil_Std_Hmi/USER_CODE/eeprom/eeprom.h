/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               eeprom.h
** Latest modified Date:    2017-05-30
** Latest Version:          1.0
** Descriptions:            eeprom操作接口文件 
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2017-05-30
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
#ifndef __EEPROM_H
#define __EEPROM_H    

/*********************************************************************************************************
** Function name:       write_eeprom
** Descriptions:        写EEPROM
** input parameters:    usSubAddr   : 从机内部子地址
**                      ucSubAddrLen: 从机内部子地址长度
**                      pucRet      : 指向返回数据存储位置的指针
**                      ulSize      : 数据长度
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
extern INT8U eepromRead (INT16U usSubAddr, INT8U *pucRet, INT32U ulSize);

/*********************************************************************************************************
** Function name:       read_eeprom
** Descriptions:        读EEPROM
** input parameters:    usSubAddr   : 从机内部子地址
**                      ucSubAddrLen: 从机内部子地址长度
**                      pucRet      : 指向返回数据存储位置的指针
**                      ulSize      : 数据长度
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
extern INT8U eepromWrite (INT16U usSubAddr, INT8U *pucRet, INT32U ulSize);

#endif                                                                  /*  __EEPROM_H                  */

