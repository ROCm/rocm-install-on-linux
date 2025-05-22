#!/bin/bash

# #############################################################################
# Copyright (c) 2024-2025 Advanced Micro Devices, Inc. All rights reserved.
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

# Logs
CREATE_INSTALLER_LOGS=/var/log/offline_creator
CREATE_INSTALLER_CURRENT_LOG="$CREATE_INSTALLER_LOGS/create_$(date +%s).log"

SUDO=$([[ $(id -u) -ne 0 ]] && echo "sudo" ||:)
$SUDO mkdir -m 777 -p /var/log/offline_creator
{

# Creates a install .run using AMD repos as a source and adds dependent packages
WGET_RETRY_COUNT=5

# Debug Settings
DEBUG_CREATE=no
DEBUG_CONFIG=no

# System Information
DISTRO_NAME=
OS_TYPE=
DISTRO_VER=
DISTRO_CODENAME=
KERNEL_VER=


# Kernel packages to include
KERNEL_PACKAGES=

# Prereq packages to include
PREREQ_PACKAGES=

# ROCm Packages Config
ROCM_USECASES=

# Extra Packages Config
EXTRA_PACKAGES=

# Create Config
CREATE_INSTALLER_DIR=installer-package
CREATE_INSTALLER_PACKAGE_DIR=$CREATE_INSTALLER_DIR/packages
CREATE_CONFIG_FILE_UI=./create.config
CREATE_CONFIG_FILE_DEFAULT=./create-default.config
CREATE_CONFIG_AMDGPU_INSTALL=amdgpu-install
CREATE_CONFIG_AMDGPU_INSTALL_PARAMS="--dryrun --no-32"
CREATE_BUILD_TAG=
CREATE_BUILD_DATE=
CREATE_BUILD_PKG_COUNT=

# Installer Package Config/Build
INSTALL_PACKAGE_TYPE_PUBLIC=0
INSTALLER_CONFIG_FILE=$CREATE_INSTALLER_DIR/install.config

INSTALL_MAKESELF_OPTIONS=
INSTALL_MAKESELF_LOCAL=no

# Configuration Options
DOWNLOAD_PKG_FULL=0
DOWNLOAD_PKG_MIN=1

DOWNLOAD_PKG_CONFIG_NUM=$DOWNLOAD_PKG_FULL
DOWNLOAD_PKG_CONFIG=
DOWNLOAD_ONLY=no
VALIDATE_DOWNLOAD=yes
VALIDATE_REPO=/tmp/offline-repo

# Script args
PROMPT_USER=0
DEBUG_MODE=0

# Cleanup repos
CREATE_CLEAN_SOURCE_LIST_AMD=(repo-offline.list amdgpu-build.list amdgpu-local.list amdgpu.list amdgpu-proprietary.list rocm-build.list rocm.list)


###### Functions ###############################################################

usage() {
cat <<END_USAGE
Usage: $PROG [options]

[options]:
    help               = Displays this help information.
    version            = Displays the ROCm Offline Creater Tool version.
    prompt             = Run the creator with user prompts.
    config=<file_path> = <file_path> Full path to a .config file with create settings in the format of create-default.config.
    debug              = Runs script in debug mode to show what commands are being run.

    ie. $PROG
        $PROG version
        $PROG prompt
        $PROG config=/home/user/create.config prompt
END_USAGE
}

debugCreate() {
    if [[ $DEBUG_CREATE == "yes" ]]; then
        read -p "$1: (continue = y, exit = n) :" option
        if [[ $option == "n" || $option == "N" ]]; then
            echo Forcing Install Exit!
            exit 1
        fi
    fi
}

prompt_user() {
    if [[ $PROMPT_USER == 1 ]]; then
        read -p "$1" option
    else
        option=y
    fi
}

print_no_err() {
    local msg=$1
    echo -e "\e[32m++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\e[0m"
    echo -e "\e[32m No error: $msg\e[0m"
    echo -e "\e[32m++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\e[0m"
}

print_err() {
    local msg=$1
    echo -e "\e[31m++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\e[0m"
    echo -e "\e[31mError: $msg\e[0m"
    echo -e "\e[31m++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\e[0m"
}

check_error() {
    if [ $? -eq 0 ]; then
        print_no_err "$1"
    else
        print_err "$2"
        exit 1
    fi
}

pkg_installed() {
    local package_name=$1
    dpkg -s $package_name &> /dev/null
}

os_release() {
    if [[ -r  /etc/os-release ]]; then
        . /etc/os-release

    DISTRO_NAME=$ID
    DISTRO_VER=$(awk -F= '/^VERSION_ID=/{print $2}' /etc/os-release | tr -d '"')

    case "$ID" in
    ubuntu|linuxmint)
        OS_TYPE=deb
        DISTRO_CODENAME=$VERSION_CODENAME
        ;;
    debian)
        OS_TYPE=deb

        # Hardcode Debian 12 to use Ubuntu 22.04 jammy files
        if [[ $DISTRO_VER -eq 12 ]]; then
            DISTRO_CODENAME="jammy"
        else
            DISTRO_CODENAME=$VERSION_CODENAME
        fi
        ;;
    *)
        echo "$ID is Unsupported OS"
        exit 1
        ;;
    esac
    else
        echo "Unsupported OS"
        exit 1
    fi

    echo Distro:
    echo "   ${DISTRO_NAME} ${DISTRO_VER} : ${DISTRO_CODENAME} : type = $OS_TYPE"

    KERNEL_VER=$(uname -r)
    echo Kernel:
    echo "   ${KERNEL_VER}"
}

