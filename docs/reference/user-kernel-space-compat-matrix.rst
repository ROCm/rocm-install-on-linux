*****************************************************************************************
User/kernel-space support matrix
*****************************************************************************************

ROCm™ provides forward and backward compatibility between the Kernel Fusion
Driver (KFD) and its user space software for +/- 2 releases. This table shows
the compatibility combinations that are currently supported.

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
