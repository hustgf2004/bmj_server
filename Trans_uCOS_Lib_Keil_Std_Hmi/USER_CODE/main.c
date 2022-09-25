/****************************************Copyright (c)****************************************************
**                          China Coal Beijing Coal Mining Co.,Ltd.
**                                      
**                             https://www.cbmj.chinacoal.com/
**
**--------------File Info---------------------------------------------------------------------------------
**  File name :         main.c
**  Last modified Date :
**  Last Version :      V1.00
**  Descriptions :      用户主程序
**
**--------------------------------------------------------------------------------------------------------
** Created by:          超人力霸王
** Created date:        2014-08-25
** Version:             V1.00
** Descriptions :      
**--------------------------------------------------------------------------------------------------------
** Modified by :        sn
** Modified date :      2020-4-29
** Version :            0.2
** Descriptions :       修复自动补压前后柱问题
*********************************************************************************************************/

#include "main.h"
/*********************************************************************************************************
  TASK0 任务ID、优先级、堆栈设置及函数声明                                
*********************************************************************************************************/
#define TASK0_ID            4                                           /* 任务的ID                     */
#define TASK0_PRIO          TASK0_ID                                    /* 任务的优先级                 */
#define TASK0_STACK_SIZE    512                                         /* 定义用户堆栈长度             */
OS_STK  TASK0_STACK[TASK0_STACK_SIZE];                                  /* 定义任务0 堆栈               */
void    TASK0(void *pdata);                                             /* 声明任务0                    */

/*********************************************************************************************************
  TASK1 任务ID、优先级、堆栈设置及函数声明                                
*********************************************************************************************************/
#define TASK1_ID            5                                           /* 任务的ID                     */
#define TASK1_PRIO          TASK1_ID                                    /* 任务的优先级                 */
#define TASK1_STACK_SIZE    256                                         /* 定义用户堆栈长度             */
OS_STK  TASK1_STACK[TASK1_STACK_SIZE];                                  /* 定义任务1堆栈                */
void    TASK1(void *pdata);                                             /* 声明任务1                    */


#if 0  
/*********************************************************************************************************
  TASK2 任务ID、优先级、堆栈设置及函数声明                                
*********************************************************************************************************/ 
#define TASK2_ID            14                                          /* 任务的优先级                 */
#define TASK2_PRI           TASK2_ID                                    /* 任务的ID                     */
#define TASK2_STACK_SIZE    512                                         /* 定义用户堆栈长度             */
OS_STK  TASK2_STACK[TASK2_STACK_SIZE];                                  /* 定义任务 2堆栈               */
void    TASK2(void *pdata);                                             /* 声明任务 2                   */ 

/*********************************************************************************************************
  TASK3 任务ID、优先级、堆栈设置及函数声明                                
*********************************************************************************************************/
#define TASK3_ID            15                                          /* 任务的ID                     */
#define TASK3_PRIO          TASK3_ID                                    /* 任务的优先级                 */
#define TASK3_STACK_SIZE    512                                         /* 定义用户堆栈长度             */
OS_STK  TASK3_STACK[TASK3_STACK_SIZE];                                  /* 定义任务 3堆栈               */
void    TASK3(void *pdata);                                             /* 声明任务 3                   */

/*********************************************************************************************************
  TASK4 任务ID、优先级、堆栈设置及函数声明                                
*********************************************************************************************************/
#define TASK4_ID            16                                          /* 任务的ID                     */
#define TASK4_PRIO          TASK4_ID                                    /* 任务的优先级                 */
#define TASK4_STACK_SIZE    512                                         /* 定义用户堆栈长度             */
OS_STK  TASK4_STACK[TASK4_STACK_SIZE];                                  /* 定义任务 4堆栈               */
void    TASK4(void *pdata);                                             /* 声明任务 4                   */

/*********************************************************************************************************
  TASK5 任务ID、优先级、堆栈设置及函数声明                                
*********************************************************************************************************/
#define TASK5_ID            17                                          /* 任务的ID                     */
#define TASK5_PRIO          TASK5_ID                                    /* 任务的优先级                 */
#define TASK5_STACK_SIZE    512                                         /* 定义用户堆栈长度             */
OS_STK  TASK5_STACK[TASK5_STACK_SIZE];                                  /* 定义任务 5堆栈               */
void    TASK5(void *pdata);                                             /* 声明任务 5                   */
#endif


    /*
     *  全局变量定义
     */