disable_sources_list() {
    # Ubuntu 22.04
    if [ -f /etc/apt/sources.list ]; then
        echo ^^^^ Disabling sources.list...
        $SUDO mv /etc/apt/sources.list /etc/apt/sources-bak.list
        echo ^^^^ Disabling sources.list...Complete
    fi

    # Ubuntu 24.04
    if [ -f /etc/apt/sources.list.d/ubuntu.sources ]; then
        echo ^^^^ Disabling ubuntu.sources...
        $SUDO mv /etc/apt/sources.list.d/ubuntu.sources /etc/apt/sources.list.d/ubuntu.sources.bak
        echo ^^^^ Disabling ubuntu.sources...Complete
    fi

    # Debian 12
    if [ -f /etc/apt/sources.list.d/debian.sources ]; then
        echo ^^^^ Disabling debian.sources...
        $SUDO mv /etc/apt/sources.list.d/debian.sources /etc/apt/sources.list.d/debian.sources.bak
        echo ^^^^ Disabling debian.sources...Complete
    fi
}

enable_sources_list() {
    # Ubuntu 22.04
    if [ -f /etc/apt/sources-bak.list ]; then
        echo ^^^^ Enabling sources.list...
        $SUDO mv /etc/apt/sources-bak.list /etc/apt/sources.list
        echo ^^^^ Enabling sources.list...Complete
    fi

    # Ubuntu 24.04
    if [ -f /etc/apt/sources.list.d/ubuntu.sources.bak ]; then
        echo ^^^^ Enabling ubuntu.sources...
        $SUDO mv /etc/apt/sources.list.d/ubuntu.sources.bak /etc/apt/sources.list.d/ubuntu.sources
        echo ^^^^ Enabling ubuntu.sources...Complete
    fi

    # Debian 12
    if [ -f /etc/apt/sources.list.d/debian.sources.bak ]; then
        echo ^^^^ Enabling debian.sources...
        $SUDO mv /etc/apt/sources.list.d/debian.sources.bak /etc/apt/sources.list.d/debian.sources
        echo ^^^^ Enabling debian.sources...Complete
    fi
}


setup_installer_public_repos() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Install Package Type = public : Install amdgpu-install...

    if [[ -z $AMDGPU_INSTALL_URL ]]; then
        echo using default URL for amdgpu-install

        local VER_MAJ=${ROCM_VERSIONS:0:1}
        local VER_MIN=${ROCM_VERSIONS:2:1}
        local VER_MIN_MIN=${ROCM_VERSIONS:4:1}

        if [[ -z $VER_MIN_MIN ]]; then
            VER_MIN_MIN=0
        fi

        AMDGPU_INSTALL_NAME=amdgpu-install_$VER_MAJ.$VER_MIN.$VER_MAJ"0"$VER_MIN"0"$VER_MIN_MIN-1_all.deb
        AMDGPU_INSTALL_URL=https://repo.radeon.com/amdgpu-install/$ROCM_VERSIONS/ubuntu/$DISTRO_CODENAME/$AMDGPU_INSTALL_NAME
    else
        AMDGPU_INSTALL_NAME=$(basename $AMDGPU_INSTALL_URL)
    fi

    echo install: $AMDGPU_INSTALL_NAME

    # Download the amdgpu-install package and associated dependencies
    wget --tries $WGET_RETRY_COUNT $AMDGPU_INSTALL_URL

    check_error "Successfully downloaded amdgpu-install." "Failed amdgpu-install download."

    $SUDO chmod 644 ./$AMDGPU_INSTALL_NAME

    $SUDO apt-get -y --download-only -o Dir::Cache="./$CREATE_INSTALLER_PACKAGE_DIR" -o Dir::Cache::archives="./$CREATE_INSTALLER_PACKAGE_DIR" \
    install ./$AMDGPU_INSTALL_NAME

    # Install amdgpu-install for host installer creation
    $SUDO apt-get install -y ./$AMDGPU_INSTALL_NAME

    # Update the amdgpu.list (if required)
    if [[ -n $AMDGPU_URL ]]; then
        echo Updating amdgpu url...

        # Find the URL in the file and replace it
        $SUDO sed -i "s#https[^ ]*#$AMDGPU_URL#g" "/etc/apt/sources.list.d/amdgpu.list"
    fi

    # Update the rocm.list (if required)
    if [[ -n $ROCM_URL ]]; then
        echo Updating rocm url...

        # Find the URL in the file and replace it
        $SUDO sed -i "s#https[^ ]*#$ROCM_URL#g" "/etc/apt/sources.list.d/rocm.list"
    fi

    echo Install amdgpu-install...Complete

    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Copying amdgpu-install

    # Copy the amdgpu-install script from /usr/bin to the installer
    $SUDO cp /usr/bin/amdgpu-install $CREATE_INSTALLER_DIR
    $SUDO chmod 755 $CREATE_INSTALLER_DIR/amdgpu-install
}

