;****************************************CopyrightEQU  (c)************************************************
;**                         
;**
;**                               
;**
;**--------------File Info--------------------------------------------------------------------------------
;** File name:           LPC2294.inc
;** Last modified Date:  2012-12-31
;** Last Version:        1.0
;** Descriptions:        Defines the special registers and firmware programs for
;**                      lpc22xx\lpc212x\lpc211x\lpc210x
;**-------------------------------------------------------------------------------------------------------
;** Modified by:         
;** Modified date:       2012-12-31
;** Version:             1.0
;** Descriptions:        lpc22xx\lpc212x\lpc211x\lpc210x芯片的头文件
;**
;**-------------------------------------------------------------------------------------------------------
;** Modified by:
;** Modified date:
;** Version:
;** Descriptions:
;**
;********************************************************************************************************/
;/*******************************************************************************************************
;  EXTERNAL MEMORY CONTROLLER (EMC)
;  外部总线控制器
;********************************************************************************************************/

BCFG0           EQU 0xFFE00000                                          ;  lpc22xx only 
BCFG1           EQU 0xFFE00004                                          ;  lpc22xx only 
BCFG2           EQU 0xFFE00008                                          ;  lpc22xx only 
BCFG3           EQU 0xFFE0000C                                          ;  lpc22xx only 

;/********************************************************************************************************
;;  External Interrupts
;;  外部中断控制寄存器
;********************************************************************************************************/

EXTINT          EQU 0xE01FC140
EXTWAKE         EQU 0xE01FC144
EXTMODE         EQU 0xE01FC148                                          ;  Not used for lpc210x
EXTPOLAR        EQU 0xE01FC14C                                          ;  Not used for lpc210x

;/********************************************************************************************************
;  SMemory mapping control.
;  内存remap控制寄存器
;********************************************************************************************************/

MEMMAP          EQU 0xE01FC040

;/********************************************************************************************************
;  Phase Locked Loop (PLL)
;  PLL控制寄存器
;********************************************************************************************************/

PLLCON          EQU 0xE01FC080
PLLCFG          EQU 0xE01FC084
PLLSTAT         EQU 0xE01FC088
PLLFEED         EQU 0xE01FC08C

;/********************************************************************************************************
;  Power Control
;  功率控制寄存器
;********************************************************************************************************/

PCON            EQU 0xE01FC0C0
PCONP           EQU 0xE01FC0C4

;/********************************************************************************************************
;  VPB Divider
;  VLSI外设总线（VPB）分频寄存器
;********************************************************************************************************/

VPBDIV          EQU 0xE01FC100

;/********************************************************************************************************
;  Memory Accelerator Module (MAM)
;  存储器加速模块
;********************************************************************************************************/

MAMCR           EQU 0xE01FC000
MAMTIM          EQU 0xE01FC004

;/********************************************************************************************************
;  Vectored Interrupt Controller (VIC)
;  向量中断控制器(VIC)的特殊寄存器
;********************************************************************************************************/

