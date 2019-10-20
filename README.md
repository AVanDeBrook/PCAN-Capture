# PCAN-Capture
This project uses the PEAK PCAN Viewer to read CAN messages from the foxBMS battery management system and display the voltages in decimal format.

# Documentation
Included in the `docs` folder is the decomiled HTML documentation of the PCAN Viewer API along with a PDF documenting the paramaters used in the API.

# Code
In the `src` folder is the code that is used to read the CAN messages from the PCAN Viewer and convert the data into an easier to read decimal format for every cell in a BMS Slave board.

The following files are included in the `src/lib` folder:
* `PCANBasic.h`: Contains the basic API function prototypes, PCAN types, and enumerations for use with the API.
* `PCANBasic.dll`: Contains the actual implementation of the API.

# Notes
* To-Self: This code still needs to be tested on the actual hardware.
