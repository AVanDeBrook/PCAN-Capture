# PCAN-Capture
This project uses the PEAK PCAN Viewer to read CAN messages from the foxBMS battery management system and display the voltages in decimal format.

# Documentation
Included in the `docs` folder is the compiled HTML documentation of the PCAN Viewer API along with a PDF documenting the paramaters used in the API.

More information on the hardware in the following links:
* [PEAK-System Technik PCAN-USB Adapter](https://phytools.com/collections/usb-interfaces/products/pcan-usb-adapter) info can be found under `Download Links` at the bottom of the page.
* [foxBMS CAN Messages](https://docs.foxbms.org/en/latest/getting_started/communicating/communicating.html) in the `TX Messages` table. Specifically, message IDs `0x200` - `0x205`

Note: Decompile the documentation using something like 7ZIP or WinRAR to view the actual documentation.

# Code
In the `src` folder is the code that is used to read the CAN messages from the PCAN Viewer and convert the data into an easier to read decimal format for every cell in a BMS Slave board.

The following files are included in the `src/lib` folder:
* `PCANBasic.h`: Contains the basic API function prototypes, PCAN types, and enumerations for use with the API.
* `PCANBasic.dll`: Contains the actual implementation of the API.

# Notes
* This code is meant to be used with specific hardware in a specific way, may not work in a generic way.
* If the PCAN hardware is not connected to the PC the program will fail to initialize and exit.
* Hardware used: [PCAN-USB Adapter](https://phytools.com/collections/usb-interfaces/products/pcan-usb-adapter)

# TODO
* Slow down output to make voltages readable.
* Consider using seperate thread to update voltage readings, then read from the user thread.
