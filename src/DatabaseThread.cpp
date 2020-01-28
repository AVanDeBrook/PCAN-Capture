#include "DatabaseThread.h"
#include "Utils.h"

extern TPCANMsg can_message;
extern TPCANTimestamp timestamp;
extern bool running_state;

DatabaseThread::DatabaseThread(void)
{
    DatabaseThread::init();
}

DatabaseThread::~DatabaseThread()
{
    WaitForSingleObject(db_thread_handle, 0);
}

void DatabaseThread::init(void)
{
    int dummy_param = 0;

    db_thread_handle = CreateThread(NULL, 0, DatabaseThread::update_database, &dummy_param, 0, &db_thread_id);

    if (db_thread_handle == NULL) {
        std::cerr << "Database thread not created.\n";
        thread_errors = true;
    } else {
        printf("Thread created.\nID: %d\nHandle: %d\n", db_thread_id, db_thread_handle);
    }
}

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
            Utils::process_voltages();
        }

        //Sleep(100);
    }
}