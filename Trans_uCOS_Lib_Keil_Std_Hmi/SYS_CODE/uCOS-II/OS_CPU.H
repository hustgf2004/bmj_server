/****************************************Copyright (c)****************************************************
**                            
**
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               os_cpu.h
** Latest modified Date:    2012-12-31
** Latest Version:          1.0
** Descriptions:            ��COS-II��ARM7�ϵ���ֲ����CPU���ò��֣���ADS1.2����
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2012-12-31
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
#ifndef __OS_CPU_H
#define __OS_CPU_H
#ifdef  __cplusplus
extern "C" {
#endif
/*********************************************************************************************************
  ������������޹ص���������
*********************************************************************************************************/
typedef unsigned char  BOOLEAN;                                         /*  ��������                    */
typedef unsigned char  INT8U;                                           /*  �޷���8λ���ͱ���           */
typedef signed   char  INT8S;                                           /*  �з���8λ���ͱ���           */
typedef unsigned short INT16U;                                          /*  �޷���16λ���ͱ���          */
typedef signed   short INT16S;                                          /*  �з���16λ���ͱ���          */
typedef unsigned int   INT32U;                                          /*  �޷���32λ���ͱ���          */
typedef signed   int   INT32S;                                          /*  �з���32λ���ͱ���          */
typedef float          FP32;                                            /*  �����ȸ�������32λ���ȣ�    */
typedef double         FP64;                                            /*  ˫���ȸ�������64λ���ȣ�    */

typedef INT32U         OS_STK;                                          /*  ��ջ��32λ����              */

/*********************************************************************************************************
  �����Ǽ���UC/OS V1.XX���������ͣ���uC/OS-IIû��ʹ��
*********************************************************************************************************/
#define BYTE           INT8S
#define UBYTE          INT8U
#define WORD           INT16S
#define UWORD          INT16U
#define LONG           INT32S
#define ULONG          INT32U


/*********************************************************************************************************
  ��ARM7��ϵ�ṹ��ص�һЩ����
*********************************************************************************************************/
#define OS_CRITICAL_METHOD      2                                       /*  ѡ�񿪡����жϵķ�ʽ        */
#define OS_STK_GROWTH           1                                       /*  ��ջ�Ǵ������³���          */

/*********************************************************************************************************
** Function name:           OsSwiHandle1
** Descriptions:            SWI��������
** input parameters:        iHandle: �������ֹ���
**                          ����:    ���ݹ��ܾ���
** output parameters:       ���ݹ��ܾ���
** Returned value:          ���ݹ��ܾ���
*********************************************************************************************************/
__swi(0x00) void OsSwiHandle1(int iHandle);
__swi(0x01) void *OsSwiHandle2(int iHandle, int iIndex);

/*********************************************************************************************************
** Function name:           OS_TASK_SW
** Descriptions:            ���������л�����
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void OS_TASK_SW (void)
{
	OsSwiHandle1(0);
}

/*********************************************************************************************************
** Function name:           OSStartHighRdy
** Descriptions:            �������ȼ���ߵ�����
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void OSStartHighRdy (void)
{
	OsSwiHandle1(1);
}

/*********************************************************************************************************
** Function name:           OS_ENTER_CRITICAL
** Descriptions:            ���ж�
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void OS_ENTER_CRITICAL (void)
{
	OsSwiHandle1(2);
}

__inline void IrqDisable(void)
{
    OsSwiHandle1(2);
}

/*********************************************************************************************************
** Function name:           OS_EXIT_CRITICAL
** Descriptions:            ���ж� 
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void OS_EXIT_CRITICAL (void)
{
	OsSwiHandle1(3);
}
__inline void IrqEnable(void)
{
    OsSwiHandle1(3);
}
/*********************************************************************************************************
** Function name:           ChangeToSYSMode
** Descriptions:            �����л���ϵͳģʽ 
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void ChangeToSYSMode (void)
{
	OsSwiHandle1(4);
}

/*********************************************************************************************************
** Function name:           ChangeToUSRMode
** Descriptions:            �����л����û�ģʽ 
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void ChangeToUSRMode (void)
{
	OsSwiHandle1(5);
}

/*********************************************************************************************************
** Function name:           OSISRBegin
** Descriptions:            �жϿ�ʼ����
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void OSISRBegin (void)
{
	OsSwiHandle1(6);
}

/*********************************************************************************************************
** Function name:           OSISRNeedSwap
** Descriptions:            �ж��ж��Ƿ���Ҫ�л� 
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void OSISRNeedSwap (void)
{
	OsSwiHandle1(7);
}

/*********************************************************************************************************
** Function name:           ENTER_FIQ
** Descriptions:            �ؿ��� �ж�
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void ENTER_FIQ (void)
{
	OsSwiHandle1(8);
}

__inline void FiqDisable(void)
{
    OsSwiHandle1(8);
}

/*********************************************************************************************************
** Function name:           EXIT_FIQ
** Descriptions:            ���ж� 
** input parameters:        none
**                          
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__inline void EXIT_FIQ (void)
{
	OsSwiHandle1(9);
}
__inline void FiqEnable(void)
{
    OsSwiHandle1(9);
}

#ifdef __cplusplus
    }
#endif
#endif                                                                  /*  __OS_CPU_H                  */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/