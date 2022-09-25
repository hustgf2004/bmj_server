/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.h
** Latest modified Date:    2017-05-30
** Latest Version:          1.0
** Descriptions:            用户程序主函数头文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2017-05-30
** Version:                 1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
*********************************************************************************************************/
#ifndef __MAIN_H 
#define __MAIN_H

/*********************************************************************************************************
**  这一段无需改动
*********************************************************************************************************/
#include     ".\cfg_file\config.h"
#include     ".\cfg_file\PinCfg\LPC2200PinCfg.h"

/*********************************************************************************************************
    协议帧信息结构体定义
*********************************************************************************************************/
struct __can_frame                                                      
{
    BOOLEAN ucIsRemote;                                                 /*  是否远程帧标志              */
    BOOLEAN ucIsExtend;                                                 /*  是否扩展帧标志              */
    INT8U   ucDataLen;                                                  /*  数据长度                    */
    union {
        unsigned long   ulDWord;
        struct {                    
            unsigned int ulSrc      :8;                                 /*  源地址位域                  */
            unsigned int ulDst      :8;                                 /*  目的地址位域                */
            unsigned int ulRsv      :2;                                 /*  保留位域                    */
            unsigned int ulDir      :2;                                 /*  方向码位域                  */
            unsigned int ulAck      :2;                                 /*  响应码位域                  */
            unsigned int ulCmd      :4;                                 /*  命令码位域                  */
            unsigned int ulPri      :3;                                 /*  优先级位域                  */
        }ulBits;
    }ulId;                                                              /*  帧ID                        */
    INT8U   ucBuf[8];                                                   /*  帧数据                      */
};
typedef struct __can_frame __CANFRAME;


/*********************************************************************************************************
    CAN接收协议帧信息结构体定义
*********************************************************************************************************/
struct __can_msg 
{
  __CANFRAME    cf;
    INT8U       ucFromTo;
}; 
typedef struct __can_msg __CAN_MSG;

extern void can2ReviceHook (void *pRsv,CANFRAME ucfRbr);
extern void can4ReviceHook (void *pRsv,CANFRAME ucfRbr);
extern void CanInit(void);
extern uint8 CanMsgSend(__CAN_MSG *pcm); 

/*********************************************************************************************************
  应用程序配置 根据需要改动 
*********************************************************************************************************/ 
#include ".\eeprom\eeprom.h" 

#include ".\flash\IAP.h"
#include ".\flash\norflash.h" 
#include ".\tmUart2Can\tmUart2Can.h"
#include ".\key\key.h"
#include ".\valve\valve.h"

/*定义can端口*/
#define     COM_PORT_SELF              0x00                                     //人机界面通讯逻辑端口ID
#define     COM_PORT_LEFT              0x01                                     //左邻架通讯逻辑端口ID
#define     COM_PORT_RIGHT             0x02                                     //右邻架通讯逻辑端口ID
#define     COM_PORT_BUS               0x03                                     //总线通讯逻辑端口ID

#define     CAN_PORT_LEFT              CAN4                                     //左邻架通讯网络物理地址ID
#define     CAN_PORT_RIGHT             CAN2                                     //右邻架通讯网络物理地址ID
#define     CAN_PORT_BUS               0x00                                     //总线通讯网络物理地址ID 
#define     CAN_PORT_SELF              0x05

#define     OPERATOR_NUMBER 251
#define     COMPUTER_NUMBER 253    //(虚拟现实252 没有虚拟现实253)
#define     NET_NUMBER 254              //254


