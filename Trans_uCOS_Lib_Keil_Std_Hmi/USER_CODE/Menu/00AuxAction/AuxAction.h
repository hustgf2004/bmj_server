/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn  
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               AuxAction.h
** Latest modified Date:    2021-09-22
** Latest Version:          1.0.0
** Descriptions:            ���������˵�ҳͷ�ļ�
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ����������
** Created date:            2021-09-22
** Version:                 1.0.0
** Descriptions:            The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#ifndef __AUX_ACTION_H
#define __AUX_ACTION_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** Function name:           miAuxActionInit
** Descriptions:            ���������˵�ҳ��ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miAuxActionInit(void);
    
/*********************************************************************************************************
** Function name:           miAuxActionDel
** Descriptions:            ���������˵�ҳж��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miAuxActionDel (void);

/*********************************************************************************************************
** Function name:           miAuxToValve
** Descriptions:            ��������ת��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern INT32U miAuxToValve(TREE_NODE *ptnAuxMenu, INT8U ucIsAuxRight);

#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __AUX_ACTION_H              */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