VICIRQStatus    EQU 0xFFFFF000
VICFIQStatus    EQU 0xFFFFF004
VICRawIntr      EQU 0xFFFFF008
VICIntSelect    EQU 0xFFFFF00C
VICIntEnable    EQU 0xFFFFF010
VICIntEnClr     EQU 0xFFFFF014
VICSoftInt      EQU 0xFFFFF018
VICSoftIntClear EQU 0xFFFFF01C
VICProtection   EQU 0xFFFFF020
VICVectAddr     EQU 0xFFFFF030
VICDefVectAddr  EQU 0xFFFFF034
VICVectAddr0    EQU 0xFFFFF100
VICVectAddr1    EQU 0xFFFFF104
VICVectAddr2    EQU 0xFFFFF108
VICVectAddr3    EQU 0xFFFFF10C
VICVectAddr4    EQU 0xFFFFF110
VICVectAddr5    EQU 0xFFFFF114
VICVectAddr6    EQU 0xFFFFF118
VICVectAddr7    EQU 0xFFFFF11C
VICVectAddr8    EQU 0xFFFFF120
VICVectAddr9    EQU 0xFFFFF124
VICVectAddr10   EQU 0xFFFFF128
VICVectAddr11   EQU 0xFFFFF12C
VICVectAddr12   EQU 0xFFFFF130
VICVectAddr13   EQU 0xFFFFF134
VICVectAddr14   EQU 0xFFFFF138
VICVectAddr15   EQU 0xFFFFF13C
VICVectCntl0    EQU 0xFFFFF200
VICVectCntl1    EQU 0xFFFFF204
VICVectCntl2    EQU 0xFFFFF208
VICVectCntl3    EQU 0xFFFFF20C
VICVectCntl4    EQU 0xFFFFF210
VICVectCntl5    EQU 0xFFFFF214
VICVectCntl6    EQU 0xFFFFF218
VICVectCntl7    EQU 0xFFFFF21C
VICVectCntl8    EQU 0xFFFFF220
VICVectCntl9    EQU 0xFFFFF224
VICVectCntl10   EQU 0xFFFFF228
VICVectCntl11   EQU 0xFFFFF22C
VICVectCntl12   EQU 0xFFFFF230
VICVectCntl13   EQU 0xFFFFF234
VICVectCntl14   EQU 0xFFFFF238
VICVectCntl15   EQU 0xFFFFF23C

;/********************************************************************************************************
;  Pin Connect Block
;  管脚连接模块控制寄存器
;********************************************************************************************************/

PINSEL0         EQU 0xE002C000
PINSEL1         EQU 0xE002C004
PINSEL2         EQU 0xE002C014                                          ;  Not used for lpc210x

;/********************************************************************************************************
;  General Purpose Input/Output (GPIO)
;  通用并行IO口的特殊寄存器
;********************************************************************************************************/

IOPIN           EQU 0xE0028000                                          ;  lpc210x only 
IOSET           EQU 0xE0028004                                          ;  lpc210x only 
IODIR           EQU 0xE0028008                                          ;  lpc210x only 
IOCLR           EQU 0xE002800C                                          ;  lpc210x only 

IO0PIN          EQU 0xE0028000                                          ;  Not used for lpc210x
IO0SET          EQU 0xE0028004                                          ;  Not used for lpc210x
IO0DIR          EQU 0xE0028008                                          ;  Not used for lpc210x
IO0CLR          EQU 0xE002800C                                          ;  Not used for lpc210x

IO1PIN          EQU 0xE0028010                                          ;  Not used for lpc210x
IO1SET          EQU 0xE0028014                                          ;  Not used for lpc210x
IO1DIR          EQU 0xE0028018                                          ;  Not used for lpc210x
IO1CLR          EQU 0xE002801C                                          ;  Not used for lpc210x

IO2PIN          EQU 0xE0028020                                          ;  lpc22xx only 
IO2SET          EQU 0xE0028024                                          ;  lpc22xx only 
IO2DIR          EQU 0xE0028028                                          ;  lpc22xx only 
IO2CLR          EQU 0xE002802C                                          ;  lpc22xx only 

IO3PIN          EQU 0xE0028030                                          ;  lpc22xx only 
IO3SET          EQU 0xE0028034                                          ;  lpc22xx only 
IO3DIR          EQU 0xE0028038                                          ;  lpc22xx only 
IO3CLR          EQU 0xE002803C                                          ;  lpc22xx only 

;/********************************************************************************************************
;  Universal Asynchronous Receiver Transmitter 0 (UART0)
;  通用异步串行口0(UART0)的特殊寄存器
;********************************************************************************************************/

U0RBR           EQU 0xE000C000
U0THR           EQU 0xE000C000
U0IER           EQU 0xE000C004
U0IIR           EQU 0xE000C008
U0FCR           EQU 0xE000C008
U0LCR           EQU 0xE000C00C
U0LSR           EQU 0xE000C014
U0SCR           EQU 0xE000C01C
U0DLL           EQU 0xE000C000
U0DLM           EQU 0xE000C004

;/********************************************************************************************************
;  Universal Asynchronous Receiver Transmitter 1 (UART1)
;  通用异步串行口1(UART1)的特殊寄存器
;********************************************************************************************************/