typedef struct __dev_para {
    INT8U               usGblFaceMin;                                   /*  最小架号                    */
    INT8U               ucGblFaceMinRsv;
    INT8U               usGblFaceMax;                                   /*  最大架号                    */
    INT8U               ucGblFaceMaxRsv;
    INT16U              usMasterTime;                                   /*  主控时间                    */
    INT16U              usPsaP0;                                        /*  补压下限                    */
    INT16U              usPsaP1;                                        /*  补压上限                    */
    INT16U              usPsaP2;                                        /*  初撑力                      */
    INT8U               ucPsaT0;                                        /*  */
    INT16U              usPsaT1;                                        /*  补压间隔                    */
    INT8U               ucAutoInitPara;                                 /*  跟机初始化参数              */
    INT8U               ucObliCaliEn;                                   /*  倾角校正 bit0:0/1 关/开     */
    INT8U               ucPsaTimes;                                     /*  补压次数                    */
    INT16U              usStopRange;                                    /*  停止范围                    */
    union  {                                                             /*  成组动作使能开关            */
        INT16U          usWord;
        struct {
            INT16U      usRsv0      :1;
            INT16U      usReturnPerch           :1;                     /*  回高位                      */
            INT16U      usLiftBase              :1;
            INT16U      usRsv3 :1;

            INT16U      usRsv4  :1;
            INT16U      usRsv5  :1;
            INT16U      usSpray                 :1;                     /*  成组喷雾                    */
            INT16U      usRsv7          :1;

            
            INT16U      usNbrPush               :1;                     /*  邻架助推                    */
            INT16U      usRsv9  :1;
            INT16U      usRsv10 :1;
            INT16U      usRsv11 :1;

            INT16U      usLinkageFirstEn        :1;                     /*  联动优先                    */
            INT16U      usBatchStab             :1;                     /*  成组护帮板                  */
            INT16U      usBatchPushConvyerEn    :1;                     /*  成组推溜                    */
            INT16U      usSelfAsq               :1;                     /*  本架自动移架                */

        }__attribute__((packed)) Bits;
        
    } __attribute__((packed)) usBatchEn;
    //BATCH_EN    usBatchEn;                                                        
    INT8U               ucPullOffset;
    INT8U               ucPushOffset;
    INT8U               ucDir;
    INT16U              usShieldNo;
    INT8U               ucPwrGrpNo;

    /*
     *  跟机参数列
     */

    INT16U              usPsaP3;                                        /*  后柱补压目标压力            */
    INT8U               ucAutoStatus;                                   /*  启动跟机
                                                                         *  0启动
                                                                         *  1异常
                                                                         *  2人工停止
                                                                         *  3故障
                                                                         */
    INT16U              usAutoFirst;                                    /*  跟机首架编号                */
    INT16U              usAutoLast;                                     /*  跟机末架编号                */
    union {                                                             /*  跟机开关                    */
        INT8U          ucWord;
        struct {
            INT8U       ucUpPush                :1;                     /*  上行跟机推溜                */
            INT8U       ucDownPush              :1;                     /*  下行跟机推溜                */
            INT8U       ucUpFlipIn              :1;                     /*  上行伸缩梁收                */
            INT8U       ucDownFlipOut           :1;                     /*  下行伸缩梁伸                */
            INT8U       ucRsv4                  :1;
            INT8U       ucSpray                 :1;                     /*  跟机喷雾                    */
            INT8U       ucRsv6                  :1;
            INT8U       ucRsv7                  :1;
        } __attribute__((packed)) Bits;        
    } __attribute__((packed)) ucAutoEn;                                       



    INT8U               ucAsqDis;                                       /*  [36]移架距离                */
    INT8U               ucBpDis;                                        /*  [37]推溜距离                */
    INT8U               ucFlipInDis;                                    /*  [38]收伸缩梁距离            */
    INT8U               ucFlipOutDis;                                   /*  [39]伸伸缩梁距离            */
    INT8U               ucHGSsprayDis;                                  /*  [40]跟机喷雾距离            */
    INT8U               ucHGSsprayRange;                                /*  [41]跟机喷雾范围            */
    INT8U               ucUpSnakeMax;                                   /*  [42]上行蛇形大号            */
    INT8U               ucUpSnakeMin;                                   /*  [43]上行蛇形小号            */
    INT8U               ucUpCleanMax;                                   /*  [44]上行清浮煤大号          */
    INT8U               ucUpCleanMin;                                   /*  [45]上行清浮煤小号          */
    INT8U               ucUpAsqBpTrigger;                               /*  [46]上行补充推溜移架触发点  */
    INT8U               ucDownSnakeMax;                                 /*  [47]下行蛇形大号            */
    INT8U               ucShearerHopLimit;                              /*  [48]煤机限制                */
    INT8U               ucDownSnakeMin;                                 /*  [49]下行蛇形小号            */
    INT8U               ucDownCleanMax;                                 /*  [50]下行清浮煤大号          */
    INT8U               ucDownCleanMin;                                 /*  [51]下行清浮煤小号          */
    INT8U               ucDownAsqBpTrigger;                             /*  [52]下行段补充推溜移架触发点*/
    INT8U               ucAutoRunDir;                                   /*  [53]跟机方向1/2-下行/上行   */
    INT8U               ucAutoPhase;                                    /*  [54]自动跟机阶段设置参数    */
    INT8U               ucAutoAsqMax;                                   /*  [55]备用2机尾顺序移架点     */
    INT8U               ucAutoAsqMaxTrigger;                            /*  [56]备用3机尾顺序移架触发点 */
    INT8U               ucAutoAsqMin;                                   /*  [57]备用4机头顺序移架点     */
    INT8U               ucAutoAsqMinTrigger;                            /*  [58]备用5机头顺序移架触发点 */
    INT8U               ucShearerLength;                                /*  [59]煤机身长                */

    /*
     *  成组移架参数列
     */
    INT16U              usAsqStrebSS;//ASQ_STREB_SS           (PARA_LIST[60] | (PARA_LIST[61] << 8))   /*  [60,61]成组移架参数         */

    INT8U               ucAsqRange;                                     /*  [62]成组移架范围            */
    INT8U               ucAsqCollection; //ASQ_COLLECTION          PARA_LIST[63]                           /*  [63]成组移架控制参数        */
    INT16U              usAsqWarnTime;// ASQ_WARN_T             (PARA_LIST[64] | (PARA_LIST[65] << 8))   /*  [64,65]成组预警时间         */

    INT16U              usAsqP0;//ASQ_P0                 (PARA_LIST[66] | (PARA_LIST[67] << 8))   /*  [66,67]移架压力             */

    INT16U              usAsqP1;// ASQ_P1                 (PARA_LIST[68] | (PARA_LIST[69] << 8))   /*  [68,69]移架压力             */

    INT16U              usAsqP2;// ASQ_P2                 (PARA_LIST[70] | (PARA_LIST[71] << 8))   /*  [70,71]移架压力             */

    INT16U              usAsqP3;// ASQ_P3                 (PARA_LIST[72] | (PARA_LIST[73] << 8))   /*  [72,73]移架压力             */
    INT16U              usAsqNbrWaitTime;// ASQ_NB_T               (PARA_LIST[74] | (PARA_LIST[75] << 8))   /*  [74,75]移架等待时间         */

    INT16U              usAsqEndStrk;// ASQ_END_STRK           (PARA_LIST[76] | (PARA_LIST[77] << 8))   /*  [76,77]目标行程             */

    INT8U               ucRearBpRange;// REAR_CONV_BATCH_PUSH_SCOPE    PARA_LIST[78]                           /*  [78]成组推后溜动作范围      */
    INT8U               ucRearBpGrp;// REAR_CONV_BATCH_PUSH_GROUP    PARA_LIST[79]                           /*  [79]成组推后溜动作组        */
    INT8U               ucRearBpTime; //REAR_CONV_BATCH_PUSH_T        PARA_LIST[80]                           /*  [80]成组推后溜动作时间      */
    INT8U               ucRearBpInterval;// REAR_CONV_BATCH_PUSH_OFFSET   PARA_LIST[81]                           /*  [81]成组推后溜启动间隔      */
    INT8U               ucAsqPreLowTime; //ASQ_PRELOW_T            PARA_LIST[82]                           /*  [82]预降柱时间              */
    INT8U               ucAsqP0LowTime;// ASQ_P0_LOWER_T          PARA_LIST[83]                           /*  [83]降柱至ASQ_P0时间        */
    INT8U               ucAsqLow2Time;// ASQ_LOW2_T              PARA_LIST[84]                           /*  [84]再次降柱时间            */
    INT8U               ucAsqBaseLiftStartTime;// ASQ_BASE_LIFT_START_T   PARA_LIST[85]                           /*  [85]抬底开始时间            */
    INT8U               ucAsqBaseLiftTime;// ASQ_BASE_LIFT_T         PARA_LIST[86]                           /*  [86]抬底时间                */
    INT16U              usAsqAdvTime;// ASQ_ADV_T              (PARA_LIST[87] | (PARA_LIST[88] << 8))   /*  [87,88]移架时间             */

    INT8U               ucAsqRelowTime;// ASQ_RELOW_T             PARA_LIST[89]                           /*  [89]再降柱时间              */
    INT8U               ucReadvTime;// ASQ_READV_T             PARA_LIST[90]                           /*  [90]再移架时间              */
    INT8U               ucAsqRelowTimes;// ASQ_RELOW_C             PARA_LIST[91]                           /*  [91]再降柱次数              */
    INT8U               ucAsqSetP1Time;// ASQ_SET_P1_T            PARA_LIST[92]                           /*  [92]升柱至P1时间            */
    INT8U               ucAsqSetP2Time;// ASQ_SET_P2_T            PARA_LIST[93]                           /*  [93]升柱至P2时间            */
                                                                        //94
    INT8U               ucAsqInterval;// ASQ_OFFSET              PARA_LIST[95]                           /*  [95]启动间隔                */
    INT16U              ucAsqNbrPushStrk;// ASQ_NB_PUSH_STRK       (PARA_LIST[96] | (PARA_LIST[97] << 8))   /*  [96,97]邻架助推行程         */

    /*
     *  成组推溜参数列
     */
    INT8U               ucBpRange;// CONV_BATCH_PUSH_SCOPE   PARA_LIST[98]                           /*  [98]成组推溜动作范围        */
    INT8U               ucBpGrp;// CONV_BATCH_PUSH_GROUP   PARA_LIST[99]                           /*  [99]成组推溜组号            */
    INT16U              usAsqRearLegP0;// ASQ_REAR_LEG_P0        (PARA_LIST[100]|PARA_LIST[101] << 8)   /*  [100,101]移架压力（后柱）   */  
    INT16U              usBpTime;// CONV_BATCH_PUSH_T      (PARA_LIST[102]|PARA_LIST[103] << 8)   /*  [102,103]成组推溜时间       */

    INT16U              usBpDelay;// CONV_BATCH_PUSH_DELAY  (PARA_LIST[104]|PARA_LIST[105] << 8)   /*  [104,105]成组推溜延时       */
//INT8U      *BP_DELAYH;
//INT8U      *BP_DELAYL;
    INT8U               ucBpInterval;// CONV_BATCH_PUSH_OFFSET PARA_LIST[106]                           /*  [106]成组推溜启动间隔       */
                                                                        //107，108
    INT8U               ucBpPresetTime;// CONV_BATCH_PUSH_PRESET_T PARA_LIST[109]                           //109预升柱动作时间
                                                                        //110
//INT8U      *BP_EXTH;
//INT8U      *BP_EXTL;
    INT16U              usBpEndStrk; //CONV_BATCH_PUSH_END_STRK (PARA_LIST[111]|PARA_LIST[112] << 8)   //111，112
//INT8U      *BP_END_STRKH;
//INT8U      *BP_END_STRKL;
    INT16U              usBpLTime;// BP_L_PUSH_T            (PARA_LIST[113]|PARA_LIST[114] << 8)   //113，114
//INT8U      *BP_L_PUSH_TH;
//INT8U      *BP_L_PUSH_TL;
    INT16U              usBpProtect;// BP_PROTECT             (PARA_LIST[115]|PARA_LIST[116] << 8)   //115，116
//INT8U      *BP_PROTECTH;
//INT8U      *BP_PROTECTL;
    INT8U               ucBpSetAllow;// BP_SET_ALLOW            PARA_LIST[117]                          //[117]升柱允许
    INT16U              usBpPress;// BP_PRESS               (PARA_LIST[118]|PARA_LIST[119] << 8)   //[118，119]允许压力
//INT8U      *BP_PRESSH;
//INT8U      *BP_PRESSL;

    /*
     *  成组伸缩梁参数列
     */
    INT8U               ucRearConvBatchPullRange;// REAR_CONV_BATCH_PULL_SCOPE PARA_LIST[120]                       /*  [120]成组拉后溜动作范围     */
    INT8U               ucReadConvBatchPullGrp;// REAR_CONV_BATCH_PULL_GROUP PARA_LIST[121]                       /*  [121]成组拉后溜动作组       */
    INT16U              usRearConvBatchPullTime;// REAR_CONV_BATCH_PULL_T    (PARA_LIST[122] | PARA_LIST[123] << 8)/*  [122,123]成组拉后溜时间     */
//INT8U      *PULL_BEHIND_TH;
//INT8U      *PULL_BEHIND_TL;
    INT8U               ucReadConvBatchPullDelay;// REAR_CONV_BATCH_PULL_DELAY  PARA_LIST[124]                      /*  [124]成组拉后溜组间延迟     */
    INT8U               ucReadConvBatchPullInterval;// REAR_CONV_BATCH_PULL_OFFSET PARA_LIST[125]                      /*  [125]成组拉后溜启动间隔     */
    INT16U              ucReadConvPullTime;// REAR_CONV_PULL_T           (PARA_LIST[126] | PARA_LIST[127] << 8)/*  [126,127]本架拉后溜时间     */
//INT8U      *PULL_BEHIND_TSH;
//INT8U      *PULL_BEHIND_TSL;  
    INT8U               ucStabBatchRange;// STAB_BATCH_SCOPE            PARA_LIST[128]                      /*  [128]成组护帮动作范围       */
    INT8U               ucStabBatchDelay;// STAB_BATCH_DELAY            PARA_LIST[129]                      /*  [129]成组护帮架间延迟       */
    INT8U               ucFlipBatchInTime;// FLIP_BATCH_IN_T             PARA_LIST[130]                      /*  [130]成组收伸缩梁动作时间   */
    INT8U               ucFlipBatchOutTime;// FLIP_BATCH_OUT_T            PARA_LIST[131]                      /*  [131]成组伸伸缩梁动作时间   */
    INT8U               ucStabBatchOutTime;// STAB_BATCH_OUT_T            PARA_LIST[132]                      /*  [132]成组伸护帮板动作时间   */
    INT8U               ucStabBatchInTime;//     STAB_BATCH_IN_T             PARA_LIST[133]                      /*  [133]成组收护帮板动作时间   */
    INT8U               ucStabInStartTime;// STAB_IN_START_T             PARA_LIST[134]                      /*  [134]联动及自动移架一级护帮收开始动作时间*/
    INT8U               ucStabInActTime;// STAB_IN_ACT_T               PARA_LIST[135]                      /*  [135]联动及自动移架一级护帮收动作时间*/
    INT8U               ucFlipInStartTime;// FLIP_IN_START_T             PARA_LIST[136]                      /*  [136]联动及自动移架伸缩梁收开始动作时间*/
    INT8U               ucFlipInActTime;// FLIP_IN_ACT_T               PARA_LIST[137]                      /*  [137]联动及自动移架伸缩梁收动作时间*/
    INT8U               ucStabOutStartTime;// STAB_OUT_START_T            PARA_LIST[138]                      /*  [138]联动及自动移架一级护帮伸开始动作时间*/
    INT8U               ucStabOutActTime;// STAB_OUT_ACT_T              PARA_LIST[139]                      /*  [139]联动及自动移架一级护帮伸动作时间*/
    INT8U               ucFlipOutStartTime;// FLIP_OUT_START_T            PARA_LIST[140]                      /*  [140]联动及自动移架伸缩梁伸开始动作时间*/
    INT8U               ucFlipOutActTime;// FLIP_OUT_ACT_T              PARA_LIST[141]                      /*  [141]联动及自动移架伸缩梁伸动作时间*/
    INT8U               ucFlipBatchInLowTime;// FLIP_BATCH_LOW_T            PARA_LIST[142]                      /*  [142]成组收伸缩梁降柱时间   */
    INT8U               ucStabBatchInterval;// STAB_BATCH_OFFSET           PARA_LIST[143]                      /*  [143]成组护帮板组间间隔     */

    /*
     *  成组拉溜参数列
     */
    INT8U               ucConvBatchPullRange;// CONV_BATCH_PULL_SCOPE       PARA_LIST[144]                      /*  [144]成组拉溜范围           */
    INT8U               ucConvBatchPullGrp;// CONV_BATCH_PULL_GROUP       PARA_LIST[145]                      /*  [145]成组拉溜动作组         */
    INT16U              usConvBatchPullTime;// CONV_BATCH_PULL_T          (PARA_LIST[146]|PARA_LIST[147] << 8) /*  [146,147]成组拉溜动作时间   */
//INT8U      *CP_IN_TH;
//INT8U      *CP_IN_TL;
    INT16U              usConvBatchPullDelay;// CONV_BATCH_PULL_DELAY      (PARA_LIST[148]|PARA_LIST[149] << 8) /*  [148,149]成组拉溜架间延迟   */
//INT8U      *CP_DELAYH;
//INT8U      *CP_DELAYL;
    INT8U               ucConvBatchPullSetEn;// CONV_PULL_LEG_SET_ALLOW     PARA_LIST[150]                      /*  [150]升柱允许               */
    INT16U              usConvPullWaitTime;// CONV_PULL_WAIT_T           (PARA_LIST[151]|PARA_LIST[152] << 8) /*  [151,152]等待时间           */
//INT8U      *CP_WAIT_TH;
//INT8U      *CP_WAIT_TL;
    INT16U              usConvPullEndStrk;// CONV_PULL_END_STRK         (PARA_LIST[153]|PARA_LIST[154] << 8) /*  [153,154]目标行程           */
//INT8U      *CP_END_STRKH;
//INT8U      *CP_END_STRKL;
    INT8U               ucConvBatchPullInterl;// CONV_BATCH_PULL_OFFSET      PARA_LIST[155]                      /*  [155]成组拉溜组间间隔       */

    /*
     *  成组喷水参数列
     */
    INT8U               ucFrtGirderLinkOutStartTime;// FRT_GIRDER_LINK_OUT_START_T PARA_LIST[156]                      /*  [156]联动伸前梁开始时间     */
    INT8U               ucFrtGirderLinkOutTime;// FRT_GIRDER_LINK_OUT_T       PARA_LIST[157]                      /*  [157]联动伸前梁动作时间     */
    INT8U               ucReadConvBatchPushDelay;// REAR_CONV_BATCH_PUSH_DELAY  PARA_LIST[158]                      /*  [158]成组推后溜组间延迟     */
    INT8U               ucFrtGirderBatchOutTime;// FRT_GIRDER_BATCH_OUT_T      PARA_LIST[159]                      /*  [159]成组伸前梁动作时间     */
    INT8U               ucFrtGirderBatchInTime;// FRT_GIRDER_BATCH_IN_T       PARA_LIST[160]                      /*  [160]成组收前梁动作时间     */
    INT8U               ucFrtGirderLinkInStartTime;// FRT_GIRDER_LINK_IN_START_T  PARA_LIST[161]                      /*  [161]联动收前梁开始时间     */
    INT8U               ucFrtGirderLinkInTime;// FRT_GIRDER_LINK_IN_T        PARA_LIST[162]                      /*  [162]联动收前梁动作时间     */
    INT8U               ucAsqSprayNum;// ASQ_SPRAY_NUM               PARA_LIST[163]                      /*  [163]Asq顶梁喷雾架数        */
    INT8U               ucAsqSprayTime;// ASQ_SPRAY_T                 PARA_LIST[164]                      /*  [164,165]顶梁喷雾时间       */
//INT8U      *ASQ_Spray_TH;
//INT8U      *ASQ_Spray_TL;
    INT8U               ucHGAsqRange;// HG_ASQ_SCOPE                PARA_LIST[166]                      /*  [166]跟机asq范围            */
    INT8U               ucHgBpRange;// HG_BP_SCOPE                 PARA_LIST[167]                      /*  [167]跟机推溜范围           */
    INT8U               ucHgFlipOutRange;// HG_FLIP_OUT_SCOPE           PARA_LIST[168]                      /*  [168]跟机伸伸缩梁范围       */
    INT8U               ucHgFlipInRange;// HG_FLIP_IN_SCOPE            PARA_LIST[169]                      /*  [169]跟机收伸缩梁范围       */
          
    /*
     *  参数列
     */
    INT8U               ucShearerDataInterval;// SHR_DATA_T                  PARA_LIST[170]                      /*  [170]采煤机位置数据报送时间间隔*/
    INT8U               ucSnrDataInterval;// SNR_DATA_T                  PARA_LIST[171]                      /*  [171]网络检测令牌传输时间间隔*/
    INT8U               ucSnrFirtNum;// SNR_FIRST_NUM               PARA_LIST[172]                      /*  [172]首架编号               */
                                                                        //173-未用 
                                                                        //174-未用
    INT8U               ucDownloadInterval;// DOWN_APART_T                PARA_LIST[175]                      /*  [175]下载间隔               */
    INT8U               ucDownloadDelay;// DOWN_DELAY_T               (PARA_LIST[176]|PARA_LIST[177]<< 8)  /*  [176,177]下载延时           */
//INT8U      *DOWN_DELAY_TL;                                            
//INT8U      *DOWN_DELAY_TH;
    INT8U               ucParaPwd0;// PARA_PASSWORD_0           ((PARA_LIST[181] >> 4) & 0x0F)            //修改参数密码1
    INT8U               ucParaPwd1;// PARA_PASSWORD_1           ((PARA_LIST[181] >> 0) & 0x0F)            //修改参数密码2
    INT8U               ucParaPwd2;// PARA_PASSWORD_2           ((PARA_LIST[180] >> 4) & 0x0F)            //修改参数密码3
    INT8U               ucParaPwd3;// PARA_PASSWORD_3           ((PARA_LIST[180] >> 0) & 0x0F)            //修改参数密码4
    INT8U               ucVip;// VIP_PARAMETER               PARA_LIST[182]                      /*  [182]关键参数 0/1-开/关     */
    INT8U               ucAlterSideTime;//            PARA_LIST[183]                      /*  [183]隔架侧护动作时间（调架时间）*/
    INT8U               ucAlterActionTime;// WARN_TIME_COUNT2            PARA_LIST[184]                      /*  [184]隔架底调动作时间（调架时间）*/
    INT16U              usSnrSendInterval;// SENSOR_SEND_T              (PARA_LIST[185]|PARA_LIST[186]<<8)   /*  [185,186]传感器报送时间     */
//INT8U      *SENSOR_SEND_TL;                                             //185
//INT8U      *SENSOR_SEND_TH;                                             //186 
    INT8U               ucGrpMin;// GROUP_MIN                   PARA_LIST[187]                      /*  [187]成组小号               */
    INT8U               ucGrpMax;// GROUP_MAX                   PARA_LIST[188]                      /*  [188]成组大号               */
    INT8U               ucAsqSprayEnFlag;// ASQ_SPRAY_PERMIT            PARA_LIST[189]                      
                                                                        /*  [189]喷水允许,0/1-禁止/允许 
                                                                         *  .0-自动移架本架是否允许顶梁喷雾
                                                                         *  .1-自动移架左边是否允许顶梁喷雾
                                                                         *  .2-自动移架右边是否允许顶梁喷雾
                                                                         *  .3-自动移架机道喷雾随同顶梁喷雾
                                                                         *  .4-自动移架放煤喷雾随同顶梁喷雾
                                                                         *  .5 降移升顶梁喷雾允许
                                                                         *  .6 降移升机道喷雾是否允许 
                                                                         *  .7 降移升放煤喷雾是否允许
                                                                         */

    INT8U               ucSnrEn;// SNR_FLAG                   (PARA_LIST[190]|PARA_LIST[191]<<8)   /*  [190,191]传感器开关         */
//INT8U      *snr_flagL;                                                  //190
//INT8U      *snr_flagH;                                                  //191
    INT8U           ucAutoStabEn;// AUTO_STAB_CONTROL           PARA_LIST[192]                      /*  [192]跟机护帮板上下行动作控制1/2/3上行/下行/上下行*/
    INT8U           ucAutoAsqEn;// AUTO_ASQ_CONTROL            PARA_LIST[193]                      /*  [193]跟机自动移架上下行动作控制*/  
    INT8U           ucAutoBpEn; //AUTO_BP_CONTROL             PARA_LIST[194]                      /*  [194]跟机推溜上下行动作控制 */
    INT8U           ucAutoSsprayEn;// AUTO_SSPRAY_CONTROL         PARA_LIST[195]                      /*  [195]跟机喷水上下行动作控制 */ 
    INT8U           ucAutoAbortMax;// AUTO_FORBID_SUPPLY_1        PARA_LIST[196]                      /*  [196]跟机中不动作架大号     */
    INT8U           ucAutoAbortMin;// AUTO_FORBID_SUPPLY_2        PARA_LIST[197]                      /*  [197]跟机中不动作架小号     */
    INT8U           ucLowStrebStartTime;// DOWN_STREB_START            PARA_LIST[200]                      /*  [200]降柱时平衡开始动作时间 */
    INT8U           ucLowStrebTime;// DOWN_STREB_TIME             PARA_LIST[201]                      /*  [201]降柱时平衡动作时间     */
    INT8U           ucSetStrebStartTime;// UP_STREB_START              PARA_LIST[202]                      /*  [202]升柱时平衡开始动作时间 */
    INT8U           ucSetStrebTime;// UP_STREB_TIME               PARA_LIST[203]                      /*  [203]升柱时平衡动作时间     */
    INT8U           ucBatchSprayRange;// TG_SSPRAY1                  PARA_LIST[204]                      /*  [204]成组喷水范围           */
    INT8U           ucBatchSprayTime;// TG_SSPRAY2                  PARA_LIST[205]                      /*  [205]成组喷水时间           */
    INT8U           ucBatchSprayInterval;// TG_SSPRAY_OFFSET            PARA_LIST[206]                      /*  [206]成组喷水启动间隔       */
    INT8U           ucMiddleNum1;// MIDDLE_NUM_1                PARA_LIST[208]                      /*  [208]中间架小号             */
    INT8U           ucMiddleNum2;// MIDDLE_NUM_2                PARA_LIST[209]                      /*  [209]中间架大号             */
    INT8U           ucFlashBoardInTime1;// IN_FLASHBOARD_T1            PARA_LIST[210]                      /*  [210]放顶煤ASQ收插板动作时间1*/
    INT8U           ucTailInStartTime;// IN_TAIL_START_T1            PARA_LIST[211]                      /*  [211]放顶煤ASQ降尾梁开始动作时间1*/
    INT8U           ucTailInActTime;// IN_TAIL_ACT_T1              PARA_LIST[212]                      /*  [212]放顶煤ASQ降尾梁动作时间1*/
    INT8U           ucAsqExpendTime;// ASQ_EXPEND_T1               PARA_LIST[213]                      /*  [213]放煤时间1              */
    INT8U           ucTailOutActTime;// OUT_TAIL_ACT_T1             PARA_LIST[214]                      /*  [214]放顶煤ASQ升尾梁动作时间1*/
    INT8U           ucFlashBoardOutStartTime;// OUT_FLASHBOARD_START_T1     PARA_LIST[215]                      /*  [215]放顶煤ASQ伸插板开始动作时间1*/
    INT8U           ucFlashBoardOutActTime;// OUT_FLASHBOARD_ACT_T1       PARA_LIST[216]                      /*  [216]放顶煤ASQ伸插板动作时间1*/
    INT8U           ucExpendUpWaitTime;// EXPEND_UP_T1                PARA_LIST[217]                      /*  [217]放顶煤上方等待时间1    */
    INT8U           ucCycles1;// CIRCULAR_1                  PARA_LIST[218]                      /*  [218]循环次数1              */
    INT8U           ucFlashBoardInTime2;// IN_FLASHBOARD_T2            PARA_LIST[219]                      /*  [219]放顶煤ASQ收插板动作时间2*/
    INT8U           ucTailInStartTime2;// IN_TAIL_START_T2            PARA_LIST[220]                      /*  [220]放顶煤ASQ降尾梁开始动作时间2*/
    INT8U           ucTailInActTime2;// IN_TAIL_ACT_T2              PARA_LIST[221]                      /*  [221]放顶煤ASQ降尾梁动作时间2*/
    INT8U           ucAsqExpendTime2;// ASQ_EXPEND_T2               PARA_LIST[222]                      /*  [222]放煤时间2              */
    INT8U           ucTailOutActTime2;// OUT_TAIL_ACT_T2             PARA_LIST[223]                      /*  [223]放顶煤ASQ升尾梁动作时间2*/
    INT8U           ucFlashBoardOutStartTime2;// OUT_FLASHBOARD_START_T2     PARA_LIST[224]                      /*  [224]放顶煤ASQ伸插板开始动作时间2*/
    INT8U           ucFlashBoardOutActTime2;// OUT_FLASHBOARD_ACT_T2       PARA_LIST[225]                      /*  [225]放顶煤ASQ伸插板动作时间2*/
    INT8U           ucExpendUpWaitTime2;// EXPEND_UP_T2                PARA_LIST[226]                      /*  [226]放顶煤上方等待时间2    */
    INT8U           ucCycles2;// CIRCULAR_2                  PARA_LIST[227]                      /*  [227]循环次数2              */
    INT8U           ucFlashBoardInTime3;// IN_FLASHBOARD_T3            PARA_LIST[228]                      /*  [228]放顶煤ASQ收插板动作时间3*/
    INT8U           ucTailInStartTime3;// IN_TAIL_START_T3            PARA_LIST[229]                      /*  [229]放顶煤ASQ降尾梁开始动作时间3*/
    INT8U           ucTailInActTime3;// IN_TAIL_ACT_T3              PARA_LIST[230]                      /*  [230]放顶煤ASQ降尾梁动作时间3*/
    INT8U           ucAsqExpendTime3;// ASQ_EXPEND_T3               PARA_LIST[231]                      /*  [231]放煤时间3              */
    INT8U           ucTailOutActTime3;// OUT_TAIL_ACT_T3             PARA_LIST[232]                      /*  [232]放顶煤ASQ升尾梁动作时间3*/
    INT8U           ucFlashBoardOutStartTime3;// OUT_FLASHBOARD_START_T3     PARA_LIST[233]                      /*  [233]放顶煤ASQ伸插板开始动作时间3*/
    INT8U           ucFlashBoardOutActTime3;// OUT_FLASHBOARD_ACT_T3       PARA_LIST[234]                      /*  [234]放顶煤ASQ伸插板动作时间3*/
    INT8U           ucExpendUpWaitTime3;// EXPEND_UP_T3                PARA_LIST[235]                      /*  [235]放顶煤上方等待时间3    */
    INT8U           ucCycles3;// CIRCULAR_3                  PARA_LIST[236]                      /*  [236]循环次数3              */
    INT8U           ucAsqExpendInterval;// ASQ_EXPEND_DELAY            PARA_LIST[237]                      /*  [237]放顶煤架间延迟时间     */
    INT8U           ucExpendGrp;// EXPEND_GROUP                PARA_LIST[238]                      /*  [238]放煤动作组             */
    INT8U           ucExpendType;// EXPEND_OFFSET               PARA_LIST[239]                      /*  [239]放顶类型               */
    INT8U           ucReturnTailOutTime; //RETURN_OUTAIL_T             PARA_LIST[240]                      /*  [240]回高位尾梁升时间       */
    INT8U           ucReturnFlashBoardOutStartTime;// RETURN_OUTF_START           PARA_LIST[241]                      /*  [241]回高位插板伸开始时间   */
    INT8U           ucReturnFlashBoardOutActTime;// RETURN_OUTF_T               PARA_LIST[242]                      /*  [242]回高位插板伸动作时间   */
    INT8U           ucReturnGrp;// RETURN_GROUP                PARA_LIST[243]                      /*  [243]回高位组数             */
    INT8U           ucReturnInterval;// RETURN_OFFSET               PARA_LIST[244]                      /*  [244]回高位启动间隔         */
    INT8U           ucExpendSprayEn;// EXPEND_SPRAY_PERMIT         PARA_LIST[245]                      
                                                                        /*  [245]- 
                                                                         *  Bit0-本架放煤喷雾是否允许
                                                                         *  Bit1-左邻架放煤喷雾是否允许
                                                                         *  Bit2-右邻架放煤喷雾是否允许
                                                                         *  bit3-尾梁插板动作时放煤喷雾是否允许
                                                                         */
    INT8U           ucExpendSprayTime;// EXPEND_SPRAY_TIME           PARA_LIST[246]                      /*  [246]放煤喷雾时间           */
    INT8U           ucExpendSprayNum;// EXPEND_SPRAY_NUM            PARA_LIST[247]                      /*  [247]放煤喷雾架数           */
    INT8U           ucTimingSprayDelay;// TIMING_SPRAY_DELAY          PARA_LIST[248]                      /*  [248]定时喷雾启动间隔       */
    INT8U           ucTimingSprayGrp;// TIMING_SPRAY_GROUP          PARA_LIST[249]                      /*  [249]定时喷雾组内架数       */
    INT8U           ucTimingSprayTime;// TIMING_SPRAY_T              PARA_LIST[250]                      //250-定时喷雾动作时间
    INT8U           ucTimingSprayDir;// TIMING_SPRAY_START          PARA_LIST[251]                      //251-定时喷雾动作方向1-从小到大，2-从大到小
    INT8U           ucTimingSprayEn;// TIMING_SPRAY_PERMIT         PARA_LIST[252]                      //252-定时喷雾是否允许
    INT16U          usSideOutTs;// SIDE_OUT_TS                (PARA_LIST[253]|PARA_LIST[254]<<8)
//INT8U      *SIDE_OUT_TSL;											    //253,254 本架伸侧护动作时间
//INT8U      *SIDE_OUT_TSH;											    //253,254 本架伸侧护动作时间
    INT8U           ucStab2OutStartTime;// STAB2_OUT_START_T           PARA_LIST[256]                      //256联动及自动移架二级护帮伸开始动作时间
    INT8U           ucStab2OutActTime;// STAB2_OUT_ACT_T             PARA_LIST[257]                      //257联动及自动移架二级护帮伸动作时间        
    INT8U           ucStab3OutStartTime;// STAB3_OUT_START_T           PARA_LIST[258]                      //258联动及自动移架三级护帮伸开始动作时间
    INT8U           ucStab3OutActTime;// STAB3_OUT_ACT_T             PARA_LIST[259]                      //259联动及自动移架三级护帮伸动作时间
    INT8U           ucStab2InStartTime;// STAB2_IN_START_T            PARA_LIST[260]                      //260联动及自动移架二级护帮收开始动作时间
    INT8U           ucStab2InActTime;// STAB2_IN_ACT_T              PARA_LIST[261]                      //261联动及自动移架二级护帮收动作时间        
    INT8U           ucStab3InStartTime;// STAB3_IN_START_T            PARA_LIST[262]                      //262联动及自动移架三级护帮收开始动作时间
    INT8U           ucStab3InActTime;// STAB3_IN_ACT_T              PARA_LIST[263]                      //263联动及自动移架三级护帮收动作时间
    INT8U           ucShakeTime;// SHAKE_TIME                  PARA_LIST[264]                      //264-抖动时间
    INT8U           ucShakeTimes;// SHAKE_NUM                   PARA_LIST[265]                      //265-抖动次数
    INT16U          usMsgWndTime;// MESSAGE_WIN_TIME           (PARA_LIST[266]|PARA_LIST[267])      //266、267-消息窗时间ms
//INT8U      *MESSAGE_WIN_TIMEL;                                          //266
//INT8U      *MESSAGE_WIN_TIMEH;                                          //267
    INT16U           usEvtWndTime;// EVENT_WIN_TIME             (PARA_LIST[268]|PARA_LIST[269]<<8)   //268、269-事件窗时间ms
//INT8U      *EVENT_WIN_TIMEL;                                            //268
//INT8U      *EVENT_WIN_TIMEH;                                            //269
    INT8U           ucAsqReturnDelay;// ASQ_RETURN_DELAY            PARA_LIST[270]                      //270-回高位架间延迟时间
    INT16U          usAsqStrebP0;// ASQ_STREB_P0               (PARA_LIST[271]|PARA_LIST[272]<<8)   //271,272 平衡差动开始压力
//INT8U      *ASQ_STREB_P0L;
//INT8U      *ASQ_STREB_P0H;                                                                                                        											
    INT8U           ucAsqStrebEn;// ASQ_STREB_IN_OUT_FLAG       PARA_LIST[273]                      //273  bit0平衡差动开关:0禁止，1允许
                                                                        //     bit1-一级护帮行程传感器开关：0-开，1-关
                                                                        //     bit2-倾角传感器开关：0-开，1-关
                                                                        //     bit3-一级护帮压力传感器开关：0-开，1-关
                                                                        //     bit4-三级护帮限位传感器开关：0-开，1-关
                                                                        //     bit5高度传感器开关
                                                                        //     bit6 平衡上压力开关
                                                                        //     bit7 平衡下压力开关
    INT16U          usObli1Cal1;// OBLI1_REVISE_D             (PARA_LIST[274]|PARA_LIST[275]<<8)   //274,275校正值1
//INT8U      *OBLI1_REVISE_DL;
//INT8U      *OBLI1_REVISE_DH;
     INT16U          usObli1Cal2;// OBLI2_REVISE_D             (PARA_LIST[276]|PARA_LIST[277]<<8)   //276,277校正值2
//INT8U      *OBLI2_REVISE_DL;
//INT8U      *OBLI2_REVISE_DH;
     INT16U          usObli1Cal3;// OBLI3_REVISE_D             (PARA_LIST[278]|PARA_LIST[279]<<8)   //278,279校正值3
//INT8U      *OBLI3_REVISE_DL;
//INT8U      *OBLI3_REVISE_DH;
    INT16U          usLength1; //LENGTH_1                   (PARA_LIST[280]|PARA_LIST[281]<<8)   //280,281-长度1
//INT8U      *LENGTH_1L;
//INT8U      *LENGTH_1H;
    INT16U          usLength2;// LENGTH_2                   (PARA_LIST[282]|PARA_LIST[283]<<8)   //282,283-长度2
//INT8U      *LENGTH_2L;
//INT8U      *LENGTH_2H;
    INT16U          usLength3;// LENGTH_3                   (PARA_LIST[284]|PARA_LIST[285]<<8)   //284,285-长度3
//INT8U      *LENGTH_3L;
//INT8U      *LENGTH_3H;
    INT16U          usLength4;// LENGTH_4                   (PARA_LIST[286]|PARA_LIST[287]<<8)   //286，287-底座高度
//INT8U      *LENGTH_4L;
//INT8U      *LENGTH_4H;
    INT8U           ucObliSendInterval;// SEND_DISTIME                PARA_LIST[288]                      //288-倾角报送间隔
    INT8U           ucObliRelative;// OBLI_RELATE_CONTR           PARA_LIST[289]                      //289-倾角相关控制
                                                                        /*
                                                                         *  Bit0-平衡,升柱倾角相关
                                                                         *  Bit1-降柱高度相关
                                                                         *  Bit2-降柱倾角相关
                                                                         *  Bit3-升柱高度相关
                                                                         *  Bit4-基准支架允许 0-禁止 1-允许 
                                                                         *  Bit5-自动移架时降柱和高度相关
                                                                         */
    INT8U           ucObliFixNum;// OBLI_FIX_NUM                PARA_LIST[290]                      //290 第四倾角传感器安装架数
    INT8U           ucObli4Fix;// OBLI4_FIT_FLAG              PARA_LIST[291]                      //291第四倾角传感器安装标志
    INT16U          usObliCal4;// OBLI4_REVISE_D             (PARA_LIST[292]|PARA_LIST[293]<<8)   //292,293校正值4
//INT8U      *OBLI4_REVISE_DL;
//INT8U      *OBLI4_REVISE_DH; 
    INT8U           ucHeightShow;// HEIGHT_SHOW_D               PARA_LIST[294]                      //294---显示高度阀值
    INT8U           ucObliShow;// OBLI_SHOW_D                 PARA_LIST[295]                      //295---显示角度阀值
    INT8U           ucObliChkTime;// CHECK_OLI_TIME              PARA_LIST[296]                      //296---检测倾角传感器时间 
    INT8U           ucObliAxis;// OBLI_X_Y                    PARA_LIST[297]                      //297-bit0：0-x，1-y轴选择
    INT8U           ucStab3BatchOutTime;// STAB3_OUT_T                 PARA_LIST[298]                      //298-成组伸三级护帮动作时间
    INT8U           ucStab3BatchInTime;// STAB3_IN_T                  PARA_LIST[299]                      //299-成组收三级护帮动作时间
    INT16U          usLowHeigth;// DROP_HEIGHT                (PARA_LIST[300]|PARA_LIST[301]<<8)   //300,301-降柱高度设置
//INT8U      *DROP_HEIGHTL;                                             
//INT8U      *DROP_HEIGHTH;
    INT8U           ucObliBaseLine;// COM_ABS_ANGLE               PARA_LIST[302]                      //302-倾角设置//*COM_ABS_ANGLE：2---支架基准，3---报角度，4---取消支架基准，5-版本号，6-eeprom状态
    INT16U          usStab1OutEnd;// STAB1_OUT_AIM              (PARA_LIST[303]|PARA_LIST[304]<<8)   //303,304-伸一级护帮目标行程
//INT8U      *STAB1_OUT_AIML;
//INT8U      *STAB1_OUT_AIMH;
    INT16U          usStab1InEnd;// STAB1_IN_AIM               (PARA_LIST[305]|PARA_LIST[306]<<8)   //305,306-收一级护帮目标行程
//INT8U      *STAB1_IN_AIML;
//INT8U      *STAB1_IN_AIMH;
    INT16U          usStab1OutPEnd;// STAB1_OUT_PRESSURE_AIM     (PARA_LIST[307]|PARA_LIST[308]<<8)   //307,308-伸一级护帮目标压力
//INT8U      *STAB1_OUT_PRESSURE_AIML;
//INT8U      *STAB1_OUT_PRESSURE_AIMH;
    INT8U           ucRewashEn;// REVERSE_SWASH_PROHIBIT      PARA_LIST[309]                      //309-自动定时反冲洗功能开关
                                                                        //Bit0-反冲功能总开关　0-禁止　1-允许
                                                                        //Bit1-上反冲开关　　　0-禁止　1-允许
                                                                        //Bit2-上反冲开关　　　0-禁止　1-允许
                                                                        //bit3-成组反冲洗开关  0-禁止  1-允许
    INT8U           ucRewashTime;// REVERSE_SWASH_T             PARA_LIST[310]                      //310-反冲动作时间
    INT8U           ucRewashUpDownInterval;// UP_DOWN_TIMEGAP             PARA_LIST[311]                      //311-上下反冲时间间隔
    INT8U           ucRewashInterval;// SHIELD_SWASH_TIMEGAP        PARA_LIST[312]                      //312-架间启动时间间隔
    INT8U           ucTimingRewashHour1;// REVERSE_SWASH_TIME1_H       PARA_LIST[313]                      //313-反冲定时1－时
    INT8U           ucTimingRewashMin1;// REVERSE_SWASH_TIME1_M       PARA_LIST[314]                      //314-反冲定时1－分
    INT8U           ucTimingRewashHour2;// REVERSE_SWASH_TIME2_H       PARA_LIST[315]                      //315-反冲定时2－时
    INT8U           ucTimingRewashMin2;// REVERSE_SWASH_TIME2_M       PARA_LIST[316]                      //316-反冲定时2－分
    INT8U           ucTimingRewashHour3;// REVERSE_SWASH_TIME3_H       PARA_LIST[317]                      //317-反冲定时3－时
    INT8U           ucTimingRewashMin3;// REVERSE_SWASH_TIME3_M       PARA_LIST[318]                      //318-反冲定时3－分
    INT8U           ucTimingRewashHour4;// REVERSE_SWASH_TIME4_H       PARA_LIST[319]                      //319-反冲定时4－时
    INT8U           ucTimingRewashMin4;// REVERSE_SWASH_TIME4_M       PARA_LIST[320]                      //320-反冲定时4－分
    INT8U           ucStabPsaEn;// STAB_PSA_CONTROL            PARA_LIST[321]                      //321-一级护帮自动补压相关
                                                                        //bit0-一级护帮自动补压允许，禁止
                                                                        //bit1-联动伸三级护帮允许,禁止
                                                                        //bit2-联动收一级护帮分段是否优先
                                                                        //bit3-一级护帮限位开关允许禁止
    INT16U          usStabPsaP0;// STAB_PSA_P0                (PARA_LIST[322]|PARA_LIST[323]<<8)   //322,323-一级护帮自动补压压力下限
//INT8U      *STAB_PSA_P0L;
//INT8U      *STAB_PSA_P0H;
    INT16U          usStabPsaP1;// STAB_PSA_P1                (PARA_LIST[324]|PARA_LIST[325]<<8)   //324,325-一级护帮自动补压压力上限
//INT8U      *STAB_PSA_P1L;
//INT8U      *STAB_PSA_P1H;
    INT8U           ucStabPsaTimes;// STAB_PSA_NUM                PARA_LIST[326]                      //326-一级护帮自动补压允许次数
    INT8U           ucStabPsaTime;// STAB_PSA_T                  PARA_LIST[327]                      //327-一级护帮自动补压单次时间
    INT8U           ucStabPsaInterval;// STAB_PSA_SPACET             PARA_LIST[328]                      //328-一级护帮自动补压间隔时间
    INT16U          usStabPsaP2;// STAB_PSA_P2                (PARA_LIST[329]|PARA_LIST[330]<<8)   //329,330-一级护帮自动补压目标压力
//INT8U      *STAB_PSA_P2L;
//INT8U      *STAB_PSA_P2H;
    INT8U           ucAsqStabLowDelay;// ASQ_STAB_LOW_DELAY          PARA_LIST[331]                      //331--延时降柱
    INT8U           ucSprayEn;// PLATEN_FORER_BEHIND         PARA_LIST[332]                      //332-跟机喷雾动作在前滚筒还是后滚筒，
                                                                        //bit0-上前喷雾0-禁止 1-允许
                                                                        //bit1-上后喷雾0-禁止 1-允许
                                                                        //bit2-下前喷雾0-禁止 1-允许
                                                                        //bit3-下后喷雾0-禁止 1-允许
                                                                        //bit5-护帮喷雾，
                                                                        //bit6-移架喷雾，
                                                                        //bit7-降柱喷雾
    INT8U           ucAsqSprayEn; //ASQ_SPRAY                   PARA_LIST[333]                      //333-自动移架喷水允许
    INT8U           ucAsqSprayStartTime;// ASQ_SPRAY_B_T               PARA_LIST[334]                      //334-自动移架开始喷水时间0.1s
    INT8U           ucAsqLowSprayTime;// DOWN_SPRAY_T                PARA_LIST[335]                      //335-降柱移架喷水时间0.1s
    INT16U          usBaseLiftEnd;// LIFT_SET_AIM               (PARA_LIST[336]|PARA_LIST[337]<<8)   //336,337-移架抬底的目标行程
//INT8U      *LIFT_SET_AIML;
//INT8U      *LIFT_SET_AIMH;
    INT8U           ucStabInStartTimeMin;// STAB_IN_S_MIN               PARA_LIST[338]                      //338联动收 收一级护帮开始最小时间
    INT8U           ucStabInStartTimeMax;// STAB_IN_S_MAX               PARA_LIST[339]                      //339联动收 收一级护帮开始最大时间																	
    INT8U           ucHGUpFrtSSprayDis;// HG_SSPRAY3                  PARA_LIST[340]                      //340-上行前滚筒距离
    INT8U           ucHGUpFrtSSprayRange;// HG_SSPRAY4                  PARA_LIST[341]                      //341-上行前滚筒范围
    INT8U           ucHGUpRearSSprayDis;// HG_SSPRAY5                  PARA_LIST[342]                      //342-上行后滚筒距离
    INT8U           ucHGUpRearSSprayRange;// HG_SSPRAY6                  PARA_LIST[343]                      //343-上行后滚筒范围
    INT8U           ucHGDownFrtSSprayDis;// HG_SSPRAY7                  PARA_LIST[344]                      //344-下行前滚筒距离
    INT8U           ucHGDownFrtSSprayRange;// HG_SSPRAY8                  PARA_LIST[345]                      //345-下行前滚筒范围
    INT8U           ucHGDownRearSSprayDis;// HG_SSPRAY9                  PARA_LIST[346]                      //346-下行后滚筒距离
    INT8U           ucHGDownRearSSprayRange;// HG_SSPRAY10                 PARA_LIST[347]                      //347-下行后滚筒范围
    INT8U           ucHGSSprayTime;// HG_SSPRAY_TIME              PARA_LIST[348]                      //348-跟机喷雾动作时间
    INT8U           ucStab2InTime;// STAB2_IN_T                  PARA_LIST[349]                      //349-二级护帮收动作时间
    INT8U           ucStab2OutTime;// STAB2_OUT_T                 PARA_LIST[350]                      //350-二级护帮伸动作时间
    INT8U           ucStab2OutStartTime2;// STAB2_OUT_START2_T          PARA_LIST[351]                      //351-联动时二级护帮伸开始时间（第二次动作）
    INT8U           ucStab2OutActTime2;// STAB2_OUT_ACT2_T            PARA_LIST[352]                      //352-联动时二级护帮伸动作时间（第二次动作）
    INT8U           ucStab2InStartTime2;// STAB2_IN_START2_T           PARA_LIST[353]                      //353-联动时二级护帮收开始时间（第二次动作）
    INT8U           ucStab2InActTime2;// STAB2_IN_ACT2_T             PARA_LIST[354]                      //354-联动时二级护帮收动作时间（第二次动作）
    INT8U           ucStab2ActType;// STAB2_ACT                   PARA_LIST[355]                      //355-二级护帮联动动作开关	  1--伸 0--收
                                                                        //Bit3		一级护帮伸时二级护帮第2次做什么动作伸/收
                                                                        //Bit2		一级护帮伸时二级护帮第1次做什么动作伸/收
                                                                        //Bit1		一级护帮收时二级护帮第2次做什么动作伸/收 
                                                                        //Bit0		一级护帮收时二级护帮第1次做什么动作伸/收 
    INT8U           ucLeftSideOutTime;// LEFT_SIDE_OUT_T             PARA_LIST[356]                      //356-本架伸顶梁侧护板动作时间
    INT8U           ucRightSideOutTime;// RIGHT_SIDE_OUT_T            PARA_LIST[357]                      //357-本架伸掩护梁侧护板动作时间
    INT8U           ucAsqSideEn;// ASQ_FORMER_SIDE             PARA_LIST[358]                      //358-自动移架过程侧护板动作开关
    INT8U           ucAsqsetSideOutTime;// ASQ_SIDE_OUT_T              PARA_LIST[359]                      //359-ASQ中升柱后伸侧护持续时间
    INT8U           ucAsqPullSideOutTime;// ASQ_SIDE_OUTT_T1            PARA_LIST[360]                      //360-ASQ中移架后伸侧护持续时间
    INT8U           ucAsqLiftLowTime;// ASQ_LIFT_LOW_T              PARA_LIST[361]                      //361-ASQ中收抬底座动作时间
    INT8U           ucJockeySideLockTime;// JOCKEY_SIDE_LOCK_T          PARA_LIST[362]                      //362-单动升柱后侧护解锁持续时间
    INT8U           ucAsqSideLockTime;// ASQ_SIDE_LOCK_T             PARA_LIST[363]                      //363-ASQ中升柱侧护解锁持续时间
    INT8U           ucBatchRewashOffset;// FILTRATE_OFFSET             PARA_LIST[364]                      //364-成组反冲洗启动间隔
    INT8U           ucBatchRewashRange;// FILTRATE_SCOPE              PARA_LIST[365]                      //365-成组反冲洗动作范围
    INT8U           ucYear;// MODIFY_YEAR                 PARA_LIST[366]                      //366-时钟修改年
    INT8U           ucMonth;// MODIFY_MONTH                PARA_LIST[367]                      //367-时钟修改月
    INT8U           ucDate;// MODIFY_DATE                 PARA_LIST[368]                      //368-时钟修改日
    INT8U           ucHour;// MODIFY_HOUR                 PARA_LIST[369]                      //369-时钟修改时
    INT8U           ucMinute;// MODIFY_MINUTE               PARA_LIST[370]                      //370-时钟修改分
    INT8U           ucWeek;// MODIFY_WEEK                 PARA_LIST[371]                      //371-时钟修改星期
    INT16U          usFixHeight;// FIX_HEIGHT                 (PARA_LIST[372]|PARA_LIST[373]<<8)   //372、373-激光测距仪安装高度
//INT8U      *FIX_HEIGHTL;                                                        
//INT8U      *FIX_HEIGHTH;                                                         
    INT16U          usIrHoldTime;// IR_STAY_TIME               (PARA_LIST[374]|PARA_LIST[375]<<8)   //374、375-红外信号保持时间
//INT8U      *IR_STAY_TIMEL;
//INT8U      *IR_STAY_TIMEH;
    INT8U           ucMiddleNum3;// MIDDLE_NUM_3                PARA_LIST[376]                      //376-端头小号
    INT8U           ucMiddleNum4;// MIDDLE_NUM_4                PARA_LIST[377]                      //377-端头架大号
    INT8U           ucAngle;// ANGLE_NUM                   PARA_LIST[378]                      //378-顶梁和掩护梁夹角
    INT8U           ucAngleUp;// ANGLE_UP_NUM                PARA_LIST[379]                      //379-顶梁上扬限制角度  
    INT8U           ucAngeleDown;// ANGLE_DOWN_NUM              PARA_LIST[380]                      //380-顶梁下栽限制角度
    INT8U           ucAutoType;// AUTO_TYPE                   PARA_LIST[381]                      //381-自动跟机类型  0-中部 1-全工作面


    INT8U       ucShieldNo;
    INT8U       ucAsqWarnT;
    INT8U       ucFlipOutStartT;
    INT8U       ucFlipOutActT;
    INT8U       ucPusherOutStartT;
    INT8U       ucPusherOutActT;
    INT8U       ucFlipInStartT;
    INT8U       ucFlipInActT;
    INT8U       ucPusherInStartT;
    INT8U       ucPusherInActT;
    INT8U       ucLiftOutStartT;
    INT8U       ucLiftOutActT;
    INT8U       ucLiftInStartT;
    INT8U       ucLiftInActT;
}__attribute__((packed)) DEV_PARA, *PDEV_PARA;


