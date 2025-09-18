# ##############################################################################
# Copyright (c) 2024-2025 Advanced Micro Devices, Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# ##############################################################################

cmake_minimum_required(VERSION 3.6)

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" VERSION_FILE_CONTENT)
string(REPLACE "\n" ";" VERSION_STRING_LIST ${VERSION_FILE_CONTENT})
list(GET VERSION_STRING_LIST 0 VERSION_STRING)
list(GET VERSION_STRING_LIST 1 ROCM_VERSION_STRING)

project(offline_install_tool VERSION ${VERSION_STRING} LANGUAGES C)

set(OFFLINE_TOOL_NAME "rocm-offline-creator_")

# Check for the Distro
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    execute_process (
        COMMAND bash -c "awk -F= '/^ID=/{print $2}' /etc/os-release |tr -d '\n' | tr -d '\"'"
        OUTPUT_VARIABLE distro
    )

    # Ubuntu 20.04
    execute_process (
        COMMAND bash -c "grep '20.04' /etc/os-release"
        OUTPUT_VARIABLE IS_UBUNTU_2004
    )

    # Ubuntu 22.04
    execute_process (
        COMMAND bash -c "grep '22.04' /etc/os-release"
        OUTPUT_VARIABLE IS_UBUNTU_2204
    )

    # Ubuntu 24.04
    execute_process (
        COMMAND bash -c "grep '24.04' /etc/os-release"
        OUTPUT_VARIABLE IS_UBUNTU_2404
    )

    # Suse 15.5
    execute_process (
        COMMAND bash -c "grep '15.5' /etc/os-release"
        OUTPUT_VARIABLE IS_SLES_155
    )

    # Suse 15.6
    execute_process (
        COMMAND bash -c "grep '15.6' /etc/os-release"
        OUTPUT_VARIABLE IS_SLES_156
    )

    # Suse 15.6
    execute_process (
        COMMAND bash -c "grep '15.7' /etc/os-release"
        OUTPUT_VARIABLE IS_SLES_157
    )
    
    # Rhel 8.9
    execute_process (
        COMMAND bash -c "grep 'Red Hat Enterprise Linux 8.9' /etc/os-release"
        OUTPUT_VARIABLE IS_RHEL_89
    )

    # Rhel 8.10
    execute_process (
        COMMAND bash -c "grep 'Red Hat Enterprise Linux 8.10' /etc/os-release"
        OUTPUT_VARIABLE IS_RHEL_810
    )

    # Rhel 9.2
    execute_process (
        COMMAND bash -c "grep '9.3' /etc/os-release"
        OUTPUT_VARIABLE IS_RHEL_93
    )

    # Rhel 9.3
    execute_process (
        COMMAND bash -c "grep '9.2' /etc/os-release"
        OUTPUT_VARIABLE IS_RHEL_92
    )

    # Rhel 9.4
    execute_process (
        COMMAND bash -c "grep 'Red Hat Enterprise Linux 9.4' /etc/os-release"
        OUTPUT_VARIABLE IS_RHEL_94
    )

    # Rhel 9.5
    execute_process (
        COMMAND bash -c "grep 'Red Hat Enterprise Linux 9.5' /etc/os-release"
        OUTPUT_VARIABLE IS_RHEL_95
    )

    # Rhel 9.6
    execute_process (
        COMMAND bash -c "grep 'Red Hat Enterprise Linux 9.6' /etc/os-release"
        OUTPUT_VARIABLE IS_RHEL_96
    )

    # Oracle Linux 8.10
    execute_process (
        COMMAND bash -c "grep 'Oracle Linux Server 8.10' /etc/os-release"
        OUTPUT_VARIABLE IS_OL_810
    )

    # Oracle Linux 9.5
    execute_process (
        COMMAND bash -c "grep 'Oracle Linux Server 9.5' /etc/os-release"
        OUTPUT_VARIABLE IS_OL_95
    )

    # Oracle Linux 9.6
    execute_process (
        COMMAND bash -c "grep 'Oracle Linux Server 9.6' /etc/os-release"
        OUTPUT_VARIABLE IS_OL_96
    )

    # Debian 12
    execute_process (
        COMMAND bash -c "grep 'Debian GNU/Linux 12' /etc/os-release"
        OUTPUT_VARIABLE IS_DEBIAN_12
    )

    # Rocky 9.6
    execute_process (
        COMMAND bash -c "grep 'Rocky Linux 9.6' /etc/os-release"
        OUTPUT_VARIABLE IS_ROCKY_96 
    )

    message(STATUS "Linux distro: ${distro}")
    message(STATUS "IS_SLES_155: ${IS_SLES_155}")
    message(STATUS "IS_SLES_156: ${IS_SLES_156}")
    message(STATUS "IS_SLES_157: ${IS_SLES_157}")
    message(STATUS "IS_RHEL_89: ${IS_RHEL_89}")
    message(STATUS "IS_RHEL_810: ${IS_RHEL_810}")
    message(STATUS "IS_RHEL_92: ${IS_RHEL_92}")
    message(STATUS "IS_RHEL_93: ${IS_RHEL_93}")
    message(STATUS "IS_RHEL_94: ${IS_RHEL_94}")
    message(STATUS "IS_RHEL_95: ${IS_RHEL_95}")
    message(STATUS "IS_RHEL_96: ${IS_RHEL_96}")
    message(STATUS "IS_RHEL_100: ${IS_RHEL_100}")
    message(STATUS "IS_UBUNTU_2004: ${IS_UBUNTU_2004}")
    message(STATUS "IS_UBUNTU_2204: ${IS_UBUNTU_2204}")
    message(STATUS "IS_UBUNTU_2404: ${IS_UBUNTU_2404}")
    message(STATUS "IS_OL_810: ${IS_OL_810}")
    message(STATUS "IS_OL_95: ${IS_OL_95}")
    message(STATUS "IS_OL_96: ${IS_OL_96}")
    message(STATUS "IS_OL_100: ${IS_OL_100}")
    message(STATUS "IS_DEBIAN_12: ${IS_DEBIAN_12}")
    message(STATUS "IS_DEBIAN_13: ${IS_DEBIAN_13}")
    message(STATUS "IS_ROCKY_96: ${IS_ROCKY_96}")
