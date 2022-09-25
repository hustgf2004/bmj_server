/****************************************Copyright (c)****************************************************
**                      Beijing Huatai Industrial Equipment Co.,Ltd.
**                                      
**                                 http://www.huatai.com.cn  
**
**--------------File Info---------------------------------------------------------------------------------
**  File name :         valve.c
**  Last modified Date :
**  Last Version :      V1.00
**  Descriptions :      电磁先导阀驱动器操作函数集
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

#include  "main.h"


const INT32U    *GpuiValveTbl;                                         /*  本架阀动作表                */





/*********************************************************************************************************
    电磁阀口定义表
*********************************************************************************************************/
const INT32U    __SuiValveTbl[] = {                                     /*  电磁阀定义表                */
                        0x00000000,		                                /*  电磁阀初始化                */
                        0x00000000,  	                                /*  降柱                        */
                        0x00000000,		                                /*  移架                        */
                        0x00000000,		                                /*  升柱                        */
                        0x00000000,		                                /*  推溜                        */
                        0x00000000,		                                /*  抬底                        */
                        0x00000000,		                                /*  伸平衡                      */
                        0x00000000,		                                /*  收平衡                      */
                        0x00000000,		                                /*  伸伸缩梁                    */
                        0x00000000,		                                /*  收伸缩梁                    */
                        0x00000000,		                                /*  伸一级护帮                  */
                        0x00000000,		                                /*  收一级护帮                  */
                        0x00000000,		                                /*  伸二级护帮                  */
                        0x00000000,		                                /*  收二级护帮                  */
                        0x00000000,		                                /*  喷雾                        */
                        0x00000000,		                                /*  收侧护                      */
                        0x00000000,		                                /*  伸侧护                      */
                        0x00000000,		                                /*  收底调                      */
                        0x00000000,		                                /*  伸底调                      */
                        0x00000000,                                     /*  降前立柱（左）              */
                        0x00000000,                                     /*  升前立柱（左）              */
                        0x00000000,                                     /*  降后立柱（右）              */
                        0x00000000,                                     /*  升后立柱（右）              */
                        0x00000000,                                     /*  伸尾梁                      */
                        0x00000000,                                     /*  收尾梁                      */
                        0x00000000,                                     /*  伸插板                      */
                        0x00000000,                                     /*  收插板                      */
                        0x00000000,                                     /*  伸后溜                      */  
                        0x00000000,                                     /*  拉后溜                      */
                        0x00000000,                                     /*  伸前梁                      */
                        0x00000000,                                     /*  收前梁                      */
                        0x04000000,	                                    /*  反冲洗1                     */
                        0x08000000,                                     /*  反冲洗2                     */
                        0x00000000,                                     /*  伸摆梁                      */
                        0x00000000,                                     /*  收摆梁                      */
                        0x00000000,                                     /*  伸三级护帮                  */
                        0x00000000,                                     /*  收三级护帮                  */
                        0x00000000,                                     /*  反冲洗3                     */
                        0x00000000,                                     /*  反冲洗4                     */
                        0x00000000,                                     /*  放煤喷雾                    */
                        0x00000000,                                     /*  顶梁喷雾                    */
                        0x00000000,                                     /*  机道喷雾                    */
                        0x00000000,                                     /*  升尾柱                      */
                        0x00000000,                                     /*  收尾柱                      */
                        0x00000000,                                     /*  备用1                       */
                        0x00000000,                                     /*  护帮板联动动作              */
                        0x00000000,                                     /*  备用2                       */
                        0x00000000,                                     /*  备用3                       */
                        0x00000000,                                     /*  备用4                       */
                        0x00000000,                                     /*  备用5                       */
                        0x00000000,                                     /*  备用6                       */
                        0x00000000,                                     /*  伸顶梁侧护                  */
                        0x00000000,                                     /*  收顶梁侧护                  */            
                        0x00000000,                                     /*  伸掩护梁侧护                */
                        0x00000000,                                     /*  收掩护梁侧护                */                            
                        0x00000000,                                     /*  降中柱                      */
                        0x00000000,                                     /*  升中柱                      */
                        0x00000000,                                     /*  机头右升                    */
                        0x00000000,                                     /*  机头左升                    */
                        0x00000000,                                     /*  机头右降                    */
                        0x00000000,                                     /*  机头左降                    */
                        0x00000000,                                     /*  机尾左升                    */
                        0x00000000,                                     /*  机尾右升                    */
                        0x00000000,                                     /*  机尾右降                    */
                        0x00000000,                                     /*  左推移伸                    */
                        0x00000000,                                     /*  左推移收                    */
                        0x00000000,                                     /*  机头左移                    */
                        0x00000000,                                     /*  机头右移                    */
                        0x00000000,                                     /*  机尾左移                    */
                        0x00000000,                                     /*  机尾右移                    */
                        0x00000000,                                     /*  右推移伸                    */
                        0x00000000,                                     /*  右推移收                    */
                        0x00000000,                                     /*  机尾左降                    */
                        0x00000000,                                     /*  左托辊升                    */
                        0x00000000,                                     /*  左托辊降                    */
                        0x00000000,                                     /*  右托辊升                    */
                        0x00000000,                                     /*  右托辊降                    */
                        0x00000001,                                     /*  推移伸                      */
                        0x00000002,                                     /*  推移收                      */
                        0x00000000,                                     /*  左伸缩伸                    */
                        0x00000000,                                     /*  左伸缩收                    */
                        0x00000000,                                     /*  右伸缩伸                    */
                        0x00000000,                                     /*  右伸缩收                    */
                        0x00000000,                                     /*  挑带伸                      */
                        0x00000000,                                     /*  挑带收                      */
                        0x00000000,                                     /*  侧一伸                      */
                        0x00000000,                                     /*  侧一收                      */
                        0x00000000,                                     /*  侧二伸                      */
                        0x00000000,                                     /*  侧二收                      */
                        0x00000000,	                                    /*  侧三伸                      */
                        0x00000000,                                     /*  侧三收                      */
                        0x00000000,	                                    /*  侧四伸                      */
                        0x00000000,                                     /*  侧四收                      */
                        0x00000004,                                     /*  抬架伸                      */
                        0x00000008,                                     /*  抬架收                      */
                        0x00000010,                                     /*  底调左                      */
                        0x00000020,                                     /*  底调右                      */
                        0x00000040,                                     /*  底调上                      */
                        0x00000080,                                     /*  底调下                      */
                        0x00000100,                                     /*  顶梁伸                      */
                        0x00000200,                                     /*  顶梁收                      */                           
};
                        

                            
                            