typedef struct {
    INT8U       ucAsqWarnT;
    INT8U       ucFlipOutStartT;
    INT8U       ucFlipOutActT;
    INT8U       ucPusherOutStartT;
    INT8U       ucPusherOutActT;
    INT8U       ucFlipInStartT;
    INT8U       ucFlipInActT;
    INT8U       ucPusherInStartT;
    INT8U       ucPusherInActT;
    INT8U       ucLiftOutStartT;
    INT8U       ucLiftOutActT;
    INT8U       ucLiftInStartT;
    INT8U       ucLiftInActT;    
} AUTO_PARA, *PAUTO_PARA;

typedef enum {                                                          /*  支架状态定义                */
    STA_IDLE,                                                           /*  空闲                        */
    STA_HOST,                                                           /*  主控                        */
    STA_S_SLAVE,                                                        /*  从控                        */
    STA_G_SLAVE,                                                        /*  成组从控                    */
    STA_S_LOCK,                                                         /*  软件闭锁                    */
    STA_H_LOCK,                                                         /*  硬件闭锁                    */
    //STA_SELF,                                                           /*  自控                        */
    STA_ACT = 0x08,                                                     /*  动作中                      */                                    
} SHIELD_STAT;
 

/*定义系统时间*/
#define     MS_TIMER  							(OSTimeGet()*(1000/OS_TICKS_PER_SEC))
#define     SEC_TIMER							(OSTimeGet()/OS_TICKS_PER_SEC)
typedef struct __dev_status {
    INT16U          usShieldNo;                                         /*  本架地址                    */
    SHIELD_STAT     ucStatus;                                           /*  本架状态机                  */
    INT8U           ucIsStop;
    INT8U           ucIsLock;
    INT8U           ucIsAuthorized;
    INT32U          uiAuthorizedTimeoutTick;                            /*  授权超时计时器              */
    INT32U          uiValveStatus;                                      /*  本架阀开口状态              */
    INT8U           ucIsWarning;                                        /*  预警状态                    */
    INT32U          uiWarnStartTick;                                    /*  预警起始计时器              */
    INT32U          uiWarnTimeoutTick;                                  /*  预警超时计时器              */
    INT8U           ucSlaveNo;                                          /*  被控架号                    */
    INT8U           ucSlaveDir;                                         /*  被控架方向
                                                                         *  0   左
                                                                         *  1   右         
                                                                         */
    
    INT8U           ucShearerDir;                                       /*  采煤机方向                  */
    INT8U           ucShearerPos;                                       /*  采煤机位置                  */
    //INT8U           ucIndicatorFlag;
    union {
        INT8U       ucWord;
        struct {
            INT8U   ucKeyPush       :2;
            INT8U   ucSafe          :2;
            INT8U   ucWarn          :2;
            INT8U   ucRsv           :2;
        }Bits;
    } ucIndicatorFlg;                                                   /*  声光报警标识                */
    
    INT32U          uiTimeStamp;                                        /*  系统时间戳                  */
    
    INT8U           ucIsReceiverReady;                                  /*  无线接收器就绪标识          */
    INT8U           ucIsRemoteReady;                                    /*  无线遥控器连接标识          */
    INT32U          uiRemoteCommTimeoutTick;                            /*  无线遥控器通信超时计时器    */
    INT32U          uiRemoteTimeoutTick;                                /*  无线遥控器连接超时计时器    */
    INT32U          uiMasterTimeoutTick;                                /*  主控超时计时器              */
} DEV_STATUS, *PDEV_STATUS;


