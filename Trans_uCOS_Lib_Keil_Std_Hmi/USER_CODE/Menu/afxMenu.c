/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn   
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               afxMenu.c
** Latest modified Date:    2014-12-05
** Latest Version:          1.0
** Descriptions:            
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

#include "..\main.h"


/*********************************************************************************************************
  外部声明
*********************************************************************************************************/


/*********************************************************************************************************
  函数声明
*********************************************************************************************************/
static INT32S __menuItemCreate(MENU_ITEM_INFO *pmiibThis);
static INT32S __menuItemDel(MENU_ITEM_INFO *pmiibThis);


/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/
BOOLEAN         __GucEntered;                                           /*  参数修改状态标识            */
TREE_NODE      *__GptnRootMenu;                                         /*  菜单根节点                  */
TREE_NODE      *__GptnCurMenu;                                          /*  当前菜单节点                */


/*********************************************************************************************************
  内部使用变量
*********************************************************************************************************/
const MENU_ITEM_FUNC GmifRoot = {
    __menuItemCreate,
    __menuItemDel,
    NULL,
    NULL
};

static const  char *const __SscStr[4] = {   "  请输入新密码  ",
                                            "请再次输入新密码",    
                                            " 新密码设置成功 ",
                                            " 新密码设置失败 "};

INT8U    __SucIndex;  
static char   __SscParamFmt[32];                                            
/*********************************************************************************************************
** Function name:           menuItemCreate
** Descriptions:            创建菜单项
** input parameters:        pmiiThis    菜单项信息
** output parameters:       none
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考afxMenu.h
*********************************************************************************************************/
static INT32S __menuItemCreate (MENU_ITEM_INFO *pmiiThis)
{
    INT32S      siErr = 0;
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
    *  ............
    */
    
    return siErr;
}

/*********************************************************************************************************
** Function name:           menuItemDel
** Descriptions:            删除菜单项
** input parameters:        pmiiThis    菜单项信息
** output parameters:       none
** Returned value:          SYS_OK      成功
**                          负数        错误,绝对值参考afxMenu.h
*********************************************************************************************************/
static INT32S __menuItemDel (MENU_ITEM_INFO *pmiiThis)
{
    INT32S      siErr = 0;
    pmiiThis = pmiiThis;
   /*  
    *  添加用户代码        
    *  ............
    */
    mainDisplay();
    Gds.ucIsAuthorized = FALSE;
    return siErr;    
}
/*********************************************************************************************************
  根节点菜单项定义
*********************************************************************************************************/
const MENU_ITEM_INFO_BASE __GmiibRoot = {                               /*  菜单项信息                  */
    "设置",
    (MENU_ITEM_FUNC *)&GmifRoot,
    0x0000
};
#if 0
/*********************************************************************************************************
** Function name:           miRootInit
** Descriptions:            根菜单节点初始化
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miRootInit(void)
{ 
    /*
     *  添加菜单
     */
    miAdd(NULL, &__GmiibRoot);
}
/*********************************************************************************************************
** Function name:           mpRootDel
** Descriptions:            根菜单节点卸载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void miRootDel (void)
{ 
    /*
     *  删除菜单页
     */
    miDel(&__GmiibRoot);
}
#endif

/*********************************************************************************************************
** Function name:           kbd2Ascii
** Descriptions:            键码转换为ascii码
** input parameters:        uiKbdCode           键码
**                          
** output parameters:       none
** Returned value:          ascii码
**                          
*********************************************************************************************************/
INT8U kbd2Ascii(INT32U  uiKbdCode)
{
    switch (uiKbdCode) {
        case JP_0:
            return '0';
        
        case JP_1:
            return '1';
        
        case JP_2:
            return '2';
        
        case JP_3:
            return '3';
        
        case JP_4:
            return '4';
        
        case JP_5:
            return '5';
        
        case JP_6:
            return '6';
        
        case JP_7:
            return '7';
        
        case JP_8:
            return '8';
        
        case JP_9:
            return '9';
        
        default:
            return 0;        
    }
}
/*********************************************************************************************************
** Function name:           miIsExist
** Descriptions:            检查菜单是否已存在
** input parameters:        ptnParent       父节点
**                          pmiib           待检查的菜单项
** output parameters:       none
** Returned value:          !NULL           存在
**                          NULL            不存在
*********************************************************************************************************/
static TREE_NODE* __miIsExist(TREE_NODE *ptnParent, const MENU_ITEM_INFO_BASE *pmiib)
{
    TREE_NODE      *ptnRtn = NULL;
    TREE_NODE     **pptnWalker;
    MENU_ITEM_INFO *pmii;
    /*
     *  参数过滤
     */
    if ((NULL == pmiib) ||
        (NULL == ptnParent)) {
        return NULL;
    }
    
    pptnWalker = &ptnParent;//->ptnChild;
    while (*pptnWalker) {
        pmii = (*pptnWalker)->pvData;                             
        if (pmii->pmiib == pmiib) {                                     /*  节点已经存在                */
            ptnRtn = *pptnWalker;
            break;
        } else if ((*pptnWalker)->ptnChild) {
            ptnRtn = __miIsExist((*pptnWalker)->ptnChild, pmiib);
            if (ptnRtn) {
                break;
            } else {
                pptnWalker = &(*pptnWalker)->ptnNext;
            }
        } else {
            pptnWalker = &(*pptnWalker)->ptnNext;
        }
    }
    return ptnRtn;
}

/*********************************************************************************************************
** Function name:           __miAdd
** Descriptions:            增加菜单页
** input parameters:        pmiParent       父菜单项节点
**                          pmiib           要增加的菜单项
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __miAdd(TREE_NODE *ptnRoot, const MENU_ITEM_INFO_BASE *pmiibParent, const MENU_ITEM_INFO_BASE *pmiibAdd)
{
    TREE_NODE      *ptnParent;
    TREE_NODE      *ptnAdd;
    INT32S          siErr;   
    /*
     *  参数过滤
     */        
    if ((NULL == pmiibAdd) ||
        (NULL == ptnRoot)) {                                               
        return (-SYS_PARA_ERR);
    }
    if (NULL == pmiibAdd->pmifFunc) {                                   /*  端口函数列表无效            */
        return (-SYS_PARA_ERR);
    }
    
    /*
     *  寻找父节点
     */
    //ptnRoot = __GptnRootMenu;
    ptnParent = __miIsExist(ptnRoot, pmiibParent);
    if (NULL == ptnParent) {                                            /*  父节点不存在                */
        return (-SYS_NO_NODE);
    }
    
    /*
     *  查找重复节点
     */
    if (__miIsExist(ptnRoot, pmiibAdd)) {                                 /*  待插入节点已存在            */
        return (-SYS_NODE_EXIST);
    }

    /*
     *  添加节点
     */
    
    ptnAdd = sysHeapMalloc(sizeof(TREE_NODE));
    if (NULL == ptnAdd) {
        return (-SYS_NO_MEMORY);
    }
    memset(ptnAdd, 0x00, sizeof(TREE_NODE));
    
    (ptnAdd)->pvData = sysHeapMalloc(sizeof(MENU_ITEM_INFO));
    if (NULL == ptnAdd->pvData) {
        sysHeapFree(ptnAdd);
        return (-SYS_NO_MEMORY);
    }
    memset(ptnAdd->pvData, 0x00, sizeof(MENU_ITEM_INFO));

    ((MENU_ITEM_INFO *)ptnAdd->pvData)->pmiib = pmiibAdd; 

    if (ptnParent) {
        sysIrqDisable();
        siErr = treeAddNode(ptnParent, ptnAdd);
        sysIrqEnable();

        if (siErr < 0) {
            sysHeapFree((ptnAdd)->pvData);
            sysHeapFree(ptnAdd);
            return siErr;
        }
    } else {
        ;
    }
    if (pmiibAdd->pmifFunc->pfuncCreate) {
        return pmiibAdd->pmifFunc->pfuncCreate(ptnAdd->pvData);
    }    
    return SYS_OK;
}


