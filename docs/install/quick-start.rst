.. meta::
  :description: Quick start install guide
  :keywords: ROCm installation, AMD, ROCm, Package manager, AMDGPU

.. _rocm-install-quick:

******************************
Quick start installation guide
******************************

This topic provides basic installation instructions for ROCm on Linux using your distribution’s native package manager. Before you begin, you should confirm your :ref:`kernel version <verify_kernel_version>` matches the :ref:`ROCm system requirements <supported_distributions>`.  

Once you do, review your required installation instructions by selecting your operating system and version, and then run the provided commands in your terminal. The commands include the installation of the prerequisites, along with installing ROCm.

For more in-depth installation instructions, refer to :ref:`detailed-install-overview`.

.. note::

    If you’re using ROCm with AMD Radeon or Radeon Pro GPUs for graphics workloads, see the `Use ROCm on Radeon GPU <https://rocm.docs.amd.com/projects/radeon/en/latest/docs/install/native_linux/install-radeon.html>`_ documentation for installation instructions .

ROCm installation
=================================================

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
                       sudo apt install python3-setuptools python3-wheel
                       sudo usermod -a -G render,video $LOGNAME # Add the current user to the render and video groups
                       sudo apt install rocm
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
                       sudo apt install -y python3-setuptools python3-wheel
                       sudo usermod -a -G render,video $LOGNAME # Add the current user to the render and video groups
                       sudo apt install rocm

                {% endfor %}

        .. tab-item:: Red Hat Enterprise Linux
            :sync: rhel-tab

            .. tab-set::

                {% for os_version in config.html_context['rhel_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   Before installing ROCm on RHEL, :ref:`register your Enterprise Linux and update the OS installation <register-enterprise-linux>`.

                   .. code-block:: bash
                       :substitutions:

                       sudo dnf install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/rhel/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.el{{ os_major }}.noarch.rpm
                       sudo dnf clean all
                       wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-{{ os_major }}.noarch.rpm
                       sudo rpm -ivh epel-release-latest-{{ os_major }}.noarch.rpm
                       sudo dnf install dnf-plugin-config-manager
                       sudo crb enable
                       sudo dnf install python3-setuptools python3-wheel
                       sudo usermod -a -G render,video $LOGNAME # Add the current user to the render and video groups
                       sudo dnf install rocm

                {% endfor %}

        .. tab-item:: Oracle Linux
            :sync: ol-tab

            .. tab-set::

                {% for os_version in config.html_context['ol_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_major }}

                   Before installing ROCm on OL, :ref:`update the OS installation <update-enterprise-linux>`.

                   .. code-block:: bash
                       :substitutions:

                       sudo dnf install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/el/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.el{{ os_major }}.noarch.rpm
                       sudo dnf clean all
                       wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-{{ os_major }}.noarch.rpm
                       sudo rpm -ivh epel-release-latest-{{ os_major }}.noarch.rpm
                       sudo dnf install dnf-plugin-config-manager
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

                   Before installing ROCm on SLES, :ref:`register your Enterprise Linux update the OS installation <register-enterprise-linux>`.

                   .. code-block:: bash
                       :substitutions:

                       sudo SUSEConnect -p sle-module-desktop-applications/{{ os_version }}/x86_64
                       sudo SUSEConnect -p sle-module-development-tools/{{ os_version }}/x86_64
                       sudo SUSEConnect -p PackageHub/{{ os_version }}/x86_64
                       sudo zypper install zypper
                       sudo zypper --no-gpg-checks install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/sle/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.noarch.rpm
                       sudo zypper --gpg-auto-import-keys refresh
                       sudo zypper addrepo https://download.opensuse.org/repositories/devel:languages:perl/{{ os_version}}/devel:languages:perl.repo
                       sudo zypper addrepo https://download.opensuse.org/repositories/Education/{{ os_version }}/Education.repo
                       sudo zypper addrepo https://download.opensuse.org/repositories/science/SLE_15_SP5/science.repo
                       sudo zypper --gpg-auto-import-keys refresh
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
                       sudo curl -o /etc/yum.repos.d/azurelinux-extended.repo https://packages.microsoft.com/azurelinux/{{ os_version }}/prod/extended/x86_64/config.repo
                       sudo tdnf install python3-setuptools python3-wheel
                       sudo usermod -a -G render,video $LOGNAME # Add the current user to the render and video groups
                       sudo tee --append /etc/yum.repos.d/rocm.repo <<EOF
                       [ROCm-|amdgpu_version|]
                       name=ROCm|amdgpu_version|
                       baseurl=https://repo.radeon.com/rocm/azurelinux{{ os_major }}/|amdgpu_version|/main/
                       enabled=1
                       gpgcheck=1
                       gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
                       EOF
                       sudo tdnf install rocm
                       sudo tdnf clean all

                {% endfor %}

AMDGPU driver installation
=================================================

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
                       sudo apt install "linux-headers-$(uname -r)" "linux-modules-extra-$(uname -r)"
                       sudo apt install amdgpu-dkms

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
                       sudo apt install "linux-headers-$(uname -r)"
                       sudo apt install amdgpu-dkms

                {% endfor %}

        .. tab-item:: Red Hat Enterprise Linux
            :sync: rhel-tab

            .. tab-set::

                {% for os_version in config.html_context['rhel_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   Before installing AMDGPU driver on RHEL, :ref:`register your Enterprise Linux and update the OS installation <register-enterprise-linux>`.

                   .. code-block:: bash
                       :substitutions:

                       sudo dnf install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/rhel/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.el{{ os_major }}.noarch.rpm
                       sudo dnf clean all
                       {% if os_major == '9' -%}
                       sudo dnf install "kernel-headers-$(uname -r)" "kernel-devel-$(uname -r)" "kernel-devel-matched-$(uname -r)"
                       {%- else -%}
                       sudo dnf install "kernel-headers-$(uname -r)" "kernel-devel-$(uname -r)"
                       {%- endif %}
                       sudo dnf install amdgpu-dkms

                {% endfor %}

        .. tab-item:: Oracle Linux
            :sync: ol-tab

            .. tab-set::

                {% for os_version in config.html_context['ol_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_major }}

                   Before installing AMDGPU driver on OL, :ref:`update the OS installation <update-enterprise-linux>`.

                   .. code-block:: bash
                       :substitutions:

                       sudo dnf install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/el/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.el{{ os_major }}.noarch.rpm
                       sudo dnf clean all
                       sudo dnf install "kernel-uek-devel-$(uname -r)"
                       sudo dnf install amdgpu-dkms

                {% endfor %}

        .. tab-item:: SUSE Linux Enterprise Server
            :sync: sle-tab

            .. tab-set::

                {% for os_version in config.html_context['sles_version_numbers'] %}
                .. tab-item:: {{ os_version }}

                   Before installing AMDGPU driver on SLES, :ref:`register your Enterprise Linux and update the OS installation <register-enterprise-linux>`.

                   .. code-block:: bash
                       :substitutions:

                       sudo SUSEConnect -p sle-module-desktop-applications/{{ os_version }}/x86_64
                       sudo SUSEConnect -p sle-module-development-tools/{{ os_version }}/x86_64
                       sudo SUSEConnect -p PackageHub/{{ os_version }}/x86_64
                       sudo zypper install zypper
                       sudo zypper --no-gpg-checks install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/sle/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.noarch.rpm
                       sudo zypper --gpg-auto-import-keys refresh
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
                       sudo tdnf install azurelinux-repos-amd
                       sudo tdnf repolist --refresh
                       sudo tdnf install amdgpu

                {% endfor %}

.. important::

    To apply all settings, reboot your system.

.. note::

    Quick Start enables GPU access for the current user only. To grant GPU access to all users, see :ref:`Configuring permissions for GPU access <group_permissions>`.

After completing the installation, review the :doc:`post-install`. If you have issues with your installation, see :doc:`Troubleshooting <../reference/install-faq>`.
