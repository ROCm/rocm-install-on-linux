.. _sles-multi-install:

Multi-version install is for the special case, when you need multiple versions of ROCm
on the same machine, not just the newest. If you just want to install the latest use
the steps in :ref:`sles-register-rocm` and :ref:`sles-install`.

.. rubric:: Register kernel-mode driver

This step is the same as previously described, follow the steps in :ref:`sles-register-driver`.

.. rubric:: Register ROCm packages

.. code-block:: bash
    :substitutions:

    for ver in |rocm_multi_versions|; do
    sudo tee --append /etc/zypp/repos.d/rocm.repo <<EOF
    [ROCm-$ver]
    name=ROCm$ver
    baseurl=https://repo.radeon.com/rocm/zyp/$ver/main
    enabled=1
    gpgcheck=1
    gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
    EOF
    done

    sudo zypper ref

.. rubric:: Installing

Install kernel driver.

.. code-block:: bash

    sudo zypper --gpg-auto-import-keys install amdgpu-dkms
    sudo reboot

Install ROCm packages.

.. code-block:: bash
    :substitutions:

    for ver in |rocm_multi_versions|; do
        sudo zypper --gpg-auto-import-keys install rocm$ver
    done

Complete the :doc:`post-install`.
