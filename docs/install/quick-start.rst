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

    Like AMD Instinct accelerators, AMD Radeon and Radeon Pro GPUs can be used in environments for compute purposes (no display information or graphics). If using AMD Radeon or Radeon Pro GPUs with ROCm for graphics-related purposes (for example, display connected), review the `Radeon installation instructions <https://rocm.docs.amd.com/projects/radeon/en/latest/index.html>`_ in the Use ROCm on Radeon GPU documentation to confirm system requirements.

.. datatemplate:nodata::

    .. tab-set::

        .. tab-item:: Ubuntu

            .. tab-set::

                {% for (os_version, os_release) in config.html_context['ubuntu_version_numbers'] %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo apt update
                       sudo apt install "linux-headers-$(uname -r)" "linux-modules-extra-$(uname -r)"
                       sudo usermod -a -G render,video $LOGNAME # Add the current user to the render and video groups
                       wget https://repo.radeon.com/amdgpu-install/|amdgpu_version|/ubuntu/{{ os_release }}/amdgpu-install_|amdgpu_install_version|_all.deb
                       sudo apt install ./amdgpu-install_|amdgpu_install_version|_all.deb
                       sudo apt update
                       sudo apt install amdgpu-dkms rocm
                {% endfor %}

        .. tab-item:: Red Hat Enterprise Linux

            .. tab-set::

                {% for os_version in config.html_context['rhel_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   Before installing ROCm on RHEL, :ref:`register your Enterprise Linux <register-enterprise-linux>`.

                   .. code-block:: bash
                       :substitutions:

                       sudo dnf update
                       wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-{{ os_major }}.noarch.rpm
                       sudo rpm -ivh epel-release-latest-{{ os_major }}.noarch.rpm
                       sudo dnf install dnf-plugin-config-manager
                       sudo crb enable
                       sudo dnf install "kernel-headers-$(uname -r)" "kernel-devel-$(uname -r)"
                       sudo usermod -a -G render,video $LOGNAME # Add the current user to the render and video groups
                       sudo dnf install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/rhel/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.el{{ os_major }}.noarch.rpm
                       sudo dnf clean all
                       sudo dnf install amdgpu-dkms rocm
                {% endfor %}

        .. tab-item:: SUSE Linux Enterprise Server

            .. tab-set::

                {% for os_version in config.html_context['sles_version_numbers'] %}
                .. tab-item:: {{ os_version }}

                   Before installing ROCm on SLES, :ref:`register your Enterprise Linux <register-enterprise-linux>`.

                   .. code-block:: bash
                       :substitutions:

                       sudo zypper update
                       SUSEConnect -p sle-module-desktop-applications/{{ os_version }}/x86_64
                       SUSEConnect -p sle-module-development-tools/{{ os_version }}/x86_64
                       SUSEConnect -p PackageHub/{{ os_version }}/x86_64
                       sudo zypper addrepo https://download.opensuse.org/repositories/devel:languages:perl/{{ os_version}}/devel:languages:perl.repo
                       sudo zypper addrepo https://download.opensuse.org/repositories/Education/{{ os_version }}/Education.repo
                       sudo zypper install kernel-default-devel
                       sudo usermod -a -G render,video $LOGNAME # Add the current user to the render and video groups
                       sudo zypper --no-gpg-checks install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/sle/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.noarch.rpm
                       sudo zypper refresh
                       sudo zypper install amdgpu-dkms rocm
                {% endfor %}

.. important::

    To apply all settings, reboot your system.

After completing the installation, review the :doc:`post-install`. If you have issues with your installation, see :doc:`Troubleshooting <../reference/install-faq>`.
