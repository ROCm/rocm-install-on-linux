#!/bin/bash


###### Functions ###############################################################

# Colour text
YELLOW="\033[0;93m"
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

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

os_release

is_debian_kernel_headers_available