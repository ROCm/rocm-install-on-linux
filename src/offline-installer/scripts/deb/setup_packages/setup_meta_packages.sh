#!/bin/bash
setup_installer_public_repos() {
    echo =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    echo Install Package Type = public : Setting up public repos ...

    ## Package signing key
    # Make the directory if it doesn't exist yet.
    # This location is recommended by the distribution maintainers.
    $SUDO mkdir --parents --mode=0755 /etc/apt/keyrings

    # Download the key, convert the signing-key to a full
    # keyring required by apt and store in the keyring directory
    wget https://repo.radeon.com/rocm/rocm.gpg.key -O - | \
        gpg --dearmor | $SUDO tee /etc/apt/keyrings/rocm.gpg > /dev/null
    $SUDO chmod 644 /etc/apt/keyrings/rocm.gpg

    ## Register kernel-mode driver ##
    echo "deb [arch=amd64 signed-by=/etc/apt/keyrings/rocm.gpg] https://repo.radeon.com/amdgpu/$ROCM_VERSIONS/ubuntu $DISTRO_CODENAME main" \
        | $SUDO tee /etc/apt/sources.list.d/amdgpu.list

    ## Register ROCm packages ##
    echo "deb [arch=amd64,i386 signed-by=/etc/apt/keyrings/rocm.gpg] https://repo.radeon.com/rocm/apt/$ROCM_VERSIONS $DISTRO_CODENAME main" \
        | $SUDO tee /etc/apt/sources.list.d/rocm.list
    echo -e 'Package: *\nPin: release o=repo.radeon.com\nPin-Priority: 600' \
        | $SUDO tee /etc/apt/preferences.d/rocm-pin-600

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

    $SUDO apt update
}

build_package_list() {
    local package_list=()

    # Build out initial package list
    for usecase in ${ROCM_USECASES//,/ }; do
        package_list+="$usecase "
    done

    PACKAGES=${package_list[@]}
}