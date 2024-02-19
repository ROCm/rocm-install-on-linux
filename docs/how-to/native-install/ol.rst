.. meta::
  :description: Oracle Linux native installation
  :keywords: ROCm install, installation instructions, OL, Oracle Linux  native installation,
    AMD, ROCm

**********************************************************************************************
Oracle Linux native installation
**********************************************************************************************

.. _ol-register-repo:

Register repositories
=====================================================

Register kernel-mode driver
----------------------------------------------------------------------------------------------------------

.. datatemplate:nodata::

    .. tab-set::
        {% for (os_release, os_version) in config.html_context['ol_version_numbers'] %}
        .. tab-item:: {{ os_version }}
            :sync: ol-{{ os_version }} ol-{{ os_release }}

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

.. _ol-register-rocm:

Register ROCm packages
----------------------------------------------------------------------------------------------------------

.. datatemplate:nodata::

    .. tab-set::
        {% for os_release in config.html_context['ol_release_version_numbers'] %}
        .. tab-item:: {{ os_release }}
            :sync: ol-{{ os_release }}

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

.. _ol-install:

.. include:: install-rocm-template.rst

Upgrade
=====================================================

To upgrade an existing ROCm installation to a newer version, follow the steps in
:ref:`ol-register-repo` and :ref:`ol-install`. 

.. note::

    Upgrading the kernel driver may also upgrade the GPU firmware, which requires a
    system reboot to take effect.

.. _ol-uninstall:

.. include:: uninstall-rocm-template.rst