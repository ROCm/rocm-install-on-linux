.. meta::
  :description: ROCm installation options
  :keywords: ROCm installation, AMD, ROCm, Package manager, AMDGPU, single-version installation,
    multi-version installation

.. _rocm-install-overview:

*************************************************************
ROCm installation overview
*************************************************************

To install ROCm, you can use the AMDGPU installer or the package manager. You can also opt for
single-version or multi-version installation. These topics are described in detail in the following
sections.

If you're new to ROCm, we recommend using the :ref:`rocm-install-quick`.

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
