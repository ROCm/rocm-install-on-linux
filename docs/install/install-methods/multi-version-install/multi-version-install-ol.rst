.. meta::
  :description: Install multiple ROCm versions
  :keywords: installation instructions, AMD, ROCm, multiple versions, OL, Oracle Linux

.. _ol-multi-version_install:

*****************************************
Oracle Linux multi-version installation
*****************************************

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met.


.. _ol-multi-register-rocm:

Register ROCm repositories
=====================================================

.. datatemplate:nodata::

   .. tab-set::
      {% for os_version in config.html_context['ol_version_numbers'] %}
      {% set os_major, _  = os_version.split('.') %}
      .. tab-item:: OL {{ os_version }}
            :sync: ol-{{ os_version }}

            .. code-block:: bash
               :substitutions:

               # Note: There is NO trailing .0 in the patch version for repositories
               for ver in |rocm_multi_versions|; do
               sudo tee --append /etc/yum.repos.d/rocm.repo <<EOF
               [rocm-$ver]
               name=ROCm $ver repository
               baseurl=https://repo.radeon.com/rocm/el{{ os_major }}/$ver/main
               enabled=1
               priority=50
               gpgcheck=1
               gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
               EOF
               done
               sudo dnf clean all
      {% endfor %}

.. _ol-multi-install:

Installing
=====================================================

Install kernel driver
--------------------------------------------------------------------------

For information about the AMDGPU driver installation, see the `Oracle Linux native installation <https://instinct.docs.amd.com/projects/amdgpu-docs/en/docs-30.20.0/install/detailed-install/package-manager/package-manager-ol.html>`_ in the AMD Instinct Data Center GPU Documentation.

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
         sudo dnf install rocm$ver
   done

.. note::

      For versions earlier than ROCm 6.0.0, use ``rocm-hip-sdk`` instead of ``rocm`` (for example, ``rocm-hip-sdk5.7.1``).

.. _ol-multi-post-install:

Post-installation
=====================================================

Complete the :doc:`../../post-install`.

.. tip::

   For a single-version installation of the latest ROCm version on OL,
   follow the steps in :doc:`../package-manager/package-manager-ol` in the ROCm documentation.

.. _ol-multi-uninstall:

Uninstalling
=====================================================

Uninstall specific meta packages
---------------------------------------------------------------------------

.. code-block:: bash
   :substitutions:

   # Note: There IS a trailing .0 in the patch version for packages
   for ver in |rocm_multi_versions_package_versions|; do
      sudo dnf remove rocm$ver
   done

Uninstall ROCm packages
---------------------------------------------------------------------------

.. code-block:: bash
   :substitutions:

   # Note: There IS a trailing .0 in the patch version for packages
   for ver in |rocm_multi_versions_package_versions|; do
      sudo dnf remove rocm-core$ver amdgpu-core$ver
   done

Remove ROCm repositories
---------------------------------------------------------------------------

.. code-block:: bash

   # Remove ROCm repositories
   sudo rm /etc/yum.repos.d/rocm.repo*

   # Clear the cache and clean the system
   sudo rm -rf /var/cache/dnf
   sudo dnf clean all

.. Important::

    To apply all settings, reboot your system.
