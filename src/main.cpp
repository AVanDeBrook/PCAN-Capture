#include <iostream>
#include <windows.h>

#include "PCANBasic.h"
#include "main.h"

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

    CAN_Init();

    db_thread_handle = CreateThread(NULL, 0, update_database, &dummy_param, 0,  &db_thread_id);

    if (db_thread_handle == NULL) {
        cout << "Thread not created.\n";
        return 0;
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

void CAN_Init(void)
{
    TPCANStatus retval;
    char message[256];

    // Initialize PCAN on USB Bus 1 @ 0.5 MHz
    retval = CAN_Initialize(PCAN_USBBUS1, PCAN_BAUD_500K);

    // Error handling
    if (retval == PCAN_ERROR_OK) {
        cout << "PCAN USB Bus Initialized" << endl;
    } else {
        CAN_GetErrorText(retval, 0, message);
        cout << message << endl;
        return;
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
}

DWORD WINAPI update_database(LPVOID dummy_param)
{
    TPCANStatus retval;
    char message[256];

    while (1) {

        if (!running_state) {
            return -1;
        }

        // Read next CAN message in queue
        retval = CAN_Read(PCAN_USBBUS1, &can_message, &timestamp);

        // Error handling
        if (retval != PCAN_ERROR_OK && retval != PCAN_ERROR_QRCVEMPTY) {
            CAN_GetErrorText(retval, 0, message);
            //cout << message << endl;
            return -1;
        } else {
            CAN_GetErrorText(retval, 0, message);
            //cout << message << endl;
        }

        // Paranoia check to make sure the message IDs are correct.
        //
        // According to the API docs the filtering mechanism does not
        // guarantee only messages in this range.
        if ((can_message.ID & 0x0FFF) >= 0x200 && (can_message.ID & 0x0FFF) <= 0x203) {
            process_voltages();
        }

        //Sleep(100);
    }
}

void process_voltages(void)
{
    // Each cell voltage is 16 bits. The first byte is a status byte.
    uint16_t voltage_calcs[3] = {0};
    // Voltages are transmitted in little endian byte order
    // this converts them to "normal" values.
    //
    // Basically, the bytes need to be swapped.
    voltage_calcs[0] = can_message.DATA[2] << 8;
    voltage_calcs[0] |= can_message.DATA[1];

    voltage_calcs[1] = can_message.DATA[4] << 8;
    voltage_calcs[1] |= can_message.DATA[3];

    voltage_calcs[2] = can_message.DATA[6] << 8;
    voltage_calcs[2] |= can_message.DATA[5];

    cell_voltages[can_message.ID - 0x200].message_id = can_message.ID;

    // Save voltages to data structure.
    for (int i = 0; i < 3; i++) {
        cell_voltages[can_message.ID - 0x200].voltages[i] = voltage_calcs[i];
    }
}

void display_voltages(void)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            float temp = cell_voltages[i].voltages[j] / 1000.0;
            printf("Cell %02d: %0.3f V\n", ((3*i) + j) + 1, temp);
        }
    }
}

void print_message_data(void)
{
    printf("CAN Message data:");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", can_message.DATA[i]);
    }
    printf("\n");
}

void input_trigger(UserInput_t input)
{
    switch (input) {
    case SHOW_MENU:
        cout << "Options:\n1) Display Voltages\n2) Exit\n\nAction: ";
        break;
    case PRINT_VOLTAGES:
        display_voltages();
        break;
    default:
        cout << "Enter a value from the menu.\n";
    }
}
