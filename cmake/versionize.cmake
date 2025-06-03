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

# Write the version to a header file
file(WRITE ${VERSION_HEADER} "#pragma once\n")
file(APPEND ${VERSION_HEADER} "constexpr auto APP_VERSION = \"${GIT_VERSION}\";\n")

# Include the generated file directory
include_directories(${CMAKE_BINARY_DIR}/generated)

# Generate SonarQube properties file

file(WRITE "${CMAKE_SOURCE_DIR}/sonar-project.properties"
"sonar.projectName=${PROJECT_NAME}
sonar.projectKey=mapi-ng_${PROJECT_NAME}
sonar.organization=mapi-ng
sonar.projectVersion=${GIT_VERSION_ROOT}

sonar.sources=.
sonar.sourceEncoding=UTF-8

sonar.cfamily.enableModules=true
")
