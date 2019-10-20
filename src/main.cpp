#include <iostream>
#include "PCANBasic.h"
#include "main.h"

using namespace std;

TPCANMsg can_message;
TPCANTimestamp timestamp;
Voltage_Group_t cell_voltages[6];

int main(void)
{
    TPCANStatus retval;
    char message[256];

    retval = CAN_Initialize(PCAN_USBBUS1, PCAN_BAUD_500K);

    if (retval == PCAN_ERROR_OK) {
        cout << "PCAN USB Bus Initialized" << endl;
    } else {
        CAN_GetErrorText(retval, 0, message);
        cout << message << endl;
    }

    retval = CAN_FilterMessages(PCAN_USBBUS1, 0x200, 0x205, PCAN_MESSAGE_STANDARD);

    if (retval == PCAN_ERROR_OK) {
        cout << "Filtering for CAN Messages with IDs 0x200 - 0x205" << endl;
    } else {
        CAN_GetErrorText(retval, 0, message);
        cout << message << endl;
    }

    while (1) {
        retval = CAN_Read(PCAN_USBBUS1, &can_message, &timestamp);

        if (retval != PCAN_ERROR_OK && retval != PCAN_ERROR_QRCVEMPTY) {
            CAN_GetErrorText(retval, 0, message);
            cout << message << endl;
            goto SYS_EXIT;
        }

        if (can_message.ID >= 0x200 && can_message.ID <= 0x205) {
            Process_Voltages();
        }
    }

    SYS_EXIT:
        CAN_Uninitialize(PCAN_NONEBUS);
        return 0;
}

void Process_Voltages(void)
{
    uint16_t voltage_calcs[3] = {0};
    // Voltages are transmitted in little endian byte order
    // this converts them to normal values.
    voltage_calcs[0] = can_message.DATA[2] << 8;
    voltage_calcs[0] |= can_message.DATA[1];

    voltage_calcs[1] = can_message.DATA[4] << 8;
    voltage_calcs[1] |= can_message.DATA[3];

    voltage_calcs[2] = can_message.DATA[6] << 8;
    voltage_calcs[2] |= can_message.DATA[5];

    for (int i = 0; i < 3; i++) {
        cell_voltages[can_message.ID - 0x200].voltages[i] = voltage_calcs[i];
    }
}

void Display_Voltages(void)
{
    for (int i = 0; i < 6; i++) {
        printf("Cell %d: %d mV\n", i, cell_voltages[i].voltages[0]);
        printf("Cell %d: %d\n mV", i, cell_voltages[i].voltages[1]);
        printf("Cell %d: %d\n mV", i, cell_voltages[i].voltages[2]);
    }
}