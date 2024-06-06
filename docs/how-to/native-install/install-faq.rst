.. meta::
  :description: Frequently asked questions for install
  :keywords: Linux, install, FAQ, ubuntu, RHEL, SUSE, AMD, ROCm

.. _troubleshooting:

************************************************************************************
Installation Troubleshooting
************************************************************************************

Troubleshooting describes issues that some users encounter when installing the ROCm tools or libraries.

Issue #1: Installation Methods
=================================

As an example, the latest version of ROCm is 6.0.2, but the installation instructions result in release 6.0.0 being installed.

**Solution:** You may have used the quick-start installation method which only installs the latest major release. Use one of the other available installation methods:

* :doc:`Quick-start installation <../../tutorial/quick-start>` - Installs only the latest **major** release (i.e. 6.0.0, or 6.1.0)
* :doc:`Native package manager install method <./index>` - Installs the specified *major and minor* release version (i.e. 6.0.0, 6.0.2)
* :doc:`amdgpu-install method <../amdgpu-install>` - Installs the specified *major and minor* release version (i.e. 6.0.0, 6.0.2)

Refer to `ROCm Issue #2422 <https://github.com/ROCm/ROCm/issues/2422>`_ for additional details.


Issue #2: Install Prerequisites
==================================

When installing, I see the following message: ``Problem: nothing provides perl-URI-Encode needed to be installed by ...``

**Solution:** Ensure that the :doc:`../prerequisites` are installed.  There are prerequisite PERL packages required for SUSE.  RHEL also requires Extra Packages for Enterprise Linux (EPEL) to be installed, which is also mentioned in prerequisites.  Be sure to install those first, then repeat your installation steps.

Refer to `ROCm Issue #1827 <https://github.com/ROCm/ROCm/issues/1827>`_. 


Issue #3: PATH variable
============================

After successfully installing ROCm, when I run ``rocminfo`` (or another ROCm tool) the command is not found.

**Solution:** You may need to update your ``PATH`` environment variable as described in :doc:`./post-install`.

Refer to `ROCm Issue #1607 <https://github.com/ROCm/ROCm/issues/1607>`_.


Issue #4: C++ libraries
=========================

When compiling HIP programs, I get a linking error for ``-lstdc++``, or ``fatal error: 'cmath' file not found``.

**Solution:** You can install C++ libraries using your package manager. The following is an Ubuntu example:

.. code-block:: bash

  sudo apt-get install libstdc++-12-dev

Refer to `ROCm Issue #2031 <https://github.com/ROCm/ROCm/issues/2031>`_.


.. _multi-gpu:

Issue #5: Application hangs on Multi-GPU systems
==================================================

Running on a system with multiple GPUs the application hangs with the GPU use at 100%, but without the expected GPU temperature buildup

This issue often results in the following message in the application transcript: 

.. code-block:: shell

  NCCL WARN Missing "iommu=pt" from kernel command line which can lead to system instablity or hang!

**Solution:** To resolve this issue add ``iommu=pt`` to ``GRUB_CMDLINE_LINUX_DEFAULT`` in ``/etc/default/grub``. Then run the following command: 

.. code-block:: shell

  sudo update-grub 

Reboot the system, and run the following command:

.. code-block:: shell

  cat /proc/cmdline

The returned information should reflect the addition of ``iommu``:

.. code-block:: shell

  BOOT_IMAGE=/vmlinuz-5.15.0-101-generic root=/dev/mapper/ubuntu--vg-ubuntu--lv ro iommu=pt

Refer to `RCCL Issue #1129 <https://github.com/ROCm/rccl/issues/1129>`_ for more information. 


.. _troubleshooting-registering-license:

Issue #6: Registering Enterprise Linux
========================================

Prior to installing ROCm, you should be registered and activated with the distro you're using.  Visit these external pages for help with your OS distro.

.. tab-set::

  .. tab-item:: RHEL

    Typically you can register by following the step-by-step user interface.
    However, if you need to register by command line, you can follow these examples:
    
    .. code-block:: shell

      subscription-manager register --username <username> --password <password>
      subscription-manager attach --auto
      subscription-manager repos --enable codeready-builder-for-rhel-9-x86_64-rpms

    More details about `registering for RHEL <https://access.redhat.com/solutions/253273>`_

  .. tab-item:: SLES

    Typically you can register by following the step-by-step user interface.
    However, if you need to register by command line, you can follow these examples:
    
    .. code-block:: shell

      SUSEConnect -r <REGCODE>
      SUSEConnect -p sle-module-desktop-application/15.4/x86_64
      SUSEConnect -p sle-module-development-tools/15.4/x86_64
      SUSEConnect -p PackageHub/15.4/x86_64

    More details about `registering for SLES <https://www.suse.com/support/kb/doc/?id=000018564>`_



.. _troubleshooting-install-missing-packages-for-dockers:

Issue #7: Additional packages for docker images
================================================

Docker images may not include some basic packages.  When installing ROCm using docker images, you may need to install packages prior to following ROCm install instructions. Here are some suggested steps when using docker images.

.. tab-set::

  .. tab-item:: Ubuntu

    .. code-block:: shell

      apt update
      apt install sudo wget


  .. tab-item:: RHEL

    .. code-block:: shell

      dnf install sudo wget
      subscription-manager register --username <username> --password <password>
      subscription-manager attach --auto
      subscription-manager repos --enable codeready-builder-for-rhel-9-x86_64-rpms


  .. tab-item:: SLES

    .. code-block:: shell

      zypper install sudo wget SUSEConnet
      SUSEConnect -r <REGCODE>
      SUSEConnect -p sle-module-desktop-application/15.4/x86_64
      SUSEConnect -p sle-module-development-tools/15.4/x86_64
      SUSEConnect -p PackageHub/15.4/x86_64


After installing these packages and registering using your license for enterprise linux, you can install ROCm following the :doc:`quick start guide <../../tutorial/quick-start>` on your docker images.


