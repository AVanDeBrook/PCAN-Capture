#ifndef _DATABASE_THREAD_H
#define _DATABASE_THREAD_H

#include <iostream>
#include <windows.h>
#include "general.h"

class DatabaseThread
{
    private:

    public:
        /// Constructor(s)
        DatabaseThread();

        /// Deconstructor(s)
        ~DatabaseThread();

        /**
         * Function to update the can message database. Executed in a thread
         * seperate from the main function.
         *
         * @param LPVOID dummy parameter, not used in this function. Required
         *               prototype for a thread in windows.
         * @return
         */
        DWORD WINAPI update_database(LPVOID dummy_param);
};

#endif