/*********************************************************************************************************
** Function name:           __miInsertPrev
** Descriptions:            同级在指定菜单项的前面插入菜单
** input parameters:        pmiBrother      同级菜单项节点
**                          pmiib           要增加的菜单项
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __miInsertPrev(TREE_NODE *ptnRoot, const MENU_ITEM_INFO_BASE *pmiibBrother, const MENU_ITEM_INFO_BASE *pmiibAdd)
{
    TREE_NODE      *ptnBrother;
    TREE_NODE      *ptnAdd;
    INT32S          siErr;   
    /*
     *  参数过滤
     */        
    if ((NULL == pmiibAdd) ||
        (NULL == pmiibBrother) ||
        (NULL == ptnRoot)) {                                               
        return (-SYS_PARA_ERR);
    }
    if (NULL == pmiibAdd->pmifFunc) {                                   /*  端口函数列表无效            */
        return (-SYS_PARA_ERR);
    }
    
    /*
     *  寻找父节点
     */
    ptnBrother = __miIsExist(ptnRoot, pmiibBrother);
    if (NULL == ptnBrother) {                                           /*  兄弟节点不存在              */
        return (-SYS_NO_NODE);
    }
    
    /*
     *  查找重复节点
     */
    if (__miIsExist(ptnRoot, pmiibAdd)) {                               /*  待插入节点已存在            */
        return (-SYS_NODE_EXIST);
    }

    /*
     *  添加节点
     */
    
    ptnAdd = sysHeapMalloc(sizeof(TREE_NODE));
    if (NULL == ptnAdd) {
        return (-SYS_NO_MEMORY);
    }
    memset(ptnAdd, 0x00, sizeof(TREE_NODE));
    
    (ptnAdd)->pvData = sysHeapMalloc(sizeof(MENU_ITEM_INFO));
    if (NULL == ptnAdd->pvData) {
        sysHeapFree(ptnAdd);
        return (-SYS_NO_MEMORY);
    }
    memset(ptnAdd->pvData, 0x00, sizeof(MENU_ITEM_INFO));

    ((MENU_ITEM_INFO *)ptnAdd->pvData)->pmiib = pmiibAdd; 


    sysIrqDisable();
    siErr = treeInsertNodeFront(ptnBrother, ptnAdd);
    sysIrqEnable();

    if (siErr < 0) {
        sysHeapFree((ptnAdd)->pvData);
        sysHeapFree(ptnAdd);
        return siErr;
    }

    if (pmiibAdd->pmifFunc->pfuncCreate) {
        return pmiibAdd->pmifFunc->pfuncCreate(ptnAdd->pvData);
    }    
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           __miInsertNext
** Descriptions:            同级在指定菜单项的后面插入菜单
** input parameters:        pmiBrother      同级菜单项节点
**                          pmiib           要增加的菜单项
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __miInsertNext(TREE_NODE *ptnRoot, const MENU_ITEM_INFO_BASE *pmiibBrother, const MENU_ITEM_INFO_BASE *pmiibAdd)
{
    TREE_NODE      *ptnBrother;
    TREE_NODE      *ptnAdd;
    INT32S          siErr;   
    /*
     *  参数过滤
     */        
    if ((NULL == pmiibAdd) ||
        (NULL == pmiibBrother) ||
        (NULL == ptnRoot)) {                                               
        return (-SYS_PARA_ERR);
    }
    if (NULL == pmiibAdd->pmifFunc) {                                   /*  端口函数列表无效            */
        return (-SYS_PARA_ERR);
    }
    
    /*
     *  寻找父节点
     */
    ptnBrother = __miIsExist(ptnRoot, pmiibBrother);
    if (NULL == ptnBrother) {                                           /*  兄弟节点不存在              */
        return (-SYS_NO_NODE);
    }
    
    /*
     *  查找重复节点
     */
    if (__miIsExist(ptnRoot, pmiibAdd)) {                               /*  待插入节点已存在            */
        return (-SYS_NODE_EXIST);
    }

    /*
     *  添加节点
     */
    
    ptnAdd = sysHeapMalloc(sizeof(TREE_NODE));
    if (NULL == ptnAdd) {
        return (-SYS_NO_MEMORY);
    }
    memset(ptnAdd, 0x00, sizeof(TREE_NODE));
    
    (ptnAdd)->pvData = sysHeapMalloc(sizeof(MENU_ITEM_INFO));
    if (NULL == ptnAdd->pvData) {
        sysHeapFree(ptnAdd);
        return (-SYS_NO_MEMORY);
    }
    memset(ptnAdd->pvData, 0x00, sizeof(MENU_ITEM_INFO));

    ((MENU_ITEM_INFO *)ptnAdd->pvData)->pmiib = pmiibAdd; 


    sysIrqDisable();
    siErr = treeInsertNodePost(ptnBrother, ptnAdd);
    sysIrqEnable();

    if (siErr < 0) {
        sysHeapFree((ptnAdd)->pvData);
        sysHeapFree(ptnAdd);
        return siErr;
    }

    if (pmiibAdd->pmifFunc->pfuncCreate) {
        return pmiibAdd->pmifFunc->pfuncCreate(ptnAdd->pvData);
    }    
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           miAdd
** Descriptions:            增加菜单页
** input parameters:        pmiParent       父菜单项节点
**                          pmiib           要增加的菜单项
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S miAdd(const MENU_ITEM_INFO_BASE *pmiibParent, const MENU_ITEM_INFO_BASE *pmiibAdd)
{
    if (!__GptnRootMenu) {                                                 /*  根节点                      */
        TREE_NODE *ptnRoot;
        if (__GptnRootMenu) {                                           /*  根节点存在                  */
            return (-SYS_NODE_EXIST);
        }
        ptnRoot = sysHeapMalloc(sizeof(TREE_NODE));
        if (NULL == ptnRoot) {
            return (-SYS_NO_MEMORY);
        }
        memset(ptnRoot, 0x00, sizeof(TREE_NODE));
        
        ptnRoot->pvData = sysHeapMalloc(sizeof(MENU_ITEM_INFO));
        if (NULL == ptnRoot->pvData) {
            sysHeapFree(ptnRoot);
            return (-SYS_NO_MEMORY);
        }
        memset(ptnRoot->pvData, 0x00, sizeof(MENU_ITEM_INFO));
        ((MENU_ITEM_INFO *)ptnRoot->pvData)->pmiib = &__GmiibRoot;//pmiibAdd; 
        __GptnRootMenu = ptnRoot;
        if (__GmiibRoot.pmifFunc->pfuncCreate) {
            __GmiibRoot.pmifFunc->pfuncCreate(ptnRoot->pvData);
        }        
    }
    return __miAdd(__GptnRootMenu, pmiibParent, pmiibAdd);
}    

/*********************************************************************************************************
** Function name:           __miDel
** Descriptions:            删除以本菜单项为根节点的菜单树
** input parameters:        ptnDel         待删除菜单项
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __miDel(TREE_NODE *ptnDel)
{
    MENU_ITEM_INFO *pmiiDel;
    
    TREE_NODE     **pptnWalker;

    INT32S          siErr = 0;
    /*
     *  参数过滤
     */        
    if (NULL == ptnDel) {
        return (-SYS_PARA_ERR);
    }
    
    pptnWalker = &ptnDel; 
    
    //while (*pptnWalker) {
        while ((*pptnWalker)->ptnChild) {                                  /*  存在子节点                  */
            __miDel((*pptnWalker)->ptnChild);
        }
    //}
    //    ptnDel = *pptnWalker;
        pmiiDel = (MENU_ITEM_INFO *)ptnDel->pvData;
        
        if (pmiiDel->pmiib->pmifFunc->pfuncDel) {                       /*  端口卸载函数有效            */
            pmiiDel->pmiib->pmifFunc->pfuncDel(pmiiDel);
        }
        sysHeapFree(pmiiDel);
        //ptnDel->pvData = NULL;
        sysIrqDisable();                                                /*  进入临界段代码              */
        siErr = treeDelNode(ptnDel);
        sysIrqEnable();                                                 /*  退出临界段代码              */       
        if (siErr < 0)
    //        break;
        while (1);
        sysHeapFree(ptnDel);
    //    pptnWalker = &(*pptnWalker)->ptnNext;
    //}
    
    return siErr;
}
/*********************************************************************************************************
** Function name:           miDel
** Descriptions:            删除菜单项
** input parameters:        ptnRoot         菜单项根节点
**                          pmiib           待删除菜单项
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S miDel(const MENU_ITEM_INFO_BASE *pmiibDel)
{
    TREE_NODE      *ptnDel;
    MENU_ITEM_INFO *pmiiRoot;
    INT32S          siErr;
    INT8U           ucIsRoot = 0;
    /*
     *  参数过滤
     */
    if (NULL == pmiibDel) {
        return (-SYS_PARA_ERR);
    }
    
    if (NULL == __GptnRootMenu) {                                       /*  菜单树不存在                */          
        return (-SYS_NO_NODE);
    }
    pmiiRoot = (MENU_ITEM_INFO *)__GptnRootMenu->pvData;
    //ucIsRoot = pmiiRoot->pmiib == pmiibDel;
    
    ptnDel = __miIsExist(__GptnRootMenu, pmiibDel);
    if (NULL == ptnDel) {
        return (-SYS_NO_NODE);
    }
    if (((ptnDel->ptnNext == NULL) && (ptnDel->ptnPrev == NULL) &&
        (ptnDel->ptnParent == __GptnRootMenu)) ||
        (ptnDel == __GptnRootMenu)) {
        ucIsRoot = TRUE;
    }
    siErr = __miDel(ptnDel);
    if (siErr < 0) {
        return siErr;
    }
    
    if  (ucIsRoot) {                                                    /*  删除根节点                  */
        if (ptnDel == __GptnRootMenu) {                                 /*  根节点已删除                */
            ;
        } else {
            __miDel(__GptnRootMenu);
        }
        __GptnRootMenu = NULL;
        __GptnCurMenu = NULL;
    }
    return siErr;
}
/*********************************************************************************************************
** Function name:           __miDelTail
** Descriptions:            删除以本菜单项为根节点的菜单树兄弟节点从尾部开始删
** input parameters:        ptnDel         待删除菜单项
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
static INT32S __miDelTail(TREE_NODE *ptnDel)
{
    MENU_ITEM_INFO *pmiiDel;
    
    TREE_NODE     **pptnWalker;

    INT32S          siErr = 0;
    /*
     *  参数过滤
     */        
    if (NULL == ptnDel) {
        return (-SYS_PARA_ERR);
    }
    
    
    /*
     *  删除子节点
     */
    while (ptnDel->ptnChild) {
        TREE_NODE *ptnDelTemp;
        pptnWalker = &ptnDel->ptnChild;
        /*
         *  查找兄弟中的尾部节点
         */
        while ((*pptnWalker)->ptnNext) {
            pptnWalker = &(*pptnWalker)->ptnNext;
        }
        if ((*pptnWalker)->ptnChild) {                                  /*  存在子节点                  */
            __miDelTail((*pptnWalker));
        }
        ptnDelTemp = *pptnWalker;
        pmiiDel = (MENU_ITEM_INFO *)(*pptnWalker)->pvData;
        
        if (pmiiDel->pmiib->pmifFunc->pfuncDel) {                       /*  端口卸载函数有效            */
            pmiiDel->pmiib->pmifFunc->pfuncDel(pmiiDel);
        }
        sysHeapFree(pmiiDel);
        sysIrqDisable();                                                /*  进入临界段代码              */
        siErr = treeDelNode(ptnDelTemp);
        sysIrqEnable();                                                 /*  退出临界段代码              */       
        if (siErr < 0)
            return siErr;
        sysHeapFree(ptnDelTemp);
    }
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           miDel
** Descriptions:            删除菜单项
** input parameters:        ptnRoot         菜单项根节点
**                          pmiib           待删除菜单项
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S miDelTail(const MENU_ITEM_INFO_BASE *pmiibDel)
{
    TREE_NODE      *ptnDel;
    MENU_ITEM_INFO *pmiiRoot;
    INT32S          siErr;
    INT8U           ucIsRoot;
    /*
     *  参数过滤
     */
    if (NULL == pmiibDel) {
        return (-SYS_PARA_ERR);
    }
    
    if (NULL == __GptnRootMenu) {                                       /*  菜单树不存在                */          
        return (-SYS_NO_NODE);
    }
    pmiiRoot = (MENU_ITEM_INFO *)__GptnRootMenu->pvData;
    ucIsRoot = pmiiRoot->pmiib == pmiibDel;
    
    ptnDel = __miIsExist(__GptnRootMenu, pmiibDel);
    if (NULL == ptnDel) {
        return (-SYS_NO_NODE);
    }
    siErr = __miDelTail(ptnDel);
    if (siErr < 0) {
        return siErr;
    }

    /*
     *  删除自身节点
     */
    pmiiRoot = (MENU_ITEM_INFO *)ptnDel->pvData;
    
    if (pmiiRoot->pmiib->pmifFunc->pfuncDel) {                       /*  端口卸载函数有效            */
        pmiiRoot->pmiib->pmifFunc->pfuncDel(pmiiRoot);
    }
    sysHeapFree(pmiiRoot);
    sysIrqDisable();                                                /*  进入临界段代码              */
    siErr = treeDelNode(ptnDel);
    sysIrqEnable();                                                 /*  退出临界段代码              */       
    if (siErr < 0)
        return siErr;
    sysHeapFree(ptnDel);

    if  (ucIsRoot) {                                                    /*  删除根节点                  */
        __GptnRootMenu = NULL;
    }
    return siErr;
}

