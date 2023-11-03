# Upgrade ROCm with the package manager

This section explains how to upgrade the existing AMDGPU driver and ROCm
packages to the latest version using your OS's distributed package manager.

```{note}
Package upgrade is applicable to single-version packages only. If the preference
is to install an updated version of the ROCm along with the currently
installed version, refer to the [](install) page.
```

## Upgrade Steps

### Update the AMDGPU repository

Execute the commands below based on your distribution to point the `amdgpu`
repository to the new release.

::::::{tab-set}
:::::{tab-item} Ubuntu
:sync: ubuntu

::::{tab-set}
:::{tab-item} Ubuntu 20.04
:sync: ubuntu-20.04

```shell
# version
version=5.7


# amdgpu repository for focal
echo "deb [arch=amd64 signed-by=/etc/apt/keyrings/rocm.gpg] https://repo.radeon.com/amdgpu/$version/ubuntu focal main" \
    | sudo tee /etc/apt/sources.list.d/amdgpu.list
sudo apt update
```

:::
:::{tab-item} Ubuntu 22.04
:sync: ubuntu-22.04

```shell
# version
version=5.7


# amdgpu repository for jammy
echo "deb [arch=amd64 signed-by=/etc/apt/keyrings/rocm.gpg] https://repo.radeon.com/amdgpu/$version/ubuntu jammy main" \
    | sudo tee /etc/apt/sources.list.d/amdgpu.list
sudo apt update
```

:::
::::
:::::
:::::{tab-item} Red Hat Enterprise Linux
:sync: RHEL

::::{tab-set}
:::{tab-item} RHEL 8.6
:sync: RHEL-8.6
:sync: RHEL-8

```shell
# version
version=5.7


sudo tee /etc/yum.repos.d/amdgpu.repo <<EOF
[amdgpu]
name=amdgpu
baseurl=https://repo.radeon.com/amdgpu/$version/rhel/8.6/main/x86_64/
enabled=1
priority=50
gpgcheck=1
gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
EOF
sudo yum clean all
```

:::
:::{tab-item} RHEL 8.7
:sync: RHEL-8.7
:sync: RHEL-8

```shell
# version
version=5.7


sudo tee /etc/yum.repos.d/amdgpu.repo <<EOF
[amdgpu]
name=amdgpu
baseurl=https://repo.radeon.com/amdgpu/$version/rhel/8.7/main/x86_64/
enabled=1
priority=50
gpgcheck=1
gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
EOF
sudo yum clean all
```

:::
:::{tab-item} RHEL 8.8
:sync: RHEL-8.8
:sync: RHEL-8

```shell
# version
version=5.7


sudo tee /etc/yum.repos.d/amdgpu.repo <<EOF
[amdgpu]
name=amdgpu
baseurl=https://repo.radeon.com/amdgpu/$version/rhel/8.8/main/x86_64/
enabled=1
priority=50
gpgcheck=1
gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
EOF
sudo yum clean all
```

:::
:::{tab-item} RHEL 9.1
:sync: RHEL-9.1
:sync: RHEL-9

```shell
# version
version=5.7


sudo tee /etc/yum.repos.d/amdgpu.repo <<EOF
[amdgpu]
name=amdgpu
baseurl=https://repo.radeon.com/amdgpu/$version/rhel/9.1/main/x86_64/
enabled=1
priority=50
gpgcheck=1
gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
EOF
sudo yum clean all
```

:::
:::{tab-item} RHEL 9.2
:sync: RHEL-9.2
:sync: RHEL-9

```shell
# version
version=5.7


sudo tee /etc/yum.repos.d/amdgpu.repo <<EOF
[amdgpu]
name=amdgpu
baseurl=https://repo.radeon.com/amdgpu/$version/rhel/9.2/main/x86_64/
enabled=1
priority=50
gpgcheck=1
gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
EOF
sudo yum clean all
```

:::
::::
:::::
:::::{tab-item} SUSE Linux Enterprise Server
:sync: SLES

::::{tab-set}
:::{tab-item} SLES 15.4
:sync: SLES-15.4

```shell
# version
version=5.7


sudo tee /etc/zypp/repos.d/amdgpu.repo <<EOF
[amdgpu]
name=amdgpu
baseurl=https://repo.radeon.com/amdgpu/$version/sle/15.4/main/x86_64
enabled=1
gpgcheck=1
gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
EOF
sudo zypper ref
```

:::
:::{tab-item} SLES 15.5
:sync: SLES-15.5

