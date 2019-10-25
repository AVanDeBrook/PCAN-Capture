#ifndef __MAIN_H_
#define __MAIN_H_

#include <stdint.h>

/****** Definitions & Constants ******/
#define MOD_0_CELL_BASE 0x200
#define MOD_0_CELL_MAX 0x205

/****** Prototypes ******/
void process_voltages(void);
void display_voltages(void);
void print_message_data(void);
void input_trigger(uint8_t user_input);

/****** Data Structures ******/
typedef struct _Voltage_Group_t {
    uint16_t voltages[3];
} Voltage_Group_t;

typedef enum _UserInput_t {
    SHOW_MENU       = 0x00,
    READ_VOLTAGES   = 0x01,
    PRINT_VOLTAGES  = 0x02,
} UserInput_t;

#endif