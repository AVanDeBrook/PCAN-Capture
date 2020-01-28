#ifndef _CAN_MAIN_H
#define _CAN_MAIN_H

#include <iostream>
#include "general.h"

class CANMain
{
    private:

    public:
        /// Constructor(s)
        CANMain();
        /// Deconstructor(s)
        ~CANMain();

        /**
         * Function to initialize the PCAN interface/api.
         *
         * @return StdError_e   Enumerator of possible types of errors
         *                      (including no error)
         */
        StdError_e init(void);

        /**
         * Function to setup CAN message filtering.
         *
         * @param high_msg      Highest CAN message to accept.
         * @param low_msg       Lowest CAN message to accept.
         * @return StdError_e   Enumerator indicating type of error (or lack thereof).
         */
        StdError_e filter_messages(int high_msg, int low_msg);
};

#endif