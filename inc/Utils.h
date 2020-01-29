#ifndef _UTILS_H
#define _UTILS_H

#include <iostream>
#include "general.h"

class Utils
{
    private:

    public:
        static void process_voltages(void);
        static void display_voltages(void);
        static void print_message_data(void);
        static void input_trigger(UserInput_t input);
        static void process_state(void);
        static void display_state(void);
};

#endif