/*********************************************************************************************************
** Function name:           miInsertPrev
** Descriptions:            增加前置菜单页
** input parameters:        pmiibBrother    兄弟菜单项节点
**                          pmiibAdd        要增加的菜单项
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S miInsertPrev(const MENU_ITEM_INFO_BASE *pmiibBrother, const MENU_ITEM_INFO_BASE *pmiibAdd)
{
        /*
     *  参数过滤
     */        
    if ((NULL == pmiibAdd) ||
        (NULL == pmiibBrother)) {                                               
        return (-SYS_PARA_ERR);
    }
    if (NULL == pmiibAdd->pmifFunc) {                                   /*  端口函数列表无效            */
        return (-SYS_PARA_ERR);
    }
    if (__GptnRootMenu == NULL) {
        return (-SYS_NO_NODE);
    }
    return __miInsertPrev(__GptnRootMenu, pmiibBrother, pmiibAdd);
}
    

/*********************************************************************************************************
** Function name:           miInsertNext
** Descriptions:            增加后置菜单页
** input parameters:        pmiibBrother    兄弟菜单项节点
**                          pmiibAdd        要增加的菜单项
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S miInsertNext(const MENU_ITEM_INFO_BASE *pmiibBrother, const MENU_ITEM_INFO_BASE *pmiibAdd)
{
        /*
     *  参数过滤
     */        
    if ((NULL == pmiibAdd) ||
        (NULL == pmiibBrother)) {                                               
        return (-SYS_PARA_ERR);
    }
    if (NULL == pmiibAdd->pmifFunc) {                                   /*  端口函数列表无效            */
        return (-SYS_PARA_ERR);
    }
    if (__GptnRootMenu == NULL) {
        return (-SYS_NO_NODE);
    }
    return __miInsertNext(__GptnRootMenu, pmiibBrother, pmiibAdd);
}


/*********************************************************************************************************
** Function name:           miFlush
** Descriptions:            清空所有菜单项
** input parameters:        ptnRoot         菜单根节点
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S miFlush(void)
{
    if (NULL == __GptnRootMenu) {
        return (-SYS_NO_NODE);
    }
    /*
     *  两种菜单树的删除都可用
     */
    //if (miDelTail(((MENU_ITEM_INFO *)__GptnRootMenu->pvData)->pmiib) < 0) {
    //    while (1);
    //}
    if (miDel(((MENU_ITEM_INFO *)__GptnRootMenu->pvData)->pmiib) < 0) {
        while (1);
    }
    __GucEntered = FALSE;
    __SucIndex = 0;
    __GptnCurMenu = NULL;
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           miGetIndex
** Descriptions:            获取指定菜单项在所属页中的索引
** input parameters:        ptnMenu         菜单根节点
** output parameters:       puiRtn          索引返回指针
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S miGetIndex(TREE_NODE *ptn, INT32U *puiRtn)
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
    return treeGetIndex(ptn, puiRtn);
}


