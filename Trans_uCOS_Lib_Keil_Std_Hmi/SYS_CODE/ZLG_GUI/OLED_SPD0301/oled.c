/****************************************************************************************
* �ļ�����LCDDRIVE.C
* ���ܣ�ͼ��Һ��240*128����(�ͺ�ΪSMG240128A)��32K��ʾ�棬0000H-7FFFH��ַ����ʾ�Ǻ����ֽڣ���λ
*      ��ǰ��
* ˵����ͼ��Һ������T6963CΪLCD����оƬ���ڴ���ѹ����������5�����磬���нӿ�(ʹ��LPC2210����)��
* Ӳ�����ӣ� D0--D7  <===>  D0--D7
*           /WR     <===>  nWE
*           /RD     <===>  nOE
*           /CE     <===>  nCS3_1
*           C/D     <===>  A1
*
*           /RST    <===>  VCC
****************************************************************************************/
#include "oled.h"
#include  "..\..\Head\system.h"

unsigned char  	__SucDispBuf[GUI_LCM_YMAX/8][GUI_LCM_XMAX];				// ����GUI��ʾ������
static unsigned char __SucIsNew;
/* ����LCM��ַ */

#define  LCD_COM    	            (*((volatile unsigned char *) 0x83000000))
#define  LCD_DAT    	            (*((volatile unsigned char *) 0x83000002))	

/***********************************************************************
* ���ƣ�LCD_WriteCmd()
* ���ܣ�д�����ӳ���(��������ǰ�������Һ��ģ���״̬)
* ��ڲ�����command  	Ҫд��LCM��������
* ���ڲ�������
* ˵��������������LCM��������Ϊ�����ʽ
***********************************************************************/
#define   LcdWriteCmd(ucCmd)      LCD_COM = (unsigned char)ucCmd


/***********************************************************************
* ���ƣ�LCD_WriteData()
* ���ܣ�д�����ӳ���(��������ǰ�������Һ��ģ���״̬)
* ��ڲ�����dat  	Ҫд��LCM������
* ���ڲ�������
* ˵��������������LCM��������Ϊ�����ʽ
***********************************************************************/
#define  LcdWriteData(ucDat)      LCD_DAT = (unsigned char)ucDat



/***********************************************************************
* ���ƣ�LCD_ReadState()
* ���ܣ���ȡ״̬���ӳ���
* ��ڲ�������
* ���ڲ���������ֵ��Ϊ������״̬��
* ˵��������������LCM��������Ϊ���뷽ʽ
***********************************************************************/
#define  LcdReadState()           LCD_COM


/***********************************************************************
* ���ƣ�LCD_ReadData()
* ���ܣ���ȡ�����ӳ���
* ��ڲ�������
* ���ڲ���������ֵ��Ϊ����������
* ˵��������������LCM��������Ϊ���뷽ʽ
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

/* ����ΪLCM�������㣬��Ҫ������T6963�ĸ�������ṩ������ʾ��ַ�ȹ��ܣ��ڷ�������ǰ������״̬�֡�����������ģʽ���Ȳ��������������ģʽ������������� */

/* T6963C ����� */
#define     SD_CUR_POS		0x21						/* ���λ������(ֻ�����õ���Ч��ʾ��ַ������ʾʱ�ſ���) */
#define     SD_CGR_POS		0x22						/* CGRAMƫ�õ�ַ����(�����������ѵķ���) */
#define     SD_ADR_POS		0x24						/* ��ַָ��λ��(���ö�д����ָ��) */

#define     SD_TXT_STP		0x40						/* �ı�����ַ(�Ӵ˵�ַ��ʼ����Ļ���Ͻ���ʾ�ַ�) */
#define     SD_TXT_WID		0x41						/* �ı������(������ʾ��ȣ�N/6��N/8������NΪx��ĵ���) */
#define     SD_GRH_STP		0x42						/* ͼ������ַ(�Ӵ˵�ַ��ʼ����Ļ���Ͻ���ʾ��) */
#define     SD_GRH_WID		0x43						/* ͼ�������(������ʾ��ȣ�N/6��N/8������NΪx��ĵ���) */

