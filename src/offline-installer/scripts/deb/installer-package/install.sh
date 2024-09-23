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

# Logs
RUN_INSTALLER_LOGS=/var/log/offline_creator
RUN_INSTALLER_CURRENT_LOG="$RUN_INSTALLER_LOGS/install_$(date +%s).log"

{

# Debug Settings
DEBUG_INSTALL=no
DEBUG_CONFIG=no
INSTALL_REPO_ONLY=no

# ROCm Install Config
ROCM_INSTALL_PATH=/opt/rocm
ROCM_INSTALL_VERSION_FULL=
ROCM_INSTALL_VERSION=
ROCM_USECASES=
ROCM_USECASES_PACKAGES=

# Extra Package Config
EXTRA_PACKAGES=

# Installer Config
INSTALLER_CONFIG_FILE=./install.config

INSTALL_REPO=/tmp/offline-repo
INSTALL_REPO_LIST=repo-offline.list
INSTALL_REPO_PIN=repo-offline-pin

UNINSTALL_PREV_ROCM=no
ROCM_POST_INSTALL=no

INSTALLER=
INSTALL_DIR=

# Script args
PROMPT_USER=0
INSTALLER_DRYRUN=0
INSTALLER_OPTS="-y "

# Installer .list cleanup
INSTALL_CLEAN_SOURCE_LIST_AMD=(amdgpu-build.list amdgpu-local.list amdgpu.list rocm-build.list rocm.list)
INSTALL_CLEAN_SOURCE_LIST=(repo-offline.list repo-offline-local.list)

# Post-Install Config

####### Functions ################################################################

usage() {
cat <<END_USAGE
Usage: $PROG [options]

[options}:
    help     = Display this help information.
    prompt   = Run the installer with user prompts.
    drynun   = Simulate running the installer (no packages will be installed).
END_USAGE
}

debugInstall() {
    if [[ $DEBUG_INSTALL == "yes" ]]; then
        read -p "$1: (continue = y, exit = n): " option
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
    echo -e "\e[32m++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\e[0m"
    echo -e "\e[32m No error: $msg\e[0m"
    echo -e "\e[32m++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\e[0m"
}

print_err() {
    local msg=$1
    echo -e "\e[31m++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\e[0m"
    echo -e "\e[31mError: $msg\e[0m"
    echo -e "\e[31m++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\e[0m"
}

pkg_installed() {
    local package_name=$1
    dpkg -l $package_name &> /dev/null
}

os_release() {	
    if [[ -r  /etc/os-release ]]; then
        . /etc/os-release

	DISTRO_NAME=$ID
	DISTRO_VER=$(awk -F= '/^VERSION_ID=/{print $2}' /etc/os-release | tr -d '"')

	case "$ID" in
	ubuntu|linuxmint|debian)
	    OS_TYPE=deb
	    DISTRO_CODENAME=$VERSION_CODENAME
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
    
    pkg_installed "mokutil"
    if [ $? -eq 0 ]; then
        echo Secure Boot: $($SUDO mokutil --sb-state)
    fi
}

disable_sources_list() {
    if [ -f /etc/apt/sources.list ]; then
        echo ^^^^ Disabling sources.list...
        $SUDO mv /etc/apt/sources.list /etc/apt/sources-bak.list
        echo ^^^^ Disabling sources.list...Complete
    fi
    
    if [ -f /etc/apt/sources.list.d/ubuntu.sources ]; then
        echo ^^^^ Disabling ubuntu.sources...
        $SUDO mv /etc/apt/sources.list.d/ubuntu.sources /etc/apt/sources.list.d/ubuntu.sources.bak
        echo ^^^^ Disabling ubuntu.sources...Complete
    fi
}

enable_sources_list() {
    if [ -f /etc/apt/sources-bak.list ]; then
        echo ^^^^ Enabling sources.list...
        $SUDO mv /etc/apt/sources-bak.list /etc/apt/sources.list
        echo ^^^^ Enabling sources.list...Complete
    fi
    
    if [ -f /etc/apt/sources.list.d/ubuntu.sources.bak ]; then
        echo ^^^^ Enabling ubuntu.sources...
        $SUDO mv /etc/apt/sources.list.d/ubuntu.sources.bak /etc/apt/sources.list.d/ubuntu.sources
        echo ^^^^ Enabling ubuntu.sources...Complete
    fi
}

