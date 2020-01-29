#include "Utils.h"

extern TPCANMsg can_message;
extern Voltage_Group_t cell_voltages[4];
extern SysState_e system_state;

void Utils::process_voltages(void)
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

void Utils::display_voltages(void)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            float temp = cell_voltages[i].voltages[j] / 1000.0;
            printf("Cell %02d: %0.3f V\n", ((3*i) + j) + 1, temp);
        }
    }
}

void Utils::print_message_data(void)
{
    printf("CAN Message data:");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", can_message.DATA[i]);
    }
    printf("\n");
}

void Utils::input_trigger(UserInput_t input)
{
    switch (input) {
    case STANDBY:
        break;
    case SHOW_MENU:
        std::cout << "\nOptions:\n1) Show Menu\n2) Print Voltages\n3) System State\n4) Exit\n\nAction: ";
        break;
    case PRINT_VOLTAGES:
        Utils::display_voltages();
        break;
    case SYS_STATE:
        Utils::display_state();
        break;
    case APP_EXIT:
        std::cout << "Exitting..." << std::endl;
        break;
    default:
        std::cout << "Enter a value from the menu.\n";
    }
}

void Utils::process_state(void)
{
    system_state = (SysState_e) can_message.DATA[1];
}

void Utils::display_state(void)
{
    printf("System State: 0x%X - ", system_state);

    switch (system_state) {
    case SYS_UNINIT:
        std::cout << "Uninitialized\n";
        break;
    case SYS_IDLE:
        std::cout << "Idle\n";
        break;
    case SYS_STANDBY:
        std::cout << "Standby\n";
        break;
    case SYS_PRECHARGE_NORMAL:
        std::cout << "Precharge (normal)\n";
        break;
    case SYS_NORMAL:
        std::cout << "Normal\n";
        break;
    case SYS_PRECHARGE_CHARGE:
        std::cout << "Precharge (charge)\n";
        break;
    case SYS_CHARGE:
        std::cout << "Charge\n";
        break;
    case SYS_ERROR:
        std::cout << "Error\n";
        break;
    default:
        break;
    }
}