U1RBR           EQU 0xE0010000
U1THR           EQU 0xE0010000
U1IER           EQU 0xE0010004
U1IIR           EQU 0xE0010008
U1FCR           EQU 0xE0010008
U1LCR           EQU 0xE001000C
U1MCR           EQU 0xE0010010
U1LSR           EQU 0xE0010014
U1MSR           EQU 0xE0010018
U1SCR           EQU 0xE001001C
U1DLL           EQU 0xE0010000
U1DLM           EQU 0xE0010004

;/********************************************************************************************************
;  I2C (8/16 bit data bus)
;  芯片间总线（I2C）的特殊寄存器
;********************************************************************************************************/

I2CONSET        EQU 0xE001C000
I2STAT          EQU 0xE001C004
I2DAT           EQU 0xE001C008
I2ADR           EQU 0xE001C00C
I2SCLH          EQU 0xE001C010
I2SCLL          EQU 0xE001C014
I2CONCLR        EQU 0xE001C018

;/********************************************************************************************************
;  SPI (Serial Peripheral Interface)
;  SPI总线接口的特殊寄存器
        ;  only for lpc210x
;********************************************************************************************************/

SPI_SPCR        EQU 0xE0020000
SPI_SPSR        EQU 0xE0020004
SPI_SPDR        EQU 0xE0020008
SPI_SPCCR       EQU 0xE002000C
SPI_SPINT       EQU 0xE002001C

S0PCR           EQU 0xE0020000                                          ;  Not used for lpc210x
S0PSR           EQU 0xE0020004                                          ;  Not used for lpc210x
S0PDR           EQU 0xE0020008                                          ;  Not used for lpc210x
S0PCCR          EQU 0xE002000C                                          ;  Not used for lpc210x
S0PINT          EQU 0xE002001C                                          ;  Not used for lpc210x

S1PCR           EQU 0xE0030000                                          ;  Not used for lpc210x
S1PSR           EQU 0xE0030004                                          ;  Not used for lpc210x
S1PDR           EQU 0xE0030008                                          ;  Not used for lpc210x
S1PCCR          EQU 0xE003000C                                          ;  Not used for lpc210x
S1PINT          EQU 0xE003001C                                          ;  Not used for lpc210x

;/********************************************************************************************************
;  CAN CONTROLLERS AND ACCEPTANCE FILTER
;  CAN控制器和接收路波器
;  lpc2119\lpc2129\lpc2292\lpc2294 only
;********************************************************************************************************/

CAN1MOD         EQU 0xE0044000                                          
CAN1CMR         EQU 0xE0044004                                          
CAN1GSR         EQU 0xE0044008                                          
CAN1ICR         EQU 0xE004400C                                          
CAN1IER         EQU 0xE0044010                                          
CAN1BTR         EQU 0xE0044014                                          
CAN1EWL         EQU 0xE004401C                                          
CAN1SR          EQU 0xE0044020                                          
CAN1RFS         EQU 0xE0044024                                          
CAN1RDA         EQU 0xE0044028                                          
CAN1RDB         EQU 0xE004402C                                          
CAN1TFI1        EQU 0xE0044030                                          
CAN1TID1        EQU 0xE0044034                                          
CAN1TDA1        EQU 0xE0044038                                          
CAN1TDB1        EQU 0xE004403C                                          
CAN1TFI2        EQU 0xE0044040                                          
CAN1TID2        EQU 0xE0044044                                          
CAN1TDA2        EQU 0xE0044048                                          
CAN1TDB2        EQU 0xE004404C                                          
CAN1TFI3        EQU 0xE0044050                                          
CAN1TID3        EQU 0xE0044054                                          
CAN1TDA3        EQU 0xE0044058                                          
CAN1TDB3        EQU 0xE004405C                                          