/*********************************************************************************************************
** Function name:           miIsExist
** Descriptions:            检查菜单是否已存在
** input parameters:        ptnParent       父节点
**                          pmiib           待检查的菜单项
** output parameters:       none
** Returned value:          TRUE            存在
**                          FALSE           不存在
*********************************************************************************************************/
BOOLEAN miIsExist(const MENU_ITEM_INFO_BASE *pmiib)
{
    if (__miIsExist(__GptnRootMenu, pmiib)) {
        return TRUE;
    } else {
        return FALSE;
    }
}
/*********************************************************************************************************
** Function name:           mpDisplay
** Descriptions:            显示菜单页内容
** input parameters:        pmpiInfo        菜单页信息
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S mpDisplay(TREE_NODE *ptnParent)
{
    int i;
    TREE_NODE                  *ptnWalker;
    MENU_ITEM_INFO             *pmii;
    /*
     *  参数过滤
     */
    if (NULL == ptnParent) {
        return (-SYS_PARA_ERR);
    }
    pmii = (MENU_ITEM_INFO *)ptnParent->pvData;
    guiClrScr();
    guiPrintf((128 - 8 * strlen(pmii->pmiib->pcTitle)) / 2, 0, 0, (char *)pmii->pmiib->pcTitle);                  /*  显示菜单页标题              */
    /*
     *  显示菜单项,2项/页
     */
    ptnWalker = ptnParent->ptnChild;

    for (i = 0; i < MAX_MENU_ITEM_PER_PAGE; i++) {
        char scParamFmt[32] = { 0 };
        char scStr[64] = {0};
        if (NULL == ptnWalker) {
            break;
        }
        pmii = ptnWalker->pvData;
        strcpy(scStr, pmii->pmiib->pcTitle);
        if (NULL != pmii->pmiib->pmifFunc->pfuncParamFmt) {
            pmii->pmiib->pmifFunc->pfuncParamFmt(pmii, scParamFmt);
        }
        strcat(scStr, scParamFmt);
        /*
         *  显示菜单项标题              
         */

        guiPrintf(0, CAPTION_YSPACE + MENU_ITEM_INTERVAL * i, __GptnCurMenu == ptnWalker, scStr);

        

        pmii->ucX = 0;
        pmii->ucY = CAPTION_YSPACE + MENU_ITEM_INTERVAL * i;

        ptnWalker = ptnWalker->ptnNext;
    }
    
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           mpDisplayEx
** Descriptions:            菜单页增量显示
** input parameters:        pmpiInfo        菜单页信息
**                          ucCurIndex      菜单页起始显示菜单项
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S mpDisplayEx(TREE_NODE *ptnParent, INT8U ucCurIndex)
{
    int i;
    MENU_ITEM_INFO             *pmii;
    TREE_NODE                  *ptnWalker;
    /*
     *  参数过滤
     */
    if (NULL == ptnParent) {
        return (-SYS_PARA_ERR);
    }
    pmii = (MENU_ITEM_INFO *)ptnParent->pvData;
    
    guiClrScr();
    
    guiPrintf((128 - 8 * strlen(pmii->pmiib->pcTitle)) / 2, 0, 0, (char *)pmii->pmiib->pcTitle);                  /*  显示菜单页标题              */    
    
    ptnWalker = ptnParent->ptnChild;
    for (i = 0; i < ucCurIndex; i++) {
        if (NULL == ptnWalker) {
            return (-SYS_NOT_OK);
        }
        ptnWalker = ptnWalker->ptnNext;
    }
    /*
     *  显示菜单项
     */
    pmii = (MENU_ITEM_INFO *)ptnWalker->pvData; 
    for (i = 0; i < MAX_MENU_ITEM_PER_PAGE; i++) {                      /*  显示菜单项                  */
        char scParamFmt[32] = { 0 };
        char scStr[64] = {0};
        if (NULL == ptnWalker) {
            break;
        }
        pmii = (MENU_ITEM_INFO *)ptnWalker->pvData;
        strcpy(scStr, pmii->pmiib->pcTitle);
        if (NULL != pmii->pmiib->pmifFunc->pfuncParamFmt) {
            pmii->pmiib->pmifFunc->pfuncParamFmt(pmii, scParamFmt);
        }
        strcat(scStr, scParamFmt);
        if (__GptnCurMenu == ptnWalker) {                               /*  当前菜单项                  */
            guiPrintf(0, CAPTION_YSPACE + MENU_ITEM_INTERVAL * i, 1, scStr);                       /*  显示菜单项标题              */
        } else {
            guiPrintf(0, CAPTION_YSPACE + MENU_ITEM_INTERVAL * i, 0, scStr);                       /*  显示菜单项标题              */
        }
        pmii->ucX = 0;
        pmii->ucY = CAPTION_YSPACE + MENU_ITEM_INTERVAL * i;
        ptnWalker = ptnWalker->ptnNext;
        
    }
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           mpHome
** Descriptions:            显示菜单首页
** input parameters:        none        
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S mpHome(void)
{   
    INT32S      siErr;
    /*
     *  参数过滤
     */
    if (NULL == __GptnRootMenu) {
        return (-SYS_NO_NODE);
    }
    
    if (NULL != __GptnRootMenu->ptnChild) {
        if (__GptnRootMenu->ptnChild->ptnChild) {
            __GptnCurMenu = __GptnRootMenu->ptnChild->ptnChild;
        } else {
            __GptnCurMenu = __GptnRootMenu->ptnChild;
        }
        siErr = mpDisplay(__GptnRootMenu->ptnChild); 
    } else {
        __GptnCurMenu = __GptnRootMenu;
        siErr = mpDisplay(__GptnRootMenu);
    }
    return siErr;
}

/*********************************************************************************************************
** Function name:           miOnKey
** Descriptions:            菜单项按键响应函数
** input parameters:        pmpiThis        菜单页信息      
**                          usLen           数据长度
**                          pvData          数据指针
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S  miOnKey(INT32U uiKeyCode)
{
    TREE_NODE         **pptnWalker;
    MENU_ITEM_INFO     *pmii;
    
    INT8U               ucMenuIndex = 0;
    INT32U              uiTmp;
    /*
     *  参数过滤
     */
    
    pmii      = (MENU_ITEM_INFO *)__GptnCurMenu->pvData;
    
    if (__GptnCurMenu->ptnParent == __GptnRootMenu) {                   /*  只有根节点菜单              */
        //return pmii->pmiib->pmifFunc->pfuncOnkey(pmii, uiKeyCode);
        if (pmii->pmiib->pmifFunc->pfuncOnkey) {
            pmii->pmiib->pmifFunc->pfuncOnkey(pmii, uiKeyCode);
        }
        return;
    }
    // if (__GucEntered) {                                                 
    //     return pmii->pmiib->pmifFunc->pfuncOnkey(pmii, uiKeyCode);
    // }
    /*
     *  根据不同按键预备pptnWalker
     */
    if  ((uiKeyCode == GpuiKeyTbl[KEY_MENU_LEFT]) ||
         (uiKeyCode == GpuiKeyTbl[KEY_MENU_RIGHT])) {                   /*  左右键                      */
        if (__GptnCurMenu->ptnParent == __GptnRootMenu) {               /*  无子菜单                    */
            pptnWalker = &__GptnCurMenu;
        } else {                                                        /*  有子菜单                    */
            pptnWalker = &__GptnCurMenu->ptnParent;                     /*  菜单页                      */
        }
    } else {                                                            /*  其他按键                    */
        if (__GptnCurMenu->ptnParent == __GptnRootMenu) {               /*  无子菜单                    */
            //*pptnWalker = NULL;                                       /*  这个逻辑会死机              */
            if (pmii->pmiib->pmifFunc->pfuncOnkey) {
                return pmii->pmiib->pmifFunc->pfuncOnkey(pmii, uiKeyCode);
            }
        } else {                                                        /*  有子菜单                    */
            pptnWalker = &__GptnCurMenu->ptnParent->ptnChild;           /*  菜单项                      */
        }
    }

    /*
     *  按键处理流程
     */
    if (uiKeyCode == GpuiKeyTbl[KEY_MENU_UP]) {                         /*  上一个菜单项                */ 
        if (*pptnWalker == NULL) {
            ;
        } else if (__GptnCurMenu == (*pptnWalker)) {                    /*  上翻到顶                    */
            sysIrqDisable();
            do {                    
                if ((*pptnWalker)->ptnNext == NULL) {
                    __GptnCurMenu = *pptnWalker;
                    break;
                } else {
                    pptnWalker = &(*pptnWalker)->ptnNext;  
                    ucMenuIndex++;
                }
            } while (1);
            sysIrqEnable();
        } else {
            sysIrqDisable();
            do {                    
                if ((*pptnWalker)->ptnNext == __GptnCurMenu) {
                    __GptnCurMenu = *pptnWalker;
                    break;
                } else {
                    pptnWalker = &(*pptnWalker)->ptnNext;  
                    ucMenuIndex++;
                }
            } while (1);
            sysIrqEnable(); 
        }
        mpDisplayEx(__GptnCurMenu->ptnParent, (ucMenuIndex / MAX_MENU_ITEM_PER_PAGE) * MAX_MENU_ITEM_PER_PAGE);
    } else if (uiKeyCode == GpuiKeyTbl[KEY_MENU_DOWN]) {                /*  下一个菜单项                */  
        if (*pptnWalker == NULL) {
            ;
        } else if (NULL == __GptnCurMenu->ptnNext) {                    /*  下翻到底                    */
            __GptnCurMenu = *pptnWalker;
        } else {                
            sysIrqDisable();
            do {                    
                if (*pptnWalker == __GptnCurMenu) {
                    if ((*pptnWalker)->ptnNext) {                        
                        __GptnCurMenu = (*pptnWalker)->ptnNext;
                        ucMenuIndex++;
                    } 
                    break;
                } else {
                    pptnWalker = &(*pptnWalker)->ptnNext;  
                    ucMenuIndex++;
                }
            } while (1);
            sysIrqEnable();
        } 
        mpDisplayEx(__GptnCurMenu->ptnParent, (ucMenuIndex / MAX_MENU_ITEM_PER_PAGE) * MAX_MENU_ITEM_PER_PAGE);                
    } else if (uiKeyCode == GpuiKeyTbl[KEY_MENU_LEFT]) {                /*  左翻页                      */
        if (*pptnWalker == NULL) {
            ;
        } else if ((*pptnWalker)->ptnPrev == NULL) {                    /*  首页                        */            
            do {                                                        /*  查找末页                    */
                if ((*pptnWalker)->ptnNext == NULL) {
                    break;
                }
                pptnWalker = &(*pptnWalker)->ptnNext;
            } while (1);            
        } else {                                                        /*  前一页                      */
            pptnWalker = &(*pptnWalker)->ptnPrev;
        }
        if ((*pptnWalker)->ptnChild) {                                  /*  有子菜单项                  */
            __GptnCurMenu = (*pptnWalker)->ptnChild;
        } else {                                                        /*  无子菜单项                  */
            __GptnCurMenu = (*pptnWalker);
        }
        mpDisplay(*pptnWalker);
    } else if (uiKeyCode == GpuiKeyTbl[KEY_MENU_RIGHT]) {               /*  右翻页                      */
        if (*pptnWalker == NULL) {
            ;
        } else if ((*pptnWalker)->ptnNext == NULL) {                    /*  尾页                        */
            pptnWalker = &__GptnRootMenu->ptnChild;                     /*  回到首页                    */
        } else {
            pptnWalker = &(*pptnWalker)->ptnNext;
        }
        if ((*pptnWalker)->ptnChild) {                                  /*  有子菜单项                  */
            __GptnCurMenu = (*pptnWalker)->ptnChild;
        } else {                                                        /*  无子菜单项                  */
            __GptnCurMenu = (*pptnWalker);
        }
        mpDisplay(*pptnWalker);
    } else if (uiKeyCode == GpuiKeyTbl[KEY_ENTER]) {                    /*  确认                        */
        if (__GptnCurMenu->ptnChild) {                                  /*  存在下级菜单                */
            __GptnCurMenu = __GptnCurMenu->ptnChild;
            mpDisplay(__GptnCurMenu->ptnParent);
        } else if (__GucEntered) {
            if (pmii->pmiib->pmifFunc->pfuncOnkey) {
                pmii->pmiib->pmifFunc->pfuncOnkey(pmii, uiKeyCode);
            }
        } else if (pmii->pmiib->ucType.Bits.ucIsModifiable) {
            if (Gds.ucIsAuthorized) {
                uiTmp = strlen(pmii->pmiib->pcTitle);
                guiPrintf(pmii->ucX + uiTmp * FONT_XSIZE8, pmii->ucY, 1, "?");
                if (pmii->pvPara) {                                     /*  带参数菜单                  */
                    __GucEntered = TRUE;
                }    
                Gds.uiAuthorizedTimeoutTick = SEC_TIMER;
            } else {
                miAdd(pmii->pmiib, &__GmiibPwdInput);
                __GptnCurMenu = __GptnCurMenu->ptnChild;
                mpDisplay(__GptnCurMenu);
                __GucEntered = TRUE;
            }
        }
    } else if ((uiKeyCode == GpuiKeyTbl[KEY_ABORT]) &&                   /*  停止键                      */
               (!__GucEntered)) {                                       /*  未进入修改状态              */
        // if ((__GptnCurMenu->ptnParent) &&
        //     ((*pptnWalker)->ptnParent != __GptnRootMenu) &&
        //     (__GptnCurMenu->ptnParent->ptnParent)) {                    /*  存在上级菜单                */
        //     __GptnCurMenu = __GptnCurMenu->ptnParent->ptnParent->ptnChild;
        //     mpDisplay(__GptnCurMenu->ptnParent);                        /*  返回上一级菜单              */
        // } else {                                                        /*  根节点状态                  */
            miFlush();                                                  /*  返回空闲界面                */
        //    mainDisplay();
        //    __GucEntered = FALSE;
        // }

    } else {                                                            /*  其他按键                    */
        if (pmii->pmiib->pmifFunc->pfuncOnkey) {
            pmii->pmiib->pmifFunc->pfuncOnkey(pmii, uiKeyCode);
        }
    }
    
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           inputPwd
** Descriptions:            密码输入处理函数
** input parameters:        uiKbdCode           键码
**                          uiX                 密码输入框X坐标
**                          uiY                 密码输入框Y坐标
**                          uiMaxLen            输入最大字符数                         
**                          
** output parameters:       pucRtn              返回密码数组
** Returned value:          TRUE                解析到结果
**                          FALSE               未解析到结果
*********************************************************************************************************/
INT8U  inputPwd(INT32U uiX, INT32U uiY, INT32U uiKbdCode, INT32U uiMaxLen, INT8U  *pucRtn)	  
{
    //static INT8U    __SucIndex;
    switch(uiKbdCode) {
        case JP_0:
        case JP_1:
        case JP_2:
        case JP_3:
        case JP_4:
        case JP_5:
        case JP_6:
        case JP_7:
        case JP_8:
        case JP_9:
            if (0 == __SucIndex) {
                guiClrRectangle(uiX + FONT_XSIZE8, uiY, uiX + (uiMaxLen + 1) * FONT_XSIZE8 - 1, uiY + FONT_YSIZE16 - 1);
            }
            if (__SucIndex >= uiMaxLen) {                                       /*  超长输入自动完成输入        */
                return INPUT_UNCOMPLETED;
            }
            pucRtn[__SucIndex] = kbd2Ascii(uiKbdCode);
            guiPrintf(uiX + __SucIndex * FONT_XSIZE8, uiY, 0, "*");
            __SucIndex++;
            break;
        
        
            
        default:
            if (GpuiKeyTbl[KEY_ENTER] == uiKbdCode) {
            //if (__SucIndex < uiMaxLen) {
            //    return INPUT_UNCOMPLETED;
            //} else {
                __SucIndex = 0;
                return INPUT_COMPLETED;
            //}
            } else if (GpuiKeyTbl[KEY_ABORT] == uiKbdCode) {
                __SucIndex = 0;
                return INPUT_QUIT;
            } 
            break;
    }
    return INPUT_UNCOMPLETED;
} 

/*********************************************************************************************************
** Function name:           inputInt
** Descriptions:            整型数值型参数输入处理函数
** input parameters:        uiKbdCode           键码
**                          pmiiThis            菜单项指针
**                          psiRtn              返回数值
** output parameters:       fpRtn               解析结果返回值指针
** Returned value:          参考afxMenu.h
*********************************************************************************************************/
INT8U inputInt(INT32U uiKbdCode, MENU_ITEM_INFO *pmiiThis, INT32S *psiRtn)
{
    //static INT8U  __SucIndex;
    INT8U           ucErr = INPUT_UNCOMPLETED;
    static INT32U __SuiMaxLen;
    INT32U          uiX, uiY;
    uiX = pmiiThis->ucX + (strlen(pmiiThis->pmiib->pcTitle) + 1) * FONT_XSIZE8;
    uiY = pmiiThis->ucY;
   
    switch(uiKbdCode) {
        case JP_0:
        case JP_1:
        case JP_2:
        case JP_3:
        case JP_4:
        case JP_5:
        case JP_6:
        case JP_7:
        case JP_8:
        case JP_9:
            if (0 == __SucIndex) {                                      /*  首次输入                    */
                guiClrRectangle(uiX, uiY, 127, uiY + FONT_YSIZE16 - 1);
                //pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, __SscParamFmt);
                //__SuiMaxLen = strlen(__SscParamFmt) - 1;
                memset(&__SscParamFmt[0], 0x00, sizeof(__SscParamFmt));
            }
            __SscParamFmt[__SucIndex] = kbd2Ascii(uiKbdCode);
            __SucIndex++;
            //GUI_RectangleFill(uiX, uiY, uiX + (__SuiMaxLen + 1) * FONT_XSIZE8 - 1, uiY + FONT_YSIZE16 - 1, 0);            
            guiPrintf(uiX + FONT_XSIZE8, uiY, 0, "%s", __SscParamFmt);
            ucErr = INPUT_UNCOMPLETED;
        break;
        
        default:
            if (uiKbdCode == GpuiKeyTbl[KEY_ENTER]) {
                if (sscanf(__SscParamFmt, "%d", psiRtn)) {                  /*  数值解析成功                */            
                    ucErr = INPUT_COMPLETED;
                } else {                                                    /*  数值解析失败                */                                                
                    ucErr = INPUT_UNREASONABLE;
                }
                __SucIndex = 0; 
            } else if (uiKbdCode == GpuiKeyTbl[KEY_ABORT]) {
                __SucIndex = 0;
                ucErr = INPUT_QUIT;
            }
        break;
    }
    return ucErr;
}


/*********************************************************************************************************
** Function name:           paraEnableSwitchFmt
** Descriptions:            使能开关型参数格式化字符串函数
** input parameters:        ucOnOff             0/1 关/开
**                          
** output parameters:       pvRsv               返回格式化字符串
** Returned value:          参考afxMenu.h
*********************************************************************************************************/
static char * __SscEnStr[2] = {"开", "关"};

void paraEnableSwitchFmt(INT8U ucOnOff, void *pvRsv)
{
    sprintf(pvRsv, ":%s", __SscEnStr[ucOnOff ? 1 : 0]);
}
/*********************************************************************************************************
** Function name:           inputEnableSwitch
** Descriptions:            使能开关型参数输入处理函数
** input parameters:        uiKbdCode           键码
**                          pmiiThis            菜单项指针
**                          psiRtn              返回数值
** output parameters:       fpRtn               解析结果返回值指针
** Returned value:          参考afxMenu.h
*********************************************************************************************************/
INT8U inputEnableSwitch(INT32U uiKbdCode, MENU_ITEM_INFO *pmiiThis, INT32S *psiRtn)
{
    static INT8U  __SucEnFlag;
    unsigned int    uiLen;
    
    INT8U           ucErr = INPUT_UNCOMPLETED;
    static INT32U __SuiMaxLen;
    char            scParamFmt[32] = {0};
    INT32U          uiX, uiY;
    uiX = pmiiThis->ucX + (strlen(pmiiThis->pmiib->pcTitle) + 1) * FONT_XSIZE8;
    uiY = pmiiThis->ucY;
   
    switch(uiKbdCode) {
        case JP_K:
        case JP_0:
            __SucEnFlag = 0;
            uiLen = strlen(pmiiThis->pmiib->pcTitle);
            guiPrintf(pmiiThis->ucX + uiLen * 8, pmiiThis->ucY, 1, "?%s", __SscEnStr[__SucEnFlag]);
        break;
        case JP_M:
        case JP_1:
            __SucEnFlag = 1;
            uiLen = strlen(pmiiThis->pmiib->pcTitle);
            guiPrintf(pmiiThis->ucX + uiLen * 8, pmiiThis->ucY, 1, "?%s", __SscEnStr[__SucEnFlag]);    
        break;
        
        case JP_B:
            if (!__GucEntered) {
                __SucEnFlag = Gdp.ucAsqStrebEn & 0x01; 
                guiPrintf(uiX, uiY, 1, "?");
                break;
            }
            if (__SucEnFlag) {
                ((INT32U *)pmiiThis->pvPara)[0] |= 1;
            } else {
                ((INT32U *)pmiiThis->pvPara)[0] &= ~1;
            }
            //GdiDevInfo.ucPressureEn[2] = __SucEnFlag;
            if (1) {                         /*  参数保存失败                */
                //提示保存参数错误
                eepromWrite(0, (INT8U *)&Gdp, sizeof(DEV_PARA));;
            } else {
 
            }
            pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, scParamFmt);
            guiPrintf(uiX, uiY, 1, "%s", scParamFmt);
        break;
        case JP_E:
            pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, scParamFmt);
            guiPrintf(uiX, uiY, 1, "%s", scParamFmt);
        break;
        default:
        break;
    }
    switch(uiKbdCode) {
        case JP_0:
        case JP_1:
        case JP_2:
        case JP_3:
        case JP_4:
        case JP_5:
        case JP_6:
        case JP_7:
        case JP_8:
        case JP_9:
            if (0 == __SucIndex) {                                      /*  首次输入                    */
                guiClrRectangle(uiX, uiY, 127, uiY + FONT_YSIZE16 - 1);
                //pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, __SscParamFmt);
                //__SuiMaxLen = strlen(__SscParamFmt) - 1;
                memset(&__SscParamFmt[0], 0x00, sizeof(__SscParamFmt));
            }
            __SscParamFmt[__SucIndex] = kbd2Ascii(uiKbdCode);
            __SucIndex++;
            //GUI_RectangleFill(uiX, uiY, uiX + (__SuiMaxLen + 1) * FONT_XSIZE8 - 1, uiY + FONT_YSIZE16 - 1, 0);            
            guiPrintf(uiX + FONT_XSIZE8, uiY, 0, "%s", __SscParamFmt);
            ucErr = INPUT_UNCOMPLETED;
        break;
        
        default:
            if (uiKbdCode == GpuiKeyTbl[KEY_ENTER]) {
                if (sscanf(__SscParamFmt, "%d", psiRtn)) {                  /*  数值解析成功                */            
                    ucErr = INPUT_COMPLETED;
                } else {                                                    /*  数值解析失败                */                                                
                    ucErr = INPUT_UNREASONABLE;
                }
                __SucIndex = 0; 
            } else if (uiKbdCode == GpuiKeyTbl[KEY_ABORT]) {
                __SucIndex = 0;
                ucErr = INPUT_QUIT;
            }
        break;
    }
    return ucErr;
}

