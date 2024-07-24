#!/bin/bash

# #############################################################################
# Copyright (C) 2024 Advanced Micro Devices, Inc. All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# #############################################################################

CREATE_CLEAN_SOURCE_LIST_AMD=(repo-offline.list amdgpu-build.list amdgpu-local.list amdgpu.list amdgpu-proprietary.list rocm-build.list rocm.list)
VALIDATE_REPO=/tmp/offline-repo
CLEAN_REPO=0


###### Functions ###############################################################

print_msg() {
    local msg=$1
    echo -e "\e[93m$msg\e[0m"
}

enable_sources_list() {
    if [ -f /etc/apt/sources-bak.list ]; then
        print_msg "^^^^ Enabling sources.list..."
        $SUDO mv /etc/apt/sources-bak.list /etc/apt/sources.list
        print_msg "^^^^ Enabling sources.list...Complete"
    fi
    
    if [ -f /etc/apt/sources.list.d/ubuntu.sources.bak ]; then
        print_msg "^^^^ Enabling ubuntu.sources..."
        $SUDO mv /etc/apt/sources.list.d/ubuntu.sources.bak /etc/apt/sources.list.d/ubuntu.sources
        print_msg "^^^^ Enabling ubuntu.sources...Complete"
    fi
}

cleanup_create() {
    # Restore/enable sources.list if previously disabled
    enable_sources_list

    # Remove any creator .list files
    for index in ${CREATE_CLEAN_SOURCE_LIST_AMD[@]}; do
        if [ -f /etc/apt/sources.list.d/$index ]; then
            print_msg "==== Removing $index ===="
            $SUDO rm /etc/apt/sources.list.d/$index
            CLEAN_REPO=1
        fi
    done
   
    # Remove any creator pin files
    if [ -f /etc/apt/preferences.d/rocm-local-pin-999 ]; then
        print_msg "==== Removing rocm-local-pin-999 ===="
        $SUDO rm /etc/apt/preferences.d/rocm-local-pin-999
    fi
    
    if [ -f /etc/apt/trusted.gpg.d/amdgpu-local.gpg ]; then
        print_msg "==== Removing amdgpu-local.gpg ===="
        $SUDO rm /etc/apt/trusted.gpg.d/amdgpu-local.gpg
    fi
    
    # Remove any offline validation repo if it exists
    if [ -d $VALIDATE_REPO ]; then
        print_msg "Deleting offline repo"
        $SUDO rm -r $VALIDATE_REPO
    fi
    
    if [ $CLEAN_REPO == 1 ]; then
        $SUDO apt-get update > /dev/null 2>&1
        $SUDO apt-get clean
        
        print_msg "Offline Create cleaned up."
    fi
}


####### Main script ###############################################################

SUDO=$([[ $(id -u) -ne 0 ]] && echo "sudo" ||:)

cleanup_create

