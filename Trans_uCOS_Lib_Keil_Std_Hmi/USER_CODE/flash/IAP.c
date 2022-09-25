#include "main.h"

/* 
 *  定义CCLK值大小，单位为KHz 
 */
#define  IAP_FCCLK            (48000)
#define  IAP_ENTER_ADR        0x7FFFFFF1                                /*  IAP入口地址定义             */

/*
 *  定义函数指针  
 */
INT32U  paramIn[8];                                                     /*  IAP入口参数缓冲区           */
INT32U  paramOut[8];                                                    /*  IAP出口参数缓冲区           */

/*********************************************************************************************************
** Function name:       sysSectorPrepare
** Descriptions:        IAP操作扇区选择，命令代码50
** input parameters:    sec1:           起始扇区
**                      sec2:           终止扇区
** output parameters:   paramOut[0]:    IAP操作状态码,IAP返回值     
** Returned value:      paramOut[0]:    IAP操作状态码,IAP返回值                     
*********************************************************************************************************/
INT32U  iapSectorPrepare (INT8U sec1, INT8U sec2)
{     
    paramIn[0] = IAP_PREPARE;                                           /*  设置命令字                  */
    paramIn[1] = sec1;                                                  /*  设置参数                    */
    paramIn[2] = sec2;                            
    IAP_Entry(paramIn, paramOut);                                       /*  调用IAP服务程序             */
   
    return (paramOut[0]);                                               /*  返回状态码                  */
}

/*********************************************************************************************************
** Function name:       ramCopy
** Descriptions:        复制RAM的数据到FLASH，命令代码51
** input parameters:    dst:            目标地址，即FLASH起始地址。以512字节为分界
**                      src:            源地址，即RAM地址。地址必须字对齐
**                      no:             复制字节个数，为512/1024/4096/8192
** output parameters:   paramOut[0]:    IAP操作状态码,IAP返回值     
** Returned value:      paramOut[0]:    IAP操作状态码,IAP返回值                     
*********************************************************************************************************/
INT32U  iapRamToFlash (INT32U dst, INT32U src, INT32U no)
{  
    paramIn[0] = IAP_RAMTOFLASH;                                        /*  设置命令字                  */
    paramIn[1] = dst;                                                   /*  设置参数                    */
    paramIn[2] = src;
    paramIn[3] = no;
    paramIn[4] = IAP_FCCLK;
    IAP_Entry(paramIn, paramOut);                                       /*  调用IAP服务程序             */
    
    return (paramOut[0]);                                               /*  返回状态码                  */
}

/*********************************************************************************************************
** Function name:       sysSectorErase
** Descriptions:        扇区擦除，命令代码52
** input parameters:    sec1            起始扇区
**                      sec2            终止扇区92
** output parameters:   paramOut[0]:    IAP操作状态码,IAP返回值
** Returned value:      paramOut[0]:    IAP操作状态码,IAP返回值                     
*********************************************************************************************************/
INT32U  iapSectorErase (INT8U sec1, INT8U sec2)
{  
    paramIn[0] = IAP_ERASESECTOR;                                       /*  设置命令字                  */
    paramIn[1] = sec1;                                                  /*  设置参数                    */
    paramIn[2] = sec2;
    paramIn[3] = IAP_FCCLK;
    IAP_Entry(paramIn, paramOut);                                       /*  调用IAP服务程序             */
   
    return (paramOut[0]);                                               /*  返回状态码                  */
}

/*********************************************************************************************************
** Function name:       blankChk
** Descriptions:        扇区查空，命令代码53
** input parameters:    sec1:           起始扇区
**                      sec2:           终止扇区92
** output parameters:   paramOut[0]:    IAP操作状态码,IAP返回值
** Returned value:      paramOut[0]:    IAP操作状态码,IAP返回值                     
*********************************************************************************************************/
INT32U  iapBlankChk (INT8U sec1, INT8U sec2)
{  
    paramIn[0] = IAP_BLANKCHK;                                          /*  设置命令字                  */
    paramIn[1] = sec1;                                                  /*  设置参数                    */
    paramIn[2] = sec2;
    IAP_Entry(paramIn, paramOut);                                       /*  调用IAP服务程序             */

    return (paramOut[0]);                                               /*  返回状态码                  */
}

/*********************************************************************************************************
** Function name:       parIdRead
** Descriptions:        扇区查空，命令代码54
** input parameters:    无
** output parameters:   paramOut[0]:    IAP操作状态码,IAP返回值
** Returned value:      paramOut[0]:    IAP操作状态码,IAP返回值                     
*********************************************************************************************************/
INT32U  iapParIdRead (void)
{  
    paramIn[0] = IAP_READPARTID;                                        /*  设置命令字                  */
    IAP_Entry(paramIn, paramOut);                                       /*  调用IAP服务程序             */

    return (paramOut[1]);                                               /*  返回状态码                  */
}

/*********************************************************************************************************
** Function name:       codeIdBoot
** Descriptions:        扇区查空，命令代码55
** input parameters:    无
** output parameters:   paramOut[0]:    IAP操作状态码,IAP返回值
** Returned value:      paramOut[0]:    IAP操作状态码,IAP返回值                     
*********************************************************************************************************/
INT32U  iapCodeIdBoot (void)
{  
    paramIn[0] = IAP_BOOTCODEID;                                        /*  设置命令字                  */
    IAP_Entry(paramIn, paramOut);                                       /*  调用IAP服务程序             */

    return (paramOut[1]);                                               /*  返回状态码                  */
}

/*********************************************************************************************************
** Function name:       dataCompare
** Descriptions:        校验数据，命令代码56
** input parameters:    dst:            目标地址，即RAM/FLASH起始地址。地址必须字对齐
**                      src:            源地址，即FLASH/RAM地址。地址必须字对齐
**                      no:             复制字节个数，必须能被4整除
** output parameters:   paramOut[0]:    IAP操作状态码,IAP返回值
** Returned value:      paramOut[0]:    IAP操作状态码,IAP返回值                     
*********************************************************************************************************/
INT32U  iapDataCompare (INT32U dst, INT32U src, INT32U no)
{  
    paramIn[0] = IAP_COMPARE;                                           /*  设置命令字                  */
    paramIn[1] = dst;                                                   /*  设置参数                    */
    paramIn[2] = src;
    paramIn[3] = no;
    IAP_Entry(paramIn, paramOut);                                       /*  调用IAP服务程序             */

    return (paramOut[0]);                                               /*  返回状态码                  */
}
