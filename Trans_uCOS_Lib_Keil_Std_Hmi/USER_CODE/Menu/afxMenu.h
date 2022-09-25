/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn  
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               afxMenu.h
** Latest modified Date:    2014-12-05
** Latest Version:          1.0.0
** Descriptions:            
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
#ifndef __AFX_MENU_H
#define __AFX_MENU_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

#include    "..\SYS_CODE\Head\system.h" 


    
#define FONT_XSIZE8         8
#define FONT_YSIZE16        16
#define GUI_LCM_XMAX        128
#define GUI_LCM_YMAX        64
/*********************************************************************************************************
  菜单项操作函数
*********************************************************************************************************/
struct menu_item_info;
struct menu_item_func {
    /*
     *  构造函数
     */
    INT32S    (*pfuncCreate)(struct menu_item_info *pmiibThis);

    /*
     *  析构函数
     */
    INT32S    (*pfuncDel)(struct menu_item_info *pmiibThis);

    /*
     *  菜单项按键响应函数
     */
    INT32S    (*pfuncOnkey)(struct menu_item_info *pmiibThis,
                                  INT32U               uiKeyCode);
    /*
     *  菜单项绑定参数格式化字符串
     */
    INT32S    (*pfuncParamFmt)(struct menu_item_info *pmiibThis,
                                  void                *pvRsv);                              
};
typedef  struct menu_item_func      MENU_ITEM_FUNC;


/*********************************************************************************************************
  菜单项数据结构信息
*********************************************************************************************************/
typedef enum {
    PARA_TYPE_OPERATE,                                                  /*  操作                        */
    PARA_TYPE_EN_DISABLE,                                               /*  禁止允许                    */
    PARA_TYPE_LEFT_RIGHT,                                               /*  左/右向                     */
    PARA_TYPE_ON_OFF,                                                   /*  开/关                       */
    PARA_TYPE_IN_OUT_NONE,                                              /*  伸/收/无                    */
    PARA_TYPE_FRT_REAR_NONE,                                            /*  前/后/无                    */
    PARA_TYPE_UP_DOWN_NONE,                                             /*  上/下/无                    */
    PARA_TYPE_LEFT_RIGHT_NONE,                                          /*  左/右/无                    */
    PARA_TYPE_VALUE,                                                    /*  数字                        */
    PARA_TYPE_SWITCH,                                                   /*  开/关                       */
    PARA_TYPE_SIGNAL_PRESENT,                                           /*  有/无信号                   */
    PARA_TYPE_AIM_REACH,                                                /*  达到/未达到                 */
} __PARA_TYPE;

typedef enum {
    PARA_SCOPE_GLOBAL,                                                  /*  全局                        */
    PARA_SCOPE_LOCAL,                                                   /*  局部                        */
    PARA_SCOPE_OPTIONAL,                                                /*  可选                        */
} __PARA_SCOPE;

typedef union {
    INT8U                       ucWord;
    struct {
      __PARA_TYPE               ucType          :5;
      __PARA_SCOPE              ucScope         :2;
        INT8U                   ucIsModifiable  :1;
    } Bits;
} PARA_TYPE;
/*
 *  菜单项基础信息
 */
typedef struct menu_item_info_base {
    const char                 *pcTitle;                                /*  菜单项标题                  */
    MENU_ITEM_FUNC             *pmifFunc;                               /*  函数列表                    */ 
    INT16U                      ulAddrStart;                            /*  菜单页编号                  */
    //INT8U                       ucIsModifiable;                         /*  可修改参数菜单标识          */
    PARA_TYPE                   ucType;                                 /*  菜单类型
                                                                         *  0 开关
                                                                         *  1 类型
                                                                         * 
                                                                         * 
                                                                         * 
                                                                         * 
                                                                         */  
    // INT8U                       ucIsGlobal;                             /*  作用域
    //                                                                      *  1 全局
    //                                                                      *  2 局部
    //                                                                      *  3 全局/局部可选
    //                                                                      */                                                                                              
} MENU_ITEM_INFO_BASE, *PMENU_ITEM_INFO_BASE;

typedef struct menu_item_info {
    const MENU_ITEM_INFO_BASE  *pmiib;                                  /*  菜单项基础信息指针          */
    void                       *pvPara;                                 /*  菜单项绑定参数指针          */
    INT8U                       ucX;                                    /*  参数显示坐标X               */
    INT8U                       ucY;                                    /*  参数显示坐标Y               */                        
} MENU_ITEM_INFO, *PMENU_ITEM_INFO;


#if 0
/*
 *  菜单项单链表数据结构
 */
typedef struct __menu_item_node {
    TREE_NODE                   tnMenu;                                 /*  菜单节点                    */
    MENU_ITEM_INFO             *pmiiData;                               /*  菜单项数据                  */
} MENU_ITEM_NODE, *PMENU_ITEM_NODE;
#endif


/*
 *  菜单相关宏定义
 */

