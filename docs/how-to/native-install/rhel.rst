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
        {% for (os_release, os_version) in config.html_context['rhel_version_numbers'] %}
        .. tab-item:: RHEL {{ os_version }}
            :sync: rhel-{{ os_version }} rhel-{{ os_release }}

            .. code-block:: bash
                :substitutions:

                for ver in 5.3 5.3.2 5.3.3 5.4 5.4.1 5.4.2 5.4.3 5.4.5 5.4.6 5.5 5.5.1 5.5.2 5.5.3 5.6 5.6.1 5.7 5.7.1 5.7.2 5.7.3 6.0 6.0.1 6.0.2; do
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

                for ver in 5.3 5.3.2 5.3.3 5.4 5.4.1 5.4.2 5.4.3 5.4.5 5.4.6 5.5 5.5.1 5.5.2 5.5.3 5.6 5.6.1 5.7 5.7.1 5.7.2 5.7.3 6.0 6.0.1 6.0.2; do
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

.. _rhel-install:

.. include:: install-rocm-template.rst

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