create_installer_package_dir() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Creating directory for installer...

    debugCreate create_installer_package_dir

    # Create the installer packages directory for package download
    mkdir -p -m755 ./$CREATE_INSTALLER_PACKAGE_DIR

    echo Creating directory for installer: $CREATE_INSTALLER_PACKAGE_DIR ...Complete
}

setup_installer_repos() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Setup Package Source Repos...

    debugCreate setup_installer_repos

    if [[ $INSTALL_PACKAGE_TYPE == $INSTALL_PACKAGE_TYPE_PUBLIC ]]; then
        setup_installer_public_repos
    else
        echo Unsupport installer package type.  Exiting.
        exit 1;
    fi
}

cleanup_create() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Cleaning up installation...

    debugCreate cleanup_create

    # check that amdgpu-install isn't installed already
    pkg_installed "amdgpu-install"
    if [ $? -eq 0 ]; then
        echo amdgpu-install package is already installed. Cleaning up for new install

        $SUDO apt-get purge -y amdgpu-install

        $SUDO apt-get autoremove -y
        $SUDO apt-get update > /dev/null 2>&1
    else
        if [ -f /usr/bin/amdgpu-install ]; then
            echo amdgpu-install bin is already installed. Cleaning up for new install
            $SUDO rm /usr/bin/amdgpu-install
        else
            echo amdgpu-install not installed
        fi
    fi

    # check and remove the amdgpu-uninstall link
    if [ -f /usr/bin/amdgpu-uninstall ]; then
        $SUDO rm /usr/bin/amdgpu-uninstall
    fi

    # Remove any creator .list files
    for index in ${CREATE_CLEAN_SOURCE_LIST_AMD[@]}; do
        if [ -f /etc/apt/sources.list.d/$index ]; then
            echo =-=-=-= Removing $index =-=-=-=
            $SUDO rm /etc/apt/sources.list.d/$index
        fi
    done

    # Remove any creator pin files
    if [ -f /etc/apt/preferences.d/rocm-local-pin-999 ]; then
        echo =-=-=-= Removing rocm-local-pin-999 =-=-=-=
        $SUDO rm /etc/apt/preferences.d/rocm-local-pin-999
    fi

    if [ -f /etc/apt/trusted.gpg.d/amdgpu-local.gpg ]; then
        echo =-=-=-= Removing amdgpu-local.gpg =-=-=-=
        $SUDO rm /etc/apt/trusted.gpg.d/amdgpu-local.gpg
    fi

    # Remove any offline validation repo if it exists
    if [ -d $VALIDATE_REPO ]; then
        echo Deleting offline repo
        $SUDO rm -r $VALIDATE_REPO
    fi

    # Restore/enable sources.list if previously disabled
    enable_sources_list

    $SUDO apt-get update > /dev/null 2>&1
    $SUDO apt-get clean

    echo Cleaning up installation...Complete
}

cleanup_pkg_cache() {
    echo ++++++++++++++++++++++++++++++++
    echo Cleaning up package cache...
    
    if [ -f "./$CREATE_INSTALLER_PACKAGE_DIR/pkgcache.bin" ]; then
        $SUDO rm "./$CREATE_INSTALLER_PACKAGE_DIR/pkgcache.bin"
    fi
            
    if [ -f "./$CREATE_INSTALLER_PACKAGE_DIR/lock" ]; then
        $SUDO rm "./$CREATE_INSTALLER_PACKAGE_DIR/lock"
    fi
            
    if [ -f "./$CREATE_INSTALLER_PACKAGE_DIR/srcpkgcache.bin" ]; then
        $SUDO rm "./$CREATE_INSTALLER_PACKAGE_DIR/srcpkgcache.bin"
    fi
            
    if [ -d "./$CREATE_INSTALLER_PACKAGE_DIR/partial" ]; then
        $SUDO rm -R "./$CREATE_INSTALLER_PACKAGE_DIR/partial"
    fi
    
    echo Cleaning up package cache...Complete.
}

