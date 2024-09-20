.. meta::
  :description: Frequently asked questions for install
  :keywords: Linux, install, FAQ, ubuntu, RHEL, SUSE, AMD, ROCm

.. _troubleshooting:

************************************************************************************
Installation troubleshooting
************************************************************************************

Troubleshooting describes issues that some users encounter when installing the ROCm tools or libraries.

.. _troubleshooting-install-methods:

Issue #1: Installation methods
=================================

As an example, the latest version of ROCm is 6.0.2, but the installation instructions result in release 6.0.0 being installed.

**Solution:** You may have used the quick-start installation method which only installs the latest major release. Use one of the other available installation methods:

* :doc:`Quick-start installation <../install/quick-start>` - Installs only the latest **major** release (i.e. 6.0.0, or 6.1.0)
* :doc:`Native package manager install method <../install/native-install/index>` - Installs the specified *major and minor* release version (i.e. 6.0.0, 6.0.2)
* :doc:`amdgpu-install method <../install/amdgpu-install>` - Installs the specified *major and minor* release version (i.e. 6.0.0, 6.0.2)

Refer to `ROCm Issue #2422 <https://github.com/ROCm/ROCm/issues/2422>`_ for additional details.

.. _troubleshooting-install-prerequisites:

Issue #2: Install prerequisites
==================================

When installing, I see the following message: ``Problem: nothing provides perl-URI-Encode needed to be installed by ...``

**Solution:** Ensure that the :doc:`../install/prerequisites` are installed.  There are prerequisite PERL packages required for SUSE.  RHEL also requires Extra Packages for Enterprise Linux (EPEL) to be installed, which is also mentioned in prerequisites.  Be sure to install those first, then repeat your installation steps.

Refer to `ROCm Issue #1827 <https://github.com/ROCm/ROCm/issues/1827>`_. 

.. _troubleshooting-path:

Issue #3: PATH variable
============================

After successfully installing ROCm, when I run ``rocminfo`` (or another ROCm tool) the command is not found.

**Solution:** You may need to update your ``PATH`` environment variable as described in :doc:`../install/post-install`.

Refer to `ROCm Issue #1607 <https://github.com/ROCm/ROCm/issues/1607>`_.

.. _troubleshooting-cpp-libs:

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

.. _troubleshooting-install-missing-packages-for-dockers:

Issue #6: Additional packages for Docker installations
========================================================

Docker images often come with minimal installations, meaning some essential packages might be missing. When installing ROCm within a Docker container, you might need to install additional packages for a successful ROCm installation. Use the following commands to install the prerequisite packages.

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

      zypper install sudo wget SUSEConnect
      SUSEConnect -r <REGCODE>
      SUSEConnect -p sle-module-desktop-applications/15.5/x86_64
      SUSEConnect -p sle-module-development-tools/15.5/x86_64
      SUSEConnect -p PackageHub/15.5/x86_64

After installing these packages and :ref:`registering using your license for Enterprise Linux <register-enterprise-linux>` (if applicable), install ROCm following the :doc:`Quick start installation guide <../install/quick-start>` in your Docker container.

.. _troubleshooting-symlinks:

Issue #7: Installations using Python wheels (``.whl`` files) do not support soft links
======================================================================================

If you have installed ROCm or any ROCm component using a Python wheel (``.whl`` file), running
a ROCm command which is soft-linked will fail with ``not found`` on Ubuntu, ``bad interpreter: No such file or directory`` on SLES, and ``ModuleNotFoundError`` on RHEL. 

**Solution:** Python wheel files do not support soft links (symbolic links). You will need to run soft-linked commands from within their installation directories, or using the full path to their locations. 

For example, run ``rocm-smi`` on ROCm 6.2 in the following way:

.. code-block:: shell
    
  cd /opt/rocm-6.2.0/libexec/rocm_smi/ 
  python3 rocm_smi.py 

or 

.. code-block:: shell
    
  python3 /opt/rocm-6.2.0/libexec/rocm_smi/rocm_smi.py

See `Symbolic links in wheels <https://discuss.python.org/t/symbolic-links-in-wheels/1945>`_ for more information.
