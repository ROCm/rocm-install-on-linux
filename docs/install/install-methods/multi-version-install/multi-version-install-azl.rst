.. meta::
  :description: Install multiple ROCm versions
  :keywords: installation instructions, AMD, ROCm, multiple versions, AZL, Azure Linux

.. _azl-multi-version_install:

*****************************************
Azure Linux multi-version installation
*****************************************

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met.

.. _azl-multi-register-rocm:

Registering ROCm repositories
=====================================================

.. datatemplate:nodata::

   .. tab-set::
      {% for os_version in config.html_context['azl_version_numbers'] %}
      {% set os_major, _  = os_version.split('.') %}
      .. tab-item:: AZL {{ os_version }}
            :sync: azl-{{ os_version }}

            .. code-block:: bash
               :substitutions:

               # Note: There is NO trailing .0 in the patch version for repositories
               for ver in |rocm_multi_versions|; do
               sudo tee --append /etc/yum.repos.d/rocm.repo <<EOF
               [rocm-$ver]
               name=ROCm $ver repository
               baseurl=https://repo.radeon.com/rocm/azurelinux{{ os_major }}/$ver/main/
               enabled=1
               gpgcheck=1
               gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
               EOF
               done
               sudo tdnf clean all
      {% endfor %}

.. _azl-multi-install:

Installing
=====================================================

Install kernel driver
--------------------------------------------------------------------------

For information about the AMDGPU driver installation, see :ref:`amdgpu-driver-install` in the ROCm documentation.

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
         sudo tdnf install rocm$ver
   done

.. note::

      For versions earlier than ROCm 6.0.0, use ``rocm-hip-sdk`` instead of ``rocm`` (for example, ``rocm-hip-sdk5.7.1``).

.. _azl-multi-post-install:

Post-installation
=====================================================

Complete the :doc:`../../post-install`.

.. tip::

   For a single-version installation of the latest ROCm version on AZL,
   follow the steps in :doc:`../package-manager/package-manager-azl` in the ROCm documentation.

.. _azl-multi-uninstall:

Uninstalling
=====================================================

Uninstall specific meta packages
---------------------------------------------------------------------------

.. code-block:: bash
   :substitutions:

   # Note: There IS a trailing .0 in the patch version for packages
   for ver in |rocm_multi_versions_package_versions|; do
      sudo tdnf remove rocm$ver
   done

Uninstall ROCm packages
---------------------------------------------------------------------------

.. code-block:: bash
   :substitutions:

   # Note: There IS a trailing .0 in the patch version for packages
   for ver in |rocm_multi_versions_package_versions|; do
      sudo tdnf remove rocm-core$ver
   done

Remove ROCm repositories
---------------------------------------------------------------------------

.. code-block:: bash

      # Remove ROCm repositories
      sudo rm /etc/yum.repos.d/rocm.repo*

      # Clear the cache and clean the system
      sudo rm -rf /var/cache/tdnf
      sudo tdnf clean all

.. Important::

    To apply all settings, reboot your system.