DEV_PARA        Gdp;
DEV_STATUS      Gds;
unsigned long  GulKeyMsg;
INT32U  GulCanMsg;                                                      /*  消息通道                    */
INT32U  GulRxMsg;                                                       /*  接收消息队列                */
INT32U  GulTxMsg;                                                       /*  发送消息队列                */

//#define M32(adr) (*((volatile unsigned long  *) (adr)))

    /*
     *  全局变量定义
     */

void sysDataAbortIsr()
{
    while (1) {
        ;
    }
    
}
void sysPrefetchIsr()
{
    while (1) {
        ;
    }
}
void sysUndefinedsr()
{
    while (1) {
        ;
    }
}

void InitPLL (void) {

/* 设置系统各部分时钟 */
/* Set system timers for each component */
    PLLCON = 1;
#if (FPCLK / (FCCLK / 4)) == 1
    VPBDIV = 0;
#endif
#if (FPCLK / (FCCLK / 4)) == 2
    VPBDIV = 2;
#endif                                           /
#if (FPCLK / (FCCLK / 4)) == 4
    VPBDIV = 1;
#endif

#if (FCCO / FCCLK) == 2
    PLLCFG = ((FCCLK / FOSC) - 1) | (0 << 5);
#endif
#if (FCCO / FCCLK) == 4
    PLLCFG = ((FCCLK / FOSC) - 1) | (1 << 5);
#endif
#if (FCCO / FCCLK) == 8
    PLLCFG = ((FCCLK / FOSC) - 1) | (2 << 5);
#endif
#if (FCCO / FCCLK) == 16
    PLLCFG = ((FCCLK / FOSC) - 1) | (3 << 5);
#endif
    PLLFEED = 0xaa;
    PLLFEED = 0x55;
    while((PLLSTAT & (1 << 10)) == 0);
    PLLCON = 3;
    PLLFEED = 0xaa;
    PLLFEED = 0x55;
} 

INT32S __tmUartInit ()
{  
    char  ucUartArg[] = "BaudRate=57600 TxBufSize=128";// Fpclk=11059200";
    UART_HOOKS uartHooks;
   
    memset(&uartHooks, 0x00, sizeof(UART_HOOKS));   
    uartHooks.pReceive =  uartReceiveHook;
    if (uartInit(0, ucUartArg, &uartHooks) < 0) {           /* UART控制器初始化             */
        while(1);
    }
    vicIrqFuncSet(6, 5, (INT32U)UART0_ISR);	
    return 0;
}

    /*
     *  下载管理程序标志定义 
     */             
#define     __EN_UPGRADE_FLAG0      0x40003610                          /*  使能程序下载功能标志0       */
#define     __EN_UPGRADE_FLAG1      0x40003614                          /*  使能程序下载功能标志1       */
#define     __EN_UPGRADE_SRC        0x40003624                          /*  使能程序棒功能标志          */
#define     __EN_UPGRADE_RANGE      0x40003628                          /*  传输范围标志                */

extern void reset();
extern void switchDLM2_Handler();
void  __UpGradeBegin(void) 
{
    /*
     *  设置升级标志
     */
    ioOutportLong(0x55AA55AA, __EN_UPGRADE_FLAG0);
    ioOutportLong(0x55AA55AA, __EN_UPGRADE_FLAG1);

    /*
     *  升级开始
     */

    sysIrqDisable();
    sysChangeToSysMode();
    //switchDLM2_Handler();
    sysIrqEnable();
}

