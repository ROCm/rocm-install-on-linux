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

# Creates a install .run using AMD repos as a source and adds dependent packages
WGET_RETRY_COUNT=5

# Debug Settings
DEBUG_CREATE=no
DEBUG_CONFIG=no

# System Information
DISTRO_NAME=
OS_TYPE=
DISTRO_VER=
KERNEL_VER=


# Kernel packages to include
KERNEL_PACKAGES_VER=
KERNEL_PACKAGES=
KERNEL_PACKAGES_AMDGPU=

# ROCm Packages Config
ROCM_USECASES=

# Driver/amdgpu Packages
AMDGPU_PACKAGES=

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

# Script args
PROMPT_USER=0

# Cleanup repos
CREATE_CLEAN_YUM_REPOS_AMD=(repo-tar-offline.repo repo-offline.repo amdgpu.repo amdgpu-proprietary.repo amdgpu-build.repo amdgpu-local.repo rocm-build.repo rocm.repo)


###### Functions ###############################################################

usage() {
cat <<END_USAGE
Usage: $PROG [options]

[options}:
    help               = Displays this help information.
    version            = Displays the ROCm Offline Creater Tool version. 
    prompt             = Run the creator with user prompts.
    config=<file_path> = <file_path> Full path to a .config file with create settings in the format of create-default.config.
    
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
    rpm -q $package_name &> /dev/null
}

os_release() {	
    if [[ -r  /etc/os-release ]]; then
        . /etc/os-release

	DISTRO_NAME=$ID
	DISTRO_VER=$(awk -F= '/^VERSION_ID=/{print $2}' /etc/os-release | tr -d '"')

	case "$ID" in
	fedora|rhel|centos|almalinux|rocky)
	    OS_TYPE=rpm
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
    echo "   ${DISTRO_NAME} ${DISTRO_VER} : type = $OS_TYPE"
    
    KERNEL_VER=$(uname -r)
    echo Kernel:
    echo "   ${KERNEL_VER}"
}

update_dnf_conf() {
    $SUDO cp /etc/dnf/dnf.conf /etc/dnf/dnf.conf.bak

    # check if the dnf.conf file has fastestmirror=true
    grep -q "fastestmirror=true" /etc/dnf/dnf.conf
    if [ $? -ne 0 ]; then
        echo Enabling fastest mirror.
        echo "fastestmirror=true" | $SUDO tee -a /etc/dnf/dnf.conf
    fi
}

restore_dnf_conf() {
    # restore the dnf.conf file from the backup file
    
    if [ -f /etc/yum.repos.d/epel.repo ]; then
        echo Restoring dnf.conf
        if [ -f /etc/dnf/dnf.conf.bak ]; then
            $SUDO cp /etc/dnf/dnf.conf.bak /etc/dnf/dnf.conf
            $SUDO rm /etc/dnf/dnf.conf.bak
        fi
    fi
}

