#ifndef __BHZ1_DEF
#define __BHZ1_DEF


#define SIMULATE
#ifdef SIMULATE //simulate the bios
typedef unsigned int UINTN;
#define EFI_STATUS UINT32
#define EFIAPI
#define EFI_STATUS_OK   0
#endif


#define BHZ1_INTERNAL
//LEN && size & time
#define BHZ1_MAX_LEN            256
#define BHZ1_HEADER_LEN         8
#define BHZ1_CRC_LEN            2
#define BHZ1_SIMPLE_CMD_LEN     10
#define BHZ1_DELAY_LONG         2000000 //2s
#define BHZ1_DELAY_COMMON       50000   //50ms

//PACKAGE HEADER
//////OFFSET
#define BHZ1_SYNC_OFFSET        0
#define BHZ1_CMD_OFFSET         3
#define BHZ1_COMM_OFFSET        4
#define BHZ1_OP_OFFSET          5
#define BHZ1_LEN_OFFSET         6
#define BHZ1_DATA_OFFSET        8
//////const value
#define BHZ1_SYNC_1             0x55
#define BHZ1_SYNC_2             0xaa
//////command
#define BHZ1_CMD_ENROLL         1
#define BHZ1_CMD_IDENTIFY       2
#define BHZ1_CMD_DELETE         3
#define BHZ1_CMD_ABORT          4
#define BHZ1_CMD_GETLIST        5
#define BHZ1_CMD_GETVERSION     0x7f
#define BHZ1_CMD_CALIBRATE      7 


//ORIGINAL ERROR CODE
//Ret code
#define PS_OK 0x00
#define PS_COMM_ERR 0x01
#define PS_NO_FINGER 0x02
#define PS_GET_IMG_ERR 0x03
#define PS_FP_TOO_DRY 0x04
#define PS_FP_TOO_WET 0x05
#define PS_FP_DISORDER 0x06
#define PS_LITTLE_FEATURE 0x07
#define PS_NOT_MATCH 0x08
#define PS_NOT_SEARCHED 0x09
#define PS_MERGE_ERR 0x0a
#define PS_ADDRESS_OVER 0x0b
#define PS_READ_ERR 0x0c
#define PS_UP_TEMP_ERR 0x0d
#define PS_RECV_ERR 0x0e
#define PS_UP_IMG_ERR 0x0f
#define PS_DEL_TEMP_ERR 0x10
#define PS_CLEAR_TEMP_ERR 0x11
#define PS_SLEEP_ERR 0x12
#define PS_INVALID_PASSWORD 0x13
#define PS_RESET_ERR 0x14
#define PS_INVALID_IMAGE 0x15
#define PS_HANGOVER_UNREMOVE 0X17

#define PS_ENROLL_FAIL 0X1e
#define PS_FINGERBULK_TOPFULL 0X1f

#endif