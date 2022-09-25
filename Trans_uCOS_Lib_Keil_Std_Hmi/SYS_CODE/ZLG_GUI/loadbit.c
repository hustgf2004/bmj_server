/****************************************************************************************
* �ļ�����LOADBIT.C
* ���ܣ���ʾ��ɫͼ�μ�������ʾ���Ƚ�ͼ��ת��Ϊ��Ӧ�ĵ������飬Ȼ�󼴿ɵ��ô��ļ��ĺ������������
* ���ߣ����ܱ�
* ���ڣ�2004.02.26
* ��ע��ʹ��GUI_SetBackColor()����������ʾ��ɫ������ɫ��
****************************************************************************************/
#include  "..\Head\system.h"
#include	<stdarg.h>
#include	<string.h>

extern void lcdRectRefresh(unsigned int uiX0, unsigned int uiY0, unsigned int uiX1, unsigned int uiY1);
INT32U __GuiFontAddr;

#if  (GUI_LoadPic_EN==1)|(GUI_MenuIco_EN==1)|(GUI_PutHZ_EN==1)
/****************************************************************************
* ���ƣ�GUI_LoadLine()
* ���ܣ������ɫͼ�ε�һ�����ݡ�
* ��ڲ����� x		ָ����ʾλ�ã�x����
*           y		ָ����ʾλ�ã�y����
*           dat		Ҫ�����ʾ�����ݡ�
*           no      Ҫ��ʾ���еĵ����
* ���ڲ���������ֵΪ1ʱ��ʾ�����ɹ���Ϊ0ʱ��ʾ����ʧ�ܡ�
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
uint8  GUI_LoadLine(uint32 x, uint32 y, uint8 *dat, uint32 no)
{  uint8   bit_dat;
   uint8   i;
   TCOLOR  bakc;

   /* �������� */
   if(x>=GUI_LCM_XMAX) return(0);
   if(y>=GUI_LCM_YMAX) return(0);
   
   for(i=0; i<no; i++)
   {  /* �ж��Ƿ�Ҫ��ȡ�������� */
      if( (i%8)==0 ) bit_dat = *dat++;
     
      /* ������Ӧ�ĵ�Ϊcolor��Ϊback_color */
      if( (bit_dat&DCB2HEX_TAB[i&0x07])==0 ) 
          GUI_CopyColor(&bakc, back_color); 
      else  
          GUI_CopyColor(&bakc, disp_color);
      GUI_Point(x, y, bakc);       
     
      if( (++x)>=GUI_LCM_XMAX ) return(0);
   }
   
   return(1);
}
#endif