void CanFrmProcess(INT8U ucId, CANFRAME cfRbr)
{       
    INT32S      siErr; 
  __CAN_MSG     cmRcv;
    /*
     *  跳转到下载管理程序2
     */
    
    if ((0x1f060000 == (cfRbr.ulId & 0xffff0000)) &&
        (ucId == CAN_PORT_RIGHT)) {
        
        /*
         *  切换到下载管理程序2
         */
        __UpGradeBegin(); 
        return;
    }
    cmRcv.cf.ucIsRemote = cfRbr.ucIsRemote;
    cmRcv.cf.ucIsExtend = cfRbr.ucIsExtend;
    cmRcv.cf.ucDataLen  = cfRbr.ucDataLen;
    cmRcv.cf.ulId.ulDWord = cfRbr.ulId;
    memcpy(cmRcv.cf.ucBuf, cfRbr.ucBuf, cfRbr.ucDataLen);
    // if(port_err_cnt[can_num] > 0)       //正常操作：通讯错误计数器与通讯状态寄存器维护
    // {
    //     port_err_cnt[can_num] -= 1;
    //     if((port_err_cnt[can_num] > MIN_PORT_ERR) && (port_err_cnt[can_num] < MAX_PORT_ERR))
    //     {
    //         can_port_sta[can_num] = 1;
    //     }
    //     else
    //     {
    //         if(port_err_cnt[can_num] == 0)
    //         {
    //             can_port_sta[can_num] = 0;
    //         }
    //     }
    // }

    if (ucId == CAN_PORT_SELF) {
        siErr = sysMsgPost(GulRxMsg, (INT8U *)&cmRcv, 1);// OSQPostFront(RX_MSG,black_ptr);
    } else {
        siErr = sysMsgPost(GulRxMsg, (INT8U *)&cmRcv, 0);//OSQPost(RX_MSG,black_ptr);
    }
    if (siErr < 0) {
        ;
    }

    if (0xFE != cmRcv.cf.ulId.ulBits.ulDst) {           
        if ((CAN_PORT_RIGHT == ucId)) {                                 /*  主机发来的数据  */             
            cmRcv.ucFromTo = CAN_PORT_BUS;                             
            sysMsgPost(GulTxMsg, (INT8U *)&cmRcv, 1);
        } else if (CAN_PORT_BUS == ucId) {                              /*  工作面发来的数据*/            
            if ((0xFd == cmRcv.cf.ulId.ulBits.ulDst) || (0x00 == cmRcv.cf.ulId.ulBits.ulDst)) {
                cmRcv.ucFromTo = CAN_PORT_RIGHT; 
                sysMsgPost(GulCanMsg, (INT8U *)&cmRcv, 0);
            }
        }
    }
}

static void CanDrivReceiveHook (void *pRsv,CANFRAME canFrame)
{
    INT8U   ucChn = ((INT8U*)pRsv)[0];  
    //CanFrmProcess(ucChn + 1, canFrame);
    return;
}
volatile INT32U	GuiPacketSendNum[5];



