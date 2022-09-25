/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn  
**
**--------------File Info---------------------------------------------------------------------------------
**  File name :         valve.h
**  Last modified Date :
**  Last Version :      V1.00
**  Descriptions :      电磁先导阀驱动器操作函数集头文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:          
** Created date:        2014-08-25
** Version:             V1.00
** Descriptions :      
**--------------------------------------------------------------------------------------------------------
** Modified by :        
** Modified date :      
** Version :            
** Descriptions :       
*********************************************************************************************************/
#ifndef __VALVE_H
#define __VALVE_H	

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
    阀动作相关定义
*********************************************************************************************************/
#define VALVE_MAX                   0x3c                                /*  阀动作数组长度              */
#if 1
typedef enum {
            VALVE_INIT,
            LEG_LOW,                                                    /*  降柱                        */
            CONV_PULL,                                                  /*  移架                        */
            LEG_SET,                                                    /*  升柱                        */
            CONV_PUSH,                                                  /*  推溜                        */
            BASE_LIFT_SET,                                              /*  抬底                        */
            STREB_OUT,                                                  /*  伸平衡                      */
            STREB_IN,                                                   /*  收平衡                      */
            FLIP_OUT,                                                   /*  伸伸缩梁                    */
            FLIP_IN,                                                    /*  收伸缩梁                    */
            STAB_OUT,                                                   /*  伸一级护帮                  */
            STAB_IN,                                                    /*  收一级护帮                  */
            STAB2_OUT,                                                  /*  伸二级护帮                  */
            STAB2_IN,                                                   /*  收二级护帮                  */
            SPARY_ON,                                                   /*  喷雾                        */
            SIDE_IN,                                                    /*  收侧护                      */
            SIDE_OUT,                                                   /*  伸侧护                      */
            BASE_PUSHER_IN,                                             /*  收底调                      */
            BASE_PUSHER_OUT,                                            /*  伸底调                      */
            FRT_LEG_LOW,                                                /*  降前立柱（左）              */
            FRT_LEG_SET,                                                /*  升前立柱（左）              */
            REAR_LEG_LOW,                                               /*  降后立柱（右）              */
            REAR_LEG_SET,                                               /*  升后立柱（右）              */
            TAIL_GIRDER_OUT,                                            /*  伸尾梁                      */
            TAIL_GIRDER_IN,                                             /*  收尾梁                      */
            FLASHBOARD_OUT,                                             /*  伸插板                      */
            FLASHBOARD_IN,                                              /*  收插板                      */
            REAR_CONV_PUSH,                                             /*  伸后溜                      */
            REAR_CONV_PULL,                                             /*  拉后溜                      */
            FRT_GIRDER_OUT,                                             /*  伸前梁                      */
            FRT_GIRDER_IN,                                              /*  收前梁                      */
            FILTRATE_1,                                                 /*  反冲洗1                     */
            FILTRATE_2,                                                 /*  反冲洗2                     */
            FLIRT_OUT,                                                  /*  伸摆梁                      */
            FLIRT_IN,                                                   /*  收摆梁                      */
            STAB3_OUT,                                                  /*  伸三级护帮                  */
            STAB3_IN,                                                   /*  收三级护帮                  */
            FILTRATE_3,                                                 /*  反冲洗3                     */
            FILTRATE_4,                                                 /*  反冲洗4                     */
            BSPARY_ON,                                                  /*  放煤喷雾                    */
            ASPARY_ON,                                                  /*  顶梁喷雾                    */
            ESPARY_ON,                                                  /*  机道喷雾                    */
            TAIL_PILLAR_OUT,                                            /*  升尾柱                      */
            TAIL_PILLAR_IN,                                             /*  收尾柱                      */
            RSV1,                                                       /*  备用1                       */
            STAB_LINKAGE,                                               /*  护帮板联动动作              */
            RSV2,                                                       /*  备用2                       */
            RSV3,                                                       /*  备用3                       */
            RSV4,                                                       /*  备用4                       */
            RSV5,                                                       /*  备用5                       */
            RSV6,                                                       /*  备用6                       */
            CEILING_GIRDER_SIDE_OUT,                                    /*  伸顶梁侧护                  */
            CEILING_GIRDER_SIDE_IN,                                     /*  收顶梁侧护                  */
            COVERING_GIRDER_SIDE_OUT,                                   /*  伸掩护梁侧护                */
            COVERING_GIRDER_SIDE_IN,                                    /*  收掩护梁侧护                */
            MID_LEG_LOW,                                                /*  降中柱                      */
            MID_LEG_SET,                                                /*  升中柱                      */ 
            HEAD_RIGHT_UP,                                              /*  机头右升                    */
            HEAD_LEFT_UP,                                               /*  机头左升                    */
            HEAD_RIGHT_DOWN,                                            /*  机头右降                    */
            HEAD_LEFT_DOWN,                                             /*  机头左降                    */
            TAIL_LEFT_UP,                                               /*  机尾左升                    */
            TAIL_RIGHT_UP,                                              /*  机尾右升                    */
            TAIL_RIGHT_DOWN,                                            /*  机尾右降                    */
            LEFT_PUSHER_OUT,                                            /*  左推移伸                    */
            LEFT_PUSHER_IN,                                             /*  左推移收                    */ 
            HEAD_LEFT_MOVE,                                             /*  头左移                      */
            HEAD_RIGHT_MOVE,                                            /*  头右移                      */
            TAIL_LEFT_MOVE,                                             /*  尾左移                      */
            TAIL_RIGHT_MOVE,                                            /*  尾右移                      */
            RIGHT_PUSHER_OUT,                                           /*  右推伸                      */
            RIGHT_PUSHER_IN,                                            /*  右推收                      */            
            TAIL_LEFT_DOWN,                                             /*  尾左降                      */     
            LEFT_ROLLER_UP,                                             /*  左托辊升                    */
            LEFT_ROLLER_DOWN,                                           /*  左托辊降                    */
            RIGHT_ROLLER_UP,                                            /*  右托辊升                    */
            RIGHT_ROLLER_DOWN,                                          /*  右托辊降                    */      
            PUSHER_OUT,                                                 /*  推移伸                      */
            PUSHER_IN,                                                  /*  推移收                      */
            LEFT_FLIP_OUT,                                              /*  左伸缩伸                    */
            LEFT_FLIP_IN,                                               /*  左伸缩收                    */
            RIGHT_FLIP_OUT,                                             /*  右伸缩伸                    */
            RIGHT_FLIP_IN,                                              /*  右伸缩收                    */
            STRIPE_OUT,                                                 /*  挑带伸                      */
            STRIPE_IN,                                                  /*  挑带收                      */
            SIDE_1_OUT,                                                 /*  侧一伸                      */
            SIDE_1_IN,                                                  /*  侧一收                      */
            SIDE_2_OUT,                                                 /*  侧二伸                      */
            SIDE_2_IN,                                                  /*  侧二收                      */
            SIDE_3_OUT,	                                                /*  侧三伸                      */
            SIDE_3_IN,                                                  /*  侧三收                      */
            SIDE_4_OUT,	                                                /*  侧四伸                      */
            SIDE_4_IN,                                                  /*  侧四收                      */
            LIFT_OUT,                                                   /*  抬架伸                      */
            LIFT_IN,                                                    /*  抬架收                      */
            BASE_PUSHER_LEFT,                                           /*  底调左                      */
            BASE_PUSHER_RIGHT,                                          /*  底调右                      */
            BASE_PUSHER_UP,                                             /*  底调上                      */
            BASE_PUSHER_DOWN,                                           /*  底调下                      */
            CEILING_GIRDER_OUT,                                         /*  顶梁伸                      */
            CEILING_GIRDER_IN,                                          /*  顶梁收                      */            
            
} VALVE_INDEX; 
#endif

