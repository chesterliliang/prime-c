#ifndef __PRIME_H_
#define __PRIME_H_
#include "def.h"

UINT32 prime_abort(void);

UINT32 prime_enroll(UINT32 nID);

UINT32 prime_identify();

UINT32 prime_delete(UINT8* id);

UINT32 prime_getlist(UINT8* id, UINT8* count);

UINT32 prime_getv(UINT8* v, UINT8* len);

UINT32 prime_calibrate(void);

UINT32 prime_getstate(void);

UINT32 prime_getstatus(void);

UINT32 prime_getid(UINT32* nID);

#endif