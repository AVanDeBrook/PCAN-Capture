#ifndef _CAN_MAIN_H
#define _CAN_MAIN_H

#include <iostream>
#include "general.h"

class CANMain
{
    private:
        bool thread_created = false;
        HANDLE can_thread_handle;
        DWORD can_thread_id;
    public:
        bool thread_errors = false;
        /// Constructor(s)

        /**
         * No-arg constructor, defaults to filtering messages 0x200 - 0x203.
         * Initializing the PCAN USB dongle and API.
         */
        CANMain();

        /**
         * Constructor with the option to enable/disable message filtering.
         * Enabling filters for messages with ID 0x200 - 0x203.
         * **Note**: Message filtering is not guranteed to work 100% of the time.
         *
         * @param message_filtering Boolean to enable/disable message filtering:
         *                          true    - enable
         *                          false   - disable
         */
        CANMain(bool message_filtering);

        /// Deconstructor

        /**
         * Uninitialized the PCAN USB dongle and API, as well as any threads
         * if they were created.
         */
        ~CANMain();

        /// Functions

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

        /**
         * Seperate thread to send the state request CAN message within the
         * 95 - 105 ms window.
         *
         * @param state     State to request of the system (use the StateReq_e enumerator).
         * @return DWORD    Returns -1 in error, 1 otherwise (when thread exits successfully).
         */
        static DWORD WINAPI request_state(LPVOID dummy_param);

        /**
         * Function to initialize the state request thread (request_state).
         *
         * @return StdError_e   Returns a standard error type enumerated in general.h.
         */
        StdError_e init_threads(void);
};

#endif