#define     SD_MOD_OR       0x80						/* ��ʾ��ʽ���߼��� */
#define     SD_MOD_XOR		0x81						/* ��ʾ��ʽ���߼���� */
#define     SD_MOD_AND		0x82						/* ��ʾ��ʽ���߼��� */
#define     SD_MOD_TCH		0x83						/* ��ʾ��ʽ���ı����� */

#define     SD_DIS_SW       0x90						/* ��ʾ���أ�D0=1/0�������˸����/���� */
														/* 			D1=1/0�������ʾ����/���� */
														/* 			D2=1/0���ı���ʾ����/����(�򿪺���ʹ��) */
														/* 			D3=1/0��ͼ����ʾ����/����(�򿪺���ʹ��) */
														
#define     SD_CUR_SHP		0xA0						/* �����״ѡ��0xA0-0xA7��ʾ���ռ������ */

#define     SD_AUT_WR       0xB0						/* �Զ�д���� */
#define     SD_AUT_RD       0xB1						/* �Զ������� */
#define     SD_AUT_OVR		0xB2						/* �Զ���/д���� */

#define     SD_INC_WR       0xC0						/* ����һ��д����ַ��1 */
#define     SD_INC_RD       0xC1						/* ����һ�ζ�����ַ��1 */
#define     SD_DEC_WR       0xC2						/* ����һ��д����ַ��1 */
#define     SD_DEC_RD       0xC3						/* ����һ�ζ�����ַ��1 */
#define     SD_NOC_WR       0xC4						/* ����һ��д����ַ���� */
#define     SD_NOC_RD       0xC5						/* ����һ�ζ�����ַ���� */

#define     SD_SCN_RD       0xE0						/* ���� */

#define     SD_SCN_CP       0xE8						/* ������ */

#define     SD_BIT_OP       0xF0						/* λ������D0-D2--����D0-D7λ��D3--1Ϊ��λ��0Ϊ��� */

#define     SD_SET_LINE     0xb0 
#define     SD_SET_COL_LO   0x00 
#define     SD_SET_COL_HI   0x10 
#define     SD_SET_OFFSET   0xd3 

/***********************************************************************
* ���ƣ�LCD_TestStaBit01()
* ���ܣ��ж϶�дָ��Ͷ�д�����Ƿ�����
* ��ڲ�������
* ���ڲ���������0��ʾ��ֹ�������ʾ����
***********************************************************************/
unsigned char  __lcdTestStaBit01(void)
{  unsigned char i;

   for(i=100; i>0; i--)
   {  if( (LcdReadState()&0x03)==0x03 ) break;
   }
   
   return(i);
}


/***********************************************************************
* ���ƣ�LCD_TestStaBit3()
* ���ܣ������Զ�д״̬�Ƿ�����
* ��ڲ�������
* ���ڲ���������0��ʾ��ֹ�������ʾ����
***********************************************************************/
unsigned char  __lcdTestStaBit3(void)
{  unsigned char i;

   for(i=100; i>0; i--)
   {  if( (LcdReadState()&0x08)==0x08 ) break;
   }
   
   return(i);
}


/***********************************************************************
* ���ƣ�LCD_WriteTCmd1()
* ���ܣ�д�޲��������ӳ��򡣻����ж�LCM״̬�֡�
* ��ڲ�����command  		Ҫд��LCM��������
* ���ڲ���������������0�����򷵻�1
***********************************************************************/
unsigned char  __lcdWriteTCmd1(unsigned char command)
{  if( __lcdTestStaBit01()==0 ) return(0);
   LcdWriteCmd(command);		// ����������
   
   return(1);
}


/***********************************************************************
* ���ƣ�LCD_WriteTCmd3()
* ���ܣ�д˫���������ӳ��򡣻����ж�LCM״̬�֡�
* ��ڲ�����command  	Ҫд��LCM��������
*          dat1		����1
*          dat2		����2
* ���ڲ���������������0�����򷵻�1
* ˵�����ȷ������ֽڲ��������ݣ��ٷ���������
***********************************************************************/
unsigned char  __lcdWriteTCmd3(unsigned char command, unsigned char dat1, unsigned char dat2)
{  if( __lcdTestStaBit01()==0 ) return(0);
   LcdWriteData(dat1);				// ��������1
   
   if( __lcdTestStaBit01()==0 ) return(0);
   LcdWriteData(dat2);				// ��������2
   
   if( __lcdTestStaBit01()==0 ) return(0);
   LcdWriteCmd(command);		// ����������
   
   return(1);
}


