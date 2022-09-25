/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Lock.h
** Latest modified Date:    2021-10-07
** Latest Version:          1.0.0
** Descriptions:            ��ͣ�˵�ҳͷ�ļ�
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ����������
** Created date:            2021-10-07
** Version:                 1.0.0
** Descriptions:            The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#ifndef __STOP_H
#define __STOP_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** Function name:           miStopInit
** Descriptions:            ��ͣ�˵�ҳ��ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miStopInit(void);

/*********************************************************************************************************
** Function name:           miStopDel
** Descriptions:            ��ͣ�˵�ҳж��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miStopDel(void);

extern const MENU_ITEM_INFO_BASE __GmiibStop;
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __STOP_H                    */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