#if 0
typedef enum {                                                          /*  电磁阀定义表                */
            VALVE_INIT,                                                 /*  电磁阀初始化                */
            HEAD_RIGHT_UP,                                              /*  机头右升                    */
            HEAD_LEFT_UP,                                               /*  机头左升                    */
            HEAD_RIGHT_DOWN,                                            /*  机头右降                    */
            HEAD_LEFT_DOWN,                                             /*  机头左降                    */
            TAIL_LEFT_UP,                                               /*  机尾左升                    */
            TAIL_RIGHT_UP,                                              /*  机尾右升                    */
            TAIL_RIGHT_DOWN,                                            /*  机尾右降                    */
            LEFT_PUSHER_OUT,                                            /*  左推移伸                    */
            LEFT_PUSHER_IN,                                             /*  左推收                      */
            HEAD_LEFT_MOVE,                                             /*  头左移                      */
            HEAD_RIGHT_MOVE,                                            /*  头右移                      */
            TAIL_LEFT_MOVE,                                             /*  尾左移                      */
            TAIL_RIGHT_MOVE,                                            /*  尾右移                      */
            RIGHT_PUSHER_OUT,                                           /*  右推伸                      */
            RIGHT_PUSHER_IN,                                            /*  右推收                      */
            TAIL_LEFT_DOWN,                                             /*  尾左降                      */
            PUSHER_OUT,                                                 /*  推移伸                      */
            PUSHER_IN,                                                  /*  推移收                      */
            LEFT_FLIP_OUT,                                              /*  左伸缩伸                    */
            LEFT_FLIP_IN,                                               /*  左伸缩收                    */
            RIGHT_FLIP_OUT,                                             /*  右伸缩伸                    */
            RIGHT_FLIP_IN,                                              /*  右伸缩收                    */
            STRIPE_OUT,                                                 /*  挑带伸                      */
            STRIPE_IN,                                                  /*  挑带收                      */
            SIDE_1_OUT,                                                 /*  侧一伸                      */
            SIDE_1_IN,                                                  /*  侧一收                      */
            SIDE_2_OUT,                                                 /*  侧二伸                      */
            SIDE_2_IN,                                                  /*  侧二收                      */
            SIDE_3_OUT,	                                                /*  侧三伸                      */
            SIDE_3_IN,                                                  /*  侧三收                      */
            FLIRT_OUT,                                                  /*  伸摆梁                      */
            FLIRT_IN,                                                   /*  收摆梁                      */
//            STAB3_OUT,                                              /*  伸三级护帮                  */
//            STAB3_IN,                                              /*  收三级护帮                  */
            FILTRATE_3,                                                 /*  反冲洗3                     */
            FILTRATE_4,                                                 /*  反冲洗4                     */
            BSPARY_ON,                                                  /*  放煤喷雾                    */
            ASPARY_ON,                                                  /*  顶梁喷雾                    */
            ESPARY_ON,                                                  /*  机道喷雾                    */
            TAIL_PILLAR_OUT,                                            /*  升尾柱                      */
            TAIL_PILLAR_IN,                                             /*  收尾柱                      */
            RSV1,                                                       /*  备用1                       */
            STAB_LINKAGE,                                               /*  护帮板联动动作              */
            RSV2,                                                       /*  备用2                       */
            RSV3,                                                       /*  备用3                       */
            RSV4,                                                       /*  备用4                       */
            RSV5,                                                       /*  备用5                       */
            RSV6,                                                       /*  备用6                       */
            CEILING_GIRDER_SIDE_OUT,                                    /*  伸顶梁侧护                  */
            CEILING_GIRDER_SIDE_IN,                                     /*  收顶梁侧护                  */
            COVERING_GIRDER_SIDE_OUT,                                   /*  伸掩护梁侧护                */
            COVERING_GIRDER_SIDE_IN,                                    /*  收掩护梁侧护                */
            MID_LEG_LOW,                                                /*  降中柱                      */
            MID_LEG_SET,                                                /*  升中柱                      */ 
} VALVE_INDEX;
#endif
    /*
     *  关于支架动作的上位机通信协议
     */        
