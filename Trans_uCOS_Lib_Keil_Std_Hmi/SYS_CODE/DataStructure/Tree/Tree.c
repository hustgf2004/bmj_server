/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Tree.c
** Latest modified Date:    2021-09-29
** Latest Version:          1.1
** Descriptions:            树数据结构实现
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2017-02-04
** Version:                 1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             超人力霸王
** Modified date:           2021-09-29
** Version:                 1.1
** Descriptions:            实现相同父节点的节点之间的双向链表结构的前导指针；
**
*********************************************************************************************************/

#include    ".\Tree.h"   

/*********************************************************************************************************
  外部声明
*********************************************************************************************************/


/*********************************************************************************************************
  函数声明
*********************************************************************************************************/


/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/


/*********************************************************************************************************
  内部使用变量
*********************************************************************************************************/


/*********************************************************************************************************
** Function name:           treeInit
** Descriptions:            菜单项树初始化
** input parameters:        ptnRoot:            根节点指针
** output parameters:       none
** Returned value:          >=0             成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S treeInit(void *ptnRoot)
{
    if (!ptnRoot){
        return (-SYS_PARA_ERR);
    }
    memset(ptnRoot, 0x00, sizeof(TREE_NODE));
    
    return SYS_OK;

}

/*********************************************************************************************************
** Function name:           treeAddNode
** Descriptions:            增加一个节点
** input parameters:        ptnParent       父节点
**                          ptnAdd          待增加节点                        
** output parameters:       SYS_OK
** Returned value:          >=0             成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S  treeAddNode(TREE_NODE *ptnParent, TREE_NODE *ptnAdd)
{
    TREE_NODE  **pptnTail;
    /*
     *  参数过滤
     */
    if ((NULL == ptnParent) || (NULL == ptnAdd)) {
        return (-SYS_PARA_ERR);
    }

    /*
     *  查找链表尾节点
     */
    pptnTail = &ptnParent->ptnChild;
    do {
        if (NULL == *pptnTail) {                                        /*  无子节点                    */
            ptnAdd->ptnPrev = NULL;
            *pptnTail = ptnAdd;
            break;
        } else if ((*pptnTail)->ptnNext == NULL) {                      /*  尾节点                      */
            (*pptnTail)->ptnNext = ptnAdd;
            ptnAdd->ptnPrev = *pptnTail;
            break;
        }
        pptnTail = &(*pptnTail)->ptnNext;        
    } while(1);     
    ptnAdd->ptnParent   = ptnParent;
    ptnAdd->ptnNext     = NULL;
    ptnAdd->ptnChild    = NULL;
    return SYS_OK;
}


