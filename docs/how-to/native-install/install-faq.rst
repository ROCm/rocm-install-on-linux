.. meta::
  :description: Frequently asked questions for install
  :keywords: Linux, install, FAQ, ubuntu, RHEL, SUSE, AMD, ROCm

.. _troubleshooting:

************************************************************************************
Installation Troubleshooting
************************************************************************************

Here are some of the frequently asked questions from some common issues people faced with ROCm.

**Problem #1:** When installing, I get "Problem: nothing provides 'perl-URI-Encode' needed to be installed by ..."

Refer to `Issue #1827 <https://github.com/ROCm/ROCm/issues/1827>`_ for additional details. 

**Solution:** Ensure that the :doc:`../prerequisites` are installed.  There are prerequisite PERL packages required for SUSE.  RHEL also requires EPEL to be installed, which is also mentioned in prerequisites.  Be sure to install those first, then repeat your installation steps.


**Problem #2:** When compiling HIP programs, I get a linking error for ``-lstdc++``, or "fatal error: 'cmath' file not found".

Refer to `Issue #2031 <https://github.com/ROCm/ROCm/issues/2031>`_

**Solution:** You can install C++ libraries using your package manager. The following is an Ubuntu example:

.. code-block:: bash

  sudo apt-get install libstdc++-12-dev


**Problem 3:** The latest version of ROCm is 6.0.2, but the install instructions install 6.0.0.

Refer to `Issue #2422 <https://github.com/ROCm/ROCm/issues/2422>`_

**Solution:** You may have used the quick-start installation method which only installs the latest major release. Use one of the other available installation methods:

* Quick-start installation - Installs latest **major** release (i.e. 6.0.0, or 6.1.0)
* Native package manager install method - Provides latest **major and minor** release (i.e. 6.0.0, 6.0.2)
* ``amdgpu-install`` method - Provides latest **major and minor** release (i.e. 6.0.0, 6.0.2)


**Problem 4:** After successfully installing ROCm, when I run ``rocminfo`` the command is not found.

Refer to `Issue #1607 <https://github.com/ROCm/ROCm/issues/1607>`_

**Solution:** You may need to update your ``PATH`` environment variable as described in :doc:`post-install`.


**Problem 5:** Running on a system with multiple GPUs the application hangs with the GPU use at 100%, but without the expected GPU temperature buildup

This issue often results in the following message in the application transcript: 
``NCCL WARN Missing "iommu=pt" from kernel command line which can lead to system instablity or hang!``

Refer to `RCCL Issue #1129 <https://github.com/ROCm/rccl/issues/1129>`_

**Solution:** To resolve this issue add ``iommu=pt`` to ``GRUB_CMDLINE_LINUX_DEFAULT`` in ``/etc/default/grub``. Then run ``sudo update-grub``. 

After rebooting use ``cat /proc/cmdline`` to see that it is added:

``BOOT_IMAGE=/vmlinuz-5.15.0-101-generic root=/dev/mapper/ubuntu--vg-ubuntu--lv ro iommu=pt``





