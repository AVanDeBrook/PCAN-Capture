#include "DatabaseThread.h"

extern TPCANMsg can_message;

DWORD WINAPI DatabaseThread::update_database(LPVOID dummy_param)
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