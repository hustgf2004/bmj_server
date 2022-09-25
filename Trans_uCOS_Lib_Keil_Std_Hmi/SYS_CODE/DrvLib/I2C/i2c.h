/****************************************Copyright (c)****************************************************
**                              
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           i2c.h
** Last modified Date:  2013-08-22
** Last Version:        1.0
** Descriptions:        LPC2200 i2c驱动封装头文件
**--------------------------------------------------------------------------------------------------------
** Created by:          
** Created date:        2013-08-22
** Version:             1.0
** Descriptions:        The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
*********************************************************************************************************/
#ifndef _I2C_H_
#define _I2C_H_
#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                */

/*********************************************************************************************************
  I2C 标示
*********************************************************************************************************/
#define I2C0                0

/*********************************************************************************************************
  I2C中断通道号
*********************************************************************************************************/
#define I2C0_IRQ_CHN        9


/*********************************************************************************************************
  I2C 子地址类型
*********************************************************************************************************/
#define NON_BYTE_SADDR      0                                           /*  无子地址                    */
#define ONE_BYTE_SADDR      1                                           /*  一个字节子地址              */
#define TWO_BYTE_SADDR      2                                           /*  两个字节子地址              */

/*********************************************************************************************************
  驱动库函数操作返回值
*********************************************************************************************************/
#define I2C_BUSY            0                                           /*  I2C忙                       */
#define I2C_WRITE_END       1                                           /*  写完成                      */
#define I2C_READ_END        2                                           /*  读完成                      */
#define I2C_NOT_GET_BUS     4                                           /*  丢失仲裁                    */
#define I2C_ACK_ERR         8                                           /*  接收ACK错误                 */
#define I2C_IDLE            3                                           /*  I2C空闲                     */

/*********************************************************************************************************
  I2C模式操作命令参数
*********************************************************************************************************/
#define  SET_SPEED          0                                           /*  设定I2C速率命令             */

/*********************************************************************************************************
  I2C从机模式下的钩子函数流
*********************************************************************************************************/
struct i2cSalHooks {                                                    /*   从机模式下的钩子函数流     */
    INT8U*          pSendBuf;                                           /*   发送缓冲指针               */
    INT8U*          pRevBuf;                                            /*   接收缓冲指针               */

    void          (*pSend)  (void* pRsv, INT8U* ucSbr, INT32U* SuAddr); /*   发送数据调用的函数         */
                                                                        /*   pRsv  : 保留,用户不要操作  */
                                                                        /*   ucSbr ：待发送的数据       */
                                                                        /*   SuAddr: 待发送数据的子地址 */

    void          (*pReceive)(void* pRsv, INT8U ucRbr, INT32U* SuAddr); /*   接收到字符调用的函数       */
                                                                        /*   pRsv  : 保留,用户不要操作  */
                                                                        /*   ucRbr : 待写入的数据       */
                                                                        /*   SuAddr: 待写入数据的子地址 */
};

typedef struct i2cSalHooks  I2C_SALHOOKS;
typedef struct i2cSalHooks* PI2C_SALHOOKS;

#ifndef _IN_I2C
/*********************************************************************************************************
** Function name:       i2cInit
** Descriptions:        I2c初始化
** input parameters:    ulId    : 设备标示
**                      pucArg  : 配置参数字符窜指针                                         
**                      pvRsv   : 预留参数
** output parameters:   None
** Returned value:      操作成功: OPERATE_SUCCES
**                      操作失败: -OPERATE_FAIL
*********************************************************************************************************/
extern INT32S i2cInit(INT32U ulId, char *pucArg, void *pvRsv);

/*********************************************************************************************************
** Function name:       i2cSetMode
** Descriptions:        I2c模式设置
**
** input parameters:    ulId    : 设备标示
**                      ulCmd   : 命令参数
**                      pucArg  : 配置参数字符窜指针
** output parameters:   None
** Returned value:      操作成功: OPERATE_SUCCES
**                      操作失败: -OPERATE_FAIL
*********************************************************************************************************/
extern INT32S i2cSetMode(INT32U ulId, INT32U ulCmd, char *pucArg);