else()
    message(FATAL_ERROR "No OS detected!")
endif()

# Set the script directory for the distro
if(${distro} STREQUAL "ubuntu" OR ${distro} STREQUAL "debian")
    message(STATUS "Building for Ubuntu")
    set(SCRIPT_DIRECTORY ${CMAKE_SOURCE_DIR}/scripts/deb)
elseif(${distro} STREQUAL "rocky" OR ${distro} STREQUAL "rhel" OR ${distro} STREQUAL "ol")
    message(STATUS "Building for RHEL")
    set(SCRIPT_DIRECTORY ${CMAKE_SOURCE_DIR}/scripts/el)
elseif(${distro} STREQUAL "opensuse-leap" OR ${distro} STREQUAL "sles")
    message(STATUS "Building for Suse")
    set(SCRIPT_DIRECTORY ${CMAKE_SOURCE_DIR}/scripts/sle)
else()
    message(FATAL_ERROR "Unsupported Distro : ${distro}")
endif()

# Dependency check
find_program(MAKESELF makeself)

if(MAKESELF)
    # Execute makeself to get its version
    execute_process(COMMAND ${MAKESELF} --version OUTPUT_VARIABLE MAKESELF_VERSION_OUTPUT)

    # Extract the version number
    string(REGEX MATCH "Makeself version [0-9]+\\.[0-9]+\\.[0-9]+" MAKESELF_VERSION_STRING ${MAKESELF_VERSION_OUTPUT})
    string(REGEX REPLACE "Makeself version " "" MAKESELF_VERSION ${MAKESELF_VERSION_STRING})

    # Check if the makeself version >= 2.4.2 for supporting cleanup scripts
    if(${MAKESELF_VERSION} VERSION_GREATER_EQUAL "2.4.2")
        message(STATUS "makeself version is ${MAKESELF_VERSION}, which is >= 2.4.2")
        # The value of the file path passed via --header and --help-header 
        # must point to the file path in its actual location while running 
        # the makeself command.
        set(MAKESELF_OPTIONS --cleanup ./cleanup-create.sh --header ${SCRIPT_DIRECTORY}/rocm-makeself-header.sh --help-header ${CMAKE_CURRENT_SOURCE_DIR}/VERSION)
    endif()
