#include <iostream>
#include "PCANBasic.h"

using namespace std;

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

    CAN_Uninitialize(PCAN_NONEBUS);
    return 0;
}
