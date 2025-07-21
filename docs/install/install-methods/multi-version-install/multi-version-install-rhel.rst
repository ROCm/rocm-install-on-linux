.. meta::
  :description: Install multiple ROCm versions
  :keywords: installation instructions, AMD, ROCm, multiple versions, RHEL, Red Had Enterprise Linux

.. _rhel-multi-version_install:

*******************************************************
Red Hat Enterprise Linux multi-version installation
*******************************************************

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met before installing.

.. _rhel-multi-register-rocm:

Registering ROCm repositories
=====================================================

.. datatemplate:nodata::

   .. tab-set::
      {% for os_release in config.html_context['rhel_release_version_numbers']  %}
      .. tab-item:: RHEL {{ os_release }}
            :sync: rhel-{{ os_release }}

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

.. _rhel-multi-install:

Installing
=====================================================

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

.. _rhel-multi-post-install:

Post-installation
=====================================================

Complete the :doc:`../../post-install`.

.. tip::

   For a single-version installation of the latest ROCm version on RHEL,
   use the steps in :ref:`rhel-register-repo` and :ref:`rhel-install`.

.. _rhel-multi-uninstall:

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

.. note::

    For information about the AMDGPU driver installation, see the `Red Hat Enterprise Linux native installation <https://instinct.docs.amd.com/projects/amdgpu-docs/en/latest/install/detailed-install/package-manager/package-manager-rhel.html>`_ in the AMD Instinct Data Center GPU Documentation.