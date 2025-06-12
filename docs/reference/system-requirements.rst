.. meta::
  :description: System requirements for AMD ROCm
  :keywords: Linux support, ROCm distributions, system requirements, supported GPUs,  Instinct,
    Radeon PRO, Radeon, AMD, ROCm

.. _system-requirements:

**************************************************************************************
System requirements (Linux)
**************************************************************************************

.. |br| raw:: html

   <br>

Supported GPUs
=============================================

The following table shows the supported AMD Instinct™ accelerators, and Radeon™ PRO
and Radeon GPUs. If a GPU is not listed on this table, it's not officially supported by AMD.

Accelerators and GPUs listed in the following table support compute workloads (no display information or graphics). If you’re using ROCm with AMD Radeon or Radeon PRO GPUs for graphics workloads, see the `Use ROCm on Radeon GPU documentation <https://rocm.docs.amd.com/projects/radeon/en/latest/docs/compatibility.html>`_ to verify compatibility and system requirements.

.. tab-set::

  .. tab-item:: AMD Instinct

    .. csv-table::
      :widths: 50, 25, 25, 10
      :header: "Accelerator", "Architecture", "LLVM target", "Support"

      "AMD Instinct MI325X", "CDNA3", "gfx942", "✅ [#ub2204]_"
      "AMD Instinct MI300X", "CDNA3", "gfx942", "✅"
      "AMD Instinct MI300A", "CDNA3", "gfx942", "✅"
      "AMD Instinct MI250X", "CDNA2", "gfx90a", "✅"
      "AMD Instinct MI250", "CDNA2", "gfx90a", "✅"
      "AMD Instinct MI210", "CDNA2", "gfx90a", "✅"
      "AMD Instinct MI100", "CDNA", "gfx908", "✅"
      "AMD Instinct MI50", "GCN5.1", "gfx906", "❌"
      "AMD Instinct MI25", "GCN5.0", "gfx900", "❌"

  .. tab-item:: AMD Radeon PRO

    .. csv-table::
      :widths: 50, 25, 25, 10
      :header: "GPU", "Architecture", "LLVM target", "Support"

      "AMD Radeon AI PRO R9700", "RDNA4", "gfx1201", "✅ [#RDNA-OS]_"
      "AMD Radeon PRO V710", "RDNA3", "gfx1101", "✅"
      "AMD Radeon PRO W7900 Dual Slot", "RDNA3", "gfx1100", "✅"
      "AMD Radeon PRO W7900", "RDNA3", "gfx1100", "✅"
      "AMD Radeon PRO W7800 48GB", "RDNA3", "gfx1100", "✅"
      "AMD Radeon PRO W7800", "RDNA3", "gfx1100", "✅"
      "AMD Radeon PRO W7700", "RDNA3", "gfx1101", "✅  [#RDNA-OS]_"
      "AMD Radeon PRO W6800", "RDNA2", "gfx1030", "✅"
      "AMD Radeon PRO V620", "RDNA2", "gfx1030", "✅"
      "AMD Radeon PRO VII", "GCN5.1", "gfx906", "❌"

  .. tab-item:: AMD Radeon

    .. csv-table::
      :widths: 50, 25, 25, 10
      :header: "GPU", "Architecture", "LLVM target", "Support"

      "AMD Radeon RX 9070 XT", "RDNA4", "gfx1201", "✅ [#RDNA-OS]_"
      "AMD Radeon RX 9070 GRE", "RDNA4", "gfx1201", "✅ [#RDNA-OS]_"
      "AMD Radeon RX 9070", "RDNA4", "gfx1201", "✅ [#RDNA-OS]_"
      "AMD Radeon RX 9060 XT", "RDNA4", "gfx1200", "✅ [#RDNA-OS]_"
      "AMD Radeon RX 7900 XTX", "RDNA3", "gfx1100", "✅"
      "AMD Radeon RX 7900 XT", "RDNA3", "gfx1100", "✅"
      "AMD Radeon RX 7900 GRE", "RDNA3", "gfx1100", "✅ [#RDNA-OS]_"
      "AMD Radeon RX 7800 XT", "RDNA3", "gfx1101", "✅  [#RDNA-OS]_"
      "AMD Radeon VII", "GCN5.1", "gfx906", "❌"

