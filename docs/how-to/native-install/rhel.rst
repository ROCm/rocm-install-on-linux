.. meta::
  :description: Red Hat Enterprise Linux native installation
  :keywords: ROCm install, installation instructions, RHEL, Red Hat Enterprise Linux native installation,
    AMD, ROCm

**********************************************************************************************
Red Hat Enterprise Linux native installation
**********************************************************************************************

.. _rhel-register-repo:

Register repositories
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
                baseurl=https://repo.radeon.com/amdgpu/|rocm_version|/rhel/{{ os_version }}/main/x86_64/
                enabled=1
                priority=50
                gpgcheck=1
                gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
                EOF
                sudo yum clean all
        {% if os_version == '9.4' %}
            .. note::

                RHEL 9.4 is supported only on AMD Instinct MI300A.
        {% endif %}
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
                baseurl=https://repo.radeon.com/rocm/rhel{{ os_release }}/|rocm_version|/main
                enabled=1
                priority=50
                gpgcheck=1
                gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
                EOF

                sudo yum clean all
        {% endfor %}

.. _rhel-install:

.. include:: install-rocm-template.rst

.. _rhel-multi-install:

Multi-version install
=====================================================

Multi-version install is for the special case, when you need multiple versions of ROCm
on the same machine, not just the newest. If you just want to install the latest use
the steps in :ref:`rhel-register-repo` and :ref:`rhel-install`.

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

                for ver in |rocm_multi_versions|; do
                sudo tee /etc/yum.repos.d/amdgpu.repo <<EOF
                [amdgpu]
                name=amdgpu
                baseurl=https://repo.radeon.com/amdgpu/$ver/rhel/{{ os_version }}/main/x86_64/
                enabled=1
                priority=50
                gpgcheck=1
                gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
                EOF
                done
                sudo yum clean all
        {% if os_version == '9.4' %}
            .. note::

                RHEL 9.4 is only supported on AMD Instinct MI300A.
        {% endif %}
        {% endfor %}

.. _rhel-multi-register-rocm:

Register ROCm packages
----------------------------------------------------------------------------------------------------------

.. datatemplate:nodata::

    .. tab-set::
        {% for os_release in config.html_context['rhel_release_version_numbers']  %}
        .. tab-item:: RHEL {{ os_release }}
            :sync: rhel-{{ os_release }}

            .. code-block:: bash
                :substitutions:

                for ver in |rocm_multi_versions|; do
                sudo tee --append /etc/yum.repos.d/rocm.repo <<EOF
                [ROCm-$ver]
                name=ROCm|rocm_version|
                baseurl=https://repo.radeon.com/rocm/rhel{{ os_release }}/$ver/main
                enabled=1
                priority=50
                gpgcheck=1
                gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
                EOF
                done

                sudo yum clean all
        {% endfor %}

Installing
----------------------------------------------------------------------------------------------------------

Install kernel driver.

.. code-block:: bash

    sudo yum install amdgpu-dkms
    sudo reboot

Install ROCm packages.

.. code-block:: bash
    :substitutions:

    for ver in |rocm_multi_versions|; do
        sudo yum install rocm$ver
    done

Complete the :doc:`post-install`.

.. _rhel-upgrade:

Upgrade
=====================================================

To upgrade an existing ROCm installation to a newer version, follow the steps in
:ref:`rhel-register-repo` and :ref:`rhel-install`.

.. note::

    Upgrading the kernel driver may also upgrade the GPU firmware, which requires a
    system reboot to take effect.

.. _rhel-uninstall:

.. include:: uninstall-rocm-template.rst
