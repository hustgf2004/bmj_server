;/****************************************Copyright (c)**************************************************
;**                              
;**                                     
;**                                 
;**
;**--------------File Info-------------------------------------------------------------------------------
;** File name:          Startup.s
;** Last modified Date: 2010-12-13	
;** Last Version:       1.0
;** Descriptions: 		
;**------------------------------------------------------------------------------------------------------
;** Created by:         	
;** Created date:       2010-12-13	
;** Version:            V1.0	
;** Descriptions:       The original version
;**
;** Modified by: 		
;** Modified date:
;** Version:	
;** Descriptions: 
;**
;********************************************************************************************************/
                        INCLUDE     ..\Head\LPC2200.INC                 ;/*  引入头文件                 */
                        PRESERVE8
    IF :DEF:    CTLR    
CODE_VER_NUM            EQU         0x00010012                          ;/*  控制器应用程序版本号       */
CODE_ID                 EQU         0x12                                ;/*  控制器应用程序类型         */ 
    ENDIF
  
    
;/********************************************************************************************************
;   define the stack size
;   定义堆栈的大小
;********************************************************************************************************/
SVC_STACK_LEGTH         EQU         0
FIQ_STACK_LEGTH         EQU         32
IRQ_STACK_LEGTH         EQU         9 * 8                               ;/*  每层嵌套需要9个字堆栈，允许*/ 
ABT_STACK_LEGTH         EQU         0
UND_STACK_LEGTH         EQU         0

                                                                        ;/*  8嵌套层                    */

NoInt                   EQU         0x80                                ;/*  禁止 IRQ 中断宏定义        */
NoFIQ                   EQU         0x40                                ;/*  禁止 FIQ 中断宏定义        */

USR32Mode               EQU         0x10                                ;/*  用户模式宏定义             */
SVC32Mode               EQU         0x13                                ;/*  管理模式宏定义             */
SYS32Mode               EQU         0x1f                                ;/*  系统模式宏定义             */
IRQ32Mode               EQU         0x12                                ;/*  IRQ模式宏定义              */
FIQ32Mode               EQU         0x11                                ;/*  FIQ模式宏定义              */


BCFG_08DEF              EQU         0x00000400                          ;/*   8Bit Bus                  */
BCFG_16DEF              EQU         0x10000400                          ;/*  16Bit Bus                  */
BCFG_32DEF              EQU         0x20000400                          ;/*  32Bit Bus                  */

;//                         |       IDCY    |       WST1    |       WST2    |
;//                         |   Idle width  |   Read width  |   Write width |
;//                         |   0x00 ~ 0x0f |   0x00 ~ 0x1f |   0x00~0x1f   |
BCFG_FLASH  EQU (BCFG_16DEF :OR: (0x00<<00) :OR: (0x02<<05) :OR: (0x02<<11)) ;
BCFG_PSRAM  EQU (BCFG_16DEF :OR: (0x00<<00) :OR: (0x00<<05) :OR: (0x00<<11)) ;
;//BCFG_CS2    EQU (BCFG_16DEF :OR: (0x00<<00) :OR: (0x02<<05) :OR: (0x02<<11)) ;
BCFG_CS2    EQU (BCFG_08DEF :OR: (0x00<<00) :OR: (0x02<<05) :OR: (0x02<<11))
BCFG_CS3    EQU (BCFG_08DEF :OR: (0x00<<00) :OR: (0x02<<05) :OR: (0x02<<11)) ;

;//BCFG_FLASH  EQU (BCFG_16DEF :OR: (0x0f<<00) :OR: (0x1f<<05) :OR: (0x1f<<11)) ;
;//BCFG_PSRAM  EQU (BCFG_16DEF :OR: (0x00<<00) :OR: (0x02<<05) :OR: (0x02<<11)) ;
;//BCFG_CS2    EQU (BCFG_16DEF :OR: (0x08<<00) :OR: (0x0f<<05) :OR: (0x0f<<11)) ;
;//BCFG_CS3    EQU (BCFG_16DEF :OR: (0x00<<00) :OR: (0x02<<05) :OR: (0x02<<11)) ;