install_tools() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

    # Install dpkg-dev for Package file creation
    $SUDO apt-get install -y dpkg-dev

    # Install makself for .run creation
    $SUDO apt-get install -y makeself

    # Check the version of makself and enable cleanup script support if >= 2.4.2
    makeself_version_min=2.4.2
    makeself_version=$(makeself --version)
    makeself_version=${makeself_version#Makeself version }

    if [[ "$(printf '%s\n' "$makeself_version_min" "$makeself_version" | sort -V | head -n1)" = "$makeself_version_min" ]]; then
        INSTALL_MAKESELF_OPTIONS+="--cleanup ./cleanup-install.sh --header ./rocm-makeself-header-install.sh --help-header ./VERSION"
        echo Enabling cleanup script support.
    fi
}

get_installer_package_list() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Creating packages list...

    debugCreate get_installer_package_list

    amdgpu_install_out=$($CREATE_CONFIG_AMDGPU_INSTALL $CREATE_CONFIG_AMDGPU_INSTALL_PARAMS --usecase=$ROCM_USECASES)

    # From amdgpu_install_out, extract the apt-get install line
    declare apt_get_install_line_regex='(apt-get|apt) install.*$'
    declare apt_get_install_line="$(echo "${amdgpu_install_out}" | grep --extended-regexp "${apt_get_install_line_regex}")"

    # Example values for apt_get_install_line
    # Example 1: sudo apt-get install amdgpu-dkms linux-headers-6.5.0-28-generic
    # Example 2: apt-get install amdgpu-dkms linux-headers-6.5.0-28-generic"
    echo "${apt_get_install_line}" | grep --extended-regexp "apt-get" > /dev/null 2> /dev/null
    # Remove sudo apt-get install from the start, getting only the arguments (packages)
    PACKAGES="$(echo "${apt_get_install_line}" | sed 's/.*apt-get install //')"
    PACKAGES="${PACKAGES/linux-headers*/} "

    # set the kernel packages
    apt-cache show linux-headers-$KERNEL_VER > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        echo "Kernel Packages for $KERNEL_VER are available in the repositories."
        KERNEL_PACKAGES="linux-headers-$KERNEL_VER "
    else
        echo "Kernel Packages not available in the repositories."
        KERNEL_PACKAGES=" "
    fi

    if [ $DISTRO_NAME == "debian" ]; then
        echo "Debian system detected. Marking kernel packages for prereq installation."
        # Add kernel package list to PREREQ_PACKAGES so that it doesn't get added to ROCM_USECASES_PACKAGES
        # PREREQ_PACKAGES should be installed before ROCM_USECASES_PACKAGES
        PREREQ_PACKAGES+=${KERNEL_PACKAGES}
    else
        echo "Adding kernel packages to main package list."
        PACKAGES+=${KERNEL_PACKAGES}
    fi

    # set the ROCm usecase
    ROCM_USECASES_PACKAGES=$PACKAGES

    # remove amdgpu if not installing the driver
    if [ $AMDGPU_INSTALL_DRIVER == "no" ]; then
        echo Removing amdgpu
        PACKAGES="${PACKAGES//amdgpu-dkms/}"
        echo "PACKAGES = $PACKAGES"
    fi

    PREREQ_PACKAGES+="python3-setuptools python3-wheel "
    if [ "$ROCM_VERSIONS" = "6.3.1" ]; then
        if [ $DISTRO_VER = "20.04" ]; then
            PREREQ_PACKAGES+="libpython3.8 "
        elif [ $DISTRO_VER = "22.04" ]; then
            PREREQ_PACKAGES+="libpython3.10 "
        elif [ $DISTRO_VER = "24.04" ]; then
            PREREQ_PACKAGES+="libpython3.12 "
        fi
    fi
    # Add required prereq packages for ROCm
    PACKAGES+=${PREREQ_PACKAGES}

    # Add any extra packages
    PACKAGES+=${EXTRA_PACKAGES}

    # If only extra packages are require - only download those
    if [ $EXTRA_PACKAGES_ONLY == "yes" ]; then
        echo Only Downloading Extra Packages for Installer.
        PACKAGES=$EXTRA_PACKAGES
    fi

    echo ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    echo "KERNEL_PACKAGES = $KERNEL_PACKAGES"
    echo "PACKAGES        = $PACKAGES"
    echo ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    if [[ -z "$PACKAGES" ]]; then
        echo "ERROR: No packages found"
        exit 1
    fi

    echo Creating packages list...Complete
}

