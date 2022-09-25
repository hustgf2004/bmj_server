/****************************************Copyright (c)****************************************************
**                          Beijing Hengfengli Technology CO.,LTD.
**                                      
**                                 http://www.hengfengli.com/
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tp.h
** Latest modified Date:    2014-08-25
** Latest Version:          1.0
** Descriptions:            AnyPort协议栈头文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:              超人力霸王
** Created date:            2014-08-25
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
#ifndef __TP_H
#define __TP_H

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
  版本定义
*********************************************************************************************************/
#define     TP_VER           0x14082510                                 /*  V1.0                        */

/*********************************************************************************************************
  返回值定义
*********************************************************************************************************/
//#define     TP_OK                   0                                   /*  操作成功                    */
//#define     TP_NOT_OK               1                                   /*  操作失败                    */
//#define     TP_PARA_ERR             2                                   /*  参数错误                    */
//#define     TP_NO_FIND_DEVICE       3                                   /*  没有发现设备                */
//#define     TP_NODE_FULL            4                                   /*  节点已满                    */
//#define     TP_NO_FIND_FUNCTION     5                                   /*  没有发现指定函数            */
//#define     TP_DRIVER_FULL          6                                   /*  网络驱动满                  */
//#define     TP_DRIVER_EXIST         7                                   /*  网络驱动已安装              */
//#define     TP_FIND_NO_DRIVER       8                                   /*  没有发现网络驱动            */
//#define     TP_NO_PORT              9                                   /*  不存在的端口                */
//#define     TP_NO_MEMORY            10                                  /*  内存不足                    */
//#define     TP_TIME_OUT             11                                  /*  超时                        */
//#define     TP_PACKET_ERR           12                                  /*  帧错误                      */

/*********************************************************************************************************
  特殊通道号定义
*********************************************************************************************************/
#define     TP_DEFAULT_CHNL         0xff                                /*  默认通道号                  */

/*********************************************************************************************************
  端口操作函数
*********************************************************************************************************/
struct tp_port_info;
struct tp_port_func {
    /*
     *  构造函数
     */
    INT32S    (*pfuncCreate)(const struct tp_port_info *ptpiThis);

    /*
     *  析构函数
     */
    INT32S    (*pfuncDel)(const struct tp_port_info *ptpiThis);

    /*
     *  读端口数据
     */
    INT32S    (*pfuncRead)(const struct tp_port_info *ptpiThis,
                                 INT8U                ucChnl,
                                 INT16U               usLen,
                                 void                *pvData);

    /*
     *  写端口数据
     */
    INT32S    (*pfuncWrite)(const struct tp_port_info *ptpiThis,
                                  INT8U                ucChnl,
                                  INT16U               usLen,
                                  void                *pvData);

    /*
     *  写读端口数据
     */
    
};
typedef  struct tp_port_func      TP_PORT_FUNC;

/*********************************************************************************************************
  端口信息
*********************************************************************************************************/
struct tp_port_info {
    TP_PORT_FUNC *pdfFunc;                                              /*  函数列表                    */ 
    INT32U        ulAddrStart;                                          /*  开始端口地址                */
    INT8U         ucRemoteEn;                                           /*  远程访问许可                */
};

typedef  struct tp_port_info      TP_PORT_INFO;

/*********************************************************************************************************
  通讯驱动函数
*********************************************************************************************************/
struct tp_drv_info_base;
struct tp_drv_func_base {
   
    /*
     *  构造函数
     */
    INT32S    (*pfuncCreate)(struct tp_drv_info_base *ptpiThis);

    /*
     *  析构函数
     */
    INT32S    (*pfuncDel)(struct tp_drv_info_base *ptpiThis);
    