;/********************************************************************************************************
; The emported labels    
; 给外部使用的标号在这声明
;********************************************************************************************************/
    IMPORT  __main                          
    IMPORT  FIQ_Exception
    IMPORT  IRQ_Handler       
    IMPORT  vicControl
    IMPORT  vicReset
    IMPORT  runFirst
    IMPORT  SoftwareInterrupt

    IMPORT |Image$$ROM_EXEC$$Length|
    IMPORT |Image$$IRAM$$Length| 
    ;IMPORT |Image$$ERAM$$Length| 

    IMPORT __use_two_region_memory
    IMPORT __use_no_semihosting_swi

;/********************************************************************************************************
; The emported labels    
; 给外部使用的标号在这声明
;********************************************************************************************************/
    EXPORT  start
    EXPORT  StackUsr
    EXPORT  top_of_heap
    EXPORT  bottom_of_heap
    EXPORT  bottom_of_Stacks
    EXPORT __user_initial_stackheap
    EXPORT CodeFlag
    EXPORT uiUndefinedAddr
    EXPORT uiPrefetchAddr
    EXPORT uiDataAbortAddr        
             preserve8
    CODE32
    AREA    vectors,CODE,READONLY
        ENTRY
Reset                                                                   ;/*  中断向量表                 */
        LDR         PC, ResetAddr
        LDR     	PC, uiUndefinedAddr
        LDR    	 	PC, SWI_Addr
        LDR     	PC, uiPrefetchAddr 
        LDR     	PC, uiDataAbortAddr
        DCD     	0xB8A06F58
        LDR     	PC, IRQ_Addr
        LDR     	PC, FIQ_Addr

ResetAddr           DCD     ResetInit
uiUndefinedAddr       DCD     0x00000024
SWI_Addr            DCD     SoftwareInterruptAdd
uiPrefetchAddr        DCD     0x0000002C
uiDataAbortAddr       DCD     0x00000030

Nouse               DCD     0
IRQ_Addr            DCD     IRQ_Handler
FIQ_Addr            DCD     FIQ_Handler



Undefined
        B       .
PrefetchAbort
        B       .
DataAbort
        B       .               
;/*********************************************************************************************************
;** Function name:           SoftwareInterruptAdd
;** Descriptions:            软中断处理
;** input parameters:		 none
;** output parameters:       none
;** Returned value:			 none
;**-------------------------------------------------------------------------------------------------------
;** Modified by:
;** Modified date:
;**-------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
SoftwareInterruptAdd 
        CMP     R0, #0x100
        BLO     SoftwareInterrupt
        B       vicControl

;/********************************************************************************************************
; 快速中断
;********************************************************************************************************/      
FIQ_Handler
        STMFD   SP!, {R0-R3, LR}
        LDR     R2, =FIQ_Exception+1
        ADD     LR, PC, #1
        BX      R2
    CODE16
        BX      PC
        NOP
    CODE32         
        LDMFD   SP!, {R0-R3, LR}
        SUBS    PC,  LR,  #4     
;/********************************************************************************************************
;** Function name:          resetInit
;** Descriptions:           复位处理
;** input parameters:       None
;** Returned value:         None
;**
;** Created by:             
;** Created Date:           2010-12-10
;**-------------------------------------------------------------------------------------------------------
;** Modified by:            
;** Modified date:          2010-12-10
;**-------------------------------------------------------------------------------------------------------
;********************************************************************************************************/    
resetInit		
        LDR     R2, =VICIntEnClr
        MVN     R3, #0x00
        STR	    R3, [R2] 

        LDR     R2, =VICSoftIntClear		
        STR	    R3, [R2] 

        LDR     R2, =VICIntSelect
        MOV     R3, #0x00
        STR	    R3, [R2] 

        LDR     R2, =VICDefVectAddr
        STR	    R3, [R2]

        LDR     R2, =VICVectAddr
        STR	    R3, [R2] 

        LDR     R0, =VICVectAddr0
        MOV     R1, #0
        MOV     R2, #0
        MOV     R3, #0
        MOV     R4, #0
        MOV     R5, #0
        MOV     R6, #0
        MOV     R7, #0
        MOV     R8, #0
        STMIA   R0!, {R1-R8}
        STMIA   R0!, {R1-R8}    

        LDR     R0, =VICVectCntl0
        STMIA   R0!, {R1-R8}
        STMIA   R0!, {R1-R8}     		

        LDR     R0, =PINSEL2
        LDR     R1, =0x0f814914
        STR     R1, [R0]

        LDR     R0, =BCFG0
        LDR     R1, =BCFG_FLASH
        STR     R1, [R0]

        LDR     R0, =BCFG1
        LDR     R1, =BCFG_PSRAM
        STR     R1, [R0]

        LDR     R0, =BCFG2
        LDR     R1, =BCFG_CS2
        STR     R1, [R0]

        LDR     R0, =BCFG3
        LDR     R1, =BCFG_CS3
        STR     R1, [R0]

        
        LDR     R0, =MEMMAP
        MOV     R1, #2
        
        BL      InitStack                   	                        ;/*  初始化堆栈                 */      
        B       __main

