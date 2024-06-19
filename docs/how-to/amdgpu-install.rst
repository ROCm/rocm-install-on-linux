.. meta::
  :description: Installation via AMDGPU installer
  :keywords: installation instructions, AMDGPU, AMDGPU installer, AMD, ROCm

*************************************************************************************
Installation via AMDGPU installer
*************************************************************************************

``amdgpu-install`` is a tool that helps you install and update AMDGPU, ROCm, and ROCm components.

.. warning::

  ROCm doesn't currently support integrated graphics. Should your system have an
  AMD IGP installed, disable it in the BIOS prior to using ROCm. If the driver can
  enumerate the IGP, the ROCm runtime may crash the system, even if told to omit
  it via `HIP_VISIBLE_DEVICES <https://rocm.docs.amd.com/en/latest/conceptual/gpu-isolation.html#hip-visible-devices>`_.

.. _amdgpu-install-installation:

Installation
=================================================

Installation of ``amdgpu-install`` differs slightly depending on the OS and its package manager.

Make sure that the :doc:`/how-to/prerequisites` are met before installing.

Ubuntu
--------------------------------------------------------------------

.. datatemplate:nodata::

    .. tab-set::
        {% for (os_version, os_release) in config.html_context['ubuntu_version_numbers'] %}
        .. tab-item:: Ubuntu {{ os_version }}
            :sync: ubuntu-{{ os_version}}

            .. code-block:: bash
                :substitutions:

                sudo apt update
                wget https://repo.radeon.com/amdgpu-install/|amdgpu_version|/ubuntu/{{ os_release }}/amdgpu-install_|amdgpu_install_version|_all.deb
                sudo apt install ./amdgpu-install_|amdgpu_install_version|_all.deb
        {% endfor %}

Red Hat Enterprise Linux
--------------------------------------------------------------------

.. datatemplate:nodata::

    .. tab-set::
        {% for os_version in config.html_context['rhel_version_numbers'] %}
        {% set os_major, _  = os_version.split('.') %}
        .. tab-item:: RHEL {{ os_version }}
            :sync: rhel-{{ os_version }} rhel-{{ os_major }}

            .. code-block:: bash
                :substitutions:

                sudo yum install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/rhel/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.el{{ os_major }}.noarch.rpm

        {% if os_version == '9.4' %}
            .. note::

                RHEL 9.4 is only supported on AMD Instinct MI300A.
        {% endif %}
        {% endfor %}

SUSE Linux Enterprise
--------------------------------------------------------------------

.. datatemplate:nodata::

    .. tab-set::
        {% for os_version in config.html_context['sles_version_numbers'] %}
        .. tab-item:: SLES {{ os_version }}

            .. code-block:: bash
                :substitutions:

                sudo zypper --no-gpg-checks install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/sle/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.noarch.rpm
        {% endfor %}

.. _amdgpu-install-use-cases:

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
      - OpenCL (ROCr/KFD based) runtime
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
      - ASAN enabled OpenCL (ROCr/KFD based) runtime
      - ASAN enabled HIP runtimes
      - ASAN enabled Machine learning framework
      - ASAN enabled ROCm libraries


.. _amdgpu-install-dkms:

Install amdgpu-dkms
-------------------------------------------------

In order to install only the DKMS, which is a minimal requirement for launching containers with GPU
access, use the ``dkms`` use case:

.. code-block:: bash

   amdgpu-install --usecase=dkms

Upgrading ROCm
=================================================

The upgrade procedure with the installer script is exactly the same as
:ref:`installing for first time use <amdgpu-install-installation>`.

Installing ROCm packages
=================================================

To install use cases specific to your requirements, use the installer (``amdgpu-install``) as follows:

* To install a single use case, add it with the ``--usecase`` option:

  .. code-block:: bash

    sudo amdgpu-install --usecase=rocm

* For multiple use cases, separate them with commas:

  .. code-block:: bash

    sudo amdgpu-install --usecase=hiplibsdk,rocm

* For graphical workloads using the open-source driver, add ``graphics``. For example:

  .. code-block:: bash

    sudo amdgpu-install --usecase=graphics,rocm

* For graphical workloads using the proprietary driver, add ``workstation``. For example:

  .. code-block:: bash

    sudo amdgpu-install --usecase=workstation,rocm

* To install LLVM AddressSanitizer (ASAN) instrumented binaries (for packages that support it), add
  ``asan``. For example:

  .. code-block:: bash

    sudo amdgpu-install --usecase=rocm,asan

Uninstalling ROCm
=================================================

To uninstall all ROCm packages and the kernel-mode driver, use the following commands.

* Uninstalling single-version install

  .. code-block:: bash

    sudo amdgpu-install --uninstall

* Uninstalling a specific ROCm release

  .. code-block:: bash

    sudo amdgpu-install --uninstall --rocmrelease=<release-number>


* Uninstalling all ROCm releases

  .. code-block:: bash

    sudo amdgpu-install --uninstall --rocmrelease=all

.. _amdgpu-install-multi-version:

Multi-versioned ROCm installation
=================================================

By default (without the ``--rocmrelease`` option), the installer script installs packages in the
single-version layout.

For the multi-version ROCm installation, you must use the installer script from the latest ROCm release
you want to install.

**Example:** If you want to install ROCm releases 5.5.3, 5.6.1, and 5.7 simultaneously, you must
download the ROCm 5.7 installer. Then, you must manually add the ROCm repositories for all ROCm
releases you want to install, except for the latest one. The ``amdgpu-install`` script automatically adds
the required repositories for the latest release.

Refer to :ref:`Register ROCm packages <ubuntu-register-rocm>` on the
:doc:`Ubuntu native installation <./native-install/ubuntu>` page.

Additional options
=================================================

* Unattended installation.

  Adding ``-y`` as a parameter to ``amdgpu-install`` skips user prompts (for automation). For example:

  .. code-block:: bash

      amdgpu-install -y --usecase=rocm

* Skipping kernel mode driver installation.

  The installer script tries to install the kernel mode driver along with the requested use cases. This
  might be unnecessary (as in the case of Docker containers) or you may want to keep a specific version
  when using multi-version installation, and not have the last installed version overwrite the kernel
  mode driver.

  To skip the installation of the kernel-mode driver, add the ``--no-dkms`` option when calling the
  installer script.
