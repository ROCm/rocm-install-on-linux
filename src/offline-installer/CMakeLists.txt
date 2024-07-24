# ##############################################################################
# Copyright (c) 2024 Advanced Micro Devices, Inc.
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
        set(MAKESELF_OPTIONS --cleanup ./cleanup-create.sh)
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

# Check for the Distro
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    execute_process (
        COMMAND bash -c "awk -F= '/^ID=/{print $2}' /etc/os-release |tr -d '\n' | tr -d '\"'"
        OUTPUT_VARIABLE distro
    )

    # Ubuntu 24.04
    execute_process (
        COMMAND bash -c "grep '24.04' /etc/os-release"
        OUTPUT_VARIABLE IS_UBUNTU_2404
    )
    
    # Suse 15.5
    execute_process (
        COMMAND bash -c "grep '15.6' /etc/os-release"
        OUTPUT_VARIABLE IS_SLES_156
    )
    # Rhel 9.4
    execute_process (
        COMMAND bash -c "grep '9.4' /etc/os-release"
        OUTPUT_VARIABLE IS_RHEL_94
    )
    # Rhel 9.3
    execute_process (
        COMMAND bash -c "grep '9.3' /etc/os-release"
        OUTPUT_VARIABLE IS_RHEL_93
    )
    # Rhel 8.10
    execute_process (
        COMMAND bash -c "grep '8.10' /etc/os-release"
        OUTPUT_VARIABLE IS_RHEL_810
    )
    # Rhel 8.9
    execute_process (
        COMMAND bash -c "grep '8.9' /etc/os-release"
        OUTPUT_VARIABLE IS_RHEL_89
    )
    
    message(STATUS "Linux distro: ${distro}")
    message(STATUS "IS_SLES_156: ${IS_SLES_156}")

    message(STATUS "IS_RHEL_94: ${IS_RHEL_94}")
    message(STATUS "IS_RHEL_93: ${IS_RHEL_93}")
    message(STATUS "IS_RHEL_810: ${IS_RHEL_810}")
    message(STATUS "IS_RHEL_89: ${IS_RHEL_89}")

    message(STATUS "IS_UBUNTU_2404: ${IS_UBUNTU_2404}")
else()
    message(FATAL_ERROR "No OS detected!")
endif()

# Set the script directory for the distro
if(${distro} STREQUAL "ubuntu")
    message(STATUS "Building for Ubuntu")
    set(SCRIPT_DIRECTORY ${CMAKE_SOURCE_DIR}/scripts/deb)
elseif(${distro} STREQUAL "rocky" OR ${distro} STREQUAL "rhel")
    message(STATUS "Building for RHEL")
    set(SCRIPT_DIRECTORY ${CMAKE_SOURCE_DIR}/scripts/el)
elseif(${distro} STREQUAL "opensuse-leap" OR ${distro} STREQUAL "sles")
    message(STATUS "Building for Suse")
    set(SCRIPT_DIRECTORY ${CMAKE_SOURCE_DIR}/scripts/sle)
else()
    message(FATAL_ERROR "Unsupported Distro : ${distro}")
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


# All tests enabled by default
set(IS_ROCM_573_DISABLED 0)
set(IS_ROCM_602_DISABLED 0)
set(IS_ROCM_61_DISABLED 0)
set(IS_ROCM_611_DISABLED 0)
set(IS_ROCM_612_DISABLED 0)
set(IS_ROCM_613_DISABLED 0)
set(IS_ROCM_62_DISABLED 0)

# Disable ROCm tests older than 6.2 for sles 15.6, rhel 8.10, rhel 9.4 and ubuntu 24.04
if (IS_SLES_156 OR IS_RHEL_810 OR IS_RHEL_94 OR IS_UBUNTU_2404)
    message(STATUS "Disable all ROCm tests older than 6.2")
    set(IS_ROCM_573_DISABLED 1)
    set(IS_ROCM_602_DISABLED 1)
    set(IS_ROCM_61_DISABLED 1)
    set(IS_ROCM_611_DISABLED 1)
    set(IS_ROCM_612_DISABLED 1)
    set(IS_ROCM_613_DISABLED 1)
# Disable ROCm tests older than 6.0 for rhel 9.3 and rhel 8.9
elseif (IS_RHEL_93 OR IS_RHEL_89)
    message(STATUS "Disable all ROCm tests older than 6.0")
    set(IS_ROCM_573_DISABLED 1)
endif()



message(STATUS "SCRIPT_DIRECTORY = " ${SCRIPT_DIRECTORY})
message(STATUS "PACKAGE_NAME     = " ${PACKAGE_NAME})

# makeself [options] archive_dir file_name label [startup_script] [args]
message(STATUS "run command: makeself ${SCRIPT_DIRECTORY} ${PACKAGE_NAME}.run \"ROCm Offline Install Creator\" ./offline_init.sh")

# Define the offline targets
add_custom_target(rocm_offline_creator ALL
                  COMMAND echo "Copying version file"
                  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/VERSION ${SCRIPT_DIRECTORY}/
                  COMMAND echo "Copying init script"
                  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/scripts/offline_init.sh ${SCRIPT_DIRECTORY}/
                  COMMAND echo "Copying Default config"
                  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/scripts/create-default.config ${SCRIPT_DIRECTORY}/
                  COMMAND echo "Copy the help_menus directory"
                  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/UI/help_menus ${SCRIPT_DIRECTORY}/help_menus/
                  COMMAND echo "Building rocm_offline_creator"
                  COMMAND makeself ${MAKESELF_OPTIONS} ${SCRIPT_DIRECTORY} ${PACKAGE_NAME}.run "ROCm Offline Install Creator" ./offline_init.sh)

# UI
add_subdirectory(UI)

# Testing
add_subdirectory(tests)