#define LEG_SET_PC                  0x00000001                          /*  升柱                        */
#define LEG_LOW_PC                  0x00000002                          /*  降柱                        */
#define CONV_PUSH_PC                0x00000004                          /*  推溜                        */
#define CONV_PULL_PC                0x00000008                          /*  移架                        */
#define BASE_LIFT_SET_PC            0x00000010                          /*  抬底                        */
#define SPARY_ON_PC                 0x00000020                          /*  喷雾                        */
#define SIDE_OUT_PC                 0x00000040                          /*  伸前侧护板                  */
#define SIDE_IN_PC                  0x00000080                          /*  收前侧护板                  */
#define STREB_OUT_PC                0x00000100                          /*  伸平衡                      */
#define STREB_IN_PC                 0x00000200                          /*  收平衡                      */
#define FLIP_OUT_PC                 0x00000400                          /*  伸伸缩梁                    */
#define FLIP_IN_PC                  0x00000800                          /*  收伸缩梁                    */
#define STAB_OUT_PC                 0x00001000                          /*  伸一级护帮                  */
#define STAB_IN_PC                  0x00002000                          /*  收一级护帮                  */
#define STAB2_OUT_PC                0x00004000                          /*  伸二级护帮                  */
#define STAB2_IN_PC                 0x00008000                          /*  收二级护帮                  */
#define STAB3_OUT_PC                0x00010000                          /*  伸三级护帮                  */
#define STAB3_IN_PC                 0x00020000                          /*  收三级护帮                  */
#define FRT_GIRDER_OUT_PC           0x00040000                          /*  伸前梁                      */
#define FRT_GIRDER_IN_PC            0x00080000                          /*  收前梁                      */
#define ACTION_PUSHER_OUTPC         0x00100000                          /*  伸底调                      */
#define ACTION_PUSHER_INPC          0x00200000                          /*  收底调                      */
#define TAIL_GIRDER_OUT_PC          0x00400000                          /*  伸尾梁                      */
#define TAIL_GIRDER_IN_PC           0x00800000                          /*  收尾梁                      */
#define FLASHBOARD_OUT_PC           0x01000000                          /*  伸插板                      */
#define FLASHBOARD_IN_PC            0x02000000                          /*  收插板                      */
#define BSPARY_ON_PC                0x04000000                          /*  放煤喷雾                    */
#define ESPARY_ON_PC                0x08000000                          /*  机道喷雾                    */
#define REAR_CONV_PUSH_PC           0x10000000                          /*  伸后溜                      */
#define REAR_CONV_PULL_PC           0x20000000                          /*  拉后溜                      */
#define FRT_LEG_SET_PC              0x40000000                          /*  升前立柱（左）              */
#define REAR_LEG_SET_PC             0x80000000                          /*  升后立柱（右）              */


