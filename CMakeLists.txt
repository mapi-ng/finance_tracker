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

# Include Conan toolchain file if available
if(DEFINED ENV{CONAN_PROFILES_DIR})
    set(CONAN_TOOLCHAIN_FILE "$ENV{CONAN_PROFILES_DIR}")
else()
    set(CONAN_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/conan-profiles")
endif()

set(CONAN_TOOLCHAIN_FILE "${CONAN_TOOLCHAIN_FILE}/${CONAN_INSTALL_DIR}/${CMAKE_BUILD_TYPE}/generators/conan_toolchain.cmake")
if(EXISTS ${CONAN_TOOLCHAIN_FILE})
    include(${CONAN_TOOLCHAIN_FILE})
else()
    message(WARNING "Skipping Conan integration. Path ${CONAN_TOOLCHAIN_FILE} does not exist.")
endif()

include(CTest)
add_subdirectory(core)
add_subdirectory(utils)
