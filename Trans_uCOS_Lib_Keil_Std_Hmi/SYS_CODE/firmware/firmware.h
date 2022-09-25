/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               firmware.h
** Last modified Date:      2010-12-14
** Last Version:            1.0
** Descriptions:
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
********************************************************************************************************/
#ifndef __FIRMWARE_H
#define __FIRMWARE_H
#ifdef __cplusplus
    extern "C" {
#endif

#define __PRJ_BOOT_VER      0x14082510                                  
                                                                        /*                                                                     
                                                                         *  Boot版本为 V1.0
                                                                         *      1、初始版本
                                                                         */

//extern INT8U  sysSectorPrepare(INT8U ucStart, INT8U ucEnd);
//extern INT32U sysSectorErase(INT8U ucStart, INT8U ucEnd);
/*********************************************************************************************************
** Function name:           sysBootVersionGet
** Descriptions:            获取固件版本号
** input parameters:        none
** output parameters:       none
** Returned value:          读到的数据
*********************************************************************************************************/
extern INT32U  sysBootVersionGet(void);

/*********************************************************************************************************
** Function name:           sysInit
** Descriptions:            系统参数初始化
** input parameters:        uiFosc:     系统外部时钟
**                          uiFcclk:    系统内核时钟
**                          uiFcco:     倍频时钟
**                          uiFpclk:    外设时钟
**                          uiOsticks:  系统节拍
** output parameters:       none
** Returned value:          读到的数据
*********************************************************************************************************/
extern void sysInit (INT32U uiFosc, INT32U uiFcclk, INT32U uiFcco, INT32U uiFpclk, INT32U uiOsticks);

/*********************************************************************************************************
** Function name:           sysUpgradeBegin
** Descriptions:            开始升级
** input parameters:        pucBuf: 升级数据缓存基址
**                          uiLength：缓存大小(>=512B)
** output parameters:       none
** Returned value:          >=0:    编程起始编号
**                          负数:   失败
*********************************************************************************************************/
extern INT32S sysUpgradeBegin(INT8U* pucBuf, INT32U uiLength);

/*********************************************************************************************************
** Function name:           sysUpgradeDataWrite
** Descriptions:            编程升级数据
** input parameters:        uiBlockIndex: 数据块索引，从零开始, 每编程1KB数据累加
** output parameters:       none
** Returned value:          绝对值参考 "IAP.h"
*********************************************************************************************************/
extern INT32S sysUpgradeDataWrite(unsigned int uiBlockIndex);

/*********************************************************************************************************
** Function name:           sysUpgradeEnd
** Descriptions:            升级结束
** input parameters:        none
** output parameters:       none
** Returned value:          绝对值参考 "IAP.h"
*********************************************************************************************************/
extern INT32S sysUpgradeEnd(void);

/*********************************************************************************************************
** Function name:           GetSoftPara
** Descriptions:            返回程序头参数
** input parameters:        none
** output parameters:       none
** Returned value:          puiPara[0]: 当前程序版本号
**                          puiPara[1]: 当前程序类别标志    
*********************************************************************************************************/
extern void sysSoftParaGet(INT32U* puiPara);

/*********************************************************************************************************
** Function name:           sysUpgradeBeginUsr
** Descriptions:            开始升级
** input parameters:        none
** output parameters:       none
** Returned value:          非空指针:     升级缓冲区
*********************************************************************************************************/
extern sysUpgradeBeginUsr(INT8U* pucBuf, INT32U uiLength);

/*********************************************************************************************************
** Function name:           sysUpgradeDataWriteUsr
** Descriptions:            编程升级数据
** input parameters:        uiBlockIndex: 数据块索引，从零开始, 每编程1KB数据累加
** output parameters:       none
** Returned value:          绝对值参考 "IAP.h"
*********************************************************************************************************/
extern INT32S sysUpgradeDataWriteUsr(unsigned int uiBlockIndex);

/*********************************************************************************************************
** Function name:           sysUpgradeEndUsr
** Descriptions:            升级结束
** input parameters:        none
** output parameters:       none
** Returned value:          绝对值参考 "IAP.h"
*********************************************************************************************************/
extern INT32S sysUpgradeEndUsr(void);

/*********************************************************************************************************
** Function name:           sysSoftParaGetUsr
** Descriptions:            返回程序头参数
** input parameters:        none
** output parameters:       none
** Returned value:          puiPara[0]: 当前程序版本号
**                          puiPara[1]: 当前程序类别标志  
**                          puiPara[2]: 当前程序升级成功有效长度   
*********************************************************************************************************/
extern void sysSoftParaGetUsr(INT32U* puiPara);

/*********************************************************************************************************
** Function name:           sysCodeEraseEx
** Descriptions:            擦除应用程序有效标志
** input parameters:        none
** output parameters:       none
** Returned value:          固件版本
*********************************************************************************************************/
extern void sysCodeEraseUsr(void);

/*********************************************************************************************************
** Function name:           sysUpgradeBeginEx
** Descriptions:            开始升级
** input parameters:        none
** output parameters:       none
** Returned value:          非空指针:     升级缓冲区
*********************************************************************************************************/
extern sysUpgradeBeginEx(INT8U* pucBuf, INT32U uiLength);

/*********************************************************************************************************
** Function name:           sysUpgradeDataWriteEx
** Descriptions:            编程升级数据
** input parameters:        uiBlockIndex: 数据块索引，从零开始, 每编程1KB数据累加
** output parameters:       none
** Returned value:          绝对值参考 "IAP.h"
*********************************************************************************************************/
extern INT32S sysUpgradeDataWriteEx(unsigned int uiBlockIndex);

/*********************************************************************************************************
** Function name:           sysUpgradeEndEx
** Descriptions:            升级结束
** input parameters:        none
** output parameters:       none
** Returned value:          绝对值参考 "IAP.h"
*********************************************************************************************************/
extern INT32S sysUpgradeEndEx(void);

/*********************************************************************************************************
** Function name:           GetSoltParaEx
** Descriptions:            返回程序头参数
** input parameters:        none
** output parameters:       none
** Returned value:          puiPara[0]: 当前程序版本号
**                          puiPara[1]: 当前程序类别标志  
**                          puiPara[1]: 当前程序升级成功有效长度   
*********************************************************************************************************/
extern void sysSoftParaGetEx(INT32U* puiPara);

/*********************************************************************************************************
** Function name:           sysCodeEraseEx
** Descriptions:            擦除程序有效标志
** input parameters:        none
** output parameters:       none
** Returned value:          固件版本
*********************************************************************************************************/
extern void sysCodeEraseEx(void);

/*********************************************************************************************************
** Function name:       WordProgram
** Descriptions:        字编程
** input parameters:    地址，数据
** output parameters:   none
** Returned value:      是否成功               
*********************************************************************************************************/
extern INT32S sysWordProgramEx(uint32 Addr, uint16 Data);
 
/*********************************************************************************************************
** Function name:       SectorErase
** Descriptions:        扇区擦除
** input parameters:    扇区号
** output parameters:   none
** Returned value:      是否成功               
*********************************************************************************************************/                     
extern INT32S sysSectorEraseEx(uint32 Index); 



/*********************************************************************************************************
** Function name:           sysDataAbortIsrSet
** Descriptions:            取数终止向量函数地址设置
** input parameters:        uiAddr:     取数终止向量函数地址
** output parameters:       none
** Returned value:          读到的数据
*********************************************************************************************************/
__inline void sysDataAbortIsrSet(INT32U uiAddr)
{
    extern INT32U uiDataAbortAddr;

    uiDataAbortAddr = uiAddr;
}

/*********************************************************************************************************
** Function name:           sysPrefetchIsrSet
** Descriptions:            预取终止向量函数地址设置
** input parameters:        uiAddr:     预取终止向量函数地址
** output parameters:       none
** Returned value:          读到的数据
*********************************************************************************************************/
__inline void sysPrefetchIsrSet(INT32U uiAddr)
{
    extern INT32U uiPrefetchAddr;

    uiPrefetchAddr = uiAddr;
}

/*********************************************************************************************************
** Function name:           sysUndefinedsrSet
** Descriptions:            未定义指令向量函数地址设置
** input parameters:        uiAddr:     未定义指令向量函数地址
** output parameters:       none
** Returned value:          读到的数据
*********************************************************************************************************/
__inline void sysUndefinedsrSet(INT32U uiAddr)
{
    extern INT32U uiUndefinedAddr;

    uiUndefinedAddr = uiAddr;
}

#ifdef __cplusplus
    }
#endif

#endif
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