#define MAX_MENU_PAGE_NUM           0x10                                /*  菜单页最大数                */                
#define MAX_MENU_ITEM_PER_PAGE      0x02                                /*  每页菜单项最大数            */
#define CAPTION_YSPACE              24                                  /*  菜单页标题Y占位             */
#define CAPTION_XSTART              16                                  /*  菜单页标题显示X起始位置     */
#define MENU_ITEM_INTERVAL          24                                  /*  菜单项间隔                  */

#define GUEST_LEVEL                 0x00                                /*  用户模式                    */
#define ADMIN_LEVEL                 0x01                                /*  管理者模式                  */
#define DEVELOPER_LEVEL             0x02                                /*  开发者模式                  */


#define MIN_KEY_LAG                 400                                 /*  菜单操作按键最小时间间隔ms  */             


#define INPUT_UNCOMPLETED           0x00                                /*  输入未完成                  */
#define INPUT_COMPLETED             0x01                                /*  输入完成                    */
#define INPUT_QUIT                  0x02                                /*  输入退出                    */
#define INPUT_UNREASONABLE          0x03                                /*  输入不合理                  */
#define INPUT_PARA_ERR              0xff                                /*  调用者参数不合理            */



/*********************************************************************************************************
** Function name:           miRootInit
** Descriptions:            根菜单节点初始化
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miRootInit(void);

/*********************************************************************************************************
** Function name:           mpRootDel
** Descriptions:            根菜单节点卸载
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void miRootDel (void);

/*********************************************************************************************************
** Function name:           miTreeInit
** Descriptions:            菜单项树初始化
** input parameters:        pminRoot        菜单项根节点
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S miInit(const MENU_ITEM_INFO_BASE *pmiibRoot);

/*********************************************************************************************************
** Function name:           miAdd
** Descriptions:            增加菜单页
** input parameters:        pmiParent       父菜单项节点
**                          pmiib           要增加的菜单项
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S miAdd(const MENU_ITEM_INFO_BASE *pmiibParent, const MENU_ITEM_INFO_BASE *pmiib);

/*********************************************************************************************************
** Function name:           miDel
** Descriptions:            删除菜单项
** input parameters:        ptnRoot         菜单项根节点
**                          pmiib           待删除菜单项
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S miDel(const MENU_ITEM_INFO_BASE *pmiibDel);

/*********************************************************************************************************
** Function name:           miDel
** Descriptions:            删除菜单项
** input parameters:        pmiParent       父菜单项节点
**                          pmiib           待删除菜单项
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S miFindDel(TREE_NODE *pmiParent, const MENU_ITEM_INFO_BASE *pmiib);


/*********************************************************************************************************
** Function name:           miInsertPrev
** Descriptions:            增加前置菜单页
** input parameters:        pmiibBrother    兄弟菜单项节点
**                          pmiibAdd        要增加的菜单项
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S miInsertPrev(const MENU_ITEM_INFO_BASE *pmiibBrother, const MENU_ITEM_INFO_BASE *pmiibAdd);


/*********************************************************************************************************
** Function name:           miInsertNext
** Descriptions:            增加后置菜单页
** input parameters:        pmiibBrother    兄弟菜单项节点
**                          pmiibAdd        要增加的菜单项
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S miInsertNext(const MENU_ITEM_INFO_BASE *pmiibBrother, const MENU_ITEM_INFO_BASE *pmiibAdd);
    

/*********************************************************************************************************
** Function name:           mpListFlush
** Descriptions:            清空所有菜单页
** input parameters:        none
** output parameters:       none
** Returned value:          SYS_OK           成功
**                          负数            错误,绝对值参考afxMenu.h
*********************************************************************************************************/
extern INT32S miFlush(void);
    
/*********************************************************************************************************
** Function name:           miGetIndex
** Descriptions:            获取指定菜单项在所属页中的索引
** input parameters:        ptnMenu         菜单根节点
** output parameters:       puiRtn          索引返回指针
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S miGetIndex(TREE_NODE *ptn, INT32U *puiRtn);

/*********************************************************************************************************
** Function name:           miIsExist
** Descriptions:            检查菜单是否已存在
** input parameters:        pmiib           待检查的菜单项
** output parameters:       none
** Returned value:          TRUE            存在
**                          FALSE           不存在
*********************************************************************************************************/
extern BOOLEAN miIsExist(const MENU_ITEM_INFO_BASE *pmiib);


/*********************************************************************************************************
** Function name:           mpHome
** Descriptions:            显示菜单首页
** input parameters:        none        
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考afxMenu.h
*********************************************************************************************************/
extern INT32S mpHome(void);

/*********************************************************************************************************
** Function name:           mpOnKey
** Descriptions:            菜单页按键响应函数
** input parameters:        pmpiThis        菜单页信息      
**                          usLen           数据长度
**                          pvData          数据指针
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考afxMenu.h
*********************************************************************************************************/
extern INT32S  mpOnKey(MENU_ITEM_INFO *pmpiThis, INT16U usLen, void *pvData);

