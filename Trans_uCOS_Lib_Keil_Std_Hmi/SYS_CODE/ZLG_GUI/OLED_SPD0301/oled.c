/****************************************************************************************
* 文件名：LCDDRIVE.C
* 功能：图形液晶240*128驱动(型号为SMG240128A)。32K显示存，0000H-7FFFH地址。显示是横向字节，高位
*      在前。
* 说明：图形液晶采用T6963C为LCD控制芯片，内带负压产生器，单5伏供电，并行接口(使用LPC2210驱动)。
* 硬件连接： D0--D7  <===>  D0--D7
*           /WR     <===>  nWE
*           /RD     <===>  nOE
*           /CE     <===>  nCS3_1
*           C/D     <===>  A1
*
*           /RST    <===>  VCC
****************************************************************************************/
#include "oled.h"
#include  "..\..\Head\system.h"

unsigned char  	__SucDispBuf[GUI_LCM_YMAX/8][GUI_LCM_XMAX];				// 声明GUI显示缓冲区
static unsigned char __SucIsNew;
/* 定义LCM地址 */

#define  LCD_COM    	            (*((volatile unsigned char *) 0x83000000))
#define  LCD_DAT    	            (*((volatile unsigned char *) 0x83000002))	

/***********************************************************************
* 名称：LCD_WriteCmd()
* 功能：写命令子程序。(发送命令前，不检查液晶模块的状态)
* 入口参数：command  	要写入LCM的命令字
* 出口参数：无
* 说明：函数会设置LCM数据总线为输出方式
***********************************************************************/
#define   LcdWriteCmd(ucCmd)      LCD_COM = (unsigned char)ucCmd


/***********************************************************************
* 名称：LCD_WriteData()
* 功能：写数据子程序。(发送数据前，不检查液晶模块的状态)
* 入口参数：dat  	要写入LCM的数据
* 出口参数：无
* 说明：函数会设置LCM数据总线为输出方式
***********************************************************************/
#define  LcdWriteData(ucDat)      LCD_DAT = (unsigned char)ucDat



/***********************************************************************
* 名称：LCD_ReadState()
* 功能：读取状态字子程序。
* 入口参数：无
* 出口参数：返回值即为读出的状态字
* 说明：函数会设置LCM数据总线为输入方式
***********************************************************************/
#define  LcdReadState()           LCD_COM


/***********************************************************************
* 名称：LCD_ReadData()
* 功能：读取数据子程序。
* 入口参数：无
* 出口参数：返回值即为读出的数据
* 说明：函数会设置LCM数据总线为输入方式
***********************************************************************/
#define  LcdReadData()		    LCD_DAT

#if 0 
#define LcdReset()              {   gpioClr(P3_25);\
                                    delay1(2);\
                                    gpioSet(P3_25);\
                                }
#else
#define LcdReset()              {   gpioClr(P1_16);\
                                    delay1(2);\
                                    gpioSet(P1_16);\
                                }
#endif

/* 以下为LCM的驱动层，主要负责发送T6963的各种命令，提供设置显示地址等功能，在发送命令前会检测其状态字。带参数命令模式：先参数，后命令；操作模式：先命令，后数据 */

/* T6963C 命令定义 */
#define     SD_CUR_POS		0x21						/* 光标位置设置(只有设置到有效显示地址并打开显示时才看到) */
#define     SD_CGR_POS		0x22						/* CGRAM偏置地址设置(可以增加自已的符号) */
#define     SD_ADR_POS		0x24						/* 地址指针位置(设置读写操作指针) */

#define     SD_TXT_STP		0x40						/* 文本区首址(从此地址开始向屏幕左上角显示字符) */
#define     SD_TXT_WID		0x41						/* 文本区宽度(设置显示宽度，N/6或N/8，其中N为x轴的点数) */
#define     SD_GRH_STP		0x42						/* 图形区首址(从此地址开始向屏幕左上角显示点) */
#define     SD_GRH_WID		0x43						/* 图形区宽度(设置显示宽度，N/6或N/8，其中N为x轴的点数) */

#define     SD_MOD_OR       0x80						/* 显示方式：逻辑或 */
#define     SD_MOD_XOR		0x81						/* 显示方式：逻辑异或 */
#define     SD_MOD_AND		0x82						/* 显示方式：逻辑与 */
#define     SD_MOD_TCH		0x83						/* 显示方式：文本特征 */

