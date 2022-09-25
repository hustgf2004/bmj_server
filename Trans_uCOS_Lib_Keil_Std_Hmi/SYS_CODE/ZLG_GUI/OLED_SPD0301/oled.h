/****************************************Copyright (c)****************************************************
**                               
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           LCDDRIVE.h
** Last modified Date:  2012-12-31
** Last Version:        1.0
** Descriptions:        ZLGGUI的底层驱动头文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:          
** Created date:        2012-12-31
** Version:             1.0
** Descriptions:        ZLGGUI的底层驱动头文件
**
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:             
** Descriptions:        
*********************************************************************************************************/
#ifndef  OLED_H
#define  OLED_H

#define  GUI_CopyColor(color1, color2) 	*color1 = color2

extern void lcdSetPos(unsigned char ucX, unsigned char ucY);

extern void lcdFillAll(unsigned char dat);

extern void lcdClr(unsigned char ucClr);

extern void lcdSetPixel(unsigned char ucX, unsigned char ucY, unsigned char ucClr);
extern unsigned char lcdGetPixel (unsigned char ucX, unsigned char ucY);

extern void lcdDrawBmp (int ix0, 
                 int iy0,
                 int iwidth, 
                 int ilength,
                 unsigned short *pucBmp);
extern void lcdInit(void);
extern void lcdRefresh(void);
#endif
                 