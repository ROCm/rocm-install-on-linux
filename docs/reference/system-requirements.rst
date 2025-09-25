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

Accelerators and GPUs listed in the following table support compute workloads (no display information or graphics). If you’re using ROCm with AMD Radeon GPUs or Ryzen APUs for graphics workloads, see the `Use ROCm on Radeon and Ryzen <https://rocm.docs.amd.com/projects/radeon-ryzen/en/latest/index.html>`_ documentation to verify compatibility and system requirements.

.. tab-set::

  .. tab-item:: AMD Instinct

    .. csv-table::
      :widths: 50, 25, 25, 25, 10
      :header: "Accelerator", "Series", "Architecture", "LLVM target", "Support"

      "AMD Instinct MI355X", "MI350", "CDNA4", "gfx950", "✅ [#mi350x-os]_"
      "AMD Instinct MI350X", "MI350", "CDNA4", "gfx950", "✅ [#mi350x-os]_"
      "AMD Instinct MI325X", "MI300", "CDNA3", "gfx942", "✅ [#mi325x-os]_"
      "AMD Instinct MI300X", "MI300", "CDNA3", "gfx942", "✅ [#mi300x-os]_"
      "AMD Instinct MI300A", "MI300", "CDNA3", "gfx942", "✅ [#mi300A-os]_"
      "AMD Instinct MI250X", "MI200", "CDNA2", "gfx90a", "✅ [#mi200x-os]_"
      "AMD Instinct MI250", "MI200", "CDNA2", "gfx90a", "✅ [#mi200x-os]_"
      "AMD Instinct MI210", "MI200", "CDNA2", "gfx90a", "✅ [#mi200x-os]_"
      "AMD Instinct MI100", "MI100", "CDNA", "gfx908", "✅ [#mi100-os]_"
      "AMD Instinct MI50", "N/A", "GCN5.1", "gfx906", "❌"
      "AMD Instinct MI25", "N/A", "GCN5.0", "gfx900", "❌"

  .. tab-item:: AMD Radeon PRO

    .. csv-table::
      :widths: 50, 25, 25, 10
      :header: "GPU", "Architecture", "LLVM target", "Support"

      "AMD Radeon AI PRO R9700", "RDNA4", "gfx1201", "✅ [#RDNA-OS]_"
      "AMD Radeon PRO V710", "RDNA3", "gfx1101", "✅ [#rd-v710]_"
      "AMD Radeon PRO W7900 Dual Slot", "RDNA3", "gfx1100", "✅ [#RDNA-OS]_"
      "AMD Radeon PRO W7900", "RDNA3", "gfx1100", "✅ [#RDNA-OS]_"
      "AMD Radeon PRO W7800 48GB", "RDNA3", "gfx1100", "✅ [#RDNA-OS]_"
      "AMD Radeon PRO W7800", "RDNA3", "gfx1100", "✅ [#RDNA-OS]_"
      "AMD Radeon PRO W7700", "RDNA3", "gfx1101", "✅ [#RDNA-OS]_"
      "AMD Radeon PRO W6800", "RDNA2", "gfx1030", "✅ [#RDNA-OS]_"
      "AMD Radeon PRO V620", "RDNA2", "gfx1030", "✅ [#rd-v620]_"
      "AMD Radeon PRO VII", "GCN5.1", "gfx906", "❌"

  .. tab-item:: AMD Radeon

    .. csv-table::
      :widths: 50, 25, 25, 10
      :header: "GPU", "Architecture", "LLVM target", "Support"

      "AMD Radeon RX 9070 XT", "RDNA4", "gfx1201", "✅ [#RDNA-OS]_"
      "AMD Radeon RX 9070 GRE", "RDNA4", "gfx1201", "✅ [#RDNA-OS]_"
      "AMD Radeon RX 9070", "RDNA4", "gfx1201", "✅ [#RDNA-OS]_"
      "AMD Radeon RX 9060 XT", "RDNA4", "gfx1200", "✅ [#RDNA-OS]_"
      "AMD Radeon RX 7900 XTX", "RDNA3", "gfx1100", "✅ [#RDNA-OS]_"
      "AMD Radeon RX 7900 XT", "RDNA3", "gfx1100", "✅ [#RDNA-OS]_"
      "AMD Radeon RX 7900 GRE", "RDNA3", "gfx1100", "✅ [#RDNA-OS]_"
      "AMD Radeon RX 7800 XT", "RDNA3", "gfx1101", "✅ [#RDNA-OS]_"
      "AMD Radeon RX 7700 XT", "RDNA3", "gfx1101", "✅ [#RDNA-OS]_"
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

