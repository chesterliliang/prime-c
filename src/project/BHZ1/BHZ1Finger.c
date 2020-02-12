#include "BHZ1_def.h"
#include "../../core/def.h"
#include "../../core/prime.h"
#include "BHZ1Finger.h"

EFI_STATUS
EFIAPI
Bhz1FingerEnroll(
IN EFI_R301FINGERIO_PROTOCOL *This,
    IN UINT16 *PageID,
    OUT UINT16 *Respond
)
{
    *Respond =prime_enroll(*PageID);
    return *Respond==PRIME_ERROR_COMM?PS_COMM_ERR:PS_OK;
}

EFI_STATUS
EFIAPI
Bhz1FingerState(
    IN EFI_R301FINGERIO_PROTOCOL *This,
    OUT UINT16 *Respond
)
{
    *Respond = prime_getstate();
    //return *Respond;
    return *Respond==PRIME_ERROR_COMM?PS_COMM_ERR:PS_OK;
}

EFI_STATUS
EFIAPI
Bhz1FingerStatus(
    IN EFI_R301FINGERIO_PROTOCOL *This,
    OUT UINT16 *Respond
)
{
    *Respond = prime_getstatus();
    return *Respond;
    //return *Respond==PRIME_ERROR_COMM?PS_COMM_ERR:PS_OK;
}


EFI_STATUS
EFIAPI
BHZ1FingerAbort(
    IN EFI_R301FINGERIO_PROTOCOL *This,
    OUT UINT16 *Respond
)
{
    *Respond = prime_abort();
     return *Respond==PRIME_ERROR_COMM?PS_COMM_ERR:PS_OK;
}

EFI_STATUS
EFIAPI
Bhz1FingerIdentify(
    IN EFI_R301FINGERIO_PROTOCOL *This,
    OUT UINT16 *PageID,
    OUT UINT16 *Score,
    OUT UINT16 *Respond
)
{
    UINT32 rv = 0;
    UINT32 iStartPage = 0;
    UINT32 iPageNum = 6;
    UINT32 nID = 0;
    rv = prime_identify();
     do
    {
        rv = prime_getstatus();
        //should loop
        if (rv==PRIME_STATUS_IDLE)
        {
             continue;
        }
        if (rv == PRIME_STATUS_WAIT)
        {
            continue;
        }
        
        if (rv == PRIME_STATUS_MATCH)
        {//match OK , break to get ID
            *Respond = PRIME_STATUS_MATCH;
            *Score = 100;
            break;
        }//rests are error returns
        else if (rv == PRIME_STATUS_NOT_MATCH)
        {
            *Respond = PRIME_STATUS_NOT_MATCH;
            *Score = 0;
            return *Respond ;
        }
        else if (rv==PRIME_STATUS_TIMEOUT)
        {  
            *Respond = PRIME_STATUS_TIMEOUT;
            return *Respond ;
        }
        else
        {
            //*Respond = rv;
            //return *Respond ;
        }
        
    } while (rv);

    rv = prime_getid(&nID);
    if(rv)
        *Respond = rv;
    *PageID = nID;
    *Respond = PRIME_STATUS_MATCH;
    return *Respond;
}

EFI_STATUS
EFIAPI
Bhz1FingerDeleteTemplate(
    IN EFI_R301FINGERIO_PROTOCOL *This,
    IN UINT16 *PageID,
    OUT UINT16 *Respond)
{

    UINT8 count = 0;
    UINT8 index = (UINT8)(*PageID);

    *Respond = prime_delete(&index);
     return *Respond==PRIME_ERROR_COMM?PS_COMM_ERR:PS_OK;
}

EFI_STATUS
EFIAPI
Bhz1FingerGetTemplateNum(
    IN EFI_R301FINGERIO_PROTOCOL *This,
    OUT UINT16 *Sum,
    OUT UINT16 *Respond)
{
    UINT8 count = 0;
    UINT8 Index[10] = { 0 };
    *Respond = prime_getlist(Index,&count);
    *Sum = count;
    return *Respond==PRIME_ERROR_COMM?PS_COMM_ERR:PS_OK; 
}

EFI_STATUS
EFIAPI
Bhz1FingerGetFeature(
  IN EFI_R301FINGERIO_PROTOCOL               * This,
  IN UINT16                                 *Sequence,
  OUT UINT16                                 *Respond
)
{
    UINT8 count = 0;
    UINT8 Index[10] = { 0 };
    UINT32 i  = 0;
    UINT32 rv = prime_getlist(Index,&count);
    if(rv)
    {
        *Respond = rv;
        return rv;
    }
    while(i<count)
    {
        if(Index[i]==(*Sequence))
        {
            *Respond = PRIME_OK;
             return PRIME_OK;
        }

    }
    *Respond = PRIME_ERROR_NO_FINGER;
    return PRIME_ERROR_NO_FINGER;
}


EFI_STATUS
EFIAPI
Bhz1FingerCalibrate(
    IN EFI_R301FINGERIO_PROTOCOL *This,
    OUT UINT32 *Respond

)
{
    *Respond = prime_calibrate();
    return *Respond==PRIME_ERROR_COMM?PS_COMM_ERR:PS_OK; 
}