.. meta::
  :description: Oracle Linux native installation
  :keywords: ROCm install, installation instructions, OL, Oracle Linux native installation,
    AMD, ROCm

**********************************************************************************************
Oracle Linux native installation
**********************************************************************************************

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met before installing.

.. _ol-register-repo:

Register ROCm repositories
=====================================================

.. datatemplate:nodata::

    .. tab-set::
        {% for os_release in config.html_context['ol_release_version_numbers']  %}
        .. tab-item:: OL {{ os_release }}
            :sync: ol-{{ os_release }}

            .. code-block:: bash
                :substitutions:

                sudo tee --append /etc/yum.repos.d/rocm.repo <<EOF
                [ROCm-|rocm_version|]
                name=ROCm|rocm_version|
                baseurl=https://repo.radeon.com/rocm/el{{ os_release }}/|rocm_version|/main
                enabled=1
                priority=50
                gpgcheck=1
                gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
                EOF
                sudo dnf clean all
        {% endfor %}

.. _ol-install:

Installing
=====================================================

Install kernel driver
--------------------------------------------------------------------------

For information about the AMDGPU driver installation, see the `Oracle Linux native installation <https://instinct.docs.amd.com/projects/amdgpu-docs/en/latest/install/detailed-install/package-manager/package-manager-ol.html>`_ in the AMD Instinct Data Center GPU Documentation.

For information about driver compatibility, see :doc:`../../../reference/user-kernel-space-compat-matrix`.

Install ROCm
--------------------------------------------------------------------------

.. code-block:: bash

    sudo dnf install rocm

Complete the :doc:`../../post-install`.

.. _ol-upgrade:

Upgrading
=====================================================

To upgrade an existing ROCm installation to a newer version, follow the steps in
:ref:`rhel-register-repo` and :ref:`rhel-install`.

.. note::

    Upgrading the kernel driver may also upgrade the GPU firmware, which requires a
    system reboot to take effect.

.. _ol-package-manager-uninstall:

Uninstalling
=====================================================

Uninstall specific meta packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    sudo dnf remove rocm

Uninstall ROCm packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    sudo dnf remove rocm-core amdgpu-core

Remove ROCm repositories
---------------------------------------------------------------------------

.. code-block:: bash

    # Remove the repositories
    sudo rm /etc/yum.repos.d/rocm.repo*
    
    # Clear the cache and clean the system
    sudo rm -rf /var/cache/dnf
    sudo dnf clean all
    
    # Restart the system
    sudo reboot