/*********************************************************************************************************
** Function name:           guiPrintf
** Descriptions:            指定位置打印格式化字符串
** input parameters:        uiXPoint        x坐标
**                          uiYPoint        y坐标
**                          ucIsAnti        反显
**                          pcString        格式化字符串
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void guiPrintf(INT32U uiXPoint, INT32U uiYPoint, INT8U ucIsAnti, char * pcString,...)
{
    char    cStr[160];
    va_list ap;
    if (NULL == pcString) {
        return;
    }
    va_start(ap,pcString);
    vsprintf(cStr+3,pcString,ap);
    va_end(ap); 
    cStr[0] =  uiXPoint;
    cStr[1] =  uiYPoint; 
    cStr[2] =  ucIsAnti;
    pcString =  cStr; 
    tpWrite(2, __TP_PRINTF, strlen(pcString+3)+4, pcString, 0);
}

/*********************************************************************************************************
** Function name:           guiClrScr
** Descriptions:            清屏
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void guiClrScr()
{
    INT8U ucChar = 0x01;
    tpWrite(2, __TP_CLR_SCR, 1, &ucChar, 0);
}

/*********************************************************************************************************
** Function name:           guiClrRectangle
** Descriptions:            清除指定范围
** input parameters:        x0              起始x坐标
**                          y0              起始y坐标
**                          x1              结束x坐标
**                          y1              结束y坐标
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void  guiClrRectangle(uint32 x0, uint32 y0, uint32 x1, uint32 y1)
{
    char    cStr[4];
    cStr[0] =  x0;
    cStr[1] =  y0; 
    cStr[2] =  x1;
    cStr[3] =  y1;
    tpWrite(2, __TP_CLR_RECT, 4, cStr, 0);
}


/*********************************************************************************************************
** Function name:           ledOn
** Descriptions:            导航灯亮
** input parameters:        uiLedOn             导航指示灯位掩码
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void ledOn(INT32U uiLedOn)
{
    INT8U ucBuf[3];         
    ucBuf[2] =  ~uiLedOn;
    ucBuf[1] = ~(uiLedOn >> 8);
    ucBuf[0] = ~(uiLedOn >> 16);
    tpWrite(2, __TP_LED_ON, 3, ucBuf, 0); 
}

/*********************************************************************************************************
** Function name:           ledOff
** Descriptions:            导航灯灭
** input parameters:        uiLedOff        导航指示灯位掩码
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void ledOff(INT32U uiLedOff)
{
    INT8U ucBuf[3];         
    ucBuf[2] =  ~uiLedOff;
    ucBuf[1] = ~(uiLedOff >> 8);
    ucBuf[0] = ~(uiLedOff >> 16);
    tpWrite(2, __TP_LED_OFF, 3, ucBuf, 0);
}

/*********************************************************************************************************
** Function name:           ledBlink
** Descriptions:            导航灯和蜂鸣器(IO)闪烁
** input parameters:        usTimes         闪烁次数
**                          usOnTicks       亮持续时间ms
**                          usOffTicks      灭持续时间ms
**                          usIoNo          IO 0 黄 1 绿 2 蜂鸣器 3 错误指示灯
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void ledBlink(INT16U usTimes, INT16U usOnTicks, INT16U usOffTicks, INT16U usIoNo)
{
    INT16U usBuf[4];  
    usBuf[0] = usTimes;
    usBuf[1] = usOnTicks;
    usBuf[2] = usOffTicks;
    usBuf[3] = usIoNo;
    tpWrite(2, __TP_LED_BLINK, 8, usBuf, 0);
}
   
   
/*********************************************************************************************************
** Function name:           TaskIdlekHook
** Descriptions:            
** input parameters:        none
** output parameters:       none
** Returned value:          none                          
*********************************************************************************************************/
void TaskIdleHook(void)
{
    ;
}

