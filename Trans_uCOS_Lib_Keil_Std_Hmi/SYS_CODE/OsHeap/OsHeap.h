/****************************************Copyright (c)****************************************************
**                            
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               OsHeap.h
** Last modified Date:      2013-08-22
** Last Version:            1.0.0
** Descriptions:            OS HEAP 内存管理
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2013-08-22
** Version:                 1.0.0
** Descriptions:            OS HEAP 内存管理
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

#ifndef __OS_HEAP_H
#define __OS_HEAP_H

#include ".\OsHeapCfg.h"

/*********************************************************************************************************
  分段控制块类型定义
*********************************************************************************************************/

typedef struct __os_segment {

    struct __os_segment             *posNeighborLeft;                   /*  左边邻居分段                */
    struct __os_segment             *posNeighborRight;                  /*  右边邻居分段                */
    
    struct __os_segment             *posFreeListNext;                   /*  下一个空闲分段              */
    struct __os_segment             *posFreeListPrev;                   /*  上一个空闲分段              */
    
    void                            *pvDataPtr;                         /*  可用数据指针                */
    
    INT32U                           ulSegmentByteSize;                 /*  分段大小                    */
    INT8U                            ulSegmentUsedFlag;                 /*  分段是否被使用              */

} OS_SEGMENT_CB;

typedef OS_SEGMENT_CB             *POS_SEGMENT_CB;                      /*  分段指针                    */

/*********************************************************************************************************
  堆控制块类型定义
*********************************************************************************************************/

typedef struct __os_heap {
    
    struct __os_heap                *pohResrcList;                      /*  空闲资源单链表指针          */
    struct __os_segment             *posFreeSegment;                    /*  第一个空闲分段              */
    
    void                            *pvStartAddress;                    /*  堆内存起始地址              */
    
    INT32U                           ulTotalByteSize;                   /*  堆内存总大小                */
    INT32U                           ulSegmentCounter;                  /*  分段数量                    */
    
    INT32U                           ulUsedByteSize;                    /*  使用的字节数量              */
    INT32U                           ulFreeByteSize;                    /*  空闲的字节数量              */
    
} OS_HEAP_CB;

typedef OS_HEAP_CB                *POS_HEAP_CB;                         /*  堆控制块指针                */

/*********************************************************************************************************
** Function name:           osHeapCreate
** Descriptions:            建立一个内存堆
** input parameters:        pvStartAddr     内存堆起始地址
**                          ulByteSize      内存堆的大小
** output parameters:       NONE
** Returned value:          内存堆控制块指针
*********************************************************************************************************/
extern POS_HEAP_CB  osHeapCreate(void  *pvStartAddr, INT32U  ulByteSize);

/*********************************************************************************************************
** Function name:           osHeapDelete
** Descriptions:            删除一个内存堆
** input parameters:        ppzhDel         内存堆控制块指针的地址
** output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
extern void  osHeapDelete(POS_HEAP_CB  *ppzhDel);

/*********************************************************************************************************
** Function name:           osHeapAllocate
** Descriptions:            从一个内存堆中分配指定大小的内存
** input parameters:        pzhMem          内存堆控制块指针
**                          iByteSize       需要的内存大小
** output parameters:       NONE
** Returned value:          分配内存的起始地址
*********************************************************************************************************/
extern void  *osHeapAllocate(POS_HEAP_CB  pzhMem, int  iByteSize);

/*********************************************************************************************************
** Function name:           osHeapAllocateAlign
** Descriptions:            从一个内存堆中分配指定大小的内存, 同时满足对齐的特性
**                          此函数申请的内存必须是使用 OS_HEAP_OP_SAFE 选型为 1 时, 才能释放.
** input parameters:        pohMem          内存堆控制块指针
**                          uiByteSize      需要的内存大小
**                          uiAlign         指定内存对齐特性
** output parameters:       NONE
** Returned value:          分配内存的起始地址
*********************************************************************************************************/
extern void  *osHeapAllocateAlign(POS_HEAP_CB pohMem, unsigned int uiByteSize, unsigned int uiAlign);

/*********************************************************************************************************
** Function name:           osHeapFree
** Descriptions:            将以前获得的内存交还到内存堆
** input parameters:        pohMem          内存堆控制块指针
**                          pvFree          交还内存大小
** output parameters:       NONE
** Returned value:          成功返回 NULL 失败返回 pvFree
*********************************************************************************************************/
extern void  *osHeapFree(POS_HEAP_CB  pohMem, void * pvFree);

/*********************************************************************************************************
** Function name:           osHeapStatus
** Descriptions:            获得一个内存堆的状态
** input parameters:        pohMem,             内存堆控制块指针        可以为 NULL
**                          pulByteSize,        获得内存堆大小          可以为 NULL
**                          pulSegmentCounter,  获得分段数量            可以为 NULL
**                          pulUsedByteSize,    获得使用的字节数量      可以为 NULL
**                          pulFreeByteSize     获得空闲的字节数量      可以为 NULL
** output parameters:       NONE
** Returned value:          SYS_OK 正常 SYS_NOT_OK 错误
*********************************************************************************************************/
extern int osHeapStatus(POS_HEAP_CB  pohMem,
                     INT32U       *pulByteSize,
                     INT32U       *pulSegmentCounter,
                     INT32U       *pulUsedByteSize,
                     INT32U       *pulFreeByteSize);

/*********************************************************************************************************
** Function name:           osHeapStatusEx
** Descriptions:            获得一个内存堆的状态 (扩展接口)
** input parameters:        pohMem,             内存堆控制块指针        可以为 NULL
**                          pulByteSize,        获得内存堆大小          可以为 NULL
**                          pulSegmentCounter,  获得分段数量            可以为 NULL
**                          pulUsedByteSize,    获得使用的字节数量      可以为 NULL
**                          pulFreeByteSize     获得空闲的字节数量      可以为 NULL
**                          psegmentList[]      每一个分段的分段控制块指针列表
**                          pvReserve1
**                          pvReserve2
**                          pvReserve3
** output parameters:       NONE
** Returned value:          SYS_OK 正常 SYS_NOT_OK 错误
*********************************************************************************************************/
extern int    osHeapStatusEx(POS_HEAP_CB     pohMem,
                       INT32U           *pulByteSize,
                       INT32U           *pulSegmentCounter,
                       INT32U           *pulUsedByteSize,
                       INT32U           *pulFreeByteSize,
                       POS_SEGMENT_CB   psegmentList[],
                       void             *pvReserve1,
                       void             *pvReserve2,
                       void             *pvReserve3);


#if OS_HEAP_CONFIG_TYPE == 0
/*********************************************************************************************************
** Function name:           _osHeapInit
** Descriptions:            OS HEAP 内存管理初始化
** input parameters:        NONE
** output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
extern void   _osHeapInit(void);

#else

/*********************************************************************************************************
** Function name:           _osHeapInit
** Descriptions:            OS HEAP 内存管理初始化
** input parameters:        iMaxHeapNum     最大可以建立的堆的个数
**                          pohBuffer       控制块存放的首地址
** output parameters:       0:  表示正确
**                          -1: 表示错误
** Returned value:          NONE
*********************************************************************************************************/
extern int    _osHeapInit(int  iMaxHeapNum, void  *pohBuffer);

#endif                                                                  /*  OS_HEAP_CONFIG_TYPE == 0   */

#define osHeapInit         _osHeapInit


#endif                                                                  /*  __OS_HEAP_H                 */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
