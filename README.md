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
## Build

```
cmake -B build -S . -G Ninja
```