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

/*********************************************************************************************************
** Function name:           __osSegmentDelFree
** Descriptions:            删除一个空闲段
** input parameters:        posc            所要删除的段指针
**                          pposcFree       当前空闲段指针的地址
** output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
extern void  __osSegmentDelFree(OS_SEGMENT_CB  *posc, POS_SEGMENT_CB *pposcFree);

/*********************************************************************************************************
** Function name:           __osSegmentAddAheadFree
** Descriptions:            增加一个空闲段
** input parameters:        posc            所要增加的段指针
**                          pposcFree       当前空闲段指针的地址
** output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
extern void  __osSegmentAddAheadFree(OS_SEGMENT_CB  *posc, POS_SEGMENT_CB *pposcFree);
/*********************************************************************************************************
** Function name:           __osSegmentDelNeighbor
** Descriptions:            删除一个相邻段
** input parameters:        posc            所要删除的段指针
**                          pposcNeighbor   当前空闲段指针的地址
** output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
extern void  __osSegmentDelNeighbor(OS_SEGMENT_CB  *posc, POS_SEGMENT_CB *pposcNeighbor);

/*********************************************************************************************************
** Function name:           __osSegmentAddTailNeighbor
** Descriptions:            增加一个相邻段
** input parameters:        posc            所要增加的段指针
**                          pposcNeighbor   当前空闲段指针的地址
** output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
extern void  __osSegmentAddTailNeighbor(OS_SEGMENT_CB  *posc, POS_SEGMENT_CB *pposcNeighbor);




/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
