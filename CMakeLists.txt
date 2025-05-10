cmake_minimum_required(VERSION 4.0)
project(finance_tracker LANGUAGES CXX)
message(STATUS "==== Configuring ${PROJECT_NAME} for ${CMAKE_SYSTEM_NAME} ====")

if(UNIX)
    set(CMAKE_GENERATOR "Ninja")
    if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
        message(FATAL_ERROR "This project requires the Ninja generator.")
    endif()
endif()

# Create version header and CMake variable
include(cmake/versionize.cmake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compiler commands for C/C++ intellisense, SonarLint, etc.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra)
endif()

include(cmake/find-conan-toolchain.cmake)
include(CTest)
add_subdirectory(core)
add_subdirectory(utils)
add_subdirectory(storage)