#if 0

/*********************************************************************************************************
** Function name:           inputInt
** Descriptions:            整型数值型参数输入处理函数
** input parameters:        uiKbdCode           键码
**                          pmiiThis            菜单项指针
**                          psiRtn              返回数值
** output parameters:       fpRtn               解析结果返回值指针
** Returned value:          参考afxMenu.h
*********************************************************************************************************/
INT8U inputInt(INT32U uiKbdCode, MENU_ITEM_INFO *pmiiThis, INT32S *psiRtn)
{

    //static INT8U  __SucIndex;
    INT8U           ucErr = INPUT_UNCOMPLETED;
    static INT32U __SuiMaxLen;
    INT32U          uiX, uiY;
    uiX = pmiiThis->ucX + strlen(pmiiThis->pmiib->pcTitle) * FONT_XSIZE8;
    uiY = pmiiThis->ucY;
   
    switch(uiKbdCode) {
        case KEY_ENTER:
            if (sscanf(__SscParamFmt, "%d", psiRtn)) {                  /*  数值解析成功                */            
                ucErr = INPUT_COMPLETED;
            } else {                                                    /*  数值解析失败                */                                                
                ucErr = INPUT_UNREASONABLE;
            }
            __SucIndex = 0;  
        break;
        
        case KEY_ESC:
            __SucIndex = 0;
            ucErr = INPUT_QUIT;
        break;
        
        case KEY_0:
        case KEY_1:
        case KEY_2:
        case KEY_3:
        case KEY_4:
        case KEY_5:
        case KEY_6:
        case KEY_7:
        case KEY_8:
        case KEY_9:
        case KEY_MINUS: 
            if (0 == __SucIndex) {                                      /*  首次输入                    */
                pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, __SscParamFmt);
                __SuiMaxLen = strlen(__SscParamFmt) - 1;
                memset(&__SscParamFmt[1], 0x00, sizeof(__SscParamFmt));
            }
            __SscParamFmt[__SucIndex + 1] = kbd2Ascii(uiKbdCode);
            __SucIndex++;
            guiRectangleFill(uiX, uiY, uiX + (__SuiMaxLen + 1) * FONT_XSIZE8 - 1, uiY + FONT_YSIZE16 - 1, 0);
            guiPrintf(uiX + FONT_XSIZE8, uiY, 0, "%s", __SscParamFmt);
            ucErr = INPUT_UNCOMPLETED;
        break;
        
        default:
            
        break;
    }
    return ucErr;
}

