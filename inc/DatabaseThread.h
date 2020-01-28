#ifndef _DATABASE_THREAD_H
#define _DATABASE_THREAD_H

#include <iostream>
#include <windows.h>
#include "general.h"

class DatabaseThread
{
    private:
        HANDLE db_thread_handle;
        DWORD db_thread_id;
    public:
        bool thread_errors = false;
        /// Constructor(s)
        DatabaseThread(void);

        /// Deconstructor(s)
        ~DatabaseThread();

        /**
         * Function to initialize the thread(s) for database operations.
         */
        void init(void);

        /**
         * Function to update the can message database. Executed in a thread
         * seperate from the main function.
         *
         * @param LPVOID dummy parameter, not used in this function. Required
         *               prototype for a thread in windows.
         * @return
         */
        static DWORD WINAPI update_database(LPVOID dummy_param);
};

#endif