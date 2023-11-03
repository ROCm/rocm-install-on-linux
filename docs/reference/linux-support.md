# GPU and OS support (Linux)

(linux-support)=

## Supported Linux distributions

AMD ROCm™ Platform supports the following Linux distributions.

::::{tab-set}

:::{tab-item} Supported

| Distribution | Processor Architectures | Validated Kernel | Support |
| :----------- | :---------------------: | :--------------: | ------: |
| RHEL 9.2       | x86-64 | 5.14 (5.14.0-284.11.1.el9_2.x86_64)        | ✅ |
| RHEL 9.1       | x86-64 | 5.14.0-284.11.1.el9_2.x86_64             | ✅ |
| RHEL 8.8       | x86-64 | 4.18.0-477.el8.x86_64        | ✅ |
| RHEL 8.7       | x86-64 | 4.18.0-425.10.1.el8_7.x86_64              | ✅ |
| SLES 15 SP5    | x86-64 |  5.14.21-150500.53-default       | ✅ |
| SLES 15 SP4    | x86-64 | 5.14.21-150400.24.63-default               | ✅ |
| Ubuntu 22.04.2 | x86-64 | 5.19.0-45-generic | ✅ |
| Ubuntu 20.04.5 | x86-64 | 5.15.0-75-generic          | ✅ |

:::{versionadded} 5.6

* RHEL 8.8 and 9.2 support is added.
* SLES 15 SP5 support is added

:::

:::{tab-item} Unsupported

| Distribution | Processor Architectures | Validated Kernel | Support |
| :----------- | :---------------------: | :--------------: | ------: |
| RHEL 9.0       | x86-64 | 5.14               | ❌ |
| RHEL 8.6       | x86-64 | 5.14               | ❌ |
| SLES 15 SP3    | x86-64 | 5.3                | ❌ |
| Ubuntu 22.04.0 | x86-64 | 5.15 LTS, 5.17 OEM | ❌ |
| Ubuntu 20.04.4 | x86-64 | 5.13 HWE, 5.13 OEM | ❌ |
| Ubuntu 22.04.1 | x86-64 | 5.15 LTS           | ❌ |

:::

::::

✅: **Supported** - AMD performs full testing of all ROCm components on distro
  GA image.
❌: **Unsupported** - AMD no longer performs builds and testing on these
  previously supported distro GA images.

## Virtualization support

ROCm supports virtualization for select GPUs only as shown below.

| Hypervisor     | Version  | GPU   | Validated Guest OS (validated kernel)                                            |
|----------------|----------|-------|----------------------------------------------------------------------------------|
| VMWare         | ESXi 8   | MI250 | Ubuntu 20.04 (`5.15.0-56-generic`)                                               |
| VMWare         | ESXi 8   | MI210 | Ubuntu 20.04 (`5.15.0-56-generic`), SLES 15 SP4 (`5.14.21-150400.24.18-default`) |
| VMWare         | ESXi 7   | MI210 | Ubuntu 20.04 (`5.15.0-56-generic`), SLES 15 SP4 (`5.14.21-150400.24.18-default`) |

## Linux-supported GPUs

The table below shows supported GPUs for Instinct™, Radeon Pro™ and Radeon™
GPUs. Please click the tabs below to switch between GPU product lines. If a GPU
is not listed on this table, the GPU is not officially supported by AMD.

:::::{tab-set}

::::{tab-item} AMD Instinct™
:sync: instinct

| Product Name | Architecture | [LLVM Target](https://www.llvm.org/docs/AMDGPUUsage.html#processors) |Support |
|:------------:|:------------:|:--------------------------------------------------------------------:|:-------:|
| AMD Instinct™ MI250X | CDNA2  | gfx90a | ✅ |
| AMD Instinct™ MI250  | CDNA2  | gfx90a | ✅ |
| AMD Instinct™ MI210  | CDNA2  | gfx90a | ✅ |
| AMD Instinct™ MI100  | CDNA   | gfx908 | ✅ |
| AMD Instinct™ MI50   | GCN5.1 | gfx906 | ✅ |
| AMD Instinct™ MI25   | GCN5.0 | gfx900 | ❌ |

::::

::::{tab-item} Radeon Pro™
:sync: radeonpro

| Name | Architecture |[LLVM Target](https://www.llvm.org/docs/AMDGPUUsage.html#processors) | Support|
|:----:|:------------:|:--------------------------------------------------------------------:|:-------:|
| AMD Radeon™ Pro W7900   | RDNA3  | gfx1100 | ✅ (Ubuntu 22.04 only)|
| AMD Radeon™ Pro W6800   | RDNA2  | gfx1030 | ✅ |
| AMD Radeon™ Pro V620    | RDNA2  | gfx1030 | ✅ |
| AMD Radeon™ Pro VII     | GCN5.1 | gfx906  | ✅ |
::::

::::{tab-item} Radeon™
:sync: radeonpro

| Name | Architecture    |[LLVM Target](https://www.llvm.org/docs/AMDGPUUsage.html#processors) | Support|
|:----:|:---------------:|:--------------------------------------------------------------------:|:-------:|
| AMD Radeon™ RX 7900 XTX | RDNA3 | gfx1100  | ✅ (Ubuntu 22.04 only)|
| AMD Radeon™ VII        | GCN5.1 | gfx906  | ✅ |

::::
:::::

### Support status

✅: **Supported** - AMD enables these GPUs in our software distributions for
  the corresponding ROCm product.
⚠️: **Deprecated** - Support will be removed in a future release.
❌: **Unsupported** - This configuration is not enabled in our software
  distributions.

## CPU support

ROCm requires CPUs that support PCIe™ atomics. Modern CPUs after the release of
1st generation AMD Zen CPU and Intel™ Haswell support PCIe atomics.
