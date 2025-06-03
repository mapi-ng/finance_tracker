#!/bin/bash

gcovr -r . \
    --exclude-unreachable-branches \
    -e '.*/CMakeFiles.*' \
    -e '.*/test.*' \
    --print-summary \
    --sonarqube \
    --output coverage.xml