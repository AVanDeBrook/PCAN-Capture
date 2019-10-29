# PCAN-Capture
This project uses the PEAK PCAN Viewer to read CAN messages from the foxBMS battery management system and display the voltages in decimal format.

# Documentation
Included in the `docs` folder is the compiled HTML documentation of the PCAN Viewer API along with a PDF documenting the paramaters used in the API.

More information on the hardware in the following links:
* [PEAK-System Technik PCAN-USB Adapter](https://phytools.com/collections/usb-interfaces/products/pcan-usb-adapter) info can be found under `Download Links` at the bottom of the page.
* [foxBMS CAN Messages](https://docs.foxbms.org/en/latest/getting_started/communicating/communicating.html) in the `TX Messages` table. Specifically, message IDs `0x200` - `0x205`(only focusing on module 0 for now, as we only have 1 slave board).

Note: Decompile the documentation using something like 7ZIP or WinRAR to view the actual documentation.

# Code
In the `src` folder is the code that is used to read the CAN messages from the PCAN Viewer and convert the data into an easier to read decimal format for every cell in a BMS Slave board.

This project uses Make along with [GCC](https://gcc.gnu.org/) to compile and build the project.

To build the project, run the following two commands:

```bash
$ cd src
$ make
```
The compilation will result in a binary file called `can_cap.exe`.

The following files are included in the `lib` folder:
* `PCANBasic.h`: Contains the basic API function prototypes, PCAN types, and enumerations for use with the API.
* `PCANBasic.dll`: Contains the actual implementation of the API.

# Notes/TODO
* This code is meant to be used with specific hardware in a specific way, may not work in a generic way.
* If the PCAN hardware is not connected to the PC the program will fail to initialize and exit.
* Hardware used: [PCAN-USB Adapter](https://phytools.com/collections/usb-interfaces/products/pcan-usb-adapter)
* Slow down output to make voltages readable.
* Consider using seperate thread to update voltage readings, then read from the user thread.
* Consider using timer-triggered events rather than event triggered.
* Used Windows API to create and manage threads. Documentation [here](https://docs.microsoft.com/en-us/windows/win32/procthread/creating-threads)

# Current Problems
* Current implementation uses event triggered message reading, for whatever reason this results in a message with 0x205 being read for more often than others.
* Considering switching to a timer triggered message reading system and seperating into two threads, one for reading and updating messages the other for displaying data upon user request.
