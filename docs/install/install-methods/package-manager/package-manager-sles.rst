.. meta::
  :description: SUSE Enterprise Linux native installation
  :keywords: ROCm install, installation instructions, SUSE, SUSE Linux Enterprise Server native installation,
    AMD, ROCm

*********************************************************************************************
SUSE Linux Enterprise Server native installation
*********************************************************************************************

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met.

.. Note::

    The following installation steps also apply when upgrading from a previous ROCm version.

.. _sles-register-repo:

Registering ROCm repositories
===============================================

.. datatemplate:nodata::

   .. tab-set::
      {% for os_version in config.html_context['sles_version_numbers'] %}
      .. tab-item:: SLES {{ os_version }}
            :sync: sles-{{ os_version }}

            .. code-block:: bash
                :substitutions:

                sudo tee /etc/zypp/repos.d/rocm.repo <<EOF
                [rocm]
                name=ROCm |rocm_directory_version| repository
                baseurl=https://repo.radeon.com/rocm/zyp/|rocm_version|/main
                enabled=1
                gpgcheck=1
                gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key

                [amdgraphics]
                name=AMD Graphics |rocm_version| repository
                baseurl=https://repo.radeon.com/graphics/|rocm_version|/sle/{{ os_version }}/main/x86_64/
                enabled=1
                priority=50
                gpgcheck=1
                gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key                
                EOF             
                sudo zypper refresh
      {% endfor %}


.. _sles-install:

Installing
===============================================

Install kernel driver
--------------------------------------------------------------------------

For information about the AMDGPU driver installation, see the `SUSE Linux Enterprise Server native installation <https://instinct.docs.amd.com/projects/amdgpu-docs/en/docs-|udev_amdgpu_version|/install/detailed-install/package-manager/package-manager-sles.html>`_ in the AMD Instinct Data Center GPU Documentation.

For information about driver compatibility, see :doc:`../../../reference/user-kernel-space-compat-matrix`.

Install ROCm
--------------------------------------------------------------------------

.. code-block:: bash

    sudo zypper --gpg-auto-import-keys install rocm

.. include:: ../includes/meta-package-table.rst

.. _sles-post-install:

Post-installation
=====================================================

Complete the :doc:`../../post-install`.

.. _sles-package-manager-uninstall:

Uninstalling
================================================

Uninstall ROCm meta packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    sudo zypper remove rocm
    sudo zypper remove rocm-core amdgpu-core

Remove ROCm repositories
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    # Remove ROCm repositories
    sudo zypper removerepo "rocm"
    sudo zypper removerepo "amdgraphics"
    
    # Clear cache and clean system
    sudo zypper clean --all
    sudo zypper refresh
    
.. Important::

    To apply all settings, reboot your system.