/*********************************************************************************************************
  外设中断服务函数声明
*********************************************************************************************************/
/*********************************************************************************************************
** Function name:       FIQ_Exception
** Descriptions:        FIQ中断服务程序
** input parameters:    无
** output parameters:       none
** Returned value:      无
*********************************************************************************************************/
extern void FIQ_Exception (void);

/*********************************************************************************************************
** Function name:       DefIRQ_Exception
** Descriptions:        非向量中断服务程序
** input parameters:    无
** output parameters:       none
** Returned value:      无
*********************************************************************************************************/
extern void DefIRQ_Exception (void);

/*********************************************************************************************************
** Function name:       PWM0_ISR
** Descriptions:        PWM中断服务程序
** input parameters:    无
** output parameters:       none
** Returned value:      无
*********************************************************************************************************/
extern void PWM0_ISR (void);

/*********************************************************************************************************
** Function name:       RTC0_ISR
** Descriptions:        RTC中断服务程序
** input parameters:    无
** output parameters:       none
** Returned value:      无
*********************************************************************************************************/
extern void RTC0_ISR (void);

/*********************************************************************************************************
** Function name:       SPI0_ISR
** Descriptions:        SPI0中断服务程序
** input parameters:    无
** output parameters:       none
** Returned value:      无
*********************************************************************************************************/
extern void SPI0_ISR (void);