else()
    message(FATAL_ERROR "makeself is required to build the offline installer. Please install it.")
endif()

message(STATUS "+++++++++++++++++++++++++++")
message(STATUS "ROCm Offline Installer Tool")
message(STATUS "+++++++++++++++++++++++++++")

message(STATUS "VERSION_STRING      = " ${VERSION_STRING})
message(STATUS "ROCM_VERSION_STRING = " ${ROCM_VERSION_STRING})
message(STATUS "MAKESELF_VERSION    = " ${MAKESELF_VERSION})
message(STATUS "MAKESELF_OPTIONS    = " ${MAKESELF_OPTIONS})

enable_testing()
# URL configs but only used if you're running ctests
if(DEFINED URL_CONFIG)
    set(URL_CONFIG ${URL_CONFIG}/url.config)
    message(STATUS "Setting value of URL_CONFIG to '${URL_CONFIG}'")
else()
    set(URL_CONFIG $ENV{HOME}/url.config)
    message(STATUS "Setting value of URL_CONFIG to its default value '${URL_CONFIG}'")
endif()

if(DEFINED BUILD_INTERNAL)
    if (${BUILD_INTERNAL} STREQUAL "0")
        message(STATUS "Building public version of offline installer")
    elseif(${BUILD_INTERNAL} STREQUAL "1")
        message(STATUS "Building internal version of offline installer")
    else()
        message(FATAL_ERROR "Value of BUILD_INTERNAL must be either 0 or 1. User set it to ${BUILD_INTERNAL}")
    endif()
    message(STATUS "Setting value of macro BUILD_INTERNAL=${BUILD_INTERNAL}")
    add_definitions(-DBUILD_INTERNAL=${BUILD_INTERNAL})
endif()

# Set the package name
if(DEFINED ENV{ROCM_LIBPATCH_VERSION})
    message(STATUS "ROCM LIPATCH Defined.")
    set(PACKAGE_VERSION "${PROJECT_VERSION}.$ENV{ROCM_LIBPATCH_VERSION}")
else()
    set(PACKAGE_VERSION ${PROJECT_VERSION})
endif()

set(PACKAGE_NAME "${OFFLINE_TOOL_NAME}${PACKAGE_VERSION}-")


if (DEFINED ENV{DISTRO_PACKAGE_RELEASE})
    set(PACKAGE_NAME ${PACKAGE_NAME}$ENV{DISTRO_PACKAGE_RELEASE})
else()
    set(PACKAGE_NAME "${PACKAGE_NAME}local")
endif()

set(IS_DOCKER_CONTAINER 0)
if(DEFINED ENV{container})
    set(IS_DOCKER_CONTAINER 1)
endif()

message(STATUS: "Value of IS_DOCKER_CONTAINER: ${IS_DOCKER_CONTAINER}")


# All ROCm tests enabled by default
set(IS_ROCM_61_DISABLED 0)
set(IS_ROCM_611_DISABLED 0)
set(IS_ROCM_612_DISABLED 0)
set(IS_ROCM_613_DISABLED 0)
set(IS_ROCM_62_DISABLED 0)
set(IS_ROCM_621_DISABLED 0)
set(IS_ROCM_622_DISABLED 0)
set(IS_ROCM_624_DISABLED 0)
set(IS_ROCM_63_DISABLED 0)
set(IS_ROCM_631_DISABLED 0)
set(IS_ROCM_632_DISABLED 0)
set(IS_ROCM_633_DISABLED 0)
set(IS_ROCM_64_DISABLED 0)
set(IS_ROCM_641_DISABLED 0)
set(IS_ROCM_642_DISABLED 0)
set(IS_ROCM_643_DISABLED 0)
set(IS_ROCM_70_DISABLED 1)
set(IS_ROCM_701_DISABLED 0)

# ROCm only 6.4.1 installation test
set(IS_LATEST_RELEASE_ROCM_INSTALL_DISABLED 1)

# ROCm 6.4.1 dryrun test
# if IS_LATEST_RELEASE_ROCM_INSTALL_DISABLED is set to true, then this is set to false and vice versa
set(IS_LATEST_RELEASE_ROCM_INSTALL_DRYRUN_DISABLED 0)

