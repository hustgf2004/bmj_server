/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn  
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               key.h
** Latest modified Date:    2020-02-20
** Latest Version:          1.00
** Descriptions:            按键定义
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2020-02-20
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
#ifndef __KEY_H
#define __KEY_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
    定义键盘相关
*********************************************************************************************************/
#define MENU_LIST_MAX               0x13                                /*  菜单页                      */
#define KEY_ROM_MAX                 0x1E                                /*  菜单名字符串长度            */
#define KEY_ROM_DEFINE              0x09                                /*  参数取值控制长度            */
//#define KEY_MAX                     0x5a                                /*  键值数组长度                */    
    

/********************************************************************************************************* 
    键值定义
*********************************************************************************************************/
#define JP_0                        0x00000001 
#define JP_1                        0x00000002 
#define JP_2                        0x00000004 
#define JP_3                        0x00000008
#define JP_4                        0x00000010
#define JP_5                        0x00000020 
#define JP_6                        0x00000040 
#define JP_7                        0x00000080 
#define JP_8                        0x00000100
#define JP_9                        0x00000200
#define JP_L                        0x00000400 
#define JP_R                        0x00000800 
#define JP_E                        0x00001000 
#define JP_B                        0x00002000 
#define JP_P                        0x00004000
#define JP_N                        0x00008000
#define JP_U                        0x00010000 
#define JP_D                        0x00020000
#define JP_K                        0x00040000
#define JP_M                        0x00080000
#define JP_A                        0x00100000

#define JP_LOCK                     0x00200000
#define JP_STOP                     0x00400000
#define JP_NOP                      0x00000000



/********************************************************************************************************* 
    导航led定义
*********************************************************************************************************/
#define NAVI_M              ~0x00000001
#define NAVI_D              ~0x00000002	
#define NAVI_B              ~0x00000004	
#define NAVI_E              ~0x00000008	
#define NAVI_L              ~0x00000010	
#define NAVI_R      	    ~0x00000020	
#define NAVI_RX      	    ~0x00000040	
#define NAVI_TX             ~0x00000080	
#define NAVI_N              ~0x00000100	
#define NAVI_9              ~0x00000200	
#define NAVI_0              ~0x00000400	
#define NAVI_S              ~0x00000800	
#define NAVI_T              ~0x00001000	
#define NAVI_U              ~0x00002000	
#define NAVI_K              ~0x00004000	
#define NAVI_Q              ~0x00008000	
#define NAVI_4              ~0x00010000	
#define NAVI_I              ~0x00020000	
#define NAVI_J              ~0x00040000	
#define NAVI_5              ~0x00080000	
#define NAVI_6              ~0x00100000	
#define NAVI_7              ~0x00200000	
#define NAVI_8              ~0x00400000	
#define NAVI_P              ~0x00800000	
#define NAVI_A              ~0x01000000
#define NAVI_C              ~0x02000000	
#define NAVI_F              ~0x04000000	
#define NAVI_G              ~0x08000000	
#define NAVI_H              ~0x10000000
#define NAVI_1              ~0x20000000
#define NAVI_2              ~0x40000000	
#define NAVI_3              ~0x80000000