/*********************************************************************************************************  
** Function name:           i2cGetDatNum  
** Descriptions:            返回i2c接口数据缓存中有效数据个数
** Input parameters:        uiId            i2c器件号  
** Output parameters:       NONE  
** Returned value:          缓存有效字节数  操作成功          
**                          -OPERATE_FAIL   操作失败         
*********************************************************************************************************/   
extern INT32S i2cGetDatNum(INT32U uiId);

/*********************************************************************************************************
** Function name:           i2cRead
** Descriptions:            从I2C从器件读数据
** input parameters:        ulId            i2c器件号
**                          ucAddr          从机地址
**                          ucSubAddr       从机内部子地址存放指针
**                          ucSubAddrLen    从机内部子地址长度
**                          pucDat          指向返回数据存储位置的指针
**                          uiSize          读取数据长度
** output parameters:       None
** Returned value:          OPERATE_SUCCES  操作成功    
**                          -OPERATE_FAIL   操作失败    
*********************************************************************************************************/
extern INT32S i2cRead ( INT32U ulId,
                        INT8U  ucAddr,
                        INT8U *pucSubAddr,
                        INT8U  ucSubAddrLen,
                        INT8U *pucRet, 
                        INT32U ulSize,
                        void (*pfCallBack)(INT8U));

/*********************************************************************************************************
** Function name:           i2cWrite
** Descriptions:            向I2C从器件写数据
** input parameters:        uiId        
**                          ucAddr          从机地址
**                          ucSubAddr       从机内部子地址存放指针
**                          ucSubAddrLen    从机内部子地址长度
**                          pucRet          指向返回数据存储位置的指针
**                          uiSize          数据长度
** output parameters:       None
** Returned value:          OPERATE_SUCCES  操作成功    
**                          -OPERATE_FAIL   操作失败    
*********************************************************************************************************/
extern INT32S i2cWrite( INT32U uiId,
                        INT8U  ucAddr,
                        INT8U *pucSubAddr,
                        INT8U  ucSubAddrLen,
                        INT8U *pucDat, 
                        INT32U uiSize,
                        void (*pfCallback)(INT8U));

/*********************************************************************************************************  
** Function name:           i2cGetFlag  
** Descriptions:            返回I2C器件当前状态如果通信失败，则表示上次总线操作失败，  
**                          但是现在总线仍然是空闲的,空闲表示上次通信成功或没有进行过通信  
**                          现在总线是空闲的，可以启动总线通信  
** Input parameters:        uiId            i2c器件号  
** Output parameters:       NONE  
** Returned value:          操作成功        返回当前I2C总线状态  
**                                          I2C_IDLE： 表示总线空闲  
**                                          I2C_WRITE_END：表示写操作成功  
**                                          I2C_READ_END：表示读操作成功  
**                                          I2C_ERR：表示总线操作失败  
**                                          I2C_BUSY：表示总线正在工作中  
**                          操作失败        -OPERATE_FAIL  
*********************************************************************************************************/ 
extern INT32S i2cGetFlag(INT32U ulId);

/*********************************************************************************************************
** Function name:           i2cSetMode
** Descriptions:            i2c模式设置
**
** input parameters:        uiId            i2c器件号
**                          uiCmd           设置命令码
**                          pcArg           配置参数字符串指针
** output parameters:       None
** Returned value:          OPERATE_SUCCES  操作成功
**                          -OPERATE_FAIL   操作失败
*********************************************************************************************************/
extern INT32S i2cSetMode(INT32U uiId, INT32U uiCmd, char *pcArg);

/*********************************************************************************************************  
** Function name:           i2cIsr
** Descriptions:            i2c中断服务函数
** Input parameters:        uiId            i2c器件号  
** Output parameters:       NONE   
** Returned value:          NONE  
*********************************************************************************************************/   
extern void i2cIsr(INT32U uiId);

#endif                                                                  /*  _IN_I2C                     */
#ifdef __cplusplus
}   
#endif                                                                  /*  __cplusplus                 */
#endif                                                                  /*  _I2CCONFIG_H_               */