# Only enabled ROCm only 6.4.3 installation test on these distros in docker containers only
if ((IS_SLES_156 OR IS_RHEL_810 OR IS_RHEL_94 OR IS_RHEL_96 OR IS_UBUNTU_2204 
OR IS_UBUNTU_2404 OR IS_DEBIAN_12 OR IS_OL_810 OR IS_OL_96) AND IS_DOCKER_CONTAINER EQUAL 1)
    message(STATUS "Enable installation test for rocm only for ROCm 6.4.3")
    set(IS_LATEST_RELEASE_ROCM_INSTALL_DISABLED 0)
    set(IS_LATEST_RELEASE_ROCM_INSTALL_DRYRUN_DISABLED 1)
endif()

# Latest rocm 6.4.x not supported on rhel 8.9, 9.2 and 9.3
if (IS_RHEL_93 OR IS_RHEL_92 OR IS_RHEL_89 OR IS_SLES_155)
    set(IS_LATEST_RELEASE_ROCM_INSTALL_DISABLED 1)
    set(IS_LATEST_RELEASE_ROCM_INSTALL_DRYRUN_DISABLED 1)
endif()

# Disable ROCm tests older than 6.2 for sles 15.6, rhel 8.10, rhel 9.4 and ubuntu 24.04
if (IS_RHEL_810 OR IS_RHEL_94 OR IS_UBUNTU_2404)
    if (IS_RHEL_94 AND IS_DOCKER_CONTAINER EQUAL 1)
        # Can't create rocm 6.2.x packages on RHEL 9.4 docker because it wants to uninstall
        # system protected package systemd-udev
        message(STATUS "Disable all ROCm tests on ROCm 6.2.x on RHEL 9.4 dockers as they fail.")
        set(IS_ROCM_62_DISABLED 0)
        set(IS_ROCM_621_DISABLED 0)
        set(IS_ROCM_622_DISABLED 0)
        set(IS_ROCM_624_DISABLED 0)
    endif()
    message(STATUS "Disable all ROCm tests older than 6.2 on RHEL 8.10, RHEL 9.4 and Ubuntu 24.04")
    set(IS_ROCM_61_DISABLED 1)
    set(IS_ROCM_611_DISABLED 1)
    set(IS_ROCM_612_DISABLED 1)
    set(IS_ROCM_613_DISABLED 1)
elseif (IS_RHEL_93 OR IS_RHEL_89)
    message(STATUS "Disable all ROCm tests older than 6.0 and newer than 6.3 for RHEL 8.9, 9.3")
    set(IS_ROCM_63_DISABLED 1)
    set(IS_ROCM_631_DISABLED 1)
    set(IS_ROCM_632_DISABLED 1)
    set(IS_ROCM_633_DISABLED 1)
    set(IS_ROCM_64_DISABLED 1)
    set(IS_ROCM_641_DISABLED 1)
    set(IS_ROCM_642_DISABLED 1)
    set(IS_ROCM_643_DISABLED 1)
    set(IS_ROCM_70_DISABLED 1)
    set(IS_ROCM_701_DISABLED 1)
    set(IS_LATEST_RELEASE_ROCM_INSTALL_DISABLED 1)
    set(IS_LATEST_RELEASE_ROCM_INSTALL_DRYRUN_DISABLED 1)
elseif (IS_RHEL_92) 
    message(STATUS "Disable all ROCm tests 6.2 or newer for RHEL 9.2")
    set(IS_LATEST_RELEASE_ROCM_INSTALL_DRYRUN_DISABLED 1)
    set(IS_ROCM_62_DISABLED 1)
    set(IS_ROCM_621_DISABLED 1)
    set(IS_ROCM_622_DISABLED 1)
    set(IS_ROCM_624_DISABLED 1)
    set(IS_ROCM_63_DISABLED 1)
    set(IS_ROCM_63_DISABLED 1)
    set(IS_ROCM_631_DISABLED 1)
    set(IS_ROCM_632_DISABLED 1)
    set(IS_ROCM_633_DISABLED 1)
    set(IS_ROCM_64_DISABLED 1)
    set(IS_ROCM_641_DISABLED 1)
    set(IS_ROCM_642_DISABLED 1)
    set(IS_ROCM_643_DISABLED 1)
    set(IS_ROCM_70_DISABLED 1)
    set(IS_ROCM_701_DISABLED 1)
    set(IS_LATEST_RELEASE_ROCM_INSTALL_DISABLED 1)
    set(IS_LATEST_RELEASE_ROCM_INSTALL_DRYRUN_DISABLED 1)