typedef enum {
        KEY_LEG_LOW,                                                    /*  降柱                        */
        KEY_CONV_PULL,                                                  /*  移架                        */
        KEY_LEG_SET,                                                    /*  升柱                        */
        KEY_CONV_PUSH,                                                  /*  推溜                        */
        KEY_BASE_LIFT_SET,                                              /*  抬底                        */
        KEY_STREB_OUT,                                                  /*  伸平衡                      */
        KEY_STREB_IN,                                                   /*  收平衡                      */
        KEY_FLIP_OUT,                                                   /*  伸伸缩梁                    */
        KEY_FLIP_IN,                                                    /*  收伸缩梁                    */
        KEY_STAB_OUT,                                                   /*  伸一级护帮                  */
        KEY_STAB_IN,                                                    /*  收一级护帮                  */
        KEY_STAB2_OUT,                                                  /*  伸二级护帮                  */
        KEY_STAB2_IN,                                                   /*  收二级护帮                  */
        KEY_STAB3_OUT,                                                  /*  伸三级护帮                  */
        KEY_STAB3_IN,                                                   /*  收三级护帮                  */        
        KEY_SPARY_ON,                                                   /*  喷雾                        */
        KEY_REMOTE,                                                     /*  远程                        */
        KEY_LEFT,                                                       /*  左邻架                      */
        KEY_RIGHT,                                                      /*  右邻架                      */
        KEY_START,                                                      /*  启动                        */
        KEY_ABORT,                                                      /*  停止                        */
        KEY_LEFT_BATCH,                                                 /*  左成组                      */
        KEY_RIGHT_BATCH,                                                /*  右成组                      */        
        KEY_SIDE_IN,                                                    /*  收侧护                      */
        KEY_SIDE_OUT,                                                   /*  伸侧护                      */
        KEY_BASE_PUSHER_IN,                                             /*  收底调                      */
        KEY_MENU_LEFT,                                                  /*  左翻页                      */
        KEY_BASE_PUSHER_OUT,                                            /*  伸底调                      */
        KEY_MENU_RIGHT,                                                 /*  右翻页                      */
        KEY_MENU_UP,                                                    /*  上翻菜单                    */
        KEY_MENU_DOWN,                                                  /*  下翻菜单                    */
        KEY_INC,                                                        /*  加1计数                     */
        KEY_DEC,                                                        /*  减1计数                     */
        KEY_ENTER,                                                      /*  确认                        */
        KEY_AUX_LEFT,                                                   /*  左辅助                      */
        KEY_AUX_RIGHT,                                                  /*  右辅助                      */
        KEY_FRT_LEG_LOW,                                                /*  降前立柱（左）              */
        KEY_FRT_LEG_SET,                                                /*  升前立柱（左）              */
        KEY_MID_LEG_LOW,                                                /*  降中立柱                    */
        KEY_MID_LEG_SET,                                                /*  升中立柱                    */        
        KEY_REAR_LEG_LOW,                                               /*  降后立柱（右）              */
        KEY_REAR_LEG_SET,                                               /*  升后立柱（右）              */
        KEY_TAIL_GIRDER_OUT,                                            /*  伸尾梁                      */
        KEY_TAIL_GIRDER_IN,                                             /*  收尾梁                      */
        KEY_FLASHBOARD_OUT,                                             /*  伸插板                      */
        KEY_FLASHBOARD_IN,                                              /*  收插板                      */
        KEY_REAR_CONV_PUSH,                                             /*  伸后溜                      */
        KEY_REAR_CONV_PULL,                                             /*  拉后溜                      */
        KEY_FRT_GIRDER_OUT,                                             /*  伸前梁                      */
        KEY_FRT_GIRDER_IN,                                              /*  收前梁                      */
        KEY_FILTRATE_1,                                                 /*  反冲洗1                     */
        KEY_FILTRATE_2,                                                 /*  反冲洗2                     */        
        KEY_FLIRT_OUT,                                                  /*  伸摆梁                      */
        KEY_FLIRT_IN,                                                   /*  收摆梁                      */
        KEY_CONV_BATCH_PUSH,                                            /*  成组推溜                    */
        KEY_CONV_BATCH_PULL,                                            /*  成组拉溜                    */
        KEY_STAB1_BATCH_OUT,                                            /*  成组伸一级护帮板            */
        KEY_STAB1_BATCH_IN,                                             /*  成组收一级护帮板            */
        KEY_STAB2_BATCH_OUT,                                            /*  成组伸二级护帮板            */
        KEY_STAB2_BATCH_IN,                                             /*  成组收二级护帮板            */
        KEY_FRT_GIRDER_BATCH_OUT,                                       /*  成组伸前梁                  */
        KEY_FRT_GIRDER_BATCH_IN,                                        /*  成组收前梁                  */
        KEY_REAR_CONV_BATCH_PULL,                                       /*  成组拉后溜                  */
        KEY_FLIP_BATCH_OUT,                                             /*  成组伸伸缩梁                */
        KEY_FLIP_BATCH_IN,                                              /*  成组收伸缩梁                */
        KEY_STAB3_BATCH_OUT,                                            /*  伸三级护帮                  */
        KEY_STAB3_BATCH_IN,                                             /*  收三级护帮                  */        
        KEY_REAR_CONV_SELF_PULL,                                        /*  本架拉后溜                  */
        KEY_CONV_SELF_PUSH,                                             /*  本架推溜                    */        
        KEY_SIDE_SELF_OUT,                                              /*  本架伸侧护                  */
        KEY_BSPRAY_ON,                                                  /*  放煤喷雾                    */
        KEY_ASPRAY_ON,                                                  /*  顶梁喷雾                    */
        KEY_ESPRAY_ON,                                                  /*  机道喷雾                    */       
        KEY_FILTRATE_3,                                                 /*  反冲洗3                     */
        KEY_FILTRATE_4,                                                 /*  反冲洗4                     */  
        KEY_TAIL_PILLAR_OUT,                                            /*  升尾柱                      */
        KEY_TAIL_PILLAR_IN,                                             /*  收尾柱                      */
        KEY_BSPRAY_BATCH,                                               /*  成组放煤喷雾                */
        KEY_ASPRAY_BATCH,                                               /*  成组顶梁喷雾                */
        KEY_ESPRAY_BATCH,                                               /*  成组机道喷雾                */
        KEY_SPRAY_BATCH,                                                /*  成组喷雾                    */
        KEY_WORK_STAT,                                                  /*  工况                        */
        KEY_STAB_LINKAGE,                                               /*  护帮板联动动作              */
        KEY_FILTRATE_BATCH,                                             /*  成组反冲洗按键              */
        KEY_RTC,                                                        /*  时钟显示快捷按键            */
        KEY_PSA_PARA,                                                   /*  立柱补压参数快捷键升柱键关联*/
        KEY_PSA,                                                        /*  立柱补压功能快捷键          */
        KEY_PSA_2,                                                      /*  立柱补压功能快捷键-组合键2  */
        KEY_SELF,                                                       /*  本架自控                    */
        KEY_HEAD_RIGHT_UP,                                              /*  头右升                      */
        KEY_HEAD_LEFT_UP,                                               /*  头左升                      */
        KEY_HEAD_RIGHT_DOWN,                                            /*  头右降                      */
        KEY_HEAD_LEFT_DOWN,                                             /*  头左降                      */
        KEY_TAIL_LEFT_UP,                                               /*  尾左升                      */
        KEY_TAIL_RIGHT_UP,                                              /*  尾右升                      */
        KEY_TAIL_RIGHT_DOWN,                                            /*  尾右降                      */
        KEY_LEFT_PUSHER_OUT,                                            /*  左推伸                      */
        KEY_LEFT_PUSHER_IN,                                             /*  左推收                      */
        KEY_HEAD_LEFT_MOVE,                                             /*  头左移                      */
        KEY_HEAD_RIGHT_MOVE,                                            /*  头右移                      */
        KEY_TAIL_LEFT_MOVE,                                             /*  尾左移                      */
        KEY_TAIL_RIGHT_MOVE,                                            /*  尾右移                      */
        KEY_RIGHT_PUSHER_OUT,                                           /*  右推伸                      */
        KEY_RIGHT_PUSHER_IN,                                            /*  右推收                      */
        KEY_TAIL_LEFT_DOWN,                                             /*  尾左降                      */
        KEY_PUSHER_OUT,                                                 /*  推移伸                      */
        KEY_PUSHER_IN,                                                  /*  推移收                      */
        KEY_LEFT_FLIP_OUT,                                              /*  左伸缩伸                    */
        KEY_LEFT_FLIP_IN,                                               /*  左伸缩收                    */
        KEY_RIGHT_FLIP_OUT,                                             /*  右伸缩伸                    */
        KEY_RIGHT_FLIP_IN,                                              /*  右伸缩收                    */
        KEY_STRIPE_OUT,                                                 /*  挑带伸                      */
        KEY_STRIPE_IN,                                                  /*  挑带收                      */
        KEY_SIDE_1_OUT,                                                 /*  侧一伸                      */
        KEY_SIDE_1_IN,                                                  /*  侧一收                      */
        KEY_SIDE_2_OUT,                                                 /*  侧二伸                      */
        KEY_SIDE_2_IN,                                                  /*  侧二收                      */
        KEY_SIDE_3_OUT,	                                                /*  侧三伸                      */
        KEY_SIDE_3_IN,                                                  /*  侧三收                      */
        KEY_SIDE_4_OUT,	                                                /*  侧四伸                      */
        KEY_SIDE_4_IN,                                                  /*  侧四收                      */
        KEY_LIFT_OUT,                                                   /*  抬架伸                      */
        KEY_LIFT_IN,                                                    /*  抬架收                      */
        KEY_BASE_PUSHER_LEFT,                                           /*  底调左                      */
        KEY_BASE_PUSHER_RIGHT,                                          /*  底调右                      */
        KEY_BASE_PUSHER_UP,                                             /*  底调上                      */
        KEY_BASE_PUSHER_DOWN,                                           /*  底调下                      */
        KEY_CEILING_GIRDER_OUT,                                         /*  顶梁伸                      */
        KEY_CEILING_GIRDER_IN,                                          /*  顶梁收                      */   
} KEY_INDEX; 



