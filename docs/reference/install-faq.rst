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
* :doc:`Native package manager install method <../install/install-methods/package-manager-index>` - Installs the specified *major and minor* release version (i.e. 6.0.0, 6.0.2)

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

  sudo apt-get install libstdc++-<gcc-version>-dev

For more information on how to determine the relevant ``gcc-version``, refer to `ROCm Issue #1843 <https://github.com/ROCm/ROCm/issues/1843#issuecomment-1813746898>`_.

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
      apt install sudo wget gpg

  .. tab-item:: Debian

    .. code-block:: shell

      apt update
      apt install sudo wget gpg

  .. tab-item:: Red Hat Enterprise Linux

    .. code-block:: shell

      dnf install sudo wget

  .. tab-item:: Oracle Linux

    .. code-block:: shell

      dnf install sudo wget

  .. tab-item:: SUSE Linux Enterprise Server

    .. code-block:: shell

      zypper install sudo wget SUSEConnect awk

  .. tab-item:: Rocky Linux

    .. code-block:: shell

      dnf install sudo wget

After installing these packages, install ROCm using the :doc:`Quick start installation guide <../install/quick-start>` in your Docker container.

.. _troubleshooting-symlinks:

Issue #7: Installations using Python wheels (.whl files) do not support soft links
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

.. _troubleshooting-denylist:

Issue #8: The AMDGPU driver is not loaded after installation
======================================================================================

When you are verifying the ROCm installation according to the :doc:`post-install instructions <../install/post-install>`,
the ``rocm-smi`` and ``rocminfo`` commands might fail with the error message
``Driver not initialized`` or not display any output. This could indicate
the AMDGPU driver is not loaded.

**Solution:** Ensure the AMDGPU driver is not on a denylist such as ``/etc/modprobe.d/blacklist-amdgpu.conf``.
The location of this file might vary depending on the system distribution and version.
To verify whether the driver is on a denylist, use the following command:

.. code-block:: shell

   grep amdgpu /etc/modprobe.d/*

.. note::

   When installing the AMDGPU driver with Secure Boot enabled, you must sign ``amdgpu-dkms`` to prevent potential system loading issues. 
   For more information, see `Secure Boot Support <https://amdgpu-install.readthedocs.io/en/latest/install-installing.html#secure-boot-support>`_. 
   If you prefer not to sign the AMDGPU driver, you can disable Secure Boot from the BIOS settings instead.

.. _troubleshooting-group-membership:

Issue #9: Cannot access the AMD GPU after installation
======================================================================================

If the group permissions are not set properly during ROCm installation,
you might get an error similar to ``Permission denied`` when attempting to access the AMD GPU.

**Solution:** You must be part of the ``video`` and ``render`` groups to access the AMD GPU.
To learn how to add an account to these groups, see :ref:`group_permissions`.

Issue #10: ROCm debugging tools might become unresponsive in SELinux-enabled distributions
===========================================================================================

Red Hat Enterprise Linux (RHEL) and related distributions automatically enable a security feature named Security-Enhanced Linux (SELinux) that may prevent ROCm debugging tools like ROCgdb, ROCdbgapi, and ROCR Debug Agent from working correctly.
 
The problem occurs when attempting to debug a program that contains code that runs on the GPU. The debugging session may become unresponsive while attempting to reach a breakpoint or doing instruction-stepping in device code. ROCgdb will still be responsive and accept interruption by pressing ``Control+C``, but the breakpoint in device code won't be hit, and the instruction-stepping operation will not conclude.
 
The ROCR Debug Agent might also become unresponsive when attempting to capture data from a program that is running into queue errors, memory faults, and other triggering events.
 
As a workaround for this problem, either disable SELinux or configure it to use the permissive setting.
 
While ROCgdb or ROCR Debug Agent are being used, setting SELinux to permissive can be accomplished with the following command:

.. code-block:: shell

  sudo setenforce 0

After the session is over, it can be switched back to enforcing mode:

.. code-block:: shell

  sudo setenforce 1

.. note::

  Changing the SELinux settings can have security implications. Ensure you review your system security settings before making any changes.

