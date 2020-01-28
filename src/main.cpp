#include "general.h"
#include "CANMain.h"
#include "Utils.h"
#include "DatabaseThread.h"

TPCANMsg can_message; // CAN Message buffer
TPCANTimestamp timestamp; // Timestamp buffer
Voltage_Group_t cell_voltages[4]; // Data structure for cell voltages

bool running_state = true;

int main(void)
{
    CANMain pcan_interface;
    DatabaseThread db_threads;
    int input;

    for (;;) {
        Utils::input_trigger(SHOW_MENU);
        std::cin >> input;
        Utils::input_trigger((UserInput_t)input);

        // Yeah, yeah, don't break out of for-loops.
        // I think this fits the special condition clause.
        if (input == APP_EXIT) {
            break;
        }
    }

    // Deinitialize and free threads/memory
    pcan_interface.~CANMain();
    db_threads.~DatabaseThread();

    return 0;
}
