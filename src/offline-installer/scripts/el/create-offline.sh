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

# Colour text
YELLOW="\033[0;93m"
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Creates a install .run using AMD repos as a source and adds dependent packages
WGET_RETRY_COUNT=5

# Debug Settings
DEBUG_CREATE=no
DEBUG_CONFIG=no

# System Information
DISTRO_NAME=
OS_TYPE=
DISTRO_VER=
DISTRO_MAJOR_VER=
KERNEL_VER=

# ROCm Version Info
ROCM_VERSION_MAJOR=
ROCM_VERSION_MINOR=
ROCM_VERSION_PATCH=
AMDGPU_VERSION=


# Kernel packages to include
KERNEL_PACKAGES_VER=

# ROCm packages to include
PACKAGES=

# Prereq packages to include
PREREQ_PACKAGES_ROCM=
PREREQ_PACKAGES_AMDGPU=
PREREQ_PACKAGES=

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
DEBUG_MODE=0

FOUND_ROCKY_KERNEL_HEADERS_IN_REPO=0

# Cleanup repos
CREATE_CLEAN_YUM_REPOS_AMD=(repo-tar-offline.repo repo-offline.repo amdgpu.repo amdgpu-proprietary.repo amdgpu-build.repo amdgpu-local.repo rocm-build.repo rocm.repo rocm-graphics.repo)

GCC_TOOLSET_PACKAGES_OL=(gcc-toolset-11-gcc gcc-toolset-11-gcc-c++ gcc-toolset-11-gcc-gfortran gcc-toolset-11-libquadmath-devel gcc-toolset-11-libstdc++-devel gcc-toolset-11-gcc-gdb-plugin)

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
        $PROG debug
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
    echo -e "${GREEN}++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++${NC}"
    echo -e "${GREEN} No error: $msg${NC}"
    echo -e "${GREEN}++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++${NC}"
}

print_err() {
    local msg=$1
    echo -e "\e[31m++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++${NC}"
    echo -e "\e[31mError: $msg${NC}"
    echo -e "\e[31m++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++${NC}"
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
    DISTRO_MAJOR_VER=${DISTRO_VER%.*}

    case "$ID" in
    fedora|rhel|centos|almalinux|rocky|ol)
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
        wget --tries $WGET_RETRY_COUNT https://dl.fedoraproject.org/pub/epel/epel-release-latest-${DISTRO_MAJOR_VER}.noarch.rpm
        if [ $? -ne 0 ]; then
            print_err "Unable to download epel rpm repo at URL: https://dl.fedoraproject.org/pub/epel/epel-release-latest-${DISTRO_MAJOR_VER}.noarch.rpm"
            exit 1
        fi
        $SUDO rpm -ivh epel-release-latest-${DISTRO_MAJOR_VER}.noarch.rpm
    fi

    $SUDO dnf install -y dnf-plugin-config-manager
    $SUDO crb enable

    # Update the dnf.conf for faster mirrors etc.
    update_dnf_conf
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