/*********************************************************************************************************
**  定义单动动作显示
**  注意此处定义应同valve_define[i]的定义相同
*********************************************************************************************************/
static const char __SscJockeyNameTbl[][16] = {
                            "        ",                                 /*  无显示                      */
                            "降柱",                                     /*  降柱                        */
                            "移架",                                     /*  移架                        */
                            "升柱",                                     /*  升柱                        */
                            "推溜",                                     /*  推溜                        */
                            "抬底",                                     /*  抬底                        */
                            "伸平衡",                                   /*  伸平衡                      */
                            "收平衡",                                   /*  收平衡                      */
                            "伸伸缩梁",                                 /*  伸伸缩梁                    */
                            "收伸缩梁",                                 /*  收伸缩梁                    */
                            "伸护帮板",                                 /*  伸一级护帮                  */
                            "收护帮板",                                 /*  收一级护帮                  */
                            "伸二级护帮",                               /*  伸二级护帮                  */
                            "收二级护帮",                               /*  收二级护帮                  */
//                            "伸三级护帮",                                 /*  伸三级护帮                  */
//                            "收三级护帮",                                 /*  收三级护帮                  */
                            "喷雾",                                     /*  喷雾                        */
                            "收侧护",                                   /*  收侧护                      */
                            "伸侧护",                                   /*  伸侧护                      */
                            "收底调",                                   /*  收底调                      */
                            "伸底调",                                   /*  伸底调                      */
                            "降前柱",                                   /*  降前立柱（左）              */
                            "升前柱",                                   /*  升前立柱（左）              */                           
                            "降后柱",                                   /*  降后立柱（右）              */
                            "升后柱",                                   /*  升后立柱（右）              */
                            "伸尾梁",                                   /*  伸尾梁                      */
                            "收尾梁",                                   /*  收尾梁                      */
                            "收插板",                                   /*  伸插板                      */
                            "伸插板",                                   /*  收插板                      */
                            "伸后溜",                                   /*  伸后溜                      */  
                            "拉后溜",                                   /*  拉后溜                      */
                            "伸前梁",                                   /*  伸前梁                      */
                            "收前梁",                                   /*  收前梁                      */
                            "反冲洗1",	                                /*  反冲洗1                     */
                            "反冲洗2",                                  /*  反冲洗2                     */
                            "伸摆梁",                                   /*  伸摆梁                      */
                            "收摆梁",                                   /*  收摆梁                      */
                            "伸三级护帮",                               /*  伸三级护帮                  */
                            "收三级护帮",                               /*  收三级护帮                  */
                            "反冲洗3",                                  /*  反冲洗3                     */
                            "反冲洗4",                                  /*  反冲洗4                     */
                            "收抬底",                                   /*  放煤喷雾                    */
                            "伸调架",                                   /*  顶梁喷雾                    */
                            "收调架",                                   /*  机道喷雾                    */
                            "升尾柱",                                   /*  升尾柱                      */
                            "收尾柱",                                   /*  收尾柱                      */
                            "备用1B",                                   /*  备用1                       */
                            "收1-3护帮板联动",                          /*  护帮板联动动作              */
                            "备用1A",                                   /*  备用2                       */
                            "备用2B",                                   /*  备用3                       */
                            "备用2A",                                   /*  备用4                       */
                            "备用5",                                    /*  备用5                       */
                            "备用6",                                    /*  备用6                       */
                            "顶梁侧护伸",                               /*  伸顶梁侧护                  */
                            "顶梁侧护收",                               /*  收顶梁侧护                  */            
                            "掩护梁侧护伸",                             /*  伸掩护梁侧护                */
                            "掩护梁侧护收",                             /*  收掩护梁侧护                */                            
                            "降中柱",                                   /*  降中柱                      */
                            "升中柱",                                   /*  升中柱                      */                                 
                            "机头右升",                                 /*  机头右升                    */
                            "机头左升",                                 /*  机头左升                    */
                            "机头右降",                                 /*  机头右降                    */
                            "机头左降",                                 /*  机头左降                    */
                            "机尾左升",                                 /*  机尾左升                    */
                            //"机尾左降",                                 /*  机尾左降                    */
                            "机尾右升",                                 /*  机尾右升                    */
                            "机尾右降",                                 /*  机尾右降                    */
                            "左推移伸",                                 /*  左推移伸                    */
                            "左推移收",                                 /*  左推移收                    */
                            "机头左移",                                 /*  机头左移                    */
                            "机头右移",                                 /*  机头右移                    */
                            "机尾左移",                                 /*  机尾左移                    */
                            "机尾右移",                                 /*  机尾右移                    */
                            "右推移伸",                                 /*  右推移伸                    */
                            "右推移收",                                 /*  右推移收                    */
                            "机尾左降",                                 /*  机尾左降                    */
                            "左托辊升",                                 /*  左托辊升                    */
                            "左托辊降",                                 /*  左托辊降                    */
                            "右托辊升",                                 /*  右托辊升                    */
                            "右托辊降",                                 /*  右托辊降                    */     
                            "推移伸",                                   /*  推移伸                      */
                            "推移收",                                   /*  推移收                      */
                            "左伸缩伸",                                 /*  左伸缩伸                    */
                            "左伸缩收",                                 /*  左伸缩收                    */
                            "右伸缩伸",                                 /*  右伸缩伸                    */
                            "右伸缩收",                                 /*  右伸缩收                    */
                            "挑梁伸",                                   /*  挑带伸                      */
                            "挑梁收",                                   /*  挑带收                      */
                            "侧一伸",                                   /*  侧一伸                      */
                            "侧一收",                                   /*  侧一收                      */
                            "侧二伸",                                   /*  侧二伸                      */
                            "侧二收",                                   /*  侧二收                      */
                            "侧三伸",	                                /*  侧三伸                      */
                            "侧三收",                                   /*  侧三收                      */
                            "侧四伸",	                                /*  侧四伸                      */
                            "侧四收",                                   /*  侧四收                      */
                            "抬架伸",                                   /*  抬架伸                      */
                            "抬架收",                                   /*  抬架收                      */
                            "底调左",                                   /*  底调左                      */
                            "底调右",                                   /*  底调右                      */
                            "底调上",                                   /*  底调上                      */
                            "底调下",                                   /*  底调下                      */
                            "顶梁伸",                                   /*  顶梁伸                      */
                            "顶梁收",                                   /*  顶梁收                      */
                            "伸摆梁",                                   /*  伸摆梁                      */
                            "收摆梁",                                   /*  收摆梁                      */                          
                            "反冲洗3",                                  /*  反冲洗3                     */
                            "反冲洗4",                                  /*  反冲洗4                     */
                            "放煤喷雾",                                 /*  放煤喷雾                    */
                            "顶梁喷雾",                                 /*  顶梁喷雾                    */
                            "机道喷雾",                                 /*  机道喷雾                    */
                            "伸尾柱",                                   /*  升尾柱                      */
                            "收尾柱",                                   /*  收尾柱                      */
                            "备用1A",                                   /*  备用1                       */
                            "收1-3护帮板联动",                          /*  1-3护帮联动                 */
                            "备用1B",                                   /*  备用2                       */
                            "备用2A",                                   /*  备用3                       */
                            "备用2B",                                   /*  备用4                       */
                            "备用3A",                                   /*  备用5                       */
                            "备用3B",                                   /*  备用6                       */
                            "伸顶梁侧护板",
                            "收顶梁侧护板",
                            "伸掩护梁侧护板",
                            "收掩护梁侧护板",
                            "降中柱",                                   /*  降中立柱                    */
                            "升中柱",                                   /*  升中立柱                    */                        
                            };

                               
                            
