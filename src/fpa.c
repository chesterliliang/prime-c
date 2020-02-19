#include "def.h"
#include "crc.h"
#include "comm/io.h"
#include "fpa.h"


PRIME_INTERNAL UINT32 gen_cmd(UINT8 cmd_index, UINT8* data, UINT16 data_len, UINT8* cmd, UINT16* len)
{
    UINT8 header[PRIME_HEADER_LEN] = {PRIME_SYNC_1, PRIME_SYNC_2, 0, 0, 0, 0, 0, 0};
    UINT8 crc[PRIME_CRC_LEN] = { 0 };
    UINT32 rv = 0
    ;
    //para check
    if(data_len>0xffff)
        return PRIME_ERROR_PARA;
    if(cmd==0)
        return PRIME_ERROR_PARA;
    //gen header
    header[PRIME_CMD_OFFSET] = cmd_index;
    if(data_len>0)
    {
        header[PRIME_LEN_OFFSET] = (UINT8)((data_len>>8)&0x00ff);
        header[PRIME_LEN_OFFSET+1] = (UINT8)(data_len&0x00ff);
    }
    memcpy(cmd,header,PRIME_HEADER_LEN);
    //gen data if have
    if(data_len>0&&data!=0)
    {
        memcpy(cmd+PRIME_HEADER_LEN,data, data_len);
    }
    //gen crc
    rv = calc_crc(cmd,PRIME_HEADER_LEN+data_len,crc);
    if (rv)
        return PRIME_ERROR_CRC;
    memcpy(cmd+PRIME_HEADER_LEN+data_len,crc,PRIME_CRC_LEN);

    if(len!=0)
        *len = PRIME_HEADER_LEN + data_len + PRIME_CRC_LEN;

    return PRIME_OK;
}


PRIME_INTERNAL UINT32 handle_cmd(UINT8* cmd, UINT16 cmd_len,UINT32 delays, UINT8* response, UINT16* len)
{
    UINT32 rv = 0;
    UINT16 l = 0;
    rv = prime_write(cmd, cmd_len);
    if (rv)
        return PRIME_ERROR_COMM;

    usleep(delays);

    rv = prime_read(response, PRIME_SIMPLE_CMD_LEN);
    if (rv)
        return PRIME_ERROR_COMM;
    //sync

    if (response[PRIME_COMM_OFFSET] != PRIME_OK)
        return response[PRIME_COMM_OFFSET];
    if (response[PRIME_OP_OFFSET] != PRIME_OK)
        return response[PRIME_OP_OFFSET];
    l = response[PRIME_LEN_OFFSET]*256 + response[PRIME_LEN_OFFSET+1];
    if(l>0)
    {
        rv = prime_read(response+PRIME_SIMPLE_CMD_LEN, l);
        if (rv)
            return PRIME_ERROR_COMM;
    }
   rv = check_crc(response, PRIME_HEADER_LEN+l, response + PRIME_HEADER_LEN+l);
    if (rv)
        return PRIME_ERROR_CRC;

    if(l>0&&len!=0)
        *len = l;
   
   return PRIME_OK;
   
}

PRIME_INTERNAL UINT32 get_response(UINT8* response, UINT16* len)
{
    UINT16 l = 0;
    UINT32 rv = 0;
    usleep(PRIME_DELAY_COMMON);
    
    rv = prime_read(response, PRIME_SIMPLE_CMD_LEN);
    if (rv)
        return PRIME_ERROR_COMM;

    if (response[PRIME_COMM_OFFSET] != PRIME_OK)
        return response[PRIME_COMM_OFFSET];
    if (response[PRIME_OP_OFFSET] != PRIME_OK)
        return response[PRIME_OP_OFFSET];
    l = response[PRIME_LEN_OFFSET]*256 + response[PRIME_LEN_OFFSET+1];
    if(l>0)
    {
        rv = prime_read(response+PRIME_SIMPLE_CMD_LEN, l);
        if (rv)
            return PRIME_ERROR_COMM;
    }
   rv = check_crc(response, PRIME_HEADER_LEN+l, response + PRIME_HEADER_LEN+l);
    if (rv)
        return PRIME_ERROR_CRC;

    if(l>0&&len!=0)
        *len = l;
   
   return PRIME_OK;
}