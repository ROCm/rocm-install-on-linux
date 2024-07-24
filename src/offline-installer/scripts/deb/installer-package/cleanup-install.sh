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

INSTALL_CLEAN_SOURCE_LIST_AMD=(amdgpu-build.list amdgpu-local.list amdgpu.list rocm-build.list rocm.list)
INSTALL_CLEAN_SOURCE_LIST=(repo-offline.list repo-offline-local.list)

INSTALL_REPO=/tmp/offline-repo
INSTALL_REPO_PIN=repo-offline-pin
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

cleanup_repos() {
    # Restore/enable sources.list if previously disabled
    enable_sources_list
    
    # Remove any AMD .list files
    for index in ${INSTALL_CLEAN_SOURCE_LIST_AMD[@]}; do
        if [ -f /etc/apt/sources.list.d/$index ]; then
            print_msg "==== Removing $index ===="
            $SUDO rm /etc/apt/sources.list.d/$index
            CLEAN_REPO=1
        fi
    done
    
    if [ -d $INSTALL_REPO ]; then
        print_msg "==== Removing $INSTALL_REPO ===="
        rm -r $INSTALL_REPO
    fi

    # Remove any installer .list files
    for index in ${INSTALL_CLEAN_SOURCE_LIST[@]}; do
        if [ -f /etc/apt/sources.list.d/$index ]; then
            print_msg "==== Removing $index ===="
            $SUDO rm /etc/apt/sources.list.d/$index
            CLEAN_REPO=1
        fi
    done
    
    # Remove any install pin files
    if [ -f /etc/apt/preferences.d/$INSTALL_REPO_PIN ]; then
        print_msg "==== Removing $INSTALL_REPO_PIN ===="
        $SUDO rm /etc/apt/preferences.d/$INSTALL_REPO_PIN
    fi
    
    if [ $CLEAN_REPO == 1 ]; then
        $SUDO apt-get update > /dev/null 2>&1
        
        print_msg "Offline Install cleaned up."
    fi
}


####### Main script ###############################################################

SUDO=$([[ $(id -u) -ne 0 ]] && echo "sudo" ||:)

cleanup_repos

