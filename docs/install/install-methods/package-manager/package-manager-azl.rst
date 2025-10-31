.. meta::
  :description: Azure Linux native installation
  :keywords: ROCm install, installation instructions, AZL, Azure Linux native installation,
    AMD, ROCm

**********************************************************************************************
Azure Linux native installation
**********************************************************************************************

.. important::

    Ensure that the :doc:`/install/prerequisites` are met before installing.

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

                sudo tee --append /etc/yum.repos.d/rocm.repo <<EOF
                [ROCm-|rocm_version|]
                name=ROCm|rocm_version|
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
----------------------------------------------------------------------------------------------------------

.. code-block:: bash

    sudo tdnf install azurelinux-repos-amd
    sudo tdnf repolist --refresh
    sudo tdnf install amdgpu
    sudo modprobe amdgpu

.. note::

    For Azure Linux, the latest amdgpu version supported is from the ROCm 6.2.2 release.

Install ROCm packages
----------------------------------------------------------------------------------------------------------

.. code-block:: bash

    sudo tdnf install rocm

Complete the :doc:`../../post-install`.

.. _azl-upgrade:

Upgrading
=====================================================

To upgrade an existing ROCm installation to a newer version, follow the steps in
:ref:`rhel-register-repo` and :ref:`rhel-install`.

.. note::

    Upgrading the kernel driver may also upgrade the GPU firmware, which requires a
    system reboot to take effect.

.. _azl-package-manager-uninstall:

Uninstalling
=====================================================

Uninstall specific meta packages
---------------------------------------------------------------------------

.. code-block:: bash

    sudo tdnf remove rocm

Uninstall ROCm packages
---------------------------------------------------------------------------

.. code-block:: bash

    sudo tdnf remove rocm-core

Uninstall kernel-mode driver
---------------------------------------------------------------------------

.. code-block:: bash

    sudo tdnf remove amdgpu amdgpu-firmware kernel-drivers-gpu

Remove ROCm and AMDGPU repositories
---------------------------------------------------------------------------

.. code-block:: bash

    # Remove the repositories
    sudo tdnf remove azurelinux-repos-amd
    sudo rm /etc/yum.repos.d/rocm.repo*
    sudo rm /etc/yum.repos.d/amdgpu.repo*

    # Clear the cache and clean the system
    sudo rm -rf /var/cache/tdnf
    sudo tdnf clean all

    # Restart the system.
    sudo reboot
