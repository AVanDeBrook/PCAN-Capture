#include "CANMain.h"

extern TPCANMsg can_message;
extern TPCANTimestamp timestamp;
extern bool running_state;
extern StateReq_e request;

CANMain::CANMain(void)
{
    StdError_e retval = E_NONE;

    retval = CANMain::init();

    if (retval != E_NONE) {
        std::cerr << "Error initializing PCAN API.\n";
    }

    retval = CANMain::filter_messages(MOD_0_CELL_BASE, MOD_0_CELL_BASE + 3);
}

CANMain::CANMain(bool message_filtering)
{
    StdError_e retval = E_NONE;

    retval = CANMain::init();

    if (retval != E_NONE) {
        std::cerr << "Error initializing PCAN API.\n";
    }

    if (message_filtering) {
        retval = CANMain::filter_messages(MOD_0_CELL_BASE, MOD_0_CELL_BASE + 3);
    }
}

CANMain::~CANMain()
{
    if (thread_created) {
        WaitForSingleObject(can_thread_handle, 0);
    }

    CAN_Uninitialize(PCAN_USBBUS1);
}

StdError_e CANMain::init(void)
{
    TPCANStatus retval;
    char message[256];
    StdError_e return_code = E_NONE;

    // Initialize PCAN on USB Bus 1 @ 0.5 MHz
    retval = CAN_Initialize(PCAN_USBBUS1, PCAN_BAUD_500K);

    // Error handling
    if (retval == PCAN_ERROR_OK) {
        std::cout << "PCAN USB Bus Initialized" << std::endl;
    } else {
        CAN_GetErrorText(retval, 0, message);
        std::cout << message << std::endl;
        return_code = E_INIT;
        return return_code;
    }

    /* -- Keeping this around just in case. --
    // Filter messages with ID 0x200 - 0x203
    // The simulated battery is only 12 cells, 4 messages x 3 cells per message = 12 cells
    retval = CAN_FilterMessages(PCAN_USBBUS1, MOD_0_CELL_BASE, MOD_0_CELL_BASE + 3, PCAN_MESSAGE_STANDARD);

    // Error handling
    if (retval == PCAN_ERROR_OK) {
        std::cout << "Filtering for CAN Messages with IDs 0x200 - 0x205" << std::endl;
    } else {
        // No need to exit, there are checks later to verify message IDs
        CAN_GetErrorText(retval, 0, message);
        std::cout << message << std::endl;
    }
    */

    return return_code;
}

StdError_e CANMain::filter_messages(int low_msg, int high_msg)
{
    TPCANStatus retval;
    char message[256];
    StdError_e return_code = E_NONE;

    retval = CAN_FilterMessages(PCAN_USBBUS1, low_msg, high_msg, PCAN_MESSAGE_STANDARD);

    if (retval == PCAN_ERROR_OK) {
        printf("Filtering for CAN messages: 0x%X - 0x%X\n", low_msg, high_msg);
    } else {
        CAN_GetErrorText(retval, 0, message);
        std::cerr << message << std::endl;
        return_code = E_FILTER;
    }

    return return_code;
}

DWORD WINAPI CANMain::request_state(LPVOID dummy_param)
{
    char message[256];
    TPCANStatus retval;

    TPCANMsg can_message = {
        .ID = 0x120,
        .MSGTYPE = PCAN_MESSAGE_STANDARD,
        .LEN = 1,
        .DATA = {0, (BYTE) request, 0, 0, 0, 0, 0, 0}
    };

    while (running_state) {
        retval = CAN_Write(PCAN_USBBUS1, &can_message);

        if (retval != PCAN_ERROR_OK && retval != PCAN_ERROR_QXMTFULL) {
            CAN_GetErrorText(retval, 0, message);
            return -1;
        } else {
            CAN_GetErrorText(retval, 0, message);
        }

        Sleep(100);
    }

    return 1;
}

StdError_e CANMain::init_threads(void)
{
    int dummy_param = 0;
    StdError_e return_code = E_NONE;

    can_thread_handle = CreateThread(NULL, 0, CANMain::request_state, &dummy_param, 0, &can_thread_id);

    if (can_thread_handle == NULL) {
        std::cerr << "request_state thread not created.\n";
        thread_errors = true;
        return_code = E_INIT;
    } else {
        printf("request_state thread created.\nID: %d\nHandle: %d\n", can_thread_id, can_thread_handle);
        thread_created = true;
    }

    return return_code;
}

StdError_e CANMain::reset_system(void)
{
    TPCANStatus retval;
    char message[256];
    StdError_e return_code = E_NONE;

    TPCANMsg can_message = {
        .ID = 0x95,
        .MSGTYPE = PCAN_MESSAGE_STANDARD,
        .LEN = 0,
        .DATA = {0}
    };

    retval = CAN_Write(PCAN_USBBUS1, &can_message);

    if (retval != PCAN_ERROR_OK) {
        CAN_GetErrorText(retval, 0, message);
        return_code = E_ERR;
    } else {
        std::cout << "Reset Signal Sent.\n";
    }

    return return_code;
}