#define     SD_DIS_SW       0x90						/* 显示开关：D0=1/0，光标闪烁启用/禁用 */
														/* 			D1=1/0，光标显示启用/禁用 */
														/* 			D2=1/0，文本显示启用/禁用(打开后再使用) */
														/* 			D3=1/0，图形显示启用/禁用(打开后再使用) */
														
#define     SD_CUR_SHP		0xA0						/* 光标形状选择：0xA0-0xA7表示光标占的行数 */

#define     SD_AUT_WR       0xB0						/* 自动写设置 */
#define     SD_AUT_RD       0xB1						/* 自动读设置 */
#define     SD_AUT_OVR		0xB2						/* 自动读/写结束 */

#define     SD_INC_WR       0xC0						/* 数据一次写，地址加1 */
#define     SD_INC_RD       0xC1						/* 数据一次读，地址加1 */
#define     SD_DEC_WR       0xC2						/* 数据一次写，地址减1 */
#define     SD_DEC_RD       0xC3						/* 数据一次读，地址减1 */
#define     SD_NOC_WR       0xC4						/* 数据一次写，地址不变 */
#define     SD_NOC_RD       0xC5						/* 数据一次读，地址不变 */

#define     SD_SCN_RD       0xE0						/* 屏读 */

#define     SD_SCN_CP       0xE8						/* 屏拷贝 */

#define     SD_BIT_OP       0xF0						/* 位操作：D0-D2--定义D0-D7位，D3--1为置位，0为清除 */

#define     SD_SET_LINE     0xb0 
#define     SD_SET_COL_LO   0x00 
#define     SD_SET_COL_HI   0x10 
#define     SD_SET_OFFSET   0xd3 

/***********************************************************************
* 名称：LCD_TestStaBit01()
* 功能：判断读写指令和读写数据是否允许。
* 入口参数：无
* 出口参数：返回0表示禁止，否则表示允许
***********************************************************************/
unsigned char  __lcdTestStaBit01(void)
{  unsigned char i;

   for(i=100; i>0; i--)
   {  if( (LcdReadState()&0x03)==0x03 ) break;
   }
   
   return(i);
}


/***********************************************************************
* 名称：LCD_TestStaBit3()
* 功能：数据自动写状态是否允许。
* 入口参数：无
* 出口参数：返回0表示禁止，否则表示允许
***********************************************************************/
unsigned char  __lcdTestStaBit3(void)
{  unsigned char i;

   for(i=100; i>0; i--)
   {  if( (LcdReadState()&0x08)==0x08 ) break;
   }
   
   return(i);
}


/***********************************************************************
* 名称：LCD_WriteTCmd1()
* 功能：写无参数命令子程序。会先判断LCM状态字。
* 入口参数：command  		要写入LCM的命令字
* 出口参数：操作出错返回0，否则返回1
***********************************************************************/
unsigned char  __lcdWriteTCmd1(unsigned char command)
{  if( __lcdTestStaBit01()==0 ) return(0);
   LcdWriteCmd(command);		// 发送命令字
   
   return(1);
}


/***********************************************************************
* 名称：LCD_WriteTCmd3()
* 功能：写双参数命令子程序。会先判断LCM状态字。
* 入口参数：command  	要写入LCM的命令字
*          dat1		参数1
*          dat2		参数2
* 出口参数：操作出错返回0，否则返回1
* 说明：先发送两字节参数据数据，再发送命令字
***********************************************************************/
unsigned char  __lcdWriteTCmd3(unsigned char command, unsigned char dat1, unsigned char dat2)
{  if( __lcdTestStaBit01()==0 ) return(0);
   LcdWriteData(dat1);				// 发送数据1
   
   if( __lcdTestStaBit01()==0 ) return(0);
   LcdWriteData(dat2);				// 发送数据2
   
   if( __lcdTestStaBit01()==0 ) return(0);
   LcdWriteCmd(command);		// 发送命令字
   
   return(1);
}


/***********************************************************************
* 名称：LCD_WriteTCmd2()
* 功能：写单参数命令子程序。会先判断LCM状态字。
* 入口参数：command  	要写入LCM的命令字
*          dat1		参数1
* 出口参数：操作出错返回0，否则返回1
* 说明：先发送参数据数据，再发送命令字
***********************************************************************/
unsigned char  __lcdWriteTCmd2(unsigned char command, unsigned char dat1)
{  if( __lcdTestStaBit01()==0 ) return(0);
   LcdWriteData(dat1);				// 发送数据1
   
   if( __lcdTestStaBit01()==0 ) return(0);
   LcdWriteCmd(command);		// 发送命令字
   
   return(1);
}