CAN2MOD         EQU 0xE0048000                                          
CAN2CMR         EQU 0xE0048004                                          
CAN2GSR         EQU 0xE0048008                                          
CAN2ICR         EQU 0xE004800C                                          
CAN2IER         EQU 0xE0048010                                          
CAN2BTR         EQU 0xE0048014                                          
CAN2EWL         EQU 0xE004801C                                          
CAN2SR          EQU 0xE0048020                                          
CAN2RFS         EQU 0xE0048024                                          
CAN2RDA         EQU 0xE0048028                                          
CAN2RDB         EQU 0xE004802C                                          
CAN2TFI1        EQU 0xE0048030                                          
CAN2TID1        EQU 0xE0048034                                          
CAN2TDA1        EQU 0xE0048038                                          
CAN2TDB1        EQU 0xE004803C                                          
CAN2TFI2        EQU 0xE0048040                                          
CAN2TID2        EQU 0xE0048044                                          
CAN2TDA2        EQU 0xE0048048                                          
CAN2TDB2        EQU 0xE004804C                                          
CAN2TFI3        EQU 0xE0048050                                          
CAN2TID3        EQU 0xE0048054                                          
CAN2TDA3        EQU 0xE0048058                                          
CAN2TDB3        EQU 0xE004805C                                          

CAN3MOD         EQU 0xE004C000                                          
CAN3CMR         EQU 0xE004C004                                          
CAN3GSR         EQU 0xE004C008                                          
CAN3ICR         EQU 0xE004C00C                                          
CAN3IER         EQU 0xE004C010                                          
CAN3BTR         EQU 0xE004C014                                          
CAN3EWL         EQU 0xE004C01C                                          
CAN3SR          EQU 0xE004C020                                          
CAN3RFS         EQU 0xE004C024                                          
CAN3RDA         EQU 0xE004C028                                          
CAN3RDB         EQU 0xE004C02C                                          
CAN3TFI1        EQU 0xE004C030                                          
CAN3TID1        EQU 0xE004C034                                          
CAN3TDA1        EQU 0xE004C038                                          
CAN3TDB1        EQU 0xE004C03C                                          
CAN3TFI2        EQU 0xE004C040                                          
CAN3TID2        EQU 0xE004C044                                          
CAN3TDA2        EQU 0xE004C048                                          
CAN3TDB2        EQU 0xE004C04C                                          
CAN3TFI3        EQU 0xE004C050                                          
CAN3TID3        EQU 0xE004C054                                          
CAN3TDA3        EQU 0xE004C058                                          
CAN3TDB3        EQU 0xE004C05C                                          

CAN4MOD         EQU 0xE0050000                                          
CAN4CMR         EQU 0xE0050004                                          
CAN4GSR         EQU 0xE0050008                                          
CAN4ICR         EQU 0xE005000C                                          
CAN4IER         EQU 0xE0050010                                          
CAN4BTR         EQU 0xE0050014                                          
CAN4EWL         EQU 0xE005001C                                          
CAN4SR          EQU 0xE0050020                                          
CAN4RFS         EQU 0xE0050024                                          
CAN4RDA         EQU 0xE0050028                                          
CAN4RDB         EQU 0xE005002C                                          
CAN4TFI1        EQU 0xE0050030                                          
CAN4TID1        EQU 0xE0050034                                          
CAN4TDA1        EQU 0xE0050038                                          
CAN4TDB1        EQU 0xE005003C                                          
CAN4TFI2        EQU 0xE0050040                                          
CAN4TID2        EQU 0xE0050044                                          
CAN4TDA2        EQU 0xE0050048                                          
CAN4TDB2        EQU 0xE005004C                                          
CAN4TFI3        EQU 0xE0050050                                          
CAN4TID3        EQU 0xE0050054                                          
CAN4TDA3        EQU 0xE0050058                                          
CAN4TDB3        EQU 0xE005005C                                          

CAN5MOD         EQU 0xE0054000                                          
CAN5CMR         EQU 0xE0054004                                          
CAN5GSR         EQU 0xE0054008                                          
CAN5ICR         EQU 0xE005400C                                          
CAN5IER         EQU 0xE0054010                                          
CAN5BTR         EQU 0xE0054014                                          
CAN5EWL         EQU 0xE005401C                                          
CAN5SR          EQU 0xE0054020                                          
CAN5RFS         EQU 0xE0054024                                          
CAN5RDA         EQU 0xE0054028                                          
CAN5RDB         EQU 0xE005402C                                          
CAN5TFI1        EQU 0xE0054030                                          
CAN5TID1        EQU 0xE0054034                                          
CAN5TDA1        EQU 0xE0054038                                          
CAN5TDB1        EQU 0xE005403C                                          
CAN5TFI2        EQU 0xE0054040                                          
CAN5TID2        EQU 0xE0054044                                          
CAN5TDA2        EQU 0xE0054048                                          
CAN5TDB2        EQU 0xE005404C                                          
CAN5TFI3        EQU 0xE0054050                                          
CAN5TID3        EQU 0xE0054054                                          
CAN5TDA3        EQU 0xE0054058                                          
CAN5TDB3        EQU 0xE005405C                                          