elseif (IS_OL_810 OR IS_RHEL_95)
    message(STATUS "Disable all ROCm tests older than 6.3 for Oracle Linux 8.10 and RHEL 9.5")
    set(IS_ROCM_61_DISABLED 1)
    set(IS_ROCM_611_DISABLED 1)
    set(IS_ROCM_612_DISABLED 1)
    set(IS_ROCM_613_DISABLED 1)
    set(IS_ROCM_62_DISABLED 1)
    set(IS_ROCM_621_DISABLED 1)
    set(IS_ROCM_622_DISABLED 1)
    set(IS_ROCM_624_DISABLED 1)
elseif (IS_OL_95)
    message(STATUS "Disable all ROCm tests older than 6.4 for Oracle Linux 9.5")
    set(IS_ROCM_61_DISABLED 1)
    set(IS_ROCM_611_DISABLED 1)
    set(IS_ROCM_612_DISABLED 1)
    set(IS_ROCM_613_DISABLED 1)
    set(IS_ROCM_62_DISABLED 1)
    set(IS_ROCM_621_DISABLED 1)
    set(IS_ROCM_622_DISABLED 1)
    set(IS_ROCM_624_DISABLED 1)
    set(IS_ROCM_63_DISABLED 1)
    set(IS_ROCM_631_DISABLED 1)
    set(IS_ROCM_632_DISABLED 1)
    set(IS_ROCM_633_DISABLED 1)
elseif (IS_DEBIAN_12)
    message(STATUS "Disable all ROCm tests older than 6.3.1 for Debian 12")
    set(IS_ROCM_61_DISABLED 1)
    set(IS_ROCM_611_DISABLED 1)
    set(IS_ROCM_612_DISABLED 1)
    set(IS_ROCM_613_DISABLED 1)
    set(IS_ROCM_62_DISABLED 1)
    set(IS_ROCM_621_DISABLED 1)
    set(IS_ROCM_622_DISABLED 1)
    set(IS_ROCM_624_DISABLED 1)
    set(IS_ROCM_63_DISABLED 1)
elseif (IS_SLES_155 OR IS_UBUNTU_2004)
    message(STATUS "Disable all ROCm tests newer than 6.4+ on SLES 15.5 and Ubuntu 20.04")
    set(IS_ROCM_64_DISABLED 1)
    set(IS_ROCM_641_DISABLED 1)
    set(IS_ROCM_642_DISABLED 1)
    set(IS_ROCM_643_DISABLED 1)
    set(IS_LATEST_RELEASE_ROCM_INSTALL_DISABLED 1)
    set(IS_LATEST_RELEASE_ROCM_INSTALL_DRYRUN_DISABLED 1)
elseif (IS_RHEL_96 OR IS_OL_96)
    message(STATUS "Disable all ROCm tests older than 6.4 for RHEL 9.6 and Oracle Linux 9.6")
    set(IS_ROCM_61_DISABLED 1)
    set(IS_ROCM_611_DISABLED 1)
    set(IS_ROCM_612_DISABLED 1)
    set(IS_ROCM_613_DISABLED 1)
    set(IS_ROCM_62_DISABLED 1)
    set(IS_ROCM_621_DISABLED 1)
    set(IS_ROCM_622_DISABLED 1)
    set(IS_ROCM_624_DISABLED 1)
    set(IS_ROCM_63_DISABLED 1)
    set(IS_ROCM_631_DISABLED 1)
    set(IS_ROCM_632_DISABLED 1)
    set(IS_ROCM_633_DISABLED 1)
    set(IS_ROCM_64_DISABLED 1)
elseif(IS_SLES_156)
    message(STATUS "Disable all ROCm tests older than 6.2 and newer than 7.0 for SLES 15.6")
    set(IS_ROCM_61_DISABLED 1)
    set(IS_ROCM_611_DISABLED 1)
    set(IS_ROCM_612_DISABLED 1)
    set(IS_ROCM_613_DISABLED 1)
    set(IS_ROCM_70_DISABLED 1)
    set(IS_ROCM_701_DISABLED 1)
