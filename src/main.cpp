#include "general.h"
#include "CANMain.h"
#include "Utils.h"
#include "DatabaseThread.h"

using namespace std;

TPCANMsg can_message; // CAN Message buffer
TPCANTimestamp timestamp; // Timestamp buffer
Voltage_Group_t cell_voltages[4]; // Data structure for cell voltages

bool running_state = true;

int main(void)
{
    int input = SHOW_MENU;
    HANDLE db_thread_handle;
    DWORD db_thread_id;
    int dummy_param = 0;
    StdError_e retval = E_NONE;

    retval = CAN_Init();

    if (retval == E_INIT) {
        cerr << "Error initializing PCAN hardware, hardware most likely not connected.\n";
        return -1;
    }

    db_thread_handle = CreateThread(NULL, 0, update_database, &dummy_param, 0,  &db_thread_id);

    if (db_thread_handle == NULL) {
        cout << "Thread not created.\n";
        return -1;
    }

    while (input != (int)APP_EXIT) {
        input_trigger((UserInput_t)input);
        cin >> input;
    }

    running_state = false;
    WaitForSingleObject(db_thread_handle, 0);
    CAN_Uninitialize(PCAN_USBBUS1);
    return 0;
}
