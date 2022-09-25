/****************************************Copyright (c)****************************************************
**                            
**
**                                
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               OsHeapLib.c
** Latest modified Date:    2013-08-22
** Latest Version:          1.0
** Descriptions:            堆栈底层函数库
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2013-08-22
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


#ifndef __OS_HEAP_LIB_H
#define __OS_HEAP_LIB_H

#if     OS_HEAP_CONFIG_TYPE == 0
/*********************************************************************************************************
** Function name:           _osHeapInit
** Descriptions:            OS HEAP 内存管理初始化
** input parameters:        NONE
**                          
** output parameters:       NONE
**                          
** Returned value:          NONE
*********************************************************************************************************/
extern void _osHeapInit(void);

#else
/*********************************************************************************************************
** Function name:           _osHeapInit
** Descriptions:            OS HEAP 内存管理初始化
** input parameters:        uiMaxHeapNum    最大可以建立的堆的个数
**                          phcBuf          控制块存放的首地址
** output parameters:       0:  表示正确
**                          -1: 表示错误
** Returned value:          NONE
*********************************************************************************************************/
extern int _osHeapInit(unsigned int uiMaxHeapNum, void  *phcBuf);
#endif
/*********************************************************************************************************
** Function name:           __osHeapBuild
** Descriptions:            建立一个内存堆
** input parameters:        pvStartAddr     内存堆起始地址
**                          uiByteSize      内存堆的大小
** output parameters:       NONE
** Returned value:          内存堆控制块指针
*********************************************************************************************************/
extern POS_HEAP_CB  __osHeapBuild(void  *pvStartAddr, unsigned int uiByteSize);

/*********************************************************************************************************
** Function name:           __osHeapDelete
** Descriptions:            删除一个内存堆
** input parameters:        ppzhDel         内存堆控制块指针的地址
** output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
extern void  *__osHeapDelete(POS_HEAP_CB  pohcDel);

/*********************************************************************************************************
** Function name:           __osHeapAllocate
** Descriptions:            从一个内存堆中分配指定大小的内存
** input parameters:        pzhMem          内存堆控制块指针
**                          uiByteSize      需要的内存大小
** output parameters:       NONE
** Returned value:          分配内存的起始地址
*********************************************************************************************************/
extern void  *__osHeapAllocate(POS_HEAP_CB  pzhMem, unsigned int uiByteSize);

/*********************************************************************************************************
** Function name:           osHeapAllocateAlign
** Descriptions:            从一个内存堆中分配指定大小的内存, 同时满足对齐的特性
**                          此函数申请的内存必须是使用 OS_HEAP_OP_SAFE 选型为 1 时, 才能释放.
** input parameters:        pzhMem          内存堆控制块指针
**                          iiByteSize      需要的内存大小
**                          iiAlign         指定内存对齐特性
** output parameters:       NONE
** Returned value:          分配内存的起始地址
*********************************************************************************************************/
extern void  *__osHeapAllocateAlign(POS_HEAP_CB  pzhMem, unsigned int iByteSize, unsigned int uiAlign);

/*********************************************************************************************************
** Function name:           __osHeapFree
** Descriptions:            将以前获得的内存交还到内存堆
** input parameters:        pzhMem          内存堆控制块指针
**                          pvFree          交还内存大小
** output parameters:       NONE
** Returned value:          成功返回 NULL 失败返回 pvFree
*********************************************************************************************************/
extern void  *__osHeapFree(POS_HEAP_CB  pohMem, void * pvFree);

typedef struct __heap_cb_list {
    INT32U          uiListUsedFlag;
    OS_HEAP_CB     *pohcHeapCb;
} __HEAP_CB_LIST;

#define roundup(a, b)   ((a / b) + \
                        ((a % b) ? 1 : 0)) * \
                        b

#define OSC_ALIGN_SIZE  roundup(sizeof(OS_SEGMENT_CB), OS_HEAP_PAGESIZE)
extern __HEAP_CB_LIST __GhcFreeList;                                    /*  空闲堆控制块指针            */

#endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
