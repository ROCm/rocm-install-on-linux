Installation via AMDGPU Script
##############################

``amdgpu-install`` is a tool that helps you install and update AMDGPU and ROCm
and its components.

.. warning::
    ROCm currently doesn't support integrated graphics. Should your system have an
    AMD IGP installed, disable it in the BIOS prior to using ROCm. If the driver can
    enumerate the IGP, the ROCm runtime may crash the system, even if told to omit
    it via :ref:`hip_visible_devices`.

.. _amdgpu-install-installation:

Installation
************

Installation of ``amdgpu-install`` differs slightly depending on the OS and its package manager.

Make sure that the :doc:`/how-to/prerequisites` are met before installing.

Ubuntu
======

.. datatemplate:nodata::

    .. tab-set::
        {% for (os_version, os_release) in [('22.04', 'jammy'), ('20.04', 'focal')] %}
        .. tab-item:: Ubuntu {{ os_version }}
            :sync: ubuntu-{{ os_version}}

            .. code-block:: bash
                :substitutions:

                sudo apt update
                wget https://repo.radeon.com/amdgpu-install/|amdgpu_version|/ubuntu/{{ os_release }}/amdgpu-install_|amdgpu_install_version|_all.deb
                sudo apt install ./amdgpu-install_|amdgpu_install_version|_all.deb
        {% endfor %}

Red Hat Enterprise Linux
========================

.. datatemplate:nodata::

    .. tab-set::
        {% for (os_release, os_version) in [('8', '8.8'), ('8', '8.7'), ('9', '9.2'), ('9', '9.1')] %}
        .. tab-item:: RHEL {{ os_version }}
            :sync: rhel-{{ os_version }} rhel-{{ os_release }}

            .. code-block:: bash
                :substitutions:

                sudo yum install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/rhel/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.el{{ os_release }}.noarch.rpm
        {% endfor %}

SUSE Linux Enterprise
=====================

.. datatemplate:nodata::

    .. tab-set::
        {% for os_version in ['15.5', '15.4'] %}
        .. tab-item:: RHEL-{{ os_version }}

            .. code-block:: bash
                :substitutions:

                sudo zypper --no-gpg-checks install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/sle/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.noarch.rpm
        {% endfor %}

Usage
*****

Use case groups
===============

Instead of installing individual applications or libraries the installer script
groups packages into specific use cases, matching typical workflows and
runtimes.

To display a list of available use cases execute the command:

.. code-block:: bash

    sudo amdgpu-install --list-usecase

The available use-cases will be printed in a format similar to the example
output below.

.. code-block::

    If --usecase option is not present, the default selection is "graphics,opencl,hip"

    Available use cases:
    rocm(for users and developers requiring full ROCm stack)
    - OpenCL (ROCr/KFD based) runtime
    - HIP runtimes
    - Machine learning framework
    - All ROCm libraries and applications
    - ROCm Compiler and device libraries
    - ROCr runtime and thunk
    lrt(for users of applications requiring ROCm runtime)
    - ROCm Compiler and device libraries
    - ROCr runtime and thunk
    opencl(for users of applications requiring OpenCL on Vega or
    later products)
    - ROCr based OpenCL
    - ROCm Language runtime

    openclsdk (for application developers requiring ROCr based OpenCL)
    - ROCr based OpenCL
    - ROCm Language runtime
    - development and SDK files for ROCr based OpenCL

    hip(for users of HIP runtime on AMD products)
    - HIP runtimes
    hiplibsdk (for application developers requiring HIP on AMD products)
    - HIP runtimes
    - ROCm math libraries
    - HIP development libraries


Upgrading
=========

The upgrade procedure with the installer script is exactly the same as
:ref:`installing for first time use. <amdgpu-install-installation>`

Installing ROCm packages
==========================

To install use cases specific to your requirements, use the installer
amdgpu-install as follows:

- To install a single use case add it with the --usecase option:

  .. code-block:: bash

      sudo amdgpu-install --usecase=rocm

- For multiple use cases separate them with commas:

  .. code-block:: bash

      sudo amdgpu-install --usecase=hiplibsdk,rocm

- For graphical workloads using the open-source driver add ``graphics``. For
  example:

  .. code-block:: bash

      sudo amdgpu-install --usecase=graphics,rocm

- For graphical workloads using the proprietary driver add ``workstation``. For
  example:

  .. code-block:: bash

      sudo amdgpu-install --usecase=workstation,rocm

Uninstalling
============

To uninstall all ROCm packages and the kernel-mode driver the following commands
can be used.

- Uninstalling Single-Version Install

  .. code-block:: bash

      sudo amdgpu-install --uninstall

- Uninstalling a Specific ROCm Release

  .. code-block:: bash

      sudo amdgpu-install --uninstall --rocmrelease=<release-number>


- Uninstalling all ROCm Releases

  .. code-block:: bash

      sudo amdgpu-install --uninstall --rocmrelease=all

Multi-versioned ROCm Installation
=================================

By default (without the --rocmrelease option) the installer script will install
packages in the single-version layout.

For the multi-version ROCm installation you must use the installer script from
the latest release of ROCm that you wish to install.

**Example:** If you want to install ROCm releases 5.5.3, 5.6.1 and 5.7
simultaneously, you are required to download the installer from the latest ROCm
release 5.7.

You must add the ROCm repositories manually for all ROCm releases you want to
install except the latest one. The amdgpu-install script automatically adds the
required repositories for the latest release.

See the section "Register ROCm Packages" in :doc:`/how-to/native-install/index`
for:

- :ref:`Ubuntu <ubuntu-register-rocm>`

Aditional options
*****************

Unattended installation
=======================

Adding ``-y`` as a parameter to amdgpu-install skips user prompts (for
automation). For example:

.. code-block:: bash

    amdgpu-install -y --usecase=rocm

Skipping kernel mode driver installation
========================================

The installer script tries to install the kernel mode driver along with the
requested use cases. This might be unnecessary as in the case of docker
containers or you may wish to keep a specific version when using multi-version
installation, and not have the last installed version overwrite the kernel mode
driver.

To skip the installation of the kernel-mode driver add the --no-dkms option when
calling the installer script.
