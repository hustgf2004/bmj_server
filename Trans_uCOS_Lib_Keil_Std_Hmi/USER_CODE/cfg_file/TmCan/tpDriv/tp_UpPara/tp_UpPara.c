/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               tp_UpPara.c
** Latest modified Date:    2014-08-25
** Latest Version:          1.0
** Descriptions:            端口驱动代码文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
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


/*********************************************************************************************************
** Function name:           sysUpgradeFlag
** Descriptions:            更新下载管理程序标志区成功运行写入0x5a，更新完毕写入0xa5
** input parameters:        pucBuf: 升级数据缓存基址
**                          uiLength：缓存大小(>=512B)
** output parameters:       none
** Returned value:          >=0:    编程起始编号
**                          负数:   失败
*********************************************************************************************************/


#include ".\tp_UpPara_cfg.h"

INT32S sysParaFlag(INT8U ucFlag)
{  
    
    INT32S  siErr;
    memset(__GucUpgradeBuf , 0xFF, __UPGRADE_PAGE_SIZE);
    __GucUpgradeBuf[0] = ucFlag;
    sysSectorPrepare (16, 16);                                          /* 扇区准备						*/
    sysSectorErase (16, 16);	                                        /* 擦除扇区						*/
    sysSectorPrepare (16, 16);                                          /* 扇区准备						*/						
    sysRamToFlash(__PARA_FLAG_ADDR, (INT32U)__GucUpgradeBuf, 512); 
    siErr = sysDataCompare(__PARA_FLAG_ADDR,(INT32U)__GucUpgradeBuf, 512);
    return (-siErr);
}
    /*
     *  外部共享使用变量
     */
   
    /*
     *  内部使用变量
     */
/*********************************************************************************************************
  函数声明
*********************************************************************************************************/
static INT32S __tpCreate (const TM_PORT_INFO *ptpiThis);
static INT32S __tpDel (const TM_PORT_INFO *ptpiThis);
static INT32S __tpRead(const TM_PORT_INFO *ptpiThis, INT8U ucChanle, INT16U usLen, void *pvData);
static INT32S __tpWrite (const TM_PORT_INFO *ptpiThis, INT8U ucChanle, INT16U usLen, void *pvData);

/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/
const TM_PORT_FUNC GtpfUpPara = {
    __tpCreate,
    __tpDel,
    __tpRead,
    __tpWrite
};


BOOLEAN   __GbParaFlag;


/*********************************************************************************************************
** Function name:           __tpCreate
** Descriptions:            创建端口
** input parameters:        ptpiThis: 端口信息
** output parameters:       none
** Returned value:          TM_OK :  成功
**                          负数:    错误,绝对值参考tmcan.h
** Created by:              
** Created Date:            2014-08-25
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT32S __tpCreate (const TM_PORT_INFO *ptpiThis)
{
    TP_UPPARA_INFO *pttiPortCase;                                       /*  设备信息                    */
    
    pttiPortCase = (TP_UPPARA_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase;
    /*
     *  具体的初始化代码
     */

    __GbParaFlag = FALSE;

        
    return TM_OK;
}

/*********************************************************************************************************
** Function name:           __tpDel
** Descriptions:            删除端口
** input parameters:        ptpiThis:  端口信息
** output parameters:       none
** Returned value:          TM_OK :  成功
**                          负数:    错误,绝对值参考tmcan.h
** Created by:              
** Created Date:            2014-08-25
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
static INT32S __tpDel (const TM_PORT_INFO *ptpiThis)
{
    TP_UPPARA_INFO *pttiPortCase;                                       /*  设备信息                    */
    
    pttiPortCase = (TP_UPPARA_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase;
    /*
     *  具体的卸载代码
     */
    __GbParaFlag = FALSE;
    return TM_OK;    
}

/*********************************************************************************************************
** Function name:           __tpRead
** Descriptions:            读端口。
** input parameters:        ptpiThis: 端口信息
**                          usLen:    写数据个数
**                          pvData:   数据缓冲区
** output parameters:       none
** Returned value:          >=0 :     数据数目
** Created by:              
** Created Date:            2014-08-25
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

static INT32S __tpRead (const TM_PORT_INFO *ptpiThis, INT8U ucChanle, INT16U usLen, void *pvData)
{

    TP_UPPARA_INFO *pttiPortCase;                                       /*  设备信息                    */
    
//    INT32U  __PARAM_ADDR = __PARAM_ADDR_EX0;
    pttiPortCase = (TP_UPPARA_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase; 
    
    /*
     *  实际的写代码
     */        

     
    return usLen;
}
/*********************************************************************************************************
** Function name:           __tpWrite
** Descriptions:            写端口。
** input parameters:        ptpiThis: 端口信息
**                          usLen:    写数据个数
**                          pvData:   数据缓冲区
** output parameters:       none
** Returned value:          >=0 :     数据数目
** Created by:              
** Created Date:            2014-08-25
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

static INT32S __tpWrite (const TM_PORT_INFO *ptpiThis, INT8U ucChanle, INT16U usLen, void *pvData)
{
    TP_UPPARA_INFO   *pttiPortCase;                                     /*  设备信息                    */
    INT16U              uiTmp;
    SERVICE_PARA_S *pstPara = NULL;
    pttiPortCase = (TP_UPPARA_INFO *)ptpiThis;
    pttiPortCase = pttiPortCase; 
    /*
     *  吸参数通道错误
     */
    if (((__GucTmDrivChn[(__PORT_DEF_LEFT >> 3) & 0x07][__PORT_DEF_LEFT & 0x07] != ucChanle) && 
        (__GucTmDrivChn[(__PORT_DEF_RIGHT >> 3) & 0x07][__PORT_DEF_RIGHT & 0x07] != ucChanle))||
        (__GuiChanle != ucChanle)) {
        return 0;
    }
    /*
     *  长度判断
     */
    if ((usLen > 0x400) || (usLen < 256)) {                                                
        return 0;
    } 
    /*
     *  架号计算
     */
    pstPara = (SERVICE_PARA_S*)pvData;
    if(pstPara->bAddrDir & 0x01) {                                  /*  左边增向                    */
        if (__GucTmDrivChn[0][__PORT_DEF_LEFT] == ucChanle) {
            pstPara->u8ShldNo -= 1;   
        } else {
            pstPara->u8ShldNo += 1;
        }    
    } else {                                                            /*  右边增向                    */
        if (__GucTmDrivChn[0][__PORT_DEF_LEFT] == ucChanle) {
            pstPara->u8ShldNo += 1;    
        } else {
            pstPara->u8ShldNo -= 1;   
        }     
    }

    if (1 == write_eeprom(0x00, pvData, usLen)) {
        if (0xBB != ioInportByte(__PARA_FLAG_ADDR)) {                   /*  参数写入成功                */
            OSSchedLock();
            sysIrqDisable();
            sysParaFlag(0xBB);
            sysIrqEnable();
            OSSchedUnlock();
        }
        GUI_Printf(__GucXPoint, __GucYPoint, 1, "参数写入成功！  ");
        __GbParaFlag = TRUE;
        return usLen;
    } else {                                                            /*  参数写入失败                */
        GUI_Printf(__GucXPoint, __GucYPoint, 1, "参数写入失败！  ");
        __GbParaFlag = FALSE;
        return usLen;
    } 
}

/*********************************************************************************************************
  DEL FILE
*********************************************************************************************************/
