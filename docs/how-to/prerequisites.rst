Installation Prerequisites
##########################

You must perform the following steps before installing ROCm and check if the
system meets all the requirements to proceed with the installation.

Confirm the System Has a Supported Linux Distribution Version
**************************************************************

The ROCm installation is supported only on specific Linux distributions and
kernel versions.

Check the Linux Distribution and Kernel Version on Your System
==============================================================

This section discusses obtaining information about the Linux distribution and
kernel version.

Linux Distribution Information
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Verify the Linux distribution using the following steps:

1. To obtain the Linux distribution information, type the following command on
   your system from the Command Line Interface (CLI):

   .. code-block:: shell

       uname -m && cat /etc/*release

2. Confirm that the obtained Linux distribution information matches with those listed in :ref:`supported_distributions`.

   **Example:** Running the command above on an Ubuntu system results in the
   following output:

   .. code-block:: shell

        x86_64
        DISTRIB_ID=Ubuntu
        DISTRIB_RELEASE=20.04
        DISTRIB_CODENAME=focal
        DISTRIB_DESCRIPTION="Ubuntu 20.04.5 LTS"
    
.. _check-kernel-info:

Kernel Information
^^^^^^^^^^^^^^^^^^

Verify the kernel version using the following steps:

1. To check the kernel version of your Linux system, type the following command:

   .. code-block:: shell

       uname -srmv

   **Example:** The output of the command above lists the kernel version in the
   following format:

   .. code-block:: shell

       Linux 5.15.0-46-generic #44~20.04.5-Ubuntu SMP Fri Jun 24 13:27:29 UTC 2022 x86_64

2. Confirm that the obtained kernel version information matches with system
   requirements as listed in :ref:`supported_distributions`.

Additional package repositories
*******************************

On some distributions the ROCm packages depend on packages outside the default
package repositories. These extra repositories need to be enabled before
installation. Follow the instructions below based on your distributions.

.. tab-set::

    .. tab-item:: Ubuntu

        All packages are available in the default Ubuntu repositories, therefore no additional repositories need to be added.

    .. tab-item:: Red Hat Enterprise Linux

        1. Add the EPEL repository:

           .. tab-set::


               .. tab-item:: RHEL 8

                   .. code-block:: shell

                       wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-8.noarch.rpm
                       sudo rpm -ivh epel-release-latest-8.noarch.rpm

               .. tab-item:: RHEL 9

                   .. code-block:: shell

                       wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-9.noarch.rpm
                       sudo rpm -ivh epel-release-latest-8.noarch.rpm

        2. Enable the CodeReady Linux Builder repository:
        
           .. code-block:: shell

               sudo crb enable

    .. tab-item:: SUSE Linux Enterprise Server

        Add the Perl language repository.
        
        .. tab-set::

            .. tab-item:: SLES 15.4

                .. code-block:: shell

                    zypper addrepo https://download.opensuse.org/repositories/devel:/languages:/perl/15.4/devel:languages:perl.repo

            .. tab-item:: SLES 15.5

                .. code-block:: shell

                    zypper addrepo https://download.opensuse.org/repositories/devel:/languages:/perl/15.5/devel:languages:perl.repo

Kernel Headers and Development Packages
***************************************

The driver package uses
:abbr:`DKMS (Dynamic Kernel Module Support)` [DKMS-wiki]_ to build
the `amdgpu-dkms` module (driver) for the installed kernels. This requires the
Linux kernel headers and modules to be installed for each. Usually these are
automatically installed with the kernel, but if you have multiple kernel
versions or you have downloaded the kernel images and not the kernel
meta-packages then they must be manually installed.

.. [DKMS-wiki] https://en.wikipedia.org/wiki/Dynamic_Kernel_Module_Support

To install for the currently active kernel run the command corresponding
to your distribution.

.. tab-set::

    .. tab-item:: Ubuntu

        .. code-block:: shell

            sudo apt install "linux-headers-$(uname -r)" "linux-modules-extra-$(uname -r)"

    .. tab-item:: Red Hat Enterprise Linux

        .. code-block:: shell

            sudo yum install kernel-headers kernel-devel


    .. tab-item:: SUSE Linux Enterprise Server

        .. code-block:: shell

            sudo zypper install kernel-default-devel

Setting Permissions for Groups
******************************

This section provides steps to add any current user to a video group to access
GPU resources.
Use of the video group is recommended for all ROCm-supported operating
systems.

1. To check the groups in your system, issue the following command:

   .. code-block:: shell

       groups

2. Add yourself to the ``render`` and ``video`` group using the command:

   .. code-block:: shell

       sudo usermod -a -G render,video $LOGNAME

To add all future users to the ``video`` and ``render`` groups by default, run
the following commands:

.. code-block:: shell

    echo 'ADD_EXTRA_GROUPS=1' | sudo tee -a /etc/adduser.conf
    echo 'EXTRA_GROUPS=video' | sudo tee -a /etc/adduser.conf
    echo 'EXTRA_GROUPS=render' | sudo tee -a /etc/adduser.conf
