cmake_minimum_required(VERSION 3.18)

project(variable)

set(CMAKE_CXX_STANDARD 17)

# Base information
message(STATUS "CMAKE_VERSION: " ${CMAKE_VERSION})
message(STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
message(STATUS "CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR})

# System information
message(STATUS "CMAKE_HOST_SYSTEM_NAME: " ${CMAKE_HOST_SYSTEM_NAME})
message(STATUS "CMAKE_HOST_SYSTEM_PROCESSOR: " ${CMAKE_HOST_SYSTEM_PROCESSOR})
message(STATUS "CMAKE_HOST_SYSTEM_VERSION: " ${CMAKE_HOST_SYSTEM_VERSION})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Build flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O2")

add_executable(
        variable
        main.cpp
)

target_link_libraries(
        variable
)
