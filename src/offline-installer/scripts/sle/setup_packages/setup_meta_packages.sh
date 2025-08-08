#!/bin/bash


setup_installer_public_repos() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Install Package Type = public : Install amdgpu-install...
        
    ## Package signing key
    # Make the directory if it doesn't exist yet.    
    $SUDO mkdir --parents --mode=0755 /etc/amdgpu-install
    # Download key into the directory
    $SUDO wget -O /etc/amdgpu-install/rocm.gpg.key https://repo.radeon.com/rocm/rocm.gpg.key
    # Import key into the RPM database
    $SUDO rpm --import /etc/amdgpu-install/rocm.gpg.key

    ## Register kernel-mode driver ##
    $SUDO tee /etc/zypp/repos.d/amdgpu.repo <<EOF
[amdgpu]
name=amdgpu
baseurl=https://repo.radeon.com/amdgpu/$ROCM_VERSIONS/sle/$VERSION_ID/main/x86_64/
enabled=1
gpgcheck=1
gpgkey=file:///etc/amdgpu-install/rocm.gpg.key
EOF

    ## Register ROCm packages ##
    $SUDO tee /etc/zypp/repos.d/rocm.repo <<EOF
[ROCm-$ROCM_VERSIONS]
name=ROCm$ROCM_VERSIONS
baseurl=https://repo.radeon.com/rocm/zyp/$ROCM_VERSIONS/main
enabled=1
gpgcheck=1
gpgkey=file:///etc/amdgpu-install/rocm.gpg.key
EOF

    $SUDO zypper refresh

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
}

build_package_list() {
    local package_list=()

    # Build out initial package list
    for usecase in ${ROCM_USECASES//,/ }; do
        package_list+="$usecase "
    done

    PACKAGES=${package_list[@]}
}