#include "general.h"
#include "CANMain.h"
#include "Utils.h"
#include "DatabaseThread.h"

TPCANMsg can_message; // CAN Message buffer
TPCANTimestamp timestamp; // Timestamp buffer
Voltage_Group_t cell_voltages[4]; // Data structure for cell voltages

bool running_state = true;

int main(void)
{

}