/*********************************************************************************************************
** Function name:           inputFloat
** Descriptions:            浮点型数值型参数输入处理函数
** input parameters:        uiKbdCode           键码
**                          pmiiThis            菜单项指针
**                          pfpRtn              返回数值
** output parameters:       fpRtn               解析结果返回值指针
** Returned value:          参考afxMenu.h
*********************************************************************************************************/
INT8U inputFloat(INT32U uiKbdCode, MENU_ITEM_INFO *pmiiThis, FP32 *pfpRtn)
{
    //static char   __SscParamFmt[32];
    //static INT8U  __SucIndex;
    INT8U           ucErr = INPUT_UNCOMPLETED;
    static INT32U __SuiMaxLen;
    INT32U          uiX, uiY;
    uiX = pmiiThis->ucX + strlen(pmiiThis->pmiib->pcTitle) * FONT_XSIZE8;
    uiY = pmiiThis->ucY;
    
    /*
     *  中山大洋电机发现问题
     */
    if ((!__GucEntered) && (uiKbdCode != KEY_ENTER)) {
        return ucErr;
    }
    //==================================================================================================    
    switch(uiKbdCode) {
        case KEY_ENTER:
            if (!__GucEntered) {
                guiPrintf(uiX, uiY, 1, "?");
            } else if (sscanf(__SscParamFmt, "%f", pfpRtn)) {           /*  数值解析成功                */            
                ucErr = INPUT_COMPLETED;
            } else {                                                    /*  数值解析失败                */                                                
                ucErr = INPUT_UNREASONABLE;
            }
            __SucIndex = 0;  
        break;
        
        case KEY_ESC:
            __SucIndex = 0;
            ucErr = INPUT_QUIT;
        break;
        
        case KEY_0:
        case KEY_1:
        case KEY_2:
        case KEY_3:
        case KEY_4:
        case KEY_5:
        case KEY_6:
        case KEY_7:
        case KEY_8:
        case KEY_9:
        case KEY_MINUS:
        case KEY_DOT:  
            if (0 == __SucIndex) {                                      /*  首次输入                    */
                pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, __SscParamFmt);
                __SuiMaxLen = strlen(__SscParamFmt) - 1;
                memset(__SscParamFmt, 0x00, sizeof(__SscParamFmt));
            }
            ucErr = INPUT_UNCOMPLETED;
            if (__SucIndex >= __SuiMaxLen) {
                break;
            }
            __SscParamFmt[__SucIndex] = kbd2Ascii(uiKbdCode);
            __SucIndex++;
            guiRectangleFill(uiX + FONT_XSIZE8, uiY, uiX + (__SuiMaxLen + 1) * FONT_XSIZE8 - 1, uiY + FONT_YSIZE16 - 1, 0);
            guiPrintf(uiX + FONT_XSIZE8, uiY, 0, "%s", __SscParamFmt);
            
        break;
        
        case KEY_DEL:
            ucErr = INPUT_UNCOMPLETED;
            memset(__SscParamFmt, 0x00, sizeof(__SscParamFmt));
            __SucIndex = 0;
            guiRectangleFill(uiX + FONT_XSIZE8, uiY, uiX + (__SuiMaxLen + 1) * FONT_XSIZE8 - 1, uiY + FONT_YSIZE16 - 1, 1);
            
        break;
        default:
            
        break;
    } 
    return ucErr;
}