INT32U      GuiValveSnrRelation;                                               /*  传感器相关参数              */
    
    /*
     *  bit9 三级护帮板：   1-护帮板伸/护帮板收
     *  bit8 二级护帮板：   1-护帮板伸/护帮板收
     *  bit7 推移千斤顶：   1-移架/推溜
     *  bit6 喷水：         1-喷水
     *  bit5 侧护板：       1-侧护板伸/侧护板收
     *  bit4 平衡千斤顶:    1-平衡千斤顶伸/平衡千斤顶收
     *  bit3 一级护帮板：   1-护帮板伸/护帮板收
     *  bit2 伸缩梁：       1-伸缩梁伸/收
     *  bit1 抬底千斤顶     1-抬底
     *  bit0 支架架型       1-四柱支架/0：两柱支架
     */
INT32U      GuiShieldType; 	                                            /*  支架功能配置                */

INT32U      GuiPressureSnrNum;                                               /*  压力传感器数量 1-1个，2-2个 */ 


/*********************************************************************************************************
** Function name:           valveTblGet
** Descriptions:            电磁阀定义
** input parameters:        ucShieldNum         架号 
**                          
** output parameters:       none
** Returned value:          非空                阀口定义表指针
**                          NULL                未定义架号     
*********************************************************************************************************/
const INT32U *valveTblGet(INT8U ucShieldNum)
{
    const INT32U *puiRtn;
    /*
     *  邻架或隔架动作赋值
     */
    if (ucShieldNum >= Gdp.ucMiddleNum1 && 
        ucShieldNum <= Gdp.ucMiddleNum2) {                                 /*  中间架                      */
        puiRtn = __SuiValveTbl;
    } else if ((ucShieldNum <= Gdp.ucMiddleNum3 && ucShieldNum >= Gdp.usGblFaceMin) ||
               (ucShieldNum >= Gdp.ucMiddleNum4 && ucShieldNum <= Gdp.usGblFaceMax)) {
                                                                        /*  端头架                      */
        puiRtn = __SuiValveTbl;
    } else if (ucShieldNum > Gdp.ucMiddleNum3 || ucShieldNum < Gdp.ucMiddleNum4) {
                                                                        /*  过渡架                      */
        puiRtn = __SuiValveTbl;
    } else {
        puiRtn = NULL;
    }
    return puiRtn;    
}


