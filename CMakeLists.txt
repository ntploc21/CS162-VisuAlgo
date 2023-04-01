cmake_minimum_required(VERSION 3.22)
project(CS162-VisuAlgo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# Raylib
set(RAYLIB_VERSION 4.2.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # Fetch/download and build raylib
    include(FetchContent)
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

######################################

# YAML

# set(YAML_VERSION 0.6.0)
# find_package(yaml-cpp REQUIRED)
# if(NOT yaml-cpp_FOUND) # Fetch/download yaml-cpp
# include_directories(${YAML_INCLUDE_DIRS})
# target_link_libraries(${YAML_CPP_LIBRARIES})

######################################

# Unit testing

######################################

# Include libraries and source files

link_directories(lib)
include_directories(src)
add_executable(${PROJECT_NAME}
    # Main folder
    src/Main.cpp
    src/Application.cpp
    src/State.cpp
    src/StateStack.cpp
    src/SceneNode.cpp
    src/FontHolder.cpp

    # States
    src/States/HomepageState.cpp
    src/States/SettingsState.cpp
    ## Array
    src/States/Array/StaticArrayState.cpp
    src/States/Array/DynamicArrayState.cpp

    ## Linked List
    src/States/LinkedList/SLLState.cpp
    src/States/LinkedList/DLLState.cpp
    src/States/LinkedList/CLLState.cpp
    src/States/LinkedList/StackState.cpp
    src/States/LinkedList/QueueState.cpp

    # Components
    src/Components/NavigationBar.cpp
)

target_link_libraries(${PROJECT_NAME} raylib)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC include)

# Copy assets to build folder

add_custom_target(assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(${PROJECT_NAME} assets)

######################################

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_CURRENT_SOURCE_DIR})