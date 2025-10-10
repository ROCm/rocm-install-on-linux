.. meta::
  :description: Install multiple ROCm versions
  :keywords: installation instructions, AMD, ROCm, multiple versions, SLES, SUSE Linux Enterprise

.. _sles-multi-version_install:

***************************************************
SUSE Linux Enterprise multi-version installation
***************************************************

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met before installing.

.. _sles-multi-register-rocm:

Registering ROCm repositories
===============================================

.. datatemplate:nodata::

   .. tab-set::
      .. tab-item:: SLES 15.6

            .. code-block:: bash
               :substitutions:
               
               # Note: There is NO trailing .0 in the patch version for repositories
               for ver in |rocm_multi_versions|; do
               sudo tee --append /etc/zypp/repos.d/rocm.repo <<EOF
               [ROCm-$ver]
               name=ROCm$ver
               baseurl=https://repo.radeon.com/rocm/zyp/$ver/main
               enabled=1
               gpgcheck=1
               gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
               EOF
               done
               sudo zypper refresh

.. _sles-multi-install:

Installing
=====================================================

Install kernel driver
--------------------------------------------------------------------------

For information about the AMDGPU driver installation, see the `SUSE Linux Enterprise Server native installation <https://instinct.docs.amd.com/projects/amdgpu-docs/en/latest/install/detailed-install/package-manager/package-manager-sles.html>`_ in the AMD Instinct Data Center GPU Documentation.

For information about driver compatibility, see :doc:`../../../reference/user-kernel-space-compat-matrix`.

Install ROCm
--------------------------------------------------------------------------

Before proceeding with a multi-version ROCm installation, you must remove
ROCm packages that were previously installed from a single-version
installation to avoid conflicts.

.. code-block:: bash
   :substitutions:

   # Note: There IS a trailing .0 in the patch version for packages
   for ver in |rocm_multi_versions_package_versions|; do
         sudo zypper --gpg-auto-import-keys install rocm$ver
   done

.. note::

      For versions earlier than ROCm 6.0.0, use ``rocm-hip-sdk`` instead of ``rocm`` (for example, ``rocm-hip-sdk5.7.1``).


.. _sles-multi-post-install:

Post-installation
=====================================================

Complete the :doc:`../../post-install`.

.. tip::

   For a single-version installation of the latest ROCm version on SLES,
   use the steps in :ref:`sles-register-repo` and :ref:`sles-install`.

.. _sles-multi-uninstall:

Uninstalling
=====================================================

Uninstall specific meta packages
---------------------------------------------------------------------------

.. code-block:: bash
   :substitutions:

   # Note: There IS a trailing .0 in the patch version for packages
   for ver in |rocm_multi_versions_package_versions|; do
      sudo zypper remove rocm$ver
   done

Uninstall ROCm packages
---------------------------------------------------------------------------

.. code-block:: bash
   :substitutions:

   # Note: There IS a trailing .0 in the patch version for packages
   for ver in |rocm_multi_versions_package_versions|; do
      sudo zypper remove rocm-core$ver amdgpu-core$ver
   done

Remove ROCm repositories
---------------------------------------------------------------------------

.. code-block:: bash
   :substitutions:

   # Remove the repositories
   # Note: There is NO trailing .0 in the patch version for repositories
   for ver |rocm_multi_versions|; do
      sudo zypper removerepo "ROCm-$ver"
   done
   
   # Clear cache and clean system
   sudo zypper clean --all
   sudo zypper refresh
   
   # Restart the system
   sudo reboot

