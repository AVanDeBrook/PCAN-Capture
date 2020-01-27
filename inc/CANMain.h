#ifndef _CAN_MAIN_H
#define _CAN_MAIN_H

#include <iostream>
#include "general.h"

class CANMain
{
    private:

    public:
        CANMain();
        ~CANMain();
        StdError_e init(void);
};

#endif