download_validate_resolve() {
    echo ++++++++++++++++++++++++++++++++
    echo Validating Downloaded packages for install...

    # Remove any creator .list files
    for index in ${CREATE_CLEAN_SOURCE_LIST_AMD[@]}; do
        if [ -f /etc/apt/sources.list.d/$index ]; then
            echo =-=-=-= Removing $index =-=-=-=
            $SUDO rm /etc/apt/sources.list.d/$index
        fi
    done

    # create the repo
    echo "deb [trusted=yes] file:$VALIDATE_REPO ./" | $SUDO tee -a /etc/apt/sources.list.d/repo-offline.list

    mkdir -m775 $VALIDATE_REPO
    $SUDO cp -Rp $(pwd)/$CREATE_INSTALLER_PACKAGE_DIR/* $VALIDATE_REPO
    $SUDO rm -R $VALIDATE_REPO/partial

    pushd $VALIDATE_REPO
        dpkg-scanpackages . /dev/null | gzip -9c > Packages.gz
        chmod 664 Packages.gz
    popd

    disable_sources_list

    $SUDO apt-get update > /dev/null 2>&1
    $SUDO apt-get clean

    # simulate/dryrun the install
    $SUDO apt-get install --dry-run $PACKAGES
    if [ $? -eq 0 ]; then
        print_no_err "Valid package dependencies."
    else
        print_err "Repo validation failed."
        enable_sources_list
        exit 1
    fi

    # cleanup the temp repo
    $SUDO rm -r $VALIDATE_REPO
    $SUDO rm /etc/apt/sources.list.d/repo-offline.list

    enable_sources_list

    $SUDO apt-get update > /dev/null 2>&1

    echo Validating Downloaded packages for install...Complete
}

download_installer_packages() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Downloading...
    echo PACKAGES= ${PACKAGES}
    echo ++++++++++++++++++++++++++

    debugCreate download_installer_packages

    # Download packages for selected usecases
    pushd ./$CREATE_INSTALLER_PACKAGE_DIR

        $SUDO dpkg --remove-architecture i386

        $SUDO apt-get clean
        $SUDO apt-get update > /dev/null

        echo =-=-=-= download packages =-=-=-=
        prompt_user "Start Download (y/n): "
        if [[ $option == "Y" || $option == "y" ]]; then

            # check the download mode
            if [ $DOWNLOAD_PKG_CONFIG_NUM == $DOWNLOAD_PKG_FULL ]; then
                # full download - normal full dep mode
                $SUDO apt-get -y --download-only -o Dir::Cache="./" -o Dir::Cache::archives="./" install ${PACKAGES}
                $SUDO apt-get -y download $(apt-cache depends ${DOWNLOAD_PKG_CONFIG} ${PACKAGES} | grep "^\w")
            else
                # simple download - minimum dep mode
                $SUDO apt-get -y --download-only -o Dir::Cache="./" -o Dir::Cache::archives="./" install ${PACKAGES}
            fi

            # check for any errors during download
            check_error "Package download successful." "Package download failed."
        else
            echo Cancelling Download.  Exiting.
            exit 1
        fi

    popd

    echo Downloading...Complete

    # Check if downloading only
    if [[ $DOWNLOAD_ONLY == "yes" ]]; then
        echo ++++++++++++++++++++++++++++++++
        echo Download packages only. Exiting.
        mkdir -p -m755 $VALIDATE_REPO
        cp -r ./$CREATE_INSTALLER_PACKAGE_DIR/* $VALIDATE_REPO/
        echo ++++++++++++++++++++++++++++++++
        exit 1
    fi
}

create_install_repo() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Creating Installer Repo Setup...

    debugCreate create_install_repo

    # Clean up
    cleanup_pkg_cache

    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Creating Packages list...

    CREATE_BUILD_PKG_COUNT=$(ls ./$CREATE_INSTALLER_PACKAGE_DIR | wc -l)

    # Create the Packages index for the offline repo
    pushd ./$CREATE_INSTALLER_PACKAGE_DIR
        dpkg-scanpackages . /dev/null | gzip -9c > Packages.gz
        chmod 664 Packages.gz
    popd

    echo Creating Packages list...Complete : Total $CREATE_BUILD_PKG_COUNT packages
    echo Creating Installer Repo Setup...Complete
}

parse_package_config() {
    echo ^^^^ Parsing dependency config = $DOWNLOAD_PKG_CONFIG_NUM.

    local download_config=

    if [ $DOWNLOAD_PKG_CONFIG_NUM == $DOWNLOAD_PKG_FULL ]; then
        download_config=-full
        DOWNLOAD_PKG_CONFIG="--recurse --no-recommends --no-suggests --no-conflicts --no-breaks --no-replaces --no-enhances --no-pre-depends"
    else
        download_config=-minimum
        DOWNLOAD_PKG_CONFIG=
    fi

    CREATE_BUILD_TAG+=$download_config
}

parse_rocm_config() {
    echo ^^^^ Parsing ROCm usecase config.

    if [ $INSTALL_PACKAGE_TYPE == $INSTALL_PACKAGE_TYPE_PUBLIC ]; then
        if [ -z $ROCM_VERSIONS ]; then
            echo ERROR: No ROCm Version number set.  Exiting.
            exit 1
        fi
        CREATE_BUILD_TAG+="_rocm-$ROCM_VERSIONS"
    else
        echo "No ROCm info."
    fi
}

parse_driver_config() {
    echo ^^^^ Parsing Driver/amdgpu config.

    if [ $INSTALL_PACKAGE_TYPE == $INSTALL_PACKAGE_TYPE_PUBLIC ]; then
        if [ -z $ROCM_VERSIONS ]; then
            echo ERROR: No ROCm Version number set.  Exiting.
            exit 1
        fi
        CREATE_BUILD_TAG+="_amdgpu-$ROCM_VERSIONS"
    else
        echo "No Driver info."
    fi
}

parse_extras_config() {
    echo ^^^^ Parsing Extra packages config.
}

parse_build_config() {
    echo ^^^^ Parsing Build config.

    CREATE_BUILD_DATE=$(date)

    if [ $INSTALL_MAKESELF_LOCAL == "yes" ]; then
        INSTALL_MAKESELF_OPTIONS=--current
    fi
}

parse_version() {
    i=0

    while IFS= read -r line; do
        case $i in
            0) CREATE_VERSION="$line" ;;
            1) CREATE_ROCM_VERSION="$line" ;;
            2) CREATE_PACKAGE="$line" ;;
        esac

        i=$((i+1))
    done < "./VERSION"

    echo Creator Version : $CREATE_VERSION-$CREATE_ROCM_VERSION
    echo Creator Package : $CREATE_PACKAGE
}

config_create() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Create Configure...

    local CREATE_CONFIG_FILE=

    # Check for user-modified config file (input .config to create script)
    if [[ ${CONFIG_FILE_PATH##*.} == "config" ]] && [[ -f $CONFIG_FILE_PATH ]]; then
         CREATE_CONFIG_FILE=$CONFIG_FILE_PATH
    elif [ -f $CREATE_CONFIG_FILE_UI ]; then
        CREATE_CONFIG_FILE=$CREATE_CONFIG_FILE_UI
    else
        print_err "Create configuration file not found."
        exit 1
    fi

    echo "Using Create Configuration file: $CREATE_CONFIG_FILE"
    source $CREATE_CONFIG_FILE

    # Check for a URL config file
    if [[ -n $URL_CONFIG ]]; then
        if [[ -f $URL_CONFIG ]]; then
            echo "Using URL Configuration file   : $URL_CONFIG"
            source $URL_CONFIG

            echo Checking URL for $ROCM_VERSIONS
            if [[ "$AMDGPU_INSTALL_URL" != *"$ROCM_VERSIONS"* ]]; then
                echo ROCm version in URL file does not match.
                exit 1
            fi

            if [[ "$ROCM_URL" != *"$ROCM_VERSIONS"* ]]; then
                echo ROCm version in URL file does not match.
                exit 1
            fi

            if [[ "$AMDGPU_URL" != *"$ROCM_VERSIONS"* ]]; then
                echo ROCm version in URL file does not match.
                exit 1
            fi

            echo "AMDGPU_INSTALL_URL = $AMDGPU_INSTALL_URL"
            echo "ROCM_URL           = $ROCM_URL"
            echo "AMDGPU_URL         = $AMDGPU_URL"
        else
            echo -e "\e[93mWaring: URL configuration file not found.  Using defaults.\e[0m"
        fi
    fi

    # Check for the installer package generation type
    if [ $INSTALL_PACKAGE_TYPE == $INSTALL_PACKAGE_TYPE_PUBLIC ]; then
        CREATE_BUILD_TAG=repo-public
    else
        echo "No supported installer package type. Exiting."
       exit 1
    fi

    # Parse any additional changes to each config type
    parse_package_config

    parse_rocm_config
    parse_driver_config
    parse_extras_config

    parse_build_config

    parse_version

    echo Create Configure...Complete
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


write_install_config() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Writing install config: $INSTALLER_CONFIG_FILE

    if [ -f $INSTALLER_CONFIG_FILE ]; then
        echo Warning Config file exists!
    else
        # Write out all config parameters for used by the installer
        echo CREATE_PACKAGE=\"$CREATE_PACKAGE\" >> $INSTALLER_CONFIG_FILE
        echo CREATE_VERSION=\"$CREATE_VERSION-$CREATE_ROCM_VERSION\" >> $INSTALLER_CONFIG_FILE
        echo CREATE_BUILD_TAG=\"$CREATE_BUILD_TAG\" >> $INSTALLER_CONFIG_FILE
        echo CREATE_DISTRO_NAME=\"$DISTRO_NAME\" >> $INSTALLER_CONFIG_FILE
        echo CREATE_DISTRO_VER=\"$DISTRO_VER\" >> $INSTALLER_CONFIG_FILE
        echo CREATE_DISTRO_KERNEL_VER=\"$KERNEL_VER\" >> $INSTALLER_CONFIG_FILE
        echo CREATE_BUILD_DATE=\"$CREATE_BUILD_DATE\" >> $INSTALLER_CONFIG_FILE
        echo INSTALL_MAKESELF_LOCAL=$INSTALL_MAKESELF_LOCAL >> $INSTALLER_CONFIG_FILE

        echo PREREQ_PACKAGES=\"$PREREQ_PACKAGES\" >> $INSTALLER_CONFIG_FILE

        echo ROCM_VERSIONS=$ROCM_VERSIONS >> $INSTALLER_CONFIG_FILE
        echo ROCM_USECASES=$ROCM_USECASES >> $INSTALLER_CONFIG_FILE
        echo ROCM_USECASES_PACKAGES=\"$ROCM_USECASES_PACKAGES\" >> $INSTALLER_CONFIG_FILE
        echo ROCM_BUILD=$ROCM_BUILD >> $INSTALLER_CONFIG_FILE

        echo EXTRA_PACKAGES=\"$EXTRA_PACKAGES\" >> $INSTALLER_CONFIG_FILE

        echo AMDGPU_INSTALL_DRIVER=$AMDGPU_INSTALL_DRIVER >> $INSTALLER_CONFIG_FILE
        echo AMDGPU_BUILD=$AMDGPU_BUILD >> $INSTALLER_CONFIG_FILE
        echo AMDGPU_POST_INSTALL_BLACKLIST=$AMDGPU_POST_INSTALL_BLACKLIST >> $INSTALLER_CONFIG_FILE
        echo AMDGPU_POST_INSTALL_START=$AMDGPU_POST_INSTALL_START >> $INSTALLER_CONFIG_FILE
        
        echo AMDGPU_POST_GPU_ACCESS_CURRENT_USER=$AMDGPU_POST_GPU_ACCESS_CURRENT_USER >> $INSTALLER_CONFIG_FILE
        echo AMDGPU_POST_GPU_ACCESS_ALL_USERS=$AMDGPU_POST_GPU_ACCESS_ALL_USERS >> $INSTALLER_CONFIG_FILE
    fi
}

build_installer() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Building Offline Installer .run...
    echo Using options: $INSTALL_MAKESELF_OPTIONS

    debugCreate build_installer

    # Write out the installer config file
    write_install_config

    # Create the .run for the installer
    makeself $INSTALL_MAKESELF_OPTIONS --nox11 ./$CREATE_INSTALLER_DIR "./$INSTALL_PACKAGE_NAME" "ROCm Offline Install" ./install.sh
    cp -Rp "$INSTALL_PACKAGE_NAME" $INSTALL_PACKAGE_DIR

    echo Building Offline Installer .run...Complete
}


####### Main script ###############################################################

echo ==================================
echo OFFLINE INSTALL CREATOR
echo ----------------------------------

PROG=${0##*/}