INT32S valveInit(void)
{
            
    /*
     *  本架动作赋值
     */
    if ((Gdp.ucShieldNo >= Gdp.ucMiddleNum1) && 
        (Gdp.ucShieldNo <= Gdp.ucMiddleNum2)) {           /*  中间架                      */
        GpuiValveTbl = __SuiValveTbl;
        GuiShieldType = 0x00BE;
        GuiPressureSnrNum = 1;
    } else if (((Gdp.ucShieldNo <= Gdp.ucMiddleNum3) && (Gdp.ucShieldNo >= Gdp.usGblFaceMin)) || 
               ((Gdp.ucShieldNo >= Gdp.ucMiddleNum4) && (Gdp.ucShieldNo <= Gdp.usGblFaceMax))) {
                                                                        /*  端头架                      */
        GpuiValveTbl = __SuiValveTbl;
        GuiShieldType = 0x0081; 
        GuiPressureSnrNum = 2; 
    } else {                                                        /*  过渡架                      */
        GpuiValveTbl = __SuiValveTbl;        
        GuiShieldType = 0x00a5; 
        GuiPressureSnrNum = 2;      
    }
    /* 
     *  传感器相关参数 
     */
    GuiValveSnrRelation =  GpuiValveTbl[LEG_LOW] | 
                    GpuiValveTbl[CONV_PULL] | 
                    GpuiValveTbl[FRT_LEG_SET] | 
                    GpuiValveTbl[CONV_PUSH] | 
                    GpuiValveTbl[FRT_LEG_LOW] | 
                    GpuiValveTbl[FRT_LEG_SET] | 
                    GpuiValveTbl[REAR_LEG_LOW] | 
                    GpuiValveTbl[REAR_LEG_SET] | 
                    GpuiValveTbl[STAB_OUT] | 
                    GpuiValveTbl[STAB_IN] | 
                    GpuiValveTbl[STAB3_OUT] | 
                    GpuiValveTbl[STAB3_IN]; 
}



