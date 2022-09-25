/****************************************Copyright (c)****************************************************
**                            
**
**                                
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               OsHeapShow.h
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
extern INT32S osHeapStatus(POS_HEAP_CB  pohMem,
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
extern INT32S osHeapStatusEx (POS_HEAP_CB     pohMem,
                    INT32U           *pulByteSize,
                    INT32U           *pulSegmentCounter,
                    INT32U           *pulUsedByteSize,
                    INT32U           *pulFreeByteSize,
                    POS_SEGMENT_CB   psegmentList[],
                    void             *pvReserve1,
                    void             *pvReserve2,
                    void             *pvReserve3);
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
