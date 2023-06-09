cmake_minimum_required(VERSION 3.22)
project(CS162-VisuAlgo)



# Enable project web version compilation
if (EMSCRIPTEN)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 --preload-file assets -s ASYNCIFY -sALLOW_MEMORY_GROWTH")
    set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it.
endif ()

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
enable_testing()
include(CTest)

add_executable(core_base_list_test_exe
    unittest/doctest_main.cpp
    unittest/List.test.cpp
)

add_executable(core_stack_test_exe
    unittest/doctest_main.cpp
    unittest/Stack.test.cpp
)

add_executable(core_queue_test_exe
    unittest/doctest_main.cpp
    unittest/Queue.test.cpp
)

target_include_directories(core_base_list_test_exe PRIVATE include)
target_include_directories(core_stack_test_exe PRIVATE include)
target_include_directories(core_queue_test_exe PRIVATE include)

if(NOT MSVC)
    target_link_directories(core_base_list_test_exe PRIVATE -fsanitize=address,undefined,leak -g)
    target_link_directories(core_base_list_test_exe PRIVATE -fsanitize=address,undefined,leak -g)
    target_link_directories(core_base_list_test_exe PRIVATE -fsanitize=address,undefined,leak -g)
endif()

add_test(core_base_list_test core_base_list_test_exe)
add_test(core_stack_test core_stack_test_exe)
add_test(core_queue_test core_queue_test_exe)

add_custom_target(run_base_list_test ALL
    COMMAND ctest --output-on-failure
    DEPENDS core_base_list_test_exe)

add_custom_target(run_stack_test ALL
    COMMAND ctest --output-on-failure
    DEPENDS core_stack_test_exe)

add_custom_target(run_queue_test ALL
    COMMAND ctest --output-on-failure
    DEPENDS core_queue_test_exe)

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
    src/FontHolder.cpp
    src/TextureHolder.cpp
    src/Component.cpp
    src/Container.cpp
    src/Settings.cpp
    src/Identifiers/CategoryInfo.cpp
    src/Identifiers/DSInfo.cpp

    # States
    src/States/HomepageState.cpp
    ## Array
    src/States/Array/StaticArrayState.cpp
    src/States/Array/DynamicArrayState.cpp
    # src/States/Array/ArrayState.cpp
    # src/States/Array/ArrayState.cpp

    ## Linked List
    src/States/LinkedList/SLLState.cpp
    src/States/LinkedList/DLLState.cpp
    src/States/LinkedList/CLLState.cpp
    src/States/LinkedList/StackState.cpp
    src/States/LinkedList/QueueState.cpp
    # src/States/LinkedList/LLState.cpp
    # src/States/LinkedList/LLState.cpp

    # Components
    ## Common
    src/Components/Common/NavigationBar.cpp
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
    src/Components/Visualization/LinkedList.cpp
    src/Components/Visualization/SinglyLinkedList.cpp
    src/Components/Visualization/DoublyLinkedList.cpp
    src/Components/Visualization/CircularLinkedList.cpp
    src/Components/Visualization/DynamicArray.cpp
    
    # Core
    ## Animation
    # src/Core/Animation/AnimationController.cpp
    # src/Core/Animation/AnimationState.cpp
    src/Animation/AnimationFactory.cpp
    # src/Core/Animation/AnimationController.cpp
    # src/Core/Animation/AnimationState.cpp
    src/Animation/AnimationFactory.cpp

    ## Algorithms
    ### Array
    src/Algorithms/Array/StaticArray.cpp
    src/Algorithms/Array/DynamicArray.cpp
    ### LinkedList
    # src/Core/DataStructures/LinkedList/BaseNode.hpp
    src/Algorithms/LinkedList/CircularLinkedList.cpp
    src/Algorithms/LinkedList/DoublyLinkedList.cpp
    src/Algorithms/LinkedList/SinglyLinkedList.cpp
    src/Algorithms/LinkedList/Queue.cpp
    src/Algorithms/LinkedList/Stack.cpp
    
    ## Utils
    src/Utils/Utils.cpp
    include/tinyfiledialogs.c
)

target_link_libraries(${PROJECT_NAME} raylib)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC include)

# Copy assets to build folder

# idk what i am doing
file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})