extern const INT32U GuiUnlockPwd[3];
extern const INT32U *GpuiKeyTbl;

/*********************************************************************************************************
** Function name:       keyTblGet
** Descriptions:        键盘上按键动作初始化
** input parameters:    ucNo                    架号
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
extern const INT32U *keyTblGet(INT8U ucNo);

/*********************************************************************************************************
** Function name:       keyToAction
** Descriptions:        将动作转化成相应电磁阀开关量
** input parameters:    uiKeyValue              按下的键值
**                      puiKeyTbl               按键动作表
**                      puiValveTbl             电磁阀口动作表
**                      
** output parameters:   None
** Returned value:      阀驱动标识
*********************************************************************************************************/
extern INT32U keyToAction(INT32U uiKeyValue, const INT32U *puiKeyTbl, const INT32U *puiValveTbl);

/*********************************************************************************************************
** Function name:       keyAuxToValve
** Descriptions:        将辅助动作菜单的对应动作转换成电磁阀码
** input parameters:    ucRow:          辅助菜单的哪一个行
**                      ucRowFocus：    反显的是第一行还是第二行
**                      ucIsAuxRight:   0/1 左辅助/右辅助
** output parameters:   None
** Returned value:      电磁阀码
*********************************************************************************************************/
extern INT32U keyAuxToValve(INT8U ucRow, const INT32U *puiValveTbl, INT8U ucIsAuxRight);


