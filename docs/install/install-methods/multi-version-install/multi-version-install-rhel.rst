.. meta::
  :description: Install multiple ROCm versions
  :keywords: installation instructions, AMD, ROCm, multiple versions, RHEL, Red Had Enterprise Linux

.. raw:: html

   <meta http-equiv="refresh" content="0; url=https://rocm.docs.amd.com/en/latest/install/rocm.html">

$$$$$$$$$$$$$$
Redirecting...
$$$$$$$$$$$$$$

.. important::

   This page has moved! Go to `<https://rocm.docs.amd.com/en/latest/install/rocm.html>`__ for the latest instructions on installing ROCm.

.. _rhel-multi-version_install:

*******************************************************
Red Hat Enterprise Linux multi-version installation
*******************************************************

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met.

.. _rhel-multi-register-rocm:

Registering ROCm repositories
=====================================================

.. datatemplate:nodata::

   .. tab-set::
      {% for os_version in config.html_context['rhel_multi_versions'] %}
      {% set os_major, _  = os_version.split('.') %}
      .. tab-item:: RHEL {{ os_version }}
            :sync: rhel-{{ os_version }}

            .. code-block:: bash
               :substitutions:

               # Note: There is NO trailing .0 in the patch version for repositories
               for ver in |rocm_multi_versions_new|; do
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

.. _rhel-multi-install:

Installing
=====================================================

Install kernel driver
--------------------------------------------------------------------------

For information about the AMDGPU driver installation, see the `Red Hat Enterprise Linux native installation <https://instinct.docs.amd.com/projects/amdgpu-docs/en/docs-30.30.4/install/detailed-install/package-manager/package-manager-rhel.html>`_ in the AMD Instinct Data Center GPU Documentation.

For information about driver compatibility, see :doc:`../../../reference/user-kernel-space-compat-matrix`.

Install ROCm
--------------------------------------------------------------------------

Before proceeding with a multi-version ROCm installation, you must remove
ROCm packages that were previously installed from a single-version
installation to avoid conflicts.

.. code-block:: bash
   :substitutions:

   # Note: There IS a trailing .0 in the patch version for packages
   for ver in |rocm_multi_versions_package_versions_new|; do
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
   follow the steps in :doc:`../package-manager/package-manager-rhel` in the ROCm documentation.

.. _rhel-multi-uninstall:

Uninstalling
=====================================================

Uninstall specific meta packages
---------------------------------------------------------------------------

.. code-block:: bash
   :substitutions:

   # Note: There IS a trailing .0 in the patch version for packages
   for ver in |rocm_multi_versions_package_versions_new|; do
      sudo dnf remove rocm$ver
   done

Uninstall ROCm packages
---------------------------------------------------------------------------

.. code-block:: bash
   :substitutions:

   # Note: There IS a trailing .0 in the patch version for packages
   for ver in |rocm_multi_versions_package_versions_new|; do
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
