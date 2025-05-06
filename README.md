# Finance Tracker
![Build](https://github.com/mapi-ng/finance_tracker/actions/workflows/cmake-multi-platform.yml/badge.svg) [![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=mapi-ng_finance_tracker&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=mapi-ng_finance_tracker)

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
4. Detect Conan profile (optional)
    ```
    conan profile detect --force
    ```
5. Install packages from Conanfile.txt using provided profiles.
    ```
    cd conan-profiles
    ./conan-packages-installer.sh
    ```
    Script will install packages for preset configurations.

## Configuring, building and testing

Following commands will configure, build and run tests for the project based on the specified preset from `CMakePresets.json`

```
cmake --preset [preset]
cmake --build --preset [preset]
```

For example:

```
cmake --preset gcc-debug
cmake --build --preset gcc-debug
```