/*********************************************************************************************************
** Function name:           main
** Descriptions:            主函数
** input parameters:        none
** output parameters:       none
** Returned value:          none                          
** Created by:              
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
int main (void)
{
    OSInit(); 
    OSTaskCreateExt(TASK0,
                    (void *)0,
                    &TASK0_STACK[TASK0_STACK_SIZE-1],
                    TASK0_PRIO,
                    TASK0_ID,
                    &TASK0_STACK[0],
                    TASK0_STACK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR); 
    OSStart();    
    return 0;                                   
}

/*********************************************************************************************************
** Function name:           TASK0
** Descriptions:            启动任务
** input parameters:        none
** output parameters:       none
** Returned value:          none                          
** Created by:              
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
void TASK0 (void *pdata)
{  
    extern const unsigned char ucLogo[];
    char               *pscCanArg = "BaudRate=33300 Mode=1 AfMode=0";
    SD2405_TIME       __SExRtcTime;  
    CAN_HOOKS           canReceiveHook;    
    UART_HOOKS          uartHooks;
    INT8U               ucFlag, i;
    INT32S              siErr;
    INT16U              usLsr;
    INT32U              uiIrSendTick;
    INT32U              uiDrvSendTick;
    INT8U               ucBuf[8];
    INT32U              uiMsTics;
    INT32U              __SuiTick;
    

    OSTaskIdleHookSet(TaskIdleHook);
    pinInit();                                                          /*  管脚初始化                  */    
    targetInit();                                                       /*  系统初始化,版本号验证       */
    
    sysDataAbortIsrSet((INT32U)sysDataAbortIsr);
    sysPrefetchIsrSet((INT32U)sysPrefetchIsr);
    sysUndefinedsrSet((INT32U)sysUndefinedsr);

    GulKeyMsg = sysMsgCreate (5, 4);



    
    
    /*
     *  初始化uart0, uart1
     */
    //memset(&uartHooks, 0x00, sizeof(UART_HOOKS));
    //uartHooks.pReceive = uartReceiveHook;
    //uartInit(UART1, "BaudRate=9600 TxBufSize=512", &uartHooks); 
    //uartInit(UART0, "BaudRate=57600 TxBufSize=512 FifoLen=8", NULL);

    //vicIrqFuncSet(UART1_IRQ_CHN, 8, (INT32U)UART1_ISR);
    //vicIrqFuncSet(UART0_IRQ_CHN, 7, (INT32U)UART0_ISR);
 
    guiClrScr();
    
    /*
     *  建立通讯机制：创建消息队列
     */ 
    GulCanMsg = sysMsgCreate(20, sizeof(__CANFRAME));
    if (GulCanMsg == 0) {
        while(1);
    }
    
    GulRxMsg = sysMsgCreate(20, sizeof(__CAN_MSG));
    if (GulRxMsg == 0) {
        while (1);
    }
    
    
    
    __tmUartInit(0);

    memset(&canReceiveHook, 0, sizeof(CAN_HOOKS));
    canReceiveHook.pReceive =  CanDrivReceiveHook;
    //for (i = 0; i < 4; i++) {
        canInit(CAN1, "BaudRate=33300 Mode=1", &canReceiveHook);   
        vicDefIrqEnable(20 + CAN1);										 
        vicDefIrqEnable(26 + CAN1);	
        canInit(CAN2, "BaudRate=33300 Mode=1", &canReceiveHook);   
        vicDefIrqEnable(20 + CAN2);										 
        vicDefIrqEnable(26 + CAN2);	
        canInit(CAN4, "BaudRate=33300 Mode=1", &canReceiveHook);   
        vicDefIrqEnable(20 + CAN4);										 
        vicDefIrqEnable(26 + CAN4);	
    //}
    //vicDefIrqEnable(19);
    //vicDefIrqFuncSet((INT32U)CAN_ISR);                                  /* 设置中断服务函数      */ 
    
    
    OSTimeDlyHMSM(0, 0, 2, 0);                   
    /*
     *  全局变量初始化
     */


    
    /*
     *  参数初始化
     */
   if (((INT8U *)0x34000)[0] != 0xaa) {                                 /*  参数无效                    */
       extern const INT8U __GucParaDefault[512];
        eepromWrite(0, (INT8U *)__GucParaDefault, 381);                  /*  写入默认参数                */
       
        memset(TASK1_STACK, 0xaa, sizeof(TASK1_STACK));                                 /*  借用全局变量作为SRAM        */
        sysIrqDisable();
        iapSectorPrepare(12, 12);
        iapSectorErase(12, 12);
        iapSectorPrepare(12, 12);
        iapRamToFlash(0x34000, (((INT32U)TASK1_STACK) + 0x7f) & ~0x7f, 512);
        siErr = iapDataCompare(0x34000, (((INT32U)TASK1_STACK) + 0x7f) & ~0x7f, 512);
        if (siErr != CMD_SUCCESS) {
            ;
        }
//        Init(0, 12000000, 2);       // Initialize Flash Programming Functions
//        EraseSector(0x34000);
//        ProgramPage(0x34000, 512, (INT8U *)&Gdp);
//        InitPLL();
        sysIrqEnable();	
   } else {                                                            /*  参数有效                    */    
       ;
   }
    eepromRead(0, (INT8U *)&Gdp, sizeof(DEV_PARA));
    if (Gdp.usMasterTime < 50) {                                        /*  限制最小主控时间            */
        Gdp.usMasterTime = 100;
    }
    Gds.ucSlaveNo = Gdp.ucShieldNo;


    //GpuiValveTbl = valveTblGet(Gdp.ucShieldNo);
    GpuiKeyTbl = keyTblGet(Gdp.ucShieldNo);
                                                     


       
    OSTaskCreateExt(TASK1,
                    (void *)0,
                    &TASK1_STACK[TASK1_STACK_SIZE - 1],
                    TASK1_PRIO,
                    TASK1_ID,
                    &TASK1_STACK[0],
                    TASK1_STACK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
    
#if SD2405_TIME_INIT > 0
    sd2405Init(&__SExRtcTime); 
#endif                                                                  /*  SD2405_TIME_INIT            */
    upSysTime(); 


    
while (1) {       
        if (MS_TIMER - uiMsTics >= 1000) {
            Gds.uiTimeStamp++;
            uiMsTics = MS_TIMER;
            if (!__GptnCurMenu) {                                       /*  主界面                      */
                INT32U uiHours, uiMinutes, uiSeconds, uiTemp;
                uiTemp      = Gds.uiTimeStamp / 60;
                uiSeconds   = Gds.uiTimeStamp % 60;
                uiHours     = uiTemp / 60;
                uiMinutes   = uiTemp % 60;
                guiPrintf(0, 48, 0, "运行时间%02d:%02d:%02d", uiHours, uiMinutes, uiSeconds);
            }
        }
        

        if (Gds.ucIndicatorFlg.Bits.ucKeyPush) {                        /*  按键提示音                  */
            if (Gds.ucIndicatorFlg.Bits.ucKeyPush == 1) {               /*  未提示                      */                                                                                
                ledBlink(1, 1, 1, 2);                                   /*  开启蜂鸣器                  */
                __SuiTick = MS_TIMER;
                Gds.ucIndicatorFlg.Bits.ucKeyPush = 2;
            } else /*if (Gds.ucIndicatorFlg.Bits.ucKeyPush == 2)*/{     /*  已提示                      */
                if (MS_TIMER - __SuiTick >= 100) {
                    ledBlink(0, 500, 500, 2);                           /*  关闭蜂鸣器                  */
                    Gds.ucIndicatorFlg.Bits.ucKeyPush = 0;
                } else {
                    ;
                }
            }
        } else if (Gds.ucIndicatorFlg.Bits.ucSafe) {                    /*  急停/闭锁提示音             */
            static INT8U __SucBeepTimes;
            if (Gds.ucIndicatorFlg.Bits.ucSafe == 1) {                  /*  未提示                      */
                ledBlink(3, 10, 10, 2);
                __SuiTick = MS_TIMER;
                Gds.ucIndicatorFlg.Bits.ucSafe = 2;
            }
        } else if (Gds.ucIndicatorFlg.Bits.ucWarn) {                        /*  动作预警                    */
            if (MS_TIMER - __SuiTick >= 500) {                              /*  报警间隔                    */

                __SuiTick = MS_TIMER;
            }
        } else {                                                            /*  无声光报警                  */

            if (Gds.ucIsRemoteReady) {
                ;
            } else {
                ;
            }
        }

        OSTimeLag(OS_TICKS_PER_SEC / 50);                               /*  任务精确延时20ms            */       
    }
}

