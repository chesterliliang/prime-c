#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "config.h"
#include "prime.h"

UINT32 enroll(UINT16 nID)
{
    unsigned int rv = 0;
    unsigned char data[256] = {0};
    int i = 0;
    printf("------test FingeEnroll!------\n");
    memset(data, 0, 256);
    rv = prime_enroll(nID);
    printf("------rv = %d---\n", rv);   
    printf("====>press finger====>\n");
    do
    {
        rv = prime_getstatus();
        if (rv==PRIME_STATUS_IDLE)
        {
             continue;
        }
        //printf("====>prime_getstatus tv %d ====>\n", rv);
        switch (rv)
        {

        case PRIME_STATUS_GOOD:
            printf("#####success +1 #####\n");
            printf("====>press finger====>\n");
            break;
        case PRIME_STATUS_TIMEOUT:
            printf("#####time out #####\n");
            return PRIME_STATUS_TIMEOUT;
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
    } while (rv);
    printf("------rv = %d-----\n", rv);

    return 0;
}

void identify()
{
    unsigned int rv = 0;
    int i = 0;
    UINT16 nID = 0;
    printf("------test FingerUserIdentify!------\n");
    rv = prime_identify();
    printf("------rv = %d---\n", rv);   
    printf("====>press finger====>\n");
    do{
        rv = prime_getstatus();
        //printf("====>prime_getstatus tv %d ====>\n", rv);
        switch (rv)
        {
            case PRIME_STATUS_MATCH:
                printf("####matched nID=%d ####\n",nID);
                return;
            case PRIME_STATUS_NOT_MATCH:
                printf("####not match####\n");
                return;
            case PRIME_STATUS_TIMEOUT:
                printf("####time out####\n");
                return;
            default:
                break;
         }
    }while(1);

}

void verifypin(void)
{
    unsigned int rv = 0;
    int i = 0;
    UINT16 nID = 0;
    UINT16 score = 0;
    printf("------verifypin!------\n");
    rv = prime_verifypin((UINT8*)"88888888",8);
    printf("rv = %d\n",rv);
}
int main(void)
{
    //verifypin();
    enroll(0);
    identify();
    return 0;
}