    /*
     *  写端口数据
     */
    INT32S    (*pfuncWrite)(struct tp_drv_info_base    *ptpiThis,
                                    INT8U               ucDst,
                                    INT8U               ucSrc,
                                    INT8U               ucAddr,
                                    INT16U              usLen,
                                    void               *pvData,
                                    INT8U               ucAck,
                                    INT8U               ucFType);
    /*
     *  读端口数据
     */
    INT32S    (*pfuncRead)(struct tp_drv_info_base     *ptpiThis,
                                    INT8U               ucDst,
                                    INT8U               ucSrc,
                                    INT8U               ucAddr,
                                    INT16U              usLen,
                                    void               *pvData,
                                    INT8U               ucFType);
                                      
};

typedef  struct tp_drv_func_base      TP_DRV_FUNC_BASE;
 
/*********************************************************************************************************
  通讯驱动信息
*********************************************************************************************************/
struct tp_drv_info_base {
    TP_DRV_FUNC_BASE    *pdfFunc;                                       /*  驱动函数信息                */    
  
    INT32U               uiChnl;                                        /*  驱动通道号                  */
    INT32U               uiReceiveDelay;                                /*  等待接收延迟时间            */
    INT32U              *pulHostTable;                                  /*  主控设备转换码表            */
    INT32U              *pulSlaveTable;                                 /*  被控设备转换码表            */
    
};

typedef  struct tp_drv_info_base      TP_DRV_INFO_BASE;

/*********************************************************************************************************
** Function name:           tpRead
** Descriptions:            端口读
** input parameters:        uiChnl          驱动通道号
**                          ucDstAddr       目的地址
**                          ucAddr          端口地址
**                          usLen           数据数目
**                          pvData          数据保存地址
**                          
** output parameters:       pvData          读到的数据
** Returned value:          >=0             完成的数据数目
**                          负数            错误,绝对值参考tp.h         
*********************************************************************************************************/
extern INT32S tpRead(INT32U uiChnl, INT8U ucAddr, INT16U usLen, void *pvData);
extern INT32S tpReadBus(INT32U uiChnl, INT8U ucDst, INT8U ucSrc, INT8U ucAddr, INT16U usLen, void *pvData);

/*********************************************************************************************************
** Function name:           tpWrite
** Descriptions:            端口写
** input parameters:        uiChnl          驱动通道号
**                          ucDstAddr       目的地址
**                          ucAddr          端口地址
**                          usLen           数据数目
**                          pvData          数据保存地址
**                          ucAck           0--无回复 1--有回复
** output parameters:       none
** Returned value:          >=0             完成的数据数目
**                          负数            错误,绝对值参考tp.h         
*********************************************************************************************************/
extern INT32S tpWrite(INT32U uiChnl, INT8U ucAddr, INT16U usLen, void *pvData, INT8U ucAck);
extern INT32S tpWriteBus(INT32U uiChnl, INT8U ucDst, INT8U ucSrc, INT8U ucAddr, INT16U usLen, void *pvData, INT8U ucAck);
/*********************************************************************************************************
** Function name:           tpWriteRead
** Descriptions:            端口写读
** input parameters:        uiChnl          驱动通道号
**                          ucAddr          端口地址
**                          usLen           数据数目
**                          pvData          数据保存地址
**                          ucAck           0--无回复 1--有回复
** output parameters:       none
** Returned value:          >=0             完成的数据数目
**                          负数            错误,绝对值参考tp.h          
*********************************************************************************************************/

/*********************************************************************************************************
  以下为内部使用的函数与结构体定义，用户无需关心
*********************************************************************************************************/

/*********************************************************************************************************
  单向链表
*********************************************************************************************************/
struct __tp_list {
    struct __tp_list     *plNext;                                       /*  下一个端口                  */
    const TP_PORT_INFO   *ptpiData;                                     /*  端口数据                    */
};

typedef  struct __tp_list           __TP_LIST;



/*********************************************************************************************************
  宏定义
*********************************************************************************************************/
#define TP_BUS_FLAG_CHAR    0x00                                        /*  总线协议标识                */
#define TP_NBR_FLAG_CHAR    0x02                                        /*  点对点协议标识              */

#define __TP_REMOTE_FUNC   \
    {                      \
        tpDrvCreate,      \
        tpDrvDel,         \
        tpDrvWrite,       \
        tpDrvRead         \
    }

