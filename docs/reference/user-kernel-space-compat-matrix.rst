.. meta::
  :description: User and kernel-space support matrix
  :keywords: Linux support, support matrix, system requirements, user space versions, kernel-mode GPU driver, KMD, AMD, ROCm

*****************************************************************************************
User and kernel-space support matrix
*****************************************************************************************

Starting from ROCm™ 6.4.0, forward and backward compatibility between the AMD Kernel-mode GPU Driver (KMD) and its user space software is provided up to a year apart (assuming hardware support is available in both). For earlier ROCm releases, the compatibility is provided for +/- 2 releases. This table shows the compatibility combinations that are currently supported.

.. csv-table::
  :widths: 30, 70
  :header: "KMD", "Tested user space versions"

    "6.4.x", "6.1.x, 6.2.x, 6.3.x, 6.4.x"
    "6.3.x", "6.1.x, 6.2.x, 6.3.x, 6.4.x"
    "6.2.x", "6.0.x, 6.1.x, 6.2.x, 6.3.x"
    "6.1.x", "5.7.x, 6.0.x, 6.1.x, 6.2.x, 6.3.x"
    "6.0.x", "5.6.x, 5.7.x, 6.0.x, 6.1.x, 6.2.x"
    "5.7.x", "5.5.x, 5.6.x, 5.7.x, 6.0.x, 6.1.x"
    "5.6.x", "5.4.x, 5.5.x, 5.6.x, 5.7.x, 6.0.x"
    "5.5.x", "5.3.x, 5.4.x, 5.5.x, 5.6.x, 5.7.x"
    "5.4.x", "5.2.x, 5.3.x, 5.4.x, 5.5.x, 5.6.x"
    "5.3.x", "5.1.x, 5.2.x, 5.3.x, 5.4.x, 5.5.x"