#if  (GUI_LoadPic_EN==1)|(GUI_MenuIco_EN==1)
/****************************************************************************
* ���ƣ�GUI_LoadPic()
* ���ܣ������ɫͼ�����ݡ�
* ��ڲ����� x		ָ����ʾλ�ã�x����
*           y		ָ����ʾλ�ã�y����
*           dat		Ҫ�����ʾ������
*           hno     Ҫ��ʾ���еĵ����
*           lno     Ҫ��ʾ���еĵ����
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
void  GUI_LoadPic(uint32 x, uint32 y, uint8 *dat, uint32 hno, uint32 lno)
{  
    uint32  i;
    uint32 y_temp = y;
    for(i=0; i<lno; i++) {  
        GUI_LoadLine(x, y_temp, dat, hno);				// ���һ������
        y_temp++;										// ��ʾ��һ��
        dat += (hno>>3);							// ������һ�е�����
        if ((hno & 0x07) != 0) 
            dat++;
    }
#if __DISPLAY_ON_EN > 0
   lcdRectRefresh(x, y, x + hno, y + lno); 
#endif
}




/****************************************************************************
* ���ƣ�GUI_LoadPic1()
* ���ܣ������ɫͼ�����ݣ�������ʾ��
* ��ڲ����� x		ָ����ʾλ�ã�x����
*           y		ָ����ʾλ�ã�y����
*           dat		Ҫ�����ʾ�����ݡ�
*           hno     Ҫ��ʾ���еĵ����
*           lno     Ҫ��ʾ���еĵ����
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
void  GUI_LoadPic1(uint32 x, uint32 y, uint8 *dat, uint32 hno, uint32 lno)
{  uint32  i;
   
   GUI_ExchangeColor();									// ��ʾɫ�뱳��ɫ����
   for(i=0; i<lno; i++)
   {  GUI_LoadLine(x, y, dat, hno);						// ���һ������
      y++;												// ��ʾ��һ��
      dat += (hno>>3);									// ������һ�е�����
      if( (hno&0x07)!=0 ) dat++;
   }
   GUI_ExchangeColor();
   
}
#endif


#if  GUI_PutHZ_EN==1
/****************************************************************************
* ���ƣ�GUI_PutHZ()
* ���ܣ���ʾ���֡�
* ��ڲ����� x		ָ����ʾλ�ã�x����
*           y		ָ����ʾλ�ã�y����
*           dat		Ҫ�����ʾ�ĺ��ֵ������ݡ�
*           hno     Ҫ��ʾ���еĵ����
*           lno     Ҫ��ʾ���еĵ����
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
void  __GUI_PutHZ(uint32 x, uint32 y, uint8 *dat, uint8 hno, uint8 lno)
{  uint8  i;

   for(i=0; i<lno; i++)
   {  GUI_LoadLine(x, y, dat, hno);						// ���һ������
      y++;												// ��ʾ��һ��
      dat += (hno>>3);									// ������һ�е�����
      if( (hno&0x07)!=0 ) dat++;
   }
}
#endif



/*********************************************************************************************************
** ��������: GUI_PutHZ
** ��������: ���һ���ַ�
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
void GUI_PutHZ(unsigned int uiX, unsigned int uiY, unsigned char *pucDat)
{
    unsigned char *pucFontAddr;
    unsigned char ucBuf[32];
    
    if (*pucDat < 128) {                                                /*  ASCII��                     */                                
        #if 0
        pucFontAddr = (unsigned char *)__GuiFontAddr + 
                       (*pucDat - 0x20) * FONT_YSIZE16 * 2;
        #else
        pucFontAddr = (unsigned char *)FONT8x16ASCII +
                       (*pucDat - 0x20) * FONT_YSIZE16;
        #endif
        /*
         *  2013.02.01�޸�
         *  ASCII����ʾ���ݴ�16*16�����г�ȡ         
         */
        #if 0
        for (uiOffset = 0; uiOffset < FONT_YSIZE16; uiOffset++) {
            
                ucBuf[uiOffset] = pucFontAddr[uiOffset * 2]; 
        }
        #else
        memcpy(ucBuf, pucFontAddr , ( FONT_YSIZE16 * FONT_XSIZE8 / 8));
        #endif
        __GUI_PutHZ(uiX, uiY, ucBuf, FONT_XSIZE8, FONT_YSIZE16); 
                
    } else {                                                            /*  ����                        */
        
        
        pucFontAddr = (unsigned char *)__GuiFontAddr; 
                    //+ 0x60 * FONT_YSIZE16; 
        #if 0
        /*
         *  �ֿ����˾��򣬵���ƫ�����ļ��� by xuwl
         */
        if (pucDat[0] >= 0xb0 ) {
            pucFontAddr += ((pucDat[0] - 0xA0 - 1 - 6)*94+(pucDat[1] - 0xA0-1))*
                            ( FONT_XSIZE16 * FONT_YSIZE16 / 8);
        } else {                                                        /*  ���ķ���                    */
            pucFontAddr += ((pucDat[0] - 0xA0-1)*94+(pucDat[1] - 0xA0-1))*
                            ( FONT_XSIZE16 * FONT_YSIZE16 / 8);     
        }
        
        #else
        pucFontAddr += ((pucDat[0] - 0xA0-1)*94+(pucDat[1] - 0xA0-1))*
                        ( FONT_XSIZE16 * FONT_YSIZE16 / 8);          
        #endif
        
             
        
        
        memcpy(ucBuf, pucFontAddr , FONT_XSIZE16 * FONT_YSIZE16 / 8);
        //*(unsigned short *)&ucBuf[16] = *(unsigned short *)(pucFontAddr + 16);    
        __GUI_PutHZ(uiX, uiY, ucBuf, FONT_XSIZE16 ,FONT_YSIZE16);           //���������
    }    
}
#if 0
/*********************************************************************************************************
** ��������: GUI_DispStringH
** ��������: ��ָ��λ��ˮƽ���һ���ַ�
** �䡡��:  ucX:x����;
**          ucY:y����
**          str:�ַ���
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
void GUI_DispStringH(unsigned char ucX, unsigned char ucY, unsigned char *str)
{
  
    while(1)
    {  
        if( (*str)=='\0' ) break;
     
        if(*str > 127) {                                                /*  ��������                    */
            GUI_PutHZ(ucX, ucY, str);
            str += 2;  
            ucX += FONT_XSIZE16; 
        } else {
            GUI_PutHZ(ucX, ucY, str);
            str += 1;
            ucX += FONT_XSIZE8;                                         /*  ��������                    */
        } 
    }