/*********************************************************************************************************
** Function name:           paraFloatOnKey
** Descriptions:            浮点型参数菜单项按键响应函数
** input parameters:        pmiibThis:  菜单项信息
**                          pvData:     待处理数据指针
**                          
** output parameters:       pfpRtn:     参数输出指针
** Returned value:          SYS_OK :  成功
**                          负数:    错误,绝对值参考afxMenu.h
*********************************************************************************************************/
INT32S paraFloatOnKey (MENU_ITEM_INFO *pmiiThis, void *pvData, FP32 *pfpRtn)
{
    INT32U         *puiKeyCode;    
    FP32            fpRtn;
    char            scParamFmt[32];
    INT32U          uiX, uiY;
    INT8U           ucErr;
    uiX = pmiiThis->ucX + strlen(pmiiThis->pmiib->pcTitle) * FONT_XSIZE8;
    uiY = pmiiThis->ucY;
    /*
     *  参数过滤
     */
    if (NULL == pmiiThis) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == pvData) {
        return (-SYS_PARA_ERR);
    }
    puiKeyCode = pvData;
    ucErr = inputFloat(puiKeyCode[0], pmiiThis, &fpRtn);
    if (INPUT_UNCOMPLETED == ucErr) {                                   /*  未完成输入                  */
        return SYS_OK;
    }
    if (INPUT_COMPLETED == ucErr) {                                     /*  参数输入完成                */
        pfpRtn[0] = fpRtn;
        if (dsSaveParam(&GdiDevInfo) < 0) {                             /*  参数保存失败                */
            dsRecoverParam(&GdiDevInfo);
        } else {
            ;
        }         
    } else if (INPUT_QUIT == ucErr) {                                   /*  退出输入                    */                              
        ;
    } else if (INPUT_UNREASONABLE == ucErr) {                           /*  输入非法                    */
        ;
    } else {                                                            /*  参数未完成输入              */
        ;
    }
    pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, scParamFmt);
    guiRectangleFill(uiX, uiY, GUI_LCM_XMAX, uiY + FONT_YSIZE16, 0);
    guiPrintf(uiX, uiY, 1, "%s", scParamFmt);
    __GucEntered = !__GucEntered;
    //mpDisplay(__GpdlsCurMenuPage->pvData);
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           paraIntegerOnKey
** Descriptions:            菜单项按键响应函数
** input parameters:        pmiibThis:  菜单项信息
**                          pvData:     待处理数据指针
**                          
** output parameters:       pfpRtn:     参数输出指针
** Returned value:          SYS_OK :    成功
**                          负数:       错误,绝对值参考afxMenu.h
*********************************************************************************************************/
INT32S paraIntegerOnKey (MENU_ITEM_INFO *pmiiThis, void *pvData, INT32S *psiRtn)
{
    INT32U     *puiKeyCode;    
    FP32            fpRtn;
    char            scParamFmt[32];
    INT32U          uiX, uiY;
    INT8U           ucErr;
    uiX = pmiiThis->ucX + strlen(pmiiThis->pmiib->pcTitle) * FONT_XSIZE8;
    uiY = pmiiThis->ucY;
    /*
     *  参数过滤
     */
    if (NULL == pmiiThis) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == pvData) {
        return (-SYS_PARA_ERR);
    }
    puiKeyCode = pvData;
    ucErr = inputFloat(puiKeyCode[0], pmiiThis, &fpRtn);
    if (INPUT_COMPLETED == ucErr) {                                     /*  参数输入完成                */
        psiRtn[0] = (INT32S)fpRtn;
        if (dsSaveParam(&GdiDevInfo) < 0) {                         /*  参数保存失败                */
            dsRecoverParam(&GdiDevInfo);
        } else {
            ;
        } 
        pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, scParamFmt);
        guiRectangleFill(uiX, uiY, GUI_LCM_XMAX, uiY + FONT_YSIZE16, 0);
        guiPrintf(uiX, uiY, 1, "%s", scParamFmt);
        __GucEntered = !__GucEntered;
        //mpDisplay(__GpdlsCurMenuPage->pvData);
    } else if (INPUT_QUIT == ucErr) {                                   /*  退出输入                    */                              
        ;
    } else if (INPUT_UNREASONABLE == ucErr) {                           /*  输入非法                    */
        ;
    } else {                                                            /*  参数未完成输入              */
        ;
    }
    return SYS_OK;
}

