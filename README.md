# Finance Tracker

## Prerequisites

Conan package manager
To install Conan, follow these steps:

1. Make sure Python is installed.

2. Install Conan using pip:
    ```
    pipx install conan
    ```

3. Verify the installation:
    ```
    conan --version
    ```
4. Detect Conan profile
    ```
    conan profile detect --force
    ```
    It will be named `default`
5. Install packages from Conanfile.txt using included profiles.
    ```
    conan install . --build=missing -pr ./conan-profiles/conan-profile-x64-gcc-debug.txt
    conan install . --build=missing -pr ./conan-profiles/conan-profile-x64-gcc-release.txt
    ```

## Build

```
cmake -B build -S . -G Ninja
```