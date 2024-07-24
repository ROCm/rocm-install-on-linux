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



###### Functions ###############################################################

usage() {
cat <<END_USAGE
Usage: $PROG [options]

[options}:
    help               = Displays this help information.
    version            = Displays the ROCm Offline Creater Tool version. 
    prompt             = Run the creator with user prompts.
    config=<file_path> = <file_path> Full path to a .config file with create settings in the format of create-default.config.
    
    ie. ./rocm-offline-creator_1.0.0-local.run
        ./rocm-offline-creator_1.0.0-local.run version
        ./rocm-offline-creator_1.0.0-local.run prompt
        ./rocm-offline-creator_1.0.0-local.run config=/home/user/create.config prompt
END_USAGE
}

print_version() {
    i=0
    
    while IFS= read -r line; do
        case $i in
            0) VERSION="$line" ;;
            1) ROCM_VERSION="$line" ;;
        esac
        
        i=$((i+1))
    done < "./VERSION"
    
    echo ROCm Offline Creator Version : $VERSION-$ROCM_VERSION
}

####### Main script ###############################################################

PROG=${0##*/}

# parse args
while (($#))
do
    case "$1" in
    help)
        usage
        exit 0
        ;;
    version)
        print_version
        exit 0
        ;;
    config=*)
        echo Using configuration file.
        CONFIG_FILE_PATH="${1#*=}"
        shift
        ;;
    *)
        ARGS+="$1 "
        shift
        ;;
    esac
done

if [ -n "$CONFIG_FILE_PATH" ]; then
    echo Using create script.
    ./create-offline.sh config=$CONFIG_FILE_PATH $ARGS
else
    echo Using UI.
   ./rocm_offline_ui $ARGS
fi

