.. meta::
  :description: ROCm installation options
  :keywords: ROCm installation, AMD, ROCm, Package manager, AMDGPU, single-version installation,
    multi-version installation

.. _rocm-install-overview:

*************************************************************
ROCm installation options
*************************************************************

To install ROCm, you can use the AMDGPU installer or the package manager. You can also opt for
single-version or multi-version installation. These topics are described in detail in the following
sections.

If you're new to ROCm, we recommend using the :ref:`rocm-install-quick` guide.

.. note::
    If you're using a Radeon GPU with graphical applications, refer to the
    `Radeon installation instructions <https://www.amd.com/en/support/kb/faq/rs-install>`_.

Package manager versus AMDGPU installer
===========================================================

ROCm supports two methods for installation:

- Using the Linux distribution package manager
- Running the ``amdgpu-install`` script

There is no difference in the final installation between these two methods.

Using the distribution's package manager lets the user install,
upgrade and uninstall using familiar commands and workflows. Third party
ecosystem support is the same as your OS package manager.

The ``amdgpu-install`` script is a wrapper around the package manager. The same
packages are installed by this script as the package manager system.

The installer automates the installation process for the AMDGPU
and ROCm stack. It handles the complete installation process
for ROCm, including setting up the repository, cleaning the system, updating,
and installing the desired drivers and meta-packages. Users who are
less familiar with the package manager can choose this method for ROCm
installation.

.. _installation-types:

Single-version versus multi-version installation
===========================================================

ROCm packages are versioned with both semantic versioning that is package
specific and a ROCm release version.

Single-version installation
---------------------------------------------------------------------------------

The single-version ROCm installation refers to the following:

- Installation of a single instance of the ROCm release on a system
- Use of non-versioned ROCm meta-packages

Multi-version installation
---------------------------------------------------------------------------------

The multi-version installation refers to the following:

- Installation of multiple instances of the ROCm stack on a system. Extending
  the package name and its dependencies with the release version adds the
  ability to support multiple versions of packages simultaneously.
- Use of versioned ROCm meta-packages.

.. attention::
    ROCm packages that were previously installed from a single-version installation
    must be removed before proceeding with the multi-version installation to avoid
    conflicts.

.. note::
    Multi-version install is not available for the kernel driver module, also referred to as AMDGPU.

The following image demonstrates the difference between single-version and
multi-version ROCm installation types:

.. image:: /data/install/linux/linux001.png
    :alt: ROCm Installation Types
