Red Hat Enterprise Linux Native Installation
############################################

.. _rhel-register-repo:

Registering Repositories
************************

Register Kernel-Mode Driver
===========================


.. datatemplate:nodata::

    .. tab-set::
        {% for (os_release, os_version) in [('8', '8.8'), ('8', '8.7'), ('9', '9.2'), ('9', '9.1')] %}
        .. tab-item:: RHEL {{ os_version }}
            :sync: rhel-{{ os_version }} rhel-{{ os_release }}

            .. code-block:: bash
                :substitutions:

                sudo tee /etc/yum.repos.d/amdgpu.repo <<EOF
                [amdgpu]
                name=amdgpu
                baseurl=https://repo.radeon.com/amdgpu/|rocm_version|/rhel/{{ os_version }}/main/x86_64/
                enabled=1
                priority=50
                gpgcheck=1
                gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
                EOF
                sudo yum clean all
        {% endfor %}

.. _rhel-register-rocm:

Register ROCm packages
======================


.. datatemplate:nodata::

    .. tab-set::
        {% for os_release in ['8', '9'] %}
        .. tab-item:: RHEL {{ os_release }}
            :sync: rhel-{{ os_release }}

            .. code-block:: bash
                :substitutions:

                sudo tee --append /etc/yum.repos.d/rocm.repo <<EOF
                [ROCm-|rocm_version|]
                name=ROCm|rocm_version|
                baseurl=https://repo.radeon.com/rocm/thel{{ os_release }}/|rocm_version|/main
                enabled=1
                priority=50
                gpgcheck=1
                gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
                EOF

                sudo yum clean all
        {% endfor %}

.. _rhel-install:

Installation
************

Install Kernel Driver
=====================

.. code-block:: bash

    sudo yum install amdgpu-dkms
    sudo reboot

Install ROCm Packages
=====================

.. code-block:: bash

    sudo yum install rocm-hip-sdk

Perform :doc:`post-install`.

Upgrading
*********

To upgrade an existing ROCm installation to a newer version, follow the steps in
:ref:`rhel-register-repo` and :ref:`rhel-install`.

.. _rhel-uninstall:

Uninstalling
************

Uninstalling Specific Meta-Packages
===================================

.. code-block:: bash
    :substitutions:

    # sudo apt autoremove <package-name>
    # For example:
    sudo yum remove rocm-hip-sdk
    # Or for version specific packages:
    sudo yum remove rocm-hip-sdk|rocm_version|

Complete Uninstallation of ROCm Packages
========================================

.. code-block:: bash
    :substitutions:

    sudo yum remove rocm-core
    # Or for version specific packages:
    sudo yum remove rocm-core|rocm_version|

Uninstall Kernel-Mode Driver
============================

.. code-block:: bash

    sudo yum remove  amdgpu-dkms

Remove ROCm and AMDGPU Repositories
===================================

.. code-block:: bash

    # Remove the repositories.
    sudo rm /etc/yum.repos.d/rocm.list
    sudo rm /etc/yum.repos.d/amdgpu.list

    # Clear the cache and clean the system.
    sudo rm -rf /var/cache/yum
    sudo yum clean all

    # Restart the system.
    sudo reboot
