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

        .. datatemplate:nodata::
            
           .. tab-set::

              {% for os_release in config.html_context['rhel_release_version_numbers']  %}

                .. tab-item:: RHEL {{ os_release }}
        
                    .. code-block:: shell

                       subscription-manager register --username <username> --password <password>
                       subscription-manager attach --auto

           {% endfor %}

           More details about `registering for RHEL <https://access.redhat.com/solutions/253273>`_

  .. tab-item:: SUSE Linux Enterprise Server
        :sync: sle-tab

        Typically you can register by following the step-by-step user interface.
        If you need to register by command line, use the following commands:

        .. datatemplate:nodata::

            .. tab-set::

                {% for os_version in config.html_context['sles_version_numbers'] %}
                {% set os_release, os_sp  = os_version.split('.') %}

                .. tab-item:: SLES {{ os_version }}
                   
                   .. code-block:: shell

                      SUSEConnect -r <REGCODE>
                      SUSEConnect -p sle-module-desktop-applications/{{ os_version }}/x86_64
                      SUSEConnect -p sle-module-development-tools/{{ os_version }}/x86_64
                      SUSEConnect -p PackageHub/{{ os_version }}/x86_64

                {% endfor %}

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

        Add the Perl language and Education repositories.

        .. datatemplate:nodata::

            .. tab-set::

                {% for os_version in config.html_context['sles_version_numbers'] %}
                {% set os_release, os_sp  = os_version.split('.') %}

                .. tab-item:: SLES {{ os_version }}

                    .. code-block:: shell

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

Setting permissions for groups
================================================================

This section provides steps to add any current user to a video group to access GPU resources. We
recommend using the video group for all ROCm-supported operating systems.

1. To check the groups in your system, issue the following command:

   .. code-block:: shell

       groups

2. Add yourself to the ``render`` and ``video`` group using the command:

   .. code-block:: shell

        sudo usermod -a -G render,video $LOGNAME

   To add all future users to the ``render`` and ``video`` groups by default, run the following commands:

   .. code-block:: shell

        echo 'ADD_EXTRA_GROUPS=1' | sudo tee -a /etc/adduser.conf
        echo 'EXTRA_GROUPS=video' | sudo tee -a /etc/adduser.conf
        echo 'EXTRA_GROUPS=render' | sudo tee -a /etc/adduser.conf

.. tip::

    On systems with multiple users, if ROCm is installed system wide, each individual user should be added to the ``render`` and ``video`` groups. 

Disable integrated graphics (IGP), if applicable
================================================================

ROCm doesn't currently support integrated graphics. Should your system have an
AMD IGP installed, disable it in the BIOS prior to using ROCm. If the driver can
enumerate the IGP, the ROCm runtime may crash the system, even if told to omit
it via `HIP_VISIBLE_DEVICES <https://rocm.docs.amd.com/en/latest/conceptual/gpu-isolation.html#hip-visible-devices>`_.
