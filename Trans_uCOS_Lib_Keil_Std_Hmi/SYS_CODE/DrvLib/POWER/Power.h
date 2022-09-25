/****************************************Copyright (c)****************************************************
**                              
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Power.h
** Last modified Date:  2012-12-31
** Last Version:        1.0
** Descriptions:        LPC2200 Power驱动
**--------------------------------------------------------------------------------------------------------
** Created by:          
** Created date:        2012-12-31
** Version:             V1.0
** Descriptions:        The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
*********************************************************************************************************/

#ifndef __POWER_H_
#define __POWER_H_
#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
  PCON 相关索引
*********************************************************************************************************/
#define     PCON0           0                                           /*  功率控制设备号              */


/*********************************************************************************************************
  PCON 模式配置命令
*********************************************************************************************************/
#define     SET_PCONMODE    0                                           /*  处理器功率控制模式          */
#define     SET_PCONPMODE   1                                           /*  外设功率控制模式            */

/*********************************************************************************************************
  外设功率控制宏定义
*********************************************************************************************************/
#define Off                 0
#define On                  1

#define PCTIM0      (On << 1)                                           /*  定时器0                     */
#define PCTIM1      (On << 2)                                           /*  定时器1                     */
#define PCUART0     (On << 3)                                           /*  UART0                       */
#define PCUART1     (On << 4)                                           /*  UART1                       */
#define PCPWM1      (On << 5)                                           /*  PWM0                        */

#define PCI2C0      (On << 7)                                           /*  I2C0                        */
#define PCSPI0      (On << 8)                                           /*  SPI0                        */
#define PCRTC       (On << 9)                                           /*  RTC                         */
#define PCSSP1      (On << 10)                                          /*  SPI1                        */
#define PCEMC       (On << 11)                                          /*  外部存储器                  */
#define PCAD        (On << 12)                                          /*  AD转换器                    */
/*  仅LPC2292/2204      */ 
#define PCCAN1      (On << 13)                                          /*  CAN1                        */                                     
#define PCCAN2      (On << 14)                                          /*  CAN2                        */
#define PCCAN3      (On << 15)                                          /*  CAN3                        */
#define PCCAN4      (On << 16)                                          /*  CAN4                        */
#define PC_CUSTOM   (PCTIM0 | PCTIM1  | PCUART0 | PCUART1 | PCPWM1 | \
                     PCI2C0 | PCSPI0  | PCRTC   | PCSSP1  | PCEMC  | PCAD |\
                     PCCAN1 | PCCAN2 | PCCAN3 | PCCAN4)


/*********************************************************************************************************
** Function name:       powerSetMode
** Descriptions:        系统进入空闲或掉电模式和外设功率控制
** input parameters：   ulId            子设备号
**                      ulCmd           命令参数
**                      pucArg          配置参数字符窜指针
** output parameters:   None               
** Returned value:      操作成功        OPERATE_SUCCESS;
**                      操作失败        -OPERATE_FAIL
** Example:             char  pconpArg[32];
**                      sprintf(pconpArg, "DevSel=%u", PC_CUSTOM);
**                      powerSetMode(PCON0, SET_PCONPMODE, pconpArg);
*********************************************************************************************************/
extern INT32S powerSetMode(INT32U ulId, INT32U ulCmd, char *pucArg);

#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */
#endif                                                                  /*  _POWER_H_                   */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
