#ifndef __MAIN_H_
#define __MAIN_H_

#include <iostream>
#include <windows.h>
#include <stdint.h>
#include "PCANBasic.h"

/****** Definitions, Constants, Enumerations ******/
#define MOD_0_CELL_BASE 0x200
#define MOD_0_CELL_MAX 0x205

typedef enum _UserInput_t {
    STANDBY         = 0x00,
    SHOW_MENU       = 0x01,
    PRINT_VOLTAGES  = 0x02,
    SYS_STATE       = 0x03,
    APP_EXIT        = 0x04,
} UserInput_t;

typedef enum _StdError_e {
    E_NONE = 0x00,  // No error
    E_INIT = 0xFF,  // Error in initialization
    E_FILTER = 0x02,  // Error setting up a message filter
    E_ERR = 0x01,   // Unknown error
} StdError_e;

typedef enum _SysState_e {
    SYS_UNINIT = 0x00,          /// System Uninitialized
    SYS_IDLE = 0x03,            /// System Idle
    SYS_STANDBY = 0x04,         /// System Standby
    SYS_PRECHARGE_NORMAL = 0x05,/// System Precharge (normal)
    SYS_NORMAL = 0x06,          /// System Normal
    SYS_PRECHARGE_CHARGE = 0x07,/// System Precharge (charge)
    SYS_CHARGE = 0x08,          /// System Charge
    SYS_ERROR = 0xF0            /// System Error
} SysState_e;

typedef enum _StateReq_e {
    STATE_NONE = 0x00,
    STATE_NORMAL = 0x03,
    STATE_CHARGE = 0x04,
    STATE_STANDBY = 0x08
} StateReq_e;

/****** Prototypes ******/

/****** Data Structures ******/
typedef struct _Voltage_Group_t {
    uint16_t message_id;
    uint16_t voltages[3];
} Voltage_Group_t;

#endif