elseif (IS_SLES_157)
    message(STATUS "Disable all ROCm tests older than 6.4.1 SLES 15.7")
    set(IS_ROCM_61_DISABLED 1)
    set(IS_ROCM_611_DISABLED 1)
    set(IS_ROCM_612_DISABLED 1)
    set(IS_ROCM_613_DISABLED 1)
    set(IS_ROCM_62_DISABLED 1)
    set(IS_ROCM_621_DISABLED 1)
    set(IS_ROCM_622_DISABLED 1)
    set(IS_ROCM_624_DISABLED 1)
    set(IS_ROCM_63_DISABLED 1)
    set(IS_ROCM_631_DISABLED 1)
    set(IS_ROCM_632_DISABLED 1)
    set(IS_ROCM_633_DISABLED 1)
    set(IS_ROCM_64_DISABLED 1)
    set(IS_ROCM_641_DISABLED 1)
elseif (IS_ROCKY_96)
    message(STATUS "Disable all ROCm tests older than 7.0 for Rocky 9.6")
    set(IS_ROCM_61_DISABLED 1)
    set(IS_ROCM_611_DISABLED 1)
    set(IS_ROCM_612_DISABLED 1)
    set(IS_ROCM_613_DISABLED 1)
    set(IS_ROCM_62_DISABLED 1)
    set(IS_ROCM_621_DISABLED 1)
    set(IS_ROCM_622_DISABLED 1)
    set(IS_ROCM_624_DISABLED 1)
    set(IS_ROCM_63_DISABLED 1)
    set(IS_ROCM_631_DISABLED 1)
    set(IS_ROCM_632_DISABLED 1)
    set(IS_ROCM_633_DISABLED 1)
    set(IS_ROCM_64_DISABLED 1)
    set(IS_ROCM_641_DISABLED 1)
    set(IS_ROCM_642_DISABLED 1)
    set(IS_ROCM_643_DISABLED 1)
    set(IS_LATEST_RELEASE_ROCM_INSTALL_DISABLED 1)
    set(IS_LATEST_RELEASE_ROCM_INSTALL_DRYRUN_DISABLED 1)
endif()

message(STATUS "SCRIPT_DIRECTORY = " ${SCRIPT_DIRECTORY})
message(STATUS "PACKAGE_NAME     = " ${PACKAGE_NAME})

# makeself [options] archive_dir file_name label [startup_script] [args]
message(STATUS "run command: makeself ${MAKESELF_OPTIONS} --nox11 ${SCRIPT_DIRECTORY} ${PACKAGE_NAME}.run \"ROCm Offline Install Creator\" ./offline_init.sh")

# Update the VERSION file for the PACKAGE name
file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/VERSION
"${VERSION_STRING}
${ROCM_VERSION_STRING}
${PACKAGE_NAME}
")

# Define the offline targets
add_custom_target(rocm_offline_creator ALL
                  COMMAND echo "Copying version file"
                  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/VERSION ${SCRIPT_DIRECTORY}/
                  COMMAND echo "Copying init script"
                  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/scripts/offline_init.sh ${SCRIPT_DIRECTORY}/
                  COMMAND echo "Copying Default config"
                  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/scripts/create-default.config ${SCRIPT_DIRECTORY}/
                  COMMAND echo "Copying header file"
                  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/scripts/rocm-makeself-header.sh ${SCRIPT_DIRECTORY}/
                  COMMAND echo "Copying install.sh header file"
                  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/scripts/rocm-makeself-header-install.sh ${SCRIPT_DIRECTORY}/
                  COMMAND echo "Copy the rocm_menus directory"
                  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/UI/rocm_menus ${SCRIPT_DIRECTORY}/rocm_menus/
                  COMMAND echo "Building rocm_offline_creator"
                  COMMAND makeself ${MAKESELF_OPTIONS} --nox11 ${SCRIPT_DIRECTORY} ${PACKAGE_NAME}.run "ROCm Offline Install Creator" ./offline_init.sh)

# UI
add_subdirectory(UI)

# Testing
add_subdirectory(tests)
