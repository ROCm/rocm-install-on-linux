.. meta::
  :description: Rocky Linux native installation
  :keywords: ROCm install, installation instructions, Rocky Linux, Rocky Linux native installation,
    AMD, ROCm

**********************************************************************************************
Rocky Linux native installation
**********************************************************************************************

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met before installing.

.. Note::

    The following installation steps also apply when upgrading from a previous ROCm version.

.. _rl-register-repo:

Registering ROCm repositories
=====================================================

.. datatemplate:nodata::

    .. tab-set::

        {% for os_version in config.html_context['rl_version_numbers'] %}
        {% set os_major, _  = os_version.split('.') %}
        .. tab-item:: Rocky {{ os_version }}
            :sync: rl-{{ os_version }}

            .. code-block:: bash
                :substitutions:

                sudo tee /etc/yum.repos.d/rocm.repo <<EOF
                [rocm]
                name=ROCm |rocm_directory_version| repository
                baseurl=https://repo.radeon.com/rocm/el{{ os_major }}/|rocm_version|/main
                enabled=1
                priority=50
                gpgcheck=1
                gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key

                [amdgraphics]
                name=AMD Graphics |rocm_directory_version| repository
                baseurl=https://repo.radeon.com/graphics/|rocm_version|/el/{{ os_version }}/main/x86_64/
                enabled=1
                priority=50
                gpgcheck=1
                gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key                
                EOF
                sudo dnf clean all
        {% endfor %}

.. _rl-install:

Installing
=====================================================

Install kernel driver
--------------------------------------------------------------------------

For information about the AMDGPU driver installation, see the `Rocky Linux native installation <https://instinct.docs.amd.com/projects/amdgpu-docs/en/latest/install/detailed-install/package-manager/package-manager-rl.html>`_ in the AMD Instinct Data Center GPU Documentation.

For information about driver compatibility, see :doc:`../../../reference/user-kernel-space-compat-matrix`.

Install ROCm
--------------------------------------------------------------------------

.. code-block:: bash

    sudo dnf install rocm

.. include:: ../includes/meta-package-table.rst

.. _rl-post-install:

Post-installation
=====================================================

Complete the :doc:`../../post-install`.

.. _rl-package-manager-uninstall:

Uninstalling
=====================================================

Uninstall ROCm meta packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    sudo dnf remove rocm
    sudo dnf remove rocm-core amdgpu-core

Remove ROCm repositories
---------------------------------------------------------------------------

.. code-block:: bash
    
    # Remove the repositories
    sudo rm /etc/yum.repos.d/rocm.repo*

    # Clear the cache and clean the system
    sudo rm -rf /var/cache/dnf
    sudo dnf clean all

.. Important::

    To apply all settings, reboot your system.
