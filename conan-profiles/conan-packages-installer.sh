#!/bin/bash

# This script installs the conan packages for the project
# builds: Release, Debug
# compilers: gcc, clang.

conan install . --build=missing --profile:build conan-profile-x64-gcc-debug.txt --profile:host conan-profile-x64-gcc-debug.txt
conan install . --build=missing --profile:build conan-profile-x64-gcc-release.txt --profile:host conan-profile-x64-gcc-release.txt
mv build build-conan-packages-gcc
conan install . --build=missing --profile:build conan-profile-x64-clang-debug.txt --profile:host conan-profile-x64-clang-debug.txt
conan install . --build=missing --profile:build conan-profile-x64-clang-release.txt --profile:host conan-profile-x64-clang-release.txt
mv build build-conan-packages-clang
