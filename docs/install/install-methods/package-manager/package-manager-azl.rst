.. meta::
  :description: Azure Linux native installation
  :keywords: ROCm install, installation instructions, AZL, Azure Linux native installation,
    AMD, ROCm

**********************************************************************************************
Azure Linux native installation
**********************************************************************************************

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met.

.. Note::

    The following installation steps also apply when upgrading from a previous ROCm version.

.. _azl-register-repo:

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

                sudo tee /etc/yum.repos.d/rocm.repo <<EOF
                [rocm]
                name=ROCm |rocm_version| repository
                baseurl=https://repo.radeon.com/rocm/azurelinux{{ os_major }}/|rocm_version|/main/
                enabled=1
                gpgcheck=1
                gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
                EOF
                sudo tdnf clean all
        {% endfor %}

.. _azl-install:

Installing
=====================================================

Install kernel driver
--------------------------------------------------------------------------

For information about the AMDGPU driver installation, see :ref:`amdgpu-driver-install` in the ROCm documentation.

For information about driver compatibility, see :doc:`../../../reference/user-kernel-space-compat-matrix`.

Install ROCm
--------------------------------------------------------------------------

.. code-block:: bash

    sudo tdnf install rocm

.. include:: ../includes/meta-package-table.rst

.. _azl-post-install:

Post-installation
=====================================================

Complete the :doc:`../../post-install`.

.. _azl-package-manager-uninstall:

Uninstalling
=====================================================

Uninstall ROCm meta packages
---------------------------------------------------------------------------

.. code-block:: bash

    sudo tdnf remove rocm
    sudo tdnf remove rocm-core

Remove ROCm repositories
---------------------------------------------------------------------------

.. code-block:: bash

    # Remove the repositories
    sudo rm /etc/yum.repos.d/rocm.repo*

    # Clear the cache and clean the system
    sudo rm -rf /var/cache/tdnf
    sudo tdnf clean all

.. Important::

    To apply all settings, reboot your system.

