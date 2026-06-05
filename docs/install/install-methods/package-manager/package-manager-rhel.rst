.. meta::
  :description: Red Hat Enterprise Linux native installation
  :keywords: ROCm install, installation instructions, RHEL, Red Hat Enterprise Linux native installation,
    AMD, ROCm

**********************************************************************************************
Red Hat Enterprise Linux native installation
**********************************************************************************************

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met.

.. Note::

    The following installation steps also apply when upgrading from a previous ROCm version.

.. _rhel-register-repo:

Registering ROCm repositories
=====================================================

.. datatemplate:nodata::

    .. tab-set::

        {% for os_version in config.html_context['rhel_version_numbers'] %}
        {% set os_major, _  = os_version.split('.') %}
        .. tab-item:: RHEL {{ os_version }}
            :sync: rhel-{{ os_version }}

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
                name=AMD Graphics 7.2.1 repository
                {% if os_major == '9' -%}
                baseurl=https://repo.radeon.com/graphics/7.2.1/el/{{ os_version }}/main/x86_64/
                {%- else -%}
                baseurl=https://repo.radeon.com/graphics/7.2.1/el/{{ os_major }}/main/x86_64/
                {%- endif %}
                enabled=1
                priority=50
                gpgcheck=1
                gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key                
                EOF
                sudo dnf clean all
        {% endfor %}

.. _rhel-install:

Installing
=====================================================

Install kernel driver
--------------------------------------------------------------------------

For information about the AMDGPU driver installation, see the `Red Hat Enterprise Linux native installation <https://instinct.docs.amd.com/projects/amdgpu-docs/en/docs-30.30.2/install/detailed-install/package-manager/package-manager-rhel.html>`_ in the AMD Instinct Data Center GPU Documentation.

For information about driver compatibility, see :doc:`../../../reference/user-kernel-space-compat-matrix`.

Install ROCm
--------------------------------------------------------------------------

.. code-block:: bash

    sudo dnf install rocm

.. include:: ../includes/meta-package-table.rst

.. _rhel-post-install:

Post-installation
=====================================================

Complete the :doc:`../../post-install`.

.. _rhel-package-manager-uninstall:

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