/*********************************************************************************************************
** Function name:           paraUCharOnKey
** Descriptions:            菜单项按键响应函数
** input parameters:        pmiibThis:  菜单项信息
**                          pvData:     待处理数据指针
**                          
** output parameters:       pfpRtn:     参数输出指针
** Returned value:          SYS_OK :    成功
**                          负数:       错误,绝对值参考afxMenu.h
*********************************************************************************************************/
INT32S paraUCharOnKey (MENU_ITEM_INFO *pmiiThis, void *pvData, INT8U *pucRtn)
{
  __IFSF_MSG        imMsg;
    INT32U         *puiKeyCode;    
    FP32            fpRtn;
    char            scParamFmt[32];
    INT32U          uiX, uiY;
    INT8U           ucErr;
    uiX = pmiiThis->ucX + strlen(pmiiThis->pmiib->pcTitle) * FONT_XSIZE8;
    uiY = pmiiThis->ucY;
    /*
     *  参数过滤
     */
    if (NULL == pmiiThis) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == pvData) {
        return (-SYS_PARA_ERR);
    }
    puiKeyCode = pvData;
    ucErr = inputFloat(puiKeyCode[0], pmiiThis, &fpRtn);
    if (INPUT_UNCOMPLETED == ucErr) {
        return SYS_OK;
    }
    if ((INPUT_COMPLETED == ucErr) &&                                   /*  参数输入完成                */
        ((fpRtn > 0.0f) &&
        (fpRtn <= 255.0f))) {                                           /*  合理数值                    */
        pucRtn[0] = (INT8U)fpRtn;
        if (dsSaveParam(&GdiDevInfo) < 0) {                             /*  参数保存失败                */
            dsRecoverParam(&GdiDevInfo);
        } else {
            ;
        };       

    } else if (INPUT_QUIT == ucErr) {                                   /*  退出输入                    */                              
        ;
    } else if (INPUT_UNREASONABLE == ucErr) {                           /*  输入非法                    */
        ;
    } else {                                                            /*  参数未完成输入              */
        ;
    }
    pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, scParamFmt);
    guiRectangleFill(uiX, uiY, GUI_LCM_XMAX, uiY + FONT_YSIZE16, 0);
    guiPrintf(uiX, uiY, 1, "%s", scParamFmt);
    return SYS_OK; 
}

/*********************************************************************************************************
** Function name:           paraEnDateOnKey
** Descriptions:            日期设置菜单项按键响应函数
** input parameters:        pmiibThis:  菜单项信息
**                          pvData:     待处理数据指针
**                          
** output parameters:       pfpRtn:     参数输出指针
** Returned value:          SYS_OK :    成功
**                          负数:       错误,绝对值参考afxMenu.h
*********************************************************************************************************/
INT32S paraEnDateOnKey (MENU_ITEM_INFO *pmiiThis, void *pvData, INT8U *pucRtn)
{
    INT32U     *puiKeyCode;    
    FP32            fpRtn;
    char            scParamFmt[32] = {0};
    INT32U          uiX, uiY;
    INT8U           ucErr;
    uiX = pmiiThis->ucX + strlen(pmiiThis->pmiib->pcTitle) * FONT_XSIZE8;
    uiY = pmiiThis->ucY;
    /*
     *  参数过滤
     */
    if (NULL == pmiiThis) {
        return (-SYS_PARA_ERR);
    }
    if (NULL == pvData) {
        return (-SYS_PARA_ERR);
    }
    puiKeyCode = pvData;
    ucErr = inputFloat(puiKeyCode[0], pmiiThis, &fpRtn);
    if (INPUT_COMPLETED == ucErr) {                                     /*  参数输入完成                */
        pucRtn[0] = (INT8U)fpRtn;
        if (dsSaveParam(&GdiDevInfo) < 0) {                         /*  参数保存失败                */
            dsRecoverParam(&GdiDevInfo);
        } else {
            ;
        } 
        pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, scParamFmt);
        guiRectangleFill(uiX, uiY, GUI_LCM_XMAX, uiY + FONT_YSIZE16, 0);
        guiPrintf(uiX, uiY, 1, "%s", scParamFmt);
        __GucEntered = !__GucEntered;
        //mpDisplay(__GpdlsCurMenuPage->pvData);
    } else if (INPUT_QUIT == ucErr) {                                   /*  退出输入                    */                              
        ;
    } else if (INPUT_UNREASONABLE == ucErr) {                           /*  输入非法                    */
        ;
    } else {                                                            /*  参数未完成输入              */
        ;
    }
    return SYS_OK;
}
#endif
/*********************************************************************************************************
** Function name:           pwdChgOnKey
** Descriptions:            密码修改处理函数
** input parameters:        pmiibThis:  菜单项信息
**                          pvData:     待处理数据指针
**                          
** output parameters:       pfpRtn:     参数输出指针
** Returned value:          SYS_OK :    成功
**                          负数:       错误,绝对值参考afxMenu.h
*********************************************************************************************************/
INT32S pwdChgOnKey (MENU_ITEM_INFO *pmiiThis, void *pvData, INT8U *pucRtn)
{
    INT32U         *puiKeyCode;
    static INT8U  __SucPassword[2][6];
    static INT8U  __SucTimes;
    static INT32U   uiX, uiY;
    INT8U           ucErr;
    char scParamFmt[16];
    puiKeyCode = pvData;
    if ((!__GucEntered) && puiKeyCode[0] == GpuiKeyTbl[KEY_ABORT]) {
        __SucTimes = 0;
        return SYS_OK;
    }
    uiX = pmiiThis->ucX + strlen(pmiiThis->pmiib->pcTitle) * FONT_XSIZE8;
    uiY = pmiiThis->ucY;
    if (!__GucEntered && puiKeyCode[0] == KEY_ENTER) {
        guiPrintf(uiX, uiY, 0, "?");
        guiPrintf(0, 0, 0, "%s", __SscStr[__SucTimes]);
        return SYS_OK;
    }
    
    ucErr = inputPwd(uiX + FONT_XSIZE8, uiY, puiKeyCode[0], 6, __SucPassword[__SucTimes]);
    if (INPUT_COMPLETED == ucErr) {
        
        __SucTimes++;
        guiPrintf(0, 0, 0, "%s", __SscStr[__SucTimes]);
        pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, scParamFmt);
        guiPrintf(uiX, uiY, 1, "%s", scParamFmt);
        
        if (__SucTimes > 1) {                                           /*  完成2次输入                 */
            if (memcmp(__SucPassword[0], __SucPassword[1], 6)) {
                __SucTimes++;
            } else {
                memcpy(pucRtn, __SucPassword[0], 6);
//                if (dsSaveParam(&GdiDevInfo) < 0) {                         /*  参数保存失败                */
//                    //提示保存参数错误
//                    dsRecoverParam(&GdiDevInfo);
//                } else {
//                    ;
//                }
            }
            guiPrintf(0, 0, 0, "%s", __SscStr[__SucTimes]);
            guiPrintf(uiX, uiY, 1, ":");
            __SucTimes = 0;
        } else {
            guiPrintf(uiX, uiY, 1, "?");
            __GucEntered = !__GucEntered;
        }
    } else if (INPUT_QUIT == ucErr) {
        guiPrintf(0, 0, 0, "%s", __SscStr[__SucTimes]);
        pmiiThis->pmiib->pmifFunc->pfuncParamFmt(pmiiThis, scParamFmt);
        guiPrintf(uiX, uiY, 1, "%s", scParamFmt);
    }
    return SYS_OK;
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
