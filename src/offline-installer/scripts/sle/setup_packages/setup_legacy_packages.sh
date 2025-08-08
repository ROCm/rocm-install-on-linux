#!/bin/bash

CREATE_CONFIG_AMDGPU_INSTALL=amdgpu-install
CREATE_CONFIG_AMDGPU_INSTALL_PARAMS="--dryrun --no-32"


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
    
        AMDGPU_INSTALL_NAME=amdgpu-install-$VER_MAJ.$VER_MIN.$VER_MAJ"0"$VER_MIN"0"$VER_MIN_MIN-1.noarch.rpm
        AMDGPU_INSTALL_URL=https://repo.radeon.com/amdgpu-install/$ROCM_VERSIONS/sle/$DISTRO_VER/$AMDGPU_INSTALL_NAME
    else
        AMDGPU_INSTALL_NAME=$(basename $AMDGPU_INSTALL_URL)
    fi
    
    echo install: $AMDGPU_INSTALL_NAME
        
    # Download and install the amdgpu-install package
    $SUDO zypper --no-gpg-checks install -y $AMDGPU_INSTALL_URL
        
    check_error "Successfully installed amdgpu-install." "Failed amdgpu-install install."

    # Update the amdgpu.repo (if required)
    if [[ -n $AMDGPU_URL ]]; then
        echo Updating amdgpu url...
        
        # Find the URL in the file and replace it
        $SUDO sed -i "s#https[^ ]*#$AMDGPU_URL#g" "/etc/zypp/repos.d/amdgpu.repo"
    fi
    
    # Update the rocm.repo (if required)
    if [[ -n $ROCM_URL ]]; then
        echo Updating rocm url...
        
        # Find the URL in the file and replace it
        $SUDO sed -i "s#https[^ ]*#$ROCM_URL#g" "/etc/zypp/repos.d/rocm.repo"
    fi
    
    # Workaround gpg check issue
    $SUDO zypper modifyrepo -G amdgpu
    $SUDO zypper modifyrepo -G rocm
        
    # Install amdgpu-install for host installer creation
    $SUDO zypper --gpg-auto-import-keys ref
    $SUDO zypper clean
    $SUDO zypper refresh > /dev/null 2>&1

    echo Install amdgpu-install...Complete
        
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Copying amdgpu-install

    # Copy the amdgpu-install script from /usr/bin to the installer
    $SUDO cp /usr/bin/amdgpu-install $CREATE_INSTALLER_DIR
    $SUDO chmod 755 $CREATE_INSTALLER_DIR/amdgpu-install
}

build_package_list() {
    amdgpu_install_out=$($CREATE_CONFIG_AMDGPU_INSTALL $CREATE_CONFIG_AMDGPU_INSTALL_PARAMS --usecase=$ROCM_USECASES --no-dkms)
        
    # Remove text 'zypper install' or 'sudo zypper install' from amdgpu_install_out
    # docker doesn't have 'sudo' output but barel metal does
    PACKAGES=$(echo "${amdgpu_install_out}" | sed -E 's/(sudo )?zypper install//')
    # Replace newline w/ a space as the text 'ln -s[flags] src dst' is preprended by a newline
    PACKAGES=$(tr '\n' ' ' <<< "${PACKAGES}")
    # removes the text ln -[flags] src dst
    PACKAGES=$(echo "${PACKAGES}" | sed -E 's/(sudo)? ln -[a-zA-Z]+ .* .*//')

    PACKAGES+=" "
}