SUDO=$([[ $(id -u) -ne 0 ]] && echo "sudo" ||:)
echo SUDO: $SUDO

# parse args
while (($#))
do
    case "$1" in
    help)
        usage
        exit 0
        ;;
    url=*)
        URL_CONFIG="${1#*=}"
        echo URL configuration file: $URL_CONFIG
        shift
        ;;
    prompt)
        echo "Enabling creator user prompts."
        PROMPT_USER=1
        shift
        ;;
    config=*)
        CONFIG_FILE_PATH="${1#*=}"
        echo Create configuration file: $CONFIG_FILE_PATH
        shift
        ;;
    debug)
        echo "Enabling debug mode."
        DEBUG_MODE=1
        shift
        ;;
    *)
        shift
        ;;
    esac
done

if [ "$DEBUG_MODE" -eq 1 ]; then
    echo "Turn on debugging"
    set -x
fi

# Configure the creator
config_create


echo --------------------------------------------------
os_release

echo Build Name :
echo "    $CREATE_BUILD_TAG"
echo "    $CREATE_BUILD_DATE"
echo Usecases:
echo "    $ROCM_USECASES"
echo Extra Packages:
echo "    $EXTRA_PACKAGES"
echo ROCm Info:
echo "    ROCM_VERSIONS = $ROCM_VERSIONS"
echo --------------------------------------------------
echo Creator/Build Options:
echo -------------------------------
echo "Installer Name     = $INSTALL_PACKAGE_NAME"
echo "Installer Location = $INSTALL_PACKAGE_DIR"
echo "Installer Execute  = $INSTALL_MAKESELF_OPTIONS : local = $INSTALL_MAKESELF_LOCAL"
echo -------------------------------
echo amdgpu Options:
echo ---------------
echo "Install amdgpu              = $AMDGPU_INSTALL_DRIVER"
echo "Blacklist amdgpu on install = $AMDGPU_POST_INSTALL_BLACKLIST"
echo "Start amdgpu on install     = $AMDGPU_POST_INSTALL_START"
echo -------------------------------
echo Extra Package Options:
echo ----------------------
echo "Extra Packages Only    = $EXTRA_PACKAGES_ONLY"
echo -------------------------------
echo Post Install Options:
echo ----------------------
echo "Video,Render Group Add      = $AMDGPU_POST_GPU_ACCESS_CURRENT_USER"
echo "Add udev rule               = $AMDGPU_POST_GPU_ACCESS_ALL_USERS" 
echo -------------------------------
echo Config Options:
echo ---------------
echo "DEBUG_CREATE        = $DEBUG_CREATE"
echo "DOWNLOAD_ONLY       = $DOWNLOAD_ONLY"
echo "DOWNLOAD_PKG_CONFIG = $DOWNLOAD_PKG_CONFIG <$DOWNLOAD_PKG_CONFIG_NUM>"
echo "PROMPT_USER         = $PROMPT_USER"
echo --------------------------------------------------

