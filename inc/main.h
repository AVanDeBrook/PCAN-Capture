#ifndef __MAIN_H_
#define __MAIN_H_

#include <stdint.h>

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
    E_ERR = 0x01,   // Unknown error
} StdError_e;

/****** Prototypes ******/
StdError_e CAN_Init(void);
DWORD WINAPI update_database(LPVOID dummy_param);
void process_voltages(void);
void display_voltages(void);
void print_message_data(void);
void input_trigger(UserInput_t user_input);

/****** Data Structures ******/
typedef struct _Voltage_Group_t {
    uint16_t message_id;
    uint16_t voltages[3];
} Voltage_Group_t;

#endif