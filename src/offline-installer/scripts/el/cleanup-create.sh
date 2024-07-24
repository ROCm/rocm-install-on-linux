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

CREATE_CLEAN_YUM_REPOS_AMD=(repo-tar-offline.repo repo-offline.repo amdgpu.repo amdgpu-proprietary.repo amdgpu-build.repo amdgpu-local.repo rocm-build.repo rocm.repo)
CLEAN_REPO=0


###### Functions ###############################################################

print_msg() {
    local msg=$1
    echo -e "\e[93m$msg\e[0m"
}

restore_dnf_conf() {
    # restore the dnf.conf file from the backup file
    if [ -f /etc/yum.repos.d/epel.repo ]; then
        if [ -f /etc/dnf/dnf.conf.bak ]; then
            print_msg "==== Restoring .conf ===="
            $SUDO cp /etc/dnf/dnf.conf.bak /etc/dnf/dnf.conf
            $SUDO rm /etc/dnf/dnf.conf.bak
        fi
    fi
}

cleanup_create() {

    # restore the dnf.conf
    restore_dnf_conf
    
    # Remove any creator .repo files
    for index in ${CREATE_CLEAN_YUM_REPOS_AMD[@]}; do
        if [ -f /etc/yum.repos.d/$index ]; then
            print_msg "==== Removing $index ===="
            $SUDO rm /etc/yum.repos.d/$index
            CLEAN_REPO=1
        fi
    done
    
    if [ $CLEAN_REPO == 1 ]; then
        # cleanup dnf cache
        $SUDO dnf clean all
        $SUDO rm -r /var/cache/dnf/*
        
        print_msg "Offline Create cleaned up."
    fi
}


####### Main script ###############################################################

SUDO=$([[ $(id -u) -ne 0 ]] && echo "sudo" ||:)

cleanup_create