#define __TP_REMOTE_FUNC_EX \
    {                      \
        tpDrvCreate,      \
        tpDrvDel,         \
        tpDrvWriteEx,     \
        tpDrvReadEx       \
    }    
/*********************************************************************************************************
  帧代码定义
*********************************************************************************************************/
#define TP_READ_FLG       0x00                                           /*  端口读                     */
#define TP_WRITE_FLG      0x01                                           /*  端口写                     */
#define TP_NREAD_FLG      0x02                                           /*  保留                       */
#define TP_NWRITE_FLG     0x03                                           /*  端口写,不需要回复          */

#define TP_RREAD_FLG      0x04                                           /*  端口读成功回复             */
#define TP_RWRITE_FLG     0x05                                           /*  端口写成功回复             */
#define TP_RFREAD_FLG     0x06                                           /*  端口读失败回复             */
#define TP_RFWRITE_FLG    0x07                                           /*  端口写失败回复             */

/*********************************************************************************************************
  字节顺序变换
*********************************************************************************************************/
#ifndef tp_ntohl
#define tp_ntohl(x) x = (INT32U)(((INT8U *)&(x))[0] << 24 | \
                                 ((INT8U *)&(x))[1] << 16 | \
                                 ((INT8U *)&(x))[2] << 8  | \
                                 ((INT8U *)&(x))[3] << 0)
#endif                                                                  /*  tp_ntohl                    */

#ifndef tp_htonl
#define tp_htonl(x) x = (INT32U)(((INT8U *)&(x))[0] << 24 | \
                                 ((INT8U *)&(x))[1] << 16 | \
                                 ((INT8U *)&(x))[2] << 8  | \
                                 ((INT8U *)&(x))[3] << 0)
#endif                                                                  /*  tp_htonl                    */

#ifndef tp_ntohs
#define tp_ntohs(x) x = (INT16U)(((INT8U *)&(x))[0] << 8  | \
                                 ((INT8U *)&(x))[1] << 0)
#endif                                                                  /*  tp_ntohs                    */

#ifndef tp_htons
#define tp_htons(x) x = (INT16U)(((INT8U *)&(x))[0] << 8  | \
                                 ((INT8U *)&(x))[1] << 0)
#endif                                                                  /*  tp_htons                    */

/*********************************************************************************************************
  默认协议驱动信息
*********************************************************************************************************/
struct tp_drv_info;
struct tp_packet_head;
struct tp_drv_func {                                                 /*  驱动函数列表                */
    TP_DRV_FUNC_BASE dfFunc;                                         /*  驱动基础函数列表            */

    /*
     *  构造函数
     */
    INT32S    (*pfuncCreate)(struct tp_drv_info *ptpiThis);

    /*
     *  析构函数
     */
    INT32S    (*pfuncDel)(struct tp_drv_info *ptpiThis);

    /*
     *  发送数据包
     */
    INT32S    (*pfuncSend)(struct tp_drv_info  *ptpiThis,                                  
                           struct tp_packet_head  *pData);
                          
};

typedef  struct tp_drv_func     TP_DRV_FUNC;


struct tp_drv_info {
    TP_DRV_INFO_BASE    dibInfo;                                        /*  驱动信息                    */
    INT8U               ucId;                                           /*  设备ID号                    */
};

typedef  struct tp_drv_info     TP_DRV_INFO;
/*********************************************************************************************************

*********************************************************************************************************/


/*********************************************************************************************************
  协议包结构
*********************************************************************************************************/
#if 0

typedef union __headbits
{
    unsigned int	uiWord;
    struct 
    {
        unsigned int uiFtype    :2;                                     /*  帧类型                      */
        union {
            struct {
        unsigned int uiSegNum   :14;                                    /*  分帧计数                    */
        unsigned int uiSegPolo  :2;                                     /*  分帧标志                    */  
            } NbrHeadBits;
            struct {
                unsigned int uiDstAddr  :8;
                unsigned int uiSrcAddr  :8;
            } BusHeadBits;
        }SegBits;
        unsigned int uiPortAddr :8;                                     /*  功能端口地址                */
        unsigned int uiRF       :3;                                     /*  运行标志                    */
        unsigned int uiRsv      :3;    
    }Bits;
}__HEADBITS, *__PHEADBITS;
#endif

