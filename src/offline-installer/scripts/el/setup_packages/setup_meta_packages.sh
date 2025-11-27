#!/bin/bash


setup_repo_priorities() {
    echo Setting up repo priorities...
    
    # Set EPEL to exclude ROCm and HIP packages and lower priority
    if [ -f /etc/yum.repos.d/epel.repo ]; then
        if ! grep -q "excludepkgs=rocm" /etc/yum.repos.d/epel.repo; then
            echo "Excluding ROCm and HIP packages from EPEL..."
            $SUDO sed -i '/\[epel\]/a excludepkgs=rocm* hip*' /etc/yum.repos.d/epel.repo
        fi
        
        if ! grep -q "priority=" /etc/yum.repos.d/epel.repo; then
            echo "Setting EPEL priority to 10..."
            $SUDO sed -i '/excludepkgs=rocm*/a priority=10' /etc/yum.repos.d/epel.repo
        fi
    fi
    
    # Set ROCm repo to higher priority and include ROCm and HIP packages
    if [ -f /etc/yum.repos.d/rocm.repo ]; then
        if ! grep -q "includepkgs=rocm" /etc/yum.repos.d/rocm.repo; then
            echo "Including ROCm and HIP packages in rocm repo..."
            $SUDO sed -i '/priority=1/a includepkgs=rocm* hip*' /etc/yum.repos.d/rocm.repo
        fi
    fi
    
    # Clear cache to apply changes
    $SUDO dnf clean all
    $SUDO dnf makecache > /dev/null 2>&1
    
    echo Setting up repo priorities...Complete.
}


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

    # amdgpu and graphics URL for rhel 8.x and 10.x only contains the major version of the distro for ROCm 7.0.2+
    local baseurl_amdgpu
    local baseurl_graphics
    if ([[ $DISTRO_MAJOR_VER -eq 8 ]] || [[ $DISTRO_MAJOR_VER -eq 10 ]]) && ([[ $ROCM_VERSION_LIBPATCH -ge 70002 ]]); then
        baseurl_amdgpu="https://repo.radeon.com/amdgpu/$amdgpu_version_mapped/el/$DISTRO_MAJOR_VER/main/x86_64/"
        baseurl_graphics="https://repo.radeon.com/graphics/$ROCM_VERSIONS/el/$DISTRO_MAJOR_VER/main/x86_64/"
    else
        baseurl_amdgpu="https://repo.radeon.com/amdgpu/$amdgpu_version_mapped/el/$DISTRO_VER/main/x86_64/"
        baseurl_graphics="https://repo.radeon.com/graphics/$ROCM_VERSIONS/el/$DISTRO_VER/main/x86_64/"
    fi
    
    ## Register kernel-mode driver ##
    $SUDO tee /etc/yum.repos.d/amdgpu.repo <<EOF
[amdgpu]
name=amdgpu
baseurl=$baseurl_amdgpu
enabled=1
priority=50
gpgcheck=1
gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
EOF

    # Register graphics packages for ROCm 7.0.0 and later
    if [[ $ROCM_VERSION_MAJOR -ge 7 ]]; then
        $SUDO tee /etc/yum.repos.d/rocm-graphics.repo <<EOF
[ROCm-$ROCM_VERSIONS-Graphics]
name=ROCm$ROCM_VERSIONS-Graphics
baseurl=$baseurl_graphics
enabled=1
priority=50
gpgcheck=1
gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
EOF
    fi

    ## Register ROCm packages ##
    $SUDO tee /etc/yum.repos.d/rocm.repo <<EOF
[ROCm-$ROCM_VERSIONS]
name=ROCm$ROCM_VERSIONS
baseurl=https://repo.radeon.com/rocm/el${DISTRO_MAJOR_VER}/$ROCM_VERSIONS/main
enabled=1
priority=50
gpgcheck=1
gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
EOF

    $SUDO dnf clean all

    # Update the amdgpu.repo (if required)
    if [[ -n $AMDGPU_URL ]]; then
        echo Updating amdgpu url...

        # Find the URL in the file and replace it
        $SUDO sed -E -i "s#baseurl=(.*)#baseurl=$AMDGPU_URL#" "/etc/yum.repos.d/amdgpu.repo"
    fi

    # Update the rocm.repo (if required)
    if [[ -n $ROCM_URL ]]; then
        echo Updating rocm url...

        # Find the URL in the file and replace it
        $SUDO sed -E -i "s#baseurl=(.*)#baseurl=$ROCM_URL#" "/etc/yum.repos.d/rocm.repo"
    fi

    # Update the rocm-graphics.list (if required)
    # rocm-graphics.list is only used for ROCm 7.0.0 and later
    if [[ $ROCM_VERSION_MAJOR -ge 7 ]]; then
        if [[ -n $GRAPHICS_URL ]]; then
            echo Updating rocm url...

            # Find the URL in the file and replace it
            $SUDO sed -E -i "s#baseurl=(.*)#baseurl=$GRAPHICS_URL#" "/etc/yum.repos.d/rocm-graphics.repo"
        fi
    fi

    # Setup repo priorities if required
    if [[ $DISTRO_MAJOR_VER -ge 10 ]]; then
        setup_repo_priorities
    fi
}

build_package_list() {
    local package_list=()

    # Build out initial package list
    for usecase in ${ROCM_USECASES//,/ }; do
        package_list+="$usecase "
    done

    PACKAGES=${package_list[@]}
}
