#!/bin/bash

CREATE_CONFIG_AMDGPU_INSTALL=amdgpu-install
CREATE_CONFIG_AMDGPU_INSTALL_PARAMS="--dryrun --no-32"


setup_installer_public_repos() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Install Package Type = public : Install amdgpu-install...
    
    echo "AMDGPU_VERSION = $AMDGPU_VERSION"
    echo "ROCM_VERSIONS  = $ROCM_VERSIONS"
    
    local amdgpu_install_ver=
    if [[ -n $AMDGPU_VERSION ]]; then
        amdgpu_install_ver=$AMDGPU_VERSION
    elif [[ -n $ROCM_VERSIONS ]]; then
        amdgpu_install_ver=$ROCM_VERSIONS
    else
        print_err "No rocm/amdgpu version for amdgpu-install download."
        exit 1
    fi
    
    if [[ -z $AMDGPU_INSTALL_URL ]]; then
        echo Using default URL for amdgpu-install $amdgpu_install_ver

        local VER_MAJ=${amdgpu_install_ver:0:1}
        local VER_MIN=${amdgpu_install_ver:2:1}
        local VER_MIN_MIN=${amdgpu_install_ver:4:1}

        if [[ -z $VER_MIN_MIN ]]; then
            VER_MIN_MIN=0
        fi

        if [[ $DISTRO_VER == 8* ]]; then
            local RHEL_BASE_VER=el8
        else
            local RHEL_BASE_VER=el9
        fi

        AMDGPU_INSTALL_NAME=amdgpu-install-$VER_MAJ.$VER_MIN.$VER_MAJ"0"$VER_MIN"0"$VER_MIN_MIN-1.$RHEL_BASE_VER.noarch.rpm
        if [ $DISTRO_NAME = "rhel" ]; then
            AMDGPU_INSTALL_URL=https://repo.radeon.com/amdgpu-install/$amdgpu_install_ver/rhel/$DISTRO_VER/$AMDGPU_INSTALL_NAME
        else
            AMDGPU_INSTALL_URL=https://repo.radeon.com/amdgpu-install/$amdgpu_install_ver/el/$DISTRO_VER/$AMDGPU_INSTALL_NAME
        fi
    else
        AMDGPU_INSTALL_NAME=$(basename $AMDGPU_INSTALL_URL)
    fi

    echo install: $AMDGPU_INSTALL_NAME

    # Download the amdgpu-install package and associated dependencies
    wget --tries $WGET_RETRY_COUNT $AMDGPU_INSTALL_URL

    check_error "Successfully downloaded amdgpu-install." "Failed amdgpu-install download."

    $SUDO chmod 644 ./$AMDGPU_INSTALL_NAME

    $SUDO dnf download --downloadonly --resolve --downloaddir="./$CREATE_INSTALLER_PACKAGE_DIR" ./$AMDGPU_INSTALL_NAME

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

build_package_list() {
    amdgpu_install_out=$($CREATE_CONFIG_AMDGPU_INSTALL $CREATE_CONFIG_AMDGPU_INSTALL_PARAMS --usecase=$ROCM_USECASES --no-dkms)

    # Remove text 'dnf install' or 'sudo dnf install' from amdgpu_install_out
    # docker doesn't have 'sudo' output but barel metal does
    PACKAGES=$(echo "${amdgpu_install_out}" | sed -E 's/(sudo )?dnf install//')
    PACKAGES=${PACKAGES%%kernel*}
    if [ -z "$SUDO" ]; then
        PACKAGES=${PACKAGES%%ln*}
    else
        PACKAGES=${PACKAGES%%sudo ln*}
    fi

    # Remove trailing newline
    PACKAGES=$(tr -d '\n' <<< "$PACKAGES")

    PACKAGES+=" "
}
