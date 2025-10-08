cmake_minimum_required(VERSION 3.16)

project(Modern-CPP-CFS-Scheduler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Define all source files in a list ---
set(SOURCES
    main.cpp
    src/cfs.cpp
    src/cpuBoundProcessExecution.cpp
    src/ioBoundProcessExecution.cpp
    src/processService.cpp
    src/queueService.cpp
)

# --- Create the executable and add sources at the same time ---
add_executable(${PROJECT_NAME} ${SOURCES})

# --- Add Include Directories ---
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/nlohmann"
)

# --- Add Compiler Warnings ---
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
