#!/bin/bash


setup_installer_public_repos() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Install Package Type = public : Install amdgpu-install...

    local version_id_mapped=$DISTRO_VER
    if [[ "$DISTRO_VER"  == *.0 ]]; then
        version_id_mapped=$DISTRO_MAJOR_VER
    fi

    # amdgpu and graphics URL for rhel 8.x and 10.x only contains the major version of the distro for ROCm 7.0.2+
    local baseurl_amdgpu, baseurl_graphics
    if ([[ $DISTRO_MAJOR_VER -eq 8 ]] || [[ $DISTRO_MAJOR_VER -eq 10 ]]) && ([[ $ROCM_VERSION_MAJOR -ge 7 ]] && [[ $ROCM_VERSION_PATCH -ge 2 ]]); then
        baseurl_amdgpu="https://repo.radeon.com/amdgpu/$AMDGPU_VERSION/el/$DISTRO_MAJOR_VER/main/x86_64/"
        baseurl_graphics="https://repo.radeon.com/graphics/$ROCM_VERSIONS/el/$DISTRO_MAJOR_VER/main/x86_64/"
    else
        baseurl_amdgpu="https://repo.radeon.com/amdgpu/$AMDGPU_VERSION/el/$version_id_mapped/main/x86_64/"
        baseurl_graphics="https://repo.radeon.com/graphics/$ROCM_VERSIONS/el/$VERSION_ID/main/x86_64/"
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
}

build_package_list() {
    local package_list=()

    # Build out initial package list
    for usecase in ${ROCM_USECASES//,/ }; do
        package_list+="$usecase "
    done

    PACKAGES=${package_list[@]}
}
