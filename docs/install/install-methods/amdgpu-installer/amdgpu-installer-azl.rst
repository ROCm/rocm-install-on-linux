.. meta::
  :description: Azure Linux AMDGPU installer installation
  :keywords: installation instructions, AMDGPU, AMDGPU installer, AMD, ROCm, Azure Linux, Azure Linux AMDGPU installer installation

*************************************************************************************
Azure Linux AMDGPU installer installation
*************************************************************************************

``amdgpu-install`` is a tool that helps you install and update AMDGPU, ROCm, and ROCm components.

.. warning::

  ROCm doesn't support integrated graphics. If your system has an
  AMD IGP installed, disable it in the BIOS prior to using ROCm. If the driver can
  enumerate the IGP, the ROCm runtime might crash the system, even if told to omit
  it via `HIP_VISIBLE_DEVICES <https://rocm.docs.amd.com/en/latest/conceptual/gpu-isolation.html#hip-visible-devices>`_.

.. _azl-amdgpu-install-installation:

Installation
=================================================

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met before installing.

.. datatemplate:nodata::

  .. tab-set::
      {% for os_version in config.html_context['azl_version_numbers'] %}
      {% set os_major, _  = os_version.split('.') %}
      .. tab-item:: AZL {{ os_version }}

          .. code-block:: bash
              :substitutions:

              sudo tdnf install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/azurelinux/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.azl{{ os_major }}.noarch.rpm --nogpgcheck
      {% endfor %}

.. _azl-amdgpu-install-use-cases:

Use cases
=================================================

Instead of installing individual applications or libraries, the installer script groups packages into specific
use cases that match typical workflows and runtimes.

To display a list of available use cases, run:

.. code-block:: bash

    sudo amdgpu-install --list-usecase

The available use-cases are printed in a format similar to:

.. code-block::

    If --usecase option is not present, the default selection is "graphics,opencl,hip"

    Available use cases:
    dkms            (to only install the kernel mode driver)
      - Kernel mode driver (included in all usecases)
    graphics        (for users of graphics applications)
      - Open source Mesa 3D graphics and multimedia libraries
    multimedia      (for users of open source multimedia)
      - Open source Mesa 3D multimedia libraries
    multimediasdk   (for developers of open source multimedia)
      - Open source Mesa 3D multimedia libraries
      - Development headers for multimedia libraries
    workstation     (for users of legacy WS applications)
      - Open source multimedia libraries
      - Closed source (legacy) OpenGL
    rocm            (for users and developers requiring full ROCm stack)
      - OpenCL (ROCr/KMD based) runtime
      - HIP runtimes
      - Machine learning framework
      - All ROCm libraries and applications
    rocmdev         (for developers requiring ROCm runtime and
                    profiling/debugging tools)
      - HIP runtimes
      - OpenCL runtime
      - Profiler, Tracer and Debugger tools
    rocmdevtools    (for developers requiring ROCm profiling/debugging tools)
      - Profiler, Tracer and Debugger tools
    amf             (for users of AMF based multimedia)
      - AMF closed source multimedia library
    lrt             (for users of applications requiring ROCm runtime)
      - ROCm Compiler and device libraries
      - ROCr runtime and thunk
    opencl          (for users of applications requiring OpenCL on Vega or later
                    products)
      - ROCr based OpenCL
      - ROCm Language runtime
    openclsdk       (for application developers requiring ROCr based OpenCL)
      - ROCr based OpenCL
      - ROCm Language runtime
      - development and SDK files for ROCr based OpenCL
    hip             (for users of HIP runtime on AMD products)
      - HIP runtimes
    hiplibsdk       (for application developers requiring HIP on AMD products)
      - HIP runtimes
      - ROCm math libraries
      - HIP development libraries
    openmpsdk       (for users of openmp/flang on AMD products)
      - OpenMP runtime and devel packages
    mllib           (for users executing machine learning workloads)
      - MIOpen hip/tensile libraries
      - Clang OpenCL
      - MIOpen kernels
    mlsdk           (for developers executing machine learning workloads)
      - MIOpen development libraries
      - Clang OpenCL development libraries
      - MIOpen kernels
    asan            (for users of ASAN enabled ROCm packages)
      - ASAN enabled OpenCL (ROCr/KMD based) runtime
      - ASAN enabled HIP runtimes
      - ASAN enabled Machine learning framework
      - ASAN enabled ROCm libraries


.. _azl-amdgpu-install-dkms:

Install kernel driver
-------------------------------------------------

.. code-block:: bash

    sudo tdnf install azurelinux-repos-amd
    sudo tdnf repolist --refresh
    sudo tdnf install amdgpu
    sudo modprobe amdgpu

Upgrading ROCm
=================================================

The upgrade procedure with the installer script is the same as installing it for first-time use.

Installing ROCm packages
=================================================

To install use cases specific to your requirements, use the installer (``amdgpu-install``) as follows:

* To install a single use case, add it with the ``--usecase`` option:

  .. code-block:: bash

    sudo amdgpu-install --usecase=rocm --no-dkms

* The ``--help`` option displays all available options for the ``amdgpu-install`` script:

  .. code-block:: bash

    sudo amdgpu-install --help


.. _azl-amdgpu-install-uninstall:

Uninstalling
=====================================================

Uninstalling ROCm
---------------------------------------------------------------------------

.. code-block:: bash

  sudo amdgpu-install --uninstall

Uninstall kernel driver
---------------------------------------------------------------------------

.. code-block:: bash

  sudo tdnf remove amdgpu amdgpu-firmware kernel-drivers-gpu

Uninstalling amdgpu-install
---------------------------------------------------------------------------

After uninstalling ROCm and kernel driver, remove the amdgpu-install package from the system.

.. code-block:: bash

    sudo tdnf remove amdgpu-install

Remove ROCm and AMDGPU repositories
---------------------------------------------------------------------------

.. code-block:: bash

    # Remove the repositories
    sudo tdnf remove azurelinux-repos-amd
    sudo rm /etc/yum.repos.d/rocm.repo*
    sudo rm /etc/yum.repos.d/amdgpu.repo*

    # Clear the cache and clean the system
    sudo rm -rf /var/cache/tdnf
    sudo tdnf clean all

    # Restart the system.
    sudo reboot

Additional options
=================================================

* Unattended installation.

  Adding ``-y`` as a parameter to ``amdgpu-install`` skips user prompts (for automation). For example:

  .. code-block:: bash

      amdgpu-install -y --usecase=rocm

* Skipping kernel mode driver installation.

  The installer script tries to install the kernel mode driver and the requested use cases. This
  might be unnecessary (as in the case of Docker containers). You might want to keep a specific version
  when using multi-version installation, and not have the last installed version overwrite the kernel
  mode driver.

  To skip the installation of the kernel-mode driver, add the ``--no-dkms`` option when calling the
  installer script.
