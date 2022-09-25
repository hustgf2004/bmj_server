/****************************************Copyright (c)****************************************************
**                         Guangzhou ZHIYUAN electronics Co.,LTD.                               
**                                     
**                               http://www.embedtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           target.h
** Last modified Date:  2004-09-17
** Last Version:        1.0
** Descriptions:        header file of the specific codes for LPC2200 target boards
**                      Every project should include a copy of this file, user may modify it as needed
**--------------------------------------------------------------------------------------------------------
** Created by:          Chenmingji
** Created date:        2004-02-02
** Version:             1.0
** Descriptions:        The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:         Chenmingji
** Modified date:       2004-09-17
** Version:             1.01
** Descriptions:        Renewed the template, added codes to surport more compilers
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*********************************************************************************************************/
#ifndef __TARGET_H
#define __TARGET_H

#define __PRJ_TEMPLET_VER   0x2014082510                                /*  工程模板版本为 V1.0         */

/*********************************************************************************************************
    RTC时间结构体定义
*********************************************************************************************************/
typedef struct rtc_time  SD2405_TIME;
typedef struct rtc_time* PSD2405_TIME;


#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

#ifndef IN_TARGET

/*********************************************************************************************************
** Function name:           sd2405Init
** Descriptions:            Initialize the system time
** input parameters:        The system time
** output parameters:       None
** Returned value:          None
*********************************************************************************************************/
extern void sd2405Init(SD2405_TIME *pTime);

/*********************************************************************************************************
** Function name:           upSysTime
** Descriptions:            Update the system time 
** input parameters:        None
** output parameters:       None
** Returned value:          None
*********************************************************************************************************/
extern void upSysTime(void);

/*********************************************************************************************************
** Function name:           sd2405Read
** Descriptions:            read the system time
** input parameters:        The system time point
** output parameters:       The system time
** Returned value:          成功： OPERATE_SUCCESS
**                          失败： -OPERATE_FAIL
*********************************************************************************************************/
extern INT32S sd2405Read (SD2405_TIME *pTime);

/*********************************************************************************************************
** Function name:           Reset
** Descriptions:            resets the target board.
** input parameters:        None
** output parameters:       None
** Returned value:          None
*********************************************************************************************************/
extern void Reset (void);

/*********************************************************************************************************
** Function name:           TargetInit
**
** Descriptions:            Initialize the target board; it is called in a necessary place, change it as
**                          needed
**
** input parameters:        None
** output parameters:       None
** Returned value:          None
*********************************************************************************************************/
extern void TargetInit (void);
#endif                                                                  /*  IN_TARGET                   */

#ifdef __cplusplus
    }
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  _TARGET_H                   */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