✅: **Supported** - Official software distributions of the current ROCm release fully support this hardware.

⚠️: **Deprecated** - The current ROCm release has limited support for this hardware. Existing features and capabilities are maintained, but no new features or optimizations will be added. A future ROCm release will remove support.

❌: **Unsupported** - The current ROCm release does not support this hardware. The HIP runtime might continue to run applications for an unsupported GPU, but prebuilt ROCm libraries are not officially supported and will cause runtime errors.

.. important:: 

   Systems with multiple GPUs may require ``iommu=pt`` to be set at boot time to prevent application hangs, as described in
   :ref:`multi-gpu`.

.. note::

   See the :ref:`Compatibility matrix <rocm:architecture-support-compatibility-matrix>` for an overview
   of supported GPU architectures across ROCm releases.

.. _supported_distributions:

Supported operating systems
=============================================

AMD ROCm software supports the following Linux distributions.

.. csv-table::
    :widths: 50, 50, 25, 25
    :header: "Operating system", "Kernel", "Glibc", "Support"
    :escape: \

    "Ubuntu 24.04.2", "6.8 [GA], 6.11 [HWE]", "2.39", "✅"
    "Ubuntu 22.04.5", "5.15 [GA], 6.8 [HWE]", "2.35", "✅"
    "RHEL 9.6", "5.14+", "2.34", "✅"
    "RHEL 9.4", "5.14+", "2.34", "✅"
    "RHEL 8.10", "4.18.0+", "2.28", "✅"
    "SLES 15 SP6", "6.5.0+", "2.38", "✅"
    "Oracle Linux 9", "5.15.0 (UEK)", "2.35", "✅ [#mi300x]_"
    "Oracle Linux 8", "5.15.0 (UEK)", "2.28", "✅ [#mi300x]_"
    "Azure Linux 3.0", "6.6.60", "2.38", "✅ [#azurelinux]_"
    "Debian 12", "6.1", "2.36", "✅ [#single-node]_"
    

.. note::

  * See `Red Hat Enterprise Linux Release Dates <https://access.redhat.com/articles/3078>`_ to learn about the specific kernel versions supported on Red Hat Enterprise Linux (RHEL).
  * See `List of SUSE Linux Enterprise Server kernel <https://www.suse.com/support/kb/doc/?id=000019587>`_ to learn about the specific kernel version supported on SUSE Linux Enterprise Server (SLES).
  * See the :doc:`rocm:compatibility/compatibility-matrix` for an overview of OS support across ROCm releases.

Virtualization support
======================

ROCm supports virtualization for the Instinct accelerators and Radeon PRO GPUs listed in the following table.

