/////////////////////////////////////////////////////////////
/*
*   TODO TODO TODO
*   Re-implement the file!!!!!!!!!!!
*   We don't know how and just let it based on linux api
*   EFAPI AND UINTN is kept for your convinient
*/


#include "../core/def.h"
#include "../project/BHZ1/BHZ1_def.h"
#include "linux_uart.h"

UINTN EFIAPI SerialPort2Write(
    IN UINT8    *Buffer,
    IN UINTN    NumberOfBytes
)
{
    int rv = 0;
    rv = uart_write(Buffer,NumberOfBytes);
    if(rv>0)
        return 0;// OK
    else
        return 1;// fail
    
}

UINTN EFIAPI SerialPort2Read(
    IN UINT8    *Buffer,
    IN UINTN    NumberOfBytes
)
{
    int rv = 0;
    rv = uart_read(Buffer,NumberOfBytes);
    if(rv>0)
        return 0;//OK
    else
        return 1;//fail
}