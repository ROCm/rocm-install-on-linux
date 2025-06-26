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

.. note ::

  The tested user space versions in the following table are accurate as of the time of publication. For the most up-to-date information about AMD Kernel-mode GPU Driver (KMD) and tested user space versions, see the latest version of this table at `User and kernel-space support matrix <https://rocm.docs.amd.com/projects/install-on-linux/en/latest/reference/user-kernel-space-compat-matrix.html>`_.

.. csv-table::
  :widths: 30, 70
  :header: "KFD", "Tested user space versions"

    "5.0.2", "5.1.0, 5.2.0"
    "5.1.0", "5.0.2"
    "5.1.3", "5.2.0, 5.3.0"
    "5.2.0", "5.0.2, 5.1.3"
    "5.2.3", "5.3.0, 5.4.0"
    "5.3.0", "5.1.3, 5.2.3"
    "5.3.3", "5.4.0, 5.5.0"
    "5.4.0", "5.2.3, 5.3.3"
    "5.4.3", "5.5.0, 5.6.0"
    "5.4.4", "5.5.0"
    "5.5.0", "5.3.3, 5.4.3"
    "5.5.1", "5.6.0, 5.7.0"
    "5.6.0", "5.4.3, 5.5.1"
    "5.6.1", "5.7.0"
    "5.7.0", "5.5.0, 5.6.1"
    "5.7.1", "5.5.0, 5.6.1"
    "6.0.0", "5.6.1, 5.7.0"
