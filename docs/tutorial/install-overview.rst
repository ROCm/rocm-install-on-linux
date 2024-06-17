.. meta::
  :description: ROCm installation options
  :keywords: ROCm installation, AMD, ROCm, Package manager, AMDGPU, single-version installation,
    multi-version installation

.. _rocm-install-overview:

*************************************************************
ROCm installation overview
*************************************************************

If you're new to ROCm, we recommend using the :ref:`rocm-install-quick`.

.. note::
    If you're using a Radeon GPU with graphical applications, refer to the
    `Radeon installation instructions <https://www.amd.com/en/support/kb/faq/rs-install>`_.

To install ROCm, you can use the package manager or the AMDGPU installer. You can also opt for
single-version or multi-version installation. These topics are described in detail in the following
sections.

Installation methods
######################

* :ref:`package_manager_versus_amdgpu`
* :ref:`Multi version installation (Optional) <multi-version-install-overview>`


.. _package_manager_versus_amdgpu:

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

* :doc:`Package manager installation <../how-to/native-install/index>`
* :doc:`AMDGPU installation <../how-to/amdgpu-install>`

.. _multi-version-install-overview:

Multi version installation (Optional)
===========================================================

A select few users may want to install multiple versions of ROCm. Multi version installation covers situations where you need multiple versions of ROCm on the same machine. 
Follow :doc:`installing multiple ROCm versions<../how-to/native-install/multi-version-install>` for instructions.