/*********************************************************************************************************
** Function name:           paraEnableSwitchFmt
** Descriptions:            使能开关型参数格式化字符串函数
** input parameters:        ucOnOff             0/1 关/开
**                          
** output parameters:       pvRsv               返回格式化字符串
** Returned value:          参考afxMenu.h
*********************************************************************************************************/
extern void paraEnableSwitchFmt(INT8U ucOnOff, void *pvRsv);

/*********************************************************************************************************
** Function name:           inputEnableSwitch
** Descriptions:            使能开关型参数输入处理函数
** input parameters:        uiKbdCode           键码
**                          pmiiThis            菜单项指针
**                          psiRtn              返回数值
** output parameters:       fpRtn               解析结果返回值指针
** Returned value:          参考afxMenu.h
*********************************************************************************************************/
extern INT8U inputEnableSwitch(INT32U uiKbdCode, MENU_ITEM_INFO *pmiiThis, INT32S *psiRtn);

/*********************************************************************************************************
** Function name:           inputFloat
** Descriptions:            浮点型数值型参数输入处理函数
** input parameters:        uiKbdCode           键码
**                          pmiiThis            菜单项指针
** output parameters:       fpRtn               解析结果返回值指针
** Returned value:          TRUE                解析到结果
**                          FALSE               未解析到结果
*********************************************************************************************************/
extern INT8U inputFloat(INT32U uiKbdCode, MENU_ITEM_INFO *pmiiThis, FP32 *pfpRtn);

/*********************************************************************************************************
** Function name:           paraOnKey
** Descriptions:            菜单项按键响应函数
** input parameters:        pmiibThis:  菜单项信息
**                          pvData:     待处理数据指针
**                          
** output parameters:       pfpRtn:     参数输出指针
** Returned value:          SYS_OK :  成功
**                          负数:    错误,绝对值参考afxMenu.h
** Created by:              
** Created Date:            2014-12-05
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
extern INT32S paraFlotOnKey (MENU_ITEM_INFO *pmiiThis, void *pvData, FP32 *pfpRtn);

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
extern INT32S paraIntegerOnKey (MENU_ITEM_INFO *pmiiThis, void *pvData, INT32S *psiRtn);

/*********************************************************************************************************
** Function name:           paraUCharOnKey
** Descriptions:            菜单项按键响应函数
** input parameters:        pmiibThis:  菜单项信息
**                          pvData:     待处理数据指针
**                          
** output parameters:       pfpRtn:     参数输出指针
** Returned value:          SYS_OK :    成功
**                          负数:       错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S paraUCharOnKey (MENU_ITEM_INFO *pmiiThis, void *pvData, INT8U *pucRtn);

/*********************************************************************************************************
** Function name:           pwdChgOnKey
** Descriptions:            密码修改处理函数
** input parameters:        pmiibThis:  菜单项信息
**                          pvData:     待处理数据指针
**                          
** output parameters:       pfpRtn:     参数输出指针
** Returned value:          SYS_OK :    成功
**                          负数:       错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S pwdChgOnKey (MENU_ITEM_INFO *pmiiThis, void *pvData, INT8U *pucRtn);

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
extern INT8U  inputPwd(INT32U uiX, INT32U uiY, INT32U uiKbdCode, INT32U uiMaxLen, INT8U  *pucRtn);

/*********************************************************************************************************
** Function name:           miOnKey
** Descriptions:            菜单项按键响应函数
** input parameters:        pmpiThis        菜单页信息      
**                          usLen           数据长度
**                          pvData          数据指针
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考afxMenu.h
*********************************************************************************************************/
extern INT32S  miOnKey(INT32U uiKeyCode);

/*********************************************************************************************************
** Function name:           mpDisplay
** Descriptions:            显示菜单页内容
** input parameters:        pmpiInfo        菜单页信息
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S mpDisplay(TREE_NODE *ptnParent);

/*********************************************************************************************************
** Function name:           mpDisplayEx
** Descriptions:            菜单页增量显示
** input parameters:        pmpiInfo        菜单页信息
**                          ucCurIndex      菜单页起始显示菜单项
** output parameters:       none
** Returned value:          SYS_OK          成功
**                          负数            错误,绝对值参考afxMenu.h
*********************************************************************************************************/
extern INT32S mpDisplayEx(TREE_NODE *ptnParent, INT8U ucCurIndex);

extern __DUAL_LIST *__GpdlsCurMenuPage;                                 /*  当前菜单页节点指针          */



extern INT8U        __GucPara[256];                                     /*  控制器参数                  */
extern BOOLEAN      __GucEntered;                                       /*  参数修改状态标识            */

extern TREE_NODE   *__GptnCurMenu;
extern TREE_NODE   *__GptnRootMenu;
extern const MENU_ITEM_INFO_BASE __GmiibRoot;                           /*  根菜单项信息                */
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __AFX_MENU_H                */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