/***********************************************************************
* ���ƣ�LCD_WriteTCmd2()
* ���ܣ�д�����������ӳ��򡣻����ж�LCM״̬�֡�
* ��ڲ�����command  	Ҫд��LCM��������
*          dat1		����1
* ���ڲ���������������0�����򷵻�1
* ˵�����ȷ��Ͳ��������ݣ��ٷ���������
***********************************************************************/
unsigned char  __lcdWriteTCmd2(unsigned char command, unsigned char dat1)
{  if( __lcdTestStaBit01()==0 ) return(0);
   LcdWriteData(dat1);				// ��������1
   
   if( __lcdTestStaBit01()==0 ) return(0);
   LcdWriteCmd(command);		// ����������
   
   return(1);
}


/***********************************************************************
* ���ƣ�LCD_WriteTData1()
* ���ܣ�д1�ֽ������ӳ��򡣻����ж�״̬�֡�
* ��ڲ�����dat  		Ҫд��LCM������
* ���ڲ���������������0�����򷵻�1
***********************************************************************/
unsigned char  __lcdWriteTData1(unsigned char dat)
{  if( __lcdTestStaBit3()==0 ) return(0);
   LcdWriteData(dat);				// ����������
   
   return(1);
}


/* ����ΪLCM���û��ӿڲ㣬��Ҫ��������û���������͵�LCM��Ϊ�û�����ṩ�ӿ� */


/***********************************************************************
* ���ƣ�LCD_Initialize()
* ���ܣ�LCM��ʼ������LCM��ʼ��Ϊ��ͼ��ģʽ����ʾ��ʼ��ַΪ0x0000����
* ��ڲ�������
* ���ڲ�������
* ˵��������������LCM��������Ϊ�����ʽ
***********************************************************************/
void  __lcdInitialize(void)
{  
    __lcdWriteTCmd3(SD_TXT_STP, 0x00, 0x00);			// �����ı���ʽRAM��ʼ��ַ
    __lcdWriteTCmd3(SD_TXT_WID, 30, 0x00);			// �����ı�ģʽ�Ŀ�ȣ����ΪN/6��N/8��NΪ��ȵ�������240
    __lcdWriteTCmd3(SD_GRH_STP, 0x00, 0x00);			// ����ͼ�η�ʽRAM��ʼ��ַ
    __lcdWriteTCmd3(SD_GRH_WID, 30, 0x00);			// ����ͼ��ģʽ�Ŀ�ȣ����ΪN/6��N/8��NΪ��ȵ�������240
    __lcdWriteTCmd1(SD_MOD_OR);						// ������ʾ��ʽΪ"��"
    __lcdWriteTCmd1(SD_DIS_SW|0x08);					// ���ô�ͼ����ʾģʽ
}


