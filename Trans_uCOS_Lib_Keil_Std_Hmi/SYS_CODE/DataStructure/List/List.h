/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               List.h
** Latest modified Date:    2014-12-05
** Latest Version:          1.0.0
** Descriptions:            链表数据结构
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2014-12-05
** Version:                 1.0.0
** Descriptions:            The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#ifndef __LIST_H
#define __LIST_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

#include    "..\SYS_CODE\Head\system.h" 




/*
 *  链表控制块数据结构
 */
typedef struct __list_cb {
    void                   *pls;                                        /*  链表指针                    */
    INT32U                  uiMaxNode;                                  /*  链表最大节点数              */
    void                   *pvFreeNode;                                 /*  链表当前空闲节点            */
    void                   *pvFirstNode;                                /*  链表被占用的首节点          */
} __LIST_CB, *__PLIST_CB;


/*
 *  通用单链表数据结构
 */
typedef struct __single_list {
    struct __single_list   *pslsNext;                                   /*  链表下一个元素              */
    void                   *pvData;                                     /*  本节点数据指针              */
} __SINGLE_LIST, *__PSINGLE_LIST;


/*
 *  通用双链表数据结构
 */
typedef struct __dual_list {
    struct __dual_list     *pdlsPrev;                                   /*  链表前一个节点              */    
    struct __dual_list     *pdlsNext;                                   /*  链表下一个节点              */

    void                   *pvData;                                     /*  本节点数据指针              */
} __DUAL_LIST, *__PDUAL_LIST;



/*********************************************************************************************************
** Function name:           lsInit
** Descriptions:            在一内存块上初始化单链表
** input parameters:        plcb            单链表存放地址
**                          uiMaxNode       单链表最大数量
**                         
**                          
** output parameters:       SYS_OK
** Returned value:          >=0             成功
**                          负数            错误,绝对值参考afxMenu.h
*********************************************************************************************************/
extern INT32S  lsInit(__LIST_CB *plcb, INT32U uiMaxNode);

/*********************************************************************************************************
** Function name:           lsNodeAdd
** Descriptions:            单链表增加一个节点
** input parameters:        plcb            单链表存放地址
**                          pvData          节点的数据指针
**                         
**                          
** output parameters:       SYS_OK
** Returned value:          >=0             成功
**                          负数            错误,绝对值参考afxMenu.h
*********************************************************************************************************/
extern INT32S  lsNodeAdd(__LIST_CB *plcb, void *pvData);

/*********************************************************************************************************
** Function name:           lsNodeDel
** Descriptions:            单链表删除一个节点
** input parameters:        plcb            单链表存放地址
**                          pvData          节点的数据指针
**                         
**                          
** output parameters:       SYS_OK
** Returned value:          >=0             成功
**                          负数            错误,绝对值参考afxMenu.h
*********************************************************************************************************/
extern INT32S  lsNodeDel(__LIST_CB *plcb, void *pvData);

/*********************************************************************************************************
** Function name:           dlsInit
** Descriptions:            在一内存块上初始化双链表
** input parameters:        plcb            双链表存放地址
**                          uiMaxNode       双链表最大数量
**                         
**                          
** output parameters:       SYS_OK
** Returned value:          >=0             成功
**                          负数            错误,绝对值参考afxMenu.h
*********************************************************************************************************/
extern INT32S  dlsInit(__LIST_CB *plcb, INT32U uiMaxNode);

/*********************************************************************************************************
** Function name:           dlsNodeAdd
** Descriptions:            双链表增加一个节点
** input parameters:        plcb            双链表控制块指针
**                          pvData          节点的数据指针
**                         
**                          
** output parameters:       SYS_OK
** Returned value:          >=0             成功
**                          负数            错误,绝对值参考afxMenu.h
*********************************************************************************************************/
extern INT32S  dlsNodeAdd(__LIST_CB *plcb, void *pvData);


/*********************************************************************************************************
** Function name:           dlsNodeDel
** Descriptions:            双链表删除一个节点
** input parameters:        plcb            双链表控制块指针
**                          pvData          节点的数据指针
**                         
**                          
** output parameters:       SYS_OK
** Returned value:          >=0             成功
**                          负数            错误,绝对值参考afxMenu.h
*********************************************************************************************************/
extern INT32S  dlsNodeDel(__LIST_CB *plcb, void *pvData);

#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __LIST_H                */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