create_repos() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Creating repo directories...
    
    debugInstall create_repos
    
    echo Creating Offline Install repo: $INSTALL_REPO
    mkdir -m775 $INSTALL_REPO
    
    echo Creating repo directories...Complete
}

setup_repos() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Copying Packages...
    
    debugInstall setup_repos
    
    # Copy ROCm packages to the new location
    cp -Rp ./packages/* $INSTALL_REPO

    echo Copying Packages... Complete

    # Disable the sources.list
    disable_sources_list
    
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Setting offline repos...
    
    # Copy the .list/pin files to /etc/apt
    echo ^^^^ Copying .list to /etc/apt/sources.list.d...
    $SUDO cp -Rp ./$INSTALL_REPO_LIST /etc/apt/sources.list.d
    echo ^^^^ Copying .list to /etc/apt/sources.list.d...Complete
    
    echo ^^^^ Copying pin to /etc/apt/preferences.d...
    $SUDO cp -Rp ./$INSTALL_REPO_PIN /etc/apt/preferences.d
    echo ^^^^ Copying pin to /etc/apt/preferences.d...Complete
    
    $SUDO apt-get update > /dev/null 2>&1
    
    echo Setting offline repos...Complete
}

cleanup_repos() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Cleaning up repos...
    
    debugInstall cleanup_repos
    
    # Remove any AMD .list files
    for index in ${INSTALL_CLEAN_SOURCE_LIST_AMD[@]}; do
        if [ -f /etc/apt/sources.list.d/$index ]; then
            echo =-=-=-= Removing $index =-=-=-=
            $SUDO rm /etc/apt/sources.list.d/$index
        fi
    done

    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Removing repo directories...
    if [ -d $INSTALL_REPO ]; then
        echo =-=-=-= Removing $INSTALL_REPO =-=-=-=
        rm -r $INSTALL_REPO
    fi
    
    # Restore/enable sources.list if previously disabled
    enable_sources_list

    # Remove any installer .list files
    for index in ${INSTALL_CLEAN_SOURCE_LIST[@]}; do
        if [ -f /etc/apt/sources.list.d/$index ]; then
            echo =-=-=-= Removing $index =-=-=-=
            $SUDO rm /etc/apt/sources.list.d/$index
        fi
    done
    
    # Remove any install pin files
    if [ -f /etc/apt/preferences.d/$INSTALL_REPO_PIN ]; then
        echo =-=-=-= Removing $INSTALL_REPO_PIN =-=-=-=
        $SUDO rm /etc/apt/preferences.d/$INSTALL_REPO_PIN
    fi
    
    $SUDO apt-get update > /dev/null 2>&1
    
    echo Cleaning up repos...Complete
}

config_install() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Install Configure...
    
    if [ -f $INSTALLER_CONFIG_FILE ]; then
        echo Using create configuration file: $INSTALLER_CONFIG_FILE
        source $INSTALLER_CONFIG_FILE
    else
        echo Using default installer configuration
        ROCM_USECASES=rocm
        ROCM_USECASES_PACKAGES="rocm-developer-tools rocm-utils rocm-openmp-sdk rocm-opencl-sdk rocm-ml-sdk amdgpu-dkms"
    fi
    
    if [ $AMDGPU_INSTALL_DRIVER == "no" ]; then
        echo amdgpu driver will not be installed.
        ROCM_USECASES_PACKAGES="${ROCM_USECASES_PACKAGES/amdgpu-dkms/}"
    fi
    
    # Check that the installer was created for the same distro
    if [[ $CREATE_DISTRO_NAME == $DISTRO_NAME && $CREATE_DISTRO_VER == $DISTRO_VER ]]; then
        print_no_err "Installer Version Match: $CREATE_DISTRO_NAME $CREATE_DISTRO_VER"
    else
        print_err "Installer Version Mismatch: $CREATE_DISTRO_NAME $CREATE_DISTRO_VER != $DISTRO_NAME $DISTRO_VER"
        exit 1
    fi
    
    # Check that the installer was created for the same kernel version
    if [[ $CREATE_DISTRO_KERNEL_VER == $KERNEL_VER ]]; then
        print_no_err "Installer Kernel Version Match: $CREATE_DISTRO_KERNEL_VER"
    else
        print_err "Installer Kernel Version Mismatch: $CREATE_DISTRO_KERNEL_VER != $KERNEL_VER"
        exit 1
    fi
    
    # Check that /etc/apt/sources.list.d exist
    if [ ! -d /etc/apt/sources.list.d ]; then
        print_err "/etc/apt/sources.list.d does not exist."
        exit 1
    fi
    
    # Parse the ROCm version
    ROCM_VERSION_MAJOR=${ROCM_VERSIONS:0:1}
    ROCM_VERSION_MINOR=${ROCM_VERSIONS:2:1}
    ROCM_VERSION_PATCH=${ROCM_VERSIONS:4:1}
    
    if [ -z $ROCM_VERSION_PATCH ]; then
        ROCM_VERSION_PATCH=0
    fi
    ROCM_INSTALL_VERSION=$ROCM_VERSION_MAJOR.$ROCM_VERSION_MINOR.$ROCM_VERSION_PATCH
    
    # Add ROCm post installation for non-driver only install
    if [[ ! $ROCM_USECASES == "dkms" ]]; then
        ROCM_POST_INSTALL=yes
    fi

    echo Install Configure...Complete
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


install_check() {
    local exit_status=$?
    
    if [ $exit_status -eq 0 ]; then
    	print_no_err "Packages installed successfully."
    else
        print_err "Packages failed to install.  exit_status $exit_status"
        cleanup_repos
        exit 1
    fi
}

install_rocm() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Installing ROCm from: $(pwd)
    echo Installing ROCm packages...
    echo $ROCM_USECASES_PACKAGES
    echo ---------------------------------------------
    
    debugInstall install_rocm
    
    $SUDO apt-get update > /dev/null
     
    if [[ $INSTALL_REPO_ONLY == "yes" ]]; then
        echo Installed only packages to offline repo.
        echo Install Complete.
        exit 1
    fi
    
    echo ^^^^ Installing packages...
    $SUDO apt-get install $INSTALLER_OPTS $ROCM_USECASES_PACKAGES
    install_check
    echo ^^^^ Installing packages...Complete
    
    if [ -n "$EXTRA_PACKAGES" ]; then
        echo ---------------------------------------------
        echo Installing Extra packages... $EXTRA_PACKAGES
        $SUDO apt-get install $INSTALLER_OPTS $EXTRA_PACKAGES
        echo Installing Extra packages...Complete
    fi
    
    echo ---------------------------------------------
    echo Setting up amdgpu-install...
    
    $SUDO cp ./amdgpu-install /usr/bin
    $SUDO chmod 755 /usr/bin/amdgpu-install
    
    echo Creating amdgpu-uninstall...
    $SUDO ln -sf ./amdgpu-install /usr/bin/amdgpu-uninstall
    
    echo Setting amdgpu-install...Complete
}

uninstall_rocm() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Uninstalling previous ROCm...
    
    debugInstall uninstall_rocm
    
    # check that amdgpu-install isn't installed already
    pkg_installed "amdgpu-install"
    if [ $? -eq 0 ]; then
        echo amdgpu-install package is already installed. Cleaning up for new install
        
        $SUDO amdgpu-uninstall
        
        $SUDO apt purge amdgpu-install
        $SUDO apt autoremove
    else
        echo amdgpu-install package not installed - using the bin if avaiable
        if [ -f /usr/bin/amdgpu-install ]; then
            $SUDO amdgpu-install --uninstall
            $SUDO rm /usr/bin/amdgpu-install
            $SUDO rm /usr/bin/amdgpu-uninstall
        else
            echo Unable to uninstall previous ROCm
        fi
    fi
    
    echo Cleaning up installation...Complete
}

install_extra_links() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    
    echo Installing Extra Symbolic Links for $ROCM_INSTALL_PATH-$ROCM_INSTALL_VERSION
    
    if [ -f $ROCM_INSTALL_PATH-$ROCM_INSTALL_VERSION/bin/rocminfo ]; then
        echo Creating link for rocminfo

        # /etc/alternatives symlinks
        if [ ! -f /etc/alternatives/rocminfo ]; then
            $SUDO ln -s $ROCM_INSTALL_PATH-$ROCM_INSTALL_VERSION/bin/rocminfo /etc/alternatives/rocminfo
        fi

        # /usr/bin symlinks
        if [ ! -f /usr/bin/rocminfo ]; then
            $SUDO ln -s /etc/alternatives/rocminfo /usr/bin/rocminfo
        fi
    else
        echo rocminfo not found.
    fi
    
    if [ -f $ROCM_INSTALL_PATH-$ROCM_INSTALL_VERSION/bin/rocm-smi ]; then
        echo Creating link for rocm-smi
    
        # /etc/alternatives symlinks
        if [ ! -f /etc/alternatives/rocm-smi ]; then
            $SUDO ln -s $ROCM_INSTALL_PATH-$ROCM_INSTALL_VERSION/bin/rocm-smi /etc/alternatives/rocm-smi
        fi

        # /usr/bin symlinks
        if [ ! -f /usr/bin/rocm-smi ]; then
            $SUDO ln -s /etc/alternatives/rocm-smi /usr/bin/rocm-smi
        fi
    else
        echo rocm-smi not found.
    fi
}

install_post_rocm() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Installing ROCm post-install config
    
    # Configure the system linker
    # Instruct the system linker where to find shared objects (.so files) for ROCm applications.S
    echo Configuring linker for ROCm...
$SUDO tee --append /etc/ld.so.conf.d/rocm.conf <<EOF
$ROCM_INSTALL_PATH/lib
$ROCM_INSTALL_PATH/lib64
EOF
$SUDO ldconfig

    # Configure PATH.  Add binary paths to the PATH environment variable.
    echo Adding ROCm $ROCM_INSTALL_VERSION to PATH...
    
    export PATH=$PATH:$ROCM_INSTALL_PATH-$ROCM_INSTALL_VERSION/bin
    
    echo ROCm PATH added: $PATH
}

install_post_user_group() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Setting Render/Video group...
    echo Current User = $USER
        
    $SUDO usermod -aG render,video $USER
    #exec $SUDO su -l $USER
        
    echo -e "\e[31m< System reboot may be required >\e[0m"
         
    echo Setting Render/Video group...Complete
}

install_post_amdgpu_blacklist() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Blacklisting amdgpu driver...
    
    echo "blacklist amdgpu" | $SUDO tee -a /etc/modprobe.d/blacklist.conf
    $SUDO update-initramfs -u -k all
    
    echo Blacklisting amdgpu driver...Complete
}

install_post_start_amdgpu() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Starting amdgpu driver...
    
    $SUDO modprobe amdgpu
    
    echo Starting amdgpu driver...Complete
}

install_post_config() {
    # Update the rocm install version info
    if [ -d $ROCM_INSTALL_PATH ]; then
        echo ROCM directory found.
    
        ROCM_INSTALL_VERSION_FULL=$(cat $ROCM_INSTALL_PATH/.info/version)
        echo ROCM_INSTALL_VERSION_FULL = $ROCM_INSTALL_VERSION_FULL
    
        ROCM_INSTALL_VERSION=${ROCM_INSTALL_VERSION_FULL%-*}
        echo ROCM_INSTALL_VERSION = $ROCM_INSTALL_VERSION
    fi

    # Install any extra post-install settings
    if [ $ROCM_POST_INSTALL == "yes" ]; then
        install_post_rocm
    fi

    # Set the video,render group if required
    if [ $AMDGPU_POST_INSTALL_VIDEO_RENDER_GRP == "yes" ]; then
         install_post_user_group
    fi
    
    # Blacklist the amdgpu driver if required
    if [ $AMDGPU_POST_INSTALL_BLACKLIST == "yes" ]; then
        install_post_amdgpu_blacklist
    fi
    
    # Init/Start the amdgpu driver after install if required
    if [ $AMDGPU_POST_INSTALL_START == "yes" ]; then
        install_post_start_amdgpu
    fi
}

####### Main script ###############################################################

echo ========================
echo OFFLINE INSTALL
echo ========================

PROG=${0##*/}
INSTALLER=${0##*/}
INSTALL_DIR=$(cd ${0%/*} && pwd -P)
echo Installer $INSTALLER running from: $INSTALL_DIR

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
    dryrun)
        echo "Installer dryrun."
        INSTALLER_DRYRUN=1
        INSTALLER_OPTS+="--dry-run"
        shift
        ;;
    prompt)
        echo "Enabling installer user prompts."
        PROMPT_USER=1
        shift
        ;;
    *)
        shift
        ;;
    esac
done

os_release

config_install

echo Usecases:
echo "    $ROCM_USECASES"
echo Usecase Packages:
echo "    $ROCM_USECASES_PACKAGES"
echo Extras:
echo "    $EXTRA_PACKAGES"


echo --------------------------------------------------
echo "CREATE_PACKAGE           = $CREATE_PACKAGE"
echo "CREATE_VERSION           = $CREATE_VERSION"
echo "CREATE_BUILD_TAG         = $CREATE_BUILD_TAG"
echo "CREATE_DISTRO_NAME       = $CREATE_DISTRO_NAME"
echo "CREATE_DISTRO_VER        = $CREATE_DISTRO_VER"
echo "CREATE_DISTRO_KERNEL_VER = $CREATE_DISTRO_KERNEL_VER"
echo "CREATE_BUILD_DATE        = $CREATE_BUILD_DATE"
echo --------------------------------------------------
echo "ROCM_INSTALL_PATH      = $ROCM_INSTALL_PATH"
echo "ROCM_VERSIONS          = $ROCM_VERSIONS : $ROCM_INSTALL_VERSION"
echo "ROCM_USECASES          = $ROCM_USECASES"
echo "ROCM_USECASES_PACKAGES = $ROCM_USECASES_PACKAGES"
echo --------------------------------------------------
echo "AMDGPU_INSTALL_DRIVER  = $AMDGPU_INSTALL_DRIVER"
echo "AMDGPU_POST_INSTALL_VIDEO_RENDER_GRP = $AMDGPU_POST_INSTALL_VIDEO_RENDER_GRP"
echo "AMDGPU_POST_INSTALL_BLACKLIST        = $AMDGPU_POST_INSTALL_BLACKLIST"
echo "AMDGPU_POST_INSTALL_START            = $AMDGPU_POST_INSTALL_START"
echo --------------------------------------------------
echo "INSTALL_REPO_ONLY      = $INSTALL_REPO_ONLY"
echo "INSTALL_REPO           = $INSTALL_REPO"
echo "INSTALL_REPO_LIST      = $INSTALL_REPO_LIST"
echo "UNINSTALL_PREV_ROCM    = $UNINSTALL_PREV_ROCM"
echo "ROCM_POST_INSTALL      = $ROCM_POST_INSTALL"
echo --------------------------------------------------
echo "DEBUG_INSTALL          = $DEBUG_INSTALL"
echo "PROMPT_USER            = $PROMPT_USER"
echo "INSTALLER_DRYRUN       = $INSTALLER_DRYRUN"
echo "INSTALLER_OPTS         = $INSTALLER_OPTS"
echo --------------------------------------------------

if [ $UNINSTALL_PREV_ROCM == "yes" ]; then
    echo ====================================================
    prompt_user "UnInstall previous ROCm (y/n): "
    if [[ $option == "Y" || $option == "y" ]]; then
        echo Uninstalling Previous ROCm install...
        
        uninstall_rocm
        
        echo Uninstalling Previous ROCm install...Complete
    fi
fi

prompt_user "Install Offline ROCm .run (y/n): "
if [[ $option == "Y" || $option == "y" ]]; then
    echo "Installing Offline ROCm"
else
    echo "Exiting."
    exit 1
fi

echo ====================================================
echo Setting up local repos...

cleanup_repos

create_repos

setup_repos

echo Setting up local repos...Complete

echo ====================================================
echo Installing Packages...
echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

echo INSTALL...

install_rocm

if [[ $INSTALLER_DRYRUN == 0 ]]; then
    install_extra_links
fi

echo Installing Packages...Complete

echo ====================================================
echo Restoring sources.list...

enable_sources_list

echo Restoring sources.list...Complete

echo ====================================================
echo Post-install Configuration...

if [[ $INSTALLER_DRYRUN == 0 ]]; then
    install_post_config
fi

echo Post-install Configuration...Complete

echo -e "\e[32m=========================\e[0m"
echo -e "\e[32mOFFLINE INSTALL COMPLETE!\e[0m"
echo -e "\e[32m=========================\e[0m"

echo ====================================================
echo Cleaning up...

prompt_user "Cleanup (y/n): "
if [[ $option == "Y" || $option == "y" ]]; then
   cleanup_repos
fi

echo Cleaning up...Complete

} 2>&1 | sudo tee $RUN_INSTALLER_CURRENT_LOG

echo "Install log stored in: $RUN_INSTALLER_CURRENT_LOG"