/*********************************************************************************************************
** Function name:       SPI1_ISR
** Descriptions:        SPI1中断服务程序
** input parameters:    无
** output parameters:       none
** Returned value:      无
*********************************************************************************************************/
extern void SPI1_ISR (void);

/*********************************************************************************************************
** Function name:       I2C0_ISR
** Descriptions:        I2C0中断服务程序
** input parameters:    无
** output parameters:       none
** Returned value:      无
*********************************************************************************************************/
extern void I2C0_ISR (void);

/*********************************************************************************************************
** Function name:       WDT0_ISR
** Descriptions:        WDT中断服务程序
** input parameters:    无
** output parameters:       none
** Returned value:      无
*********************************************************************************************************/
extern void WDT0_ISR (void);

/*********************************************************************************************************
** Function name:       EINT0_ISR
** Descriptions:        外部中断0用户响应函数
** input parameters:    无
** output parameters:       none
** Returned value:      无
*********************************************************************************************************/
extern void EINT0_ISR (void);

/*********************************************************************************************************
** Function name:       EINT1_ISR
** Descriptions:        外部中断1用户响应函数
** input parameters:    无
** output parameters:       none
** Returned value:      无
*********************************************************************************************************/
extern void EINT1_ISR (void);

/*********************************************************************************************************
** Function name:       EINT2_ISR
** Descriptions:        外部中断2用户响应函数
** input parameters:    无
** output parameters:       none
** Returned value:      无
*********************************************************************************************************/
extern void EINT2_ISR (void);

