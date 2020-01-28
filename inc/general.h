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
    SHOW_MENU       = 0x00,
    PRINT_VOLTAGES  = 0x01,
    APP_EXIT        = 0x02,
} UserInput_t;

typedef enum _StdError_e {
    E_NONE = 0x00,  // No error
    E_INIT = 0xFF,  // Error in initialization
    E_FILTER = 0x02,  // Error setting up a message filter
    E_ERR = 0x01,   // Unknown error
} StdError_e;

/****** Prototypes ******/

/****** Data Structures ******/
typedef struct _Voltage_Group_t {
    uint16_t message_id;
    uint16_t voltages[3];
} Voltage_Group_t;

#endif