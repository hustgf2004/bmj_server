/****************************************Copyright (c)****************************************************
**                  
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               PinCfg.c
** Latest modified Date:    2010-12-13
** Latest Version:          1.0
** Descriptions:            I/O���������ļ� 
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            2010-12-13
** Version:                 1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
*********************************************************************************************************/
#include "..\..\..\SYS_CODE\Head\system.h"
#include ".\LPC2200PinCfg.h"


/*********************************************************************************************************
** Function name:           pinInit
** Descriptions:            I/O���ܳ�ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              
** Created date:            2010-12-13
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
void pinInit(void)
{
    /* ������������ */
    
    //P0.00 -- P0.15
    PINSEL0  = (P0_15_FUNC <<30)|(P0_14_FUNC <<28)|(P0_13_FUNC <<26)|(P0_12_FUNC <<24)|
               (P0_11_FUNC <<22)|(P0_10_FUNC <<20)|(P0_09_FUNC <<18)|(P0_08_FUNC <<16)|
               (P0_07_FUNC <<14)|(P0_06_FUNC <<12)|(P0_05_FUNC <<10)|(P0_04_FUNC << 8)|
               (P0_03_FUNC << 6)|(P0_02_FUNC << 4)|(P0_01_FUNC << 2)|(P0_00_FUNC << 0);
    
    //P0.16 -- P0.31
    PINSEL1  = (P0_31_FUNC <<30)|(P0_30_FUNC <<28)|(P0_29_FUNC <<26)|(P0_28_FUNC <<24)|
               (P0_27_FUNC <<22)|(P0_26_FUNC <<20)|(P0_25_FUNC <<18)|(P0_24_FUNC <<16)|
               (P0_23_FUNC <<14)|(P0_22_FUNC <<12)|(P0_21_FUNC <<10)|(P0_20_FUNC << 8)|
               (P0_19_FUNC << 6)|(P0_18_FUNC << 4)|(P0_17_FUNC << 2)|(P0_16_FUNC << 0);
               
    
    
    
    // BOOT[1:0]��������λ
    if ((PINSEL2 & (0x03<<4))!= (0x02 << 4)) {
        if(P3_29_FUNC == 0)
            PINSEL2 &= ~(1<<6);         
        else 
            PINSEL2 |= (1<<6);          
            
        if(P3_28_FUNC == 0)
            PINSEL2 &= ~(1<<7);         
        else
            PINSEL2 |= (1<<7);              
            
        PINSEL2 &= ~(1<<20);            
            
        if(P2_30_FUNC == 0)
            PINSEL2 &= ~(1<<21);        
        else 
            PINSEL2 |= (1<<21);     
            
        if(P2_31_FUNC == 0)
            PINSEL2 &= ~(1<<22);        
        else
            PINSEL2 |= (1<<22);
            
        /*
         *  by xuwl P3.25-CS2 P3.24-GPIO
         */

        if (P3_25_FUNC == 0)
            PINSEL2 &= ~(3 << 14);
        else {
           PINSEL2 = (PINSEL2 & (~(3 << 14)) | (1 << 14));
        }
        if (P3_24_FUNC == 0)
            PINSEL2 &= ~(3 << 16);
        else {
            PINSEL2 = (PINSEL2 & (~(3 << 16)) | (1 << 16));
        }
        if (P3_26_FUNC == 0) {
            PINSEL2 &= ~(1 << 11);
        } else {
            PINSEL2 |= (1 << 11);
        }
        if (P3_27_FUNC == 0) {
            PINSEL2 &= ~(1 << 8);
        } else {
            PINSEL2 |= (1 << 8);
        }     
    }
    
        
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

