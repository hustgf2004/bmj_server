/****************************************Copyright (c)**************************************************
**                               
**                                      
**                                 
**
**--------------File Info-------------------------------------------------------------------------------
** File name:           MB_USER_Data.c
** Last modified Date:  2013-11-30
** Last Version:        2.0
** Descriptions:        
**
**------------------------------------------------------------------------------------------------------
** Created by:          
** Created date:        
** Version:             
** Descriptions:        
**
**------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:             
** Descriptions:
**
********************************************************************************************************/
#include "..\..\..\USER_CODE\main.h"

#if 1
/*******************************************************************************************************
//
// 用户编写操作寄存器接口函数
//
********************************************************************************************************/


uint8 AppDiscTbl[30];
uint8 AppKey1;
uint8 AppKey2;
uint8 AppKey3;


//#define KEY1   (1 << 20)
//#define KEY2   (1 << 22)

#define     BUZZER                  P0_21               // P0.21控制蜂鸣器，低电平蜂鸣

#define     BUZZER_Set()            gpioSet(BUZZER)     // 开蜂鸣器
#define     BUZZER_Clr()            gpioClr(BUZZER) 


/*********************************************************************************************************
** Function name:           MB_GetDiscrete
**
** Descriptions:            获取离散值函数，该函数由用户编写
**
** input parameters:        ch,Modbus管道号
**                          DisInputsV，保存离散输入量值指针
**                          Address，线圈地址
** Returned value:          正常返回MB_NO_ERR,出错返回ILLEGAL_DATA_ADDR，或SLAVE_DEVICE_FAILURE。
**         
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
uint8 MB_GetDiscrete (uint8 ch,uint8 *DisInputsV,uint16 Address)
{
    uint8 err;
    err = MB_NO_ERR;
    
    switch (Address) {
    case 200:
        *DisInputsV = (IO0PIN & KEY1) ? 1:0;            // 读取按键值   
        break;
    case 201:
        *DisInputsV = (IO0PIN & KEY2) ? 1:0;            // 读取按键值   
        break;
    default:
        err = ILLEGAL_DATA_ADDR;
        break;
    }
    return (err);

}

uint8 AppCoilTbl[100];
uint8 AppStatus;
uint8 AppRunning;
uint8 AppLED;
/*********************************************************************************************************
** Function name:           MB_GetCoils
**
** Descriptions:            获取线圈值函数，该函数由用户编写
**
** input parameters:        ch,Modbus管道号
**                          CoilVPtr，保存线圈值指针
**                          Address，线圈地址
** Returned value:          正常返回MB_NO_ERR,出错返回ILLEGAL_DATA_ADDR，或SLAVE_DEVICE_FAILURE。
**         
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
uint8 MB_GetCoils (uint8 ch,uint8 *DisInputsV,uint16 Address)
{
    uint8 err;
    uint8 ix;
    uint8 bit_nbr;
    err = MB_NO_ERR;
    
    if (Address < 100 * sizeof(uint8)) {
        ix = (uint8)(Address / 8);
        bit_nbr = (uint8)(Address % 8);
        *DisInputsV =(uint8)((AppCoilTbl[ix] & (1 << bit_nbr))?1:0); 
        
    } else  {
        switch (Address) {
        case 200:
            *DisInputsV = (uint8)(AppStatus?1:0);
            break;
        case 201:
            *DisInputsV = (uint8)(AppRunning?1:0);
            break;
        case 202:
            *DisInputsV = (uint8)(AppLED?1:0);
            break;
        default:
            err = ILLEGAL_DATA_ADDR;
            break;
        }
    }
    return (err);
}


/*********************************************************************************************************
** Function name:           MB_SetCoil
**
** Descriptions:            设置线圈值函数，该函数由用户编写
**
** input parameters:        ch,Modbus管道号
**                          Address，线圈地址
**                          CoilValue,线圈值（0\1）
** Returned value:          正常返回MB_NO_ERR,出错返回ILLEGAL_DATA_ADDR，或SLAVE_DEVICE_FAILURE。
**         
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
uint8 MB_SetCoil(uint8 ch,uint16 Address,uint8 CoilValue)
{
    uint8 err;
    uint8 ix;
    uint8 bit_nbr;
    err = MB_NO_ERR;
    if (Address < 100 * sizeof(uint8)) {
        ix = (uint8)(Address / 8);
        bit_nbr = (uint8)(Address % 8);
        if(CoilValue)
            AppCoilTbl[ix] |= (1 << bit_nbr);
        else
            AppCoilTbl[ix] &= ~(1 << bit_nbr);
    } else  {
        switch (Address) {
        case 200:
            if ( CoilValue ) {
                BUZZER_Set(); 
              
            } else {
                BUZZER_Clr(); 
            }

            break;
        case 201:
            AppRunning = (uint8)(CoilValue?1:0);
            break;
        case 202:
            AppLED = (uint8)(CoilValue?1:0);
            break;
        default:
            err = ILLEGAL_DATA_ADDR;
            break;
        }
    }
    return (err);
}

#define END_INPUT_REG_ADDR  150
uint16 InputBuffer[END_INPUT_REG_ADDR];
uint16 AppAD0;
uint16 AppAD1;
uint16 AppAD2;
/*********************************************************************************************************
** Function name:           MB_GetInputRegValue
**
** Descriptions:            读输入寄存器值函数，该函数由用户编写
**
** input parameters:        ch,Modbus管道号
**                          *ValuePtr，保存输入寄存器值的指针
**                          Address，寄存器地址
** Returned value:          正常返回MB_NO_ERR,出错返回ILLEGAL_DATA_ADDR，或SLAVE_DEVICE_FAILURE。
**         
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
uint8 MB_GetInputRegValue(uint8 ch,uint16 *ValuePtr,uint16 Address)
{
    uint8 err;
    err = MB_NO_ERR;
    if (Address < END_INPUT_REG_ADDR) {
        *ValuePtr = InputBuffer[Address];
    } else  {
        switch (Address) {
        case 3000:
            *ValuePtr = AppAD0;
            break;
        case 3001:
            *ValuePtr = AppAD1;
            break;
        case 3002:
            *ValuePtr = AppAD2;
            break;
        default:
            err = ILLEGAL_DATA_ADDR;
            break;
        }
    }
    return (err);
}


#define END_HOLDING_REG_ADDR 150
uint16 RegValueBuffer[END_HOLDING_REG_ADDR];
/*********************************************************************************************************
** Function name:           MB_GetRegValue
**
** Descriptions:            读保持寄存器值函数，该函数由用户编写
**
** input parameters:        ch,Modbus管道号
**                          *ValuePtr，保存获取寄存器的值的指针
**                          Address，寄存器地址
** Returned value:          正常返回MB_NO_ERR,出错返回ILLEGAL_DATA_ADDR，或SLAVE_DEVICE_FAILURE。
**         
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
uint8 MB_GetRegValue(uint8 ch,uint16 *ValuePtr,uint16 Address)
{
    if(Address < END_HOLDING_REG_ADDR) {
        *ValuePtr = RegValueBuffer[Address] ;
        return MB_NO_ERR;
    } else {
        return ILLEGAL_DATA_ADDR;
    }
}


/*********************************************************************************************************
** Function name:           MB_SetRegValue
**
** Descriptions:            写保持寄存器值函数，该函数由用户编写
**
** input parameters:        ch,Modbus管道号
**                          Address，寄存器地址
**                          Value，写入的值
** Returned value:          正常返回MB_NO_ERR,出错返回ILLEGAL_DATA_ADDR，或SLAVE_DEVICE_FAILURE。
**         
** Created by:              
** Created Date:            2013/11/30
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
uint8 MB_SetRegValue(uint8 ch,uint16 Address,uint16 Value)
{
    if (Address < END_HOLDING_REG_ADDR) {
        RegValueBuffer[Address] = Value;
        return MB_NO_ERR;
    } else {
        return ILLEGAL_DATA_ADDR;
    }
}

#endif
/****************************************************************************************************************/
// File end
/****************************************************************************************************************/