.. raw:: html

   <div class="pst-scrollable-table-container">
     <table class="table">
       <thead>
         <tr class="row-odd">
           <th class="head">
             <p>GPU</p>
           </th>
           <th class="head">
             <p>Hypervisor</p>
           </th>
           <th class="head">
             <p>Virtualization technology</p>
           </th>
           <th class="head">
             <p>Host OS and version</p>
           </th>
           <th class="head">
             <p>Guest OS</p>
           </th>
         </tr>
       </thead>
       <style>
         tbody#virtualization-support-instinct tr:last-child {
           border-bottom: 2px solid var(--pst-color-primary);
         }
       </style>
       <tbody id="virtualization-support-instinct">
         <tr class="row-even">
           <td>
             <p>MI325X</p>
           </td>
           <td>
             <p>KVM</p>
           </td>
           <td>
             <p>SRIOV</p>
           </td>
           <td>
             <p>Ubuntu 22.04</p>
           </td>
           <td>
             <p>Ubuntu 22.04</p>
           </td>
         </tr>
         <tr class="row-odd">
           <td rowspan="3">
             <p>MI300X</p>
           </td>
           <td>
             <p>Hyper-V</p>
           </td>
           <td>
             <p>SRIOV</p>
           </td>
           <td>
             <p>Azure Host 2021</p>
           </td>
           <td>
             <p>Ubuntu 22.04</p>
           </td>
         </tr>
         <tr class="row-even">
           <td>
             <p>KVM</p>
           </td>
           <td>
             <p>SRIOV</p>
           </td>
           <td>
             <p>Ubuntu 22.04</p>
           </td>
           <td>
             <p>Ubuntu 22.04</p>
           </td>
         </tr>
         <tr class="row-odd">
           <td>
             <p>KVM</p>
           </td>
           <td>
             <p>Passthrough</p>
           </td>
           <td>
             <p>Ubuntu 22.04</p>
           </td>
           <td>
             <p>Ubuntu 22.04</p>
           </td>
         </tr>
         <tr class="row-even">
           <td>
             <p>MI250</p>
           </td>
           <td>
             <p>Hyper-V</p>
           </td>
           <td>
             <p>DDA</p>
           </td>
           <td>
             <p>Azure Host 2021</p>
           </td>
           <td>
             <p>Ubuntu 22.04</p>
           </td>
         </tr>
         <tr class="row-odd">
           <td>
             <p>MI210</p>
           </td>
           <td>
             <p>KVM</p>
           </td>
           <td>
             <p>SRIOV</p>
           </td>
           <td>
             <p>RHEL 9.4</p>
           </td>
           <td>
             <p>Ubuntu 22.04, RHEL 9.4</p>
           </td>
         </tr>
         </tbody>
         <tbody id="virtualization-support-radeon-pro>
         <tr class="row-even">
           <td rowspan="2">
             <p>V710</p>
           </td>
           <td>
             <p>KVM</p>
           </td>
           <td>
             <p>SRIOV</p>
           </td>
           <td>
             <p>Ubuntu 24.04</p>
           </td>
           <td>
             <p>Ubuntu 24.04</p>
           </td>
         </tr>
         <tr class="row-odd">
           <td>
             <p>Hyper-V</p>
           </td>
           <td>
             <p>SRIOV</p>
           </td>
           <td>
             <p>Azure Host 2024</p>
           </td>
           <td>
             <p>Ubuntu 24.04</p>
           </td>
         </tr>
         <tr class="row-even">
           <td>
             <p>V620</p>
           </td>
           <td>
             <p>Hyper-V</p>
           </td>
           <td>
             <p>SRIOV</p>
           </td>
           <td>
             <p>Azure Host 2024</p>
           </td>
           <td>
             <p>Ubuntu 24.04</p>
           </td>
         </tr>
       </tbody>
     </table>
   </div>

.. note::

   These virtualization technologies are designed to dedicate entire GPUs to
   individual virtual machines (VMs), rather than allowing a single GPU to be
   shared across multiple VMs.

CPU support
=============================================

ROCm requires CPUs that support PCIe™ atomics. Modern CPUs after the release of
1st generation AMD Zen CPU and Intel™ Haswell support PCIe atomics.

.. rubric:: Footnotes

.. [#ub2204] AMD Instinct MI325X is supported only on Ubuntu 22.04 [GA Kernel 5.15].
.. [#mi300x] Oracle Linux 8 and 9 are supported only on AMD Instinct MI300X.
.. [#azurelinux] Azure Linux 3.0 is supported only on AMD Instinct MI300X and AMD Radeon PRO V710.
.. [#single-node] Debian 12 is supported only on AMD Instinct MI300X for single-node functionality. 
.. [#RDNA-OS] Radeon AI PRO R9700, Radeon RX 9070, Radeon RX 9070 GRE, Radeon RX 9070 XT, Radeon RX 9060 XT, Radeon PRO W7700, and Radeon RX 7800 XT are supported only on Ubuntu 24.04.2, Ubuntu 22.04.5, RHEL 9.6, and RHEL 9.4.
