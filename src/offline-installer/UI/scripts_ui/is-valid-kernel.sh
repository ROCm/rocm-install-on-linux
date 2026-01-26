#!/bin/bash

# #############################################################################
# Copyright (c) 2025 Advanced Micro Devices, Inc. All rights reserved.
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

# Colour text
YELLOW="\033[0;93m"
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

SUDO=$([[ $(id -u) -ne 0 ]] && echo "sudo" ||:)

usage() {
cat <<END_USAGE
Returns status code 0 if kernel version user passes through via --kernel-version is available to download.
Otherwise, returns exit status code 1.
Usage: $PROG [options]

[options]:
    -k, --kernel-version  = Displays this help information.
    -d, --debug           = Runs script in debug mode.    
    
    ie. $PROG
        $PROG --kernel-version 6.1.0-29-amd64
END_USAGE
}

if [ $# -eq 0 ]; then
    usage
    exit 1
fi


debug_print() {
    if [[ $IS_DEBUG -eq 1 ]]; then
        printf "$1\n"
    fi
}

KERNEL_VER=
IS_DEBUG=0


# Command-Line Arguments
while [[ $# -gt 0 ]]; do
    ARG="$1"
    case $ARG in
    -k | --kernel-version)
        KERNEL_VER="$2"
        shift
        shift
        ;;
    -d | --debug)
        IS_DEBUG=1
        shift
        ;;
    *)
        usage
        exit 1
        ;;
    esac
done

os_release() {
    if [[ -r  /etc/os-release ]]; then
        . /etc/os-release

        DISTRO_NAME=$ID
        DISTRO_VER=$(awk -F= '/^VERSION_ID=/{print $2}' /etc/os-release | tr -d '"')
        case "$ID" in
        debian)
            ;;
        sles)
            ;;
        *)
            debug_print "${RED}$ID is Unsupported OS${NC}"
            exit 1
            ;;
        esac
    else
        debug_print "Unsupported OS"
        exit 1
    fi
}