/*********************************************************************************************************
  总线帧ID结构
*********************************************************************************************************/
typedef union __headbits
{
    unsigned int	uiWord;
    struct {
        unsigned int uiFtype    :2;                                     /*  帧类型                      */        
        unsigned int uiSegNum   :14;                                    /*  分帧计数                    */
        unsigned int uiSegPolo  :2;                                     /*  分帧标志                    */  
        unsigned int uiPortAddr :8;                                     /*  功能端口地址                */
        unsigned int uiRF       :3;                                     /*  运行标志                    */
        unsigned int uiRsv      :3;    
    } Bits;
    struct {
        unsigned int uiFtype    :2;                                     /*  帧类型                      */
        unsigned int uiDstAddr  :8;                                     /*  目的地址                    */
        unsigned int uiSrcAddr  :8;                                     /*  源地址                      */
        unsigned int uiPortAddr :8;                                     /*  功能端口地址                */
        unsigned int uiRF       :3;                                     /*  运行标志                    */
        unsigned int uiRsv      :3;    
    } BusHeadBits;
}__HEADBITS, *__PHEADBITS;


/*********************************************************************************************************
  总线CAN帧协议分帧标识符结构
*********************************************************************************************************/
typedef union __seg_flag
{
    unsigned short usSegFlag;
    struct
    {
        unsigned int uiSegNum   :14;                                    /*  分帧计数                    */
        unsigned int uiSegPolo  :2;                                     /*  分帧标志                    */    
    } Bits;

}__SEG_FLAG, *__PSEG_FLAG;
struct tp_packet_head {                                                 /*  帧头结构                    */
  __HEADBITS        tpHeadBits;                                         /*  数据帧头                    */
    INT8U           ucDatLen;                                           /*  帧数据长度                  */
};


typedef  struct tp_packet_head      TP_PACKET_HEAD;


struct tp_packet {                                                      /*  普通帧结构                  */
    TP_PACKET_HEAD    tpHead;                                           /*  帧头                        */
    INT16U            usDatLen;                                         /*  有效数据长度                */
    INT8U            *pucDat;                                           /*  数据缓冲指针                */
    INT8U             ucChnl;                                           /*  驱动设备号                  */
};

typedef  struct tp_packet    TP_PACKET;

/*********************************************************************************************************
  tp数据结构
*********************************************************************************************************/
struct tp_drv {
    TP_DRV_INFO        *ptdi;
    INT32U              uiTimeOut;
    unsigned long       pSemSend;
    unsigned long       pSemRcv;
    TP_PACKET           tp;
    INT8U              *pucRtn;                                         /*  写应答携带数据              */
    INT32U              uiErr;
    INT32U              uiFlg;
};
typedef struct tp_drv TP_DRV, *PTP_DRV;



/*********************************************************************************************************
** Function name:           tpInit
** Descriptions:            Tp初始化
** input parameters:        none
** output parameters:       none
** Returned value:          SYS_OK: 成功
**                          负数:   错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S tpInit(void);

/*********************************************************************************************************
** Function name:           tpTick
** Descriptions:            时钟节拍处理
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void tpTick(void);

/*********************************************************************************************************
** Function name:           tpDevicePortInit
** Descriptions:            端口组初始化
** input parameters:        ptpListSpace:       端口组属性
**                          uiMaxDevices:
** output parameters:       none
** Returned value:          TP_OK:              成功
**                          负数:               错误,绝对值参考tp.h
*********************************************************************************************************/
extern INT32S tpDevicePortInit(__TP_LIST *ptpListSpace, unsigned int uiMaxDevices);    

