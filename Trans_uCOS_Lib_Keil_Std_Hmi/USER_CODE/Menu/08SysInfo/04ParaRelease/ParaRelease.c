/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               ParaRelease.c
** Latest modified Date:    2021-09-26
** Latest Version:          1.0
** Descriptions:            ���������˵���
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ����������
** Created date:            2021-09-26
** Version:                 1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

#include    "..\..\..\main.h"
/*********************************************************************************************************
  �ⲿ����
*********************************************************************************************************/

/*********************************************************************************************************
  ��������
*********************************************************************************************************/
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiibThis, INT32U uiKeyCode);


/*********************************************************************************************************
  ȫ�ֱ�������
*********************************************************************************************************/


/*********************************************************************************************************
  �ڲ�ʹ�ñ���
*********************************************************************************************************/

const MENU_ITEM_FUNC GmifParaRelease = {
    NULL,
    NULL,
    __menuItemOnKey,
    NULL
};


/*********************************************************************************************************
** Function name:           menuItemOnKey
** Descriptions:            �˵������Ӧ����
** input parameters:        pmiiThis    �˵�����Ϣ
**                          usLen       ���������ݳ���
**                          pvData      ����������ָ��
** output parameters:       none
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�sys_if.h
*********************************************************************************************************/
static INT32S __menuItemOnKey (MENU_ITEM_INFO *pmiiThis, INT32U uiKeyCode)
{      
    INT32U         *puiKeyCode;
    pmiiThis = pmiiThis;
   /*  
    *  �����û�����        
    *  ............
    */

    return SYS_OK;  
}


/*********************************************************************************************************
  ���������˵����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibParaRelease = {                        /*  �˵�����Ϣ                  */
    "��������",
    (MENU_ITEM_FUNC *)&GmifParaRelease,
    0x0804,
    (1 << 7) | (PARA_SCOPE_LOCAL << 4) | PARA_TYPE_OPERATE
};


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/