install_prereqs() {
    # Setup EPEL/crb
    if [ -f /etc/yum.repos.d/epel.repo ]; then
        echo "EPEL repo exists."
    else
        echo "EPEL repo setup."
        if [[ $DISTRO_VER == 8* ]]; then
            wget --tries $WGET_RETRY_COUNT https://dl.fedoraproject.org/pub/epel/epel-release-latest-8.noarch.rpm
            $SUDO rpm -ivh epel-release-latest-8.noarch.rpm
        elif [[ $DISTRO_VER == 9* ]]; then
            wget --tries $WGET_RETRY_COUNT https://dl.fedoraproject.org/pub/epel/epel-release-latest-9.noarch.rpm
            $SUDO rpm -ivh epel-release-latest-9.noarch.rpm
        else
            echo "Unsupported version for EPEL."
        fi
    fi
    
    $SUDO dnf install -y dnf-plugin-config-manager
    
    $SUDO crb enable
    
    # Update the dnf.conf for faster mirrors etc.
    update_dnf_conf
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
        
        if [[ $DISTRO_VER == 8* ]]; then
            local RHEL_BASE_VER=el8
        else
            local RHEL_BASE_VER=el9
        fi
        
        AMDGPU_INSTALL_NAME=amdgpu-install-$VER_MAJ.$VER_MIN.$VER_MAJ"0"$VER_MIN"0"$VER_MIN_MIN-1.$RHEL_BASE_VER.noarch.rpm
        AMDGPU_INSTALL_URL=https://repo.radeon.com/amdgpu-install/$ROCM_VERSIONS/rhel/$DISTRO_VER/$AMDGPU_INSTALL_NAME
    else
        AMDGPU_INSTALL_NAME=$(basename $AMDGPU_INSTALL_URL)
    fi
    
    echo install: $AMDGPU_INSTALL_NAME
        
    # Download the amdgpu-install package and associated dependencies
    wget --tries $WGET_RETRY_COUNT $AMDGPU_INSTALL_URL
        
    check_error "Successfully downloaded amdgpu-install." "Failed amdgpu-install download."

    $SUDO chmod 644 ./$AMDGPU_INSTALL_NAME
        
    $SUDO dnf download --downloadonly --resolve --downloaddir="./$CREATE_INSTALLER_PACKAGE_DIR" install ./$AMDGPU_INSTALL_NAME

    # Install amdgpu-install for host installer creation
    $SUDO dnf clean all
    $SUDO dnf install -y ./$AMDGPU_INSTALL_NAME
    
    # Update the amdgpu.repo (if required)
    if [[ -n $AMDGPU_URL ]]; then
        echo Updating amdgpu url...
        
        # Find the URL in the file and replace it
        $SUDO sed -i "s#https[^ ]*#$AMDGPU_URL#g" "/etc/yum.repos.d/amdgpu.repo"
    fi
    
    # Update the rocm.repo (if required)
    if [[ -n $ROCM_URL ]]; then
        echo Updating rocm url...
        
        # Find the URL in the file and replace it
        $SUDO sed -i "s#https[^ ]*#$ROCM_URL#g" "/etc/yum.repos.d/rocm.repo"
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
        
        $SUDO dnf remove -y amdgpu-install
        $SUDO dnf autoremove -y
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
    
    # Remove any creator .repo files
    for index in ${CREATE_CLEAN_YUM_REPOS_AMD[@]}; do
        if [ -f /etc/yum.repos.d/$index ]; then
            echo =-=-=-= Removing $index =-=-=-=
            $SUDO rm /etc/yum.repos.d/$index
        fi
    done
   
    # cleanup dnf cache
    $SUDO dnf clean all
    $SUDO rm -r /var/cache/dnf/*
   
    # restore the dnf.conf
    restore_dnf_conf
   
    echo Cleaning up installation...Complete
}

install_tools() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Installing tools...
    
    # Install createrepo for repo creation
    $SUDO dnf install --assumeyes createrepo
    
    # Install makself for .run creation
    $SUDO dnf install --assumeyes makeself
    
    # Check the version of makself and enable cleanup script support if >= 2.4.2
    makeself_version_min=2.4.2
    makeself_version=$(makeself --version)
    makeself_version=${makeself_version#Makeself version }

    if [[ "$(printf '%s\n' "$makeself_version_min" "$makeself_version" | sort -V | head -n1)" = "$makeself_version_min" ]]; then
        INSTALL_MAKESELF_OPTIONS+="--cleanup ./cleanup-install.sh"
        echo Enabling cleanup script support.
    fi
    
    echo Installing tools...Complete
}

get_installer_package_list() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Creating packages list...
        
    debugCreate get_installer_package_list
        
    amdgpu_install_out=$($CREATE_CONFIG_AMDGPU_INSTALL $CREATE_CONFIG_AMDGPU_INSTALL_PARAMS --usecase=$ROCM_USECASES)
    
    # Remove text 'dnf install' or 'sudo dnf install' from amdgpu_install_out
    # docker doesn't have 'sudo' output but barel metal does
    PACKAGES=$(echo "${amdgpu_install_out}" | sed -E 's/(sudo )?dnf install//')
    PACKAGES=${PACKAGES%%kernel*}
    PACKAGES=${PACKAGES%%sudo ln*}
    
    # set the ROCm usecase
    ROCM_USECASES_PACKAGES="${PACKAGES//amdgpu-dkms/}"
    
    # set the kernel packages
    $SUDO dnf list "kernel-headers-$KERNEL_VER" &> /dev/null
    if [ $? -eq 0 ]; then
        echo "Kernel Packages for $KERNEL_VER are available in the repositories."
        KERNEL_PACKAGES_VER="-$KERNEL_VER"
    else
        echo "Kernel Packages not available in the repositories.  Using defaults."
    fi
    
    KERNEL_PACKAGES="kernel-headers$KERNEL_PACKAGES_VER kernel-devel$KERNEL_PACKAGES_VER kernel-modules$KERNEL_PACKAGES_VER "
    
    if [[ $DISTRO_VER == 9* ]]; then
        echo Adding rhel9 kernel packages
        if [ $DOWNLOAD_PKG_CONFIG_NUM == $DOWNLOAD_PKG_FULL ]; then
            echo "Adding extra kernel packages for full dep mode"
            KERNEL_PACKAGES+="glibc-all-langpacks glibc-langpack-en "
        fi
         
        if [ $AMDGPU_INSTALL_DRIVER == "yes" ]; then
             echo Adding amdgpu kernel packages
             KERNEL_PACKAGES_AMDGPU="kernel-devel-matched$KERNEL_PACKAGES_VER "
        fi
    else
        echo Adding rhel8 kernel packages
        if [ $AMDGPU_INSTALL_DRIVER == "yes" ]; then
             echo Adding amdgpu kernel packages
             KERNEL_PACKAGES_AMDGPU="annobin gcc-plugin-annobin "
        fi
    fi
    
    PACKAGES+=${KERNEL_PACKAGES}
    PACKAGES+=${KERNEL_PACKAGES_AMDGPU}
    
    # remove amdgpu if not installing the driver
    if [ $AMDGPU_INSTALL_DRIVER == "yes" ]; then
        echo Adding amdgpu
        AMDGPU_PACKAGES=amdgpu-dkms
    else
        echo Removing amdgpu
        PACKAGES="${PACKAGES//amdgpu-dkms/}"
    fi
    
    # Add any extra packages
    PACKAGES+=${EXTRA_PACKAGES}
    
    # If only extra packages are require - only download those
    if [ $EXTRA_PACKAGES_ONLY == "yes" ]; then
        echo Only Downloading Extra Packages for Installer.
        PACKAGES=$EXTRA_PACKAGES
    fi 

    echo ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    echo "KERNEL_PACKAGES        = $KERNEL_PACKAGES"
    echo "KERNEL_PACKAGES_AMDGPU = $KERNEL_PACKAGES_AMDGPU"
    echo "ROCM_USECASES_PACKAGES = $ROCM_USECASES_PACKAGES"
    echo "AMDGPU_PACKAGES        = $AMDGPU_PACKAGES"
    echo "PACKAGES               = $PACKAGES"
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
    
    # create the repo
    createrepo ./$CREATE_INSTALLER_PACKAGE_DIR

    # create a .repo file for the temp repo
cat <<EOT | $SUDO tee /etc/yum.repos.d/repo-offline.repo
[repo-offline]
name=ROCm-amdgpu offline repository validation
baseurl=file://$(pwd)/$CREATE_INSTALLER_PACKAGE_DIR
enabled=0    
EOT
    # cleanup the dnf cache
    $SUDO dnf clean all
    $SUDO rm -rf /var/cache/dnf/*
    
    # simulate/dryrun the install
    errorCheck=$($SUDO dnf --nogpg --assumeno --disablerepo=* --enablerepo=repo-offline --allowerasing install $PACKAGES)
    if  [[ $errorCheck == *"Error"* ]] || [[ $errorCheck == *"uninstallable"* ]]; then
        echo Error occurred.  Repo validation failed.  Attempting to resolve...
        
        # attempt to determine what package dependencies are missing
        output_dryrun=$($SUDO dnf --nogpg --assumeno --allowerasing --disablerepo=* --enablerepo=repo-offline install $PACKAGES)
        
        missing_packages=${output_dryrun#*Removing dependent packages:}
        missing_packages=${missing_packages%%Transaction*}
        missing_packages=$(echo "$missing_packages" | awk '{print $1}' | awk -F'.' '{print $1}')
        missing_packages=$(echo "$missing_packages" | sort | uniq)
        
        echo "<><><><><><><><><><><><><>"
        echo The following packages may need to be added to extras to resolve dependencies:
        echo $missing_packages
        echo "<><><><><><><><><><><><><>"
        
        # delete the currently downloaded packages and download again
        $SUDO rm -r ./$CREATE_INSTALLER_PACKAGE_DIR/*
    	$SUDO dnf clean all 
    	$SUDO rm -rf /var/cache/dnf/*
    	
    	# download again and include the missing packages
    	pushd ./$CREATE_INSTALLER_PACKAGE_DIR
    	    $SUDO dnf download --downloadonly --resolve --skip-broken --alldeps --downloaddir="./" $PACKAGES $missing_packages
    	    $SUDO chmod 644 *
    	popd
    	
        createrepo ./$CREATE_INSTALLER_PACKAGE_DIR
        
        # simulate the install again to see if there are any errors
        errorCheck=$($SUDO dnf --nogpg --assumeno --disablerepo=* --enablerepo=repo-offline install $PACKAGES  $missing_packages)
        if  [[ $errorCheck == *"Error"* ]] || [[ $errorCheck == *"uninstallable"* ]]; then
            print_err "Repo validation failed."
            exit 1
        else
             print_no_err "Valid package dependencies."
        fi
    else
        print_no_err "Valid package dependencies."
    fi
    
    # cleanup the temp repo
    $SUDO rm -r ./$CREATE_INSTALLER_PACKAGE_DIR/repodata
    $SUDO rm /etc/yum.repos.d/repo-offline.repo
    
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
    
        $SUDO dnf clean all
        $SUDO rm -rf /var/cache/dnf/*
        
        echo Source repos:
        dnf repolist

        echo =-=-=-= download packages =-=-=-=
        prompt_user "Start Download (y/n): "
        if [[ $option == "Y" || $option == "y" ]]; then
        
            # check the download mode     
            if [ $DOWNLOAD_PKG_CONFIG_NUM == $DOWNLOAD_PKG_FULL ]; then
                # full download - normal full dep mode
                $SUDO dnf download --resolve --alldeps --downloaddir="./" $PACKAGES
            else
                # simple download - minimum dep mode
                $SUDO dnf download --resolve --downloaddir="./" $PACKAGES
            fi
            
            # check for any errors during download
            check_error "Package download successful." "Package download failed."
            
            $SUDO chmod 644 *
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
        $SUDO rm -r /tmp/offline-repo
        mkdir -p -m755 /tmp/offline-repo
        cp -r ./$CREATE_INSTALLER_PACKAGE_DIR/* /tmp/offline-repo/
        echo ++++++++++++++++++++++++++++++++
        exit 1
    fi
    
    # Verify the repo and attempt to resolve any missing dependencies (if option is enabled)
    if [[ $VALIDATE_DOWNLOAD == "yes" ]]; then
    	download_validate_resolve
    fi
}

create_install_repo() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Creating Installer Repo Setup...
    
    debugCreate create_install_repo
    
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Creating Packages list...
    
    CREATE_BUILD_PKG_COUNT=$(ls ./$CREATE_INSTALLER_PACKAGE_DIR | wc -l)

    # Create the Packages index for the offline repo
    pushd ./$CREATE_INSTALLER_PACKAGE_DIR
        createrepo .
    popd
    
    echo Creating Packages list...Complete : Total $CREATE_BUILD_PKG_COUNT packages
    echo Creating Installer Repo Setup...Complete
}

parse_package_config() {
    echo ^^^^ Parsing dependency config = $DOWNLOAD_PKG_CONFIG_NUM.
    
    local download_config=
    
    if [ $DOWNLOAD_PKG_CONFIG_NUM == $DOWNLOAD_PKG_FULL ]; then
        download_config=-full
    else
        download_config=-minimum
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
        if [[ ! -f $URL_CONFIG ]]; then
            print_err "URL configuration file not found."
            exit 1
        fi
        
        echo "Using URL Configuration file   : $URL_CONFIG"
        source $URL_CONFIG
        
        echo Checking URL for $DISTRO_VER
        if [[ "$AMDGPU_INSTALL_URL" != *"$DISTRO_VER"* ]]; then
            echo amdgpu-install distro version in URL file does not match.
            exit 1
        fi
        
        if [[ "$AMDGPU_URL" != *"$DISTRO_VER"* ]]; then
            echo amdgpu distro version in URL file does not match.
            exit 1
        fi
        
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
        echo DOWNLOAD_PKG_CONFIG_NUM=$DOWNLOAD_PKG_CONFIG_NUM >> $INSTALLER_CONFIG_FILE
        
        echo KERNEL_PACKAGES=\"$KERNEL_PACKAGES\" >> $INSTALLER_CONFIG_FILE
        
        echo ROCM_VERSIONS=$ROCM_VERSIONS >> $INSTALLER_CONFIG_FILE
        echo ROCM_USECASES=$ROCM_USECASES >> $INSTALLER_CONFIG_FILE
        echo ROCM_USECASES_PACKAGES=\"$ROCM_USECASES_PACKAGES\" >> $INSTALLER_CONFIG_FILE
        echo ROCM_BUILD=$ROCM_BUILD >> $INSTALLER_CONFIG_FILE
        
        echo EXTRA_PACKAGES=\"$EXTRA_PACKAGES\" >> $INSTALLER_CONFIG_FILE
        
        echo AMDGPU_INSTALL_DRIVER=$AMDGPU_INSTALL_DRIVER >> $INSTALLER_CONFIG_FILE
        echo AMDGPU_BUILD=$AMDGPU_BUILD >> $INSTALLER_CONFIG_FILE
        echo AMDGPU_PACKAGES=\"$AMDGPU_PACKAGES\" >> $INSTALLER_CONFIG_FILE
        echo AMDGPU_KERNEL_PACKAGES=\"$KERNEL_PACKAGES_AMDGPU\" >> $INSTALLER_CONFIG_FILE
        echo AMDGPU_POST_INSTALL_VIDEO_RENDER_GRP=$AMDGPU_POST_INSTALL_VIDEO_RENDER_GRP >> $INSTALLER_CONFIG_FILE
        echo AMDGPU_POST_INSTALL_BLACKLIST=$AMDGPU_POST_INSTALL_BLACKLIST >> $INSTALLER_CONFIG_FILE
        echo AMDGPU_POST_INSTALL_START=$AMDGPU_POST_INSTALL_START >> $INSTALLER_CONFIG_FILE
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
    makeself $INSTALL_MAKESELF_OPTIONS ./$CREATE_INSTALLER_DIR "./$INSTALL_PACKAGE_NAME" "ROCm Offline Install" ./install.sh
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
    *)
        shift
        ;;
    esac
done

echo --------------------------------------------------
os_release

# Configure the creator
config_create


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
echo "Video,Render Group Add      = $AMDGPU_POST_INSTALL_VIDEO_RENDER_GRP"
echo "Blacklist amdgpu on install = $AMDGPU_POST_INSTALL_BLACKLIST"
echo "Start amdgpu on install     = $AMDGPU_POST_INSTALL_START"
echo -------------------------------
echo Extra Package Options:
echo ----------------------
echo "Extra Packages Only    = $EXTRA_PACKAGES_ONLY"
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
echo Installing prereqs and tools...

# Install any prereqs
install_prereqs

# install any tools
install_tools

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

