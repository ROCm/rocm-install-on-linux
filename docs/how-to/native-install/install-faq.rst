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