CAN6MOD         EQU 0xE0058000                                          ;  lpc2292\lpc2294 only
CAN6CMR         EQU 0xE0058004                                          ;  lpc2292\lpc2294 only
CAN6GSR         EQU 0xE0058008                                          ;  lpc2292\lpc2294 only
CAN6ICR         EQU 0xE005800C                                          ;  lpc2292\lpc2294 only
CAN6IER         EQU 0xE0058010                                          ;  lpc2292\lpc2294 only
CAN6BTR         EQU 0xE0058014                                          ;  lpc2292\lpc2294 only
CAN6EWL         EQU 0xE005801C                                          ;  lpc2292\lpc2294 only
CAN6SR          EQU 0xE0058020                                          ;  lpc2292\lpc2294 only
CAN6RFS         EQU 0xE0058024                                          ;  lpc2292\lpc2294 only
CAN6RDA         EQU 0xE0058028                                          ;  lpc2292\lpc2294 only
CAN6RDB         EQU 0xE005802C                                          ;  lpc2292\lpc2294 only
CAN6TFI1        EQU 0xE0058030                                          ;  lpc2292\lpc2294 only
CAN6TID1        EQU 0xE0058034                                          ;  lpc2292\lpc2294 only
CAN6TDA1        EQU 0xE0058038                                          ;  lpc2292\lpc2294 only
CAN6TDB1        EQU 0xE005803C                                          ;  lpc2292\lpc2294 only
CAN6TFI2        EQU 0xE0058040                                          ;  lpc2292\lpc2294 only
CAN6TID2        EQU 0xE0058044                                          ;  lpc2292\lpc2294 only
CAN6TDA2        EQU 0xE0058048                                          ;  lpc2292\lpc2294 only
CAN6TDB2        EQU 0xE005804C                                          ;  lpc2292\lpc2294 only
CAN6TFI3        EQU 0xE0058050                                          ;  lpc2292\lpc2294 only
CAN6TID3        EQU 0xE0058054                                          ;  lpc2292\lpc2294 only
CAN6TDA3        EQU 0xE0058058                                          ;  lpc2292\lpc2294 only
CAN6TDB3        EQU 0xE005805C                                          ;  lpc2292\lpc2294 only 

CANTxSR         EQU 0xE0040000                                          
CANRxSR         EQU 0xE0040004                                          
CANMSR          EQU 0xE0040008                                          

CANAFMR         EQU 0xE003C000                                          
CANSFF_sa       EQU 0xE003C004                                          
CANSFF_GRP_sa   EQU 0xE003C008                                          
CANEFF_sa       EQU 0xE003C00C                                          
CANEFF_GRP_sa   EQU 0xE003C010                                          
CANENDofTable   EQU 0xE003C014                                          
CANLUTerrAd     EQU 0xE003C018                                          
CANLUTerr       EQU 0xE003C01C                                          
                                  
CANAFRAM        EQU 0xE0038000                                          ;  CAN Acceptance Filter RAM 

;/********************************************************************************************************
;  Timer 0
;  定时器0的特殊寄存器
;********************************************************************************************************/

T0IR            EQU 0xE0004000
T0TCR           EQU 0xE0004004
T0TC            EQU 0xE0004008
T0PR            EQU 0xE000400C
T0PC            EQU 0xE0004010
T0MCR           EQU 0xE0004014
T0MR0           EQU 0xE0004018
T0MR1           EQU 0xE000401C
T0MR2           EQU 0xE0004020
T0MR3           EQU 0xE0004024
T0CCR           EQU 0xE0004028
T0CR0           EQU 0xE000402C
T0CR1           EQU 0xE0004030
T0CR2           EQU 0xE0004034
T0CR3           EQU 0xE0004038
T0EMR           EQU 0xE000403C

