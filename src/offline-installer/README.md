# ROCm Offline Installer Creator

## Overview

A tool for creating a pre-configured ROCm component offline installer using OS package management.

The ROCm Offline Installer Creator is a tool which allows a user to create an installer package that can be used to install a pre-configured setup of ROCm and/or the amdgpu driver on a target system without network or internal access.

## Prerequisites

>[Required]

1. One-time network/internet connection when running the offline creator tool.
2. Create system (Host) = Install system (Target)

The system running the creator tool (Host) must match the Linux Distribution Version and Kernel Version for the system where the created installer will be run (Target).

>[Recommended]

1. Host OS image is identical to Target OS image.
2. Host OS does not have ROCm installed.

## Linux Distributions

The offline tool is designed to support the follow list of Linux Distros:

* Ubuntu: `20.04, 22.04, 24.04`
* RHEL  : `8.9, 8.10, 9.2, 9.3, 9.4`
* SLSE  : `15.5, 15.6`

## Linux Distros ROCm Versions Support Matrix

ROCm versions enabled for each distro.

| OS Name        | 5.7.3  | 6.0    | 6.0.1  | 6.0.2  | 6.0.3  | 6.1.x  | 6.2.x  |
| :---           | :----: | :----: | :----: | :----: |  :----:| :----: | :----: |
| Ubuntu 20.04   | Yes    |  Yes   |  Yes   |  Yes   |  Yes   |  Yes   |  Yes   |
| Ubuntu 22.04   | Yes    |  Yes   |  Yes   |  Yes   |  Yes   |  Yes   |  Yes   |
| Ubuntu 24.04   | No     |  No    |  No    |  No    |  No    |  No    |  Yes   |
| Rhel 8.9       | No     |  Yes   |  Yes   |  Yes   |  Yes   |  Yes   |  Yes   |
| Rhel 8.10      | No     |  No    |  No    |  No    |  No    |  No    |  Yes   |
| Rhel 9.2       | Yes    |  Yes   |  Yes   |  Yes   |  Yes   |  Yes   |  Yes   |
| Rhel 9.3       | No     |  Yes   |  Yes   |  Yes   |  Yes   |  Yes   |  Yes   |
| Rhel 9.4       | No     |  No    |  No    |  No    |  No    |  No    |  Yes   |
| Suse 15.5      | Yes    |  No    |  No    |  No    |  Yes   |  Yes   |  Yes   |
| Suse 15.6      | No     |  No    |  No    |  No    |  No    |  No    |  Yes   |

## ROCm Usecases Support Notes

`multimediasdk` is not supported on ROCm 5.7.3 and on 6.2+

## Building

### Prerequisites

The following packages require installation prior to building the Offline installer creator from source.

#### Ubuntu

``` shell
    sudo apt install cmake
    sudo apt install build-essential
    sudo apt install libncurses5-dev
    sudo apt install makeself
    sudo apt install wget
```

#### RHEL

Install the RHEL version-specific prerequisites:

Install the following for RHEL 8.x:

``` shell
    sudo dnf install wget
    wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-8.noarch.rpm
    sudo rpm -ivh epel-release-latest-8.noarch.rpm
    sudo crb enable
```

Install the following for RHEL 9.x:

``` shell
    sudo dnf install wget
    wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-9.noarch.rpm
    sudo rpm -ivh epel-release-latest-9.noarch.rpm
    sudo crb enable
```

Install the generic RHEL x.x prerequisites

``` shell
    sudo dnf install cmake
    sudo dnf install gcc gcc-c++
    sudo dnf install ncurses-devel
    sudo dnf install makeself
```

#### SLSE

Install the following for SLSE 15.5:

``` shell
    sudo SUSEConnect -p PackageHub/15.5/x86_64
```

Install the following for SLSE 15.6:

``` shell
    sudo SUSEConnect -p PackageHub/15.6/x86_64
```

Install the following for SLSE 15.x:

``` shell
    sudo zypper install cmake
    sudo zypper install gcc gcc-c++
    sudo zypper install ncurses-devel
    sudo zypper install makeself
```

### Clone the tool source

``` shell
    git clone git@github.com:ROCm/rocm-install-on-linux-internal.git
```

### Build Configuration

``` shell
    cd src/offline-install
    mkdir build 
    cd build
    cmake ..
```

### Build the tool

Build the Offine installer creator:

``` shell
make
```

* Local build output = rocm-offline-creator_1.0.0-local.run
* ROCm build output  = rocm-offline-creator_1.0.0.602000-1-22.04.run

## Packaging

### Creator .run

The ROCm offline creator tool is packaged as a self-extracting “.run” file that maybe run from any location on the host system creating an offline installer.  

Users have the option of either building the tool from source as described the “Building” section above or by downloading a pre-built version from repo.radeon.com.

On the host system, run the Offline creator tool as follows:

``` shell
    ./rocm-offline-creator_1.0.0-local.run
```

The Offline creator tool may also be run with the following options:

* help     : displays information on how to use the Offline Installer Creator.
* version  : displays the current version of the Offline Installer Creator.
* prompt   : enables user prompts during offline installer creation.
* config=  : specifies the full path to a .config file containing an offline installer
         configuration.  This parameter is used for testing purposes (see Testing).
* wconfig= : specifies the full path to a .config file that will be created with create settings chosen by user in the GUI and exit without creating an installer package. This paramter is used for testing purposes.

