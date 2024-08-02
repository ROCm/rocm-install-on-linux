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
    `Radeon installation instructions <https://rocm.docs.amd.com/projects/radeon/en/latest/index.html>`_.

To install ROCm, you can use the package manager or the AMDGPU installer. You can also opt for
single-version or multi-version installation. These topics are described in detail in the following
sections.

Installation methods
######################

* :ref:`package_manager_versus_amdgpu`
* :ref:`Multi version installation (Optional) <multi-version-install-overview>`
* :ref:`ROCM Offline Installer Creator <rocm-offline-installer-creator>`

.. _package_manager_versus_amdgpu:

Package manager versus AMDGPU installer
===========================================================

ROCm supports two methods for installation:

* :doc:`Using the Linux distribution package manager <../install/native-install/index>`
* :doc:`Running the amdgpu-install script <../install/amdgpu-install>`

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

.. _multi-version-install-overview:

Multi version installation (Optional)
===========================================================

A select few users may want to install multiple versions of ROCm. Multi version installation covers situations where you need multiple versions of ROCm on the same machine. 
Follow :doc:`installing multiple ROCm versions<../install/native-install/multi-version-install>` for instructions.

.. _rocm-offline-installer-creator:

ROCm Offline Installer Creator
===========================================================

The ROCm Offline Installer Creator creates an 
installation package for a preconfigured setup of ROCm, the AMDGPU driver, or a combination
of the two on a target system without network or internet access.
See :doc:`ROCm Offline Installer Creator <../install/rocm-offline-installer>` for instructions.
