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
  * If you're using a Radeon GPU with graphical applications, refer to the `Radeon installation instructions <https://rocm.docs.amd.com/projects/radeon/en/latest/index.html>`_.
  * The AMDGPU installer documentation has been removed to encourage the use of the package manager for ROCm installation. While the package manager is the recommended method, you can still install ROCm using the AMDGPU installer by following the `legacy process <https://rocm.docs.amd.com/projects/install-on-linux/en/docs-6.4.1/install/install-methods/amdgpu-installer-index.html>`_. Ensure to update the command with the intended ROCm version before running it.

To install ROCm, you can use the package manager. You can also opt for
single-version or multi-version installation. These topics are described in detail in the following
sections.

Installation methods
######################

* :ref:`package_manager`
* :ref:`Multi-version installation <multi-version-install-overview>`
* :ref:`ROCm Offline Installer Creator <rocm-offline-installer-creator>`
* :ref:`ROCm Runfile Installer <rocm-runfile-installer>`

.. _package_manager:

Package manager
===========================================================

The distribution's package manager lets the user install,
upgrade and uninstall using familiar commands and workflows. Third party
ecosystem support is the same as your OS package manager. See :doc:`Installation via native package manager<../install/install-methods/package-manager-index>` for instructions based on the operating system.

.. _multi-version-install-overview:

Multi-version installation
===========================================================

A multi-version ROCm installation handles situations where users need multiple
versions of ROCm on the same machine for compatibility with different
applications and hardware, testing, and other use cases.
For instructions, see :doc:`Installing multiple ROCm versions<../install/install-methods/multi-version-install-index>`.

.. _rocm-offline-installer-creator:

ROCm Offline Installer Creator
===========================================================

The ROCm Offline Installer Creator creates an 
installation package for a preconfigured setup of ROCm, the AMDGPU driver, or a combination
of the two on a target system without network or internet access.
See :doc:`ROCm Offline Installer Creator <../install/rocm-offline-installer>` for instructions.

.. _rocm-runfile-installer:

ROCm Runfile Installer
===========================================================

The ROCm Runfile Installer lets you install ROCm without using a native Linux package management system.
It can be used with or without network or internet access.
See :doc:`ROCm Runfile Installer <../install/rocm-runfile-installer>` for instructions.