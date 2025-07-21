.. meta::
  :description: User and kernel-space support matrix
  :keywords: Linux support, support matrix, system requirements, user space versions, kernel-mode GPU driver, KMD, AMD, ROCm

*****************************************************************************************
User and kernel-space support matrix
*****************************************************************************************

Starting from ROCm™ 6.4.0, forward and backward compatibility between the AMD Kernel-mode GPU Driver (KMD) and its user space software is provided up to a year apart (assuming hardware support is available in both). For earlier ROCm releases, the compatibility is provided for +/- 2 releases. This table shows the compatibility combinations that are currently supported.

.. note ::

  The tested user space versions in the following table are accurate as of the time of publication. For the most up-to-date information about AMD Kernel-mode GPU Driver (KMD) and tested user space versions, see the latest version of this table at `User and kernel-space support matrix <https://rocm.docs.amd.com/projects/install-on-linux/en/latest/reference/user-kernel-space-compat-matrix.html>`_.

.. csv-table::
  :widths: 30, 70
  :header: "KMD", "Tested user space versions"

    "6.4.x", "6.1.x, 6.2.x, 6.3.x, 6.4.x"
    "6.3.x", "6.1.x, 6.2.x, 6.3.x, 6.4.x"
    "6.2.x", "6.0.x, 6.1.x, 6.2.x, 6.3.x, 6.4.x"
    "6.1.x", "5.7.x, 6.0.x, 6.1.x, 6.2.x, 6.3.x, 6.4.x"
    "6.0.x", "5.6.x, 5.7.x, 6.0.x, 6.1.x, 6.2.x"
    "5.7.x", "5.5.x, 5.6.x, 5.7.x, 6.0.x, 6.1.x"
    "5.6.x", "5.4.x, 5.5.x, 5.6.x, 5.7.x, 6.0.x"
    "5.5.x", "5.3.x, 5.4.x, 5.5.x, 5.6.x, 5.7.x"
    "5.4.x", "5.2.x, 5.3.x, 5.4.x, 5.5.x, 5.6.x"
    "5.3.x", "5.1.x, 5.2.x, 5.3.x, 5.4.x, 5.5.x"
