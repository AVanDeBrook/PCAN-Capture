# PCAN-Capture
This project uses the PEAK PCAN Viewer to read CAN messages from the foxBMS battery management system and display the voltages in decimal format.

# Documentation
Included in the `docs` folder is the compiled HTML documentation of the PCAN Viewer API along with a PDF documenting the paramaters used in the API.

More information on the hardware in the following links:
* [PEAK-System Technik PCAN-USB Adapter](https://phytools.com/collections/usb-interfaces/products/pcan-usb-adapter) info can be found under `Download Links` at the bottom of the page.
* [foxBMS CAN Messages](https://docs.foxbms.org/en/latest/getting_started/communicating/communicating.html) in the `TX Messages` table. Specifically, message IDs `0x200` - `0x205` (only focusing on module 0 for now, as we are only testing with 1 slave board).

Note: Decompile the documentation using something like 7ZIP or WinRAR to view the actual documentation.

# Code
The `src` folder contains the actual code used to read cell voltages from the CAN messages. This code essentially makes 2 threads. One is responsible for accepting user input and displaying the information that has been read from the CAN messages sent by the battery system. The second thread's sole purpose is to constantly read and update the database that contains the information that has been recieved by the system. This will carry on forever, or until the program is terminated.

Upon proper termination of the program, all used memory is freed and the PCAN USB device and API is uninitialized. This is not guaranteed to happen when the program exits irregularly e.g. keyboard interrupt.

The following files are included in the `lib` folder:
* `PCANBasic.dll`: Contains the actual implementation of the API.

The PCANBasic header file has been moved to `inc`:
* `PCANBasic.h`: Contains the basic API function prototypes, PCAN types, and enumerations for use with the API.

# Building / Running
This project can be built using Make, there is a `makefile` included in the `src` directory.

To build this project, do the following (assuming you start from the root of this repo):
```bash
$ cd src
$ make
```
This will result in an executable file called `PCAN_Cap.exe`, running this file will execute the project. Keep in mind, the output of this program is contained entirely within the command line.

The executable is compiled with debugging symbols by using the `-g` switch in G++. The executable can be compiled without debugging symbols by changing the following lines in [`makefile`](makefile) like so:
```make
FLAGS = -g
```
to
```make
FLAGS =
```

For reference, these are the specs of the main machine this code was developed and tested on:
* Most recent version of VSCode/VSCodium
* Windows 10, update 1903
* GNU GCC version 8.1.0
* GNU G++ version 8.1.0
* GNU Make version 4.2.1
* GNU GDB version 8.1
* [Download here](https://sourceforge.net/projects/mingw-w64/)

# Notes/TODO
* Fair warning: This code is meant to be used with specific hardware in a specific way.
* If the PCAN hardware is not connected to the PC the program will fail to initialize and exit.
* Hardware used: [PCAN-USB Adapter](https://phytools.com/collections/usb-interfaces/products/pcan-usb-adapter)
* Uses seperate threads to update and display cell voltages based on user input.
* Used Windows API to create and manage threads. Documentation [here](https://docs.microsoft.com/en-us/windows/win32/procthread/creating-threads)
* **TODO**: Make a seperate branch and start organizing and refactoring the code (object oriented maybe?)
