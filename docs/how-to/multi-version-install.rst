.. meta::
  :description: Install multiple ROCm versions
  :keywords: installation instructions, AMD, ROCm, multiple versions

******************************
Install multiple ROCm versions
******************************

.. _installation-types:

ROCm packages are versioned with both a ROCm release version and
package-specific semantic versioning.

A conventional, single-version ROCm installation refers to the following:

- Installation of a single instance of the ROCm release on a system
- The use of non-versioned ROCm meta-packages

Multi-version installation
--------------------------

A multi-version ROCm installation refers to the following:

- Installation of multiple instances of the ROCm stack on a system. Extending
  the package name and its dependencies with the release version adds the
  ability to support multiple versions of packages simultaneously.
- The use of versioned ROCm meta-packages.

.. attention::

   Before proceeding with a multi-version ROCm installation, you must remove
   ROCm packages that were previously installed from a single-version
   installation to avoid conflicts.

.. note::

   Multi-version install is not available for the kernel driver module, referred
   to as AMDGPU.

The following image demonstrates the difference between single-version and
multi-version ROCm installation types:

.. image:: /data/install/linux/linux001.png
    :alt: ROCm Installation Types
