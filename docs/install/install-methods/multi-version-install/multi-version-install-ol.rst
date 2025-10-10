.. meta::
  :description: Install multiple ROCm versions
  :keywords: installation instructions, AMD, ROCm, multiple versions, OL, Oracle Linux

.. _multi-version_install:

*********************************
Oracle Linux multi-version installation
*********************************

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met before installing.


.. _ol-multi-register-rocm:

Register ROCm repositories
=====================================================

.. datatemplate:nodata::

   .. tab-set::
      {% for os_release in config.html_context['ol_release_version_numbers']  %}
      .. tab-item:: OL {{ os_release }}
            :sync: ol-{{ os_release }}

            .. code-block:: bash
               :substitutions:

               # Note: There is NO trailing .0 in the patch version for repositories
               for ver in |rocm_multi_versions|; do
               sudo tee --append /etc/yum.repos.d/rocm.repo <<EOF
               [ROCm-$ver]
               name=ROCm$ver
               baseurl=https://repo.radeon.com/rocm/el{{ os_release }}/$ver/main
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

For information about the AMDGPU driver installation, see the `Oracle Linux native installation <https://instinct.docs.amd.com/projects/amdgpu-docs/en/latest/install/detailed-install/package-manager/package-manager-ol.html>`_ in the AMD Instinct Data Center GPU Documentation.

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

Complete the :doc:`../../post-install`.

.. tip::

   For a single-version installation of the latest ROCm version on OL,
   use the steps in :ref:`ol-register-repo` and :ref:`ol-install`.

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

   # Restart the system
   sudo reboot
