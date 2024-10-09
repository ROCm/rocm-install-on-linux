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
            DISTRIB_RELEASE=20.04
            DISTRIB_CODENAME=focal
            DISTRIB_DESCRIPTION="Ubuntu 20.04.5 LTS"

.. _verify_kernel_version:

2. Verify the kernel version.

   * To check the kernel version of your Linux system, type the following command:

     .. code-block:: shell

            uname -srmv

     **Example:** The preceding command lists the kernel version in the following format:

     .. code-block:: shell

            Linux 5.15.0-46-generic #44~20.04.5-Ubuntu SMP Fri Jun 24 13:27:29 UTC 2022 x86_64

   * Confirm that your kernel version matches the system requirements, as listed in :ref:`supported_distributions`.

.. _register-enterprise-linux:

Register your Enterprise Linux
==========================================================

If you're using Red Hat Enterprise Linux (RHEL) or SUSE Linux Enterprise Server (SLES), register
your operating system to ensure you're able to download and install packages.

.. tab-set::

  .. tab-item:: Ubuntu
        :sync: ubuntu-tab

        There is no registration required for Ubuntu.

  .. tab-item:: Red Hat Enterprise Linux
        :sync: rhel-tab

        Typically you can register by following the step-by-step user interface.
        If you need to register by command line, use the following commands:

        .. code-block:: shell

            subscription-manager register --username <username> --password <password>
            subscription-manager attach --auto

        More details about `registering for RHEL <https://access.redhat.com/solutions/253273>`_

  .. tab-item:: SUSE Linux Enterprise Server
        :sync: sle-tab

        Typically you can register by following the step-by-step user interface.
        If you need to register by command line, use the following commands:
            
        .. code-block:: shell

            SUSEConnect -r <REGCODE>

        More details about `registering for SLES <https://www.suse.com/support/kb/doc/?id=000018564>`_


Additional package repositories
==========================================================

For some distributions, the ROCm installation packages depend on packages that aren't included in the default package
repositories. These external repositories need to be sourced before installation. Use the following
instructions specific to your distribution to add the necessary repositories.

.. tab-set::

    .. tab-item:: Ubuntu
        :sync: ubuntu-tab

        All ROCm installation packages are available in the default Ubuntu repositories.

    .. tab-item:: Red Hat Enterprise Linux
        :sync: rhel-tab

        1. Add the EPEL repository.

           .. datatemplate:nodata::

               .. tab-set::

                  {% for os_release in config.html_context['rhel_release_version_numbers']  %}

                      .. tab-item:: RHEL {{ os_release }}

                        .. code-block:: shell

                            wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-{{ os_release }}.noarch.rpm
                            sudo rpm -ivh epel-release-latest-{{ os_release }}.noarch.rpm

                  {% endfor %}

        2. Enable the CodeReady Linux Builder (CRB) repository.

           In order to enable CRB, you may need to install ``dnf-plugin-config-manager`` first.

           .. code-block:: shell

               sudo dnf install dnf-plugin-config-manager
               sudo crb enable

    .. tab-item:: SUSE Linux Enterprise Server
        :sync: sle-tab

        Add a few modules with SUSEConnect, along with the Perl language and Education repositories.

        .. datatemplate:nodata::

            .. tab-set::

                {% for os_version in config.html_context['sles_version_numbers'] %}
                {% set os_release, os_sp  = os_version.split('.') %}

                .. tab-item:: SLES {{ os_version }}

                    .. code-block:: shell

                        SUSEConnect -p sle-module-desktop-applications/{{ os_version }}/x86_64
                        SUSEConnect -p sle-module-development-tools/{{ os_version }}/x86_64
                        SUSEConnect -p PackageHub/{{ os_version }}/x86_64
                        sudo zypper addrepo https://download.opensuse.org/repositories/devel:/languages:/perl/{{ os_version }}/devel:languages:perl.repo
                        sudo zypper addrepo https://download.opensuse.org/repositories/Education/{{ os_version }}/Education.repo

                {% endfor %}

Kernel headers and development packages
================================================================

The driver package uses
`Dynamic Kernel Module Support (DKMS) <https://en.wikipedia.org/wiki/Dynamic_Kernel_Module_Support>`_
to build the `amdgpu-dkms` module (driver) for the installed kernels. This requires the Linux kernel
headers and modules to be installed for each. Usually these are automatically installed with the kernel,
but if you have multiple kernel versions or you have downloaded the kernel images and not the kernel
meta-packages then they must be manually installed.

