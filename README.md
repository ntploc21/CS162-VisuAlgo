# CS162-VisuAlgo

Repository: https://github.com/ntploc21/CS162-VisuAlgo

APCS - CS162 Solo Project - VisuAlgo

This is a project for the course CS162 - Introduction to Computer Science II. 

In this project, I will do a data visualization application that tries to replicate what [VisuAlgo](https://visualgo.net/en) does. Such application provides an intuitive and user-friendly interface for the display and understanding data stored in basic data structures. Users can choose from a variety of data structures (listed in the Features), and can easily initialize, add, delete, update, and search data within these data structures.
## Features
It currently supports the following data structures:
- Array
- Dynamic Array (similar to `std::vector`)
- Linked List
- Doubly Linked List
- Circular Linked List
- Stack
- Queue

Notable features include:
- Visualization of initialization and CRUD operations of different data structures
- Step-by-step code highlight
- Animation controller (play, pause, stop, etc) so that you can see the visualization in your own pace
- Action description (by natural language) for each step
- Customizable color theme
- And many more!
## Requirements
* C++20 (GNU GCC 11.3.0)
* CMake
* [Raylib](https://github.com/raysan5/raylib) and [Raygui](https://github.com/raysan5/raygui)
* [tinyfiledialogs](https://sourceforge.net/projects/tinyfiledialogs/)

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
    - You can find the generator you are using with ```cmake -h``` and plug it in ```[Your generator]```.
    - If you are using other generator that doesnt generate Makefile, you can search "Build project with [Your generator]" and search for a solution.
3. Enjoy!

## Directory Structure
- [**src/**](src) contains source code
    - [**Algorithms/**](src/Algorithms/) generate step-by-step instruction for animating/visualizing the data structures and algorithms
    - [**Animation/**](src/Animation/) processes animation and visualization also animation controller such as play, pause, stop, etc
    - [**Components/**](src/Components) contains UI components
        - [**Common/**](src/Components/Common/) contains commonly used UI components (e.g Button, etc)
        - [**Visualization/**](src/Components/Visualization/) contains UI components used mainly for visualization (e.g ```GUI::Node```, ```GUI::SinglyLinkedList```, etc)
    - [**Core/**](src/Core) contains core data structures and algorithms
    - [**Identifiers/**](src/Identifiers) contains VisuAlgo identifiers for scene, font, and stuff
    - [**States/**](src/States) contains VisuAlgo scene
    - [**Utils/**](src/Utils) contains utility functions
- [**include/**](include) contains the library header files
- [**assets/**](assets) contains the assets of the project
- [**unittest/**](unittest) contains all of the unit tests of the project

## Contributor
22125050 - Nguyen Thanh Phuoc Loc

ntploc21@gmail.com

https://www.facebook.com/ntploc.21/
