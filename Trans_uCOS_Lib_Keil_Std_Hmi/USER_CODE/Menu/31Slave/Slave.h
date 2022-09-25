/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Slave.h
** Latest modified Date:    2021-12-28
** Latest Version:          1.0.0
** Descriptions:            �ӿز˵�ҳͷ�ļ�
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ����������
** Created date:            2021-12-28
** Version:                 1.0.0
** Descriptions:            The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#ifndef __SLAVE_H
#define __SLAVE_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** Function name:           miSlvInit
** Descriptions:            �ӿز˵�ҳ��ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miSlvInit(void);

/*********************************************************************************************************
** Function name:           miSlvDel
** Descriptions:            �ӿز˵�ҳж��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miSlvDel(void);

extern const MENU_ITEM_INFO_BASE __GmiibSlv;
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __SLAVE_H                   */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
