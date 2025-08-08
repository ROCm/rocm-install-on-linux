#!/bin/bash


setup_installer_public_repos() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Install Package Type = public : Install amdgpu-install...

    ## Register kernel-mode driver ##
    $SUDO tee /etc/yum.repos.d/amdgpu.repo <<EOF
[amdgpu]
name=amdgpu
baseurl=https://repo.radeon.com/amdgpu/$ROCM_VERSIONS/el/$VERSION_ID/main/x86_64/
enabled=1
priority=50
gpgcheck=1
gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
EOF

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
        $SUDO sed -i "s#https[^ ]*#$AMDGPU_URL#g" "/etc/yum.repos.d/amdgpu.repo"
    fi

    # Update the rocm.repo (if required)
    if [[ -n $ROCM_URL ]]; then
        echo Updating rocm url...

        # Find the URL in the file and replace it
        $SUDO sed -i "s#https[^ ]*#$ROCM_URL#g" "/etc/yum.repos.d/rocm.repo"
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