/*********************************************************************************************************
** ��������: lcdInit
** ��������: ��ʼ��LCD
** �䡡��: ��
** �䡡��: ��
** ȫ�ֱ���: ��
** ����ģ��: LcdWriteCmd
**
** ������: ��ΰ��
** �ա���: 2010��7��10��
**-------------------------------------------------------------------------------------------------------
** �޸���: 
** �ա���: 
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
** ��������: LcdSetPos
** ��������: ����Һ������ǰ���λ��
** �䡡��: ucX��x���ꣻucY��y����
** �䡡��: ��
** ȫ�ֱ���: ��
** ����ģ��: LcdWriteCmd
**
** ������: ��ΰ��
** �ա���: 2010��7��10��
**-------------------------------------------------------------------------------------------------------
** �޸���: 
** �ա���: 
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
* ���ƣ�LCD_FillAll()
* ���ܣ�LCD��䡣��ͼ�η�ʽ������䣬��ʼ��ַΪ0x0000��
* ��ڲ�����dat		Ҫ��������
* ���ڲ�������
***********************************************************************/
void  lcdFillAll(unsigned char dat)
{  
    #if 0
    uint32  i;

   
    __lcdWriteTCmd3(SD_ADR_POS, 0x00, 0x00);			// �õ�ַָ��
    __lcdWriteTCmd1(SD_AUT_WR);						// �Զ�д
    for(i=0;i<128*30;i++)
    {  __lcdWriteTData1(dat);								// д����
    }
    LCD_WriteTCmd1(SD_AUT_OVR);						// �Զ�д����
    LCD_WriteTCmd3(SD_ADR_POS,0x00,0x00);			// ���õ�ַָ��
    #else
    unsigned char i,j;
	
	__lcdWriteTCmd3(SD_ADR_POS, 0x00, 0x00);			// �õ�ַָ��
	__lcdWriteTCmd1(SD_AUT_WR);						// �Զ�д
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
    __lcdWriteTCmd1(SD_AUT_OVR);						// �Զ�д����
    __lcdWriteTCmd3(SD_ADR_POS,0x00,0x00);			// ���õ�ַָ��
    #endif
}

/*********************************************************************************************************
** ��������: LcdSetPixel
** ��������: ����һ����
** �䡡��: ucX��x���ꣻucY��y����
** �䡡��: ��
** ȫ�ֱ���: ��
** ����ģ��: LcdWriteCmd
**
** ������: ��ΰ��
** �ա���: 2010��7��10��
**-------------------------------------------------------------------------------------------------------
** �޸���: 
** �ա���: 
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
** ��������: lcdDrawBmp
** ��������: ����һ������
** �䡡��: ucX��x���ꣻucY��y����
** �䡡��: ��
** ȫ�ֱ���: ��
** ����ģ��: LcdWriteCmd
**
** ������: ��ΰ��
** �ա���: 2010��7��10��
**-------------------------------------------------------------------------------------------------------
** �޸���: 
** �ա���: 
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
** Descriptions:            ˢ��ָ�������������ʾ����Ҫ�����ڲ�����ʱ������ˢ��ռ��̫��CPUʱ��
** input parameters:        uiX0:           ������ʼX����
**                          uiY0:           ������ʼY����
**                          uiX1:           �����յ�X����
**                          uiY1��          �����յ�Y����
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
** Descriptions:            ˢ��ȫ��
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
** ��������: lcdClr
** ��������: ����
** �䡡��: ucX��x���ꣻucY��y����
** �䡡��: ��
** ȫ�ֱ���: ��
** ����ģ��: 
**
** ������: ��ΰ��
** �ա���: 2010��7��10��
**-------------------------------------------------------------------------------------------------------
** �޸���: 
** �ա���: 
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
** ��������: lcdClr
** ��������: ����
** �䡡��: ucX��x���ꣻucY��y����
** �䡡��: ��
** ȫ�ֱ���: ��
** ����ģ��: 
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
* ���ƣ�LCD_UpdatePoint()
* ���ܣ���ָ��λ���ϻ��㣬ˢ��ĳһ�㡣
* ��ڲ����� x		ָ���������е�λ��
*           y		ָ���������е�λ��
* ���ڲ���������ֵΪ1ʱ��ʾ�����ɹ���Ϊ0ʱ��ʾ����ʧ�ܡ�
* ˵��������ʧ��ԭ����ָ����ַ������������Χ��
****************************************************************************/
void  lcdUpdatePoint(unsigned int uiX, unsigned int uiY)
{  unsigned int  uiAddr; 
 
   /* �ҳ�Ŀ���ַ */
   uiAddr = uiY * (GUI_LCM_XMAX >> 3) + (uiX >> 3);
   __lcdWriteTCmd3(SD_ADR_POS, uiAddr & 0xFF, uiAddr >> 8);	// �õ�ַָ��
   
   /* ������� */
   __lcdWriteTCmd2(SD_INC_WR, __SucDispBuf[uiY][uiX >> 3]);
}

