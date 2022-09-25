/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               PwdInput.c
** Latest modified Date:    2021-12-30
** Latest Version:          1.0
** Descriptions:            ��������˵�ҳ  
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ����������
** Created date:            2021-12-30
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

#include    "..\..\main.h"   

/*********************************************************************************************************
  �ⲿ����
*********************************************************************************************************/
extern TREE_NODE      *__GptnCurMenu;                                   /*  ��ǰ�˵��ڵ�                */
extern TREE_NODE      *__GptnRootMenu;                                  /*  �˵����ڵ�                  */

/*********************************************************************************************************
  ��������
*********************************************************************************************************/
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemDel(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemOnKey(MENU_ITEM_INFO *pmiibThis, INT32U uiKeyCode);

/*********************************************************************************************************
  ȫ�ֱ�������
*********************************************************************************************************/


/*********************************************************************************************************
  �ڲ�ʹ�ñ���
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifPwdInput = {
    __menuItemCreate,
    __menuItemDel,
    __menuItemOnKey,
    NULL
};


static INT8U __SucPassword[6];                                    
/*********************************************************************************************************
** Function name:           menuItemCreate
** Descriptions:            �����˵���
** input parameters:        pmiiThis    �˵�ҳ��Ϣ
** output parameters:       none
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�sys_if.h
*********************************************************************************************************/
static INT32S __menuItemCreate (MENU_ITEM_INFO *pmiiThis)
{
    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */ 
    memset(__SucPassword, 0x00, sizeof(__SucPassword));
    Gds.ucIsAuthorized = FALSE;
    ledNavi(NAVI_1 & NAVI_2 & NAVI_3 & NAVI_4 & NAVI_5 & NAVI_6 & NAVI_7 & NAVI_8 & NAVI_9 & NAVI_0 & NAVI_Q & NAVI_E);
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           menuItemDel
** Descriptions:            ɾ���˵�ҳ
** input parameters:        pmiiThis    �˵�ҳ��Ϣ
** output parameters:       none
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�sys_if.h
*********************************************************************************************************/
static INT32S __menuItemDel (MENU_ITEM_INFO *pmiiThis)
{
    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */
    if (strcmp("7910", __SucPassword) == 0) {                           /*  ������ȷ                    */
        Gds.ucIsAuthorized = TRUE;
        Gds.uiAuthorizedTimeoutTick = SEC_TIMER;
    }
    __GucEntered = 0;
    ledNavi(0xffffffff);
    return SYS_OK;    
}

/*********************************************************************************************************
** Function name:           menuItemOnKey
** Descriptions:            �˵������Ӧ����
** input parameters:        pmiiThis    �˵�ҳ��Ϣ
**                          usLen       ���������ݳ���
**                          pvData      ����������ָ��
** output parameters:       none
** Returned value:          SYS_OK      �ɹ�
**                          ����        ����,����ֵ�ο�sys_if.h
*********************************************************************************************************/
static INT32S __menuItemOnKey (MENU_ITEM_INFO *pmiiThis, INT32U uiKeyCode)
{
    INT8U           ucErr;
    INT32U          uiIdx;
    //static INT8U __SucPassword[6];
    pmiiThis = pmiiThis;
   /*  
    *  ����û�����        
    *  ............
    */
    
    /*
     *  ��������
     */
    if (NULL == pmiiThis) {
        return (-SYS_PARA_ERR);
    }

    ucErr = inputPwd(0, 16, uiKeyCode, 6, __SucPassword);
    if (INPUT_QUIT == ucErr) {                                          /*  �˳�����                    */
        memset(__SucPassword, 0x00, sizeof(__SucPassword));
        miDel(&__GmiibPwdInput);
        //mpHome(); 
        __GptnCurMenu = __GptnCurMenu->ptnParent;                       /*  �ָ�ԭ�в˵���              */
        if (miGetIndex(__GptnCurMenu, &uiIdx) < 0) {
            uiIdx = 0;
        }
        if (uiIdx & 0x01) {
            uiIdx -= 1;
        }
        mpDisplayEx(__GptnCurMenu->ptnParent, uiIdx);                   /*  ��ʾ��ǰ�˵�                */
    } else if (INPUT_COMPLETED == ucErr) {                              /*  �����������                */
        miDel(&__GmiibPwdInput);
        //mpHome();
        __GptnCurMenu = __GptnCurMenu->ptnParent;
        if (miGetIndex(__GptnCurMenu, &uiIdx) < 0) {
            uiIdx = 0;
        }
        if (uiIdx & 0x01) {
            uiIdx -= 1;
        }
        mpDisplayEx(__GptnCurMenu->ptnParent, uiIdx);                   /*  ��ʾ��ǰ�˵�                */
    }
    return SYS_OK;
}


/*********************************************************************************************************
  ��������˵�ҳ����
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibPwdInput = {                    /*  �˵�����Ϣ                  */
    "����������",
    (MENU_ITEM_FUNC *)&GmifPwdInput,
    0x6300
};

/*********************************************************************************************************
** Function name:           miPwdInputInit
** Descriptions:            ��������˵����ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miPwdInputInit(void)
{ 
    /*
     *  ��Ӳ˵�ҳ
     */
    miAdd(NULL, &__GmiibPwdInput);
}
/*********************************************************************************************************
** Function name:           miPwdInputDel
** Descriptions:            ��������˵���ж��
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void mpPwdInputDel (void)
{ 
    /*
     *  ɾ���˵�ҳ
     */
    miDel(&__GmiibPwdInput);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
