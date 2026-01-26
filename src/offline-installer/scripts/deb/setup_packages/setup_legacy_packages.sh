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

        AMDGPU_INSTALL_NAME=amdgpu-install_$VER_MAJ.$VER_MIN.$VER_MAJ"0"$VER_MIN"0"$VER_MIN_MIN-1_all.deb
        AMDGPU_INSTALL_URL=https://repo.radeon.com/amdgpu-install/$amdgpu_install_ver/ubuntu/$DISTRO_CODENAME/$AMDGPU_INSTALL_NAME
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

build_package_list() {
    amdgpu_install_out=$($CREATE_CONFIG_AMDGPU_INSTALL $CREATE_CONFIG_AMDGPU_INSTALL_PARAMS --usecase=$ROCM_USECASES --no-dkms)

    # From amdgpu_install_out, extract the apt-get install line
    declare apt_get_install_line_regex='(apt-get|apt) install.*$'
    declare apt_get_install_line="$(echo "${amdgpu_install_out}" | grep --extended-regexp "${apt_get_install_line_regex}")"

    # Example values for apt_get_install_line
    # Example 1: sudo apt-get install amdgpu-dkms linux-headers-6.5.0-28-generic
    # Example 2: apt-get install amdgpu-dkms linux-headers-6.5.0-28-generic"
    echo "${apt_get_install_line}" | grep --extended-regexp "apt-get" > /dev/null 2> /dev/null
    # Remove sudo apt-get install from the start, getting only the arguments (packages)
    PACKAGES="$(echo "${apt_get_install_line}" | sed 's/.*apt-get install//')"
    PACKAGES="${PACKAGES/linux-headers*/}"

    PACKAGES+=" "
}