static const INT8U __SucValveOpsitTbl[60][2] = {                               /*  互斥动作电磁阀对应表        */
                                    3,  1,                              /*  升柱/降柱                   */
                                    1,  3,//降柱，升柱
                                    4,  2,//推溜，移架
                                    2,  4,//移架，推溜
                                    5,  16,
                                    16, 5,
                                    6,  7,
                                    7,  6,
                                    8,  9,//伸伸缩梁，收伸缩梁
                                    9,  8,//收伸缩梁，伸伸缩梁
                                    10, 11,//伸一级护帮，收一级护帮
                                    11, 10,//收一级护帮，伸一级护帮
                                    12, 13,//伸二级护帮，收二级护帮
                                    13, 12,//收二级护帮，伸二级护帮
                                    14, 15,//伸侧护，收侧护
                                    15, 14,//收侧护，伸侧护
                                    18, 17,//伸一级护帮，收一级护帮
                                    17, 18,//收一级护帮，伸一级护帮
                                    19, 20,//降前立柱，升前立柱
                                    20, 19,//升前立柱，降前立柱
                                    21, 22,//降后立柱，升后立柱
                                    22, 21,//升后立柱，降后立柱
                                    23, 24,//伸尾梁，收尾梁
                                    24, 23,//收尾梁，伸尾梁
                                    25, 26,//伸插板，收插板
                                    26, 25,//收插板，伸插板
                                    27, 28,//伸后溜，拉后溜
                                    28, 27,//拉后溜，伸后溜
                                    29, 30,//伸前梁，收前梁
                                    30, 29,//收前梁，伸前梁
                                    33, 34,//伸摆梁，收摆梁
                                    34, 33,//收摆梁，伸摆梁
                                    31, 32,//反冲洗1，反冲洗2
                                    32, 31,//反冲洗2，反冲洗1
                                    35, 36,//伸三级护帮,收三级护帮
                                    36, 35,//收三级护帮,伸三级护帮
                                    37, 38,//反冲洗3，反冲洗4
                                    38, 37,//反冲洗4，反冲洗3
                                    42, 43,
                                    43, 42,
                                    44, 46,
                                    46, 44,
                                    47, 48,
                                    48, 47,
                                    49, 50,
                                    50, 49,
                                    };                                      
/*********************************************************************************************************
** Function name:           valveOpposite
** Descriptions:            将电磁阀中互斥的电磁阀关掉
** input parameters:        uiValveData: 输入需要处理的电磁阀动作
**                             
**                              
**                             
** output parameters:       none
** Returned value:          处理过的电磁动作
**                               
*********************************************************************************************************/
INT32U valveOpposite(INT32U uiValveData, const INT32U *puiValveTbl)
{
  	INT32U  uiValveDataTmp;
	INT8U i;
	uiValveDataTmp = uiValveData;
    for (i = 0; i < 60; i++) {
        if (uiValveData & puiValveTbl[__SucValveOpsitTbl[i][0]]) {      /*  有互斥动作                  */
            uiValveDataTmp &= ~puiValveTbl[__SucValveOpsitTbl[i][1]];   /*  将相应的互斥动作关掉        */
        }
    }
    return uiValveDataTmp;
}

/*********************************************************************************************************
** Function name:           drvPwrDown
** Descriptions:            驱动器电源关闭
** input parameters:        none 
**                             
**                              
**                             
** output parameters:       none
** Returned value:          none
**                               
*********************************************************************************************************/
void drvPwrDown(void) {
    ioOutportWord((FUNCTION_IO_NUM & 0x00df), 0x82000004);
}										   

/*********************************************************************************************************
** Function name:           drvPwrUp
** Descriptions:            驱动器电源开启
** input parameters:        none 
**                             
**                              
**                             
** output parameters:       none
** Returned value:          none
**                               
*********************************************************************************************************/
void drvPwrUp(void) {
   ioOutportWord((FUNCTION_IO_NUM | 0x0020), 0x82000004);
}

/*********************************************************************************************************
** Function name:           ShieldHandle
** Descriptions:            支架动作(打开相应的电磁阀口)
** input parameters:        uiValveOpen:    电磁阀开启值(位掩码) 
**                             
**                              
**                             
** output parameters:       none
** Returned value:          none
**                               
*********************************************************************************************************/
void ShieldHandle(INT32U uiValveOpen) {
    INT8U   ucBuf[9];  
    INT16U  usCrc;  
    INT32U  uiValveTmp;
    if ((uiValveOpen & 0x03ffffff) != 0) {                              /*  有效值                      */
        ucBuf[0] = 0x5a;
        ucBuf[1] = 0x22;
        ucBuf[2] = uiValveOpen >> 24; 
        ucBuf[3] = uiValveOpen >> 16;
        ucBuf[4] = uiValveOpen >> 8;
        ucBuf[5] = uiValveOpen;
        usCrc = GetCrc16(&ucBuf[0], 6);
        ucBuf[6] = (usCrc >> 8) & 0xFF;
        ucBuf[7] = (usCrc >> 0) & 0xFF; 
        uartWrite(UART0, ucBuf, 8); 
    }
    if ((uiValveOpen & 0xfc000000) != 0) {                              /*  26功能以上部分              */
        uiValveTmp = (uiValveOpen & 0xff000000) >> 22;
        uiValveTmp = uiValveTmp;
        mc33996Write(uiValveTmp, NULL); 
    } 
    if (uiValveOpen == 0) {                                             /*  无需开启电磁阀              */
        mc33996Write(0x0000, NULL); 
    }   
}


