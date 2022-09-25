/****************************************************************************************
* 文件名：LOADBIT.C
* 功能：显示单色图形及汉字显示。先将图形转换为对应的点阵数组，然后即可调用此文件的函数输出驱动。
* 作者：黄绍斌
* 日期：2004.02.26
* 备注：使用GUI_SetBackColor()函数设置显示颜色及背景色。
****************************************************************************************/
#include  "..\Head\system.h"
#include	<stdarg.h>
#include	<string.h>

extern void lcdRectRefresh(unsigned int uiX0, unsigned int uiY0, unsigned int uiX1, unsigned int uiY1);
INT32U __GuiFontAddr;

#if  (GUI_LoadPic_EN==1)|(GUI_MenuIco_EN==1)|(GUI_PutHZ_EN==1)
/****************************************************************************
* 名称：GUI_LoadLine()
* 功能：输出单色图形的一行数据。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
*           dat		要输出显示的数据。
*           no      要显示此行的点个数
* 出口参数：返回值为1时表示操作成功，为0时表示操作失败。
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
uint8  GUI_LoadLine(uint32 x, uint32 y, uint8 *dat, uint32 no)
{  uint8   bit_dat;
   uint8   i;
   TCOLOR  bakc;

   /* 参数过滤 */
   if(x>=GUI_LCM_XMAX) return(0);
   if(y>=GUI_LCM_YMAX) return(0);
   
   for(i=0; i<no; i++)
   {  /* 判断是否要读取点阵数据 */
      if( (i%8)==0 ) bit_dat = *dat++;
     
      /* 设置相应的点为color或为back_color */
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
* 名称：GUI_LoadPic()
* 功能：输出单色图形数据。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
*           dat		要输出显示的数据
*           hno     要显示此行的点个数
*           lno     要显示此列的点个数
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
void  GUI_LoadPic(uint32 x, uint32 y, uint8 *dat, uint32 hno, uint32 lno)
{  
    uint32  i;
    uint32 y_temp = y;
    for(i=0; i<lno; i++) {  
        GUI_LoadLine(x, y_temp, dat, hno);				// 输出一行数据
        y_temp++;										// 显示下一行
        dat += (hno>>3);							// 计算下一行的数据
        if ((hno & 0x07) != 0) 
            dat++;
    }
#if __DISPLAY_ON_EN > 0
   lcdRectRefresh(x, y, x + hno, y + lno); 
#endif
}




/****************************************************************************
* 名称：GUI_LoadPic1()
* 功能：输出单色图形数据，反相显示。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
*           dat		要输出显示的数据。
*           hno     要显示此行的点个数
*           lno     要显示此列的点个数
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
void  GUI_LoadPic1(uint32 x, uint32 y, uint8 *dat, uint32 hno, uint32 lno)
{  uint32  i;
   
   GUI_ExchangeColor();									// 显示色与背景色交换
   for(i=0; i<lno; i++)
   {  GUI_LoadLine(x, y, dat, hno);						// 输出一行数据
      y++;												// 显示下一行
      dat += (hno>>3);									// 计算下一行的数据
      if( (hno&0x07)!=0 ) dat++;
   }
   GUI_ExchangeColor();
   
}
#endif


#if  GUI_PutHZ_EN==1
/****************************************************************************
* 名称：GUI_PutHZ()
* 功能：显示汉字。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
*           dat		要输出显示的汉字点阵数据。
*           hno     要显示此行的点个数
*           lno     要显示此列的点个数
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
void  __GUI_PutHZ(uint32 x, uint32 y, uint8 *dat, uint8 hno, uint8 lno)
{  uint8  i;

   for(i=0; i<lno; i++)
   {  GUI_LoadLine(x, y, dat, hno);						// 输出一行数据
      y++;												// 显示下一行
      dat += (hno>>3);									// 计算下一行的数据
      if( (hno&0x07)!=0 ) dat++;
   }
}
#endif



/*********************************************************************************************************
** 函数名称: GUI_PutHZ
** 功能描述: 输出一个字符
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
void GUI_PutHZ(unsigned int uiX, unsigned int uiY, unsigned char *pucDat)
{
    unsigned char *pucFontAddr;
    unsigned char ucBuf[32];
    
    if (*pucDat < 128) {                                                /*  ASCII码                     */                                
        #if 0
        pucFontAddr = (unsigned char *)__GuiFontAddr + 
                       (*pucDat - 0x20) * FONT_YSIZE16 * 2;
        #else
        pucFontAddr = (unsigned char *)FONT8x16ASCII +
                       (*pucDat - 0x20) * FONT_YSIZE16;
        #endif
        /*
         *  2013.02.01修改
         *  ASCII码显示数据从16*16点阵中抽取         
         */
        #if 0
        for (uiOffset = 0; uiOffset < FONT_YSIZE16; uiOffset++) {
            
                ucBuf[uiOffset] = pucFontAddr[uiOffset * 2]; 
        }
        #else
        memcpy(ucBuf, pucFontAddr , ( FONT_YSIZE16 * FONT_XSIZE8 / 8));
        #endif
        __GUI_PutHZ(uiX, uiY, ucBuf, FONT_XSIZE8, FONT_YSIZE16); 
                
    } else {                                                            /*  汉字                        */
        
        
        pucFontAddr = (unsigned char *)__GuiFontAddr; 
                    //+ 0x60 * FONT_YSIZE16; 
        #if 0
        /*
         *  字库做了精简，调整偏移量的计算 by xuwl
         */
        if (pucDat[0] >= 0xb0 ) {
            pucFontAddr += ((pucDat[0] - 0xA0 - 1 - 6)*94+(pucDat[1] - 0xA0-1))*
                            ( FONT_XSIZE16 * FONT_YSIZE16 / 8);
        } else {                                                        /*  中文符号                    */
            pucFontAddr += ((pucDat[0] - 0xA0-1)*94+(pucDat[1] - 0xA0-1))*
                            ( FONT_XSIZE16 * FONT_YSIZE16 / 8);     
        }
        
        #else
        pucFontAddr += ((pucDat[0] - 0xA0-1)*94+(pucDat[1] - 0xA0-1))*
                        ( FONT_XSIZE16 * FONT_YSIZE16 / 8);          
        #endif
        
             
        
        
        memcpy(ucBuf, pucFontAddr , FONT_XSIZE16 * FONT_YSIZE16 / 8);
        //*(unsigned short *)&ucBuf[16] = *(unsigned short *)(pucFontAddr + 16);    
        __GUI_PutHZ(uiX, uiY, ucBuf, FONT_XSIZE16 ,FONT_YSIZE16);           //输出中文字
    }    
}
#if 0
/*********************************************************************************************************
** 函数名称: GUI_DispStringH
** 功能描述: 在指定位置水平输出一串字符
** 输　入:  ucX:x坐标;
**          ucY:y坐标
**          str:字符串
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
void GUI_DispStringH(unsigned char ucX, unsigned char ucY, unsigned char *str)
{
  
    while(1)
    {  
        if( (*str)=='\0' ) break;
     
        if(*str > 127) {                                                /*  中文字体                    */
            GUI_PutHZ(ucX, ucY, str);
            str += 2;  
            ucX += FONT_XSIZE16; 
        } else {
            GUI_PutHZ(ucX, ucY, str);
            str += 1;
            ucX += FONT_XSIZE8;                                         /*  西文字体                    */
        } 
    }
#if __DISPLAY_ON_EN > 0
    lcdRefresh();
#endif
}
#endif
/*********************************************************************************************************
** 函数名称: GUI_DispStringH
** 功能描述: 在指定位置输出一串字符
** 输　入:  ucX:x坐标;
**          ucY:y坐标;
**          ucIsAnti:反显标志
**          str:字符串
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
        if ((*pStr == '\n') || (*pStr == '\r')) {                       /*  回车或换行符                */
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
        if (*pStr == 0)                                                 /*  结束符                      */
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
** 函数名称: GUI_Printf
** 功能描述: 在指定位置输出一串字符
** 输　入:  ucX:x坐标;
**          ucY:y坐标;
**          ucIsAnti:反显标志
**          pcFmt:格式化字符串
** 输　出:      无
** 全局变量:    无
** 调用模块: 
**
** 作　者: 徐伟林
** 日　期: 2010年7月10日
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
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
