/****************************************Copyright (c)**************************************************
**                               北京天地玛珂电液控制系统有限公司
**                               自动化部      
**
**                                 http://www.tdmacro.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: Modbus_TCP_Slave_data.c
**创   建   人: 徐伟林
**最后修改日期: 2010年5月19日
**描        述: 基于Modbus-TCP协议的服务器Slave端接口函数
**              
**              
**              
**             
**              
**              
**              
**             
**--------------当前版本信息----------------------------------------------------------------------------
** 创建人: 徐伟林
** 版  本: v1.0
** 日　期: 2010年5月19日
** 描　述: 原始版本
**
**--------------历史版本信息------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
** 描　述: 
**
**------------------------------------------------------------------------------------------------------
**--------------修改记录------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
** 描　述: 
**			
** 涉及函数:
**			
**			
**			
**
**------------------------------------------------------------------------------------------------------



********************************************************************************************************/ 

#include "main.h"

// 存储器的数据结构
typedef struct tag_MB_TCP_REG_TBL{
	
	uint16	m_nInputStatus;				// 开关量输入状态寄存器					
	uint16	m_nAdSample1;			    // 传感器采样寄存器1
	uint16	m_nAdSample2;				// 传感器采样寄存器2
	uint16	m_nFreqSample1;				// 脉冲频率采样寄存器1
	uint16	m_nFreqSample2;				// 脉冲频率采样寄存器2
	uint16	m_nReserved1;
	uint16	m_nReserved2;
	uint16	m_nReserved3;
	uint16	m_nReserved4;
	uint16	m_nReserved5;
	uint16	m_nReserved6;
	uint16	m_nReserved7;
	uint16	m_nReserved8;
	uint16	m_nReserved9;
	uint16	m_nReserved10;
	uint16	m_nReserved11;
	uint16	m_nReserved12;
	uint16	m_nReserved13;

	uint16	m_nReserved14;
	uint16	m_nReserved15;
	uint16	m_nReserved16;
	uint16	m_nReserved17;
	uint16	m_nReserved18;
	uint16	m_nReserved19;
	uint16	m_nReserved20;
	uint16	m_nReserved21;
	uint16	m_nReserved22;
	uint16	m_nReserved23;
	uint16	m_nReserved24;
	uint16	m_nReserved25;
	uint16	m_nReserved26;
	uint16	m_nReserved27;
	}MB_TCP_REG_TBL,*pMB_TCP_REG_TBL;
	
#if 1  
#if MODBUS_SERVER_INSIDE_EN
/*******************************************************************************************************
//
// 用户编写操作寄存器接口函数
//
********************************************************************************************************/

#if TCP_READ_DIS_INPUT_EN

static uint8 AppDiscTbl[30] = {0x8a,0x93,0x35};
static uint8 AppKey1;
static uint8 AppKey2;
static uint8 AppKey3;

#define KEY1   (1 << 6)
#define KEY2   (1 << 7)
#define KEY3   (1 << 8)
#define KEY4   (1 << 9)
#define KEY5   (1 << 10)
#define KEY6   (1 << 11)

#define KEY7   (1 << 25)
void keyIni(void)
{
    PINSEL0 &= ~(0xFFF << (6 * 2));
    
    IO0DIR  &= ~(KEY1 | KEY2 | KEY3 | KEY4 | KEY5 | KEY6 | KEY7); 
}