/***********************************************************************
* 名称：LCD_WriteTData1()
* 功能：写1字节数据子程序。会先判断状态字。
* 入口参数：dat  		要写入LCM的数据
* 出口参数：操作出错返回0，否则返回1
***********************************************************************/
unsigned char  __lcdWriteTData1(unsigned char dat)
{  if( __lcdTestStaBit3()==0 ) return(0);
   LcdWriteData(dat);				// 发送命令字
   
   return(1);
}


/* 以下为LCM的用户接口层，主要负责解释用户命令，并发送到LCM，为用户编程提供接口 */


/***********************************************************************
* 名称：LCD_Initialize()
* 功能：LCM初始化，将LCM初始化为纯图形模式，显示起始地址为0x0000，。
* 入口参数：无
* 出口参数：无
* 说明：函数会设置LCM数据总线为输出方式
***********************************************************************/
void  __lcdInitialize(void)
{  
    __lcdWriteTCmd3(SD_TXT_STP, 0x00, 0x00);			// 设置文本方式RAM起始地址
    __lcdWriteTCmd3(SD_TXT_WID, 30, 0x00);			// 设置文本模式的宽度，宽度为N/6或N/8，N为宽度点数，如240
    __lcdWriteTCmd3(SD_GRH_STP, 0x00, 0x00);			// 设置图形方式RAM起始地址
    __lcdWriteTCmd3(SD_GRH_WID, 30, 0x00);			// 设置图形模式的宽度，宽度为N/6或N/8，N为宽度点数，如240
    __lcdWriteTCmd1(SD_MOD_OR);						// 设置显示方式为"或"
    __lcdWriteTCmd1(SD_DIS_SW|0x08);					// 设置纯图形显示模式
}


