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
#ifndef __TREE_H
#define __TREE_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

#include    "..\SYS_CODE\Head\system.h" 


/*
 *  树节点数据结构
 */
typedef struct __tree_node {
    struct __tree_node     *ptnPrev;                                    /*  左节点                      */
    struct __tree_node     *ptnNext;                                    /*  右节点                      */
    struct __tree_node     *ptnParent;                                  /*  父节点                      */
    struct __tree_node     *ptnChild;                                   /*  子节点                      */
    void                   *pvData;                                     /*  节点数据                    */
} TREE_NODE, *PTREE_NODE;


/*********************************************************************************************************
** Function name:           treeInit
** Descriptions:            菜单项树初始化
** input parameters:        ptnRoot:            根节点指针
** output parameters:       none
** Returned value:          >=0             成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S treeInit(void *ptnRoot);

/*********************************************************************************************************
** Function name:           treeAddNode
** Descriptions:            增加一个节点
** input parameters:        ptnParent       父节点
**                          ptnAdd          待增加的节点
**                         
**                          
** output parameters:       SYS_OK
** Returned value:          >=0             成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S  treeAddNode(TREE_NODE *ptnParent, TREE_NODE *ptnAdd);

/*********************************************************************************************************
** Function name:           treeDelNode
** Descriptions:            删除一个节点
** input parameters:        ptnParent       父节点
**                          ptnDel          待删节点
**                         
**                          
** output parameters:       SYS_OK
** Returned value:          >=0             成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S  treeDelNode(TREE_NODE *ptnDel);

/*********************************************************************************************************
** Function name:           treeGetIndex
** Descriptions:            获取指定节点在同级兄弟节点中的索引
** input parameters:        ptnM            菜单根节点
** output parameters:       puiRtn          索引返回指针
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S treeGetIndex(TREE_NODE *ptn, INT32U *puiRtn);


/*********************************************************************************************************
** Function name:           treeInsertNodeFront
** Descriptions:            插入一个同级前置节点
** input parameters:        ptnBrother      兄弟节点
**                          ptnAdd          待增加节点                        
** output parameters:       SYS_OK
** Returned value:          >=0             成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S  treeInsertNodeFront(TREE_NODE *ptnBrother, TREE_NODE *ptnAdd);

/*********************************************************************************************************
** Function name:           treeInsertNodePost
** Descriptions:            插入一个同级后置节点
** input parameters:        ptnBrother      兄弟节点
**                          ptnAdd          待增加节点                        
** output parameters:       SYS_OK
** Returned value:          >=0             成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S  treeInsertNodePost(TREE_NODE *ptnBrother, TREE_NODE *ptnAdd);

#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __TREE_H                    */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
