#ifndef FAULT_INFO_UNIT_TEST_H_
#define FAULT_INFO_UNIT_TEST_H_

#include "stdint.h"
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

enum {
    DEM_EVENT_ID_NULL = 0,
    ID_LAST
};

enum {
    ID_START = ID_LAST,
    ID_Video_error,
    ID_Sensor_error,
    ID_LCD_error,
    ID_Power_error,
    ID_I2C_Bus_error,
    ID_CAN_Bus_Off_error,
    ID_Lost_Communication_With_VIU2_error,
    ID_MAX_error
};

typedef struct {
    uint8_t  TotalFaultNum;
    uint8_t  FrameIndex;
    uint8_t  SupplierNum;
    uint16_t FaultNum[4];
} SrcInfoDecoded_t;

typedef struct {
	// byte[0]
    uint8 Info_TotalFaultNum;

	// byte[1]
    uint8 Info_FrameIdx  : 5;
    uint8 Info_SuppilerNum : 3;

    // Info_FaultNum1/ 2/ 3/ 4 用byte2/3 3/4 /5/6 6/7
    uint8_t Byte2;
    uint8_t Byte3;
    uint8_t Byte4;
    uint8_t Byte5;
    uint8_t Byte6;
    uint8_t Byte7;
} Fault_Info_t;

static uint8 fault_info_data[8] = {0};

static Fault_Info_t fault_info;

void demo_app_start(void);

#endif // FAULT_INFO_UNIT_TEST_H_