/*********************************************************************************************************
** Function name:       EINT3_ISR
** Descriptions:        外部中断3用户响应函数
** input parameters:    无
** output parameters:       none
** Returned value:      无
*********************************************************************************************************/
extern void EINT3_ISR (void);

/*********************************************************************************************************
** Function name:       UART0_ISR
** Descriptions:        UART0中断响应函数
** input parameters:    无
** output parameters:       none
** Returned value:      无
*********************************************************************************************************/
extern void UART0_ISR (void);

/*********************************************************************************************************
** Function name:       UART1_ISR
** Descriptions:        UART1中断响应函数
** input parameters:    无
** output parameters:       none
** Returned value:      无
*********************************************************************************************************/
extern void UART1_ISR (void);

/*********************************************************************************************************
** Function name:       TIMER1_ISR
** Descriptions:        TIMER1中断响应函数
** input parameters:    无
** output parameters:       none
** Returned value:      无
*********************************************************************************************************/
extern void TIMER1_ISR (void);

/*********************************************************************************************************
** Function name:       CAN_ISR
** Descriptions:        CAN中断响应函数
** input parameters:    无
** output parameters:       none
** Returned value:      无
*********************************************************************************************************/
extern void CAN_ISR (void);

/*********************************************************************************************************
** Function name:       ADC0_ISR
** Descriptions:        ADC中断响应函数
** input parameters:    无
** output parameters:       none
** Returned value:      无
*********************************************************************************************************/
extern void ADC0_ISR (void);


extern void guiPrintf(unsigned int uiXPoint, unsigned int uiYPoint, INT8U ucIsAnti, char * pcString,...);

extern void guiClScr();

extern void  guiClrRectangle(uint32 x0, uint32 y0, uint32 x1, uint32 y1);
    
extern unsigned long    GulKeyMsg;                                      /*  按键消息队列                */

extern DEV_PARA         Gdp;
extern DEV_STATUS       Gds;

#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