;/********************************************************************************************************
;  Timer 1
;  定时器1的特殊寄存器
;********************************************************************************************************/

T1IR            EQU 0xE0008000
T1TCR           EQU 0xE0008004
T1TC            EQU 0xE0008008
T1PR            EQU 0xE000800C
T1PC            EQU 0xE0008010
T1MCR           EQU 0xE0008014
T1MR0           EQU 0xE0008018
T1MR1           EQU 0xE000801C
T1MR2           EQU 0xE0008020
T1MR3           EQU 0xE0008024
T1CCR           EQU 0xE0008028
T1CR0           EQU 0xE000802C
T1CR1           EQU 0xE0008030
T1CR2           EQU 0xE0008034
T1CR3           EQU 0xE0008038
T1EMR           EQU 0xE000803C

;/********************************************************************************************************
;  Pulse Width Modulator (PWM)
;  脉宽调制器的特殊寄存器
;********************************************************************************************************/

PWMIR           EQU 0xE0014000
PWMTCR          EQU 0xE0014004
PWMTC           EQU 0xE0014008
PWMPR           EQU 0xE001400C
PWMPC           EQU 0xE0014010
PWMMCR          EQU 0xE0014014
PWMMR0          EQU 0xE0014018
PWMMR1          EQU 0xE001401C
PWMMR2          EQU 0xE0014020
PWMMR3          EQU 0xE0014024
PWMMR4          EQU 0xE0014040
PWMMR5          EQU 0xE0014044
PWMMR6          EQU 0xE0014048
PWMPCR          EQU 0xE001404C
PWMLER          EQU 0xE0014050

;/********************************************************************************************************
;  A/D CONVERTER
;  A/D转换器
;********************************************************************************************************/

ADCR            EQU 0xE0034000                                          ;  Not used for lpc210x
ADDR            EQU 0xE0034004                                          ;  Not used for lpc210x

;/********************************************************************************************************
;  Real Time Clock
;  实时时钟的特殊寄存器
;********************************************************************************************************/

ILR             EQU 0xE0024000
CTC             EQU 0xE0024004
CCR             EQU 0xE0024008
CIIR            EQU 0xE002400C
AMR             EQU 0xE0024010
CTIME0          EQU 0xE0024014
CTIME1          EQU 0xE0024018
CTIME2          EQU 0xE002401C
SEC             EQU 0xE0024020
MIN             EQU 0xE0024024
HOUR            EQU 0xE0024028
DOM             EQU 0xE002402C
DOW             EQU 0xE0024030
DOY             EQU 0xE0024034
MONTH           EQU 0xE0024038
YEAR            EQU 0xE002403C
ALSEC           EQU 0xE0024060
ALMIN           EQU 0xE0024064
ALHOUR          EQU 0xE0024068
ALDOM           EQU 0xE002406C
ALDOW           EQU 0xE0024070
ALDOY           EQU 0xE0024074
ALMON           EQU 0xE0024078
ALYEAR          EQU 0xE002407C
PREINT          EQU 0xE0024080
PREFRAC         EQU 0xE0024084

;/********************************************************************************************************
;  Watchdog
;  看门狗的特殊寄存器
;********************************************************************************************************/

WDMOD           EQU 0xE0000000
WDTC            EQU 0xE0000004
WDFEED          EQU 0xE0000008
WDTV            EQU 0xE000000C

;/********************************************************************************************************
;  Define firmware Functions
;  定义固件函数
;********************************************************************************************************/
rm_init_entry             EQU  0x7fffff91
rm_undef_handler          EQU  0x7fffffa0
rm_prefetchabort_handler  EQU  0x7fffffb0
rm_dataabort_handler      EQU  0x7fffffc0
rm_irqhandler             EQU  0x7fffffd0
rm_irqhandler2            EQU  0x7fffffe0
iap_entry                 EQU  0x7ffffff1

;/********************************************************************************************************
;  End File
;********************************************************************************************************/
 END