;/********************************************************************************************************
;** Function name:          ResetInit
;**
;** Descriptions:           复位处理
;**
;** input parameters:       None
;** Returned value:         None
;**
;** Created by:             Chenmingji
;** Created Date:           2004/02/02
;**-------------------------------------------------------------------------------------------------------
;** Modified by:            
;** Modified date:          
;**-------------------------------------------------------------------------------------------------------
;********************************************************************************************************/

ResetInit 
    ;初始化外部总线控制器，根据目标板决定配置

        
        BL      vicReset
        LDR     R0, =PINSEL2
    IF :DEF: EN_CRP
        LDR     R1, =0x0f814910
    ELSE
        LDR     R1, =0x0f814914
    ENDIF

        STR     R1, [R0]

        LDR     R0, =BCFG0
        LDR     R1, =BCFG_FLASH
        STR     R1, [R0]

        LDR     R0, =BCFG1
        LDR     R1, =BCFG_PSRAM
        STR     R1, [R0]

        LDR     R0, =BCFG2
        LDR     R1, =BCFG_CS2
        STR     R1, [R0]

        LDR     R0, =BCFG3
        LDR     R1, =BCFG_CS3
        STR     R1, [R0]
        
        BL      InitStack               ;初始化堆栈
                                        ;跳转到c语言入口
        B       __main
        
    
