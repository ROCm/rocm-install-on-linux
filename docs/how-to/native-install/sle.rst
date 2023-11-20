SUSE Linux Enterprise Native Installation
#########################################

Registering ROCm Repositories
*****************************

Register Kernel-Mode Driver
===========================


.. datatemplate:nodata::

    .. tab-set::
        {% for os_version in ['15.5', '15.4'] %}
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

Register ROCm Packages
======================

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

Installation
************

Install Kernel Driver
=====================

.. code-block:: bash

    sudo zypper --gpg-auto-import-keys install amdgpu-dkms
    sudo reboot

Install ROCm Packages
=====================

.. code-block:: bash

    sudo zypper --gpg-auto-import-keys install rocm-hip-sdk

Perform :doc:`post-install`.