/*********************************************************************************************************
** 函数名称: MB_TCP_GetDiscrete
** 功能描述: 获取离散值函数，该函数由用户编写 
** 输　入: ch，设备ID  
**         DisInputsV，保存离散输入量值指针  
**         Address，线圈地址
**
** 输　出: 正常返回MB_NO_ERR,出错返回ILLEGAL_DATA_ADDR，或SLAVE_DEVICE_FAILURE。
** 全局变量: 
** 调用模块: 
** 作　者: 徐伟林
** 日　期: 2010年5月19日
**
**------------------------------------------------------------------------------------------------------
** 修改人:				
** 日  期:			
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
uint8 MB_TCP_GetDiscrete (uint8 ch, uint8 *DisInputsV,uint16 Address)
{
	uint8 err;
	uint8 ix;
	uint8 bit_nbr;
	err = MB_NO_ERR;
	if (Address < 200)//100 * sizeof(uint8))
	{
		ix =(uint8)( Address / 8);
		bit_nbr = (uint8)(Address % 8);
		*DisInputsV =(uint8)((AppDiscTbl[ix] & (1 << bit_nbr))?1:0); 
	}
	else
	{
		switch (Address)
		{
		 
		    case 200:
			    *DisInputsV = (uint8)((IO0PIN & KEY1) ? 1:0);
			    break;
		    case 201:
			    *DisInputsV = (uint8)((IO0PIN & KEY2) ? 1:0);
			    break;
		    case 202:
			    *DisInputsV = (uint8)((IO0PIN & KEY3) ? 1:0);
			    break;
		    case 203:
			    *DisInputsV = (uint8)((IO0PIN & KEY4) ? 1:0);
			    break;
			case 204:
				*DisInputsV = (uint8)(AppKey1?1:0);
				break;
			case 205:
				*DisInputsV = (uint8)(AppKey2?1:0);
				break;
			case 206:
				*DisInputsV = (uint8)(AppKey3?1:0);
				break;
			default:
				err = ILLEGAL_DATA_ADDR;
				break;
		}
	}
	return (err);
}
#endif

#if TCP_READ_COILS_EN

static uint8 AppCoilTbl[100]={0x15,0x52};
static uint8 AppStatus;

/*********************************************************************************************************
** 函数名称: MB_TCP_GetCoils
** 功能描述: 获取线圈值函数，该函数由用户编写 
** 输　入: ch，设备ID  
**         CoilVPtr，保存线圈值指针  
**         Address，线圈地址
**
** 输　出: 正常返回MB_NO_ERR,出错返回ILLEGAL_DATA_ADDR，或SLAVE_DEVICE_FAILURE。
** 全局变量: 
** 调用模块: 
** 作　者: 徐伟林
** 日　期: 2010年5月19日
**
**------------------------------------------------------------------------------------------------------
** 修改人:				
** 日  期:			
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
uint8 MB_TCP_GetCoils (uint8 ch, uint8 *CoilVPtr,uint16 Address)
{
	uint8 err;
	uint8 ix;
	uint8 bit_nbr;
	err = MB_NO_ERR;
	
	if (Address < 100 * 8 * sizeof(uint8))
	{
		ix = (uint8)(Address / 8);
		bit_nbr = (uint8)(Address % 8);
		*CoilVPtr =(uint8)((AppCoilTbl[ix] & (1 << bit_nbr))?1:0);
	}
	
	else
	{
		switch (Address) 
		{
			case 99:
				*CoilVPtr = 1;//AppStatus?1:0;
				break;
			case 100:
				*CoilVPtr = 1;//AppRunning?1:0;
				break;
			case 101:
				*CoilVPtr = 1;//AppLED?1:0;
				break;
		    case 102:
		    	*CoilVPtr = 1;//AppLED?1:0;
				break;
			case 103:
				*CoilVPtr = 1;//AppLED?1:0;
				break;
			case 104:
				*CoilVPtr = 1;//AppLED?1:0;
				break;
			case 105:
				*CoilVPtr = 1;//AppLED?1:0;
				break;
			case 106:
				*CoilVPtr = 1;//AppLED?1:0;
				break;		    
			default:
				err = ILLEGAL_DATA_ADDR;
				break;
		}
	}
	return (err);
}
#endif
#if TCP_WRITE_SING_COIL_EN||TCP_WRITE_MULT_COIL_EN
/*********************************************************************************************************
** 函数名称: MB_TCP_SetCoils
** 功能描述: 设置线圈值函数，该函数由用户编写 
** 输　入: ch，设备ID  
**         CoilVPtr，保存线圈值指针  
**         Address，线圈地址
**
** 输　出: 正常返回MB_NO_ERR,出错返回ILLEGAL_DATA_ADDR，或SLAVE_DEVICE_FAILURE。
** 全局变量: 
** 调用模块: 
** 作　者: 徐伟林
** 日　期: 2010年5月19日
**
**------------------------------------------------------------------------------------------------------
** 修改人:				
** 日  期:			
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
uint8 MB_TCP_SetCoil(uint8 ch, uint16 Address,uint8 CoilValue)
{
	uint8 err;
	uint8 ix;
	uint8 bit_nbr;
	err = MB_NO_ERR;
	if (Address < 100 * sizeof(uint8)) {
		ix = (uint8)(Address / 8);
		bit_nbr = (uint8)(Address % 8);
		if(CoilValue)
			AppCoilTbl[ix] = (uint8)((AppCoilTbl[ix] | (uint8)((1 << bit_nbr))));
		else
			AppCoilTbl[ix] = (uint8)(AppCoilTbl[ix] & (uint8)(~(1 << bit_nbr)));
	} else 	{
	    switch (Address) 
	    {
		    case 199:
			    AppStatus = (uint8)(CoilValue?1:0);
			    if ( AppStatus ) {
                    sysGpioClr(P1_27);
                } else {
                    sysGpioSet(P1_27); 						// 蜂鸣器熄灭
                }
			    break;
		    case 200:
			    AppStatus = (uint8)(CoilValue?1:0);
			    if ( AppStatus ) {
                     sysGpioClr(P1_27);
                } else {
                     sysGpioSet(P1_27); 						// 蜂鸣器熄灭
                }
			    break;
		    case 201:
			    AppStatus = (uint8)(CoilValue?1:0);
			    if ( AppStatus ) {
                    sysGpioClr(P1_27);
                } else {
                    sysGpioSet(P1_27); 						// 蜂鸣器熄灭
                }
			    break;
		    case 202:
			    AppStatus = (uint8)(CoilValue?1:0);
			    if ( AppStatus ) {
                     sysGpioClr(P1_27);
                } else {
                    sysGpioSet(P1_27); 						// 蜂鸣器熄灭
                }
			    break;
		    case 203:
			    AppStatus = (uint8)(CoilValue?1:0);
			    if ( AppStatus ) {
                     sysGpioClr(P1_27);
                } else {
                     sysGpioSet(P1_27); 						// 蜂鸣器熄灭
                }
			    break;
		    case 204:
			    AppStatus = (uint8)(CoilValue?1:0);
			    if ( AppStatus ) {
                     sysGpioClr(P1_27);
                } else {
                     sysGpioSet(P1_27); 						// 蜂鸣器熄灭
                }
			    break;
		    case 205:
			    AppStatus = (uint8)(CoilValue?1:0);
			    if ( AppStatus ) {
                     sysGpioClr(P1_27);
                } else {
                     sysGpioSet(P1_27); 						// 蜂鸣器熄灭
                }
			    break;
		    case 206:
			    AppStatus = (uint8)(CoilValue?1:0);
			    if ( AppStatus ) {
                     sysGpioClr(P1_27);
                } else {
                     sysGpioSet(P1_27); 						// 蜂鸣器熄灭
                }
			    break;
		    default:
			    err = ILLEGAL_DATA_ADDR;
			    break;
	    }
	}
	return (err);
}
#endif
#if TCP_READ_INPUT_REG_EN
#define END_INPUT_REG_ADDR 	150
static uint16 InputBuffer[END_INPUT_REG_ADDR] = {0x1234,0x5678,0x9abc};
static uint16 AppAD0;
static uint16 AppAD1;
static uint16 AppAD2;
/*********************************************************************************************************
** 函数名称:			MB_TCP_GetInputRegValue
**
** 功能描述:			读输入寄存器值函数，该函数由用户编写
**
** 输    入:		    ch，设备ID
**						*ValuePtr，保存输入寄存器值的指针
**						Address，寄存器地址
** 输    出:			正常返回MB_NO_ERR,出错返回ILLEGAL_DATA_ADDR，或SLAVE_DEVICE_FAILURE。
**         
** 作    者:			徐伟林
** 日    期:			2010年5月19日
**-------------------------------------------------------------------------------------------------------
** 修改人:				
** 日  期:			
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
uint8 MB_TCP_GetInputRegValue(uint8 ch, uint16 *ValuePtr,uint16 Address)
{
	uint8 err;
	err = MB_NO_ERR;
	if (Address < END_INPUT_REG_ADDR)
	{
		*ValuePtr = InputBuffer[Address];
	}
	else
	{
		switch (Address) 
		{
			case 300:
				*ValuePtr = AppAD0;
				break;
			case 301:
				*ValuePtr = AppAD1;
				break;
			case 302:
				*ValuePtr = AppAD2;
				break;
			case 303:
				*ValuePtr = AppAD2;
				break;
			case 304:
				*ValuePtr = AppAD2;
				break;
			case 305:
				*ValuePtr = AppAD2;
				break;
			case 306:
				*ValuePtr = AppAD2;
				break;
			case 307:
				*ValuePtr = AppAD2;
				break;
			case 308:
				*ValuePtr = AppAD2;
				break;
			case 309:
				*ValuePtr = AppAD2;
				break;
			case 310:
				*ValuePtr = AppAD2;
				break;
			case 311:
				*ValuePtr = AppAD2;
				break;
			case 312:
				*ValuePtr = AppAD2;
				break;
			case 313:
				*ValuePtr = AppAD2;
				break;
			case 314:
				*ValuePtr = AppAD2;
				break;
			case 315:
				*ValuePtr = AppAD2;
				break;
			default:
				err = ILLEGAL_DATA_ADDR;
				break;
		}
	}
	return (err);
}
#endif


/*********************************************************************************************************
** 在周立功的协议基础上修改的部分，根据实际的应用所有的通信通过读写Holding Register来实现，所有起始地址为40001
** 通信协议：
** 寄存器地址			
** 40129（0x80）		BIT0 急停信号其余位保留
** 40130（0x81）		BIT0~BIT9	传感器采样值1
** 40131（0x82）		BIT0~BIT9	传感器采样值2					
** 40132（0x83）		BIT0~BIT15	频率采样值1					
** 40133（0x84）		BIT0~BIT15	频率采样值2
**         
** 40145（0x90）		BIT0~BIT15	由主机设置寄存器1
** 40146（0x91）		BIT0~BIT15	由主机设置寄存器2
** 40147（0x92）		BIT0~BIT15	由主机设置寄存器3
** 40148（0x93）		BIT0~BIT15	由主机设置寄存器4		
** 	
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#if  TCP_READ_HOLD_REG_EN||TCP_WRITE_SING_REG_EN||TCP_WRITE_MULT_REG_EN||TCP_MASK_WRITE_REG_EN||TCP_READ_WRITE_REG_EN


#define MB_TCP_HOLDING_REG_ADDR_OFFSET		0x80
#define MB_TCP_HOLDING_REG_NUM				64
//#define END_HOLDING_REG_ADDR 150

//存储器表64个字，128个字节
volatile uint16 MB_TCP_RegBuf[MB_TCP_HOLDING_REG_NUM]={0x0000,0x0000,0x0000,0x0000,0x0000,0x1101,0x2202,0x3303,0x4404,0x5505,0x6606,0x7707,0x8808,0x9909,0xaa0a};


						
volatile MB_TCP_REG_TBL * const pMB_TCP_RegTbl = (MB_TCP_REG_TBL *)&MB_TCP_RegBuf[0];  						

#endif
/*********************************************************************************************************
** 函数名称:			MB_TCP_GetRegValue
**
** 功能描述:			读保持寄存器值函数，该函数由用户编写
**
** 输    入:		    ch，设备ID
**						*ValuePtr，保存获取寄存器的值的指针
**						Address，寄存器地址
** 输    出:			正常返回MB_NO_ERR,出错返回ILLEGAL_DATA_ADDR，或SLAVE_DEVICE_FAILURE。
**         
** 作    者:			徐伟林
** 日    期:			2010年5月19日
**-------------------------------------------------------------------------------------------------------
** 修改人:				
** 日  期:			
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#if  TCP_READ_HOLD_REG_EN||TCP_READ_WRITE_REG_EN
uint8 MB_TCP_GetRegValue(uint8 ch, uint16 *ValuePtr,uint16 Address)
{
	if((Address >= MB_TCP_HOLDING_REG_ADDR_OFFSET)&&(Address < MB_TCP_HOLDING_REG_NUM+MB_TCP_HOLDING_REG_ADDR_OFFSET))
	{
		*ValuePtr = MB_TCP_RegBuf[Address - MB_TCP_HOLDING_REG_ADDR_OFFSET];
		return MB_NO_ERR;
	}
	else
		return ILLEGAL_DATA_ADDR;

}
#endif
/*********************************************************************************************************
** 函数名称:			MB_TCP_SetRegValue
**
** 功能描述:			写保持寄存器值函数，该函数由用户编写
**
** 输    入:		    ch，设备ID
**						Address，寄存器地址
**						Value，写入的值
** 输    出:			正常返回MB_NO_ERR,出错返回ILLEGAL_DATA_ADDR，或SLAVE_DEVICE_FAILURE。
**         
** 作    者:			徐伟林
** 日    期:			2010年5月19日
**-------------------------------------------------------------------------------------------------------
** 修改者:				
** 日  期:			
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#if  TCP_WRITE_SING_REG_EN||TCP_WRITE_MULT_REG_EN||TCP_MASK_WRITE_REG_EN||TCP_READ_WRITE_REG_EN
uint8 MB_TCP_SetRegValue(uint8 ch, uint16 Address,uint16 Value)
{
	if((Address >= MB_TCP_HOLDING_REG_ADDR_OFFSET)&&(Address < MB_TCP_HOLDING_REG_NUM+MB_TCP_HOLDING_REG_ADDR_OFFSET))
	{
		MB_TCP_RegBuf[Address - MB_TCP_HOLDING_REG_ADDR_OFFSET] = Value;
		return MB_NO_ERR;
	}
	else
		return ILLEGAL_DATA_ADDR;
}
#endif
/*********************************************************************************************************
** 函数名称:           BSP_MB_TmrInit
** 功能描述:            定时器初始化函数,根据提供的参数设定定时器中断产生的频率
** 输    入:        time，定时器频率，最小值为25uS
** 输    出:       none
** 
** 作    者:           徐伟林
** 日    期:           2010年5月19日
**--------------------------------------------------------------------------------------------------------
** 修改者:             
** 日  期:           
**--------------------------------------------------------------------------------------------------------
**              
**           
**                          
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/ 
#if 0
void BSP_MB_TmrInit (INT32U time)
{
    char TmrArg[50];
    sprintf(TmrArg, "Time=%uld ActCtrl=3",time);
    sysTimerInit(TIMER1,"Mode=0",NULL);		 	                        /*  定时器1初始化               */
   /* 
	* 设置定时器1的工作模式为定时模式：
    * Time=500：定时时间为500us 
	* ActCtrl=3：匹配后将T1TC复位,并产生中断 
	*/
	sysTimerSetMode(TIMER1,SET_TIMERMODE,TmrArg);
									 	                           
	if(0 == vicIrqFuncSet(TIMER1_IRQ_CHN,7,(uint32)TIMER1_ISR))    			/*  设置中断，一定要在中断函数中
	                                                                        添加MB_TmrUpdate()函数      */
    while(1);
    sysTimerStart(TIMER1);                                            /*  开启定时器                  */
}
#endif

#endif
#endif
/****************************************************************************************************************/
// File end
/****************************************************************************************************************/
