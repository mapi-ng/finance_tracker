# Get software version from git tag

# Define path for generated file
set(VERSION_HEADER "${CMAKE_BINARY_DIR}/generated/version.h")

execute_process(
    COMMAND git describe --tags --dirty --always
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "${PROJECT_NAME} version: ${GIT_VERSION}")

# Write the version to a header file
file(WRITE ${VERSION_HEADER} "#pragma once\n")
file(APPEND ${VERSION_HEADER} "constexpr auto APP_VERSION = \"${GIT_VERSION}\";\n")

# Include the generated file directory
include_directories(${CMAKE_BINARY_DIR}/generated)