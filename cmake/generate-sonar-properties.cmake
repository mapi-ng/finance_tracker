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
sonar.test.inclusions=**/test/**

sonar.cfamily.enableModules=true
sonar.test.inclusions=**/test/**
")
