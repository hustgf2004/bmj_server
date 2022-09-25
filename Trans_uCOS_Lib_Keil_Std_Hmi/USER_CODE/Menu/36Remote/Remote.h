/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Remote.h
** Latest modified Date:    2022-01-03
** Latest Version:          1.0.0
** Descriptions:            ң�ز˵�ҳͷ�ļ�
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ����������
** Created date:            2022-01-03
** Version:                 1.0.0
** Descriptions:            The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#ifndef __REMOTE_H
#define __REMOTE_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** Function name:           miRemoteInit
** Descriptions:            ң�ز˵�ҳ��ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miRemoteInit(void);

/*********************************************************************************************************
** Function name:           miRemoteDel
** Descriptions:            ң�ز˵�ҳж��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miRemoteDel(void);

extern const MENU_ITEM_INFO_BASE __GmiibRemote;
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __REMOTE_H                  */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
