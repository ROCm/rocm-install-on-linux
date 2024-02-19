.. meta::
  :description: Linux GPU and OS support
  :keywords: Linux support, ROCm distributions, system requirements, supported GPUs,  Instinct,
    Radeon PRO, Radeon, AMD, ROCm

.. _system-requirements:

**************************************************************************************
System requirements (Linux)
**************************************************************************************

Supported GPUs
=============================================

The following table shows the supported GPUs for Instinct™, Radeon™ PRO and Radeon™. If a
GPU is not listed on this table, It's not officially supported by AMD.

.. tab-set::

  .. tab-item:: AMD Instinct

    .. csv-table::
      :widths: 50, 25, 25, 10
      :header: "GPU", "Architecture", "LLVM target", "Support"

      "AMD Instinct MI300X", "CDNA3", "gfx942", "✅"
      "AMD Instinct MI300A", "CDNA3", "gfx942", "✅ :sup:`1`"
      "AMD Instinct MI250X", "CDNA2", "gfx90a", "✅"
      "AMD Instinct MI250", "CDNA2", "gfx90a", "✅"
      "AMD Instinct MI210", "CDNA2", "gfx90a", "✅"
      "AMD Instinct MI100", "CDNA", "gfx908", "✅"
      "AMD Instinct MI50", "GCN5.1", "gfx906", "⚠️"
      "AMD Instinct MI25", "GCN5.0", "gfx900", "❌"

  .. tab-item:: AMD Radeon PRO

    .. csv-table::
      :widths: 50, 25, 25, 10
      :header: "GPU", "Architecture", "LLVM target", "Support"

      "AMD Radeon PRO W7900", "RDNA3", "gfx1100", "✅"
      "AMD Radeon PRO W7800", "RDNA3", "gfx1100", "✅"
      "AMD Radeon PRO W6800", "RDNA2", "gfx1030", "✅"
      "AMD Radeon PRO V620", "RDNA2", "gfx1030", "✅"
      "AMD Radeon PRO VII", "GCN5.1", "gfx906", "✅"

  .. tab-item:: AMD Radeon

    .. csv-table::
      :widths: 50, 25, 25, 10
      :header: "GPU", "Architecture", "LLVM target", "Support"

      "AMD Radeon RX 7900 XTX", "RDNA3", "gfx1100", "✅"
      "AMD Radeon RX 7900 XT", "RDNA3", "gfx1100", "✅"
      "AMD Radeon RX 7900 GRE", "RDNA3", "gfx1100", "✅"
      "AMD Radeon VII", "GCN5.1", "gfx906", "✅"

✅: **Supported** - AMD enables these GPUs in our software distributions for the corresponding
ROCm product.

⚠️: **Deprecated** - Support will be removed in a future release.

❌: **Unsupported** - This configuration is not enabled in our software distributions.

:sup:`1` MI300A is currently not officially supported on RHEL 9.x. This will be added on a later date.

.. _supported_distributions:

Supported operating systems
=============================================

AMD ROCm™ Software supports the following Linux distributions.

.. csv-table::
    :widths: 50, 50, 25
    :header: "OS", "Kernel", "Support"

    "RHEL 9.3", "5.14.0-362", "✅"
    "RHEL 9.2", "5.14.0-362", "✅"
    "RHEL 8.9", "4.18-513", "✅"
    "RHEL 8.8", "4.18-513", "✅"
    "CentOS 7.9", "3.10", "✅"
    "SLES 15 SP5", "5.14.21-150500", "✅"
    "SLES 15 SP4", "5.14.21-150500", "✅"
    "Ubuntu 22.04.4", "6.6", "✅ :sup:`2`"
    "Ubuntu 22.04.3", "6.2", "✅"
    "Ubuntu 22.04.2", "5.19", "✅"
    "Ubuntu 20.04.6", "5.15", "✅"
    "Ubuntu 20.04.5", "5.15", "✅"
    "Ubuntu 22.04.3", "5.15.133.1-microsoft-standard-WSL2", "🚧 :sup:`3`"

🚧: **Preview** - This configuration is under development and is released for preview purposes.

:sup:`2` Preview support for HWE kernels

:sup:`3` Preview support for device access in WSL2 and Docker Desktop for Windows.

Virtualization support
=============================================

ROCm supports virtualization for select GPUs only as shown below.

.. csv-table::
    :widths: 50, 25, 25, 50
    :header: "Hypervisor", "Version", "GPU", "Validated guest OS (kernel)"

    "VMWare", "ESXI 8", "MI250", "Ubuntu 20.04 (5.15.0)"
    "VMWare", "ESXI 8", "MI210", "Ubuntu 20.04 (5.15.0), SLES 15 SP4 (5.14.21)"
    "VMWare", "ESXI 7", "MI210", "Ubuntu 20.04 (5.15.0), SLES 15 SP4 (5.14.21)"

CPU support
=============================================

ROCm requires CPUs that support PCIe™ atomics. Modern CPUs after the release of
1st generation AMD Zen CPU and Intel™ Haswell support PCIe atomics.
