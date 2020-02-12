#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "src/config.h"
#include "src/core/prime.h"

UINT32 enroll(UINT16 nID)
{
    unsigned short resdata = 0;
    unsigned int rv = 0;
    unsigned char data[256] = {0};
    int i = 0;
    printf("------test FingeEnroll!------\n");
    memset(data, 0, 256);
    rv = prime_enroll(nID);
    printf("------rv = %d---resdata = %d---\n", rv, resdata);   
    printf("====>press finger====>\n");
    do
    {
        rv = prime_getstatus();
        if (rv==PRIME_STATUS_IDLE)
        {
             continue;
        }

        switch (resdata)
        {

        case PRIME_STATUS_GOOD:
            printf("#####success +1 #####\n");
            printf("====>press finger====>\n");
            break;
        case PRIME_STATUS_TIMEOUT:
            printf("#####time out #####\n");
            return resdata;
#ifdef DETAIL_INFO
        case PRIME_STATUS_WAIT:
            printf("=====>press finger=====>\n");
            break;
        case PRIME_STATUS_BAD:
            printf("#####bad image #####\n");
            break;
        case PRIME_STATUS_PART:
            printf("#####part image#####\n");
            break;
        case PRIME_STATUS_QUICK:
            printf("#####press too quick#####\n");
            break;
        case PRIME_STATUS_REDUNANT:
            printf("#####repeat part#####\n");
            break;
        case PRIME_STATUS_WERID:
            printf("#####werid image#####\n");
            break;  
#endif 
        case PRIME_OK:
            printf("#####finish#####\n");
            break; 
        default:
            break;
        }
        usleep(10000);
    } while (resdata);
    printf("------rv = %d---resdata = %d---\n", rv, resdata);

    return resdata;
}

UINT32 identify()
{
    unsigned short resdata = 0;
    unsigned int rv = 0;
    int i = 0;
    UINT16 nID = 0;
    UINT16 score = 0;
    printf("------test FingerUserIdentify!------\n");
    printf("====>press finger====>\n");
    rv = prime_identify();
    switch (rv)
    {
    case PRIME_STATUS_MATCH:
        printf("####matched nID=%d score=%d####\n",nID,score);
        break;
    case PRIME_STATUS_NOT_MATCH:
        printf("####not match####\n");
        break;
    case PRIME_STATUS_TIMEOUT:
        printf("####time out####\n");
        break;
    
    default:
        printf("####other errors %d####\n", resdata);
        break;
    }
    return resdata;
}
int main(void)
{
    enroll(0);
    identify();
    return 0;
}
