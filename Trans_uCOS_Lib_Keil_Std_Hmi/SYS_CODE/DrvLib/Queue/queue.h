/***********************************************Copyright (c)********************************************* 
**                                
**                                      
**                                       
** 
**--------------File Info--------------------------------------------------------------------------------- 
** File name:               queue.h 
** Last modified Date:      2012-12-31 
** Last Version:            1.0 
** Descriptions:            数据队列中间件 
** 
**-------------------------------------------------------------------------------------------------------- 
** Created by:               
** Created date:            2012-12-31 
** Version:                 1.0 
** Descriptions:             
** 
**-------------------------------------------------------------------------------------------------------- 
** Modified by:              
** Modified Date:            
** Version:                  
** Descriptions:            
** 
*********************************************************************************************************/ 
#ifndef __QUEUE_H 
#define __QUEUE_H 

#ifdef __cplusplus
extern "C" {
#endif   
/********************************************************************************************************* 
  队列操作返回 
*********************************************************************************************************/ 

#define QUEUE_PARA_ERR      -1                                          /* 参数错误                     */ 

 
#define QUEUE_OK            0                                           /* 操作成功                     */ 
#define QUEUE_NOK           1                                           /* 操作失败                     */             

#define QUEUE_FULL          5                                           /* 返回队列满状态               */ 
#define QUEUE_EMPTY         4                                           /* 返回队列空状态               */ 
 
/********************************************************************************************************* 
  下面的宏定义是传递给用户处理队列满时，判断对立是FIFO,还是LIFO 
*********************************************************************************************************/ 
#define Q_WRITE_MODE        1                                           /* 操作成功                     */ 
#define Q_WRITE_FRONT_MODE  2                                           /* 操作成功                     */ 
 
/********************************************************************************************************* 
  定义数据队列的数据类型 
*********************************************************************************************************/ 
#ifndef __QUEUE_DATA_TYPE 
#define __QUEUE_DATA_TYPE     INT8U 
#endif 
 
/********************************************************************************************************* 
  环形缓冲区定义数据队列结构体 
*********************************************************************************************************/ 

typedef struct { 
    __QUEUE_DATA_TYPE      *pOut;                                       /*  指向数据输出位置            */ 
    __QUEUE_DATA_TYPE      *pIn;                                        /*  指向数据输入位置            */ 
    __QUEUE_DATA_TYPE      *pEnd;                                       /*  指向Buf的结束位置           */ 
    unsigned short          usNData;                                    /*  队列中数据个数              */ 
    unsigned short          usSize;                                     /*  队列中允许存储的数据个数    */ 
    
    void                  (*pfQueueLock)(void);                         /*  队列保护入口函数指针        */
    void                  (*pfQueueUnlock)(void);                       /*  队列保护出口函数指针        */
            
    __QUEUE_DATA_TYPE       pvBuf[1];                                   /*  存储数据的空间              */
} __DATA_QUEUE, *__PDATA_QUEUE; 
 
 
 
/*********************************************************************************************************  
** Function name:           QueueCreate  
** Descriptions:            初始化数据队列  
** Input parameters:        pvQBuf          为队列分配的存储空间地址  
**                          ulSize          为队列分配的存储空间大小（字节）  
**                          pfEnterCritical 为队列读空时处理程序  
**                          pfExitCritical  为队列写满时处理程序  
** Output parameters:       NONE  
** Returned value:          QUEUE_PARA_ERR  参数错误  
**                          QUEUE_OK        成功
**                          其他            参考queue.h文件  
*********************************************************************************************************/    

extern INT8S QueueCreate ( void *pvQBuf, 
                        INT32U ulSize,
                        void (*pfEnterCritical)(void),
                        void (*pfExitCritical)(void));   
   
   
/*********************************************************************************************************  
** Function name:           QueueRead  
** Descriptions:            获取队列中的数据  
** Input parameters:        pvQBuf          指向队列的指针 
**                          pucRet          存储返回的消息的地址   
** Output parameters:       NONE  
** Returned value:          QUEUE_PARA_ERR  参数错误  
**                          QUEUE_OK        收到消息  
**                          QUEUE_EMPTY     队列空  
**                          其他            参考queue.h文件 
*********************************************************************************************************/  
extern INT8S QueueRead (void *pvQBuf, __QUEUE_DATA_TYPE *pucRet);  

   
/*********************************************************************************************************  
** Function name:           QueueWrite  
** Descriptions:            FIFO方式发送数据  
** Input parameters:        pvQBuf          指向队列的指针  
**                          ucData          发送的数据  
** Output parameters:       NONE  
** Returned value:          QUEUE_PARA_ERR  参数错误  
**                          QUEUE_FULL      队列满  
**                          QUEUE_OK        发送成功
**                          其他            参考queue.h文件   
*********************************************************************************************************/    
extern INT8S QueueWrite (void *pvQBuf, __QUEUE_DATA_TYPE ucData);
 
   
/*********************************************************************************************************  
** Function name:           QueueWriteFront  
** Descriptions:            LIFO方式发送数据  
** Input parameters:        pvQBuf          指向队列的指针  
**                          ucData          发送的数据  
** Output parameters:       NONE  
** Returned value:          QUEUE_PARA_ERR  参数错误  
**                          QUEUE_FULL      队列满  
**                          QUEUE_OK        发送成功  
**                          其他            参考queue.h文件 
*********************************************************************************************************/   
extern INT8S QueueWriteFront (void *pvQBuf, __QUEUE_DATA_TYPE ucData);   
      
   
/*********************************************************************************************************  
** Function name:           QueueDataSizeGet  
** Descriptions:            取得队列中数据数  
** Input parameters:        pvQBuf          指向队列的指针  
** Output parameters:       NONE  
** Returned value:          QUEUE_PARA_ERR  参数错误          
**                          >0              队列包含数据数  
*********************************************************************************************************/   
extern INT32S QueueDataSizeGet (void *pvQBuf);  
   
  
   
/*********************************************************************************************************  
** Function name:           QueueSize  
** Descriptions:            取得队列总容量  
** Input parameters:        pvQBuf          指向队列的指针  
** Output parameters:       NONE  
** Returned value:          QUEUE_PARA_ERR  参数错误          
**                          >0              队列总容量  
*********************************************************************************************************/  
extern INT32S QueueSize(void *pvQBuf);

/*********************************************************************************************************  
** Function name:           OSQFlush  
** Descriptions:            清空队列  
** Input parameters:        pvQBuf          指向队列的指针  
** Output parameters:       NONE  
** Returned value:          QUEUE_PARA_ERR  参数错误   
**                          QUEUE_OK        操作成功  
**                          其他            参考queue.h文件  
*********************************************************************************************************/       
extern INT8S QueueFlush (void *pvQBuf);  

extern INT32S QueueSpaceSizeGet (void *pvQBuf);


#ifdef __cplusplus
}
#endif   
 
#endif                                                                  /* __QUEUE_H                    */ 
/********************************************************************************************************* 
   END FILE 
*********************************************************************************************************/ 