/*********************************************************************************************************
** 函数名称: lcdInit
** 功能描述: 初始化LCD
** 输　入: 无
** 输　出: 无
** 全局变量: 无
** 调用模块: LcdWriteCmd
**
** 作　者: 徐伟林
** 日　期: 2010年7月10日
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void delay1(unsigned char uiSec)
{
    unsigned char j;
    while(uiSec--){
        for(j=0;j<20;j++)
        {;}
    }
}
#if 1
void lcdInit_(void)
{
	
	
	LcdReset();
	LcdWriteCmd(0xaf);    //10101111:  set display on
	delay1(2);
	//delay1(20);
	LcdWriteCmd(0xa4);    //10100100:  set Entire Display on/off: normal display(POR)
	delay1(2);
	//delay1(20);
	LcdWriteCmd(0xa6);    //10100110:  set nomal display(POR)
	delay1(2);
	//delay1(20);
	LcdWriteCmd(0x81);    //10000001:  set contrast control register 
	delay1(2);
	//delay1(20);
	LcdWriteCmd(0x80);    //10000000:  contrast set(select from 1 to 256)
    delay1(2);
	//delay1(20);
	LcdWriteCmd(0xa1);    //10100000:  set segment remap:column address 0 is mapped to SEG0(POR)
	delay1(2);
	//delay1(20);
	LcdWriteCmd(0xc8);    //11000000:  set com output scan direction:Scan from COM0 to COM(N-1)

    delay1(2);
    //delay1(20);
	LcdWriteCmd(0xd8);    //  11011000:  set area color mode on/off  
    delay1(2);
    //delay1(20);
	LcdWriteCmd(0x68);    //  00110000:  mono mode

	delay1(2);
	//delay1(20);
	LcdWriteCmd(0xda);    //  11011010:  set COM pins hardware configuration  
	delay1(2);
	//delay1(20);
	LcdWriteCmd(0x12);    //  00010010:  alternative COM pin configuration(COM62,60,58,...2,0,SEG0~96,COM1,3,5...61,63)
    delay1(2);
    //delay1(20);
    
    LcdWriteCmd(0x5c);
    delay1(2);
}


void ssd1335Init(void)
{
    LcdWriteCmd(0xae); //set display off
    delay1(2);
    LcdWriteCmd(0xad); //set DC DC
    delay1(2);
    LcdWriteCmd(0x8a); //second byte
    delay1(2);
    LcdWriteCmd(0xa8); //set multiplex ratio
    delay1(2);
    LcdWriteCmd(0x3f); //64MUX
    delay1(2);
    LcdWriteCmd(0xd3); //set display offset
    delay1(2);
    LcdWriteCmd(0x00); //second byte
    delay1(2);
    LcdWriteCmd(0x40); //set display start line
    delay1(2);
    LcdWriteCmd(0xa1); //set segment remap
    delay1(2);
    LcdWriteCmd(0xc8); //set COM output scan direction
    delay1(2);
    LcdWriteCmd(0xa6); //set normal/inverse display (normal)
    delay1(2);
    LcdWriteCmd(0xa4); //set entire display (normal)
    delay1(2);
    LcdWriteCmd(0x81); //set contrast control
    delay1(2);
    LcdWriteCmd(0x80);
    delay1(2);
    LcdWriteCmd(0xd5); //set display clock oscillator frequency/divide ratio.
    delay1(2);
    LcdWriteCmd(0x70); //105hz
    delay1(2);
    LcdWriteCmd(0xd8); //mode set
    delay1(2);
    LcdWriteCmd(0x05); //second byte
    delay1(2);
    LcdWriteCmd(0xd9); //set pre-charge period
    delay1(2);
    LcdWriteCmd(0x61); //set discharge/precharge
    delay1(2);
    LcdWriteCmd(0xaf); //set display on
    delay1(2);	
}

void ssd1305Init(void)
{
	
	LcdWriteCmd(0xaf);    //10101111:  set display on
	delay1(2);
	//delay1(20);
	LcdWriteCmd(0xa4);    //10100100:  set Entire Display on/off: normal display(POR)
	delay1(2);
	//delay1(20);
	LcdWriteCmd(0xa6);    //10100110:  set nomal display(POR)
	delay1(2);
	//delay1(20);
	LcdWriteCmd(0x81);    //10000001:  set contrast control register 
	delay1(2);
	//delay1(20);
	LcdWriteCmd(0x80);    //10000000:  contrast set(select from 1 to 256)
    delay1(2);
	//delay1(20);
	LcdWriteCmd(0xa0);    //10100000:  set segment remap:column address 0 is mapped to SEG0(POR)
	delay1(2);
	//delay1(20);
	LcdWriteCmd(0xc8);    //11000000:  set com output scan direction:Scan from COM0 to COM(N-1)

    delay1(2);
    //delay1(20);
	LcdWriteCmd(0xd8);    //  11011000:  set area color mode on/off  
    delay1(2);
    //delay1(20);
	LcdWriteCmd(0x68);    //  00110000:  mono mode

	delay1(2);
	//delay1(20);
	LcdWriteCmd(0xda);    //  11011010:  set COM pins hardware configuration  
	delay1(2);
	//delay1(20);
	LcdWriteCmd(0x12);    //  00010010:  alternative COM pin configuration(COM62,60,58,...2,0,SEG0~96,COM1,3,5...61,63)
    delay1(2);
    //delay1(20);
}

void lcdInit(void)
{
    LcdReset();
    __SucIsNew = gpioGet(P0_27);
    if (__SucIsNew) {
        ssd1335Init();
    } else {
        ssd1305Init();
    }
}
#else

void lcdInit(void)
{
	int i = 0;
	
	const unsigned char ucInitSequence[] = { 
                         0x00,   // Set Lower Column Address  
                         0x10,   // Set Higher Column Address  
                         0x40,   // Set Display Start Line  
                         0x81,   // Set Contrast Control  
                         0x80,   // 0 ~ 127  
                         0xA1,   // [A0]:column address 1 is  
                         0xC0,   // oben / unten  
                         0xA4,   // Display on  
                         0xA6,   // Normal Display 
                         0xA8,   // Set Multiplex Ratio  
                         0x3f,  
                         0xAD,   // Set DC-DC  
                         0x8A,   // 8B=ON, 8A=Off  
                         0xAF,   // AF=ON , AE=OFF 
                         0xD3,   // Set Display Offset 
                         0x00,   // No offset  
                         0xD5,   // Set Clock Divide  
                         0xd0,    
                         0xD8,   // Set Area Color On or Off  
                         0x00,   // Mono Mode  
                         0xDA,   // Set Pins Hardware  
                         0x12,  
                         0xDB,   // Set VCOMH  
                         0x00,  
                         0xD9,   // Set VP  
                         0x22,  
                         0xff};  
    do { 
         LcdWriteCmd(ucInitSequence[i]);
    	 delay1(2); 
         i++; 
    } while(ucInitSequence[i] != 0xff);
}
#endif
/*********************************************************************************************************
** 函数名称: LcdSetPos
** 功能描述: 设置液晶屏当前光标位置
** 输　入: ucX，x坐标；ucY，y坐标
** 输　出: 无
** 全局变量: 无
** 调用模块: LcdWriteCmd
**
** 作　者: 徐伟林
** 日　期: 2010年7月10日
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void lcdSetPos(unsigned char ucX, unsigned char ucY)
{ 
    ucX += 0;
    if (__SucIsNew) {
        LcdWriteCmd(SD_SET_LINE | (ucY & 0x0f)); 
        LcdWriteCmd(SD_SET_COL_LO | (ucX & 0x0f)); 
        LcdWriteCmd(SD_SET_COL_HI | ((ucX & 0xf0) >> 4)); 
    } else {
        ucX += 2; 
        LcdWriteCmd(SD_SET_LINE | (ucY & 0x0f)); 
        LcdWriteCmd(SD_SET_COL_LO | (ucX & 0x0f)); 
        LcdWriteCmd(SD_SET_COL_HI | ((ucX & 0xf0) >> 4)); 
    }
} 

/***********************************************************************
* 名称：LCD_FillAll()
* 功能：LCD填充。以图形方式进行填充，起始地址为0x0000。
* 入口参数：dat		要填充的数据
* 出口参数：无
***********************************************************************/
void  lcdFillAll(unsigned char dat)
{  
    #if 0
    uint32  i;

   
    __lcdWriteTCmd3(SD_ADR_POS, 0x00, 0x00);			// 置地址指针
    __lcdWriteTCmd1(SD_AUT_WR);						// 自动写
    for(i=0;i<128*30;i++)
    {  __lcdWriteTData1(dat);								// 写数据
    }
    LCD_WriteTCmd1(SD_AUT_OVR);						// 自动写结束
    LCD_WriteTCmd3(SD_ADR_POS,0x00,0x00);			// 重置地址指针
    #else
    unsigned char i,j;
	
	__lcdWriteTCmd3(SD_ADR_POS, 0x00, 0x00);			// 置地址指针
	__lcdWriteTCmd1(SD_AUT_WR);						// 自动写
	for(;;)
    {
        for(i = 0; i < 8; i++)
    	{ 
//    		LcdSetPos(0, i); 
    		for(j = 0; j < 128; j++)
    		{ 
    		     __lcdWriteTData1(__SucDispBuf[i][j]); 
    		};
    	}
    }
    __lcdWriteTCmd1(SD_AUT_OVR);						// 自动写结束
    __lcdWriteTCmd3(SD_ADR_POS,0x00,0x00);			// 重置地址指针
    #endif
}

