#include "def.h"
#include "fpa.h"
#include "prime.h"

UINT8 g_laststate = 0;

UINT32 prime_abort(void)
{
    UINT8 data_buf[PRIME_SIMPLE_CMD_LEN] = {0};
    UINT32 rv = 0;

    rv = gen_cmd(PRIME_CMD_ABORT, 0, 0, data_buf, 0);
    if (rv)
    {
        return PRIME_ERROR_PARA;
    }

    rv = handle_cmd(data_buf, PRIME_SIMPLE_CMD_LEN, PRIME_DELAY_MID, data_buf, 0);
    if (rv)
    {
        return rv;
    }
    return PRIME_OK;
}

UINT32 prime_enroll(UINT32 nID)
{
    UINT8 data_buf[PRIME_MAX_LEN] = {0};
    UINT32 rv = 0;
    g_laststate = 0;
    
    UINT8 id = (UINT8)nID;

    rv = gen_cmd(PRIME_CMD_ENROLL, &id, 1, data_buf, 0);
    if (rv)
    {
        return PRIME_ERROR_PARA;
    }

    rv = handle_cmd(data_buf, PRIME_SIMPLE_CMD_LEN+1, PRIME_DELAY_MID, data_buf, 0);//test
    if (rv)
    {
        return rv;
    }
    return PRIME_OK;
}

UINT32 prime_identify()
{
    UINT8 data_buf[PRIME_MAX_LEN] = {0};
    UINT32 rv = 0;
    UINT8 indicator[2] = { 0 };
    UINT16 len = 0;
    g_laststate = 0;

    rv = gen_cmd(PRIME_CMD_IDENTIFY, 0, 0, data_buf, 0);
    if (rv)
    {
        return PRIME_ERROR_PARA;
    }

    rv = handle_cmd(data_buf, PRIME_SIMPLE_CMD_LEN, PRIME_DELAY_MID, data_buf, 0);
    if (rv)
    {
        return rv;
    }

    return PRIME_OK;
}

UINT32 prime_delete(UINT8 *id)
{
    UINT8 data_buf[PRIME_MAX_LEN] = {0};
    UINT16 len = 0;
    UINT32 rv = 0;

    rv = gen_cmd(PRIME_CMD_DELETE, (UINT8 *)id, 1, data_buf, &len);
    if (rv)
    {
        return PRIME_ERROR_PARA;
    }

    rv = handle_cmd(data_buf, len, PRIME_DELAY_MID, data_buf, 0);
    if (rv)
    {
        return rv;
    }

    return PRIME_OK;
}

UINT32 prime_getlist(UINT8 *id, UINT8 *count)
{
    UINT8 data_buf[PRIME_MAX_LEN] = {0};
    UINT32 rv = 0;
    UINT16 len = 0;

    rv = gen_cmd(PRIME_CMD_GETLIST, 0, 0, data_buf, 0);
    if (rv)
    {
        return PRIME_ERROR_PARA;
    }
    rv = handle_cmd(data_buf, PRIME_SIMPLE_CMD_LEN, PRIME_DELAY_COMMON, data_buf, &len);
    if (rv)
    {
        return rv;
    }
    if (len > 0)
    {
        memcpy(id, data_buf + PRIME_DATA_OFFSET, len);
        *count = len;
    }
    return PRIME_OK;
}

UINT32 prime_getv(UINT8 *v, UINT8 *l)
{
    UINT8 data_buf[PRIME_MAX_LEN] = {0};
    UINT32 rv = 0;
    UINT16 len = 0;

    rv = gen_cmd(PRIME_CMD_GETVERSION, 0, 0, data_buf, 0);
    if (rv)
    {
        return PRIME_ERROR_PARA;
    }
    rv = handle_cmd(data_buf, PRIME_SIMPLE_CMD_LEN, PRIME_DELAY_COMMON, data_buf, &len);
    if (rv)
    {
        return rv;
    }
    if (len > 0)
    {
        memcpy(v, data_buf + PRIME_DATA_OFFSET, len);
        *l = len;
    }
    return PRIME_OK;
}

UINT32 prime_calibrate(void)
{
    UINT8 data_buf[PRIME_SIMPLE_CMD_LEN] = {0};
    UINT32 rv = 0;

    rv = gen_cmd(PRIME_CMD_CALIBRATE, 0, 0, data_buf, 0);
    if (rv)
    {
        return PRIME_ERROR_PARA;
    }

    return handle_cmd(data_buf, PRIME_SIMPLE_CMD_LEN, PRIME_DELAY_LONG, data_buf, 0);

}

UINT32 prime_getstate(void)
{
    UINT8 data_buf[PRIME_SIMPLE_CMD_LEN] = {0};
    UINT32 rv = 0;
    UINT32 rtn = 0;

    rv = gen_cmd(PRIME_CMD_GETSTATE, 0, 0, data_buf, 0);
    if (rv)
    {
        return PRIME_ERROR_PARA;
    }

    rv = handle_cmd(data_buf, PRIME_SIMPLE_CMD_LEN, PRIME_DELAY_COMMON, data_buf, 0);
    rtn = rv;
    if(rv==g_laststate)
    {
        switch (rv)
        {
        case PRIME_STATUS_WAIT:
        case PRIME_STATUS_GOOD:
        case PRIME_STATUS_BAD:
        case PRIME_STATUS_PART:
        case PRIME_STATUS_QUICK:
        case PRIME_STATUS_REDUNANT:
        case PRIME_STATUS_WERID:
            rtn = PRIME_STATUS_IDLE;
            break; 
        default:
            break;
        }
    }
    if(rv==PRIME_ERROR_COMM)
        rtn = PRIME_STATUS_IDLE;

    g_laststate = rv;
    return rtn;
}

UINT32 prime_getstatus(void)
{
    UINT8 data_buf[PRIME_SIMPLE_CMD_LEN] = {0};
    UINT16 len = 0;
    return get_response(data_buf,&len);
}

UINT32 prime_getid(UINT32* nID)
{
    
    UINT8 data_buf[PRIME_MAX_LEN] = {0};
    UINT8 response[PRIME_SIMPLE_CMD_LEN] = { 0 };
    UINT32 rv = 0;
    UINT16 len = 0;

    rv = gen_cmd(PRIME_CMD_GETID, 0, 0, data_buf, 0);
    if (rv)
    {
        return PRIME_ERROR_PARA;
    }

    rv = handle_cmd(data_buf, PRIME_SIMPLE_CMD_LEN, PRIME_DELAY_COMMON, response, &len);
    if(rv)
    {
        return rv;
    }
    if(len>0)
        *nID = (UINT32)response[PRIME_DATA_OFFSET];

    return PRIME_OK;
}