is_debian_kernel_headers_available() {
    local linux_headers_info
    local linux_headers_binary_version
    local linux_headers_file_info
    local linux_headers_hash_value
    
    local kernel_ver_sans_arch=$(sed 's/-amd64//' <<< "$KERNEL_VER")
    local kernel_arch=$(awk -F '-' '{print $NF}' <<< "$KERNEL_VER")


    # Example URL: https://snapshot.debian.org/mr/binary/linux-headers-6.1.0-29-amd64/
    linux_headers_info=$(wget --tries $WGET_RETRY_COUNT --no-check-certificate -qO- https://snapshot.debian.org/mr/binary/linux-headers-$KERNEL_VER)
    if [ $? -eq 0 ]; then
        # linux_headers_binary_version=$(jq -r '.result[0].binary_version' <<< "$linux_headers_info")
        linux_headers_binary_version=$(echo "$linux_headers_info" | tr -s ',' '\n' | grep -w version | cut -d ':' -f2 | sed 's/[^0-9a-zA-Z.-]//g')
        
        # Example URL: https://snapshot.debian.org/mr/binary/linux-headers-6.1.0-29-amd64/6.1.123-1/binfiles
        linux_headers_file_info=$(wget --tries $WGET_RETRY_COUNT --no-check-certificate -qO- https://snapshot.debian.org/mr/binary/linux-headers-$KERNEL_VER/$linux_headers_binary_version/binfiles)
        if [ $? -eq 0 ]; then
            # linux_headers_hash_value=$(jq -r '.result[0].hash' <<< "$linux_headers_file_info")
            linux_headers_hash_value=$(echo "$linux_headers_file_info" | tr -s ',' '\n' | grep -w hash | cut -d ':' -f2 | sed 's/[^0-9a-zA-Z.-]//g')

            # Downloads file w/ hash value $linux_headers_hash_value as
            # filename linux-headers-${KERNEL_VER}_${linux_headers_binary_version}_$kernel_arch.deb

            # Example URL: https://snapshot.debian.org/file/8e6043412f66d6af992c64491270619f98922266/linux-headers-6.1.0-29-amd64_6.1.123-1_amd64.deb
            wget --spider --quiet --tries $WGET_RETRY_COUNT --no-check-certificate "https://snapshot.debian.org/file/$linux_headers_hash_value/linux-headers-${KERNEL_VER}_${linux_headers_binary_version}_$kernel_arch.deb"
            if [ $? -ne 0 ]; then
                debug_print "${YELLOW}Failed to download linux-headers-${KERNEL_VER} from https://snapshot.debian.org ${NC}"
                exit 1
            else
                debug_print "${GREEN}Successfully downloaded linux-headers-$KERNEL_VER from https://snapshot.debian.org https://snapshot.debian.org/file/$linux_headers_hash_value/linux-headers-${KERNEL_VER}_${linux_headers_binary_version}_$kernel_arch.deb ${NC}"
            fi
        else
            debug_print  "${YELLOW}Failed to download metadata on kernel package linux-headers-${KERNEL_VER} from https://snapshot.debian.org ${NC}"
            exit 1
        fi
    else
        debug_print  "${YELLOW}Failed to find kernel package linux-headers-${KERNEL_VER} on https://snapshot.debian.org ${NC}"
        exit 1
    fi
    
    # Download linux-headers-$kernel_ver_sans_arch-common file

    # Example URL: https://snapshot.debian.org/mr/binary/linux-headers-6.1.0-29-common/
    linux_headers_info=$(wget --tries $WGET_RETRY_COUNT --no-check-certificate -qO- https://snapshot.debian.org/mr/binary/linux-headers-$kernel_ver_sans_arch-common)
    if [ $? -eq 0 ]; then
        # linux_headers_binary_version=$(jq -r '.result[0].binary_version' <<< "$linux_headers_info")
        linux_headers_binary_version=$(echo "$linux_headers_info" | tr -s ',' '\n' | grep -w version | cut -d ':' -f2 |sed 's/[^0-9a-zA-Z.-]//g')
        
        # Example URL: https://snapshot.debian.org/file/ee32fc44cc642e3c131ac182f98ee11e6b102856/linux-headers-6.1.0-29-common_6.1.123-1_all.deb
        linux_headers_file_info=$(wget --tries $WGET_RETRY_COUNT --no-check-certificate -qO- https://snapshot.debian.org/mr/binary/linux-headers-$kernel_ver_sans_arch-common/$linux_headers_binary_version/binfiles)
        if [ $? -eq 0 ]; then
            # linux_headers_hash_value=$(jq -r '.result[0].hash' <<< "$linux_headers_file_info")
            linux_headers_hash_value=$(echo "$linux_headers_file_info" | tr -s ',' '\n' | grep -w hash | cut -d ':' -f2 | sed 's/[^0-9a-zA-Z.-]//g')

            # Example URL: https://snapshot.debian.org/file/ee32fc44cc642e3c131ac182f98ee11e6b102856/linux-headers-6.1.0-29-common_6.1.123-1_all.deb
            wget --spider --quiet --tries $WGET_RETRY_COUNT --no-check-certificate "https://snapshot.debian.org/file/$linux_headers_hash_value/linux-headers-${kernel_ver_sans_arch}-common_${linux_headers_binary_version}_all.deb"
            if [ $? -ne 0 ]; then
                debug_print  "${YELLOW}Failed to download linux-headers-${kernel_ver_sans_arch}-common from https://snapshot.debian.org ${NC}"
                exit 1
            else
                debug_print  "${GREEN}Successfully downloaded linux-headers-$kernel_ver_sans_arch-common from https://snapshot.debian.org/file/$linux_headers_hash_value/linux-headers-${kernel_ver_sans_arch}-common_${linux_headers_binary_version}_all.deb ${NC}"
            fi
        else
            debug_print  "${YELLOW}Failed to download metadata on kernel package linux-headers-${kernel_ver_sans_arch}-common from https://snapshot.debian.org ${NC}"
            exit 1
        fi
    else
        debug_print  "${YELLOW}Failed to find kernel package linux-headers-${kernel_ver_sans_arch}-common on https://snapshot.debian.org ${NC}"
        exit 1
    fi
}

# Determine the column index of package version dynamically. Usually 6 or 7.
get_sles_kernel_header_version_column() {
    local zypper_kernel_output="$1"
    local index=1
    for word in $zypper_kernel_output; do
        local expected_kernel_regex_with_minor_version="[0-9]\.[0-9]\.[0-9]-[0-9]+\.[0-9]+\.[0-9]+(\.[0-9]+)?"

        if [[ $word =~ $expected_kernel_regex_with_minor_version ]]; then
            break
        fi
        ((index++))
    done

    echo $index
}

is_sles_kernel_headers_available() {
    local kernels_list_file="sles-kernel-avail.txt"

    # Value of KERNEL_VER for SLES 15 must be one of the following formats.
    
    # 1) 6.4.0-150700.[MAJOR_VER].[MINOR_VER].[PATCH_VER] (eg 6.4.0-150700.53.11.1)
    # 2) 6.4.0-150700.[MAJOR_VER].[MINOR_VER] (eg 6.4.0-150700.51.1).
    # 3) 6.4.0-150700.[MAJOR_VER].[MINOR_VER]-default (eg 6.4.0-150700.53.11-default)
    # 4) 6.4.0-150700.[MAJOR_VER]-default (eg 6.4.0-150700.51-default).

    # 1) and 2) from above
    local expected_kernel_regex_with_minor_version="[0-9]\.[0-9]\.[0-9]-[0-9]+\.[0-9]+\.[0-9]+(\.[0-9]+)?"

    # 3) and 4) from above
    local expected_kernel_regex_with_default="[0-9]\.[0-9]\.[0-9]-[0-9]+\.[0-9]+(\.[0-9]+)?-default"

    local sles_kernel_ver="$KERNEL_VER"

    if [[ ! $sles_kernel_ver =~ $expected_kernel_regex_with_minor_version ]] && [[ ! $sles_kernel_ver =~ $expected_kernel_regex_with_default ]]; then
        debug_print "kernel does not match regex!"
        exit 1
    fi

    # substring '-default' must be removed from KERNEL_VER because zypper doesn't
    # have the '-default' substring when listing available kernel versions
    sles_kernel_ver=$(sed 's/-default//' <<< $KERNEL_VER)
    local sles_kernel_regex="^$sles_kernel_ver$"

    # SLES adds -default to current running kernel to replace its last digit.
    # Eg if kernel 6.4.0-150700.53.3.1 or 6.4.0-150700.51.1 are installed, then SLES prints
    # kernel versions as 6.4.0-150700.53.3-default or 6.4.0-150700.51-default respectively as the output
    # of the command 'uname -r'
    if grep -q -E "\-default$" <<< "$KERNEL_VER"; then
        sles_kernel_regex="^$sles_kernel_ver\.[0-9]+$"
    fi

    # File $kernels_list_file is created in /tmp/selfg[NUMBER] folder
    if [[ ! -f $kernels_list_file ]]; then
        $SUDO zypper --quiet refresh
        local zypper_kernel_output=$($SUDO zypper --quiet search -s kernel-default-devel 2>&1 | tee $kernels_list_file)
    else
        local zypper_kernel_output=$(cat $kernels_list_file)
    fi
    
    local index=$(get_sles_kernel_header_version_column "$(cat $kernels_list_file | grep -w kernel-default-devel | head -1)")

    output=$(echo "$zypper_kernel_output" | awk "{print \$${index}}" | grep -q -E $sles_kernel_regex)
    if [ $? -ne 0 ]; then
        debug_print "No kernel header with version $KERNEL_VER"
        exit 1
    else
        output=$(echo "$zypper_kernel_output" | awk "{print \$${index}}" | grep -E $sles_kernel_regex | sort | uniq)
        lines=$(wc -l <<< "$output")
        if [ $lines -gt 1 ]; then
            debug_print "Detected more than one kernel with regex '${sles_kernel_regex}'"
            exit 2
        fi
    fi
}

os_release

if [[ $DISTRO_NAME == "debian" ]]; then
    is_debian_kernel_headers_available
elif [[ $DISTRO_NAME == "sles" ]]; then 
    is_sles_kernel_headers_available
else
    debug_print "${RED} $DISTRO_NAME is unsupported${NC}"
    exit 1
fi