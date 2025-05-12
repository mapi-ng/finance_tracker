# Get software version from git tag

# Define path for generated file
set(VERSION_HEADER "${CMAKE_BINARY_DIR}/generated/version.h")

# Generate root of the version tag, without the 'v' prefix
execute_process(
    COMMAND git describe --tags --abbrev=0
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_VERSION_ROOT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(REGEX REPLACE "^v" "" GIT_VERSION_ROOT "${GIT_VERSION_ROOT}")

# Generate the full version string
execute_process(
    COMMAND git describe --tags --dirty --always
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "${PROJECT_NAME} version: ${GIT_VERSION}")