/*********************************************************************************************************
** Function name:       keyToNum
** Descriptions:        键盘转数字
** input parameters:    uiKeyCode               键值
** output parameters:   None  
** Returned value:      数字 如无效则返回0x0f,加1键返回0x0a，减1键返回0x0b
*********************************************************************************************************/
extern INT8U keyToNum(INT32U uiKeyCode);

/*********************************************************************************************************
** Function name:       keyNum
** Descriptions:        按下键个数判断
** input parameters:    uiKeyCode               键值
** output parameters:   None  
** Returned value:      按键个数
*********************************************************************************************************/
extern INT8U keyNum(INT32U uiKeyCode);

/*********************************************************************************************************
** Function name:       keyShow
** Descriptions:        键盘闭锁时的键值显示
** input parameters:    uiKeyCode               按键值
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
extern void keyShow(INT32U uiKeyCode);

/*********************************************************************************************************
** Function name:       ledNavi
** Descriptions:        导航灯亮
** input parameters:    uiLedNavi               导航指示灯的位掩码取反
** Returned value:      void
*********************************************************************************************************/
extern void ledNavi(INT32U uiLedNavi);

/*********************************************************************************************************
** Function name:       ledComm
** Descriptions:        通信导航灯闪烁
** input parameters:    ucLedNo                 指示灯编号
** Returned value:      void
*********************************************************************************************************/
extern void ledComm(INT8U ucLedNo);		


#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __KEY_H                     */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/


