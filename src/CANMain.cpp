#include "CANMain.h"

StdError_e PCANMAIN::init(void)
{
    TPCANStatus retval;
    char message[256];
    StdError_e return_code = E_NONE;

    // Initialize PCAN on USB Bus 1 @ 0.5 MHz
    retval = CAN_Initialize(PCAN_USBBUS1, PCAN_BAUD_500K);

    // Error handling
    if (retval == PCAN_ERROR_OK) {
        cout << "PCAN USB Bus Initialized" << endl;
    } else {
        CAN_GetErrorText(retval, 0, message);
        cout << message << endl;
        return_code = E_INIT;
        return return_code;
    }

    // Filter messages with ID 0x200 - 0x203
    // The simulated battery is only 12 cells, 4 messages x 3 cells per message = 12 cells
    retval = CAN_FilterMessages(PCAN_USBBUS1, MOD_0_CELL_BASE, MOD_0_CELL_BASE + 3, PCAN_MESSAGE_STANDARD);

    // Error handling
    if (retval == PCAN_ERROR_OK) {
        cout << "Filtering for CAN Messages with IDs 0x200 - 0x205" << endl;
    } else {
        // No need to exit, there are checks later to verify message IDs
        CAN_GetErrorText(retval, 0, message);
        cout << message << endl;
    }

    return return_code;
}