/*********************************************************************************************************
** Function name:           treeDelNode
** Descriptions:            删除一个节点
** input parameters:        ptnParent       父节点
**                          ptnDel          待删节点                         
** output parameters:       SYS_OK
** Returned value:          >=0             成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S  treeDelNode_(TREE_NODE *ptnParent, void *pvDel)
{
    TREE_NODE **pptnWalker;
    TREE_NODE  *ptnPrev;
    /*
     *  参数过滤
     */
    if ((NULL == ptnParent) || (NULL == pvDel)){
        return (-SYS_PARA_ERR);
    }
    /*
     *  查找链表相同数据指针
     */
    pptnWalker = &ptnParent->ptnChild;
    ptnPrev = ptnParent;
    
    do {
        if (NULL == (*pptnWalker)) {
            return (-SYS_NO_NODE);
        }
        if ((*pptnWalker)->pvData == pvDel) {                           /*  待删节点                    */
            break;
        } else {
            ptnPrev = *pptnWalker;
            pptnWalker = &(*pptnWalker)->ptnNext;
        }
    } while(1);
    
    ptnPrev->ptnNext = (*pptnWalker)->ptnNext;                           /*  删除节点                    */   
    sysHeapFree(*pptnWalker);
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           treeDelNode
** Descriptions:            删除一个节点
** input parameters:        ptnDel          待删节点
**                          
**                         
**                          
** output parameters:       SYS_OK
** Returned value:          >=0             成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S  treeDelNode(TREE_NODE *ptnDel)
{
    TREE_NODE **pptnWalker;
    TREE_NODE  *ptnPrev;
    TREE_NODE  *ptnParent;
    /*
     *  参数过滤
     */
    if (NULL == ptnDel) {
        return (-SYS_PARA_ERR);
    }
    //if (ptnDel->ptnChild) {                                             /*  非叶节点                    */
    //    return (-SYS_PARA_ERR);
    //}
    ptnParent = ptnDel->ptnParent;
    if (NULL == ptnParent) {                                            /*  根节点                      */
        return SYS_OK;
    }
    /*
     *  查找左节点
     */
    pptnWalker = &ptnParent->ptnChild;
    ptnPrev = ptnParent;
    do {
        if (NULL == (*pptnWalker)) {
            return (-SYS_NO_NODE);
        }
        if (*pptnWalker == ptnDel) {                                    /*  待删节点                    */
            break;
        } else {
            ptnPrev = *pptnWalker;
            pptnWalker = &(*pptnWalker)->ptnNext;
        }
    } while(1);
    if (ptnPrev == ptnParent) {                                         /*  首节点                      */        
        if ((*pptnWalker)->ptnNext) {                                   /*  多兄弟节点                  */
            (*pptnWalker)->ptnNext->ptnPrev = NULL;
        } else {                                                        /*  单兄弟节点                  */
            ;
        }
        ptnPrev->ptnChild = (*pptnWalker)->ptnNext;
    } else {                                                            /*  多兄弟节点                  */   
        ptnPrev->ptnNext = (*pptnWalker)->ptnNext;
        (*pptnWalker)->ptnNext->ptnPrev = ptnPrev;
    }        
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           treeGetIndex
** Descriptions:            获取指定节点在同级兄弟节点中的索引
** input parameters:        ptnM            菜单根节点
** output parameters:       puiRtn          索引返回指针
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S treeGetIndex(TREE_NODE *ptn, INT32U *puiRtn)
{
    INT32U      uiIndex;
    TREE_NODE  *ptnWalker;
    if ((ptn == NULL) || (puiRtn == NULL)) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == ptn->ptnParent) {
        return (-SYS_NO_NODE);
    }
    /*
     *  两种菜单树的删除都可用
     */
    ptnWalker = ptn->ptnParent->ptnChild;                               /*  首个子节点                  */
    uiIndex = 0;
    do {
        if (ptnWalker == ptn) {
            *puiRtn = uiIndex;
            break;
        }
        ptnWalker = ptnWalker->ptnNext;
        if (ptnWalker == NULL) {
            return (-SYS_NO_NODE);
        }
        uiIndex++;
    } while (1);
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           treeInsertNodeFront
** Descriptions:            插入一个同级前置节点
** input parameters:        ptnBrother      兄弟节点
**                          ptnAdd          待增加节点                        
** output parameters:       SYS_OK
** Returned value:          >=0             成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S  treeInsertNodeFront(TREE_NODE *ptnBrother, TREE_NODE *ptnAdd)
{
    /*
     *  参数过滤
     */
    if ((NULL == ptnBrother) || (NULL == ptnAdd)) {
        return (-SYS_PARA_ERR);
    }  
    ptnAdd->ptnParent   = ptnBrother->ptnParent;
    ptnAdd->ptnNext     = ptnBrother;
    ptnAdd->ptnPrev     = ptnBrother->ptnPrev;
    ptnAdd->ptnChild    = NULL;
    if (ptnBrother->ptnPrev) {                                          /*  兄弟节点原前置节点有效      */
        ptnBrother->ptnPrev->ptnNext = ptnAdd;
    }
    
    ptnBrother->ptnPrev = ptnAdd;
    
    if (ptnAdd->ptnPrev == NULL) {                                      /*  同级首节点                  */
        if (ptnAdd->ptnParent) {
            ptnAdd->ptnParent->ptnChild = ptnAdd;
        }
    }
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           treeInsertNodePost
** Descriptions:            插入一个同级后置节点
** input parameters:        ptnBrother      兄弟节点
**                          ptnAdd          待增加节点                        
** output parameters:       SYS_OK
** Returned value:          >=0             成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S  treeInsertNodePost(TREE_NODE *ptnBrother, TREE_NODE *ptnAdd)
{
    /*
     *  参数过滤
     */
    if ((NULL == ptnBrother) || (NULL == ptnAdd)) {
        return (-SYS_PARA_ERR);
    }  
    ptnAdd->ptnParent   = ptnBrother->ptnParent;
    ptnAdd->ptnNext     = ptnBrother->ptnNext;
    ptnAdd->ptnPrev     = ptnBrother;
    ptnAdd->ptnChild    = NULL;
    if (ptnBrother->ptnNext) {                                          /*  兄弟节点原后置节点有效      */
        ptnBrother->ptnNext->ptnPrev = ptnAdd;
    }
    
    ptnBrother->ptnNext = ptnAdd;
    return SYS_OK;
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