;/********************************************************************************************************
;** Function name:          InitStack
;**
;** Descriptions:           初始化堆栈
;**
;** input parameters:       None
;** Returned value:         None
;**
;** Created by:             Chenmingji
;** Created Date:           2004/02/02
;**-------------------------------------------------------------------------------------------------------
;** Modified by:            
;** Modified date:          2008-01-15
;**-------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
InitStack 
        MOV     R0, LR                
;Build the SVC stack
;设置管理模式堆栈
        MSR     CPSR_c, #0xd3        
        LDR     SP, StackSvc
        ;LDR     R1, =uiSwiFuncAddr 
        ;LDR     R2, =SoftwareInterruptAdd
        ;STR     R2, [R1]
;Build the IRQ stack
;设置中断模式堆栈
        MSR     CPSR_c, #0xd2
        LDR     SP, StackIrq  
        ;LDR     R1, =uiIrqFuncAddr 
        ;LDR     R2, =IRQ_Handler
        ;STR     R2, [R1]
;Build the FIQ stack    
;设置快速中断模式堆栈
        MSR     CPSR_c, #0xd1
        LDR     SP, StackFiq
        ;LDR     R1, =uiFiqFuncAddr 
        ;LDR     R2, =Fiq_Handle
        ;STR     R2, [R1]
;Build the DATAABORT stack
;设置中止模式堆栈
        MSR     CPSR_c, #0xd7
        LDR     SP, StackAbt
;Build the UDF stack
;设置未定义模式堆栈
        MSR     CPSR_c, #0xdb
        LDR     SP, StackUnd
;Build the SYS stack
;设置系统模式堆栈
        MSR     CPSR_c, #0xdf
        LDR     SP, =StackUsr           
    	BX    	R0

start
        B       runFirst
               
;/********************************************************************************************************
;** Function name:          Fiq_Handle
;** Descriptions:           快速中断处理
;** input parameters:       None
;** Returned value:         None
;**
;** Created by:             
;** Created Date:           2010-12-10
;**-------------------------------------------------------------------------------------------------------
;** Modified by:            
;** Modified date:          2010-12-10
;**-------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
Fiq_Handle
        STMFD   SP!, {R0-R3, LR}
        LDR     R3, =FIQ_Exception+1
        ADD     LR, PC, #1
        BX      R3
    CODE16
        BX      PC
        NOP        
    CODE32
        LDMFD   SP!, {R0-R3, LR}
        SUBS	PC, LR, #4
 
        EXPORT  switchBoot_Handler
switchBoot_Handler 
        LDR     R0, =MEMMAP
        MOV     R1, #0
        STR     R1, [R0]
        LDR     R0, =0x00000000
        BX      R0      

;/********************************************************************************************************
;** Function name:          __user_initial_stackheap
;**
;** Descriptions:           库函数初始化堆和栈，不能删除
;**
;** input parameters:       参考库函数手册
;** Returned value:         参考库函数手册
;**
;** Created by:             Chenmingji
;** Created Date:           2004/02/02
;**-------------------------------------------------------------------------------------------------------
;** Modified by:            
;** Modified date:          2008-01-15
;**-------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
__user_initial_stackheap    
    LDR     R0, =bottom_of_heap		
    ;LDR     R1, =StackUsr			
    LDR     R2, =top_of_heap		
    LDR     R3, =bottom_of_Stacks		
    BX      LR
    

    EXPORT _sys_exit
_sys_exit
    B       .

    EXPORT __rt_div0
    EXPORT fputc
    EXPORT fgetc
    EXPORT _sys_close
    EXPORT _sys_write
    EXPORT _sys_read
    EXPORT _sys_istty
    EXPORT _sys_seek
    EXPORT _sys_ensure
    EXPORT _sys_flen
    EXPORT _sys_tmpnam
    EXPORT _sys_command_string

__rt_div0
fputc
fgetc
_sys_close
_sys_write
_sys_read
_sys_istty
_sys_seek
_sys_ensure
_sys_flen
_sys_tmpnam
_sys_command_string
    NOP	
    MOV     R0, #0
    BX      LR	

    LTORG
StackSvc           DCD     SvcStackSpace  + (SVC_STACK_LEGTH - 1) * 4
StackIrq           DCD     IrqStackSpace  + (IRQ_STACK_LEGTH - 1) * 4
StackFiq           DCD     FiqStackSpace  + (FIQ_STACK_LEGTH - 1) * 4
StackAbt           DCD     AbtStackSpace  + (ABT_STACK_LEGTH - 1) * 4
StackUnd           DCD     UndtStackSpace + (UND_STACK_LEGTH - 1) * 4



        AREA   CODES_FLAG,CODE,READONLY
        EXPORT CodeFlag
        EXPORT CODE_VER
CodeFlag
CODE_VER
    DCD CODE_VER_NUM
CODE_LEN        
    DCD |Image$$ROM_EXEC$$Length| + |Image$$IRAM$$Length|; + |Image$$ERAM$$Length| 
    DCD CODE_ID     
                

        AREA    MyStacks, DATA, NOINIT, ALIGN = 2;                      ;/*  分配堆栈空间               */         
SvcStackSpace      SPACE   SVC_STACK_LEGTH * 4                          ;/*  管理模式堆栈空间           */
IrqStackSpace      SPACE   IRQ_STACK_LEGTH * 4                          ;/*  中断模式堆栈空间           */
FiqStackSpace      SPACE   FIQ_STACK_LEGTH * 4                          ;/*  快速中断模式堆栈空间       */
AbtStackSpace      SPACE   ABT_STACK_LEGTH * 4                          ;/*  中止义模式堆栈空间         */
UndtStackSpace     SPACE   UND_STACK_LEGTH * 4                          ;/*  未定义模式堆栈             */ 

        AREA    HeapBottom, DATA, NOINIT
bottom_of_heap    	SPACE   1

        AREA    StackBottom, DATA, NOINIT
bottom_of_Stacks    SPACE   1

        AREA    HeapTop, DATA, NOINIT
top_of_heap

        AREA    StacksTop, DATA, NOINIT
StackUsr        
    END
;/*********************************************************************************************************
;**                            End Of File
;********************************************************************************************************/
