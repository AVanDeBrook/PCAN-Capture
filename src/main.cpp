#include "general.h"
#include "CANMain.h"
#include "Utils.h"
#include "DatabaseThread.h"

// @TODO: Throw this stuff into a data structure, so it's more oganized.
TPCANMsg can_message; // CAN Message buffer
TPCANTimestamp timestamp; // Timestamp buffer
Voltage_Group_t cell_voltages[4]; // Data structure for cell voltages
SysState_e system_state;

bool running_state = true;
StateReq_e request = STATE_STANDBY;

int main(void)
{
    CANMain pcan_interface = new CANMain(false);
    DatabaseThread db_threads;
    int input;

    // Important note: thread to request states must be initialized first,
    // then send reset signal to system, otherwise system will go into error.
    pcan_interface.init_threads();
    pcan_interface.reset_system();

    while (running_state) {
        Utils::input_trigger(SHOW_MENU);
        std::cin >> input;
        Utils::input_trigger((UserInput_t)input);

        // Yeah, yeah, don't break out of for-loops.
        // However, I think this fits the special condition clause.
        if (input == APP_EXIT) {
            running_state = false;
        }
    }

    // Deinitialize and free threads/memory
    pcan_interface.~CANMain();
    db_threads.~DatabaseThread();

    return 0;
}
