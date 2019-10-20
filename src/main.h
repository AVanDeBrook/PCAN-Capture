#ifndef __MAIN_H_
#define __MAIN_H_

#include <stdint.h>


/****** Prototypes ******/
void Process_Voltages(void);
void Display_Voltages(void);

/****** Data Structures ******/
typedef struct Voltage_Group {
    uint16_t voltages[3];
} Voltage_Group_t;

#endif