#!/bin/bash


setup_installer_public_repos() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Install Package Type = public : Install amdgpu-install...

    local amdgpu_version_mapped=$AMDGPU_VERSION

    if [[ $ROCM_VERSION_MAJOR -eq 7 ]] ; then
        if [[ $ROCM_VERSION_MINOR -eq 0 ]]; then
            # ROCm 7.0
            amdgpu_version_mapped="30.10"
            # ROCm 7.0.1
            if [[ $ROCM_VERSION_PATCH -eq 1 ]]; then
                amdgpu_version_mapped="30.10.1"
            # ROCm 7.0.2
            elif [[ $ROCM_VERSION_PATCH -eq 2 ]]; then
                amdgpu_version_mapped="30.10.2"
            fi
        elif [[ $ROCM_VERSION_MINOR -eq 1 ]]; then
            # ROCm 7.1
            amdgpu_version_mapped="30.20"

            # ROCm 7.1.1
            if [[ $ROCM_VERSION_PATCH -eq 1 ]]; then
                amdgpu_version_mapped="30.20.1"
            fi
        fi
    fi
    
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
baseurl=https://repo.radeon.com/amdgpu/$amdgpu_version_mapped/sle/$VERSION_ID/main/x86_64/
enabled=1
gpgcheck=1
gpgkey=file:///etc/amdgpu-install/rocm.gpg.key
EOF

    # Register graphics packages for ROCm 7.0.0 and later
    if [[ $ROCM_VERSION_MAJOR -ge 7 ]]; then
        $SUDO tee /etc/zypp/repos.d/rocm-graphics.repo <<EOF
[ROCm-$ROCM_VERSIONS-Graphics]
name=ROCm$ROCM_VERSIONS-Graphics
baseurl=https://repo.radeon.com/graphics/$ROCM_VERSIONS/sle/$VERSION_ID/main/x86_64/
enabled=1
gpgcheck=1
gpgkey=file:///etc/amdgpu-install/rocm.gpg.key
EOF
    fi

    ## Register ROCm packages ##
    $SUDO tee /etc/zypp/repos.d/rocm.repo <<EOF
[ROCm-$ROCM_VERSIONS]
name=ROCm$ROCM_VERSIONS
baseurl=https://repo.radeon.com/rocm/zyp/$ROCM_VERSIONS/main
enabled=1
gpgcheck=1
gpgkey=file:///etc/amdgpu-install/rocm.gpg.key
EOF

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

    # Update the rocm-graphics.list (if required)
    # rocm-graphics.list is only used for ROCm 7.0.0 and later
    if [[ $ROCM_VERSION_MAJOR -ge 7 ]]; then
        if [[ -n $GRAPHICS_URL ]]; then
            echo Updating rocm url...

            # Find the URL in the file and replace it
            $SUDO sed -i "s#https[^ ]*#$GRAPHICS_URL#g" "/etc/zypp/repos.d/rocm-graphics.repo"
        fi
    fi

    $SUDO zypper refresh

    # Workaround gpg check issue
    $SUDO zypper modifyrepo -G amdgpu
    $SUDO zypper modifyrepo -G ROCm-$ROCM_VERSIONS
    if [[ $ROCM_VERSION_MAJOR -ge 7 ]]; then
        $SUDO zypper modifyrepo -G ROCm-$ROCM_VERSIONS-Graphics
    fi
        
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