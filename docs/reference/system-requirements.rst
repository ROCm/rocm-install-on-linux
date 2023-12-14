.. _system-requirements:

**************************************************************************************
System requirements
**************************************************************************************

Supported GPUs
=============================================

The table below shows supported GPUs for Instinct™, Radeon Pro™ and Radeon™ GPUs.
Please click the tabs below to switch between GPU product lines.
If a GPU is not listed on this table, the GPU is not officially supported by AMD.

.. tab-set::

    .. tab-item:: AMD Instinct™

        .. list-table::
            :widths: 50 25 25 10
            :header-rows: 1

            * - GPU
              - Architecture
              - LLVM Target
              - Support

            * - AMD Instinct™ MI300X
              - CDNA3
              - gfx940
              - ✅
            * - AMD Instinct™ MI300A
              - CDNA3
              - gfx940
              - ✅ [#]_

            * - AMD Instinct™ MI250X
              - CDNA2
              - gfx90a
              - ✅
            * - AMD Instinct™ MI250
              - CDNA2
              - gfx90a
              - ✅
            * - AMD Instinct™ MI210
              - CDNA2
              - gfx90a
              - ✅

            * - AMD Instinct™ MI100
              - CDNA
              - gfx908
              - ✅

            * - AMD Instinct™ MI50
              - GCN5.1
              - gfx906
              - ⚠️
            * - AMD Instinct™ MI25
              - GCN5.0
              - gfx900
              - ❌

    .. tab-item:: AMD Radeon Pro™

        .. list-table::
            :widths: 50 25 25 10
            :header-rows: 1

            * - GPU
              - Architecture
              - LLVM Target
              - Support

            * - AMD Radeon™ Pro W7900
              - RDNA3
              - gfx1100
              - ✅
            * - AMD Radeon™ Pro W6800
              - RDNA3
              - gfx1030
              - ✅
            * - AMD Radeon™ Pro V620
              - RDNA2
              - gfx1030
              - ✅
            * - AMD Radeon™ Pro VII
              - RDNA2
              - GCN5.1
              - ✅

    .. tab-item:: AMD Radeon™

        .. list-table::
            :widths: 50 25 25 10
            :header-rows: 1

            * - GPU
              - Architecture
              - LLVM Target
              - Support

            * - AMD Radeon™ RX 7900 XTX
              - RDNA3
              - gfx1100
              - ✅
            * - AMD Radeon™ VII
              - GCN5.1
              - gfx906
              - ✅

Support status:

✅: **Supported** - AMD enables these GPUs in our software distributions for the corresponding ROCm product.
⚠️: **Deprecated** - Support will be removed in a future release.
❌: **Unsupported** - This configuration is not enabled in our software distributions.

.. [#]
    MI300A is currently not officially supported on RHEL 9.x.
    This will be added on a later date.  

Supported operating systems
=============================================

AMD ROCm™ Software supports the following Linux distributions.

.. list-table::
    :widths: 50 50 25
    :header-rows: 1

    * - OS
      - Kernel
      - Support

    * - RHEL 9.3
      - 5.14
      - ✅
    * - RHEL 9.2
      - 5.14
      - ✅

    * - RHEL 8.9
      - 4.18
      - ✅
    * - RHEL 8.8
      - 4.18
      - ✅

    * - CentOS 7.9
      - 3.10
      - ✅

    * - SLES 15 SP5
      - 5.14
      - ✅
    * - SLES 15 SP4
      - 5.14
      - ✅

    * - Ubuntu 22.04.3
      - 5.19
      - ✅
    * - Ubuntu 22.04.2
      - 5.19
      - ✅

    * - Ubuntu 20.04.6
      - 5.15
      - ✅
    * - Ubuntu 20.04.5
      - 5.15
      - ✅

Virtualization support
=============================================

ROCm supports virtualization for select GPUs only as shown below.

.. list-table::
    :widths: 50 25 25 50
    :header-rows: 1

    * - Hypervisor
      - Version
      - GPU
      - Validated Guest OS (Kernel)

    * - VMWare
      - ESXI 8
      - MI250
      - Ubuntu 20.04 (5.15.0)

    * - VMWare
      - ESXI 8
      - MI210
      - Ubuntu 20.04 (5.15.0), SLES 15 SP4 (5.14.21)

    * - VMWare
      - ESXI 7
      - MI210
      - Ubuntu 20.04 (5.15.0), SLES 15 SP4 (5.14.21)

CPU support
=============================================

ROCm requires CPUs that support PCIe™ atomics. Modern CPUs after the release of
1st generation AMD Zen CPU and Intel™ Haswell support PCIe atomics.
