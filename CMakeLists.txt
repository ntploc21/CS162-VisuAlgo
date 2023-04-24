cmake_minimum_required(VERSION 3.22)
project(CS162-VisuAlgo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

######################################

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

# Unit testing

# enable_testing()
# include(CTest)

# add_executable(core_base_create_test_exe
#     UnitTest/doctest_main.cpp
#     UnitTest/Operations/Create/Create.test.cpp
#     src/Core/Operations/Create/Create.cpp
# )

# add_executable(core_base_singly_linked_list_exe
#     UnitTest/doctest_main.cpp
#     UnitTest/DataStructures/SinglyLinkedList.test.cpp
#     # src/Core/DataStructures/LinkedList/SinglyLinkedList.hpp
#     src/Core/Operations/Create/Create.cpp
# )

# target_include_directories(core_base_create_test_exe PRIVATE include)
# target_include_directories(core_base_singly_linked_list_exe PRIVATE include)

# if(NOT MSVC)
#     target_link_directories(core_base_create_test_exe PRIVATE -fsanitize=address,undefined,leak -g)
#     target_link_directories(core_base_singly_linked_list_exe PRIVATE -fsanitize=address,undefined,leak -g)
# endif()

# add_test(core_base_create_test core_base_create_test_exe)

# add_test(core_base_singly_linked_list core_base_singly_linked_list_exe)

# add_custom_target(run_base_create_test ALL
#     COMMAND ctest --output-on-failure
#     DEPENDS core_base_create_test_exe)

# add_custom_target(run_base_singly_linked_list ALL
#     COMMAND ctest --output-on-failure
#     DEPENDS core_base_singly_linked_list_exe)

# YAML

# set(YAML_VERSION 0.6.0)
# find_package(yaml-cpp REQUIRED)
# if(NOT yaml-cpp_FOUND) # Fetch/download yaml-cpp
# include_directories(${YAML_INCLUDE_DIRS})
# target_link_libraries(${YAML_CPP_LIBRARIES})

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
    src/TextureHolder.cpp
    src/Component.cpp
    src/Container.cpp
    src/Identifiers/CategoryInfo.cpp
    src/Identifiers/DSInfo.cpp
    src/Utils.cpp

    # States
    src/States/HomepageState.cpp
    src/States/SettingsState.cpp
    ## Array
    src/States/Array/StaticArrayState.cpp
    src/States/Array/DynamicArrayState.cpp
    # src/States/Array/ArrayState.cpp

    ## Linked List
    src/States/LinkedList/SLLState.cpp
    src/States/LinkedList/DLLState.cpp
    src/States/LinkedList/CLLState.cpp
    src/States/LinkedList/StackState.cpp
    src/States/LinkedList/QueueState.cpp
    # src/States/LinkedList/LLState.cpp

    # Components
    ## Common
    src/Components/Common/NavigationBar.cpp
    src/Components/Common/Footer.cpp
    src/Components/Common/Card.cpp
    src/Components/Common/OperationList.cpp
    src/Components/Common/OperationContainer.cpp
    src/Components/Common/Button.cpp
    src/Components/Common/OptionInputField.cpp
    src/Components/Common/InputField.cpp
    src/Components/Common/StringInputField.cpp
    src/Components/Common/IntegerInputField.cpp
    src/Components/Common/CodeHighlighter.cpp
    ## Visualization
    src/Components/Visualization/Node.cpp
    src/Components/Visualization/DataStructure.cpp
    src/Components/Visualization/SinglyLinkedList.cpp
    
    # Core
    ## Animation
    # src/Core/Animation/AnimationController.cpp
    # src/Core/Animation/AnimationState.cpp
    src/Core/Animation/AnimationFactory.cpp

    ## Algorithms
    ### Array
    src/Core/Algorithms/Array/StaticArray.cpp
    ### LinkedList
    # src/Core/DataStructures/LinkedList/BaseNode.hpp
    # src/Core/Algorithms/Algorithm.cpp
    src/Core/Algorithms/LinkedList/SinglyLinkedList.cpp
    src/Core/Algorithms/LinkedList/Queue.cpp
    src/Core/Algorithms/LinkedList/Stack.cpp
    

    ### Add

    ### Update

    ### Search

    ### Delete

    ### Export
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