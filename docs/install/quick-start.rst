.. meta::
  :description: Quick start install guide
  :keywords: ROCm installation, AMD, ROCm, Package manager, AMDGPU

.. _rocm-install-quick:

******************************
Quick start installation guide
******************************

.. note::

    See `Use ROCm on Radeon and Ryzen <https://rocm.docs.amd.com/projects/radeon-ryzen/en/latest/index.html>`_ for instructions on installing ROCm on systems with AMD Radeon GPUs or Ryzen APUs for graphics workloads.

Before proceeding, ensure your kernel meets the :ref:`ROCm system requirements <supported_distributions>`. Then select your operating system and version, and run the provided commands to install the AMD GPU and ROCm. 

For detailed guidance, see `Installation via native package manager <https://instinct.docs.amd.com/projects/amdgpu-docs/en/latest/install/package-manager-index.html>`_ for AMD GPU installation and :doc:`Detailed install <detailed-install>` for ROCm installation.

Installing
==========

Register repositories
---------------------

.. datatemplate:nodata::

    .. tab-set::

        .. tab-item:: Ubuntu
            :sync: ubuntu-tab

            .. tab-set::

                {% for (os_version, os_release) in config.html_context['ubuntu_version_numbers'] %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       wget https://repo.radeon.com/amdgpu-install/|amdgpu_version|/ubuntu/{{ os_release }}/amdgpu-install_|amdgpu_install_version|_all.deb
                       sudo apt install ./amdgpu-install_|amdgpu_install_version|_all.deb
                       sudo apt update
                {% endfor %}
        
        .. tab-item:: Debian
            :sync: debian-tab

            .. tab-set::

                {% for (os_version, os_release) in config.html_context['debian_version_numbers'] %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       wget https://repo.radeon.com/amdgpu-install/|amdgpu_version|/ubuntu/{{ os_release }}/amdgpu-install_|amdgpu_install_version|_all.deb
                       sudo apt install ./amdgpu-install_|amdgpu_install_version|_all.deb
                       sudo apt update

                {% endfor %}

        .. tab-item:: Red Hat Enterprise Linux
            :sync: rhel-tab

            .. tab-set::

                {% for os_version in config.html_context['rhel_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   Before installing ROCm on RHEL, :ref:`register and update your Enterprise Linux <register-enterprise-linux>`.

                   .. code-block:: bash
                       :substitutions:

                       sudo dnf install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/rhel/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.el{{ os_major }}.noarch.rpm
                       sudo dnf clean all

                {% endfor %}

        .. tab-item:: Oracle Linux
            :sync: ol-tab

            .. tab-set::

                {% for os_version in config.html_context['ol_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   Before installing ROCm on OL, :ref:`update your Enterprise Linux <update-enterprise-linux>`.

                   .. code-block:: bash
                       :substitutions:

                       sudo dnf install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/el/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.el{{ os_major }}.noarch.rpm
                       sudo dnf clean all

                {% endfor %}

        .. tab-item:: SUSE Linux Enterprise Server
            :sync: sle-tab

            .. tab-set::

                {% for os_version in config.html_context['sles_version_numbers'] %}
                .. tab-item:: {{ os_version }}

                   Before installing ROCm on SLES, :ref:`register and update your Enterprise Linux <register-enterprise-linux>`.

                   .. code-block:: bash
                       :substitutions:

                       sudo SUSEConnect -p sle-module-desktop-applications/{{ os_version }}/x86_64
                       sudo SUSEConnect -p sle-module-development-tools/{{ os_version }}/x86_64
                       sudo SUSEConnect -p PackageHub/{{ os_version }}/x86_64
                       sudo zypper install zypper
                       sudo zypper --no-gpg-checks install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/sle/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.noarch.rpm
                       sudo zypper --gpg-auto-import-keys refresh

                {% endfor %}

        .. tab-item:: Azure Linux
            :sync: azl-tab

            .. tab-set::

                {% for os_version in config.html_context['azl_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo curl -o /etc/yum.repos.d/azurelinux-extended.repo https://packages.microsoft.com/azurelinux/{{ os_version }}/prod/extended/x86_64/config.repo
                       sudo tee /etc/yum.repos.d/rocm.repo <<EOF
                       [ROCm-|amdgpu_version|]
                       name=ROCm|amdgpu_version|
                       baseurl=https://repo.radeon.com/rocm/azurelinux{{ os_major }}/|amdgpu_version|/main/
                       enabled=1
                       gpgcheck=1
                       gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
                       EOF
                       sudo tdnf install azurelinux-repos-amd
                       sudo tdnf repolist --refresh

                {% endfor %}

        .. tab-item:: Rocky Linux
            :sync: rl-tab

            .. tab-set::

                {% for os_version in config.html_context['rl_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo dnf install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/el/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.el{{ os_major }}.noarch.rpm
                       sudo dnf clean all

                {% endfor %}

Install kernel driver
---------------------

.. datatemplate:nodata::

    .. tab-set::

        .. tab-item:: Ubuntu
            :sync: ubuntu-tab

            .. tab-set::

                {% for (os_version, os_release) in config.html_context['ubuntu_version_numbers'] %}
                .. tab-item:: {{ os_version }}

                   .. caution::

                      Remove any AMD GPU driver from a previous installation by following the uninstall steps in :ref:`Uninstall kernel driver <uninstall-kernel-driver>`.

                   .. code-block:: bash
                       :substitutions:

                       sudo apt install "linux-headers-$(uname -r)" "linux-modules-extra-$(uname -r)"
                       sudo apt install amdgpu-dkms

                {% endfor %}
        
        .. tab-item:: Debian
            :sync: debian-tab

            .. tab-set::

                {% for (os_version, os_release) in config.html_context['debian_version_numbers'] %}
                .. tab-item:: {{ os_version }}

                   .. caution::

                      Remove any AMD GPU driver from a previous installation by following uninstallation steps in :ref:`Uninstall kernel driver <uninstall-kernel-driver>`.

                   .. code-block:: bash
                       :substitutions:

                       sudo apt install "linux-headers-$(uname -r)"
                       sudo apt install amdgpu-dkms

                {% endfor %}

        .. tab-item:: Red Hat Enterprise Linux
            :sync: rhel-tab

            .. tab-set::

                {% for os_version in config.html_context['rhel_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   .. caution::

                      Remove any AMD GPU driver from a previous installation by following uninstallation steps in :ref:`Uninstall kernel driver <uninstall-kernel-driver>`.
                   
                   .. code-block:: bash
                       :substitutions:

                       {% if os_major == '8' -%}
                       sudo dnf install "kernel-headers-$(uname -r)" "kernel-devel-$(uname -r)"
                       {%- else -%}
                       sudo dnf install "kernel-headers-$(uname -r)" "kernel-devel-$(uname -r)" "kernel-devel-matched-$(uname -r)"
                       {%- endif %}
                       sudo dnf install amdgpu-dkms

                {% endfor %}

        .. tab-item:: Oracle Linux
            :sync: ol-tab

            .. tab-set::

                {% for os_version in config.html_context['ol_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   .. caution::

                      Remove any AMD GPU driver from a previous installation by following uninstallation steps in :ref:`Uninstall kernel driver <uninstall-kernel-driver>`.

                   .. code-block:: bash
                       :substitutions:

                       sudo dnf install "kernel-uek-devel-$(uname -r)"
                       sudo dnf install amdgpu-dkms

                {% endfor %}

        .. tab-item:: SUSE Linux Enterprise Server
            :sync: sle-tab

            .. tab-set::

                {% for os_version in config.html_context['sles_version_numbers'] %}
                .. tab-item:: {{ os_version }}

                   .. caution::

                      Remove any AMD GPU driver from a previous installation by following uninstallation steps in :ref:`Uninstall kernel driver <uninstall-kernel-driver>`.

                   .. code-block:: bash
                       :substitutions:

                       sudo zypper install kernel-default-devel
                       sudo zypper install amdgpu-dkms

                {% endfor %}

        .. tab-item:: Azure Linux
            :sync: azl-tab

            .. tab-set::

                {% for os_version in config.html_context['azl_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo tdnf install "kernel-headers-$(uname -r)" "kernel-devel-$(uname -r)"
                       sudo tdnf install amdgpu

                   .. note::
                
                       For Azure Linux, the latest amdgpu version supported is from the ROCm 6.2.2 release.

                {% endfor %}

        .. tab-item:: Rocky Linux
            :sync: rl-tab

            .. tab-set::

                {% for os_version in config.html_context['rl_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   .. caution::

                      Remove any AMD GPU driver from a previous installation by following uninstallation steps in :ref:`Uninstall kernel driver <uninstall-kernel-driver>`.

                   .. code-block:: bash
                       :substitutions:

                       sudo dnf install "kernel-headers" "kernel-devel" "kernel-devel-matched"
                       sudo dnf install amdgpu-dkms

                {% endfor %}

.. important::

    To apply all settings, reboot your system.

Install ROCm
------------

.. datatemplate:nodata::

    .. tab-set::

        .. tab-item:: Ubuntu
            :sync: ubuntu-tab

            .. tab-set::

                {% for (os_version, os_release) in config.html_context['ubuntu_version_numbers'] %}
                .. tab-item:: {{ os_version }}
                   :sync: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo apt install python3-setuptools python3-wheel
                       sudo usermod -a -G render,video $LOGNAME # Add the current user to the render and video groups
                       sudo apt install rocm
                {% endfor %}
        
        .. tab-item:: Debian
            :sync: debian-tab

            .. tab-set::

                {% for (os_version, os_release) in config.html_context['debian_version_numbers'] %}
                .. tab-item:: {{ os_version }}
                   :sync: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo apt install python3-setuptools python3-wheel
                       sudo usermod -a -G render,video $LOGNAME # Add the current user to the render and video groups
                       sudo apt install rocm

                {% endfor %}

        .. tab-item:: Red Hat Enterprise Linux
            :sync: rhel-tab

            .. tab-set::

                {% for os_version in config.html_context['rhel_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}
                   :sync: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-{{ os_major }}.noarch.rpm
                       sudo rpm -ivh epel-release-latest-{{ os_major }}.noarch.rpm
                       sudo dnf config-manager --enable codeready-builder-for-rhel-{{ os_major }}-x86_64-rpms
                       sudo dnf install python3-setuptools python3-wheel
                       sudo usermod -a -G render,video $LOGNAME # Add the current user to the render and video groups
                       sudo dnf install rocm

                {% endfor %}

        .. tab-item:: Oracle Linux
            :sync: ol-tab

            .. tab-set::

                {% for os_version in config.html_context['ol_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}
                   :sync: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-{{ os_major }}.noarch.rpm
                       sudo rpm -ivh epel-release-latest-{{ os_major }}.noarch.rpm
                       sudo crb enable
                       sudo dnf install python3-setuptools python3-wheel
                       sudo usermod -a -G render,video $LOGNAME # Add the current user to the render and video groups
                       sudo dnf install rocm

                {% endfor %}

        .. tab-item:: SUSE Linux Enterprise Server
            :sync: sle-tab

            .. tab-set::

                {% for os_version in config.html_context['sles_version_numbers'] %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo zypper addrepo https://download.opensuse.org/repositories/science/SLE_15_SP5/science.repo
                       sudo zypper install python3-setuptools python3-wheel
                       sudo usermod -a -G render,video $LOGNAME # Add the current user to the render and video groups
                       sudo zypper install rocm

                {% endfor %}

        .. tab-item:: Azure Linux
            :sync: azl-tab

            .. tab-set::

                {% for os_version in config.html_context['azl_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo tdnf install dnf-plugin-config-manager
                       sudo tdnf install python3-setuptools python3-wheel
                       sudo usermod -a -G render,video $LOGNAME # Add the current user to the render and video groups
                       sudo tdnf install rocm
                       sudo tdnf clean all

                {% endfor %}

        .. tab-item:: Rocky Linux
            :sync: rl-tab

            .. tab-set::

                {% for os_version in config.html_context['rl_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-{{ os_major }}.noarch.rpm
                       sudo rpm -ivh epel-release-latest-{{ os_major }}.noarch.rpm
                       sudo dnf install dnf-plugin-config-manager
                       sudo crb enable
                       sudo dnf install python3-setuptools python3-wheel
                       sudo usermod -a -G render,video $LOGNAME # Add the current user to the render and video groups
                       sudo dnf install rocm

                {% endfor %}

.. important::

    To apply all settings, reboot your system.

.. note::

    Quick Start enables GPU access for the current user only. To grant GPU access to all users, see :ref:`Configuring permissions for GPU access <group_permissions>`.

After completing the installation, review the :doc:`post-install`. If you have issues with your installation, see :doc:`Troubleshooting <../reference/install-faq>`.

Uninstalling
============

Uninstall ROCm
--------------

.. datatemplate:nodata::

    .. tab-set::

        .. tab-item:: Ubuntu
            :sync: ubuntu-tab

            .. tab-set::

                {% for (os_version, os_release) in config.html_context['ubuntu_version_numbers'] %}
                .. tab-item:: {{ os_version }}
                   :sync: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo apt autoremove rocm
                       sudo apt autoremove rocm-core

                {% endfor %}
        
        .. tab-item:: Debian
            :sync: debian-tab

            .. tab-set::

                {% for (os_version, os_release) in config.html_context['debian_version_numbers'] %}
                .. tab-item:: {{ os_version }}
                   :sync: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo apt autoremove rocm
                       sudo apt autoremove rocm-core

                {% endfor %}

        .. tab-item:: Red Hat Enterprise Linux
            :sync: rhel-tab

            .. tab-set::

                {% for os_version in config.html_context['rhel_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}
                   :sync: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo dnf remove rocm
                       sudo dnf remove rocm-core amdgpu-core

                {% endfor %}

        .. tab-item:: Oracle Linux
            :sync: ol-tab

            .. tab-set::

                {% for os_version in config.html_context['ol_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}
                   :sync: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo dnf remove rocm
                       sudo dnf remove rocm-core amdgpu-core

                {% endfor %}

        .. tab-item:: SUSE Linux Enterprise Server
            :sync: sle-tab

            .. tab-set::

                {% for os_version in config.html_context['sles_version_numbers'] %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo zypper remove rocm
                       sudo zypper remove rocm-core amdgpu-core

                {% endfor %}

        .. tab-item:: Azure Linux
            :sync: azl-tab

            .. tab-set::

                {% for os_version in config.html_context['azl_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo tdnf remove rocm
                       sudo tdnf remove rocm-core

                {% endfor %}

        .. tab-item:: Rocky Linux
            :sync: rl-tab

            .. tab-set::

                {% for os_version in config.html_context['rl_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo dnf remove rocm
                       sudo dnf remove rocm-core amdgpu-core

                {% endfor %}

.. _uninstall-kernel-driver:

Uninstall kernel driver
-----------------------

.. datatemplate:nodata::

    .. tab-set::

        .. tab-item:: Ubuntu
            :sync: ubuntu-tab

            .. tab-set::

                {% for (os_version, os_release) in config.html_context['ubuntu_version_numbers'] %}
                .. tab-item:: {{ os_version }}
                   :sync: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo apt autoremove amdgpu-dkms

                {% endfor %}
        
        .. tab-item:: Debian
            :sync: debian-tab

            .. tab-set::

                {% for (os_version, os_release) in config.html_context['debian_version_numbers'] %}
                .. tab-item:: {{ os_version }}
                   :sync: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo apt autoremove amdgpu-dkms

                {% endfor %}

        .. tab-item:: Red Hat Enterprise Linux
            :sync: rhel-tab

            .. tab-set::

                {% for os_version in config.html_context['rhel_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}
                   :sync: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo dnf remove amdgpu-dkms

                {% endfor %}

        .. tab-item:: Oracle Linux
            :sync: ol-tab

            .. tab-set::

                {% for os_version in config.html_context['ol_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}
                   :sync: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo dnf remove amdgpu-dkms

                {% endfor %}

        .. tab-item:: SUSE Linux Enterprise Server
            :sync: sle-tab

            .. tab-set::

                {% for os_version in config.html_context['sles_version_numbers'] %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo zypper remove amdgpu-dkms amdgpu-dkms-firmware

                {% endfor %}

        .. tab-item:: Azure Linux
            :sync: azl-tab

            .. tab-set::

                {% for os_version in config.html_context['azl_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo tdnf remove amdgpu amdgpu-firmware kernel-drivers-gpu

                {% endfor %}


        .. tab-item:: Rocky Linux
            :sync: rl-tab

            .. tab-set::

                {% for os_version in config.html_context['rl_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo dnf remove amdgpu-dkms

                {% endfor %}

.. important::

    To apply all settings, reboot your system.

Remove repositories
-------------------

.. datatemplate:nodata::

    .. tab-set::

        .. tab-item:: Ubuntu
            :sync: ubuntu-tab

            .. tab-set::

                {% for (os_version, os_release) in config.html_context['ubuntu_version_numbers'] %}
                .. tab-item:: {{ os_version }}
                   :sync: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                        sudo apt purge amdgpu-install
                        sudo apt autoremove

                        # Clear the cache and clean the system
                        sudo rm -rf /var/cache/apt/*
                        sudo apt clean all
                        sudo apt update

                {% endfor %}
        
        .. tab-item:: Debian
            :sync: debian-tab

            .. tab-set::

                {% for (os_version, os_release) in config.html_context['debian_version_numbers'] %}
                .. tab-item:: {{ os_version }}
                   :sync: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                        sudo apt purge amdgpu-install
                        sudo apt autoremove

                        # Clear the cache and clean the system
                        sudo rm -rf /var/cache/apt/*
                        sudo apt clean all
                        sudo apt update

                {% endfor %}

        .. tab-item:: Red Hat Enterprise Linux
            :sync: rhel-tab

            .. tab-set::

                {% for os_version in config.html_context['rhel_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}
                   :sync: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                        sudo dnf remove amdgpu-install

                        # Clear the cache and clean the system
                        sudo rm -rf /var/cache/dnf
                        sudo dnf clean all

                {% endfor %}

        .. tab-item:: Oracle Linux
            :sync: ol-tab

            .. tab-set::

                {% for os_version in config.html_context['ol_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}
                   :sync: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                        sudo dnf remove amdgpu-install

                        # Clear the cache and clean the system
                        sudo rm -rf /var/cache/dnf
                        sudo dnf clean all

                {% endfor %}

        .. tab-item:: SUSE Linux Enterprise Server
            :sync: sle-tab

            .. tab-set::

                {% for os_version in config.html_context['sles_version_numbers'] %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                        sudo zypper remove amdgpu-install

                        # Clear the cache and clean the system
                        sudo zypper clean --all
                        sudo zypper refresh

                {% endfor %}

        .. tab-item:: Azure Linux
            :sync: azl-tab

            .. tab-set::

                {% for os_version in config.html_context['azl_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                        sudo rm /etc/yum.repos.d/rocm.repo*
                        sudo tdnf remove azurelinux-repos-amd

                        # Clear the cache and clean the system
                        sudo rm -rf /var/cache/tdnf
                        sudo tdnf clean all

                {% endfor %}

        .. tab-item:: Rocky Linux
            :sync: rl-tab

            .. tab-set::

                {% for os_version in config.html_context['rl_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                        sudo dnf remove amdgpu-install

                        # Clear the cache and clean the system
                        sudo rm -rf /var/cache/dnf
                        sudo dnf clean all

                {% endfor %}