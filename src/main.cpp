#include <iostream>
#include <windows.h>
#include "PCANBasic.h"
#include "main.h"

using namespace std;

TPCANMsg can_message; // CAN Message buffer
TPCANTimestamp timestamp; // Timestamp buffer
Voltage_Group_t cell_voltages[6]; // Data structure for cell voltages

int main(void)
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
        goto SYS_EXIT;
    }

    retval = CAN_SetValue(PCAN_USBBUS1, PCAN_RECEIVE_EVENT, message, 256);

    if (retval != PCAN_ERROR_OK) {
        CAN_GetErrorText(retval, 0, message);
        cout << message << endl;
        goto SYS_EXIT;
    }

    // Filter messages with ID 0x200 - 0x205
    retval = CAN_FilterMessages(PCAN_USBBUS1, 0x200, 0x205, PCAN_MESSAGE_STANDARD);

    // Error handling
    if (retval == PCAN_ERROR_OK) {
        cout << "Filtering for CAN Messages with IDs 0x200 - 0x205" << endl;
    } else {
        // No need to exit, the paranoia check below allows the program to keep running normaly.
        // Maybe just a little slower.
        CAN_GetErrorText(retval, 0, message);
        cout << message << endl;
    }

    while (1) {
        // Read next CAN message in queue
        retval = CAN_Read(PCAN_USBBUS1, &can_message, &timestamp);

        // Error handling
        if (retval != PCAN_ERROR_OK && retval != PCAN_ERROR_QRCVEMPTY) {
            CAN_GetErrorText(retval, 0, message);
            cout << message << endl;
            goto SYS_EXIT;
        }

        // Paranoia check to make sure the message IDs are correct.
        //
        // According to the API docs the filtering mechanism does not
        // guarantee only messages in this range.
        if ((can_message.ID & 0x0FFF) >= 0x200 && (can_message.ID & 0x0FFF) <= 0x205) {
            //print_message_data();
            process_voltages();
            display_voltages();
        }
    }

    SYS_EXIT:
        CAN_Uninitialize(PCAN_NONEBUS);
        return 0;
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

    // Save voltages to data structure.
    for (int i = 0; i < 3; i++) {
        cell_voltages[can_message.ID - 0x200].voltages[i] = voltage_calcs[i];
    }
}

void display_voltages(void)
{
    for (int i = 0; i < 6; i++) {
        printf("Module %d: Cell 0: %d mV\n", i, cell_voltages[i].voltages[0]);
        printf("Module %d: Cell 1: %d mV\n", i, cell_voltages[i].voltages[1]);
        printf("Modeul %d: Cell 2: %d mV\n", i, cell_voltages[i].voltages[2]);
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