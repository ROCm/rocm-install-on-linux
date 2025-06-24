.. meta::
  :description: Package details
  :keywords: OpenCL, OpenMP, package manager, AMD, ROCm

************************************************************************************
Package details
************************************************************************************

This section provides information about the required meta-packages for the
following AMD ROCm programming models:

* Heterogeneous-Computing Interface for Portability (HIP)
* OpenCL™
* OpenMP™

ROCm package naming conventions
============================================================

A meta-package is a grouping of related packages and dependencies used to
support a specific use case.

**Example:** Running HIP applications

All meta-packages exist in both versioned and non-versioned forms.

* Non-versioned packages: For a single-version installation of the ROCm stack
* Versioned packages: For multi-version installations of the ROCm stack

.. image:: ../data/install/linux/linux002.png
    :alt: ROCm Release Package Naming

The figure above demonstrates the single and multi-version ROCm packages' naming
structure, including examples for various Linux distributions. See terms below:

*Module* - It is the part of the package that represents the name of the ROCm
component.

**Example:** The examples mentioned in the image represent the ROCm HIP module.

*Module version* - It is the version of the library released in that package. It
should increase with a newer release.

*Release version* - It shows the ROCm release version when the package was
released.

**Example:** `50400` points to the ROCm 5.4.0 release.

*Build id* - It represents the build number for that release.

*Arch* - It shows the architecture for which the package was created.

*Distro* - It describes the distribution for which the package was created. It is
valid only for rpm packages.

**Example:** `el8` represents RHEL 8.x packages.

Components of ROCm programming models
============================================================

The figure below demonstrates the high-level layered architecture of ROCm programming models and their meta-packages.
All meta-packages are a combination of required packages and libraries.

.. image:: ../data/install/linux/linux003.png
    :width: 1500
    :alt: ROCm meta packages

.. note::
    The preceding figure is for informational purposes only. The individual packages in a meta-package
    are subject to change. To avoid conflicts, install meta-packages, not individual packages.

**Example:**

- ``rocm-hip-runtime`` is used to deploy on supported machines to execute HIP
  applications.
- ``rocm-hip-sdk`` contains runtime components to deploy and execute HIP
  applications.

.. note::
    ``rocm-llvm`` is not a meta-package; it's a single package that installs the ROCm Clang compiler files.

.. include:: ../install/install-methods/includes/meta-package-table.rst

Packages in ROCm programming models
============================================================

This section discusses the available meta-packages and their packages.
The following table shows the meta-packages and their associated (meta-)packages in a ROCm programming model.

.. note::

   ``rocm-utils`` is a legacy meta-package that includes ``rocminfo``, ``rocm-cmake``, and ``rocm-core``. 
   Other meta-packages manage the installation of these components.

.. note::

  Some meta packages and dependencies in the tables below have names ending with ``-dev``, as they are based on Ubuntu. 
  On RPM-based systems like RHEL, these packages use a different naming convention and typically end with ``-devel`` instead.

ROCm runtime packages
---------------------

.. table::
  :widths: 20 80

  +----------------------------+----------------------------------------------------------------------------------------------------------+
  | Meta package               | Associated meta packages or packages                                                                     |
  +============================+==========================================================================================================+
  | ``rocm``                   | Meta packages: ``rocm-developer-tools``, ``rocm-ml-sdk``, ``rocm-opencl-sdk``, ``rocm-openmp-sdk``       |
  |                            |                                                                                                          |
  |                            | Packages: ``rocm-utils``, ``mivisionx``, ``migraphx``, ``rpp``, ``rocm-core``, ``migraphx-dev``,         |
  |                            | ``mivisionx-dev``, ``rpp-dev``                                                                           |
  +----------------------------+----------------------------------------------------------------------------------------------------------+
  | ``rocm-language-runtime``  | Packages: ``comgr``, ``hsa-rocr``, ``rocm-core``, ``openmp-extras-runtime``                              |
  +----------------------------+----------------------------------------------------------------------------------------------------------+
  | ``rocm-hip-runtime``       | Meta packages: ``rocm-language-runtime``                                                                 |
  |                            |                                                                                                          |
  |                            | Packages: ``hip-runtime-amd``, ``rocm-core``, ``rocminfo``                                               |
  +----------------------------+----------------------------------------------------------------------------------------------------------+
  | ``rocm-hip-libraries``     | Meta packages: ``rocm-hip-runtime``                                                                      |
  |                            |                                                                                                          |
  |                            | Packages: ``rocm-core``, ``rocm-smi-lib``, ``hipblas``, ``hipblaslt``, ``hipfft``, ``hipsparse``,        |
  |                            | ``hipsolver``, ``hiptensor``, ``rccl``, ``rocalution``, ``rocblas``, ``rocfft``,                         |
  |                            | ``rocrand``, ``hiprand``, ``rocsolver``, ``rocsparse``, ``hipsparselt``                                  |
  +----------------------------+----------------------------------------------------------------------------------------------------------+
  | ``rocm-opencl-runtime``    | Meta packages: ``rocm-language-runtime``                                                                 |
  |                            |                                                                                                          |
  |                            | Packages: ``rocm-core``, ``rocm-opencl``                                                                 |
  +----------------------------+----------------------------------------------------------------------------------------------------------+
  | ``rocm-ml-libraries``      | Meta packages: ``rocm-hip-libraries``                                                                    |
  |                            |                                                                                                          |
  |                            | Packages: ``miopen-hip``, ``half``, ``rocm-core``, ``rocm-llvm``                                         |
  +----------------------------+----------------------------------------------------------------------------------------------------------+


