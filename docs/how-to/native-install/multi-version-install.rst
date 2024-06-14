.. meta::
  :description: Install multiple ROCm versions
  :keywords: installation instructions, AMD, ROCm, multiple versions

*********************************
Installing multiple ROCm versions
*********************************

A multi-version ROCm installation covers situations where you need multiple
versions of ROCm on the same machine -- for compatibility with different
applications and hardware, testing, and other use cases.

.. _installation-types:

A multi-version ROCm installation involves the following.

* Installing multiple instances of the ROCm stack on a system.

* Using versioned ROCm meta-packages. ROCm packages are versioned with both
  a ROCm release version and package-specific semantic versioning. Extending a
  package name and its dependencies with the release version adds the ability to
  support multiple versions of packages simultaneously.

A single-version ROCm installation involves the following.

* Installing a single instance of the ROCm release on a system.

* Using non-versioned ROCm meta-packages.

See :doc:`../../tutorial/quick-start` or :doc:`../../tutorial/detailed-install` for
a standard single-version installation.

The following diagram illustrates the difference between single-version and
multi-version ROCm installations.

.. image:: /data/install/linux/linux001.png
    :alt: ROCm Installation Types

.. note::

   The AMDGPU kernel driver module does not support multi-version installation.


Using your package manager
==========================

Before proceeding with a multi-version ROCm installation, you must remove
ROCm packages that were previously installed from a single-version
installation to avoid conflicts.

.. tab-set::

   .. tab-item:: Ubuntu

      .. include:: ./includes/ubuntu-multi-install.rst

   .. tab-item:: RHEL

      .. include:: ./includes/rhel-multi-install.rst

   .. tab-item:: SLES

      .. include:: ./includes/sles-multi-install.rst

.. _amdgpu-install-multi-version:

Using the AMDGPU installer
==========================

By default (without the ``--rocmrelease`` option), the ``amdgpu-install``
script installs packages in the single-version layout. See
:doc:`how-to/amdgpu-install` for an overview of the AMDGPU installer.

For a multi-version ROCm installation, you must use the installer script from
the latest ROCm release you want to install.

For example, to install ROCm releases 5.5.3, 5.6.1, and 5.7 simultaneously, you
must download the ROCm 5.7 installer. Then, you must manually add the ROCm
repositories for all ROCm releases you want to install except for the latest
one. The ``amdgpu-install`` script automatically adds the required repositories
for the latest release.

Refer to :ref:`Register ROCm packages <ubuntu-register-rocm>` on the
:doc:`Ubuntu native installation <./native-install/ubuntu>` page.
