.. meta::
  :description: User and kernel-space support matrix

  :keywords: Linux support, support matrix, system requirements, user space versions, Kernel Fusion
    Driver , AMD, ROCm

*****************************************************************************************
User and kernel-space support matrix
*****************************************************************************************

ROCm™ provides forward and backward compatibility between the Kernel Fusion
Driver (KFD) and its user space software for +/- 2 releases. This table shows
the compatibility combinations that are currently supported.

.. csv-table::
  :widths: 30, 70
  :header: "KFD", "Tested user space versions"

    "6.2.x", "6.0.x, 6.1.x"
    "6.1.x", "5.7.x, 6.0.x, 6.2.x"
    "6.0.x", "5.6.x, 5.7.x, 6.1.x, 6.2.x"
    "5.7.x", "5.5.x, 5.6.x, 6.0.x, 6.1.x"
    "5.6.x", "5.4.x, 5.5.x, 5.7.x, 6.0.x"
    "5.5.x", "5.3.x, 5.4.x, 5.6.x, 5.7.x"
    "5.4.x", "5.2.x, 5.3.x, 5.5.x, 5.6.x"
    "5.3.x", "5.1.x, 5.2.x, 5.4.x, 5.5.x"