ROCm developer packages
-----------------------

.. table::
  :widths: 20 80

  +----------------------------+-------------------------------------------------------------------------------------------------------------------------------------+
  | Meta package               | Associated meta packages or packages                                                                                                |
  +============================+=====================================================================================================================================+
  | ``rocm-developer-tools``   | Meta packages: ``rocm-language-runtime``                                                                                            |
  |                            |                                                                                                                                     |
  |                            | Packages: ``amd-smi-lib``, ``rocm-core``, ``rocm-dbgapi``, ``rocm-debug-agent``, ``rocm-gdb``, ``hsa-amd-aqlprofile``,              |
  |                            | ``rocm-smi-lib``, ``rocprofiler-register``, ``rocprofiler``, ``rocprofiler-plugins``, ``roctracer``, ``rocprofiler-sdk``,           |
  |                            | ``rocprofiler-sdk-roctx``, ``rocprofiler-compute``, ``rocprofiler-systems``, ``rocprofiler-dev``, ``roctracer-dev``                 |
  +----------------------------+-------------------------------------------------------------------------------------------------------------------------------------+
  | ``rocm-hip-runtime-dev``   | Meta packages: ``rocm-hip-runtime``                                                                                                 |
  |                            |                                                                                                                                     |
  |                            | Packages: ``rocm-core``, ``rocm-device-libs``, ``rocm-cmake``, ``rocm-llvm``, ``hipcc``, ``hipify-clang``, ``hip-doc``,             |
  |                            | ``hip-samples``, ``hip-dev``, ``hsa-rocr-dev``                                                                                      |
  +----------------------------+-------------------------------------------------------------------------------------------------------------------------------------+
  | ``rocm-hip-sdk``           | Meta packages: ``rocm-hip-libraries``, ``rocm-hip-runtime-dev``                                                                     |
  |                            |                                                                                                                                     |
  |                            | Packages: ``rocm-core``, ``composablekernel-dev``, ``hipblas-common-dev``, ``hipblas-dev``, ``hipblaslt-dev``, ``hipcub-dev``,      |
  |                            | ``hipfft-dev``, ``hipsparse-dev``, ``hipsolver-dev``, ``hipfort-dev``, ``hiptensor-dev``, ``rccl-dev``, ``rocalution-dev``,         |
  |                            | ``rocblas-dev``, ``rocfft-dev``, ``rocprim-dev``, ``rocrand-dev``, ``hiprand-dev``, ``rocsolver-dev``, ``rocsparse-dev``,           |
  |                            | ``rocthrust-dev``, ``rocwmma-dev``, ``hipsparselt-dev``                                                                             |
  +----------------------------+-------------------------------------------------------------------------------------------------------------------------------------+
  | ``rocm-opencl-sdk``        | Meta packages: ``rocm-opencl-runtime``                                                                                              |
  |                            |                                                                                                                                     |
  |                            | Packages: ``hsa-rocr-dev``, ``rocm-core``, ``rocm-opencl-dev``                                                                      |
  +----------------------------+-------------------------------------------------------------------------------------------------------------------------------------+
  | ``rocm-openmp-sdk``        | Meta packages: ``rocm-language-runtime``                                                                                            |
  |                            |                                                                                                                                     |
  |                            | Packages: ``rocm-device-libs``, ``rocm-llvm``, ``rocm-core``, ``hsa-rocr-dev``, ``openmp-extras-dev``                               |
  +----------------------------+-------------------------------------------------------------------------------------------------------------------------------------+
  | ``rocm-ml-sdk``            | Meta packages: ``rocm-hip-sdk``                                                                                                     |
  |                            |                                                                                                                                     |
  |                            | Packages: ``rocm-ml-libraries``, ``rocm-hip-sdk``, ``miopen-hip-dev``, ``rocm-core``                                                |
  +----------------------------+-------------------------------------------------------------------------------------------------------------------------------------+

