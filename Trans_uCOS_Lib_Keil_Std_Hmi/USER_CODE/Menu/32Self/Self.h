/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Self.h
** Latest modified Date:    2021-10-03
** Latest Version:          1.0.0
** Descriptions:            �Կز˵�ҳͷ�ļ�
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ����������
** Created date:            2021-10-03
** Version:                 1.0.0
** Descriptions:            The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#ifndef __SELF_H
#define __SELF_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** Function name:           miSelfInit
** Descriptions:            �Կز˵�ҳ��ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miSelfInit(void);

/*********************************************************************************************************
** Function name:           miSelfDel
** Descriptions:            �Կز˵�ҳж��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miSelfDel(void);

/*********************************************************************************************************
** Function name:           keyOnMaster
** Descriptions:            ���ؽ��水����Ӧ
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void keyOnMaster(INT32U uiKeyCode);

extern const MENU_ITEM_INFO_BASE __GmiibSelf;
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __SELF_H                    */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