#if __DISPLAY_ON_EN > 0
    lcdRefresh();
#endif
}
#endif
/*********************************************************************************************************
** ��������: GUI_DispStringH
** ��������: ��ָ��λ�����һ���ַ�
** �䡡��:  ucX:x����;
**          ucY:y����;
**          ucIsAnti:���Ա�־
**          str:�ַ���
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
void GUI_DispString(unsigned char ucX, unsigned char ucY, unsigned char ucIsAnti, unsigned char *pStr) 
{
    unsigned int uiX, uiY;
    if (!pStr)
        return;
    if ((ucX >= GUI_LCM_XMAX) || (ucY >= GUI_LCM_YMAX)) {
        return;
    }
    uiX = ucX;
    uiY = ucY;
    
    OSSchedLock();
    if (ucIsAnti) {
        GUI_SetColor(0, 1);
    }
    for (; *pStr; pStr++) {
        if ((*pStr == '\n') || (*pStr == '\r')) {                       /*  �س����з�                */
            uiX = 0;
            if (*pStr == '\n')
            uiY += FONT_YSIZE16;
        } else {
            GUI_PutHZ(uiX, uiY, pStr);
            if (*pStr < 0x7f) {
                uiX += FONT_XSIZE8;
                
            }
            else {
                uiX += FONT_XSIZE16;
                pStr++;
            }
            if (uiX >= GUI_LCM_XMAX) {
                break;
                //uiX = 0;
                //uiY += FONT_YSIZE16;
            }
        }
        if (*pStr == 0)                                                 /*  ������                      */
          break;
    }
    if (ucIsAnti) {
        GUI_SetColor(1 , 0);
    }
    OSSchedUnlock();
 #if __DISPLAY_ON_EN > 0 
    //lcdRefresh();
    lcdRectRefresh(ucX, ucY, uiX, uiY + FONT_YSIZE16);
 #endif
}

/*********************************************************************************************************
** ��������: GUI_Printf
** ��������: ��ָ��λ�����һ���ַ�
** �䡡��:  ucX:x����;
**          ucY:y����;
**          ucIsAnti:���Ա�־
**          pcFmt:��ʽ���ַ���
** �䡡��:      ��
** ȫ�ֱ���:    ��
** ����ģ��: 
**
** ������: ��ΰ��
** �ա���: 2010��7��10��
**-------------------------------------------------------------------------------------------------------
** �޸���: 
** �ա���: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void GUI_Printf(unsigned int uiX, unsigned int uiY, unsigned char ucIsAnti, const char  *pcFmt,...)
{       
    va_list ap;
    char pbString[256];        
    unsigned char *pcString;
    va_start(ap, pcFmt);
    vsprintf(pbString, pcFmt, ap);

    va_end(ap);
    pcString = (unsigned char *)pbString;
    GUI_DispString(uiX, uiY, ucIsAnti, pcString);
}

/*********************************************************************************************************
** Function name:           GUI_Refresh
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
INT32S GUI_Refresh(int uiX0, int uiY0, int uiX1, int uiY1)
{
    if ((uiX0 > GUI_LCM_XMAX) || (uiX1 > GUI_LCM_XMAX) ||
        (uiY0 > GUI_LCM_YMAX) || (uiY1 > GUI_LCM_YMAX)) {
        return (-SYS_PARA_ERR);
    }
    lcdRectRefresh(uiX0, uiY0, uiX1, uiY1);
    return SYS_OK;
}


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