/*********************************************************************************************************
** Function name:           tpRemoteInit
** Descriptions:            网络驱动管理初始化
** input parameters:        ppdiDriversSpace:   保存网络驱动信息的指针的存储空间
**                          uiMaxDrivers:       最大网络驱动数目
**                          pRsv:               保留参数
** output parameters:       none
** Returned value:          SYS_OK:             成功
**                          负数:               错误,绝对值参考sys_if.h
*********************************************************************************************************/
INT32S tpRemoteDriversInit(TP_DRV_INFO_BASE   **ppdibDriversSpace,
                          unsigned int          uiMaxDrivers,
                          void                 *pRsv);

/*********************************************************************************************************
** Function name:           tpDrivCreate
** Descriptions:            网络驱动程序初始化
** input parameters:        ptdibThis:          网络标识
** output parameters:       none
** Returned value:          SYS_OK:             成功
**                          负数:               错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S tpDrvCreate (TP_DRV_INFO_BASE *ptdibThis);

/*********************************************************************************************************
** Function name:           tpDrivDel
** Descriptions:            删除网络驱动程序
** input parameters:        ptdibThis:          网络标识
** output parameters:       none
** Returned value:          TP_OK:              成功
**                          负数:               错误,绝对值参考tp.h
*********************************************************************************************************/
extern INT32S tpDrvDel (TP_DRV_INFO_BASE *ptdibThis);

/*********************************************************************************************************
** Function name:           tpDrivWrite
** Descriptions:            网络驱动写操作
** input parameters:        ptdibThis:          网络标识
**                          ucDst:              目的地址
**                          ucSrc:              源地址
**                          ucAddr:             端口地址
**                          usLen:              数据数目
**                          pvData:             数据保存地址
** output parameters:       none
** Returned value:          >=0:                完成的数据数目
**                          负数:               错误,绝对值参考tp.h
*********************************************************************************************************/
extern INT32S tpDrvWrite(TP_DRV_INFO_BASE      *ptdibThis,
                          INT8U                 ucAddr,
                          INT16U                usLen,
                          void                 *pvData,
                          INT8U                 ucAck); 
extern INT32S tpDrvWriteEx(TP_DRV_INFO_BASE      *ptdibThis,
                          INT8U                 ucDst,
                          INT8U                 ucSrc,
                          INT8U                 ucAddr,
                          INT16U                usLen,
                          void                 *pvData,
                          INT8U                 ucAck,
                          INT8U                 ucFType); 
/*********************************************************************************************************
** Function name:           tpDrvRead
** Descriptions:            网络驱动读操作
** input parameters:        ptdibThis:          网络标识
**                          ucDst:              目的地址
**                          ucSrc:              源地址
**                          ucAddr:             端口地址
**                          usLen:              数据数目
** output parameters:       pvData:             数据
** Returned value:          >=0:                完成的数据数目
**                          负数:               错误,绝对值参考sys_if.h
*********************************************************************************************************/
extern INT32S tpDrvRead (TP_DRV_INFO_BASE      *ptdibThis,
                         INT8U                  ucAddr,
                         INT16U                 usLen,
                         void                  *pvDat);

extern INT32S tpDrvReadEx(TP_DRV_INFO_BASE      *ptdibThis,
                         INT8U                  ucDst,
                         INT8U                  ucSrc,
                         INT8U                  ucAddr,
                         INT16U                 usLen,
                         void                  *pvDat,
                         INT8U                  ucFType);
/*********************************************************************************************************
** Function name:           tpReceive
** Descriptions:            接收帧处理
** input parameters:        ptdibThis:          网络驱动标识
**                          ptphPacket:         数据帧
** output parameters:       none
** Returned value:          TP_OK:              成功
**                          负数:               错误,绝对值参考tp.h
*********************************************************************************************************/
extern INT32S tpReceive(TP_DRV_INFO_BASE *ptdibThis, TP_PACKET_HEAD *ptphPacket);

/*********************************************************************************************************
** Function name:           tpDrvsInit
** Descriptions:            基于AnyPort协议初始化驱动
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/

extern TP_DRV_INFO  *const __GptdiDrvs[TP_MAX_DRIVER];  
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __TP_H                      */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
