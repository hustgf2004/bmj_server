/****************************************************************************************
* �ļ�����LOADBIT.H
* ���ܣ���ʾ��ɫͼ�μ�������ʾ��(ͷ�ļ�)
* ���ߣ����ܱ�
* ���ڣ�2004.02.26
* ��ע��
****************************************************************************************/
#ifndef  LOADBIT_H
#define  LOADBIT_H

#define     FONT_XSIZE8         8
#define     FONT_XSIZE16        16
#define     FONT_YSIZE16        16

/*********************************************************************************************************
* ���ƣ�GUI_Initialize()
* ���ܣ���ʼ��GUI��������ʼ����ʾ����������ʼ��LCM��������
* ��ڲ�����uiBrightness:����(0~0xFF)
**          uiContrast: �Աȶ�(0~0xFF)
* ���ڲ�������
* ˵�����û�����LCM��ʵ�������д�˺�����
*********************************************************************************************************/
//extern void  GUI_Initialize(INT32U uiBrightness, INT32U uiContrast);

/*********************************************************************************************************
* ���ƣ�GUI_BrightnessSet()
* ���ܣ����ȵ���
* ��ڲ�����uiBrightness:����(0~0xFF)
* ���ڲ�������
* ˵�����û�����LCM��ʵ�������д�˺�����
*********************************************************************************************************/
//extern void  GUI_BrightnessSet(INT32U uiBrightness);

/*********************************************************************************************************
* ���ƣ�GUI_ContrastSet()
* ���ܣ��Աȶȵ���
* ��ڲ�����uiContrast: �Աȶ�(0~0xFF)
* ���ڲ�������
* ˵�����û�����LCM��ʵ�������д�˺�����
*********************************************************************************************************/
//extern void  GUI_ContrastSet(INT32U uiContrast);

/*********************************************************************************************************
* ���ƣ�GUI_FillSCR()
* ���ܣ�ȫ����䡣ֱ��ʹ�����������ʾ��������
* ��ڲ�����dat		��������
* ���ڲ�������
* ˵�����û�����LCM��ʵ�������д�˺�����
*********************************************************************************************************/
extern void  GUI_FillSCR(TCOLOR dat);    

/*********************************************************************************************************
* ���ƣ�GUI_ClearSCR()
* ���ܣ�������
* ��ڲ�������
* ���ڲ�������
* ˵�����û�����LCM��ʵ�������д�˺�����
*********************************************************************************************************/
extern void  GUI_ClearSCR(void);

/*********************************************************************************************************
* ���ƣ�GUI_ClearRectangle()
* ���ܣ�������������
* ��ڲ�����x0		ˮƽ����������е�λ��
*           y0		ˮƽ����������е�λ��
*           x1      ˮƽ���յ������е�λ��
* ���ڲ�������
* ˵�����û�����LCM��ʵ�������д�˺�����
*********************************************************************************************************/
extern void  GUI_ClearRectangle(uint32 x0, uint32 y0, uint32 x1, uint32 y1);

/****************************************************************************
* ���ƣ�GUI_LoadPic()
* ���ܣ������ɫͼ�����ݣ�������ʾ��
* ��ڲ����� x		ָ����ʾλ�ã�x����
*           y		ָ����ʾλ�ã�y����
*           dat		Ҫ�����ʾ������
*           hno     Ҫ��ʾ���еĵ����
*           lno     Ҫ��ʾ���еĵ����
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
extern  void  GUI_LoadPic(uint32 x, uint32 y, uint8 *dat, uint32 hno, uint32 lno);


                    


/****************************************************************************
* ���ƣ�GUI_LoadPic1()
* ���ܣ������ɫͼ�����ݣ�������ʾ��
* ��ڲ����� x		ָ����ʾλ�ã�x����
*           y		ָ����ʾλ�ã�y����
*           dat		Ҫ�����ʾ������
*           hno     Ҫ��ʾ���еĵ����
*           lno     Ҫ��ʾ���еĵ����
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
extern  void  GUI_LoadPic1(uint32 x, uint32 y, uint8 *dat, uint32 hno, uint32 lno);


/****************************************************************************
* ���ƣ�GUI_PutHZ()
* ���ܣ���ʾ���֡�
* ��ڲ����� x		ָ����ʾλ�ã�x����
*           y		ָ����ʾλ�ã�y����
*           dat		Ҫ�����ʾ�ĺ��ֵ�������
*           hno     Ҫ��ʾ���еĵ����
*           lno     Ҫ��ʾ���еĵ����
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
//extern  void  __GUI_PutHZ(uint32 x, uint32 y, uint8 *dat, uint8 hno, uint8 lno);

/****************************************************************************
* ���ƣ�GUI_Printf()
* ���ܣ���ӡ�����
* ��ڲ�����uiXPoint		ָ����ʾλ�ã�x����
*           uiYPoint		ָ����ʾλ�ã�y����
*           ucIsAnti		�Ƿ���
*           pcString        ��ʽ�ַ���
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
extern  void GUI_Printf(unsigned int uiXPoint, 
                        unsigned int uiYPoint, 
                        INT8U ucIsAnti, 
                        const char * pcString,...);

/****************************************************************************
* ���ƣ�GUI_PrintfEx()
* ���ܣ���ӡ�����
* ��ڲ�����uiCol		    ָ����ʾλ�ã�����ʼֵ
*           uiLine		    ָ����ʾλ�ã�����ʼֵ
*           ucIsAnti		�Ƿ���
*           pcString        ��ʽ�ַ���
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
extern  void GUI_PrintfEx (unsigned int uiCol, 
                           unsigned int uiLine, 
                           INT8U ucIsAnti, 
                           char * pcString,...);

/*********************************************************************************************************
** Function name:           GUI_Refresh
** Descriptions:            Һ��ʵʱˢ��
** input parameters:        ix0     x side coordinate of the first pixel
**                          iy0     y side coordinate of the first pixel
**                          iwidth  x side width
**                          ilength y side length
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
INT32S GUI_Refresh(int ix0, 
                   int iy0,                  
                   int iwidth, 
                   int ilength);
                   
                   
extern void GUI_DispString(unsigned char ucX, 
                            unsigned char ucY, 
                            unsigned char ucIsAnti, 
                            unsigned char *pStr);  
                            
extern void GUI_DispStringH(unsigned char ucX, 
                            unsigned char ucY, 
                            unsigned char *str);                                             
extern INT32U __GuiFontAddr;
#endif