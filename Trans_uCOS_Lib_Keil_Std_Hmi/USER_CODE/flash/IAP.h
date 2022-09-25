/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               iap.h
** Latest modified Date:    2014-12-23
** Latest Version:          1.0
** Descriptions:            iap环境接口
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2014-12-23
** Version:                 1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
*********************************************************************************************************/
#ifndef __IAP_H
#define	__IAP_H
/*
 *  器件ID
 */
#define     __MCU_LPC2109_ID    0x0201FF01                              /*  LPC2109 ID 号               */   
#define     __MCU_LPC2119_ID    0x0201FF12                              /*  LPC2119 ID 号               */   
#define     __MCU_LPC2129_ID    0x0201FF13                              /*  LPC2129 ID 号               */   
#define     __MCU_LPC2114_ID    0x0101FF12                              /*  LPC2114 ID 号               */   
#define     __MCU_LPC2124_ID    0x0101FF13                              /*  LPC2124 ID 号               */   
#define     __MCU_LPC2194_ID    0x0301FF13                              /*  LPC2194 ID 号               */   
#define     __MCU_LPC2292_ID    0x0401FF13                              /*  LPC2292 ID 号               */   
#define     __MCU_LPC2294_ID    0x0501FF13                              /*  LPC2294 ID 号               */   
#define     __MCU_LPC2214_ID    0x0601FF13                              /*  LPC2214 ID 号               */   
#define     __MCU_LPC2212_ID    0x0401FF12                              /*  LPC2212 ID 号               */   

#define     __MCU_LPC2131_ID    0x0002FF01                              /*  LPC2131 ID 号               */   
#define     __MCU_LPC2132_ID    0x0002FF11                              /*  LPC2132 ID 号               */   
#define     __MCU_LPC2134_ID    0x0002FF12                              /*  LPC2134 ID 号               */   
#define     __MCU_LPC2136_ID    0x0002FF23                              /*  LPC2136 ID 号               */   
#define     __MCU_LPC2138_ID    0x0002FF25                              /*  LPC2138 ID 号               */

/* 
 *  定义IAP命令字
 */                                     
#define     IAP_PREPARE                                50               /* 选择扇区                     */
                                                                        /* 【起始扇区号、结束扇区号】   */                    
#define     IAP_RAMTOFLASH                             51               /* 拷贝数据 FLASH目标地址       */
                                                                        /* RAM源地址    【、写入字节数  */
                                                                        /* 系统时钟频率】               */
#define     IAP_ERASESECTOR                            52               /* 擦除扇区    【起始扇区号     */
                                                                        /* 结束扇区号、系统时钟频率】   */
#define     IAP_BLANKCHK                               53               /* 查空扇区    【起始扇区号、   */
                                                                        /* 结束扇区号】                 */
#define     IAP_READPARTID                             54               /* 读器件ID    【无】           */
#define     IAP_BOOTCODEID                             55               /* 读Boot版本号【无】           */
#define     IAP_COMPARE                                56               /* 比较命令    【Flash起始地址  */
                                                                        /* RAM起始地址、需要比较的      */
                                                                        /* 字节数】                     */
/*
 *  定义IAP返回状态字
 */
#define     CMD_SUCCESS                                0
#define     INVALID_COMMAND                            1
#define     SRC_ADDR_ERROR                             2 
#define     DST_ADDR_ERROR                             3
#define     SRC_ADDR_NOT_MAPPED                        4
#define     DST_ADDR_NOT_MAPPED                        5
#define     COUNT_ERROR                                6
#define     INVALID_SECTOR                             7
#define     SECTOR_NOT_BLANK                           8
#define     SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION    9
#define     COMPARE_ERROR                              10
#define     BUSY                                       11
#define     SRC_BUF_NOT_MAPPED                         128


#define IAP_ENTER_ADR   0x7FFFFFF1                                      /* IAP入口地址定义              */
#define IAP_Entry(a, b) ((void (*)())(IAP_ENTER_ADR))(a, b)

/*********************************************************************************************************
** Function name:       sysSectorPrepare
** Descriptions:        IAP操作扇区选择，命令代码50
** input parameters:    sec1:           起始扇区
**                      sec2:           终止扇区
** output parameters:   paramout[0]:    IAP操作状态码,IAP返回值     
** Returned value:      paramout[0]:    IAP操作状态码,IAP返回值                     
*********************************************************************************************************/
extern INT32U  iapSectorPrepare (INT8U sec1, INT8U sec2);

