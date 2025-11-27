.. meta::
  :description: Installation prerequisites
  :keywords: installation prerequisites, AMD, ROCm

*********************************************************************
Installation prerequisites
*********************************************************************

Before installing ROCm, complete the following prerequisites.

1. Confirm the system has a supported Linux version.

   * To obtain the Linux distribution information, use the following command:

     .. code-block:: shell

          uname -m && cat /etc/*release

   * Confirm that your Linux distribution matches a :ref:`supported distribution <supported_distributions>`.

     **Example:** Running the preceding command on an Ubuntu system produces the following output:

     .. code-block:: shell

            x86_64
            DISTRIB_ID=Ubuntu
            DISTRIB_RELEASE=24.04
            DISTRIB_CODENAME=noble
            DISTRIB_DESCRIPTION="Ubuntu 24.04.3 LTS"

.. _verify_kernel_version:

2. Verify the kernel version.

   * To check the kernel version of your Linux system, type the following command:

     .. code-block:: shell

            uname -srmv

     **Example:** The preceding command lists the kernel version in the following format:

     .. code-block:: shell

            Linux 6.8.0-50-generic #51-Ubuntu SMP PREEMPT_DYNAMIC Sat Nov  9 17:58:29 UTC 2024 x86_64

   * Confirm that your kernel version matches the system requirements, as listed in :ref:`supported_distributions`.

.. _register-enterprise-linux:

Register your Enterprise Linux
==========================================================

If you're using Red Hat Enterprise Linux (RHEL) or SUSE Linux Enterprise Server (SLES), register
your operating system to ensure you're able to download and install packages.

.. datatemplate:nodata::

    .. tab-set::

        .. tab-item:: Ubuntu
            :sync: ubuntu-tab

            There is no registration required for Ubuntu.

        .. tab-item:: Debian
            :sync: debian-tab

            There is no registration required for Debian.

        .. tab-item:: Red Hat Enterprise Linux
            :sync: rhel-tab

            .. tab-set::

                {% for os_version in config.html_context['rhel_version_numbers'] %}
                .. tab-item:: {{ os_version }}
                    :sync: {{ os_version }}

                    Typically you can register by following the step-by-step user interface.
                    If you need to register by command line, use the following commands:

                    .. code-block:: shell
                        :substitutions:

                        {% if os_version == '10.0' or '10.1' -%}
                        subscription-manager register --username <username> --password <password>
                        {%- else -%}
                        subscription-manager register --username <username> --password <password>
                        subscription-manager attach --auto
                        {%- endif %}

                    More details about `registering for RHEL <https://access.redhat.com/solutions/253273>`_

                {% endfor %}

        .. tab-item:: Oracle Linux
            :sync: ol-tab

            There is no registration required for Oracle Linux.

        .. tab-item:: SUSE Linux Enterprise Server
            :sync: sle-tab

            Typically you can register by following the step-by-step user interface.
            If you need to register by command line, use the following commands:
                
            .. code-block:: shell

                sudo SUSEConnect -r <REGCODE>

            More details about `registering for SLES <https://www.suse.com/support/kb/doc/?id=000018564>`_

        .. tab-item:: Rocky Linux
            :sync: rl-tab

            There is no registration required for Rocky Linux.

.. _update-enterprise-linux:

Update your Enterprise Linux
==========================================================

If you are using Red Hat Enterprise Linux (RHEL), SUSE Linux Enterprise Servers (SLES), or Oracle Linux (OL), 
it is recommended that you update your operating system to the latest packages from the Linux distribution.
This is a requirement for newer hardware on older versions of RHEL, SLES, or OL.

.. datatemplate:nodata::

    .. tab-set::

        .. tab-item:: Ubuntu
            :sync: ubuntu-tab

            There is no update required for Ubuntu.
        
        .. tab-item:: Debian
            :sync: debian-tab

            There is no update required for Debian.

        .. tab-item:: Red Hat Enterprise Linux
            :sync: rhel-tab

            .. tab-set::

                {% for os_version in config.html_context['rhel_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}
                    :sync: {{ os_version }}

                    .. code-block:: bash
                        :substitutions:

                        sudo dnf update --releasever={{ os_version }} --exclude=\*release\*
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

                       sudo dnf update --releasever={{ os_version }} --exclude=\*release\*
                {% endfor %}

        .. tab-item:: SUSE Linux Enterprise Server
            :sync: sle-tab

            .. code-block:: bash

                sudo zypper update

        .. tab-item:: Rocky Linux
            :sync: rl-tab

            There is no update required for Rocky Linux.

.. important::

    To apply all settings, reboot your system.

Additional package repositories
==========================================================

For some distributions, the ROCm installation packages depend on packages that aren't included in the default package
repositories. These external repositories need to be sourced before installation. Use the following
instructions specific to your distribution to add the necessary repositories.

.. tab-set::

    .. tab-item:: Ubuntu
        :sync: ubuntu-tab

        All ROCm installation packages are available in the default Ubuntu repositories.

    .. tab-item:: Debian
        :sync: debian-tab

        All ROCm installation packages are available in the default Debian repositories.

    .. tab-item:: Red Hat Enterprise Linux
        :sync: rhel-tab

        1. Add the EPEL repository.

           .. datatemplate:nodata::

               .. tab-set::

                  {% for os_version in config.html_context['rhel_version_numbers'] %}
                  {% set os_major, _  = os_version.split('.') %}

                      .. tab-item:: {{ os_version }}
                          :sync: {{ os_version }}

                          .. code-block:: shell

                              wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-{{ os_major }}.noarch.rpm
                              sudo rpm -ivh epel-release-latest-{{ os_major }}.noarch.rpm

                  {% endfor %}

        2. Enable the CodeReady Linux Builder (CRB) repository.

           .. datatemplate:nodata::

               .. tab-set::

                  {% for os_version in config.html_context['rhel_version_numbers'] %}
                  {% set os_major, _  = os_version.split('.') %}

                      .. tab-item:: {{ os_version }}
                         :sync: {{ os_version }}

                         .. code-block:: shell

                             sudo dnf config-manager --enable codeready-builder-for-rhel-{{ os_major }}-x86_64-rpms

                  {% endfor %}

    .. tab-item:: Oracle Linux
        :sync: ol-tab

        1. Add the EPEL repository.

           .. datatemplate:nodata::

               .. tab-set::

                  {% for os_version in config.html_context['ol_version_numbers'] %}
                  {% set os_major, _  = os_version.split('.') %}
                      .. tab-item:: {{ os_version }}
                        :sync: {{ os_version }}

                        .. code-block:: shell

                            wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-{{ os_major }}.noarch.rpm
                            sudo rpm -ivh epel-release-latest-{{ os_major }}.noarch.rpm

                  {% endfor %}

        2. Enable the CodeReady Linux Builder (CRB) repository.

           .. code-block:: shell

               sudo crb enable

    .. tab-item:: SUSE Linux Enterprise Server
        :sync: sle-tab

        Add a few modules with SUSEConnect and the science repository.

        .. datatemplate:nodata::

            .. tab-set::

                {% for os_version in config.html_context['sles_version_numbers'] %}
                {% set os_release, os_sp  = os_version.split('.') %}

                .. tab-item:: {{ os_version }}

                    .. code-block:: shell

                        sudo SUSEConnect -p sle-module-desktop-applications/{{ os_version }}/x86_64
                        sudo SUSEConnect -p sle-module-development-tools/{{ os_version }}/x86_64
                        sudo SUSEConnect -p PackageHub/{{ os_version }}/x86_64
                        sudo zypper install zypper
                        sudo zypper addrepo https://download.opensuse.org/repositories/science/SLE_15_SP5/science.repo


                {% endfor %}

    .. tab-item:: Rocky Linux
        :sync: rl-tab

        1. Add the EPEL repository.

           .. datatemplate:nodata::

               .. tab-set::

                  {% for os_version in config.html_context['rl_version_numbers'] %}
                  {% set os_major, _  = os_version.split('.') %}

                      .. tab-item:: {{ os_version }}

                        .. code-block:: shell

                            wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-{{ os_major }}.noarch.rpm
                            sudo rpm -ivh epel-release-latest-{{ os_major }}.noarch.rpm

                  {% endfor %}

        2. Enable the CodeReady Linux Builder (CRB) repository.

           In order to enable CRB, you may need to install ``dnf-plugin-config-manager`` first.

           .. code-block:: shell

               sudo dnf install dnf-plugin-config-manager
               sudo crb enable

.. _additional_dev_packages:

Additional development packages
================================================================

ROCm installation requires additional packages for operation and development.

To install the required packages, use the following instructions specific to your distribution:

.. tab-set::

    .. tab-item:: Ubuntu
        :sync: ubuntu-tab

        .. code-block:: shell

            sudo apt install python3-setuptools python3-wheel

    .. tab-item:: Debian
        :sync: debian-tab

        .. code-block:: shell

            sudo apt install python3-setuptools python3-wheel


    .. tab-item:: Red Hat Enterprise Linux
        :sync: rhel-tab

        .. code-block:: shell

            sudo dnf install python3-setuptools python3-wheel

    .. tab-item:: Oracle Linux
        :sync: ol-tab

        .. code-block:: shell

            sudo dnf install python3-setuptools python3-wheel

    .. tab-item:: SUSE Linux Enterprise Server
        :sync: sle-tab

        .. code-block:: shell

            sudo zypper install python3-setuptools python3-wheel

    .. tab-item:: Rocky Linux
        :sync: rl-tab

        .. code-block:: shell

            sudo dnf install python3-setuptools python3-wheel


Optionally, if configuring the :ref:`post-ROCm installation <config_rocm_path>` using ``environment-modules``, install the following:

.. tab-set::

    .. tab-item:: Ubuntu
        :sync: ubuntu-tab

        .. code-block:: shell

            sudo apt install environment-modules

    .. tab-item:: Debian
        :sync: debian-tab

        .. code-block:: shell

            sudo apt install environment-modules


    .. tab-item:: Red Hat Enterprise Linux
        :sync: rhel-tab

        .. code-block:: shell

            sudo dnf install environment-modules

    .. tab-item:: Oracle Linux
        :sync: ol-tab

        .. code-block:: shell

            sudo dnf install environment-modules

    .. tab-item:: SUSE Linux Enterprise Server
        :sync: sle-tab

        .. code-block:: shell

            sudo zypper install environment-modules

            # Create a link for installed modules version
            version=$(rpm -qa | grep '^Modules-' | awk -F'-' '{print $2}')
            sudo ln -s /usr/share/Modules/$version/modulefiles /usr/share/Modules/modulefiles

    .. tab-item:: Rocky Linux
        :sync: rl-tab

        .. code-block:: shell

            sudo dnf install environment-modules

.. _group_permissions:

Configuring permissions for GPU access
================================================================

There are two primary methods to configure GPU access for ROCm: group membership or
udev rules. Each method has its own advantages, and the choice depends on your 
specific requirements and system management preferences.

1. Using group membership
--------------------------------------------------------------------

By default, GPU access is managed through membership in the ``video`` and ``render`` groups.
The ``video`` and ``render`` groups are system groups in Linux used to manage access 
to graphics hardware and related functionality. Traditionally, the ``video`` group is used 
to control access to video devices, including graphics cards and video capture devices. 
The ``render`` group is more recent and specifically controls access to GPU rendering capabilities 
through Direct Rendering Manager (DRM) render nodes.

1. To check the groups in your system, issue the following command:

   .. code-block:: shell

       groups

2. Add yourself to the ``video`` and ``render`` groups:

   .. code-block:: shell

       sudo usermod -a -G video,render $LOGNAME

3. Optionally, add other users to the ``video`` and ``render`` groups:

   .. code-block:: shell

       sudo usermod -a -G video,render user1
       sudo usermod -a -G video,render user2

4. To add all future users to the render and video groups by default, run the following commands:

   .. code-block:: shell

       echo 'ADD_EXTRA_GROUPS=1' | sudo tee -a /etc/adduser.conf
       echo 'EXTRA_GROUPS=video' | sudo tee -a /etc/adduser.conf
       echo 'EXTRA_GROUPS=render' | sudo tee -a /etc/adduser.conf

2. Using udev rules
--------------------------------------------------------------------

A flexible way to manage device permissions is to use udev rules. They apply system-wide, can be 
easily deployed via configuration management tools, and eliminate the need for user group management. 
This method provides more granular control over GPU access. 
   
GPU access may be granted to either all users or a custom group:

a. Grant GPU access to all users on the system
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To set up udev rules, install the package using the following instructions specific to your distribution: 

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

                       sudo apt update 
                       wget https://repo.radeon.com/amdgpu/|udev_amdgpu_version|/ubuntu/pool/main/a/amdgpu-insecure-instinct-udev-rules/amdgpu-insecure-instinct-udev-rules_|udev_version|.{{ os_version }}_all.deb 
                       sudo apt install ./amdgpu-insecure-instinct-udev-rules_|udev_version|.{{ os_version }}_all.deb 
                {% endfor %}
        
        .. tab-item:: Debian
            :sync: debian-tab

            .. tab-set::

                {% for (os_version, os_release, ubuntu_version) in config.html_context['debian_udev_versions'] %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo apt update 
                       wget https://repo.radeon.com/amdgpu/|udev_amdgpu_version|/ubuntu/pool/main/a/amdgpu-insecure-instinct-udev-rules/amdgpu-insecure-instinct-udev-rules_|udev_version|.{{ ubuntu_version }}_all.deb 
                       sudo apt install ./amdgpu-insecure-instinct-udev-rules_|udev_version|.{{ ubuntu_version }}_all.deb 
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

                       {% if os_major == '9' -%}
                       sudo dnf install https://repo.radeon.com/amdgpu/|udev_amdgpu_version|/el/{{ os_version }}/main/x86_64/amdgpu-insecure-instinct-udev-rules-|udev_version|.el{{ os_major }}.noarch.rpm
                       {%- else -%}
                       sudo dnf install https://repo.radeon.com/amdgpu/|udev_amdgpu_version|/el/{{ os_major }}/main/x86_64/amdgpu-insecure-instinct-udev-rules-|udev_version|.el{{ os_major }}.noarch.rpm
                       {%- endif %}

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

                       {% if os_major == '9' -%}
                       sudo dnf install https://repo.radeon.com/amdgpu/|udev_amdgpu_version|/el/{{ os_version }}/main/x86_64/amdgpu-insecure-instinct-udev-rules-|udev_version|.el{{ os_major }}.noarch.rpm
                       {%- else -%}
                       sudo dnf install https://repo.radeon.com/amdgpu/|udev_amdgpu_version|/el/{{ os_major }}/main/x86_64/amdgpu-insecure-instinct-udev-rules-|udev_version|.el{{ os_major }}.noarch.rpm
                       {%- endif %}
                {% endfor %}

        .. tab-item:: SUSE Linux Enterprise Server
            :sync: sle-tab

            .. tab-set::

                {% for os_version in config.html_context['sles_version_numbers'] %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo zypper --no-gpg-checks install https://repo.radeon.com/amdgpu/|udev_amdgpu_version|/sle/{{ os_version }}/main/x86_64/amdgpu-insecure-instinct-udev-rules-|udev_version|.noarch.rpm 

                {% endfor %}

        .. tab-item:: Rocky Linux
            :sync: rl-tab

            .. tab-set::

                {% for os_version in config.html_context['rl_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                   .. code-block:: bash
                       :substitutions:

                       sudo dnf install https://repo.radeon.com/amdgpu/|udev_amdgpu_version|/el/{{ os_version }}/main/x86_64/amdgpu-insecure-instinct-udev-rules-|udev_version|.el{{ os_major }}.noarch.rpm 
                {% endfor %}

b. Grant GPU access to a custom group
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

1. Create a new group (e.g., ``devteam``):

   .. code-block:: shell

      sudo groupadd devteam

2. Add users to the new group:

   .. code-block:: shell

      sudo usermod -a -G devteam dev1
      sudo usermod -a -G devteam dev2

3. Create udev rules to assign GPU devices to this group:

   Create a file ``/etc/udev/rules.d/70-amdgpu.rules`` with:

   .. code-block:: shell

      KERNEL=="kfd", GROUP="devteam", MODE="0660"
      SUBSYSTEM=="drm", KERNEL=="renderD*", GROUP="devteam", MODE="0660"

4. Reload the udev rules:

   .. code-block:: shell

      sudo udevadm control --reload-rules && sudo udevadm trigger

This configuration grants all users in the ``devteam`` group read and write access to AMD GPU resources, 
including the AMD Kernel-mode GPU Driver (KMD) and Direct Rendering Manager (DRM) devices.

Disable integrated graphics (IGP)
================================================================

ROCm doesn't currently support integrated graphics. If your system has an
AMD IGP installed, disable it in the BIOS prior to using ROCm. If the driver can
enumerate the IGP, the ROCm runtime might crash the system, even when omission was specified
via `HIP_VISIBLE_DEVICES <https://rocm.docs.amd.com/en/latest/conceptual/gpu-isolation.html#hip-visible-devices>`_.

Secure Boot
===========

When installing the AMDGPU driver with Secure Boot enabled, you must sign ``amdgpu-dkms`` to prevent potential system loading issues. 
For more information, see `Secure Boot Support <https://amdgpu-install.readthedocs.io/en/latest/install-installing.html#secure-boot-support>`_. 
If you prefer not to sign the AMDGPU driver, you can disable Secure Boot from the BIOS settings instead.