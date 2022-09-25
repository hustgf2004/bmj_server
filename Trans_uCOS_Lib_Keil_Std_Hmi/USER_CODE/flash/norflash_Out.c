#include "main.h" 
extern INT32S __sysWordProgramEx(uint32 Addr, uint16 Data); 
extern INT32S __sysSectorEraseEx(uint32 Index); 

/*********************************************************************************************************
** Function name:       WordProgram
** Descriptions:        字编程
** input parameters:    地址，数据
** output parameters:   none
** Returned value:      是否成功               
*********************************************************************************************************/
INT32S sysWordProgramEx(uint32 Addr, uint16 Data) 
{
    return __sysWordProgramEx(Addr, Data);
}  
/*********************************************************************************************************
** Function name:       SectorErase
** Descriptions:        扇区擦除
** input parameters:    扇区号
** output parameters:   none
** Returned value:      是否成功               
*********************************************************************************************************/
                     
INT32S sysSectorEraseEx(uint32 Index) 
{
    return __sysSectorEraseEx(Index); 
}


/*********************************************************************************************************
**                            End Of File
*********************************************************************************************************/
