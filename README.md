# 6052 Emulator

This project aims to accurately simulate the actions of the MOS Technology 6502 processor. The aforementioned processor was used in the NES, and Apple computers in the 70s.

## Features

- **All instructions included**: This project includes all processor instructions, which have been taken from: [6502 Instructions](https://www.pagetable.com/c64ref/6502/?tab=2). All instructions are also split among different categories in different folders (categories are the same as on the website)
- **Execution**: There is no text editor that is included to compile 6502 assembly code. The user will have to manually load the instructions and operands into memory (can be seen in main.c)
- **Compilation**: This project utilizes make to build the project (GCC for compiling).

### How to use the emulator?

1. Clone the repository:
    ```sh
    git clone https://github.com/BigosKAR/6502_Emulator.git
    cd 6502_Emulator
    ```

2. Build the project:
    ```sh
    make
    ```