```shell
# version
version=5.7


sudo tee /etc/zypp/repos.d/amdgpu.repo <<EOF
[amdgpu]
name=amdgpu
baseurl=https://repo.radeon.com/amdgpu/$version/sle/15.5/main/x86_64
enabled=1
gpgcheck=1
gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
EOF
sudo zypper ref
```

:::
::::
:::::
::::::

### Upgrade the kernel-mode driver & reboot

Upgrade the kernel mode driver and reboot the system using the following
commands based on your distribution:

::::{tab-set}
:::{tab-item} Ubuntu
:sync: ubuntu

```shell
sudo apt install amdgpu-dkms
sudo reboot
```

:::
:::{tab-item} Red Hat Enterprise Linux
:sync: RHEL

```shell
sudo yum install amdgpu-dkms
sudo reboot
```

:::
:::{tab-item} SUSE Linux Enterprise Server
:sync: SLES

```shell
sudo zypper --gpg-auto-import-keys install amdgpu-dkms
sudo reboot
```

:::
::::

### Update the ROCm repository

Execute the commands below based on your distribution to point the `rocm`
repository to the new release.

::::::{tab-set}
:::::{tab-item} Ubuntu
:sync: ubuntu

::::{tab-set}
:::{tab-item} Ubuntu 20.04
:sync: ubuntu-20.04

```shell
# version
version=5.7


echo "deb [arch=amd64 signed-by=/etc/apt/keyrings/rocm.gpg] https://repo.radeon.com/rocm/apt/$version focal main" \
    | sudo tee /etc/apt/sources.list.d/rocm.list
echo -e 'Package: *\nPin: release o=repo.radeon.com\nPin-Priority: 600' \
    | sudo tee /etc/apt/preferences.d/rocm-pin-600
sudo apt update
```

:::
:::{tab-item} Ubuntu 22.04
:sync: ubuntu-22.04

```shell
# version
version=5.7


echo "deb [arch=amd64 signed-by=/etc/apt/keyrings/rocm.gpg] https://repo.radeon.com/rocm/apt/$version jammy main" \
    | sudo tee /etc/apt/sources.list.d/rocm.list
echo -e 'Package: *\nPin: release o=repo.radeon.com\nPin-Priority: 600' \
    | sudo tee /etc/apt/preferences.d/rocm-pin-600
sudo apt update
```

:::
::::
:::::
:::::{tab-item} Red Hat Enterprise Linux
:sync: RHEL

::::{tab-set}
:::{tab-item} RHEL 8
:sync: RHEL-8

```shell
# version
version=5.7


sudo tee /etc/yum.repos.d/rocm.repo <<EOF
[ROCm-$ver]
name=ROCm$ver
baseurl=https://repo.radeon.com/rocm/rhel8/$version/main
enabled=1
priority=50
gpgcheck=1
gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
EOF
sudo yum clean all
```

:::
:::{tab-item} RHEL 9
:sync: RHEL-9

```shell
# version
version=5.7


sudo tee /etc/yum.repos.d/rocm.repo <<EOF
[ROCm-$ver]
name=ROCm$ver
baseurl=https://repo.radeon.com/rocm/rhel9/$version/main
enabled=1
priority=50
gpgcheck=1
gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
EOF
sudo yum clean all
```

:::
::::
:::::
:::::{tab-item} SUSE Linux Enterprise Server
:sync: SLES

```shell
# version
version=5.7

sudo tee /etc/zypp/repos.d/rocm.repo <<EOF
[ROCm-$ver]
name=ROCm$ver
name=rocm
baseurl=https://repo.radeon.com/rocm/zyp/$version/main
enabled=1
gpgcheck=1
gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
EOF
sudo zypper ref
```

:::::
::::::

### Upgrade the ROCm packages

Your packages can be upgraded now through their meta-packages, see the following
example based on your distribution:

::::{tab-set}
:::{tab-item} Ubuntu
:sync: ubuntu

```shell
sudo apt install --only-upgrade rocm-hip-sdk
```

:::
:::{tab-item} Red Hat Enterprise Linux
:sync: RHEL

```shell
sudo yum update rocm-hip-sdk
```

:::
:::{tab-item} Suse Linux Enterprise Server
:sync: SLES

```shell
sudo zypper --gpg-auto-import-keys update rocm-hip-sdk
```

:::
::::

## Verification Process

To verify if the upgrade is successful, refer to the
{ref}`post-install-actions-linux` given in the
[Installation](install) section.