prompt_user "Create new installer .run (y/n): "
if [[ $option == "Y" || $option == "y" ]]; then
    echo "Creating Offline Installer"
else
    echo "Exiting."
    exit 1
fi

echo ====================================================
echo Cleaning previous state...

# Clean up and partial/interrupted tool execution
cleanup_create

echo ====================================================
echo Setup Installer Package...

# Create the directory for downloading packages for the installer package
create_installer_package_dir

# Setup source repos (.list) for sourcing packages for create the installer package
setup_installer_repos

# Get the list of packages (based on the rocm usecase) for downloading and inclusion in the installer package
get_installer_package_list

echo Setup Installer Package...Complete

echo ====================================================
echo Downloading Packages...

# Download all required packages for the installer package
download_installer_packages

echo Downloading Packages...Complete

echo ====================================================
echo Installing tools...

# install any tools
install_tools

echo Installing tools...Complete

echo ====================================================
echo Download Validation...

# Verify the repo and attempt to resolve any missing dependencies (if option is enabled)
if [[ $VALIDATE_DOWNLOAD == "yes" ]]; then
    download_validate_resolve
fi

echo Download Validation...Complete

echo ====================================================
echo Building Installer Repo...

# Build the Package file for the installer's repo
create_install_repo

echo Building Installer Repo...Complete

