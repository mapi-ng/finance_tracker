#!/bin/bash

gcovr -r . \
    --exclude-unreachable-branches \
    -e '.*/CMakeFiles.*' \
    -e '.*/test.*' \
    --exclude-throw-branches \
    --print-summary \
    --sonarqube \
    --output coverage.xml