To install for the currently active kernel run the command corresponding to your distribution.

.. tab-set::

    .. tab-item:: Ubuntu
        :sync: ubuntu-tab

        .. code-block:: shell

            sudo apt install "linux-headers-$(uname -r)" "linux-modules-extra-$(uname -r)"

    .. tab-item:: Red Hat Enterprise Linux
        :sync: rhel-tab

        .. code-block:: shell

            sudo dnf install "kernel-headers-$(uname -r)" "kernel-devel-$(uname -r)"


    .. tab-item:: SUSE Linux Enterprise Server
        :sync: sle-tab

        .. code-block:: shell

            sudo zypper install kernel-default-devel

.. _group_permissions:

Configuring permissions for GPU access
================================================================

There are two primary methods to configure GPU access for ROCm: using udev rules 
or managing group membership. Each method has its own advantages, and the choice 
depends on your specific requirements and system management preferences.

Using udev Rules (Recommended)
--------------------------------------------------------------------
Udev rules offer a flexible way to manage device permissions. They apply system-wide, can be 
easily deployed via configuration management tools, and eliminate the need for user group management. 
This method provides more granular control over GPU access.

Grant GPU access to all users on the system
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

1. Create a new file ``/etc/udev/rules.d/70-amdgpu.rules`` with the following content:

   .. code-block:: bash

      KERNEL=="kfd", MODE="0666"
      SUBSYSTEM=="drm", KERNEL=="renderD*", MODE="0666"

2. Reload the udev rules:

   .. code-block:: bash

      sudo udevadm control --reload-rules && sudo udevadm trigger

This configuration grants all users read and write access to AMD GPU resources, 
including the AMD Kernel Fusion Driver (KFD) and Direct Rendering Manager (DRM) devices.

Grant GPU access to a custom group
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

1. Create a new group (e.g., ``devteam``):

   .. code-block:: bash

      sudo groupadd devteam

2. Add users to the new group:

   .. code-block:: bash

      sudo usermod -a -G devteam dev1
      sudo usermod -a -G devteam dev2

3. Create udev rules to assign GPU devices to this group:

   Create a file ``/etc/udev/rules.d/70-amdgpu.rules`` with:

   .. code-block:: bash

      KERNEL=="kfd", GROUP="devteam", MODE="0660"
      SUBSYSTEM=="drm", KERNEL=="renderD*", GROUP="devteam", MODE="0660"

4. Reload the udev rules:

   .. code-block:: bash

      sudo udevadm control --reload-rules && sudo udevadm trigger

This configuration grants all users in the ``devteam`` group read and write access to AMD GPU resources, 
including the Kernel Fusion Driver (KFD) and Direct Rendering Manager (DRM) devices.

Using Group Membership
--------------------------------------------------------------------

Alternatively, you can manage GPU access through membership in the ``video`` and ``render`` groups.
The ``video`` and ``render`` groups are system groups in Linux used to manage access 
to graphics hardware and related functionality. Traditionally, the ``video`` group is used 
to control access to video devices, including graphics cards and video capture devices. 
The ``render`` group is more recent and specifically controls access to GPU rendering capabilities 
through Direct Rendering Manager (DRM) render nodes.

1. To check the groups in your system, issue the following command:

   .. code-block:: shell

       groups

2. Add yourself to the ``video`` and ``render`` groups:

   .. code-block:: bash

      sudo usermod -a -G video,render $LOGNAME

3. Optionally, add other users to the ``video`` and ``render`` groups:

   .. code-block:: bash

      sudo usermod -a -G video,render user1
      sudo usermod -a -G video,render user2

4. To add all future users to the render and video groups by default, run the following commands:

   .. code-block:: bash

      echo 'ADD_EXTRA_GROUPS=1' | sudo tee -a /etc/adduser.conf
      echo 'EXTRA_GROUPS=video' | sudo tee -a /etc/adduser.conf
      echo 'EXTRA_GROUPS=render' | sudo tee -a /etc/adduser.conf

Disable integrated graphics (IGP), if applicable
================================================================

ROCm doesn't currently support integrated graphics. Should your system have an
AMD IGP installed, disable it in the BIOS prior to using ROCm. If the driver can
enumerate the IGP, the ROCm runtime may crash the system, even if told to omit
it via `HIP_VISIBLE_DEVICES <https://rocm.docs.amd.com/en/latest/conceptual/gpu-isolation.html#hip-visible-devices>`_.