.. rubric:: Footnotes

.. [#mi350x-os] AMD Instinct MI355X and MI350X GPUs are only supported on Ubuntu 24.04.3, Ubuntu 22.04.5, RHEL 9.6, RHEL 9.4, and Oracle Linux 9.
.. [#mi325x-os] AMD Instinct MI325X GPU is only supported on Ubuntu 24.04.3, Ubuntu 22.04.5, RHEL 9.6, and RHEL 9.4.
.. [#mi300x-os] AMD Instinct MI300X GPU is supported on all below listed :ref:`supported_distributions`.
.. [#mi300A-os] AMD Instinct MI300A GPU is supported only on Ubuntu 24.04, Ubuntu 22.04, RHEL 9.6, RHEL 9.4, RHEL 8.10, SLES 15 SP7, Debian 12, and Rocky Linux 9.
.. [#mi200x-os] AMD Instinct MI200 Series GPUs are supported only on Ubuntu 24.04, Ubuntu 22.04, RHEL 9.6, RHEL 9.4, RHEL 8.10, SLES 15 SP7, and Debian 12.
.. [#mi100-os] AMD Instinct MI100 GPU is only supported on Ubuntu 24.04.3, Ubuntu 22.04.5, RHEL 9.6, RHEL 9.4, and RHEL 8.10.
.. [#RDNA-OS] AMD Radeon PRO ( AI PRO R9700, PRO W7900 Dual Slot, PRO W7900, PRO W7800 48GB, PRO W7800, PRO W7700, PRO W6800)  and AMD Radeon (RX 9070 XT, RX 9070 GRE, RX 9070, RX 9060 XT, RX 7900 XTX, RX 7900 XT, RX 7900 GRE, RX 7800 XT, and RX 7700 XT) are only supported on Ubuntu 24.04.3, Ubuntu 22.04.5, and RHEL 9.6.
.. [#rd-v710] AMD Radeon PRO V710 is only supported on Ubuntu 24.04.3, Ubuntu 22.04.5, RHEL 9.6, and Azure Linux 3.0.
.. [#rd-v620] AMD Radeon PRO V620 is only supported on Ubuntu 24.04.3 and Ubuntu 22.04.5.

.. _supported_distributions:

Supported operating systems
=============================================

AMD ROCm software supports the following Linux distributions.

.. csv-table::
    :widths: 50, 50, 25, 25
    :header: "Operating system", "Kernel", "Glibc", "Support"
    :escape: \

    "Ubuntu 24.04.3", "6.8 [GA], 6.14 [HWE]", "2.39", "✅"
    "Ubuntu 22.04.5", "5.15 [GA], 6.8 [HWE]", "2.35", "✅"
    "RHEL 9.6", "5.14.0-570", "2.34", "✅"
    "RHEL 9.4", "5.14.0-427", "2.34", "✅"
    "RHEL 8.10", "4.18.0-553", "2.28", "✅ [#rhel-700]_"
    "SLES 15 SP7", "6.4.0-150700.51", "2.38", "✅ [#sles-db-700]_"
    "Debian 12", "6.1.0", "2.36", "✅ [#sles-db-700]_"
    "Rocky Linux 9", "5.14.0-570", "2.34", "✅ [#rl-700]_"
    "Azure Linux 3.0", "6.6.60", "2.38", "✅ [#al-mi300x]_"
    "Oracle Linux 9", "5.15.0 (UEK)", "2.34", "✅ [#ol-700]_"
    "Oracle Linux 8", "5.15.0 (UEK)", "2.28", "✅ [#ol-mi300x]_"
    

.. note::

  * See `Red Hat Enterprise Linux Release Dates <https://access.redhat.com/articles/3078>`_ to learn about the specific kernel versions supported on Red Hat Enterprise Linux (RHEL).
  * See `List of SUSE Linux Enterprise Server kernel <https://www.suse.com/support/kb/doc/?id=000019587>`_ to learn about the specific kernel version supported on SUSE Linux Enterprise Server (SLES).
  * See the :doc:`rocm:compatibility/compatibility-matrix` for an overview of OS support across ROCm releases.


.. rubric:: Footnotes

.. [#rhel-700] RHEL 8.10 is only supported on AMD Instinct MI300X, MI300A, MI250X, MI250, MI210, and MI100 GPUs.
.. [#sles-db-700] SLES 15 SP7 and Debian 12 are only supported on AMD Instinct MI300X, MI300A, MI250X, MI250, and MI210 GPUs.
.. [#rl-700] Rocky Linux 9 is only supported on AMD Instinct MI300X and MI300A GPUs.  
.. [#al-mi300x] Azure Linux 3.0 is supported only on AMD Instinct MI300X GPU and AMD Radeon PRO V710.
.. [#ol-700] Oracle Linux 9 is supported only on AMD Instinct MI355X, MI350X, and MI300X GPUs.
.. [#ol-mi300x] Oracle Linux 8 is supported only on AMD Instinct MI300X GPUs.


Virtualization support
======================

ROCm supports virtualization for the Instinct accelerators and Radeon PRO GPUs listed in the following table.

.. important:: 
  
  GPU virtualization with KVM-based SR-IOV requires AMD GPU Virtualization Driver (GIM) driver. Refer to `GIM Release note <https://github.com/amd/MxGPU-Virtualization/releases>`_.

.. raw:: html

   <div class="pst-scrollable-table-container">
    <style>
      table#virtualization-support-table tbody tr:last-child {
        border-bottom: 2px solid var(--pst-color-border);
      }
      table#virtualization-support-table tbody#virtualization-support-mi210x tr:last-child {
        border-bottom: 2px solid var(--pst-color-primary);
      }
    </style>
     <table id="virtualization-support-table" class="table">
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
             <p>Host OS</p>
           </th>
           <th class="head">
             <p>Guest OS</p>
           </th>
         </tr>
       </thead>
       <tbody id="virtualization-support-mi355x">
        <tr class="row-even">
           <td rowspan="2" style="vertical-align: middle;">
             <p>Instinct MI355X</p>
           </td>
           <td>
             <p>KVM</p>
           </td>
           <td>
             <p>Passthrough</p>
           </td>
           <td>
             <p>Ubuntu 24.04,<br>
                RHEL 9.6</p>
           </td>
           <td>
             <p>Ubuntu 24.04,<br>
                RHEL 9.6</p>
           </td>
         </tr>
         <tr>
           <td>
             <p>KVM</p>
           </td>
           <td>
             <p>SR-IOV</p>
           </td>
           <td>
             <p>Ubuntu 24.04</p>
           </td>
           <td>
             <p>Ubuntu 24.04</p>
           </td>
         </tr>
       </tbody>
       <tbody id="virtualization-support-mi350x">
         <tr class="row-odd">
           <td rowspan="2" style="vertical-align: middle;">
             <p>Instinct MI350X</p>
           </td>
           <td>
             <p>KVM</p>
           </td>
           <td>
             <p>Passthrough</p>
           </td>
           <td>
             <p>Ubuntu 24.04,<br>
                RHEL 9.6</p>
           </td>
           <td>
             <p>Ubuntu 24.04,<br>
                RHEL 9.6</p>
           </td>
         </tr>
         <tr>
           <td>
             <p>KVM</p>
           </td>
           <td>
             <p>SR-IOV</p>
           </td>
           <td>
             <p>Ubuntu 24.04</p>
           </td>
           <td>
             <p>Ubuntu 24.04</p>
           </td>
         </tr>
       </tbody>
       <tbody id="virtualization-support-mi325x">
         <tr class="row-even">
           <td rowspan="2" style="vertical-align: middle;">
             <p>Instinct MI325X</p>
           </td>
           <td>
             <p>KVM</p>
           </td>
           <td>
             <p>Passthrough</p>
           </td>
           <td>
             <p>Ubuntu 24.04,<br>
                Ubuntu 22.04,<br>
                RHEL 9.6,<br>
                RHEL 9.4</p>
           </td>
           <td>
             <p>Ubuntu 24.04,<br>
                Ubuntu 22.04,<br>
                RHEL 9.6,<br>
                RHEL 9.4</p>
           </td>
         </tr>
         <tr>
           <td>
             <p>KVM</p>
           </td>
           <td>
             <p>SR-IOV</p>
           </td>
           <td>
             <p>Ubuntu 22.04</p>
           </td>
           <td>
             <p>Ubuntu 22.04</p>
           </td>
         </tr>
       </tbody>
       <tbody id="virtualization-support-mi300x">
         <tr class="row-odd">
          <td rowspan="3" style="vertical-align: middle;">
             <p>Instinct MI300X</p>
           </td>
           <td>
             <p>ESXi</p>
           </td>
           <td>
             <p>Passthrough</p>
           </td>
           <td>
             <p>ESXi 8.0 Update 3</p>
           </td>
           <td>
             <p>Ubuntu 24.04,<br>
                Ubuntu 22.04</p>
           </td>
          </tr>
          <tr>
           <td>
             <p>KVM</p>
           </td>
           <td>
             <p>Passthrough</p>
           </td>
           <td>
             <p>Ubuntu 24.04,<br>
                Ubuntu 22.04,<br>
                RHEL 9.6,<br>
                RHEL 9.4</p>
           </td>
           <td>
             <p>Ubuntu 24.04,<br>
                Ubuntu 22.04,<br>
                RHEL 9.6,<br>
                RHEL 9.4</p>
           </td>
         </tr>
         <tr>
           <td>
             <p>KVM</p>
           </td>
           <td>
             <p>SR-IOV</p>
           </td>
           <td>
             <p>Ubuntu 22.04</p>
           </td>
           <td>
             <p>Ubuntu 22.04</p>
           </td>
         </tr>
       </tbody>
       <tbody id="virtualization-support-mi210x">
         <tr class="row-even">
           <td rowspan="2" style="vertical-align: middle;">
             <p>Instinct MI210</p>
           </td>
           <td>
             <p>KVM</p>
           </td>
           <td>
             <p>Passthrough</p>
           </td>
           <td>
             <p>RHEL 9.4</p>
           </td>
           <td>
             <p>Ubuntu 22.04,<br>
                RHEL 9.4</p>
           </td>
          </tr>
          <tr>
           <td>
             <p>KVM</p>
           </td>
           <td>
             <p>SR-IOV</p>
           </td>
           <td>
             <p>RHEL 9.4</p>
           </td>
           <td>
             <p>Ubuntu 22.04,<br>
                RHEL 9.4</p>
           </td>
          </tr>
         </tbody>
         <tbody id="virtualization-support-radeon-pro">
         <tr class="row-odd">
           <td>
             <p>Radeon PRO V710</p>
           </td>
           <td>
             <p>KVM</p>
           </td>
           <td>
             <p>SR-IOV</p>
           </td>
           <td>
             <p>Ubuntu 24.04</p>
           </td>
           <td>
             <p>Ubuntu 24.04</p>
           </td>
         </tr>
       </tbody>
     </table>
   </div>

.. note::

  AMD Virtualization supports the following:  
  
  * Passthrough: All 8 GPUs are assigned directly to a single virtual machine (VM).
  * SR-IOV: Provides 1 Virtual Function (VF) per GPU (8 VFs in total), which can be flexibly assigned among multiple VMs (for example, 8 VMs with 1 VF each, 4 VMs with 2 VFs each, or 2 VMs with 4 VFs each)

CPU support
=============================================

ROCm requires CPUs that support PCIe™ atomics. Modern CPUs after the release of
1st generation AMD Zen CPU and Intel™ Haswell support PCIe atomics.
