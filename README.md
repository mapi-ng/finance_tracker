# Finance Tracker

![Build](https://github.com/mapi-ng/finance_tracker/actions/workflows/cmake-multi-platform.yml/badge.svg) [![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=mapi-ng_finance_tracker&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=mapi-ng_finance_tracker)

## Description

Simple budgeting application for tracking personal expenses and income.

The side purpose of this project is to learn using C++ modules
and put in practice general knowledge of modern C++.

## Prerequisites

### Development in Docker container

Project can be opened using VSCode development containers plugin,
using the following image:
[maping4/ubuntu_cpp](https://hub.docker.com/repository/docker/maping4/ubuntu_cpp/general)

### Standalone configuration requirements

For full configuration refer to [Dockerfile](https://github.com/mapi-ng/docker_files/blob/main/ubuntu_cpp/Dockerfile)

## Configuring, building and testing

Following commands will configure, build and run tests for the project based on the specified preset from
`CMakePresets.json`

```
cmake --preset [preset]
cmake --build --preset [preset]
ctest --preset [preset] --output-on-failure
```

For example:

```
cmake --preset gcc-debug
cmake --build --preset gcc-debug
ctest --preset gcc-debug --output-on-failure
```