/*********************************************************************************************************
** Function name:           LedBuzzInit
** Descriptions:            指示灯和蜂鸣器初始化
** input parameters:        none
**                             
**                              
**                             
** output parameters:       none
** Returned value:          none
**                               
*********************************************************************************************************/
void LedBuzzInit(void) 
{    
    gpioSet(__LED1_CONTROL_RED);

    gpioClr(__LED2_CONTROL_BLUE);

    gpioClr(__BEEP_CONTROL);

}


/*********************************************************************************************************
** Function name:       jockeyShow
** Descriptions:        将单动动作显示在屏幕上
** input parameters:    ucNo                    架号
**                      uiValveCode             电磁阀码值
**                      ucIsSlave               0/1 操作架/被控架
** Returned value:      None
*********************************************************************************************************/
void jockeyShow(INT16U ucNo, INT32U uiValveCode, INT8U ucIsSlave)
{
    uint8 i,j,m,n;
    uint32 tmp_valve[VALVE_MAX];
const INT32U *puiValveTbl;
    uint32 sensor_tmp[2];
    uint32 l;
    INT8U ucSnrType;                                                    /*  
                                                                         *  传感器数据显示类型
                                                                         *  0 无传感器需要显示
                                                                         *  1 行程
                                                                         *  2 压力
                                                                         *  3 2路压力
                                                                         *  4 3路压力
                                                                         */
    char  sensor_show1[5] = "mm";
    char  sensor_show2[5] = "Mpa";
    char  sensor_show[5];

    m = 0;
    n = 0;
    l = 0;
//    SensorSample();
    if (ucNo >= Gdp.ucMiddleNum1 && ucNo <= Gdp.ucMiddleNum2) {/*  中间架                      */   
        puiValveTbl = __SuiValveTbl;
    } else if ((ucNo <= Gdp.ucMiddleNum3 && ucNo >= Gdp.usGblFaceMin) || 
               (ucNo >= Gdp.ucMiddleNum4 && ucNo <= Gdp.usGblFaceMax)) {        /*  端头架                      */                                                                        
        puiValveTbl = __SuiValveTbl;
    } else if (ucNo > Gdp.ucMiddleNum3 || ucNo < Gdp.ucMiddleNum4) {          /*  过渡架                      */
        puiValveTbl = __SuiValveTbl;
    } else {                                                            /*  非法架号                    */
        return;
    }
    if (ucIsSlave == 0) {                                               /*  主控架                      */        
        guiClrRectangle(0, 16, 16*8, 4*16);
        //guiClrScr();
        j = 0;
        for (i = 0; i < sizeof(__SuiValveTbl) / sizeof(INT32U); i++) {
            if (((uiValveCode & puiValveTbl[i]) == puiValveTbl[i]) && (puiValveTbl[i] != 0)) {
                
                uiValveCode &= ~puiValveTbl[i];
                guiPrintf(0, 16 * (j + 1), 0, &__SscJockeyNameTbl[i][0]);
                j++;	
            }	
            if (j > 3) {
                break;
            }
        }
    } else {                                                            /*  从控架                      */
        guiClrScr();
        for (i = 0; i < VALVE_MAX; i++) {
            if ((uiValveCode & puiValveTbl[CONV_PUSH]) || 
                (uiValveCode & puiValveTbl[CONV_PULL])) {               /*  推溜/拉溜 显示行程          */
                sensor_tmp[0] = __GusRealDataList[18];               
                memcpy(&sensor_show, &sensor_show1, 5);                 /*  行程显示                    */
                ucSnrType = 1;                                          /*  行程                        */
            }
 #if 0               
            else if ((uiValveCode & puiValveTbl[STAB_IN]) || 
                     (uiValveCode & puiValveTbl[STAB_OUT])) {           /*  一级护帮                    */
                if (((SENSOR_TYPE_DEFINE & 0x0200) != 0) && ((SENSOR_TYPE & 0x0040) == 0)) {
                    //有一级护帮压力传感器且没有一级护帮行程传感器
                    sensor_tmp[0] = __GusRealDataList[16];               
                    memcpy(&sensor_show, &sensor_show2, 5); /*压力显示*/
                    ucSnrType = 2;/*显示在前,压力*/              
                } else if (((SENSOR_TYPE_DEFINE & 0x0200) == 0) && ((SENSOR_TYPE & 0x0040) != 0)) {
                    //没有一级护帮压力传感器且有一级护帮行程传感器
                    sensor_tmp[0] = __GusRealDataList[15];               
                    memcpy(&sensor_show, &sensor_show1, 5); /*行程显示*/
                    ucSnrType = 1;/*显示在前,行程*/  
                } else if (((SENSOR_TYPE_DEFINE & 0x0200) != 0) && ((SENSOR_TYPE & 0x0040) != 0)) {
                    //有一级护帮压力传感器且有一级护帮行程传感器
                    sensor_tmp[0] = __GusRealDataList[15]; 
                    sensor_tmp[1] = __GusRealDataList[16];              
                    ucSnrType = 4;/*显示在前后,行程压力*/  
                    }
                } else if ((((tmp_valve[i] & STREB_OUT_ACT) == STREB_OUT_ACT) && (STREB_OUT_ACT != 0))
                    || (((tmp_valve[i] & STREB_IN_ACT) == STREB_IN_ACT) && (STREB_IN_ACT != 0))) {             
                if ((SENSOR_TYPE_DEFINE & 0x0c00) == 0x0c00) {
                //有平衡上、下腔压力传感器
                sensor_tmp[1] = __GusRealDataList[26];
                sensor_tmp[0] = __GusRealDataList[25]; 
                ucSnrType = 3;/*显示在前后，前后柱显示*/
                memcpy(&sensor_show, &sensor_show2, 5);  /*压力显示*/
                }            
            }
 #endif            
            else if (uiValveCode & puiValveTbl[FRT_LEG_LOW]) {          /*  降柱                        */
                for (m = 0; m < 32; m++) {
                    if ((1 << m) & puiValveTbl[LEG_LOW]) {
                        n++;
                    }
                } 
                sensor_tmp[1] = __GusRealDataList[20];
                sensor_tmp[0] = __GusRealDataList[19]; 
                if (n == 2) {
                    ucSnrType = 3;                                      /*  显示在前后，前后柱显示      */
                } else {
                    ucSnrType = 2;                                      /*  显示在前后，前后柱显示      */
                }             
                memcpy(&sensor_show, &sensor_show2, 5);                 /*  压力显示                    */ 
            } else if (uiValveCode & puiValveTbl[LEG_SET]) {            /*  升柱                        */
                for (m = 0; m < 32; m++) {
                    if ((1 << m) & puiValveTbl[LEG_SET]) {
                        n++;
                    }
                } 
                sensor_tmp[1] = __GusRealDataList[20];
                sensor_tmp[0] = __GusRealDataList[19]; 
                if (n == 2) {
                    ucSnrType = 3;                                      /*  前后柱显示                  */
                } else {
                    ucSnrType = 2;                                      /*  显示在前后，前后柱显示      */
                }   
                memcpy(&sensor_show, &sensor_show2, 5);                 /*  压力显示                    */         
            } else if ((uiValveCode & puiValveTbl[REAR_LEG_LOW]) || 
                       (uiValveCode & puiValveTbl[REAR_LEG_SET])) {     /*  后柱动作                    */
                sensor_tmp[0] = __GusRealDataList[20];
                ucSnrType = 2;                                          /*  显示在前,后柱               */
                memcpy(&sensor_show, &sensor_show2, 5);                 /*  压力显示                    */
            } else if ((uiValveCode & puiValveTbl[FRT_LEG_LOW]) || 
                       (uiValveCode & puiValveTbl[FRT_LEG_SET])) {      /*  后柱动作                    */
                sensor_tmp[0] = __GusRealDataList[19];    
                ucSnrType = 2;                                          /*  显示在前,前柱               */
                memcpy(&sensor_show, &sensor_show2, 5);                 /*  压力显示                    */        
            }
            
            uiValveCode &= ~puiValveTbl[i];
            guiPrintf(0, 16 * j, 0, &__SscJockeyNameTbl[i][0]);        /*  显示动作名                  */
            if (ucSnrType == 0) {                                       /*  不显示传感器                */
                ;
            } else if (ucSnrType == 1) {
                if ((sensor_tmp[0] == 0xffff) || (sensor_tmp[0] == 0xfffe)) {
                    guiPrintf(8 * 7, 16 * j, 0, "vvvv mm" );           /*  显示传感器值                */ 
                } else if (sensor_tmp[0] == 0xfffd) {
                    guiPrintf(8 * 7, 16 * j, 0, "#### mm" );           /*  显示传感器值                */                 
                } else {
                    guiPrintf(8 * 7, 16 * j, 0, "%3d" , sensor_tmp[0]);/*  显示传感器值                */
                    guiPrintf(8 * 12, 16 * j, 0, &sensor_show[0]);     /*  显示传感器值单位            */ 
                }              
            } else if (ucSnrType == 2) {
                if ((sensor_tmp[0] == 0xffff) || (sensor_tmp[0] == 0xfffe)) {
                    guiPrintf(8 * 7, 16 * j, 0, "vvvv Mpa" );    /*显示传感器值*/ 
                } else if (sensor_tmp[0] == 0xfffd) {
                    guiPrintf(8 * 7, 16 * j, 0, "#### Mpa" );    /*显示传感器值*/ 
                } else {
                    guiPrintf(8 * 7, 16 * j, 0, "%2d" , sensor_tmp[0]/10); /*显示传感器值*/
                    guiPrintf(8 * 9, 16 * j, 0, ".");                    /*显示传感器值*/
                    guiPrintf(8 * 10, 16 * j, 0, "%d" , sensor_tmp[0]%10); /*显示传感器值*/
                    guiPrintf(8 * 12, 16 * j, 0, &sensor_show[0]);	    /*显示传感器值单位*/ 
                }
            } else if (ucSnrType == 3) {
                if ((sensor_tmp[0] == 0xffff) || (sensor_tmp[0] == 0xfffe)) {
                    guiPrintf(8 * 4, 16 * j, 0, "vvvvMpa");  /*显示传感器值（前）*/
                } else if (sensor_tmp[0] == 0xfffd) {
                    guiPrintf(8 * 4, 16 * j, 0, "####Mpa");  /*显示传感器值（前）*/
                } else {
                    guiPrintf(8 * 4, 16 * j, 0, "%2d" , sensor_tmp[0] / 10);  /*显示传感器值（前）*/
                    guiPrintf(8 * 6, 16 * j, 0, ".");                         /*显示传感器值（前）*/
                    guiPrintf(8 * 7, 16 * j, 0, "%d" , sensor_tmp[0]%10);     /*显示传感器值（前）*/
                }
                if ((sensor_tmp[1] == 0xffff) || (sensor_tmp[1] == 0xfffe)) {
                    guiPrintf(8 * 9, 16 * j, 0, "vvvvMpa");  /*显示传感器值（后）*/
                } else if (sensor_tmp[1] == 0xfffd) {
                    guiPrintf(8 * 9, 16 * j, 0, "####Mpa");  /*显示传感器值（后）*/
                } else {
                    guiPrintf(8 * 9, 16 * j, 0, "%2d" , sensor_tmp[1] / 10);  /*显示传感器值（后）*/
                    guiPrintf(8 * 11, 16 * j, 0, ".");                    /*显示传感器值（后）*/
                    guiPrintf(8 * 12, 16 * j, 0, "%d" , sensor_tmp[1]%10); /*显示传感器值（后）*/
                    guiPrintf(8 * 14, 16 * j, 0, &sensor_show[0]);	    /*显示传感器值单位*/
                }                         
            } else if (ucSnrType == 4) {
                if ((sensor_tmp[0] == 0xffff) || (sensor_tmp[0] == 0xfffe)) {
                    guiPrintf(8 * 4, 16 * j, 0, "vvvvmm");  /*显示传感器值（前）*/
                } else if (sensor_tmp[0] == 0xfffd) {
                    guiPrintf(8 * 4, 16 * j, 0, "####mm");  /*显示传感器值（前）*/
                } else {               
                    guiPrintf(8 * 7, 16 * j, 0, "%3dmm" , sensor_tmp[0]);     /*显示传感器值（前）*/
                }
                if ((sensor_tmp[1] == 0xffff) || (sensor_tmp[1] == 0xfffe)) {
                    guiPrintf(8 * 9, 16 * j, 0, "vvvvMpa");  /*显示传感器值（后）*/
                } else if (sensor_tmp[1] == 0xfffd) {
                    guiPrintf(8 * 9, 16 * j, 0, "####Mpa");  /*显示传感器值（后）*/
                } else {
                    guiPrintf(8 * 9, 16 * j, 0, "%2d" , sensor_tmp[1] / 10);  /*显示传感器值（后）*/
                    guiPrintf(8 * 11, 16 * j, 0, ".");                    /*显示传感器值（后）*/
                    guiPrintf(8 * 12, 16 * j, 0, "%dMpa" , sensor_tmp[1]%10); /*显示传感器值（后）*/
                }                         
            }
            j++;			
        
            if (j > 4) {
                break;
            }
        }
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

