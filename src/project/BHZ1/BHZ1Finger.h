/*++
//;******************************************************************************
//;* Copyright (c) 2006-2009, Taihang BIOS, ZD Technologies (Beijing) Ltd.. All  
//;* Rights Reserved.                                                            
//;*                                                                             
//;* You may not reproduce, distribute, publish, display, perform, modify, adapt,
//;* transmit, broadcast, present, recite, release, license or otherwise exploit 
//;* any part of this publication in any form, by any means, without the prior   
//;* written permission of ZD Technologies (Beijing) Ltd..                       
//;*                                                                             
//;******************************************************************************
//;******************************************************************************
Module Name:

  BHZ1FingerIoFunction.h

Abstract:


--*/


#ifndef _EFI_BHZ1FINGER_SERIALIO_FUNCTION_H_
#define _EFI_BHZ1FINGER_SERIALIO_FUNCTION_H_
#include "../../core/def.h"

typedef struct _EFI_R301FINGERIO_PROTOCOL
{
    UINT32 dev_index;
} EFI_R301FINGERIO_PROTOCOL;


EFI_STATUS
EFIAPI
Bhz1FingerEnroll(
IN EFI_R301FINGERIO_PROTOCOL *This,
    IN UINT16 *PageID,
    OUT UINT16 *Respond
);

EFI_STATUS
EFIAPI
Bhz1FingerState(
    IN EFI_R301FINGERIO_PROTOCOL *This,
    OUT UINT16 *ResData
);

EFI_STATUS
EFIAPI
Bhz1FingerStatus(
    IN EFI_R301FINGERIO_PROTOCOL *This,
    OUT UINT16 *Respond
);

EFI_STATUS
EFIAPI
BHZ1FingerAbort(
    IN EFI_R301FINGERIO_PROTOCOL *This,
    OUT UINT16 *Respond
);


EFI_STATUS
EFIAPI
Bhz1FingerIdentify(
    IN EFI_R301FINGERIO_PROTOCOL *This,
    OUT UINT16 *PageID,
    OUT UINT16 *Score,
    OUT UINT16 *Respond
);


EFI_STATUS
EFIAPI
Bhz1FingerDeleteTemplate(
    IN EFI_R301FINGERIO_PROTOCOL *This,
    IN UINT16 *PageID,
    OUT UINT16 *Respond);


EFI_STATUS
EFIAPI
Bhz1FingerGetTemplateNum(
    IN EFI_R301FINGERIO_PROTOCOL *This,
    OUT UINT16 *Sum,
    OUT UINT16 *Respond);



EFI_STATUS
EFIAPI
Bhz1FingerGetFeature(
  IN EFI_R301FINGERIO_PROTOCOL               * This,
  IN UINT16                                 *Sequence,
  OUT UINT16                                 *Respond
);

EFI_STATUS
EFIAPI
Bhz1FingerCalibrate(
    IN EFI_R301FINGERIO_PROTOCOL *This,
    OUT UINT32 *Respond

);

#endif