/*********************************************************************************************************
** 函数名称: LcdSetPixel
** 功能描述: 绘制一个点
** 输　入: ucX，x坐标；ucY，y坐标
** 输　出: 无
** 全局变量: 无
** 调用模块: LcdWriteCmd
**
** 作　者: 徐伟林
** 日　期: 2010年7月10日
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void lcdSetPixel(unsigned char ucX, unsigned char ucY, unsigned char ucClr) 
{
    if (ucX < GUI_LCM_XMAX && ucY < GUI_LCM_YMAX) {
    	ucX += 0;
    	
    	if(ucClr)
    		__SucDispBuf[ucY / 8][ucX] |= (1<<(ucY & 0x07));
    	else
    		__SucDispBuf[ucY / 8][ucX] &= ~(1<<(ucY & 0x07));  
    }
}

unsigned char lcdGetPixel (unsigned char ucX, unsigned char ucY)
{
    if (ucX < GUI_LCM_XMAX && ucY < GUI_LCM_YMAX) {
        
        return __SucDispBuf[ucY / GUI_LCM_XMAX][ucX] & (1 <<(ucY & 0x07)) ? 1:0;
    } 
    return 0;
} 

/*********************************************************************************************************
** 函数名称: lcdDrawBmp
** 功能描述: 绘制一块数据
** 输　入: ucX，x坐标；ucY，y坐标
** 输　出: 无
** 全局变量: 无
** 调用模块: LcdWriteCmd
**
** 作　者: 徐伟林
** 日　期: 2010年7月10日
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void lcdDrawBmp (int ix0, 
                 int iy0,
                 int iwidth, 
                 int ilength,
                 unsigned short *pucBmp)
{
    int ix, iy;
    unsigned char ucClr;
    
    for (iy = iy0; iy < ilength + iy0; iy++) {
        for (ix = ix0; ix < iwidth + ix0; ix++) {
            ucClr = *pucBmp++;
            lcdSetPixel(ix, iy, ucClr);
        }
    }     
}

/*********************************************************************************************************
** Function name:           lcdRectRefresh
** Descriptions:            刷新指定矩形区域的显示，需要调整内部的延时，否则刷屏占用太多CPU时间
** input parameters:        uiX0:           矩形起始X坐标
**                          uiY0:           矩形起始Y坐标
**                          uiX1:           矩形终点X坐标
**                          uiY1：          矩形终点Y坐标
** output parameters:       none
** Returned value:          none                          
** Created by:              
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/   
void lcdRectRefresh(unsigned int uiX0, unsigned int uiY0, unsigned int uiX1, unsigned int uiY1)
{
    unsigned char i, j;
    unsigned char ucRow, ucLine;
    if (uiX1 >= GUI_LCM_XMAX) 
        uiX1 = GUI_LCM_XMAX - 1;
    if (uiY1 >= GUI_LCM_YMAX) 
        uiY1 = GUI_LCM_YMAX - 1;
    for (i = uiY0 / 8; i < (uiY1 + 7) / 8; i++) {
		lcdSetPos(uiX0, i); 
		for (j = uiX0; j < uiX1; j++) {
            LcdWriteData(__SucDispBuf[i][j]);
		}
	}
}

/*********************************************************************************************************
** Function name:           lcdRefresh
** Descriptions:            刷新全屏
** input parameters:        none
** output parameters:       none
** Returned value:          none                          
** Created by:              
** Created date:            
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/   
void lcdRefresh(void)
{
    unsigned char i, j;
    for (i = 0; i < GUI_LCM_YMAX/8; i++) {
		lcdSetPos(0, i); 
		for (j = 0; j < GUI_LCM_XMAX; j++) {
            LcdWriteData(__SucDispBuf[i][j]);
		}
	}
}
/*********************************************************************************************************
** 函数名称: lcdClr
** 功能描述: 清屏
** 输　入: ucX，x坐标；ucY，y坐标
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
** 作　者: 徐伟林
** 日　期: 2010年7月10日
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void lcdClr(unsigned char ucClr)
{
    unsigned char i, j;
	for (i = 0; i < GUI_LCM_YMAX/8; i++) {
		for (j = 0; j < GUI_LCM_XMAX; j++) {	
		    __SucDispBuf[i][j] = ucClr;
		}
	}
	lcdRefresh();
}

/*********************************************************************************************************
** 函数名称: lcdClr
** 功能描述: 清屏
** 输　入: ucX，x坐标；ucY，y坐标
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
********************************************************************************************************/
void lcdClrRect(uint32 x, uint32 y, uint32 hno, uint32 lno, uint8 ucClr)
{
    unsigned char i, j;
    for (i = x ; i < hno; i++) {
        for (j = y; j < ((y + 7) & ~0x07); j++) {	
            __SucDispBuf[j / 8][i] = (__SucDispBuf[j / 8][i] & ~(1 << (j & 0x07))) | (ucClr << (j & 0x07));
        }
        
        for (j = (y + 7) / 8; j < (y + lno) / 8; j++) {	
            __SucDispBuf[j][i] = ucClr;
        }
        
        for (j = (y + lno) & ~0x07; j < (y + lno); j++) {	
            __SucDispBuf[j / 8][i] = (__SucDispBuf[j / 8][i] & ~(1 << (j & 0x07))) | (ucClr << (j & 0x07));
        }
    }
    lcdRectRefresh(x, y, x + hno, y + lno);
}

/****************************************************************************
* 名称：LCD_UpdatePoint()
* 功能：在指定位置上画点，刷新某一点。
* 入口参数： x		指定点所在列的位置
*           y		指定点所在行的位置
* 出口参数：返回值为1时表示操作成功，为0时表示操作失败。
* 说明：操作失败原因是指定地址超出缓冲区范围。
****************************************************************************/
void  lcdUpdatePoint(unsigned int uiX, unsigned int uiY)
{  unsigned int  uiAddr; 
 
   /* 找出目标地址 */
   uiAddr = uiY * (GUI_LCM_XMAX >> 3) + (uiX >> 3);
   __lcdWriteTCmd3(SD_ADR_POS, uiAddr & 0xFF, uiAddr >> 8);	// 置地址指针
   
   /* 输出数据 */
   __lcdWriteTCmd2(SD_INC_WR, __SucDispBuf[uiY][uiX >> 3]);
}

