/****************************************Copyright (c)****************************************************
**                              
**
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           emc.h
** Last modified Date:  2013-03-15
** Last Version:        1.01
** Descriptions:        emc驱动外部头文件
**--------------------------------------------------------------------------------------------------------
** Created by:          
** Created date:        2013-03-15
** Version:             V1.0
** Descriptions:        The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
*********************************************************************************************************/

#ifndef  _EMC_H_
#define  _EMC_H_
#ifdef  __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
  EMC 相关索引
*********************************************************************************************************/

#define  BANK0          0                                               /*  Bank0 ID 号                 */
#define  BANK1          1                                               /*  Bank1 ID 号                 */
#define  BANK2          2                                               /*  Bank2 ID 号                 */
#define  BANK3          3                                               /*  Bank3 ID 号                 */

#define  DATA_8BIT      8
#define  DATA_16BIT     16
#define  DATA_32BIT     32

/*********************************************************************************************************
  返回值定义
*********************************************************************************************************/
#define     ET_OK               0                                       /*  操作成功                    */
#define     ET_PARAMETER_ERR    1                                       /*  参数错误                    */

#define     ET_DATA_BUS_LOW     2                                       /*  数据线为低电平              */
#define     ET_DATA_BUS_HIGH    3                                       /*  数据线为高电平              */

#define     ET_DATA_BUS_TGLOW   4                                       /*  数据线粘连为低电平          */
#define     ET_DATA_BUS_TGHIGH  5                                       /*  数据线粘连为高电平          */

#define     ET_ADDR_BUS_LOW     6                                       /*  地址线为低电平              */
#define     ET_ADDR_BUS_HIGH    7                                       /*  地址线为高电平              */

#define     ET_ADDR_BUS_TGLOW   8                                       /*  地址线粘连为低电平          */
#define     ET_ADDR_BUS_TGHIGH  9                                       /*  地址线粘连为高电平          */

#define     ET_MEMORY_ERR       10                                      /*  存储空间有坏区              */

/*********************************************************************************************************
** Function name:           emcTest
** Descriptions:            EMC总线测试
** input parameters:        uiBANK      : BANK号
**                          uiSizeOfAB  : 地址宽度
**                          Rsv         : 保留参数
** output parameters:       None
** Returned value:          (((数据线或地址线数)<<16) | 错误状态码)
*********************************************************************************************************/
INT32S  emcTest(INT32U uiBANK, INT32U uiSizeOfAB, void* pRsv );


/*********************************************************************************************************  
** Function name:           emcInit  
** Descriptions:            EMC初始化
** Input parameters:        uiId            EMC的BANK号，如uiId=0,为BANK0  
**                          pcArg           配置参数字符窜指针                                                       
**                          pRsv            保留参数  
** Output parameters:       NONE  
** Returned value:          OPERATE_SUCCESS 操作成功 
**                          -OPERATE_FAIL   操作失败
** Example:                 char cEmcArt[]="BusWidth=8 ReadDly=15 WriteDly=15 Idcy=10";  
**                          emcInit( BANK0, cEmcArt, NULL );   
*********************************************************************************************************/ 
extern INT32S emcInit(INT32U ulId, char *pucArg, void *pvRsv);

/*********************************************************************************************************  
** Function name:           emcWrite  
** Descriptions:            EMC写操作  
** Input parameters:        uiId            EMC的BANK号，如uiId=0,为BANK0  
**                          uiBw            数据总线宽度  
**                          uiAddr          偏移地址0x80000000 ~ 0x83FFFFFF  
**                                          BANK0:  0x80000000 ~ 0x80FFFFFF  
**                                          BANK1:  0x81000000 ~ 0x81FFFFFF  
**                                          BANK2:  0x82000000 ~ 0x82FFFFFF  
**                                          BANK3:  0x83000000 ~ 0x83FFFFFF  
**                          uiNum           写的数据个数                                                                        
**                          pvData          输入数组首地址  
** Output parameters:       NONE  
** Returned value:          OPERATE_SUCCESS 操作成功 
**                          -OPERATE_FAIL   操作失败
**                          EXBUSADRROVER   超出地址范围
** Example:                 uint32 uiWriteData[10]={0};  
**                          emcWrite( BANK0, 16, 0x80000000, 10, uiWriteData );  
*********************************************************************************************************/ 
extern INT32S emcWrite(INT32U ulId, INT32U ulBw, INT32U ulAddr, void *pvData, INT32U ulSize);

/*********************************************************************************************************  
** Function name:           emcRead  
** Descriptions:            EMC读操作  
** Input parameters:        uiId            EMC的BANK号，如uiId=0,为BANK0  
**                          uiBw            数据总线宽度  
**                          uiAddr          偏移地址0x80000000 ~ 0x83FFFFFF  
**                                          BANK0:  0x80000000 ~ 0x80FFFFFF  
**                                          BANK1:  0x81000000 ~ 0x81FFFFFF  
**                                          BANK2:  0x82000000 ~ 0x82FFFFFF  
**                                          BANK3:  0x83000000 ~ 0x83FFFFFF  
**                          uiNum           读的数据个数                                                                        
**                          pvData          读数据的存放首地址  
** Output parameters:       NONE  
** Returned value:          OPERATE_SUCCESS 操作成功 
**                          -OPERATE_FAIL   操作失败 
** Example:                 INT32U uiReadData[10]={0};  
**                          emcRead( BANK0, 16, 0x80000000, 10, uiReadData );  
*********************************************************************************************************/
extern INT32S emcRead(INT32U ulId, INT32U ulBw, INT32U ulAddr, void *pvData, INT32U ulSize);

#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */
#endif                                                                  /*  _EMC_H_                     */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