echo ====================================================
echo Creating Installer Package...

# Create the installer .run
build_installer

echo Creating Installer Package...Complete

echo -e "\e[32m========================\e[0m"
echo -e "\e[32mOFFLINE INSTALL CREATED!\e[0m"
echo -e "\e[32m========================\e[0m"

echo Cleaning up...

prompt_user "Cleanup (y/n): "
if [[ $option == "Y" || $option == "y" ]]; then
    cleanup_create
fi

echo Cleaning up...Done

INSTALLER_INFO=$(du -h "$INSTALL_PACKAGE_DIR/$INSTALL_PACKAGE_NAME")
INSTALLER_INFO="${INSTALLER_INFO//K/KB}"
INSTALLER_INFO="${INSTALLER_INFO//M/MB}"
INSTALLER_INFO="${INSTALLER_INFO//G/GB}"
echo -e "\e[32m========================================================================================\e[0m"
echo -e "\e[32mLocation: $INSTALLER_INFO : $CREATE_BUILD_PKG_COUNT Packages\e[0m"
echo -e "\e[32m========================================================================================\e[0m"

} 2>&1 | $SUDO tee $CREATE_INSTALLER_CURRENT_LOG

echo "Create install log stored in: $CREATE_INSTALLER_CURRENT_LOG"
