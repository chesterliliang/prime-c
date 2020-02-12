#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "BHZ1_def.h"
#include "BHZ1Finger.h"

UINT32 test_calibrate(void)
{
    unsigned int resdata = 0;
    unsigned int rv = 0;
    //calibrate
    printf("------test Bhz1FingerCalibrate!------\n");
    rv = Bhz1FingerCalibrate(NULL, &resdata);
    printf("------rv = %d---resdata = %d---\n", rv, resdata);
    return resdata;
}



UINT32 test_delete(UINT16 nID)
{
    unsigned short resdata = 0;
    unsigned int rv = 0;
    unsigned char data[256] = {0};

    printf("------test BHZ1FingerUserDelete!------\n");
    memset(data, 0, 256);
    rv = Bhz1FingerDeleteTemplate(NULL, &nID, &resdata);
    printf("------rv = %d---resdata = %d---\n", rv, resdata);
    return resdata;
}

UINT32 test_Bhz1FingerGetTemplateNum(void)
{
    unsigned short resdata = 0;
    unsigned int rv = 0;
    unsigned short data;
    int i = 0;

    printf("------test Bhz1FingerGetTemplateNum!------\n");
    rv = Bhz1FingerGetTemplateNum(NULL,&data, &resdata);
    printf("------rv = %d-sum %d--resdata = %d---\n", rv,data, resdata);
    return resdata;
}

//#define DETAIL_INFO
UINT32 test_enroll(UINT16 nID)
{
    unsigned short resdata = 0;
    unsigned int rv = 0;
    unsigned char data[256] = {0};
    int i = 0;
    printf("------test BHZ1FingeEnroll!------\n");
    memset(data, 0, 256);
    rv = Bhz1FingerEnroll(NULL, &nID, &resdata);
    printf("------rv = %d---resdata = %d---\n", rv, resdata);
    if (resdata == PRIME_ERROR_COMM)
    {
        return resdata;
    }
    printf("====>press finger====>\n");
    do
    {
        rv = Bhz1FingerStatus(NULL, &resdata);
        if (resdata==PRIME_STATUS_IDLE)
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

UINT32 test_identify()
{
    unsigned short resdata = 0;
    unsigned int rv = 0;
    int i = 0;
    UINT16 nID = 0;
    UINT16 score = 0;
    printf("------test BHZ1FingerUserIdentify!------\n");
    printf("====>press finger====>\n");
    rv = Bhz1FingerIdentify(NULL,&nID, &score,&resdata);
    switch (resdata)
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

void main(void)
{

    test_Bhz1FingerGetTemplateNum();
    test_delete(0);
    test_Bhz1FingerGetTemplateNum();
    assert(test_enroll(0)== PS_OK);
    test_Bhz1FingerGetTemplateNum();
    assert(test_identify() == PS_OK);
}