#include "def.h"
#include "uart.h"

UINT32 prime_uart_write(
    UINT8    *data,
    UINT16    len
)
{
#if (_PRIME_PLATFORM== _PRIME_LINUX_)
    UINT32 rv = 0;
    rv = uart_write(data,len);
    if(rv>0)
        return PRIME_OK;
    else
        return PRIME_ERROR_COMM;
#elif (_PRIME_PLATFORM== _PRIME_BIOS_SIMU_LINUX_)
    UINT32 rv = 0;
    rv = SerialPort2Write(data,len);
    if(rv==0)//rv differ from the linux api
        return PRIME_OK;
    else
        return PRIME_ERROR_COMM;
#endif

}

UINT32 prime_uart_read(
    UINT8    *data,
    UINT16    len
)
{
#if (_PRIME_PLATFORM== _PRIME_LINUX_)
    UINT32 rv = 0;
    rv = uart_read(data,len);
    if(rv>0)
        return PRIME_OK;
    else
        return PRIME_ERROR_COMM;
#elif (_PRIME_PLATFORM== _PRIME_BIOS_SIMU_LINUX_)
    UINT32 rv = 0;
    rv = SerialPort2Read(data,len);
    if(rv==0)//rv differ from the linux api
        return PRIME_OK;
    else
        return PRIME_ERROR_COMM;
#endif
}