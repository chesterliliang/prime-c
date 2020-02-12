# How to get started with the code
## 1.Directory struct
```
.
|--src
    |--core //logic code to access the module.
    |--platform //uart api on diff platform
|--examples //projects example
|--doc //necessary docs
|--tools //tools for test
|--test //test vectors
|--readme.md

```

## 2.Build
```
git clone https://github.com/chesterliliang/prime-c-lib.git

make
```

If you can run the code binary on you platform, here is the reference:
```
./test
```
or
```
sudo ./test
```
Check UART device on Linux
```
dmesg | grep ttyS*
```

## 3. Re-config and implement on your own platform

To re-config the project, src/config.h should be modified first

```
//from
//current config  
#define _PRIME_PLATFORM     _PRIME_BIOS_SIMU_LINUX_    


//to
#define _PRIME_PLATFORM     _PRIME_<your platform>_
```

Then goto platform directory and add you own implementation of the UART on your own platform. Such as create <your project>_uart.c. 

```
//functions like 
uart_init
uart_write
uart_read
uart_close
```
should be implement here. Note that, init and close function should be include in write/read function. Because the final interface to core will be 

```
...
UINT32 prime_uart_write(
    UINT8    *data,
     UINT16    len
);

UINT32 prime_uart_read(
    UINT8    *data,
    UINT16    len
);
...
```
in src/core/uart.c

Macros defined in config.h will be used in two files.
```
//1. src/core/def.h
..
#include "../platform/linux_uart.h"
#include <unistd.h> //sleep
#include <string.h> //memcpy
#elif (_PRIME_PLATFORM== _PRIME_BIOS_SIMU_LINUX_)
#include "../project/BHZ1/BHZ1_def.h"
#include "../platform/bios_serial.h"
#include <unistd.h> //sleep
#include <string.h> //memcpy
#endif
```
Your platform Macro should be added here. The code also need the header file of sleep() and memcpy() in you platform

```
//2.src/core/uart.c
...
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
...
```
Your uart API should be here and with the Macro confition.

## 4. Customization the API

Fisrt we change the config as we do in platform part.
```
//from
//current config
#define _PRIME_PROJECT      _PRIME_BHZ1_     

//to
#define _PRIME_PROJECT      _PRIME_<your project>_     
```
Then mkdir in project folder as <your_project_name>. You could copy the makefile to from sample project folder to your folder. It contains most of the setting. You just need change the test part.

With the including of the src/core/ files
```
#include "../../core/def.h"
#include "../../core/prime.h"
```
Your API could be done with prime_*** functions. And you could write your test code the run it.

## 4. DEBUG DEFINE

To monitor the UART command, open PRIME_PRINT in linux_uart.c
TO get detail enroll status, open DETAIL_INFO in test.c

## 5. master and sync

master branch is the interrupt mode of UART. When sent cmd to device, code read the host buffer to get response
sync branch is the loop mode of UART. Enroll and verify cmd use getstate cmd to pull the response.

## 6. Trouble Shooting

Submit issues on github.