#define LEFT_LEG_SET_PC             0x00000001                          /*  升左立柱                    */
#define RIGHT_LEG_SET_PC            0x00000002                          /*  升右立柱                    */
#define ASPARY_ON_PC                0x00000004                          /*  顶梁喷雾                    */

#define TAIL_PILLAR_OUT_PC          0x00000020                          /*  升尾柱                      */
#define TAIL_PILLAR_IN_PC           0x00000040                          /*  收尾柱                      */
#define FLIRT_OUT_PC                0x00000080                          /*  伸摆梁                      */
#define FLIRT_IN_PC                 0x00000100                          /*  收摆梁                      */
#define FILTRATE_1_PC               0x00000200                          /*  反冲洗1                     */
#define FILTRATE_2_PC               0x00000400                          /*  反冲洗2                     */
#define FILTRATE_3_PC               0x00000800                          /*  反冲洗3                     */
#define FILTRATE_4_PC               0x00001000                          /*  反冲洗4                     */
#define FRT_LEG_LOW_PC              0x00002000                          /*  降前立柱                    */
#define REAR_LEG_LOW_PC             0x00004000                          /*  降后立柱                    */

#define LEFT_LEG_LOW_PC             0x00020000                          /*  降左立柱                    */
#define RIGHT_LEG_LOW_PC            0x00040000                          /*  降右立柱                    */


extern const INT32U       __SuiValveMiddle[VALVE_MAX];     /*电磁阀定义表（中间），以后只需更新此表*/
extern const INT32U       __SuiValveTransition[VALVE_MAX];     /*电磁阀定义表(端头)，以后只需更新此表*/
extern const INT32U       __SuiValveEnd[VALVE_MAX];     /*电磁阀定义表(端头)，以后只需更新此表*/

extern INT32U       GuiValveSnrRelation;		  //传感器相关参数
extern INT32U       GuiShieldType; 	      //支架功能配置
extern INT32U       GuiPressureSnrNum; 


extern const INT32U *valveTblGet(INT8U ucShieldNum);
extern INT32U       ValveOpposite(INT32U valve_data, const INT32U *puiValveTbl);
extern void         drvPwrDown(void);
extern void         drvPwrUp(void);
extern void         ShieldHandle(INT32U valve_open);

extern const INT32U *GpuiValveTbl;
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __VALVE_H                   */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