For example, to enable user prompts, use the following:

``` shell
    ./rocm-offline-creator_1.0.0-local.run prompt
```

The optional prompt parameter stops the Offline Installer creator at critcial checkpoints in the creation process and prompts the user.  At these checkpoints, the user can either continue or end the program.  Without the prompt parameter, installer creation continues without interruption, unless a failure occurs during the process.

### Installer .run

Once the configuration for a new installer was been selected from the Offline creator tool UI and “CREATE” initiated, the tool will then proceed to create another self-extracting “.run” representing the pre-configure ROCm/Driver setup.  The new “.run” is the installer package which may then be installed on “matching” target system without an internet connection (see prerequisties above).

On the target system, run the new Installer to install ROCm and/or the driver as follows:

``` shell
    ./rocm-offline-install.run
```

When run, the installer package will automatically install all ROCm and/or amdgpu driver packages and their dependencies on the target system.

The installer package may also be run with the following options:

* prompt   : enables user prompts during installion process.
* dryrun   : simulates the installation process without installing associated packages.

### Log Files

By default, the Offline Installer creator will record it's execution output to log files located in the /var/log/offline_creator directory.  The output of both creation and installation processes will written out to this directory.

## Testing

Testing of the offline creator tool has pre-set tests that maybe run to validate some of common installer configurations simulating and testing the creation of the target offline installer and running of the outputted installer.

Tests are based on the ROCm version and on the usecase being installed:

* ROCm Version: `5.7.3, 6.0.2, 6.1.x, and 6.2.x`

* Usecases    : `ROCm only, Driver only, ROCm + Driver, rocm + graphics, hip + hiplibsdk`

  * ROCm only      = Create an installer for the ROCm usecase only.
  * Driver only    = Create an installer for the amdgpu driver only.
  * ROCm + Driver  = Create an installer for both the ROCm usecase and the amdgpu driver.
  * ROCm,graphics  = Create an installer for the rocm,graphics usecase.
  * Hip, Hiplibsdk = Create an installer for the hip,hiplibsdk usescase.

### Test Build

Test are built using CMake and make.  See the “Building” section above.

### Test Run using CTest

All pre-configured tests are run using CMake and CTest utilities.

There are 3 types of tests:

1. Full test
2. ROCm Version test
3. CI test

#### Full Test

From the build location of the offline tool, run the following:

``` shell
ctest
```

A total of 90 tests will be run:

ROCm Version

* 6.2.x: ROCm only, Driver only, ROCm + Driver, ROCm + graphics, hip + hiplibsdk
* 6.1.x: ROCm only, Driver only, ROCm + Driver, ROCm + graphics, hip + hiplibsdk
* 6.0.2: ROCm only, Driver only, ROCm + Driver, ROCm + graphics, hip + hiplibsdk
* 5.7.3: ROCm only, Driver only, ROCm + Driver, ROCm + graphics, hip + hiplibsdk

#### ROCm Version Test

Subsets of the “Full” test can be selected and run via Ctest for specific versions of ROCm (5.7.3, 6.0.2, 6.1.0, etc.).
From the build location of the offline tool, run the following:

``` shell
ctest -L <rocm-version> 
```

rocm-version = 5.7.3, 6.0.2, 6.1.x, or 6.2.x

#### CI Test

This subset of tests (ROCm+Driver) represents those run for CI/CD.
From the build location of the offline tool, run the following:

``` shell
ctest -L ci 
```

### Ctest ROCm Version matrix

A matrix describing what ROCm ctests are enabled for each distro.
NOTE: There are no ctests for rocm versions 6.0.0, 6.0.1 and 6.0.3

| OS Name        | 5.7.3  | 6.0.2  | 6.1.x  | 6.2.x  |
| :---           | :----: | :----: | :----: | :----: |
| Ubuntu 20.04   | Yes    |  Yes   | Yes    | Yes    |
| Ubuntu 22.04   | Yes    |  Yes   | Yes    | Yes    |
| Ubuntu 24.04   | No     |  No    | No     | Yes    |
| Rhel 8.9       | No     |  Yes   | Yes    | Yes    |
| Rhel 8.10      | No     |  No    | No     | Yes    |
| Rhel 9.2       | Yes    |  Yes   | Yes    | Yes    |
| Rhel 9.3       | No     |  Yes   | Yes    | Yes    |
| Rhel 9.4       | No     |  No    | No     | Yes    |
| Suse 15.5      | Yes    |  Yes   | Yes    | Yes    |
| Suse 15.6      | No     |  No    | No     | Yes    |

### Test Run using .config

Outside of the pre-configured CTests, users have the option of manually configuring their own tests for the Offline Installer creator.  To manually test the creation of an offline installer without the UI interface, use the "config=" parameter when running the creator tool:

``` shell
    ./rocm-offline-creator_1.0.0-local.run config=<path-to-config-file>
```

The "config=" parameter is set to the absolute path to a configuration file, which must include the ".config" file extension.  The file itself has a specific format defined by the UI of the creator tool.  Example config files are available in the current "tests" directory of the offline-installer repository, which themselves are used for running the CTests above.

For example, run the ROCm + Driver 6.1.3 test using the "config=" parameter as follows assuming the offline-installer source is located in the $HOME directory:

``` shell
    ./rocm-offline-creator_1.0.0-local.run config=$HOME/offline-installer/tests/create-test-rocm-driver-6.1.3.config
```