remove_rocky_kernel_repo() {
    if [ -f /etc/yum.repos.d/appstream-amdgpu.repo ]; then
        echo Removing Rocky AppStream repos...
        echo =-=-=-= Removing appstream-amdgpu.repo =-=-=-=
        $SUDO rm /etc/yum.repos.d/appstream-amdgpu.repo
        
        # Cleanup the dnf caches
        $SUDO dnf clean all
        $SUDO rm -rf /var/cache/dnf/*
        $SUDO dnf makecache
        echo Removing Rocky AppStream repos...Complete.
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

    if [[ "$DISTRO_NAME" = "rocky" ]]; then
        remove_rocky_kernel_repo
    fi

    # cleanup dnf cache
    $SUDO dnf clean all
    $SUDO rm -r /var/cache/dnf/*

    # restore the dnf.conf
    restore_dnf_conf

    echo Cleaning up installation...Complete
}

install_makeself_directly() {
    makeself --version &> /dev/null
    if [ $? -ne 0 ]; then
        echo "Install makeself directly from github releases."
        wget --tries $WGET_RETRY_COUNT https://github.com/megastep/makeself/releases/download/release-2.5.0/makeself-2.5.0.run
    fi
    
    if [ $? -ne 0 ]; then
        print_err "Failed to install makeself"
        exit 1
    fi
    chmod +x makeself-2.5.0.run
    ./makeself-2.5.0.run --target makeself
    $sudo mkdir -p /usr/local/bin
    $SUDO cp ./makeself/makeself.sh /usr/local/bin/makeself
    $SUDO chmod 755 /usr/local/bin/makeself
}

install_tools() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Installing tools...

    # Install createrepo for repo creation
    $SUDO dnf install --assumeyes createrepo

    $SUDO dnf install --assumeyes makeself
    if [ $? -ne 0 ]; then
        echo -e "${YELLOW}Failed to install makeself via the package manager.${NC}"
        install_makeself_directly
    fi

    # Check the version of makself and enable cleanup script support if >= 2.4.2
    makeself_version_min=2.4.2
    makeself_version=$(makeself --version)
    makeself_version=${makeself_version#Makeself version }

    if [[ "$(printf '%s\n' "$makeself_version_min" "$makeself_version" | sort -V | head -n1)" = "$makeself_version_min" ]]; then
        INSTALL_MAKESELF_OPTIONS+="--cleanup ./cleanup-install.sh --header ./rocm-makeself-header-install.sh --help-header ./VERSION"
        echo Enabling cleanup script support.
    fi

    echo Installing tools...Complete
}

# Add kernel_to_check to KERNEL_PACKAGES_VER if it's available in repo.
add_kernel_if_available() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Checking and adding kernel "$1" if it\'s is available in the repositories...

    local kernel_to_check="$1"
    # set the kernel packages
    $SUDO dnf list "$kernel_to_check" &> /dev/null
    if [ $? -eq 0 ]; then
        echo "Kernel Packages for $KERNEL_VER are available in the repositories."
        KERNEL_PACKAGES_VER="-$KERNEL_VER"
    else
        echo "Kernel Packages not available in the repositories.  Using defaults."
    fi
}

get_kernel_headers_matching_rhck_kernel_ol() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Get kernel header packages matching installed RHCK kernel for $DISTRO_NAME $DISTRO_VER

    rhck_kernel=$(rpm -q kernel | uniq | sort | head -1 | sed 's/kernel-//')
    if [[ -n $rhck_kernel ]]; then
        if [[ $DISTRO_VER_MAJ -eq 8 ]]; then
            num_of_packages_available=$($SUDO dnf repoquery --available --queryformat "%{name}-%{version}-%{release}.%{arch}" kernel-headers-$rhck_kernel kernel-devel-$rhck_kernel | wc -l)
            if [ $num_of_packages_available -eq 2 ]; then
                echo "Adding kernel packages kernel-headers and kernel-devel for RHCK kernel $rhck_kernel"
                PREREQ_PACKAGES_AMDGPU+="kernel-headers-$rhck_kernel kernel-devel-$rhck_kernel "
            else
                echo -e "${YELLOW}Kernel Packages for RHCK kernel $rhck_kernel not available, using defaults. ${NC}"
                PREREQ_PACKAGES_AMDGPU+="kernel-headers kernel-devel"
            fi
        else
            num_of_packages_available=$($SUDO dnf repoquery --available --queryformat "%{name}-%{version}-%{release}.%{arch}" kernel-headers-$rhck_kernel kernel-devel-$rhck_kernel kernel-devel-matched-$rhck_kernel | wc -l)
            if [ $num_of_packages_available -eq 3 ]; then
                echo "Adding kernel packages kernel-headers, kernel-devel and kernel-devel-matched for RHCK kernel $rhck_kernel"
                PREREQ_PACKAGES_AMDGPU+="kernel-headers-$rhck_kernel kernel-devel-$rhck_kernel kernel-devel-matched-$rhck_kernel "
            else
                echo -e "${YELLOW}Kernel Packages for RHCK kernel $rhck_kernel not available, using defaults. ${NC}"
                PREREQ_PACKAGES_AMDGPU+="kernel-headers kernel-devel kernel-devel-matched "
            fi
        fi
    else
        echo "No RHCK kernels detected on $DISTRO_NAME $DISTRO_VER"
    fi
}

get_installer_package_list_ol() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Creating packages list for Oracle Linux...

    debugCreate get_installer_package_list_ol

    # Adding kernel to packages list.
    if [ $AMDGPU_INSTALL_DRIVER == "yes" ]; then
        kernel_to_check="kernel-uek-devel-$KERNEL_VER"
        add_kernel_if_available "$kernel_to_check"
        PREREQ_PACKAGES_AMDGPU="kernel-uek-devel$KERNEL_PACKAGES_VER "

        get_kernel_headers_matching_rhck_kernel_ol

        # Get gcc version that's identical to the one that UEK was built from.
        # gcc version on system and gcc version UEK was built from must be identical
        # before building driver using dkms, otherwise you get an error.
        
        # Expect TARGET_GCC_VERSION to be in the format [MAJOR].[MINOR].[PATCH]-[MAJOR].[MINOR].[PATCH]
        # Example: 11.5.0-2.0.1
        if [ -f "/boot/config-$(uname -r)" ]; then
            echo "Find the value of TARGET_GCC_VERSION using CONFIG_CC_VERSION_TEXT from /boot/config-$(uname -r)"
            TARGET_GCC_VERSION=$($SUDO cat /boot/config-$(uname -r) | grep CONFIG_CC_VERSION_TEXT | cut -d '=' -f2 | awk -F " " '{print $NF}' | tr -d ')' | tr -d '"')
            for gcc_package in ${GCC_TOOLSET_PACKAGES_OL[@]}; do
                # Expect full package name we want to install
                # Example: gcc-toolset-11-gcc-11.4.1-3.0.1.el8_6
                gcc_package_ver=$($SUDO dnf --disablerepo="*" --enablerepo="ol${DISTRO_MAJOR_VER}_appstream" repoquery --all --nvr | grep "$gcc_package-$TARGET_GCC_VERSION" | awk '{print $NF}' | sort | uniq | tail -1)

                if [[ -n $gcc_package_ver ]]; then
                    echo "Install $gcc_package version $gcc_package_ver"
                    PREREQ_PACKAGES_AMDGPU+="$gcc_package_ver "
                else
                    echo "Unable to find gcc version $TARGET_GCC_VERSION for package $gcc_package_ver in repo ol${DISTRO_VER_MAJ}_appstream"
                fi
            done
        fi
    fi

    if [ $ROCM_INSTALL == "yes" ]; then
        # annobin not available on OL 10.0
        if [[ $DISTRO_VER == 10* ]]; then
            PREREQ_PACKAGES_ROCM+="perl-devel gcc-plugin-annobin "
        else    
            PREREQ_PACKAGES_ROCM+="perl-devel annobin gcc-plugin-annobin "
        fi
    fi
}

get_kernel_packages_rocky() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Rocky kernel packages...
    
    remove_rocky_kernel_repo

    num_of_packages_available=$($SUDO dnf repoquery --available --queryformat "%{name}-%{version}-%{release}.%{arch}" kernel-headers-$(uname -r) kernel-devel-$(uname -r) kernel-devel-matched-$(uname -r) | wc -l)
    if [ $num_of_packages_available -eq 3 ]; then
        echo "Kernel Packages for $KERNEL_VER are available in the AppStream repositories."
        FOUND_ROCKY_KERNEL_HEADERS_IN_REPO=1
        KERNEL_PACKAGES_VER="-$KERNEL_VER"
    else
        echo -e "${YELLOW}Kernel Packages not available in the AppStream repositories. ${NC}"
    fi
    
    echo Rocky kernel packages...Complete.
}

get_rocky_kernel_pkgs_directly() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo "Downloading Rocky kernel packages directly from vault Appstream and BaseOS (kickstart)..."

    # contains all kernels packages like kernel-headers, kernel-devel, kernel-devel-matched for rocky $DISTRO_VER except for default kernel that comes w/ the OS and latest kernel in latest version of rocky
    vault_appstream_os_url="https://dl.rockylinux.org/vault/rocky/$DISTRO_VER/AppStream/x86_64/os/Packages/k/"
    
    # contain kernel packages like kernel-headers, kernel-devel, kernel-devel-matched for the kernel that comes by default with rocky version $DISTRO_VER
    vault_appstream_kickstart_url="https://dl.rockylinux.org/vault/rocky/$DISTRO_VER/AppStream/x86_64/kickstart/Packages/k/"

    local urls=(
        "$vault_appstream_os_url" 
        "$vault_appstream_kickstart_url"
    )

    local packages=(
        "kernel-headers-$KERNEL_VER.rpm"
        "kernel-devel-$KERNEL_VER.rpm"
        "kernel-devel-matched-$KERNEL_VER.rpm"
    )

    local failed=0
    
    echo --------------------------
    echo "Vault Appstream OS URL.         : $vault_appstream_os_url"
    echo "Vault Appstream Kickstart URL   : $vault_appstream_kickstart_url"
    echo --------------------------

    # Loop through the list of packages and attempt to download each
    echo "Downloading kernel package files here: $(pwd)"
    for package in "${packages[@]}"; do
        fail_count=0
        for base_url in "${urls[@]}"; do
            package_url="${base_url}$package"
            echo "Downloading: $(basename "${package_url}")"
            wget --spider --tries $WGET_RETRY_COUNT "$package_url" &> /dev/null
            if [[ $? -ne 0 ]]; then
                echo -e "${RED}URL $package_url does not exist.${NC}"
                continue
            fi
            wget -q --tries $WGET_RETRY_COUNT "$package_url" -O "$(basename "${package_url}")"
            if [[ $? -ne 0 ]]; then
                echo -e "${YELLOW}Failed to download kernel package: $package_url${NC}"
                fail_count=$((fail_count+1))
                if [ $fail_count -eq 2 ]; then
                    echo -e "${RED}Failed to download kernel package: $package from all URLs${NC}"
                    failed=1
                    break
                fi
            else
                echo -e "${GREEN}Successfully downloaded kernel $package_url${NC}"
                break
            fi
        done
    done

    # If any download failed, return failure
    if [[ $failed -eq 1 ]]; then
        echo -e "${RED}One or more kernel packages failed to download. Exiting.${NC}"
        return 1
    fi

    KERNEL_PACKAGES_VER="-$KERNEL_VER"

    echo Downloading Rocky kernel packages...Complete.
    return 0
}

delete_unused_kernel_packages() {
    local is_kernel_header_exist=
    local kernel_pkgs_to_delete=
    local uek_kernel_pkgs_to_delete=
    local rhck_kernel_pkgs_to_delete=
    local rhck_kernel_list=

    if [ $AMDGPU_INSTALL_DRIVER == "yes" ]; then
        if [ $DISTRO_NAME == "rhel" ] || [ $DISTRO_NAME == "rocky" ] ; then
            is_kernel_header_exist=$(ls | grep kernel-headers-$KERNEL_VER)
            kernel_pkgs_to_delete=$(ls | grep ^kernel- | grep -v "$(uname -r)" | xargs)
            
        elif [ $DISTRO_NAME == "ol" ]; then
            is_kernel_header_exist=$(ls | grep kernel-uek-devel-$KERNEL_VER)
            uek_kernel_pkgs_to_delete=$(ls | grep kernel-uek-devel | grep -v "$(uname -r)" | xargs)
            
            # If multiple RHCK installed on system, then get latest one.
            rhck_kernel=$(rpm -q kernel | uniq | sort | head -1 | sed 's/kernel-//')
            if [[ -n $rhck_kernel ]]; then
                # Delete all RHCK kernel packages if they're not matching rhck_kernel
                rhck_kernel_pkgs_to_delete=$(ls | grep -E "^kernel-headers|^kernel-devel|^kernel-devel-matched|^kernel-modules-core" | grep -Ev "uek|$rhck_kernel" | xargs)
            fi
            
            kernel_pkgs_to_delete="$uek_kernel_pkgs_to_delete $rhck_kernel_pkgs_to_delete" 
        fi

        if [[ -n $is_kernel_header_exist ]]; then
            if [[ -n $kernel_pkgs_to_delete ]]; then
                echo "Deleting unused kernel packages: $kernel_pkgs_to_delete"
                $SUDO rm $kernel_pkgs_to_delete
            fi
        fi
    fi
}

# This function is only called after we've downloaded all packages + deps
# b/c it's downloading kernel packages via wget.
download_extra_kernel_pkgs() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo "Download extra kernel packages if available"

    debugCreate download_extra_kernel_pkgs

    if [ "$DISTRO_NAME" = "rocky" ] && [ $AMDGPU_INSTALL_DRIVER == "yes" ] && [ $FOUND_ROCKY_KERNEL_HEADERS_IN_REPO -eq 0 ]; then
        get_rocky_kernel_pkgs_directly
        if [ $? -eq 1 ]; then
            echo -e "${YELLOW}Rocky kernel Packages not available in the repositories.  Using defaults.${NC}"
            PREREQ_PACKAGES_AMDGPU+="kernel-headers kernel-devel kernel-devel-matched "
        else
            PREREQ_PACKAGES_AMDGPU+="kernel-headers$KERNEL_PACKAGES_VER kernel-devel$KERNEL_PACKAGES_VER kernel-devel-matched$KERNEL_PACKAGES_VER "
            echo "Delete rocky kernel header packages that aren't used for current kernel $(uname -r)"
            delete_unused_kernel_packages
        fi

        if ! grep -q "kernel-headers.* kernel-devel.* kernel-devel-matched.*" <<< "$PREREQ_PACKAGES"; then
            echo "Adding prereq packages amdgpu to to prereq packages list."
            PREREQ_PACKAGES+="$PREREQ_PACKAGES_AMDGPU "
        else
            # PREREQ_PACKAGES_AMDGPU is already appended to PREREQ_PACKAGES
            echo "prereq packages amdgpu is already added to prereq packages list."
        fi
    fi
}

get_installer_package_list_rocky() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Creating packages list for Rocky OS...

    debugCreate get_installer_package_list_rocky

    if [ $AMDGPU_INSTALL_DRIVER == "yes" ]; then
        get_kernel_packages_rocky
        if [ $FOUND_ROCKY_KERNEL_HEADERS_IN_REPO -eq 1 ]; then
            PREREQ_PACKAGES_AMDGPU="kernel-headers$KERNEL_PACKAGES_VER kernel-devel$KERNEL_PACKAGES_VER kernel-devel-matched$KERNEL_PACKAGES_VER "
        fi
    fi
}

get_installer_package_list_el() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Creating packages list for generic EL OS...

    debugCreate get_installer_package_list_el

    if [ $AMDGPU_INSTALL_DRIVER == "yes" ]; then
        kernel_to_check="kernel-headers-$KERNEL_VER"
        add_kernel_if_available "$kernel_to_check"
        PREREQ_PACKAGES_AMDGPU="kernel-headers$KERNEL_PACKAGES_VER kernel-devel$KERNEL_PACKAGES_VER kernel-modules$KERNEL_PACKAGES_VER "
    fi

    if [[ $DISTRO_VER == 8* ]]; then
        echo Adding rhel8 kernel packages
        if [ $AMDGPU_INSTALL_DRIVER == "yes" ]; then
            echo Adding prereq amdgpu packages annobin and gcc-plugin-annobin
            PREREQ_PACKAGES_AMDGPU+="annobin gcc-plugin-annobin "
        fi
    elif [[ $DISTRO_VER == 9* ]]; then    
        if [ $AMDGPU_INSTALL_DRIVER == "yes" ]; then
            echo Adding prereq amdgpu kernel-devel-matched package
            PREREQ_PACKAGES_AMDGPU+="kernel-devel-matched$KERNEL_PACKAGES_VER "
        fi

        if [ $DOWNLOAD_PKG_CONFIG_NUM == $DOWNLOAD_PKG_FULL ]; then
            # workaround for rocm versions 6.3.x so gdm does not get uninstalled
            # when user installs rocm.
            GDM_VER=$(rpm -qa | grep gdm)
            if [ $ROCM_INSTALL == "yes" ] && [[ -n $GDM_VER ]] && [ $ROCM_USE_META = "no" ]; then
                $SUDO dnf list "$GDM_VER" &> /dev/null
                if [ $? -eq 0 ]; then
                    echo "Adding $GDM_VER to pre-req rocm packages for full dep mode"
                    PREREQ_PACKAGES_ROCM+="$GDM_VER "
                fi
            fi
        fi
    elif [[ $DISTRO_VER == 10* ]]; then
        if [ $AMDGPU_INSTALL_DRIVER == "yes" ]; then
            echo Adding prereq amdgpu kernel-devel-matched package
            PREREQ_PACKAGES_AMDGPU+="kernel-devel-matched$KERNEL_PACKAGES_VER "
        fi    
    fi
}

get_installer_package_list() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Creating packages list...

    debugCreate get_installer_package_list

    local DISTRO_VER_MAJ=${DISTRO_VER:0:1}

    # Get the list of rocm packages using amdgpu-install. 
    # Add amdgpu-dkms and kernel headers as needed
    if [ $ROCM_INSTALL == "yes" ]; then
        build_package_list

        # Add required prereq packages for ROCm
        echo "Adding prereq packages for ROCm"
        PREREQ_PACKAGES_ROCM+="python3-setuptools python3-wheel "
    fi

    # set the ROCm usecase
    ROCM_USECASES_PACKAGES=$PACKAGES

    if [ $DISTRO_NAME == "ol" ]; then
        get_installer_package_list_ol
    elif [ $DISTRO_NAME == "rocky" ]; then
        get_installer_package_list_rocky
    else
        get_installer_package_list_el
    fi

    if [[ $DISTRO_VER == 9* ]]; then
        if [ $DOWNLOAD_PKG_CONFIG_NUM == $DOWNLOAD_PKG_FULL ]; then
            echo "Adding extra pre req packages for full dep mode"
            PREREQ_PACKAGES+="glibc-all-langpacks glibc-langpack-en "
        fi
    fi

    if [ $AMDGPU_INSTALL_DRIVER == "yes" ]; then
        echo Adding amdgpu
        AMDGPU_PACKAGES=amdgpu-dkms
    fi

    PREREQ_PACKAGES+="$PREREQ_PACKAGES_AMDGPU $PREREQ_PACKAGES_ROCM"

    # Add any pre-req, amdgpu and extra packages
    PACKAGES+="$AMDGPU_PACKAGES $PREREQ_PACKAGES $EXTRA_PACKAGES"

    # If only extra packages are require - only download those
    if [ $EXTRA_PACKAGES_ONLY == "yes" ]; then
        echo Only Downloading Extra Packages for Installer.
        PACKAGES=$EXTRA_PACKAGES
    fi

    echo ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    echo "PREREQ_PACKAGES        = $PREREQ_PACKAGES"
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
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
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
    exec 3>&1
    errorCheck=$($SUDO dnf --nogpg --assumeno --disablerepo=* --enablerepo=repo-offline --allowerasing install $PACKAGES 2>&1 | tee /dev/fd/3)
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
            delete_unused_kernel_packages
            download_extra_kernel_pkgs
            $SUDO chmod 644 *
        popd

        createrepo ./$CREATE_INSTALLER_PACKAGE_DIR

        # simulate the install again to see if there are any errors
        errorCheck=$($SUDO dnf --nogpg --assumeno --disablerepo=* --enablerepo=repo-offline install $PACKAGES  $missing_packages 2>&1 | tee /dev/fd/3)
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
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

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

            delete_unused_kernel_packages
            download_extra_kernel_pkgs

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

    # Parse ROCM_VERSIONS into major, minor, patch components
    if [[ -n $ROCM_VERSIONS ]]; then
        IFS='.' read -r ROCM_VERSION_MAJOR ROCM_VERSION_MINOR ROCM_VERSION_PATCH <<< "$ROCM_VERSIONS"
        echo "Parsed ROCm version: Major=$ROCM_VERSION_MAJOR, Minor=$ROCM_VERSION_MINOR, Patch=$ROCM_VERSION_PATCH"

        if [[ -z $AMDGPU_VERSION ]]; then
            AMDGPU_VERSION=$ROCM_VERSIONS
            echo "Using default AMDGPU version: $AMDGPU_VERSION (same as ROCm version)"
        fi
    fi


    # Check for a URL config file
    if [[ -n $URL_CONFIG ]]; then
        if [[ -f $URL_CONFIG ]]; then
            echo "Using URL Configuration file   : $URL_CONFIG"
            source $URL_CONFIG

            local distro_ver_mapped=$DISTRO_VER
            if [[ "$DISTRO_VER" == *.0 ]]; then
                distro_ver_mapped="$DISTRO_MAJOR_VER"
            fi

            echo Checking URL for $DISTRO_VER
            if [[ "$AMDGPU_INSTALL_URL" != *"$distro_ver_mapped"* ]]; then
                echo amdgpu-install distro version in URL file does not match.
                exit 1
            fi

            if [[ "$AMDGPU_URL" != *"$distro_ver_mapped"* ]]; then
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

            if [[ "$AMDGPU_URL" != *"$AMDGPU_VERSION"* ]]; then
                echo ROCm version in URL file does not match.
                exit 1
            fi

            echo "AMDGPU_INSTALL_URL = $AMDGPU_INSTALL_URL"
            echo "ROCM_URL           = $ROCM_URL"
            echo "AMDGPU_URL         = $AMDGPU_URL"
        else
            echo -e "${YELLOW}Warning: URL configuration file not found.  Using defaults.${NC}"
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
        echo DOWNLOAD_PKG_CONFIG_NUM=$DOWNLOAD_PKG_CONFIG_NUM >> $INSTALLER_CONFIG_FILE

        echo PREREQ_PACKAGES=\"$PREREQ_PACKAGES\" >> $INSTALLER_CONFIG_FILE

        echo ROCM_INSTALL=$ROCM_INSTALL >> $INSTALLER_CONFIG_FILE
        echo ROCM_VERSIONS=$ROCM_VERSIONS >> $INSTALLER_CONFIG_FILE
        echo ROCM_USECASES=$ROCM_USECASES >> $INSTALLER_CONFIG_FILE
        echo ROCM_USECASES_PACKAGES=\"$ROCM_USECASES_PACKAGES\" >> $INSTALLER_CONFIG_FILE
        echo ROCM_BUILD=$ROCM_BUILD >> $INSTALLER_CONFIG_FILE

        echo EXTRA_PACKAGES=\"$EXTRA_PACKAGES\" >> $INSTALLER_CONFIG_FILE

        echo AMDGPU_INSTALL_DRIVER=$AMDGPU_INSTALL_DRIVER >> $INSTALLER_CONFIG_FILE
        echo AMDGPU_BUILD=$AMDGPU_BUILD >> $INSTALLER_CONFIG_FILE
        echo AMDGPU_PACKAGES=\"$AMDGPU_PACKAGES\" >> $INSTALLER_CONFIG_FILE
        echo AMDGPU_POST_INSTALL_BLACKLIST=$AMDGPU_POST_INSTALL_BLACKLIST >> $INSTALLER_CONFIG_FILE
        echo AMDGPU_POST_INSTALL_START=$AMDGPU_POST_INSTALL_START >> $INSTALLER_CONFIG_FILE
        echo AMDGPU_VERSION=$AMDGPU_VERSION >> $INSTALLER_CONFIG_FILE

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
echo "    ROCM_USE_META = $ROCM_USE_META"
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

if [[ $ROCM_USE_META == "yes" ]]; then
    source ./setup_packages/setup_meta_packages.sh
else
    source ./setup_packages/setup_legacy_packages.sh
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

echo -e "${GREEN}========================${NC}"
echo -e "${GREEN}OFFLINE INSTALL CREATED!${NC}"
echo -e "${GREEN}========================${NC}"

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
echo -e "${GREEN}========================================================================================${NC}"
echo -e "${GREEN}Location: $INSTALLER_INFO : $CREATE_BUILD_PKG_COUNT Packages${NC}"
echo -e "${GREEN}========================================================================================${NC}"

} 2>&1 | $SUDO tee $CREATE_INSTALLER_CURRENT_LOG

echo "Create install log stored in: $CREATE_INSTALLER_CURRENT_LOG"
