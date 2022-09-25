/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               PwdInput.h
** Latest modified Date:    2021-12-30
** Latest Version:          1.0.0
** Descriptions:            ��������˵�ҳͷ�ļ�
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ����������
** Created date:            2021-12-30
** Version:                 1.0.0
** Descriptions:            The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#ifndef __PWD_INPUT_H
#define __PWD_INPUT_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** Function name:           miPwdInputInit
** Descriptions:            ��������˵�ҳ��ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miPwdInputInit(void);

/*********************************************************************************************************
** Function name:           miPwdInputDel
** Descriptions:            ��������˵�ҳж��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miPwdInputDel(void);

extern const MENU_ITEM_INFO_BASE __GmiibPwdInput;
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __PWD_INPUT_H               */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
