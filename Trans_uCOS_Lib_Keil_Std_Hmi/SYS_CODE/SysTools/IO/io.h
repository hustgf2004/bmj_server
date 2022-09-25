/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               io.h
** Latest modified Date:    2010-12-14
** Latest Version:          1.0
** Descriptions:            访问I/O函数集
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2010-12-14
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
#ifndef __IO_H
#define __IO_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
  下面为函数声明
*********************************************************************************************************/

/*********************************************************************************************************
** Function name:           ioInportByte
** Descriptions:            从I/O端口输入一个字节(8位)
** input parameters:        ulPort: 端口地址
** output parameters:       none
** Returned value:          读到的数据
*********************************************************************************************************/
__inline INT8U ioInportByte(unsigned long ulPort)
{
    volatile INT8U *pucAddr;

    pucAddr = (INT8U *)ulPort;
    return *pucAddr;
}

/*********************************************************************************************************
** Function name:           ioInportWord
** Descriptions:            从I/O端口输入一个半字(16位)
** input parameters:        ulPort: 端口地址
** output parameters:       none
** Returned value:          读到的数据
*********************************************************************************************************/
__inline INT16U ioInportWord(unsigned long ulPort)
{
    volatile INT16U *pusAddr;

    pusAddr = (INT16U *)ulPort;
    return *pusAddr;
}

/*********************************************************************************************************
** Function name:           ioInportLong
** Descriptions:            从I/O端口输入一个字(32位)
** input parameters:        ulPort: 端口地址
** output parameters:       none
** Returned value:          读到的数据
*********************************************************************************************************/
__inline INT32U ioInportLong(unsigned long ulPort)
{
    volatile INT32U *pulAddr;

    pulAddr = (INT32U *)ulPort;
    return *pulAddr;
}

/*********************************************************************************************************
** Function name:           ioOutportByte
** Descriptions:            把一个字节(8位)输出到I/O端口
** input parameters:        ucData: 要输出的数据
**                          ulPort: 端口地址
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void ioOutportByte(INT8U ucData, unsigned long ulPort)
{
    volatile INT8U *pucAddr;

    pucAddr  = (INT8U *)ulPort;
    *pucAddr = ucData;
}

/*********************************************************************************************************
** Function name:           ioOutportWord
** Descriptions:            把一个半字节(16位)输出到I/O端口
** input parameters:        usData: 要输出的数据
**                          ulPort: 端口地址
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void ioOutportWord(INT16U usData, unsigned long ulPort)
{
    volatile INT16U *pusAddr;

    pusAddr  = (INT16U *)ulPort;
    *pusAddr = usData;
}

/*********************************************************************************************************
** Function name:           ioOutportLong
** Descriptions:            把一个字(32位)输出到I/O端口
** input parameters:        ulData: 要输出的数据
**                          ulPort: 端口地址
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void ioOutportLong(INT32U ulData, unsigned long ulPort)
{
    volatile INT32U *pulAddr;

    pulAddr  = (INT32U *)ulPort;
    *pulAddr = ulData;
}


/*********************************************************************************************************
** Function name:           ioInportMultiByte
** Descriptions:            从I/O端口输入指定数目的字节(8位)
** input parameters:        ulPort:  端口地址
**                          ulCount: 需要输入的数据数目
** output parameters:       pvData:  数据保存的起始位置
** Returned value:          none
*********************************************************************************************************/
extern void ioInportMultiByte(unsigned long ulPort, void *pvData, unsigned long ulCount);

/*********************************************************************************************************
** Function name:           ioCmpByte
** Descriptions:            比较从I/O口输入的数据(8位字节流)与内存中的数据是否一致
** input parameters:        ulPort:  端口地址
**                          pvData:  被比较数据的起始位置 
**                          ulCount: 需要比较的数据数目
** output parameters:       none
** Returned value:          0:       数据一致
**                          其他:    数据有差别    
*********************************************************************************************************/
extern int ioCmpByte(unsigned long ulPort, void *pvData, unsigned long ulCount);

/*********************************************************************************************************
** Function name:           ioInportMultiWord
** Descriptions:            从I/O端口输入指定数目的半字(16位)
** input parameters:        ulPort:  端口地址
**                          ulCount: 需要输入的数据数目
** output parameters:       pvData:  数据保存的起始位置
** Returned value:          none
*********************************************************************************************************/
extern void ioInportMultiWord(unsigned long ulPort, void *pvData, unsigned long ulCount);

/*********************************************************************************************************
** Function name:           ioCmpWord
** Descriptions:            比较从I/O口输入的数据(16位半字流)与内存中的数据是否一致
** input parameters:        ulPort:  端口地址
**                          pvData:  被比较数据的起始位置 
**                          ulCount: 需要比较的数据数目
** output parameters:       none
** Returned value:          0:       数据一致
**                          其他:    数据有差别    
*********************************************************************************************************/
extern int ioCmpWord(unsigned long ulPort, void *pvData, unsigned long ulCount);

/*********************************************************************************************************
** Function name:           ioInportMultiLong
** Descriptions:            从I/O端口输入指定数目的字(32位)
** input parameters:        ulPort:  端口地址
**                          ulCount: 需要输入的数据数目
** output parameters:       pvData:  数据保存的起始位置
** Returned value:          none
*********************************************************************************************************/
extern void ioInportMultiLong(unsigned long ulPort, void *pvData, unsigned long ulCount);

/*********************************************************************************************************
** Function name:           ioCmpLong
** Descriptions:            比较从I/O口输入的数据(32位字流)与内存中的数据是否一致
** input parameters:        ulPort:  端口地址
**                          pvData:  被比较数据的起始位置 
**                          ulCount: 需要比较的数据数目
** output parameters:       none
** Returned value:          0:       数据一致
**                          其他:    数据有差别    
*********************************************************************************************************/
extern int ioCmpLong(unsigned long ulPort, void *pvData, unsigned long ulCount);

/*********************************************************************************************************
** Function name:           ioOutportMultiByte
** Descriptions:            把指定数目的字节(8位)输出I/O端口
** input parameters:        ulPort:  端口地址
**                          pvData:  数据保存的起始位置
**                          ulCount: 需要输出的数据数目
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void ioOutportMultiByte(unsigned long ulPort, void *pvData, unsigned long ulCount);

/*********************************************************************************************************
** Function name:           ioOutportMultiWord
** Descriptions:            从I/O端口输入指定数目的半字(16位)
** input parameters:        ulPort:  端口地址
**                          pvData:  数据保存的起始位置
**                          ulCount: 需要输出的数据数目
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void ioOutportMultiWord(unsigned long ulPort, void *pvData, unsigned long ulCount);

/*********************************************************************************************************
** Function name:           ioOutportMultiLong
** Descriptions:            从I/O端口输入指定数目的字(32位)
** input parameters:        ulPort:  端口地址
**                          pvData:  数据保存的起始位置
**                          ulCount: 需要输出的数据数目
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void ioOutportMultiLong(unsigned long ulPort, void *pvData, unsigned long ulCount);


#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */
#endif                                                                  /*  __IO_H                      */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
