/****************************************Copyright (c)****************************************************
**                            
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               List.c
** Latest modified Date:    2014-12-05
** Latest Version:          1.0
** Descriptions:            链表数据结构实现
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2014-12-05
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

#include    ".\List.h"   

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


#if 0
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
INT32S  lsInit(__LIST_CB *plcb, INT32U uiMaxNode)
{
    int i;
    __SINGLE_LIST  *psls;
    /*
     *  参数过滤
     */
    if (NULL == plcb) {
        return (-SYS_PARA_ERR);
    }
    if (0 == uiMaxNode) {
        return (-SYS_PARA_ERR);
    }
    /*
     *  链表控制块数据初始化
     */
    memset(plcb, 0x00, sizeof(__LIST_CB) + uiMaxNode * sizeof(__SINGLE_LIST));
    plcb->pvFirstNode   = NULL;    
    plcb->pvFreeNode    = (void *)((INT32U)plcb + sizeof(__LIST_CB));
    plcb->uiMaxNode     = uiMaxNode;
    plcb->pls = plcb->pvFreeNode;
    psls = plcb->pls;
    /*  
     *  建立链表                    
     */
    for (i = 0; i < uiMaxNode - 1; i++) {                              
        psls[i].pslsNext = &psls[i + 1];
        
    }
    return SYS_OK;
}

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
INT32S  lsNodeAdd(__LIST_CB *plcb, void *pvData)
{
    int i;
    __SINGLE_LIST  *psls;
    /*
     *  参数过滤
     */
    if (NULL == plcb) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == pvData) {
        return (-SYS_PARA_ERR);
    }
    /*
     *  查找链表相同数据指针
     */
    psls = plcb->pvFirstNode;
    sysIrqDisable();
    do {
        if (NULL == psls) {
            break;
        }
        if (psls->pvData == pvData) {                                   /*  重复节点                    */
            sysIrqEnable();
            return (-SYS_NODE_EXIST);
        } else {
            psls = psls->pslsNext;
        }
    } while(1);
    psls = plcb->pvFreeNode;
    if (NULL == psls) {                                                 /*  链表无空闲节点              */
        return (-SYS_NODE_FULL);
    }
    psls->pvData = pvData;
    plcb->pvFreeNode = psls->pslsNext;
    psls->pslsNext = NULL;
        
    if (NULL == plcb->pvFirstNode) {                                    /*  链表节点未被占用            */
        plcb->pvFirstNode = psls;
    }
    
    sysIrqEnable();
    return SYS_OK;
}


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
INT32S  lsNodeDel(__LIST_CB *plcb, void *pvData)
{
    int i;
    __SINGLE_LIST  *psls, *pslsPrev = NULL;
    /*
     *  参数过滤
     */
    if (NULL == plcb) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == pvData) {
        return (-SYS_PARA_ERR);
    }
    /*
     *  查找链表相同数据指针
     */
    psls = plcb->pvFirstNode;
    sysIrqDisable();
    do {
        if (NULL == psls) {
            sysIrqEnable();
            return (-SYS_NO_NODE);
        }
        if (psls->pvData == pvData) {                                   /*  重复节点                    */
            break;
        } else {
            pslsPrev= psls;
            psls    = psls->pslsNext;
        }
    } while(1);
    
    
    if (NULL == pslsPrev) {                                             /*  删除首节点                  */
        plcb->pvFirstNode = psls->pslsNext;    
    } else {                                                            /*  删除中间节点                */
        pslsPrev->pslsNext = psls->pslsNext;
    }
    psls->pslsNext = plcb->pvFreeNode;
    plcb->pvFreeNode = psls;
    
    sysIrqEnable();
    return SYS_OK;
}
#endif
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
INT32S  dlsInit(__LIST_CB *plcb, INT32U uiMaxNode)
{
    int i;
    __DUAL_LIST  *pdls;
    /*
     *  参数过滤
     */
    if (NULL == plcb) {
        return (-SYS_PARA_ERR);
    }
    if (0 == uiMaxNode) {
        return (-SYS_PARA_ERR);
    }
    /*
     *  链表控制块数据初始化
     */
    memset(plcb, 0x00, sizeof(__LIST_CB) + uiMaxNode * sizeof(__DUAL_LIST));
    plcb->pvFirstNode   = NULL;    
    plcb->pvFreeNode    = (void *)((INT32U)plcb + sizeof(__LIST_CB));
    plcb->uiMaxNode     = uiMaxNode;
    plcb->pls = plcb->pvFreeNode;
    pdls = plcb->pls;
    /*  
     *  建立链表                    
     */
    for (i = 0; i < uiMaxNode - 1; i++) {                              
        pdls[i].pdlsNext = &pdls[i + 1];
        
    }
    for (i = uiMaxNode - 1; i > 0; i--) {
        pdls[i].pdlsPrev = &pdls[i - 1];
    }
    return SYS_OK;
}

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
INT32S  dlsNodeAdd(__LIST_CB *plcb, void *pvData)
{
    __DUAL_LIST  *pdls, *pdlsPrev;
    /*
     *  参数过滤
     */
    if (NULL == plcb) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == pvData) {
        return (-SYS_PARA_ERR);
    }
    /*
     *  查找链表相同数据指针
     */
    pdls        = plcb->pvFirstNode;
    pdlsPrev    = pdls;
    sysIrqDisable();
    do {
        if (NULL == pdls) {                                             /*  链表节点未被占用            */
            break;
        }
        if (pdls->pvData == pvData) {                                   /*  重复节点                    */
            sysIrqEnable();
            return (-SYS_NODE_EXIST);
        } else {
            pdlsPrev= pdls;
            pdls    = pdls->pdlsNext;
        }
    } while(1);
    
    if (NULL == plcb->pvFreeNode) {                                     /*  链表无空闲节点              */
        return (-SYS_NODE_FULL);
    }
    /*
     *  插入节点
     */    
    
    pdls = plcb->pvFreeNode;
    
    
    plcb->pvFreeNode = pdls->pdlsNext;
    pdls->pvData = pvData;      
    if (NULL != pdls->pdlsNext) {                                       /*  链表空闲首节点              */
        pdls->pdlsNext->pdlsPrev = NULL;
    }
    pdls->pdlsNext = NULL;
  
    if (NULL == plcb->pvFirstNode) {                                    /*  链表节点未被占用            */
        plcb->pvFirstNode = pdls;
    } else {                                                            /*  尾部插入                    */
        pdls->pdlsPrev      = pdlsPrev;
        pdlsPrev->pdlsNext  = pdls;
    }
    sysIrqEnable();
    return SYS_OK;
}


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
INT32S  dlsNodeDel(__LIST_CB *plcb, void *pvData)
{
    __DUAL_LIST  *pdls, *pdlsPrev = NULL;
    /*
     *  参数过滤
     */
    if (NULL == plcb) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == pvData) {
        return (-SYS_PARA_ERR);
    }
    /*
     *  查找链表相同数据指针
     */
    pdls = plcb->pvFirstNode;
    sysIrqDisable();
    do {
        if (NULL == pdls) {                                             /*  遍历全部非空闲节点          */
            sysIrqEnable();
            return (-SYS_NO_NODE);
        }
        if (pdls->pvData == pvData) {                                   /*  找到待删除节点              */
            break;
        } else {                                                        /*  查找下一个节点              */
            pdlsPrev= pdls;
            pdls    = pdls->pdlsNext;
        }
    } while(1);
    
    
    if (NULL == pdlsPrev) {                                             /*  删除首节点                  */
        plcb->pvFirstNode = pdls->pdlsNext;    
        if (pdls->pdlsNext) {                                           /*  新的首节点前向指针NULL      */
        	pdls->pdlsNext->pdlsPrev = NULL;
        }
    } else {                                                            /*  删除中间节点                */
        pdlsPrev->pdlsNext = pdls->pdlsNext;
        if (pdls->pdlsNext) {
            pdls->pdlsNext->pdlsPrev = pdlsPrev;
        }
        pdls->pdlsPrev = NULL;
    }
    pdls->pdlsNext = plcb->pvFreeNode;
    
    //pdls->pdlsNext->pdlsPrev = pdls;
    if (plcb->pvFreeNode) {
        ((__DUAL_LIST *)plcb->pvFreeNode)->pdlsPrev = pdls;
    }
    plcb->pvFreeNode = pdls;
    
    sysIrqEnable();
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           dlsNodeInsert
** Descriptions:            双链表插入一个节点
** input parameters:        plcb            双链表控制块指针
**                          pvDataTail      插入尾随位置
**                          pvData          待插入节点的数据指针
**                         
**                          
** output parameters:       SYS_OK
** Returned value:          >=0             成功
**                          负数            错误,绝对值参考afxMenu.h
*********************************************************************************************************/
INT32S  dlsNodeInsert(__LIST_CB *plcb, void *pvDataTail, void *pvData)
{
    __DUAL_LIST  *pdlsTail, *pdls;
    /*
     *  参数过滤
     */
    if (NULL == plcb) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == pvDataTail) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == pvData) {
        return (-SYS_PARA_ERR);
    }
    
    if (NULL == plcb->pvFirstNode) {
        return (-SYS_NO_NODE);
    }
    
    /*
     *  查找插入位置
     */
    pdlsTail    = plcb->pvFirstNode;
    sysIrqDisable();
    do {
        if (NULL == pdlsTail) {                                         /*  链表节点不存在              */
            sysIrqEnable();
            return (-SYS_NO_NODE);
        }
        if (pdlsTail->pvData == pvDataTail) {                           /*  找到插入位置                */
            break;
        } else {
            pdlsTail    = pdlsTail->pdlsNext;
        }
    } while(1);
    /*
     *  查找待插入节点
     */
    pdls        = plcb->pvFreeNode;
    do {
        if (NULL == pdls) {                                             /*  链表节点存在                */
            sysIrqEnable();
            return (-SYS_NODE_EXIST);
        }
        if (pdls->pvData == pvData) {                                   /*  找到插入位置                */
            break;
        } else {
            pdls    = pdls->pdlsNext;
        }
    } while(1);
    
    /*
     *  插入节点
     */    
    
    pdlsTail->pdlsNext  = pdls;
    pdls->pdlsPrev      = pdlsTail;
     
    if (NULL != pdls->pdlsPrev) {                                       /*  链表空闲首节点              */
        pdls->pdlsPrev->pdlsNext = pdls->pdlsNext;
    } 
    if (NULL != pdls->pdlsNext) {
        pdls->pdlsNext->pdlsPrev = pdls->pdlsPrev;
    }
    sysIrqEnable();
    return SYS_OK;
}
/*********************************************************************************************************
** Function name:           dlsNodeAdd
** Descriptions:            双链表增加一个节点
** input parameters:        plcb            双链表控制块指针
**                          pvData          节点的数据指针
**                         
**                          
** output parameters:       pdlsRtn         节点指针
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考afxMenu.h
*********************************************************************************************************/
INT32S  dlsNodeFind(__DUAL_LIST *pdlsRtn, __LIST_CB *plcb, void *pvData)
{
    __DUAL_LIST            *pdls;
    /*
     *  参数过滤
     */
    if (NULL == pdlsRtn) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == plcb) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == pvData) {
        return (-SYS_PARA_ERR);
    }
    pdls = plcb->pvFirstNode;
    sysIrqDisable();
    do {
        if (NULL == pdls) {                                             /*  搜寻完成                    */
            sysIrqEnable();
            return (-SYS_NO_NODE);
        }
        if (pdls->pvData == pvData) {
            break;
        }
        pdls = pdls->pdlsNext;
    } while(1);
    
    sysIrqEnable();
    pdlsRtn = pdls;
    return SYS_OK;
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