/*********************************************************************************************************
** Function name:       sysRamToFlash
** Descriptions:        复制RAM的数据到FLASH，命令代码51
** input parameters:    dst:            目标地址，即FLASH起始地址。以512字节为分界
**                      src:            源地址，即RAM地址。地址必须字对齐
**                      no:             复制字节个数，为512/1024/4096/8192
** output parameters:   paramout[0]:    IAP操作状态码,IAP返回值     
** Returned value:      paramout[0]:    IAP操作状态码,IAP返回值                     
*********************************************************************************************************/
extern INT32U  iapRamToFlash (INT32U dst, INT32U src, INT32U no);

/*********************************************************************************************************
** Function name:       sysSectorErase
** Descriptions:        扇区擦除，命令代码52
** input parameters:    sec1            起始扇区
**                      sec2            终止扇区92
** output parameters:   paramout[0]:    IAP操作状态码,IAP返回值
** Returned value:      paramout[0]:    IAP操作状态码,IAP返回值                     
*********************************************************************************************************/
extern INT32U  iapSectorErase (INT8U sec1, INT8U sec2);

/*********************************************************************************************************
** Function name:       sysBlankChk
** Descriptions:        扇区查空，命令代码53
** input parameters:    sec1:           起始扇区
**                      sec2:           终止扇区92
** output parameters:   paramout[0]:    IAP操作状态码,IAP返回值
** Returned value:      paramout[0]:    IAP操作状态码,IAP返回值                     
*********************************************************************************************************/
extern INT32U  iapBlankChk (INT8U sec1, INT8U sec2);

/*********************************************************************************************************
** Function name:       sysParIdRead
** Descriptions:        读器件ID，命令代码54
** input parameters:    无
** output parameters:   paramout[0]:    IAP操作状态码,IAP返回值
** Returned value:      paramout[0]:    IAP操作状态码,IAP返回值                     
*********************************************************************************************************/
extern  INT32U  iapParIdRead (void);

/*********************************************************************************************************
** Function name:       sysCodeIdBoot
** Descriptions:        读Boot版本，命令代码55
** input parameters:    无
** output parameters:   paramout[0]:    IAP操作状态码,IAP返回值
** Returned value:      paramout[0]:    IAP操作状态码,IAP返回值                     
*********************************************************************************************************/
extern INT32U  iapCodeIdBoot (void);

/*********************************************************************************************************
** Function name:       sysDataCompare
** Descriptions:        校验数据，命令代码56
** input parameters:    dst:            目标地址，即RAM/FLASH起始地址。地址必须字对齐
**                      src:            源地址，即FLASH/RAM地址。地址必须字对齐
**                      no:             复制字节个数，必须能被4整除
** output parameters:   paramout[0]:    IAP操作状态码,IAP返回值
** Returned value:      paramout[0]:    IAP操作状态码,IAP返回值                     
*********************************************************************************************************/
extern INT32U  iapDataCompare (INT32U dst, INT32U src, INT32U no);
typedef struct __param_flash {
    INT32U  uiParamSector0;                                             /*  参数0扇区                   */
    INT32U  uiParamSector1;                                             /*  参数1扇区                   */
    INT32U  uiParamAddr0;                                               /*  参数0首地址                 */
    INT32U  uiParamAddr1;                                               /*  参数1首地址                 */
    INT32U  uiUsrCodeStartSector;                                       /*  用户程序起始扇区            */
    INT32U  uiUsrCodeEndSector;                                         /*  用户程序结束扇区            */
    INT32U  uiRsvCodeStartSector;                                       /*  升级程序起始扇区            */
    INT32U  uiRsvCodeEndSector;                                         /*  升级程序结束扇区            */
    INT32U  uiRsvCodeSectorSize;                                        /*  升级程序扇区容量            */
    INT32U  uiUsrCodeAddr;                                              /*  用户程序首地址              */
    INT32U  uiRsvCodeAddr;                                              /*  升级程序首地址              */
    INT32U  uiUsrCodeMaxLen;
} __PARAM_FLASH, *__PPARAM_FLASH;

#endif

