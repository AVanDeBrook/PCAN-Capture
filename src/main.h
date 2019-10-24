#ifndef __MAIN_H_
#define __MAIN_H_

#include <stdint.h>

/****** Prototypes ******/
void process_voltages(void);
void display_voltages(void);
void print_message_data(void);

/****** Data Structures ******/
typedef struct Voltage_Group {
    uint16_t voltages[3];
} Voltage_Group_t;

#endif