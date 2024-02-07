.. meta::
  :description: SUSE Enterprise Linux native installation
  :keywords: ROCm install, installation instructions, SUSE, SUSE Linux Enterprise native installation,
    AMD, ROCm

*********************************************************************************************
SUSE Linux Enterprise native installation
*********************************************************************************************

.. _sles-register-rocm:

Registering ROCm repositories
===============================================

Register kernel-mode driver
--------------------------------------------------------------------------------------


.. datatemplate:nodata::

    .. tab-set::
        {% for os_version in config.html_context['sles_version_numbers'] %}
        .. tab-item:: SLES {{ os_version }}

            .. code-block:: bash
                :substitutions:

                sudo tee /etc/zypp/repos.d/amdgpu.repo <<EOF
                [amdgpu]
                name=amdgpu
                baseurl=https://repo.radeon.com/amdgpu/|rocm_version|/sle/{{ os_version }}/main/x86_64/
                enabled=1
                gpgcheck=1
                gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
                EOF

                sudo zypper ref
        {% endfor %}

Register ROCm packages
--------------------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    sudo tee --append /etc/zypp/repos.d/rocm.repo <<EOF
    [ROCm-|rocm_version|]
    name=ROCm|rocm_version|
    baseurl=https://repo.radeon.com/rocm/zyp/|rocm_version|/main
    enabled=1
    gpgcheck=1
    gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
    EOF

    sudo zypper ref

.. _sles-install:

Installing
===============================================

Install kernel driver
--------------------------------------------------------------------------------------

.. code-block:: bash

    sudo zypper --gpg-auto-import-keys install amdgpu-dkms
    sudo reboot

Install ROCm packages
--------------------------------------------------------------------------------------

.. code-block:: bash

    sudo zypper --gpg-auto-import-keys install rocm

Complete the :doc:`post-install`.

Upgrading
================================================

To upgrade an existing ROCm installation to a newer version, follow the steps in
:ref:`sles-register-rocm` and :ref:`sles-install`. Upgrading the kernel
driver may also upgrade the GPU firmware, which requires a system reboot to
take effect.

Uninstalling
================================================

Uninstall specific meta packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    # sudo zypper remove <package-name>
    # For example:
    sudo zypper remove rocm
    # Or for version specific packages:
    sudo zypper remove rocm|rocm_version|

Uninstall ROCm packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    sudo zypper remove rocm-core
    # Or for version specific packages:
    sudo zypper remove rocm-core|rocm_version|

Uninstall kernel-mode driver
---------------------------------------------------------------------------

.. code-block:: bash

    sudo zypper remove --clean-deps amdgpu-dkms

Remove ROCm and AMDGPU repositories
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    # Remove the repositories.
    # sudo zypper removerepo <rocm*/amdgpu>
    #
    # The name of the repositories can be listed with:
    sudo zypper repos
    
    # Then remove the 'ROCm' and 'amdgpu' repositories.
    # For example:
    sudo zypper removerepo ROCm-|rocm_version|
    sudo zypper removerepo amdgpu

    # Clear the cache and clean the system.
    sudo zypper clean --all

    # Restart the system.
    sudo reboot
