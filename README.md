# CS162-VisuAlgo

Repository: https://github.com/ntploc21/CS162-VisuAlgo

APCS - CS162 Solo Project - VisuAlgo

This is a project for the course CS162 - Introduction to Computer Science II. 

In this project, I will do a data visualization application that tries to replicate what [VisuAlgo](https://visualgo.net/en) does. Such application provides an intuitive and user-friendly interface for the display and understanding data stored in basic data structures. Users can choose from a variety of data structures (listed in the Features), and can easily initialize, add, delete, update, and search data within these data structures.
## Features
Will be updated soon
## Requirements
* C++20 (GNU GCC 11.3.0)
* CMake

## Building
1. Clone this repository to your machine.
    ```bash
    git clone https://github.com/ntploc21/CS162-VisuAlgo.git
    cd CS162-VisuAlgo
    ```

2. Run the following commands
    ```bash
    cmake -G [You generator] -S . -B build/
    make -C build
    ```
    - You can find the generator you are using with ```cmake -h``` and plug it in ```[Your generator]```
    - If you are using other generator that doesnt generate Makefile, you can search "Build project with [Your generator]" and search for a solution
3. Enjoy!

## Directory Structure
- [**src/**](src) contains source code.
    - [**Components/**](src/Components) contains UI components.
    - [**Core/**](src/Core) processes visualization.
    - [**States/**](src/States) contains VisuAlgo scene
    - [**Identifiers/**](src/Identifiers) contains VisuAlgo identifiers for scene, font, and stuff
- [**include/**](include) contains the library header files
- [**assets/**](assets) contains the assets of the project
- [**/unittest**](unittest) contains all of the unit tests of the project

## Contributor
22125050 - Nguyen Thanh Phuoc Loc

ntploc21@gmail.com

https://www.facebook.com/ntploc.21/
