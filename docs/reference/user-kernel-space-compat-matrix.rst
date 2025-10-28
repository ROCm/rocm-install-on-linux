.. meta::
  :description: User and AMD GPU Driver (amdgpu) support matrix
  :keywords: Linux support, support matrix, system requirements, user space versions, kernel-mode GPU driver, KMD, AMD, AMD GPU Driver (amdgpu), ROCm

*****************************************************************************************
User and AMD GPU Driver (amdgpu) support matrix
*****************************************************************************************

The AMD GPU Driver (amdgpu) is now distributed separately from the ROCm software stack and is stored under in its own location ``/amdgpu/`` in the package repository at `repo.radeon.com <https://repo.radeon.com/amdgpu/>`_. The first release was designated as AMD GPU Driver (amdgpu) version 30.10. Starting from ROCm™ 6.4.0, forward and backward compatibility between the AMD GPU Driver (amdgpu) and its user space software is provided up to a year apart (assuming hardware support is available in both). For earlier ROCm releases, the compatibility is provided for +/- 2 releases. This table shows the compatibility combinations that are currently supported.

.. note ::

  The supported user space versions in the following table are accurate as of the time of publication. For the most up-to-date information about AMD GPU Driver (amdgpu) and supported user space versions, see the latest version of this table at `User and AMD GPU Driver (amdgpu) support matrix <https://rocm.docs.amd.com/projects/install-on-linux/en/latest/reference/user-kernel-space-compat-matrix.html>`_.

.. csv-table::
  :widths: 30, 70
  :header: "AMD GPU Driver (amdgpu)", "Supported user space versions"

    "30.10", "6.2.x, 6.3.x, 6.4.x, 7.0.x"
    "6.4.x", "6.1.x, 6.2.x, 6.3.x, 6.4.x, 7.0.x"
    "6.3.x", "6.1.x, 6.2.x, 6.3.x, 6.4.x, 7.0.x"
    "6.2.x", "6.0.x, 6.1.x, 6.2.x, 6.3.x, 6.4.x, 7.0.x"
    "6.1.x", "5.7.x, 6.0.x, 6.1.x, 6.2.x, 6.3.x, 6.4.x"
    "6.0.x", "5.6.x, 5.7.x, 6.0.x, 6.1.x, 6.2.x"
    "5.7.x", "5.5.x, 5.6.x, 5.7.x, 6.0.x, 6.1.x"
    "5.6.x", "5.4.x, 5.5.x, 5.6.x, 5.7.x, 6.0.x"
    "5.5.x", "5.3.x, 5.4.x, 5.5.x, 5.6.x, 5.7.x"
    "5.4.x", "5.2.x, 5.3.x, 5.4.x, 5.5.x, 5.6.x"
    "5.3.x", "5.1.x, 5.2.x, 5.3.x, 5.4.x, 5.5.x"

.. note::

    For AZL, the latest amdgpu version supported is from the ROCm 6.2.2 release.