/*********************************************************************************************************
** Function name:           TASK1 
** Descriptions:            键盘处理任务
** input parameters:        none
** output parameters:       none
** Returned value:          none                          
** Created by:              
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
void TASK1(void *pdata) 
{  	
    INT32S          siErr;
    INT32U          uiKeyCode;                                          /*  当前键值                    */
    INT32U          uiKeyLast;                                          /*  前一次键值                  */
    INT32U          uiSafeKey;
//    INT32U          uiMasterTick;                                       /*  主控计时器                  */
    INT8U           ucBuf[8];

    
    INT8U           ucInvalidCnt;                                       /*  无效按键计数器              */
    INT8U           ucIsInvalidKey;                                     /*  是否为无效按键              */
    INT32U          uiTimeoutTicks;
    pdata = pdata;                                                      /*  防止编译警告                */
    uiSafeKey = 0;
    while (1) {
        if (Gds.ucIsRemoteReady) {
            uiTimeoutTicks = 500;
        } else {
            uiTimeoutTicks = 50;
        }
        siErr = sysMsgPend(GulKeyMsg, ucBuf, uiTimeoutTicks);
//        if ((uiKeyCode & JP_STOP) == (uiSafeKey & JP_STOP) &&
//            (uiSafeKey & JP_STOP)) {
//            continue;
//        } 
        

        if (siErr < 0) {                                                /*  无按键                      */
            uiKeyCode = 0;
            uiKeyLast = uiKeyCode;                                      /*  按键抬起                    */            
            if (Gds.ucStatus == STA_HOST) {                             /*  主控状态无按键也需更新显示  */                                                                        
//                if (OS_TASK_RESUME_PRIO != OSTaskResume(TASK3_PRIO)) {  /*  由自动移架任务控制          */
//                    continue;
//                }


            } else if ((Gds.ucStatus == STA_S_SLAVE) ||
                       (Gds.ucStatus == STA_G_SLAVE)) {                 /*  从控状态                    */
                ;
            } else if (Gds.ucStatus == STA_IDLE) {                      /*  空闲状态                    */                                   
                if (MS_TIMER - Gds.uiMasterTimeoutTick > Gdp.usMasterTime * 100) { 
                                                                        /*  手动控制主控时间到          */

                    if (__GptnCurMenu) {                                /*  菜单状态                    */                            
                        if (miIsExist(&__GmiibKeyLock)) {
                            ;
                        } else {
                            miFlush();                                      /*  退出菜单                    */
                            mainDisplay();                                  /*  显示主界面                  */
                        }
                    }
                }
//                if (SEC_TIMER - Gds.uiAuthorizedTimeoutTick >= 10) {
//                    Gds.ucIsAuthorized = FALSE;
//                }   
                continue;
            } else {
                continue;
            }
        } else {                                                        /*  按键消息                    */
            //uiKeyCode = ((INT32U *)ucBuf)[0];                           /*  取键值                      */
            uiKeyCode = (ucBuf[0] << 16) | (ucBuf[1] << 8) | ucBuf[2]; 
            if (uiKeyCode == JP_STOP) {                             /*  急停                        */
                uiKeyCode |= JP_STOP;
                //uiSafeKey &= ~JP_LOCK;
            } else if (ucBuf[0] == 0x33) {                          /*  闭锁                        */
                ;
            } else if (uiKeyCode == JP_LOCK) {
                uiKeyCode |= JP_LOCK;
            } else if (ucBuf[0] == 0x44) {
                ;
            }
            if ((uiKeyCode & (JP_LOCK | JP_STOP)) == uiSafeKey &&
                uiSafeKey) {
                continue;
            }
            if ((uiKeyCode == JP_STOP) == (uiSafeKey & JP_STOP) &&
                (uiSafeKey & JP_STOP)) {
                continue;
            } 
            if ((uiKeyCode & JP_STOP) && (!(uiSafeKey & JP_STOP))) {        /*  急停按下                    */
                ucBuf[0] = Gdp.ucShieldNo;
                ucBuf[1] = 1;            
                //tpWrite(TP_DEFAULT_CHNL, __TP_STOP, 2, ucBuf, 0);
                
                uiSafeKey |= JP_STOP;
            }  else if ((!(uiKeyCode & JP_STOP)) && (uiSafeKey & JP_STOP)) { /*  急停抬起                    */
                ucBuf[0] = Gdp.ucShieldNo;
                ucBuf[1] = 0;
                //tpWrite(TP_DEFAULT_CHNL, __TP_STOP, 2, ucBuf, 0);
                uiSafeKey &= ~JP_STOP;
            } else if ((uiKeyCode & JP_LOCK) && (!(uiSafeKey & JP_LOCK))) { /*  闭锁按下                    */            
                ucBuf[0] = Gdp.ucShieldNo;
                ucBuf[1] = 1;            
                //tpWrite(TP_DEFAULT_CHNL, __TP_LOCK, 2, ucBuf, 0);
                uiSafeKey |= JP_LOCK;
            } else if ((!(uiKeyCode & JP_LOCK)) && (uiSafeKey & JP_LOCK)) { /*  闭锁抬起                    */
                ucBuf[0] = Gdp.ucShieldNo;
                ucBuf[1] = 0;            
                //tpWrite(TP_DEFAULT_CHNL, __TP_LOCK, 2, ucBuf, 0);
                uiSafeKey &= ~JP_LOCK;
            } else {
                uiSafeKey = uiKeyCode & (JP_STOP | JP_LOCK);
            }
            
//                if (uiKeyCode & (JP_STOP | JP_LOCK)) {                          /*  急停/闭锁状态按键不响应     */
//                    //uiSafeKey = uiKeyCode & (JP_STOP | JP_LOCK);
//                    continue;    
//                }
         
            Gds.uiMasterTimeoutTick = MS_TIMER;
        }
        if (uiKeyCode == JP_NOP) {
            continue;
        }
        if (uiKeyCode == uiKeyLast) {                                   /*  重复按键                    */
            if ((__GptnCurMenu && Gds.ucStatus != STA_IDLE) &&          /*  主控状态                    */
                (uiKeyCode != GpuiKeyTbl[KEY_MENU_UP]) &&
                (uiKeyCode != GpuiKeyTbl[KEY_MENU_DOWN]) &&
                (uiKeyCode != GpuiKeyTbl[KEY_MENU_LEFT]) &&
                (uiKeyCode != GpuiKeyTbl[KEY_MENU_RIGHT]) &&
                (uiKeyCode != GpuiKeyTbl[KEY_ABORT])) {            
                ;
            } else {
                continue;
            }
        } else {
            ledBlink(1, 1, 1, 3);
            Gds.ucIndicatorFlg.Bits.ucKeyPush = 1;                      /*  按键声音设置                */
        }
        
                                           
        if (keyNum(uiKeyCode) >= 2) {                                   /*  多个按键同时按下            */
            //uiKeyCode = uiKeyLast & uiKeyCode;
        }
        uiKeyLast = uiKeyCode;
        
        if (__GptnCurMenu) {                                            /*  菜单/动作操作               */

                miOnKey(uiKeyCode);
            
        } else {                                                        /*  在空闲状态第一次按下按键    */
            ucIsInvalidKey = FALSE;
            if (uiKeyCode & GpuiKeyTbl[KEY_ABORT]) {                        /*  停止键                      */                             
                if ((Gds.ucStatus != STA_IDLE) || (__GptnCurMenu == NULL)) {/*  主界面                      */   
                    if (Gdp.ucShieldNo >= Gdp.usStopRange) {
                        ucBuf[0] = Gdp.ucShieldNo - Gdp.usStopRange;
                    } else {
                        ucBuf[0] = 0;
                    }
                    if (ucBuf[0] < Gdp.usGblFaceMin) {
                        ucBuf[0] = Gdp.usGblFaceMin;
                    }
                    ucBuf[1] = Gdp.ucShieldNo + Gdp.usStopRange;
                    if (ucBuf[1] > Gdp.usGblFaceMax) {
                        ucBuf[1] = Gdp.usGblFaceMax;
                    }
                    //tpWrite(TP_DEFAULT_CHNL, __TP_ABORT, 2, ucBuf, 0);   
                } 
            } else if ((uiKeyCode & GpuiKeyTbl[KEY_ENTER])) {           /*  故障菜单快捷键              */                    
                ;
            } else if (uiKeyCode & GpuiKeyTbl[KEY_WORK_STAT]) {         /*  工况菜单快捷键              */                    
                ;                   			                      			
            } else if ((uiKeyCode & GpuiKeyTbl[KEY_MENU_LEFT]) || 
                       (uiKeyCode & GpuiKeyTbl[KEY_MENU_RIGHT]) || 
                       (uiKeyCode & GpuiKeyTbl[KEY_MENU_UP]) || 
                       (uiKeyCode & GpuiKeyTbl[KEY_MENU_DOWN])) {       /*  菜单导航                    */
                //miRootInit();

                miBasicCfgInit();
                miAdvancedCfgInit();
//                miAsqCfgInit();
//                miSysInfoInit();
                mpHome();                
            } else if (uiKeyCode & (GpuiKeyTbl[KEY_LEFT] | GpuiKeyTbl[KEY_RIGHT])) {
                                                                        /*  左/右邻架单动               */
                Gds.ucSlaveDir = (uiKeyCode == GpuiKeyTbl[KEY_RIGHT]) ? 1 : 0;
                Gds.ucStatus = STA_HOST;                
                //miNbrInit();                                            /*  邻架控制                    */
                //mpHome();
                
            } else if (uiKeyCode & GpuiKeyTbl[KEY_SELF]) {              /*  本架自控                    */
                //miSelfInit();
                //mpHome();                
            } else {                                                    /*  无效按键                    */
                ucIsInvalidKey = TRUE;
            }
            if (ucIsInvalidKey) {
                ucInvalidCnt++; 
                if (ucInvalidCnt >= 5) {                                 /*  连续5次无效按键             */
                    ucInvalidCnt = 0;
                    miKeyLockInit();
                    mpHome();
                }
            } else {
                ucInvalidCnt = 0;
            }            								
        }                               
    }
} 

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

