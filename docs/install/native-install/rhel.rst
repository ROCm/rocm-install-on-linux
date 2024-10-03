.. meta::
  :description: Red Hat Enterprise Linux native installation
  :keywords: ROCm install, installation instructions, RHEL, Red Hat Enterprise Linux native installation,
    AMD, ROCm

**********************************************************************************************
Red Hat Enterprise Linux native installation
**********************************************************************************************

.. important::

    Make sure that the :doc:`/install/prerequisites` are met before installing.

.. _rhel-register-repo:

Registering ROCm repositories
=====================================================

Register kernel-mode driver
----------------------------------------------------------------------------------------------------------

.. datatemplate:nodata::

    .. tab-set::
        {% for os_version in config.html_context['rhel_version_numbers'] %}
        {% set os_major, _  = os_version.split('.') %}
        .. tab-item:: RHEL {{ os_version }}
            :sync: rhel-{{ os_version }} rhel-{{ os_major }}

            .. code-block:: bash
                :substitutions:

                sudo tee /etc/yum.repos.d/amdgpu.repo <<EOF
                [amdgpu]
                name=amdgpu
                baseurl=https://repo.radeon.com/amdgpu/|rocm_version|/el/{{ os_version }}/main/x86_64/
                enabled=1
                priority=50
                gpgcheck=1
                gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
                EOF
                sudo dnf clean all
        {% endfor %}

.. _rhel-register-rocm:

Register ROCm packages
----------------------------------------------------------------------------------------------------------

.. datatemplate:nodata::

    .. tab-set::
        {% for os_release in config.html_context['rhel_release_version_numbers']  %}
        .. tab-item:: RHEL {{ os_release }}
            :sync: rhel-{{ os_release }}

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

.. _rhel-install:

Installing
=====================================================

Install kernel driver
----------------------------------------------------------------------------------------------------------

.. code-block:: bash

    sudo dnf install amdgpu-dkms
    sudo reboot

Install ROCm packages
----------------------------------------------------------------------------------------------------------

.. code-block:: bash

    sudo dnf install rocm

Complete the :doc:`../post-install`.

.. _rhel-upgrade:

Upgrading
=====================================================

To upgrade an existing ROCm installation to a newer version, follow the steps in
:ref:`rhel-register-repo` and :ref:`rhel-install`.

.. note::

    Upgrading the kernel driver may also upgrade the GPU firmware, which requires a
    system reboot to take effect.

.. _rhel-uninstall:

Uninstalling
=====================================================

Uninstall specific meta packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    # sudo apt autoremove <package-name>
    # For example:
    sudo dnf remove rocm
    # Or for version specific packages:
    sudo dnf remove rocm|rocm_version|

Uninstall ROCm packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    sudo dnf remove rocm-core
    # Or for version specific packages:
    sudo dnf remove rocm-core|rocm_version|

Uninstall kernel-mode driver
---------------------------------------------------------------------------

.. code-block:: bash

    sudo dnf remove amdgpu-dkms

Remove ROCm and AMDGPU repositories
---------------------------------------------------------------------------

.. code-block:: bash

    # Remove the repositories.
    sudo rm /etc/yum.repos.d/rocm.list
    sudo rm /etc/yum.repos.d/amdgpu.list

    # Clear the cache and clean the system.
    sudo rm -rf /var/cache/yum
    sudo dnf clean all

    # Restart the system.
    sudo reboot
