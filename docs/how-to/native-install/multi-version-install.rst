.. meta::
  :description: Install multiple ROCm versions
  :keywords: installation instructions, AMD, ROCm, multiple versions

******************************
Install multiple ROCm versions
******************************

A multi-version ROCm installation covers situations where you need multiple
verions of ROCm on the same machine -- for compatibility with different
applications and hardware, testing, and other use cases.

.. _installation-types:

A multi-version ROCm installation involves the following:

* Installing multiple instances of the ROCm stack on a system.
* Using versioned ROCm meta-packages. ROCm packages are versioned with both
  a ROCm release version and package-specific semantic versioning. Extending a
  package name and its dependencies with the release version adds the ability to
  support multiple versions of packages simultaneously.

A standard single-version ROCm installation involves the following:

* Installing a single instance of the ROCm release on a system.
* Using non-versioned ROCm meta-packages.

The following diagram illustrates the difference between single-version and
multi-version ROCm installations.

.. image:: /data/install/linux/linux001.png
    :alt: ROCm Installation Types

.. note::

   The AMDGPU kernel driver module does not support multi-version installation.


Multi-version installation via package manager
==============================================

.. caution::

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
