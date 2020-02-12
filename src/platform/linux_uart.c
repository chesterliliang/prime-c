#include <stdio.h>
#include <fcntl.h>   /* File Control Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h>  /* UNIX Standard Definitions 	   */
#include <errno.h>   /* ERROR Number Definitions           */
#include "linux_uart.h"

int g_dev = 0;
#define PRIME_PRINT

int uart_init(int *dev)
{
    int fd; 

    fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NONBLOCK); 
    if (fd < 0) /* Error Checking */
    {
#ifdef PRIME_PRINT  
        printf("\n  Error! in Opening ttyUSB0  \n");
#endif
        return 0;
    }
    else
    {
#ifdef PRIME_PRINT 
        printf("\n  ttyUSB0 Opened Successfully \n");
#endif 
    }
    /*RX init*/
    struct termios SerialPortSettings; /* Create the structure                          */

    tcgetattr(fd, &SerialPortSettings); /* Get the current attributes of the Serial port */

    /* Setting the Baud rate */
    cfsetispeed(&SerialPortSettings, B57600); /* Set Read  Speed as 57600                       */
    cfsetospeed(&SerialPortSettings, B57600); /* Set Write Speed as 57600                       */
    /* 8N1 Mode */
    SerialPortSettings.c_cflag &= ~PARENB; /* Disables the Parity Enable bit(PARENB),So No Parity   */
    SerialPortSettings.c_cflag &= ~CSTOPB; /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
    SerialPortSettings.c_cflag &= ~CSIZE;  /* Clears the mask for setting the data size             */
    SerialPortSettings.c_cflag |= CS8;     /* Set the data bits = 8                                 */

    SerialPortSettings.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
    SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */

    SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);         /* Disable XON/XOFF flow control both i/p and o/p */
    SerialPortSettings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); /* Non Cannonical mode                            */

    SerialPortSettings.c_oflag &= ~OPOST; /*No Output Processing   raw  format  output*/

    /* Setting Time outs */
    SerialPortSettings.c_cc[VMIN] = 0;  /* Read at least 10 characters */
    SerialPortSettings.c_cc[VTIME] = 1; /* Wait indefinetly   */

    if ((tcsetattr(fd, TCSANOW, &SerialPortSettings)) != 0) /* Set the attributes to the termios structure*/
        printf("\n  ERROR ! in Setting attributes");
    //else
    //    printf("\n  BaudRate = 57600 \n  StopBits = 1 \n  Parity   = none");

    /*------------------------------- Read data from serial port -----------------------------*/

    tcflush(fd, TCIFLUSH); /* Discards old data in the rx buffer            */

    *dev = fd;

    return 1;
}

int uart_write(unsigned char *data, int len)
{
    int i = 0;
    int rv = 0;
    if(g_dev==0||g_dev<0)
    {
#ifdef PRIME_PRINT  
         printf("---------init--g_dev=%d------\n",g_dev);
#endif
        rv = uart_init(&g_dev);
        if(rv==0)
        {
            printf("---------init- fail-g_dev=%d------\n",g_dev);
            return 0;
        }
            
    }
#ifdef PRIME_PRINT    
    printf("--------write-----------\n");
    printf("len = %d \n", len);
    for(i=0;i<len;i++)
        printf("0x%x ", data[i]);
#endif
    rv = write(g_dev, data, len);
#ifdef PRIME_PRINT
    printf("\n------------rv=%d-------------\n",rv);
#endif
    return rv;
     
}

int uart_read(unsigned char *data, int len)
{
    int rv = 0;
    int i = 0;
    int len_get = 0;
    int counter = 0;
    if(g_dev==0||g_dev<0)
    {
        printf("---------init--g_dev=%d------\n",g_dev);
        rv = uart_init(&g_dev);
        if(rv==0)
        {
            printf("---------init- fail-g_dev=%d------\n",g_dev);
            return 0;
        }
            
    }
    rv = read(g_dev, data, len);
    if(rv<0)
    {
#ifdef PRIME_PRINT  
      //   printf("---------read error------\n");
#endif
         return rv;
    }
       
   

    //if not all the data, wait until get all
    len_get = len_get+rv;
    while(len_get<len)
    {
        usleep(10000);
        rv = read(g_dev, data+len_get, len-len_get);
        len_get = len_get+rv;
        printf("----------!multi part!------------\n");
        counter++;
        if(counter>5)
            return -1;
    }
#ifdef PRIME_PRINT
    printf("---------read----rv=%d--------\n",rv);
    printf("len = %d \n", len_get);
    for(i=0;i<len;i++)
        printf("0x%x ", data[i]);
    printf("\n------------rv=%d-------------\n",rv);
#endif
    return rv;
}

int uart_close()
{
    close(g_dev);
}


