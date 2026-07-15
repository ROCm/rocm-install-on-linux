.. meta::
  :description: User and AMD GPU Driver (amdgpu) support matrix
  :keywords: Linux support, support matrix, system requirements, user space versions, kernel-mode GPU driver, KMD, AMD, ROCm

.. raw:: html

   <meta http-equiv="refresh" content="0; url=https://rocm.docs.amd.com/en/latest/compatibility/compatibility-matrix.html">

$$$$$$$$$$$$$$
Redirecting...
$$$$$$$$$$$$$$

.. important::

   This page has moved! Go to `<https://rocm.docs.amd.com/en/latest/compatibility/compatibility-matrix.html>`__ for the latest compatibility information.

*****************************************************************************************
User and AMD GPU Driver (amdgpu) support matrix
*****************************************************************************************

The `AMD GPU Driver (amdgpu) <https://instinct.docs.amd.com/projects/amdgpu-docs/en/docs-30.30.4/>`__ is distributed separately from the ROCm software stack and is stored under in its own location ``/amdgpu/`` in the package repository at `repo.radeon.com <https://repo.radeon.com/amdgpu/>`_. Starting from ROCm 6.4.0, forward and backward compatibility between the AMD GPU Driver (amdgpu) and its user space software is provided up to a year apart (assuming hardware support is available in both). For earlier ROCm releases, the compatibility is provided for +/- 2 releases. This table shows the compatibility combinations that are currently supported.

.. note ::

   This compatibility window applies to most ROCm components; tools like
   :doc:`AMD SMI <amdsmi:index>` can have tighter dependencies on the amdgpu
   driver version since it reads GPU telemetry directly via the amdgpu kernel
   driver.

.. csv-table::
  :widths: 30, 70
  :header: "AMD GPU Driver (amdgpu)", "Supported user space versions"

    "30.30.x", "6.3.x, 6.4.x, 7.0.x, 7.1.x, 7.2.x"
    "30.20.x", "6.3.x, 6.4.x, 7.0.x, 7.1.x, 7.2.x"
    "30.10.x", "6.2.x, 6.3.x, 6.4.x, 7.0.x, 7.1.x, 7.2.x"
    "6.4.x", "6.1.x, 6.2.x, 6.3.x, 6.4.x, 7.0.x, 7.1.x, 7.2.x"
    "6.3.x", "6.1.x, 6.2.x, 6.3.x, 6.4.x, 7.0.x"
    "6.2.x", "6.0.x, 6.1.x, 6.2.x, 6.3.x, 6.4.x, 7.0.x"
    "6.1.x", "5.7.x, 6.0.x, 6.1.x, 6.2.x, 6.3.x, 6.4.x"
    "6.0.x", "5.6.x, 5.7.x, 6.0.x, 6.1.x, 6.2.x"
    "5.7.x", "5.5.x, 5.6.x, 5.7.x, 6.0.x, 6.1.x"
    "5.6.x", "5.4.x, 5.5.x, 5.6.x, 5.7.x, 6.0.x"
    "5.5.x", "5.3.x, 5.4.x, 5.5.x, 5.6.x, 5.7.x"
    "5.4.x", "5.2.x, 5.3.x, 5.4.x, 5.5.x, 5.6.x"
    "5.3.x", "5.1.x, 5.2.x, 5.3.x, 5.4.x, 5.5.x"
